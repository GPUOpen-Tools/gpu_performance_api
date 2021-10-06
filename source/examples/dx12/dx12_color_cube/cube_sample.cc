//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Cube Sample.
//==============================================================================

#include "examples\dx12\dx12_color_cube\cube_sample.h"

#include <Windows.h>

#include <cassert>
#include <chrono>
#include <codecvt>
#include <iomanip>
#include <locale>
#include <string>
#include <thread>
#include <vector>

#include <D3DCompiler.h>

#include "examples\dx12\sample.h"

extern const unsigned int kWindowWidth     = 800;
extern const unsigned int kWindowHeight    = 800;
extern const std::wstring kWindowClassName = L"D3D12 Cube Sample";

HWND              window_handle                   = nullptr;  ///< Window handle.
CubeSample*       CubeSample::cube_sample         = nullptr;  ///< CubeSample static instance.
GpaApiManager*    GpaApiManager::gpa_api_manager_ = nullptr;  ///< GPA API Manager.
GpaFuncTableInfo* gpa_function_table_info         = nullptr;  ///< GPA Function table.

bool any_errors_logged = false;  ///< Flag indicating if any GPA errors have been logged.

void LogGPA(GpaLoggingType logging_type, const char* log_message)
{
    CubeSample::Instance()->GpaLog(logging_type, log_message);
}

#define MAKE_STRING(X) #X

LRESULT CALLBACK SampleWindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    static unsigned int paint_count = 0;

    switch (uMsg)
    {
    case WM_SHOWWINDOW:
    {
        // Initialize app here.
        CubeSample::Instance()->Init();

        if (args.use_gpa)
        {
            bool gpa_ok = CubeSample::Instance()->GpaInitializeAndOpenContext();

            if (!gpa_ok)
            {
                PostQuitMessage(-1);
            }
        }

        return 0;
    }

    case WM_PAINT:
    {
        bool session_created = CubeSample::Instance()->GpaCreateProfilingSession();
        bool session_started = false;

        if (session_created)
        {
            if (CubeSample::Instance()->GpaEnableCounters())
            {
                session_started = CubeSample::Instance()->GpaBeginProfilingSession();
            }
            else
            {
                CubeSample::Instance()->GpaDeleteProfilingSession();
            }
        }
        do
        {
            bool pass_started = false;

            if (session_started)
            {
                pass_started = CubeSample::Instance()->GpaBeginPass();
            }

            // Draw the cube.
            CubeSample::Instance()->Draw();

            if (pass_started)
            {
                CubeSample::Instance()->GpaEndPass();
            }
        } while (CubeSample::Instance()->GpaNextPassNeeded());

        bool session_ended = false;

        if (session_started)
        {
            session_ended = CubeSample::Instance()->GpaEndProfilingSession();
        }

        if (session_ended)
        {
            CubeSample::Instance()->GpaPopulateSessionResult();

            if (session_created)
            {
                CubeSample::Instance()->GpaDeleteProfilingSession();
            }
        }

        paint_count++;

        if (args.num_frames > 0 && paint_count >= args.num_frames)
        {
            // If the user specified a number of frames, and we've rendered that many frames, then exit.
            PostQuitMessage(0);
        }

        return 0;
    }

    case WM_DESTROY:
        // Destroy app here.
        if (args.use_gpa)
        {
            CubeSample::Instance()->GpaReleaseContextAndDestroy();
        }

        CubeSample::Instance()->Destroy();
        PostQuitMessage(0);
        return 0;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case 0x50:  // Keyboard P for profiling.
            CubeSample::Instance()->ToggleProfiling();
            break;

        case 0x57:  // Keyboard W for wireframe.
            CubeSample::Instance()->ToggleWireFrame();
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

CubeSample* CubeSample::Instance()
{
    if (nullptr == cube_sample)
    {
        cube_sample = new (std::nothrow) CubeSample();
    }

    return cube_sample;
}

CubeSample::CubeSample()
    : d3d12_device_(nullptr)
    , d3d12_root_signature_(nullptr)
    , device_id_(0)
    , revision_id_(0)
#ifdef _DEBUG
    , d3d12_debug_interface(nullptr)
    , dxgi_debug_(nullptr)
#endif
    , dxgi_factory_2_(nullptr)
    , fill_draw_pipeline_(nullptr)
    , wire_frame_pipeline_(nullptr)
    , vertex_buffer_(nullptr)
    , vertex_buffer_view_()
    , index_buffer_(nullptr)
    , index_buffer_view_()
    , scissor_rect_()
    , rtv_resource_{nullptr, nullptr}
    , fence_event_(nullptr)
    , d3d12_fence_(nullptr)
    , fence_value_(0u)
    , dxgi_swap_chain_3_(nullptr)
    , current_back_buffer_index_(0u)
    , current_pipeline_state_(nullptr)
    , d3d12_descriptor_heap_(nullptr)
    , rtv_view_desc_size(0u)
    , d3d12_command_queue_(nullptr)
    , pipeline_state_changed_(false)
    , wire_frame_(false)
    , profiling_enable_(true)
    , frame_counter_(0u)
    , is_header_written_(false)
    , gpa_function_table_(nullptr)
    , gpa_context_id_(nullptr)
    , gpa_session_id_(nullptr)
    , num_passes_required_(0u)
    , current_pass_(-1)
    , sample_counter_(-1)
{
}

void CubeSample::Init()
{
    std::vector<char> module_path(_MAX_PATH);

    ::GetModuleFileNameA(0, module_path.data(), static_cast<DWORD>(module_path.size()));

    std::string path_only(module_path.data());

    executable_path_ = path_only.substr(0, path_only.find_last_of('\\') + 1);

    if (InitializeCommonResource())
    {
        UploadCubeData();

        if (InitializeViewPortResource())
        {
            scissor_rect_.left   = 0l;
            scissor_rect_.top    = 0l;
            scissor_rect_.right  = 800l;
            scissor_rect_.bottom = 800l;

            counter_file_name_ = std::string(executable_path_.begin(), executable_path_.end()).append("D3D12ColorCube_counterData.csv");
            gpa_log_file_name_ = std::string(executable_path_.begin(), executable_path_.end()).append("D3D12ColorCube_gpaLog.txt");

            wire_frame_ = false;
        }
    }
}

bool CubeSample::InitializeCommonResource()
{
    HRESULT result             = S_OK;
    UINT    dxgi_factory_flags = 0;

    // Enable Debug layer.
#ifdef _DEBUG
    result = D3D12GetDebugInterface(__uuidof(ID3D12Debug), reinterpret_cast<void**>(&d3d12_debug_interface));

    if (FAILED(result))
    {
        return false;
    }

    d3d12_debug_interface->EnableDebugLayer();
    dxgi_factory_flags |= DXGI_CREATE_FACTORY_DEBUG;
    AddIUnknown(d3d12_debug_interface, MAKE_STRING(d3d12_debug_interface));

    HMODULE dxgi_handle = GetModuleHandle(L"Dxgidebug.dll");

    if (nullptr != dxgi_handle)
    {
        decltype(DXGIGetDebugInterface)* dxgi_debug_function =
            reinterpret_cast<decltype(DXGIGetDebugInterface)*>(GetProcAddress(dxgi_handle, "DXGIGetDebugInterface"));

        if (nullptr != dxgi_debug_function)
        {
            result = dxgi_debug_function(__uuidof(IDXGIDebug), reinterpret_cast<void**>(&dxgi_debug_));

            if (SUCCEEDED(result))
            {
                dxgi_debug_->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                AddIUnknown(dxgi_debug_, MAKE_STRING(dxgi_debug_));
            }
        }
    }

#endif

    result = CreateDXGIFactory2(dxgi_factory_flags, __uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgi_factory_2_));

    if (FAILED(result))
    {
        return false;
    }

    AddIUnknown(dxgi_factory_2_, MAKE_STRING(dxgi_factory_2_));
    unsigned int                adapter_count = 0;
    std::vector<IDXGIAdapter1*> dxgi_adapters;
    IDXGIAdapter1*              dxgi_adapter_1 = nullptr;

    // Description flag is only available in type IDXGIAdapter1 and later.
    while (SUCCEEDED(dxgi_factory_2_->EnumAdapters1(adapter_count, &dxgi_adapter_1)))
    {
        DXGI_ADAPTER_DESC1 adapter_desc_1;
        dxgi_adapter_1->GetDesc1(&adapter_desc_1);

        if (!(adapter_desc_1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE))
        {
            dxgi_adapters.push_back(dxgi_adapter_1);
            AddIUnknown(dxgi_adapter_1, MAKE_STRING(dxgi_adapter_1));
        }

        adapter_count++;
        dxgi_adapter_1 = nullptr;
    }

    if (!dxgi_adapters.empty())
    {
        dxgi_adapter_1 = dxgi_adapters.at(0);  // Pick first hardware adapter to create the device.

        // Create the device.
        result = D3D12CreateDevice(dxgi_adapter_1, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), reinterpret_cast<void**>(&d3d12_device_));

        if (FAILED(result))
        {
            return false;
        }

        AddIUnknown(d3d12_device_, MAKE_STRING(d3d12_device_));
        result = dxgi_factory_2_->MakeWindowAssociation(window_handle, DXGI_MWA_NO_ALT_ENTER);  // This will ensure Alt-Enter won't work.

        if (FAILED(result))
        {
            return false;
        }

        // Unlike older APIs, DX12 swap chains can only be created
        // on command queue rather than on the device - create a command queue first.
        D3D12_COMMAND_QUEUE_DESC command_queue_desc = {};
        command_queue_desc.Type                     = D3D12_COMMAND_LIST_TYPE_DIRECT;
        command_queue_desc.Priority                 = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
        command_queue_desc.Flags                    = D3D12_COMMAND_QUEUE_FLAG_NONE;
        command_queue_desc.NodeMask                 = 0;

        result = d3d12_device_->CreateCommandQueue(&command_queue_desc, __uuidof(ID3D12CommandQueue), reinterpret_cast<void**>(&d3d12_command_queue_));

        if (FAILED(result))
        {
            return false;
        }

        AddIUnknown(d3d12_command_queue_, MAKE_STRING(d3d12_command_queue_));

        // Create swap chain.
        DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};
        swap_chain_desc.Width                 = kWindowWidth;
        swap_chain_desc.Height                = kWindowHeight;
        swap_chain_desc.Format                = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.Scaling               = DXGI_SCALING_NONE;
        swap_chain_desc.Stereo                = false;
        swap_chain_desc.SampleDesc.Count      = 1;
        swap_chain_desc.SampleDesc.Quality    = 0;  // Irrelevant.
        swap_chain_desc.BufferCount           = kFrameCount;
        swap_chain_desc.BufferUsage           = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.SwapEffect            = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swap_chain_desc.Flags                 = NULL;

        IDXGISwapChain1* dxgi_swap_chain_1 = nullptr;
        result = dxgi_factory_2_->CreateSwapChainForHwnd(d3d12_command_queue_, window_handle, &swap_chain_desc, nullptr, nullptr, &dxgi_swap_chain_1);

        if (FAILED(result))
        {
            return false;
        }

        result = dxgi_swap_chain_1->QueryInterface(__uuidof(IDXGISwapChain3), reinterpret_cast<void**>(&dxgi_swap_chain_3_));

        if (FAILED(result))
        {
            return false;
        }

        dxgi_swap_chain_3_->Release();
        AddIUnknown(dxgi_swap_chain_3_, MAKE_STRING(dxgi_swap_chain_3_));

        // Create a descriptor heap for render targets.
        D3D12_DESCRIPTOR_HEAP_DESC rtv_description_heap = {};
        rtv_description_heap.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtv_description_heap.NumDescriptors             = kFrameCount;  // 2 RTVs for each view port.
        rtv_description_heap.Flags                      = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        rtv_description_heap.NodeMask                   = 0;
        result = d3d12_device_->CreateDescriptorHeap(&rtv_description_heap, __uuidof(ID3D12DescriptorHeap), reinterpret_cast<void**>(&d3d12_descriptor_heap_));

        if (FAILED(result))
        {
            return false;
        }

        AddIUnknown(d3d12_descriptor_heap_, MAKE_STRING(d3d12_descriptor_heap_));

        rtv_view_desc_size                                = d3d12_device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE cpu_descriptor_handle = d3d12_descriptor_heap_->GetCPUDescriptorHandleForHeapStart();

        // Create RTV resources for the swap chain RTV.
        for (unsigned int i = 0; i < kFrameCount; i++)
        {
            // Create the render target view resource in swap chain buffer.
            result = dxgi_swap_chain_3_->GetBuffer(i, __uuidof(ID3D12Resource), reinterpret_cast<void**>(&rtv_resource_[i]));

            if (FAILED(result))
            {
                return false;
            }

            d3d12_device_->CreateRenderTargetView(rtv_resource_[i], nullptr, cpu_descriptor_handle);
            cpu_descriptor_handle.ptr = cpu_descriptor_handle.ptr + rtv_view_desc_size;  // Offset to next descriptor.
            AddIUnknown(rtv_resource_[i], MAKE_STRING(rtv_resource_[i]));
        }

        result = d3d12_device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), reinterpret_cast<void**>(&d3d12_fence_));

        if (FAILED(result))
        {
            return false;
        }

        AddIUnknown(d3d12_fence_, MAKE_STRING(d3d12_fence_));
        fence_event_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);

        if (nullptr != fence_event_)
        {
            // Create root signature.
            D3D12_ROOT_SIGNATURE_DESC root_signature_desc = {};
            root_signature_desc.NumParameters             = 0;
            root_signature_desc.pParameters               = nullptr;
            root_signature_desc.NumStaticSamplers         = 0;
            root_signature_desc.pStaticSamplers           = nullptr;
            root_signature_desc.Flags                     = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

            ID3DBlob* serialized_signature = nullptr;
            ID3DBlob* serialization_error  = nullptr;

            result = D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &serialized_signature, &serialization_error);

            if (FAILED(result))
            {
                return false;
            }

            result = d3d12_device_->CreateRootSignature(0,
                                                        serialized_signature->GetBufferPointer(),
                                                        serialized_signature->GetBufferSize(),
                                                        __uuidof(ID3D12RootSignature),
                                                        reinterpret_cast<void**>(&d3d12_root_signature_));

            if (FAILED(result))
            {
                return false;
            }

            AddIUnknown(d3d12_root_signature_, MAKE_STRING(d3d12_root_signature_));
            ID3DBlob* vertex_shader = nullptr;
            ID3DBlob* pixel_shader  = nullptr;
            ID3DBlob* error         = nullptr;

            UINT compile_flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wide_to_utf8_converter;

            std::wstring shader_path = wide_to_utf8_converter.from_bytes(executable_path_);
            shader_path.append(L"shaders.hlsl");

            result = ::D3DCompileFromFile(shader_path.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compile_flags, 0, &vertex_shader, &error);

            if (FAILED(result))
            {
                return false;
            }

            result = ::D3DCompileFromFile(shader_path.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compile_flags, 0, &pixel_shader, &error);

            if (FAILED(result))
            {
                return false;
            }

            D3D12_SHADER_BYTECODE vertex_shader_data = {vertex_shader->GetBufferPointer(), vertex_shader->GetBufferSize()};
            D3D12_SHADER_BYTECODE pixel_shader_data  = {pixel_shader->GetBufferPointer(), pixel_shader->GetBufferSize()};

            // Create graphics pipeline using root signature - one for wireframe and another for fill drawing.
            D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_obj_desc = {};
            pso_obj_desc.pRootSignature                     = d3d12_root_signature_;
            pso_obj_desc.VS                                 = vertex_shader_data;
            pso_obj_desc.PS                                 = pixel_shader_data;
            pso_obj_desc.BlendState                         = {};

            const D3D12_RENDER_TARGET_BLEND_DESC default_rt_blend_desc = {FALSE,
                                                                          FALSE,
                                                                          D3D12_BLEND_ONE,
                                                                          D3D12_BLEND_ZERO,
                                                                          D3D12_BLEND_OP_ADD,
                                                                          D3D12_BLEND_ONE,
                                                                          D3D12_BLEND_ZERO,
                                                                          D3D12_BLEND_OP_ADD,
                                                                          D3D12_LOGIC_OP_NOOP,
                                                                          D3D12_COLOR_WRITE_ENABLE_ALL};

            pso_obj_desc.BlendState.AlphaToCoverageEnable  = FALSE;
            pso_obj_desc.BlendState.IndependentBlendEnable = FALSE;

            for (auto& pso_blend_rt_iter : pso_obj_desc.BlendState.RenderTarget)
            {
                pso_blend_rt_iter = default_rt_blend_desc;
            }

            pso_obj_desc.RasterizerState.FillMode              = D3D12_FILL_MODE_SOLID;
            pso_obj_desc.RasterizerState.CullMode              = D3D12_CULL_MODE_BACK;
            pso_obj_desc.RasterizerState.FrontCounterClockwise = FALSE;
            pso_obj_desc.RasterizerState.DepthBias             = D3D12_DEFAULT_DEPTH_BIAS;
            pso_obj_desc.RasterizerState.DepthBiasClamp        = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
            pso_obj_desc.RasterizerState.SlopeScaledDepthBias  = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
            pso_obj_desc.RasterizerState.DepthClipEnable       = TRUE;
            pso_obj_desc.RasterizerState.MultisampleEnable     = FALSE;
            pso_obj_desc.RasterizerState.AntialiasedLineEnable = FALSE;
            pso_obj_desc.RasterizerState.ForcedSampleCount     = 0;
            pso_obj_desc.RasterizerState.ConservativeRaster    = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

            pso_obj_desc.DepthStencilState                = {};
            pso_obj_desc.DepthStencilState.DepthEnable    = true;
            pso_obj_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
            pso_obj_desc.DepthStencilState.DepthFunc      = D3D12_COMPARISON_FUNC_LESS_EQUAL;
            pso_obj_desc.SampleMask                       = UINT_MAX;

            D3D12_INPUT_ELEMENT_DESC vertex_input_desc[] = {
                {"SCREEN_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
                {"VERTEX_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}};

            pso_obj_desc.InputLayout           = {vertex_input_desc, 2};  // Passing 2 elements - vertex and color.
            pso_obj_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
            pso_obj_desc.NumRenderTargets      = 1;
            pso_obj_desc.RTVFormats[0]         = DXGI_FORMAT_R8G8B8A8_UNORM;
            pso_obj_desc.SampleDesc.Count      = 1;

            result = d3d12_device_->CreateGraphicsPipelineState(&pso_obj_desc, __uuidof(ID3D12PipelineState), reinterpret_cast<void**>(&fill_draw_pipeline_));

            if (FAILED(result))
            {
                return false;
            }

            AddIUnknown(fill_draw_pipeline_, MAKE_STRING(fill_draw_pipeline_));
            current_pipeline_state_ = fill_draw_pipeline_;

            pso_obj_desc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
            result = d3d12_device_->CreateGraphicsPipelineState(&pso_obj_desc, __uuidof(ID3D12PipelineState), reinterpret_cast<void**>(&wire_frame_pipeline_));

            if (FAILED(result))
            {
                return false;
            }

            AddIUnknown(wire_frame_pipeline_, MAKE_STRING(wire_frame_pipeline_));
            return true;
        }
    }

    return false;
}

bool CubeSample::InitializeViewPortResource()
{
    return top_left_viewport_.Init() && top_right_viewport_.Init() && bottom_left_viewport_.Init() && bottom_right_viewport_.Init();
}

bool CubeSample::UploadCubeData()
{
    bool success = false;

    VertexData vertex_color_data[] = {
        {{-0.5, 0.5, -0.5, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},   // 0
        {{0.5, 0.5, -0.5, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},    // 1
        {{0.5, -0.5, -0.5, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},   // 2
        {{-0.5, -0.5, -0.5, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},  // 3
        {{-0.5, 0.5, 0.5, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},    // 4
        {{0.5, 0.5, 0.5, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},     // 5
        {{0.5, -0.5, 0.5, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},    // 6
        {{-0.5, -0.5, 0.5, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}    // 7
    };

    uint32_t index_data[] = {
        0, 1, 3, 3, 1, 2,  // -Z face
        7, 4, 5, 7, 5, 6,  // +Z face

        7, 0, 4, 7, 3, 0,  // -X face
        6, 5, 1, 6, 1, 2,  // +X face

        7, 2, 3, 7, 6, 2,  // -Y face
        4, 0, 5, 5, 0, 1,  // +Y face
    };

#pragma region VertexBuffer
    {
        D3D12_RESOURCE_DESC vertex_data_buffer_resource_desc = {};
        vertex_data_buffer_resource_desc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
        vertex_data_buffer_resource_desc.Alignment           = 0;
        vertex_data_buffer_resource_desc.Width               = sizeof(vertex_color_data);
        vertex_data_buffer_resource_desc.Height = vertex_data_buffer_resource_desc.DepthOrArraySize = vertex_data_buffer_resource_desc.MipLevels = 1;
        vertex_data_buffer_resource_desc.Format             = DXGI_FORMAT_UNKNOWN;
        vertex_data_buffer_resource_desc.SampleDesc.Count   = 1;
        vertex_data_buffer_resource_desc.SampleDesc.Quality = 0;
        vertex_data_buffer_resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        vertex_data_buffer_resource_desc.Flags              = D3D12_RESOURCE_FLAG_NONE;

        D3D12_HEAP_PROPERTIES buffer_heap_properties = {};
        buffer_heap_properties.Type                  = D3D12_HEAP_TYPE_UPLOAD;
        buffer_heap_properties.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        buffer_heap_properties.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;
        buffer_heap_properties.CreationNodeMask      = 1;
        buffer_heap_properties.VisibleNodeMask       = 1;

        // Create vertex data resource.
        HRESULT result = d3d12_device_->CreateCommittedResource(&buffer_heap_properties,
                                                                D3D12_HEAP_FLAG_NONE,
                                                                &vertex_data_buffer_resource_desc,
                                                                D3D12_RESOURCE_STATE_GENERIC_READ,
                                                                nullptr,
                                                                __uuidof(ID3D12Resource),
                                                                reinterpret_cast<void**>(&vertex_buffer_));

        if (SUCCEEDED(result))
        {
            AddIUnknown(vertex_buffer_, MAKE_STRING(vertex_buffer_));
            D3D12_RANGE cpu_allowed_read_range = {};
            cpu_allowed_read_range.Begin       = 0;  // We won't be reading this from CPU after uploading the data.
            cpu_allowed_read_range.End         = 0;  // We won't be reading this from CPU after uploading the data.

            void* vertex_buffer_cpu_location = nullptr;
            // Get the CPU pointer where we will upload the vertex data.
            result = vertex_buffer_->Map(0, &cpu_allowed_read_range, &vertex_buffer_cpu_location);

            if (SUCCEEDED(result))
            {
                // Copy the vertex data to the CPU location.
                memcpy(vertex_buffer_cpu_location, vertex_color_data, sizeof(vertex_color_data));
                D3D12_RANGE* cpu_modified_range = nullptr;  // nullptr indicates all of the buffer is modified.
                vertex_buffer_->Unmap(0, cpu_modified_range);

                vertex_buffer_view_.BufferLocation = vertex_buffer_->GetGPUVirtualAddress();
                vertex_buffer_view_.SizeInBytes    = sizeof(vertex_color_data);
                vertex_buffer_view_.StrideInBytes  = sizeof(VertexData);
                success                            = true;
            }
        }
    }
#pragma endregion

#pragma region IndexBuffer

    if (success)
    {
        D3D12_RESOURCE_DESC index_data_buffer_resource_desc = {};
        index_data_buffer_resource_desc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
        index_data_buffer_resource_desc.Alignment           = 0;
        index_data_buffer_resource_desc.Width               = sizeof(index_data);
        index_data_buffer_resource_desc.Height = index_data_buffer_resource_desc.DepthOrArraySize = index_data_buffer_resource_desc.MipLevels = 1;
        index_data_buffer_resource_desc.Format             = DXGI_FORMAT_UNKNOWN;
        index_data_buffer_resource_desc.SampleDesc.Count   = 1;
        index_data_buffer_resource_desc.SampleDesc.Quality = 0;
        index_data_buffer_resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        index_data_buffer_resource_desc.Flags              = D3D12_RESOURCE_FLAG_NONE;

        D3D12_HEAP_PROPERTIES buffer_heap_properties = {};
        buffer_heap_properties.Type                  = D3D12_HEAP_TYPE_UPLOAD;
        buffer_heap_properties.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        buffer_heap_properties.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;
        buffer_heap_properties.CreationNodeMask      = 1;
        buffer_heap_properties.VisibleNodeMask       = 1;

        // Create index buffer resource.
        HRESULT result = d3d12_device_->CreateCommittedResource(&buffer_heap_properties,
                                                                D3D12_HEAP_FLAG_NONE,
                                                                &index_data_buffer_resource_desc,
                                                                D3D12_RESOURCE_STATE_GENERIC_READ | D3D12_RESOURCE_STATE_INDEX_BUFFER,
                                                                nullptr,
                                                                __uuidof(ID3D12Resource),
                                                                reinterpret_cast<void**>(&index_buffer_));

        if (SUCCEEDED(result))
        {
            AddIUnknown(index_buffer_, MAKE_STRING(index_buffer_));
            D3D12_RANGE cpu_allowed_read_range = {};
            cpu_allowed_read_range.Begin       = 0;  // We won't be reading this from CPU after uploading the data.
            cpu_allowed_read_range.End         = 0;  // We won't be reading this from CPU after uploading the data.

            void* index_buffer_cpu_location = nullptr;
            // Get the CPU pointer where we will upload the vertex data.
            result = index_buffer_->Map(0, &cpu_allowed_read_range, &index_buffer_cpu_location);

            if (SUCCEEDED(result))
            {
                // Copy the vertex data to the CPU location.
                memcpy(index_buffer_cpu_location, index_data, sizeof(index_data));
                D3D12_RANGE* cpu_modified_range = nullptr;  // nullptr indicates all of the buffer is modified.
                index_buffer_->Unmap(0, cpu_modified_range);

                index_buffer_view_.BufferLocation = index_buffer_->GetGPUVirtualAddress();
                index_buffer_view_.SizeInBytes    = sizeof(index_data);
                index_buffer_view_.Format         = DXGI_FORMAT_R32_UINT;
                success                           = true;
            }
        }
    }

#pragma endregion

    return success;
}

void CubeSample::AddIUnknown(IUnknown* unknown, const std::string& name)
{
    ID3D12Object* object = nullptr;
    HRESULT       result = unknown->QueryInterface(__uuidof(ID3D12Object), reinterpret_cast<void**>(&object));

    std::wstring wide_name(name.begin(), name.end());

    if (SUCCEEDED(result))
    {
        result = object->SetName(wide_name.c_str());
        object->Release();
    }

    app_created_unknown_cache_.push(std::pair<std::wstring, IUnknown*>(wide_name, unknown));
}

void CubeSample::AddCommandList(ID3D12GraphicsCommandList* graphics_command_list)
{
    if (nullptr != graphics_command_list)
    {
        graphics_command_queue_.push_back(graphics_command_list);
    }
}

CubeSample::Viewport::Viewport()
    : viewport_()
    , d3d_command_list_(nullptr)
    , d3d12_direct_command_list_allocator_(nullptr)
    , viewport_initialized_(false)
    , viewport_rect_()
    , gpa_command_list_(nullptr)
    , sample_id_(kUndefinedSampleId)
{
    viewport_.Width    = 400.0f;
    viewport_.Height   = 400.0f;
    viewport_.MaxDepth = 1.0f;
    viewport_.MinDepth = -1.0f;
}

void CubeSample::WaitForGpuToFinish()
{
    // Wait for the frame to finish.
    d3d12_command_queue_->Signal(d3d12_fence_, fence_value_);
    d3d12_fence_->SetEventOnCompletion(fence_value_, fence_event_);

    WaitForSingleObject(fence_event_, INFINITE);
    fence_value_++;
    current_back_buffer_index_ = dxgi_swap_chain_3_->GetCurrentBackBufferIndex();
}

CubeSample::TopLeftViewport::TopLeftViewport()
    : Viewport()
{
    viewport_.TopLeftX    = 0.0f;
    viewport_.TopLeftY    = 0.0f;
    viewport_initialized_ = true;

    viewport_rect_ = {static_cast<long>(viewport_.TopLeftX),
                      static_cast<long>(viewport_.TopLeftY),
                      static_cast<long>(viewport_.TopLeftX + viewport_.Width),
                      static_cast<long>(viewport_.TopLeftY + viewport_.Height)};
}

bool CubeSample::TopLeftViewport::Init()
{
    if (viewport_initialized_)
    {
        HRESULT result = S_OK;

        // Create command allocator.
        result = cube_sample->d3d12_device_->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&d3d12_direct_command_list_allocator_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->AddIUnknown(d3d12_direct_command_list_allocator_, MAKE_STRING(TopLeftViewport->m_pd3d12DirectmdListAllocator));

        result = cube_sample->d3d12_device_->CreateCommandList(0,
                                                               D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                               d3d12_direct_command_list_allocator_,
                                                               cube_sample->fill_draw_pipeline_,
                                                               __uuidof(ID3D12GraphicsCommandList),
                                                               reinterpret_cast<void**>(&d3d_command_list_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->current_pipeline_state_ = cube_sample->fill_draw_pipeline_;
        d3d_command_list_->Close();
        cube_sample->current_back_buffer_index_ = cube_sample->dxgi_swap_chain_3_->GetCurrentBackBufferIndex();
        cube_sample->AddCommandList(d3d_command_list_);
        cube_sample->AddIUnknown(d3d_command_list_, MAKE_STRING(TopLeftViewport->d3d_command_list_));
        return true;
    }

    return false;
}

void CubeSample::TopLeftViewport::Draw()
{
    // In this view port, we will draw a cube on single primary command list
    // and record the performance counter with one sample using GPA.

    HRESULT result = d3d12_direct_command_list_allocator_->Reset();
    UNREFERENCED_PARAMETER(result);
    result = d3d_command_list_->Reset(d3d12_direct_command_list_allocator_, cube_sample->current_pipeline_state_);

    if (cube_sample->pipeline_state_changed_)
    {
        d3d_command_list_->SetPipelineState(cube_sample->current_pipeline_state_);
    }

    d3d_command_list_->SetGraphicsRootSignature(cube_sample->d3d12_root_signature_);
    d3d_command_list_->RSSetViewports(1, &viewport_);
    d3d_command_list_->RSSetScissorRects(1, &cube_sample->scissor_rect_);

    D3D12_RESOURCE_TRANSITION_BARRIER transition_barrier = {};
    transition_barrier.pResource                         = cube_sample->rtv_resource_[cube_sample->current_back_buffer_index_];
    transition_barrier.Subresource                       = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    transition_barrier.StateBefore                       = D3D12_RESOURCE_STATE_PRESENT;
    transition_barrier.StateAfter                        = D3D12_RESOURCE_STATE_RENDER_TARGET;

    D3D12_RESOURCE_BARRIER resource_barrier = {};
    resource_barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    resource_barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    resource_barrier.Transition             = transition_barrier;
    d3d_command_list_->ResourceBarrier(1, &resource_barrier);

    D3D12_CPU_DESCRIPTOR_HANDLE rtv_desc_heap;
    rtv_desc_heap.ptr = cube_sample->d3d12_descriptor_heap_->GetCPUDescriptorHandleForHeapStart().ptr +
                        cube_sample->current_back_buffer_index_ * cube_sample->rtv_view_desc_size;
    d3d_command_list_->OMSetRenderTargets(1, &rtv_desc_heap, FALSE, nullptr);

    if (cube_sample->current_pass_ == 0)
    {
        sample_id_ = ++cube_sample->sample_counter_;
    }

    d3d_command_list_->ClearRenderTargetView(rtv_desc_heap, kClearColor, 1, &viewport_rect_);
    d3d_command_list_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    d3d_command_list_->IASetVertexBuffers(0, 1, &cube_sample->vertex_buffer_view_);
    d3d_command_list_->IASetIndexBuffer(&cube_sample->index_buffer_view_);

#pragma region GPA_CALL
    // Request GPA to start recording samples on the command list.
    bool command_list_started = cube_sample->GpaBeginCommandListForSampling(d3d_command_list_, gpa_command_list_);
    bool sample_started       = false;

    if (command_list_started)
    {
        // Start sample on the command list.
        sample_started = cube_sample->GpaBeginSample(gpa_command_list_, sample_id_);
    }
#pragma endregion

    d3d_command_list_->DrawIndexedInstanced(36, 1, 0, 0, 0);

    transition_barrier.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    transition_barrier.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;

#pragma region GPA_CALL
    if (sample_started)
    {
        // End the sample request.
        cube_sample->GpaEndSample(gpa_command_list_);

        if (command_list_started)
        {
            // End the command list for sample recording before closing the command list.
            cube_sample->GpaEndCommandListForSampling(gpa_command_list_);
        }
    }
#pragma endregion

    // Update transition.
    resource_barrier.Transition = transition_barrier;
    d3d_command_list_->ResourceBarrier(1, &resource_barrier);
    d3d_command_list_->Close();
}

void CubeSample::TopLeftViewport::ResetForNextPass()
{
    gpa_command_list_ = nullptr;
}

void CubeSample::TopLeftViewport::IterateSamples(std::function<void(const unsigned& sample_index)> func) const
{
    if (kUndefinedSampleId != sample_id_)
    {
        func(sample_id_);
    }
}

CubeSample::TopRightViewport::TopRightViewport()
    : Viewport()
    , bundle_command_allocator_(nullptr)
    , bundle_command_list_(nullptr)
    , gpa_command_list_for_bundle_(nullptr)
    , bundle_sample_id_(0xFFFF)
{
    viewport_.TopLeftX    = 400.0f;
    viewport_.TopLeftY    = 0.0f;
    viewport_initialized_ = true;

    viewport_rect_ = {static_cast<long>(viewport_.TopLeftX),
                      static_cast<long>(viewport_.TopLeftY),
                      static_cast<long>(viewport_.TopLeftX + viewport_.Width),
                      static_cast<long>(viewport_.TopLeftY + viewport_.Height)};
}

bool CubeSample::TopRightViewport::Init()
{
    if (viewport_initialized_)
    {
        HRESULT result = S_OK;

        // Create command allocator.
        result = cube_sample->d3d12_device_->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&d3d12_direct_command_list_allocator_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->AddIUnknown(d3d12_direct_command_list_allocator_, MAKE_STRING(TopRightViewport->d3d12_direct_command_list_allocator_));

        // Create command allocator for bundles.
        result = cube_sample->d3d12_device_->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_BUNDLE, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&bundle_command_allocator_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->AddIUnknown(bundle_command_allocator_, MAKE_STRING(TopRightViewport->bundle_command_allocator_));

        result = cube_sample->d3d12_device_->CreateCommandList(0,
                                                               D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                               d3d12_direct_command_list_allocator_,
                                                               cube_sample->fill_draw_pipeline_,
                                                               __uuidof(ID3D12GraphicsCommandList),
                                                               reinterpret_cast<void**>(&d3d_command_list_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->AddIUnknown(d3d_command_list_, MAKE_STRING(TopRightViewport->d3d_command_list_));

        result = cube_sample->d3d12_device_->CreateCommandList(0,
                                                               D3D12_COMMAND_LIST_TYPE_BUNDLE,
                                                               bundle_command_allocator_,
                                                               cube_sample->fill_draw_pipeline_,
                                                               __uuidof(ID3D12GraphicsCommandList),
                                                               reinterpret_cast<void**>(&bundle_command_list_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->current_pipeline_state_ = cube_sample->fill_draw_pipeline_;
        d3d_command_list_->Close();
        bundle_command_list_->Close();
        cube_sample->current_back_buffer_index_ = cube_sample->dxgi_swap_chain_3_->GetCurrentBackBufferIndex();
        cube_sample->AddCommandList(d3d_command_list_);
        cube_sample->AddIUnknown(bundle_command_list_, MAKE_STRING(TopRightViewport->bundle_command_list_));
        return true;
    }

    return false;
}

void CubeSample::TopRightViewport::Draw()
{
    // In this view port, we will be recording drawing of a cube on a bundle and execute it using primary command list
    // Usually, bundle are recorded once and executed multiple times. However in case of multi-pass sampling, GPA must
    // record the set of counters to enable on each pass, we need to record the bundle command as like a direct command list.

    // Performance counter result for the samples on the bundles can't be retrieved directly from GPA in accordance with a fact that
    // bundle can't be executed without a direct command list. To get the result of the bundle sample, app must copy the sample over
    // direct command list with new set of sample ids after each execution of the bundle.

    HRESULT result = d3d12_direct_command_list_allocator_->Reset();
    UNREFERENCED_PARAMETER(result);
    result = d3d_command_list_->Reset(d3d12_direct_command_list_allocator_, cube_sample->current_pipeline_state_);

    result = bundle_command_allocator_->Reset();
    result = bundle_command_list_->Reset(bundle_command_allocator_, cube_sample->current_pipeline_state_);

    if (cube_sample->pipeline_state_changed_)
    {
        d3d_command_list_->SetPipelineState(cube_sample->current_pipeline_state_);
        bundle_command_list_->SetPipelineState(cube_sample->current_pipeline_state_);
    }

    if (cube_sample->current_pass_ == 0)
    {
        if (args.profile_bundles)
        {
            bundle_sample_id_ = ++cube_sample->sample_counter_;  // Bundle sample id - result can't be retrieved using this.
            sample_id_        = ++cube_sample->sample_counter_;  // Copied sample id.
        }
    }

#pragma region GPA_CALL
    bool bundle_command_list_started = false;
    bool sample_started              = false;

    if (args.profile_bundles)
    {
        // Request GPA to start recording samples on the bundle.
        bundle_command_list_started = cube_sample->GpaBeginCommandListForSampling(bundle_command_list_, gpa_command_list_for_bundle_);

        if (bundle_command_list_started)
        {
            // Start sample on the bundle.
            sample_started = cube_sample->GpaBeginSample(gpa_command_list_for_bundle_, bundle_sample_id_);
        }
    }
#pragma endregion

    bundle_command_list_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    bundle_command_list_->IASetVertexBuffers(0, 1, &cube_sample->vertex_buffer_view_);
    bundle_command_list_->IASetIndexBuffer(&cube_sample->index_buffer_view_);
    bundle_command_list_->DrawIndexedInstanced(36, 1, 0, 0, 0);

#pragma region GPA_CALL
    if (sample_started)
    {
        // End the sample request.
        cube_sample->GpaEndSample(gpa_command_list_for_bundle_);

        if (bundle_command_list_started)
        {
            // End the bundle for sample recording before closing the command list.
            cube_sample->GpaEndCommandListForSampling(gpa_command_list_for_bundle_);
        }
    }
#pragma endregion

    bundle_command_list_->Close();

    d3d_command_list_->SetGraphicsRootSignature(cube_sample->d3d12_root_signature_);
    d3d_command_list_->RSSetViewports(1, &viewport_);
    d3d_command_list_->RSSetScissorRects(1, &cube_sample->scissor_rect_);

    D3D12_RESOURCE_TRANSITION_BARRIER transition_barrier = {};
    transition_barrier.pResource                         = cube_sample->rtv_resource_[cube_sample->current_back_buffer_index_];
    transition_barrier.Subresource                       = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    transition_barrier.StateBefore                       = D3D12_RESOURCE_STATE_PRESENT;
    transition_barrier.StateAfter                        = D3D12_RESOURCE_STATE_RENDER_TARGET;

    D3D12_RESOURCE_BARRIER resource_barrier = {};
    resource_barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    resource_barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    resource_barrier.Transition             = transition_barrier;
    d3d_command_list_->ResourceBarrier(1, &resource_barrier);

    D3D12_CPU_DESCRIPTOR_HANDLE rtv_desc_heap;
    rtv_desc_heap.ptr = cube_sample->d3d12_descriptor_heap_->GetCPUDescriptorHandleForHeapStart().ptr +
                        cube_sample->current_back_buffer_index_ * cube_sample->rtv_view_desc_size;
    d3d_command_list_->OMSetRenderTargets(1, &rtv_desc_heap, FALSE, nullptr);

    d3d_command_list_->ClearRenderTargetView(rtv_desc_heap, kClearColor, 1, &viewport_rect_);

#pragma region GPA_CALL
    // Request GPA to start recording samples on the direct command list.
    bool command_list_started = cube_sample->GpaBeginCommandListForSampling(d3d_command_list_, gpa_command_list_);
#pragma endregion

    d3d_command_list_->ExecuteBundle(bundle_command_list_);

#pragma region GPA_CALL
    if (command_list_started && bundle_command_list_started)
    {
        std::vector<unsigned int> tmp_vector = {sample_id_};
        // Copy the bundle sample to the direct command list after its execution.
        cube_sample->GpaCopyBundleSample(gpa_command_list_for_bundle_, gpa_command_list_, tmp_vector);
    }
#pragma endregion

    transition_barrier.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    transition_barrier.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;

#pragma region GPA_CALL
    if (command_list_started)
    {
        // End the direct command list for sample recording before closing it.
        cube_sample->GpaEndCommandListForSampling(gpa_command_list_);
    }
#pragma endregion

    // Update transition.
    resource_barrier.Transition = transition_barrier;
    d3d_command_list_->ResourceBarrier(1, &resource_barrier);
    d3d_command_list_->Close();
}

void CubeSample::TopRightViewport::ResetForNextPass()
{
    gpa_command_list_for_bundle_ = gpa_command_list_ = nullptr;
}

void CubeSample::TopRightViewport::IterateSamples(std::function<void(const unsigned& sample_index)> func) const
{
    if (kUndefinedSampleId != sample_id_)
    {
        func(sample_id_);
    }
}

CubeSample::BottomLeftViewport::BottomLeftViewport()
    : Viewport()
    , second_command_list_allocator_(nullptr)
    , second_command_list_(nullptr)
    , gpa_command_list_for_second_command_list_(nullptr)
{
    viewport_.TopLeftX    = 0.0f;
    viewport_.TopLeftY    = 400.0f;
    viewport_initialized_ = true;

    viewport_rect_ = {static_cast<long>(viewport_.TopLeftX),
                      static_cast<long>(viewport_.TopLeftY),
                      static_cast<long>(viewport_.TopLeftX + viewport_.Width),
                      static_cast<long>(viewport_.TopLeftY + viewport_.Height)};
}

bool CubeSample::BottomLeftViewport::Init()
{
    if (viewport_initialized_)
    {
        HRESULT result = S_OK;

        // Create command allocator.
        result = cube_sample->d3d12_device_->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&d3d12_direct_command_list_allocator_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->AddIUnknown(d3d12_direct_command_list_allocator_, MAKE_STRING(BottomLeftViewport->d3d12_direct_command_list_allocator_));

        result = cube_sample->d3d12_device_->CreateCommandList(0,
                                                               D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                               d3d12_direct_command_list_allocator_,
                                                               cube_sample->fill_draw_pipeline_,
                                                               __uuidof(ID3D12GraphicsCommandList),
                                                               reinterpret_cast<void**>(&d3d_command_list_));

        if (FAILED(result))
        {
            return false;
        }

        d3d_command_list_->Close();
        cube_sample->AddCommandList(d3d_command_list_);
        cube_sample->AddIUnknown(d3d_command_list_, MAKE_STRING(BottomLeftViewport->d3d_command_list_));

        result = cube_sample->d3d12_device_->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&second_command_list_allocator_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->AddIUnknown(second_command_list_allocator_, MAKE_STRING(BottomLeftViewport->second_command_list_allocator_));

        result = cube_sample->d3d12_device_->CreateCommandList(0,
                                                               D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                               second_command_list_allocator_,
                                                               cube_sample->fill_draw_pipeline_,
                                                               __uuidof(ID3D12GraphicsCommandList),
                                                               reinterpret_cast<void**>(&second_command_list_));

        if (FAILED(result))
        {
            return false;
        }

        second_command_list_->Close();
        cube_sample->AddCommandList(second_command_list_);
        cube_sample->AddIUnknown(second_command_list_, MAKE_STRING(BottomLeftViewport->second_command_list_));

        cube_sample->current_pipeline_state_    = cube_sample->fill_draw_pipeline_;
        cube_sample->current_back_buffer_index_ = cube_sample->dxgi_swap_chain_3_->GetCurrentBackBufferIndex();

        return true;
    }

    return false;
}

void CubeSample::BottomLeftViewport::Draw()
{
    // In this view port, we will be recording drawing of a cube using two direct command list.
    // Each of the command list will draw half of the triangle, though the GPA sample for
    // performance counters will span over the command list.

    HRESULT result = d3d12_direct_command_list_allocator_->Reset();
    UNREFERENCED_PARAMETER(result);
    result = second_command_list_allocator_->Reset();
    result = d3d_command_list_->Reset(d3d12_direct_command_list_allocator_, cube_sample->current_pipeline_state_);
    result = second_command_list_->Reset(second_command_list_allocator_, cube_sample->current_pipeline_state_);

    if (cube_sample->pipeline_state_changed_)
    {
        d3d_command_list_->SetPipelineState(cube_sample->current_pipeline_state_);
        second_command_list_->SetPipelineState(cube_sample->current_pipeline_state_);
    }

    if (cube_sample->current_pass_ == 0)
    {
        sample_id_ = ++cube_sample->sample_counter_;
    }

    d3d_command_list_->SetGraphicsRootSignature(cube_sample->d3d12_root_signature_);
    d3d_command_list_->RSSetViewports(1, &viewport_);
    d3d_command_list_->RSSetScissorRects(1, &cube_sample->scissor_rect_);

    second_command_list_->SetGraphicsRootSignature(cube_sample->d3d12_root_signature_);
    second_command_list_->RSSetViewports(1, &viewport_);
    second_command_list_->RSSetScissorRects(1, &cube_sample->scissor_rect_);

    D3D12_RESOURCE_TRANSITION_BARRIER transition_barrier = {};
    transition_barrier.pResource                         = cube_sample->rtv_resource_[cube_sample->current_back_buffer_index_];
    transition_barrier.Subresource                       = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    transition_barrier.StateBefore                       = D3D12_RESOURCE_STATE_PRESENT;
    transition_barrier.StateAfter                        = D3D12_RESOURCE_STATE_RENDER_TARGET;

    D3D12_RESOURCE_BARRIER resource_barrier = {};
    resource_barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    resource_barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    resource_barrier.Transition             = transition_barrier;
    d3d_command_list_->ResourceBarrier(1, &resource_barrier);
    second_command_list_->ResourceBarrier(1, &resource_barrier);

    D3D12_CPU_DESCRIPTOR_HANDLE rtv_desc_heap;
    rtv_desc_heap.ptr = cube_sample->d3d12_descriptor_heap_->GetCPUDescriptorHandleForHeapStart().ptr +
                        cube_sample->current_back_buffer_index_ * cube_sample->rtv_view_desc_size;
    d3d_command_list_->OMSetRenderTargets(1, &rtv_desc_heap, FALSE, nullptr);
    second_command_list_->OMSetRenderTargets(1, &rtv_desc_heap, FALSE, nullptr);

    d3d_command_list_->ClearRenderTargetView(rtv_desc_heap, kClearColor, 1, &viewport_rect_);

#pragma region GPA_CALL
    // Request GPA to start recording samples on the first direct command list.
    bool command_list_started = cube_sample->GpaBeginCommandListForSampling(d3d_command_list_, gpa_command_list_);
    bool sample_started       = false;

    if (command_list_started)
    {
        // Start sample on the first direct command list i.e. gpa_command_list_.
        sample_started = cube_sample->GpaBeginSample(gpa_command_list_, sample_id_);
    }
#pragma endregion

    // Draw 1st half cube (front, back, and left side; note only the front will not be culled).
    d3d_command_list_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    d3d_command_list_->IASetVertexBuffers(0, 1, &cube_sample->vertex_buffer_view_);
    d3d_command_list_->IASetIndexBuffer(&cube_sample->index_buffer_view_);
    d3d_command_list_->DrawIndexedInstanced(18, 1, 0, 0, 0);

#pragma region GPA_CALL
    // Request GPA to start recording samples on the second direct command list.
    bool second_command_list_started = cube_sample->GpaBeginCommandListForSampling(second_command_list_, gpa_command_list_for_second_command_list_);

    if (second_command_list_started && sample_started)
    {
        // Continue the original sample to the second direct command list.
        cube_sample->GpaContinueSample(sample_id_, gpa_command_list_for_second_command_list_);
    }
#pragma endregion

    // Draw 2nd half cube (right side, bttom, and top; note all of these faces get back-face culled).
    second_command_list_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    second_command_list_->IASetVertexBuffers(0, 1, &cube_sample->vertex_buffer_view_);
    second_command_list_->IASetIndexBuffer(&cube_sample->index_buffer_view_);
    second_command_list_->DrawIndexedInstanced(18, 1, 18, 0, 0);

    transition_barrier.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    transition_barrier.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;

#pragma region GPA_CALL
    if (command_list_started)
    {
        // End the first direct command list for sample recording before closing it.
        cube_sample->GpaEndCommandListForSampling(gpa_command_list_);
    }
#pragma endregion

#pragma region GPA_CALL
    if (sample_started)
    {
        // End the continuing sample on the second command list.
        cube_sample->GpaEndSample(gpa_command_list_for_second_command_list_);
    }

    if (second_command_list_started)
    {
        // End the second direct command list for sample recording before closing it.
        cube_sample->GpaEndCommandListForSampling(gpa_command_list_for_second_command_list_);
    }
#pragma endregion

    // Update transition.
    resource_barrier.Transition = transition_barrier;
    d3d_command_list_->ResourceBarrier(1, &resource_barrier);
    d3d_command_list_->Close();

    second_command_list_->ResourceBarrier(1, &resource_barrier);
    second_command_list_->Close();
}

void CubeSample::BottomLeftViewport::ResetForNextPass()
{
    gpa_command_list_for_second_command_list_ = gpa_command_list_ = nullptr;
}

void CubeSample::BottomLeftViewport::IterateSamples(std::function<void(const unsigned& sample_index)> func) const
{
    if (kUndefinedSampleId != sample_id_)
    {
        func(sample_id_);
    }
}

CubeSample::BottomRightViewport::BottomRightViewport()
    : Viewport()
    , second_command_list_allocator_(nullptr)
    , bundle_command_list_allocator_(nullptr)
    , bundle_(nullptr)
    , gpa_command_list_for_bundle_(nullptr)
    , bundle_sample_id_(0xFFFF)
    , bundle_sample_id_on_primary_command_list_(kUndefinedSampleId)
    , second_command_list_(nullptr)
    , gpa_command_list_for_second_command_list_(nullptr)
{
    viewport_.TopLeftX    = 400.0f;
    viewport_.TopLeftY    = 400.0f;
    viewport_initialized_ = true;

    viewport_rect_ = {static_cast<long>(viewport_.TopLeftX),
                      static_cast<long>(viewport_.TopLeftY),
                      static_cast<long>(viewport_.TopLeftX + viewport_.Width),
                      static_cast<long>(viewport_.TopLeftY + viewport_.Height)};
}

bool CubeSample::BottomRightViewport::Init()
{
    if (viewport_initialized_)
    {
        HRESULT result = S_OK;

        // Create command allocator.
        result = cube_sample->d3d12_device_->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&d3d12_direct_command_list_allocator_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->AddIUnknown(d3d12_direct_command_list_allocator_, MAKE_STRING(BottomRightViewport->d3d12_direct_command_list_allocator_));

        result = cube_sample->d3d12_device_->CreateCommandList(0,
                                                               D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                               d3d12_direct_command_list_allocator_,
                                                               cube_sample->fill_draw_pipeline_,
                                                               __uuidof(ID3D12GraphicsCommandList),
                                                               reinterpret_cast<void**>(&d3d_command_list_));

        if (FAILED(result))
        {
            return false;
        }

        d3d_command_list_->Close();
        cube_sample->AddCommandList(d3d_command_list_);
        cube_sample->AddIUnknown(d3d_command_list_, MAKE_STRING(BottomRightViewport->d3d_command_list_));

        // Second command list.
        result = cube_sample->d3d12_device_->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&second_command_list_allocator_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->AddIUnknown(second_command_list_allocator_, MAKE_STRING(BottomRightViewport->second_command_list_allocator_));

        result = cube_sample->d3d12_device_->CreateCommandList(0,
                                                               D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                               second_command_list_allocator_,
                                                               cube_sample->fill_draw_pipeline_,
                                                               __uuidof(ID3D12GraphicsCommandList),
                                                               reinterpret_cast<void**>(&second_command_list_));

        if (FAILED(result))
        {
            return false;
        }

        second_command_list_->Close();
        cube_sample->AddCommandList(second_command_list_);
        cube_sample->AddIUnknown(second_command_list_, MAKE_STRING(BottomRightViewport->second_command_list_));

        // Create and record bundle.
        result = cube_sample->d3d12_device_->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_BUNDLE, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&bundle_command_list_allocator_));

        if (FAILED(result))
        {
            return false;
        }

        cube_sample->AddIUnknown(bundle_command_list_allocator_, MAKE_STRING(BottomRightViewport->bundle_command_list_allocator_));

        result = cube_sample->d3d12_device_->CreateCommandList(0,
                                                               D3D12_COMMAND_LIST_TYPE_BUNDLE,
                                                               bundle_command_list_allocator_,
                                                               cube_sample->fill_draw_pipeline_,
                                                               __uuidof(ID3D12GraphicsCommandList),
                                                               reinterpret_cast<void**>(&bundle_));

        if (FAILED(result))
        {
            return false;
        }

        bundle_->Close();
        cube_sample->AddIUnknown(bundle_, MAKE_STRING(BottomRightViewport->bundle_));
        cube_sample->current_back_buffer_index_ = cube_sample->dxgi_swap_chain_3_->GetCurrentBackBufferIndex();
        cube_sample->current_pipeline_state_    = cube_sample->fill_draw_pipeline_;
        return true;
    }

    return false;
}

void CubeSample::BottomRightViewport::Draw()
{
    // In this view port, we will be recording drawing of a cube with a bundle and two direct command list,
    // each drawing 1/3rd of the cube.

    HRESULT result = d3d12_direct_command_list_allocator_->Reset();
    UNREFERENCED_PARAMETER(result);
    result = second_command_list_allocator_->Reset();
    result = bundle_command_list_allocator_->Reset();

    result = d3d_command_list_->Reset(d3d12_direct_command_list_allocator_, cube_sample->current_pipeline_state_);
    result = second_command_list_->Reset(second_command_list_allocator_, cube_sample->current_pipeline_state_);
    result = bundle_->Reset(bundle_command_list_allocator_, cube_sample->current_pipeline_state_);

    if (cube_sample->pipeline_state_changed_)
    {
        d3d_command_list_->SetPipelineState(cube_sample->current_pipeline_state_);
        second_command_list_->SetPipelineState(cube_sample->current_pipeline_state_);
        bundle_->SetPipelineState(cube_sample->current_pipeline_state_);
    }

    if (cube_sample->current_pass_ == 0)
    {
        if (args.profile_bundles)
        {
            bundle_sample_id_                         = ++cube_sample->sample_counter_;  // Bundle sample.
            bundle_sample_id_on_primary_command_list_ = ++cube_sample->sample_counter_;  // Copied sample of the bundle.
            sample_id_                                = ++cube_sample->sample_counter_;  // This sample will span over two direct command list.
        }
    }

#pragma region GPA_CALL
    bool bundle_command_list_started = false;
    bool sample_started              = false;

    if (args.profile_bundles)
    {
        // Request GPA to start recording samples on the bundle.
        bundle_command_list_started = cube_sample->GpaBeginCommandListForSampling(bundle_, gpa_command_list_for_bundle_);

        if (bundle_command_list_started)
        {
            // Start sample on the bundle.
            sample_started = cube_sample->GpaBeginSample(gpa_command_list_for_bundle_, bundle_sample_id_);
        }
    }
#pragma endregion

    // Draw 1/3 of the cube.
    bundle_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    bundle_->IASetVertexBuffers(0, 1, &cube_sample->vertex_buffer_view_);
    bundle_->IASetIndexBuffer(&cube_sample->index_buffer_view_);
    bundle_->DrawIndexedInstanced(12, 1, 0, 0, 0);

#pragma region GPA_CALL
    if (sample_started)
    {
        // End the sample request on the bundle.
        cube_sample->GpaEndSample(gpa_command_list_for_bundle_);

        if (bundle_command_list_started)
        {
            // End the bundle for sample recording before closing it.
            cube_sample->GpaEndCommandListForSampling(gpa_command_list_for_bundle_);
        }
    }
#pragma endregion

    bundle_->Close();

    d3d_command_list_->SetGraphicsRootSignature(cube_sample->d3d12_root_signature_);
    d3d_command_list_->RSSetViewports(1, &viewport_);
    d3d_command_list_->RSSetScissorRects(1, &cube_sample->scissor_rect_);

    second_command_list_->SetGraphicsRootSignature(cube_sample->d3d12_root_signature_);
    second_command_list_->RSSetViewports(1, &viewport_);
    second_command_list_->RSSetScissorRects(1, &cube_sample->scissor_rect_);

    D3D12_RESOURCE_TRANSITION_BARRIER transition_barrier = {};
    transition_barrier.pResource                         = cube_sample->rtv_resource_[cube_sample->current_back_buffer_index_];
    transition_barrier.Subresource                       = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    transition_barrier.StateBefore                       = D3D12_RESOURCE_STATE_PRESENT;
    transition_barrier.StateAfter                        = D3D12_RESOURCE_STATE_RENDER_TARGET;

    D3D12_RESOURCE_BARRIER resource_barrier = {};
    resource_barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    resource_barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    resource_barrier.Transition             = transition_barrier;

    d3d_command_list_->ResourceBarrier(1, &resource_barrier);
    second_command_list_->ResourceBarrier(1, &resource_barrier);

    D3D12_CPU_DESCRIPTOR_HANDLE rtv_desc_heap;
    rtv_desc_heap.ptr = cube_sample->d3d12_descriptor_heap_->GetCPUDescriptorHandleForHeapStart().ptr +
                        cube_sample->current_back_buffer_index_ * cube_sample->rtv_view_desc_size;
    d3d_command_list_->OMSetRenderTargets(1, &rtv_desc_heap, FALSE, nullptr);
    second_command_list_->OMSetRenderTargets(1, &rtv_desc_heap, FALSE, nullptr);

    d3d_command_list_->ClearRenderTargetView(rtv_desc_heap, kClearColor, 1, &viewport_rect_);

    d3d_command_list_->ExecuteBundle(bundle_);

    d3d_command_list_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    d3d_command_list_->IASetVertexBuffers(0, 1, &cube_sample->vertex_buffer_view_);
    d3d_command_list_->IASetIndexBuffer(&cube_sample->index_buffer_view_);

#pragma region GPA_CALL
    // Request GPA to start recording samples on the first direct command list.
    bool command_list_started = cube_sample->GpaBeginCommandListForSampling(d3d_command_list_, gpa_command_list_);

    // Request GPA to start recording samples on the second direct command list.
    bool second_command_list_started = cube_sample->GpaBeginCommandListForSampling(second_command_list_, gpa_command_list_for_second_command_list_);
#pragma endregion

    second_command_list_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    second_command_list_->IASetVertexBuffers(0, 1, &cube_sample->vertex_buffer_view_);
    second_command_list_->IASetIndexBuffer(&cube_sample->index_buffer_view_);

#pragma region GPA_CALL
    if (bundle_command_list_started && command_list_started)
    {
        // Copy the bundle sample to the direct command list after its execution on first direct command list.
        std::vector<unsigned int> tmp_vector = {bundle_sample_id_on_primary_command_list_};
        cube_sample->GpaCopyBundleSample(gpa_command_list_for_bundle_, gpa_command_list_, tmp_vector);
    }

    if (command_list_started)
    {
        // Start sample on the first direct command list i.e. gpa_command_list_.
        sample_started = cube_sample->GpaBeginSample(gpa_command_list_, sample_id_);
    }

    if (sample_started && second_command_list_started)
    {
        // Continue the original sample to the second direct command list.
        cube_sample->GpaContinueSample(sample_id_, gpa_command_list_for_second_command_list_);
    }
#pragma endregion

    // Draw 1/3rd of cube.
    d3d_command_list_->DrawIndexedInstanced(12, 1, 12, 0, 0);

    // Draw 1/3rd of cube.
    second_command_list_->DrawIndexedInstanced(12, 1, 24, 0, 0);

    transition_barrier.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    transition_barrier.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;

#pragma region GPA_CALL
    if (sample_started)
    {
        // End the continuing sample on the second command list.
        cube_sample->GpaEndSample(gpa_command_list_for_second_command_list_);
    }

    if (second_command_list_started)
    {
        // End the second direct command list for sample recording before closing it.
        cube_sample->GpaEndCommandListForSampling(gpa_command_list_for_second_command_list_);
    }

    if (command_list_started)
    {
        // End the first direct command list for sample recording before closing it.
        cube_sample->GpaEndCommandListForSampling(gpa_command_list_);
    }
#pragma endregion

    // Update transition.
    resource_barrier.Transition = transition_barrier;
    d3d_command_list_->ResourceBarrier(1, &resource_barrier);
    d3d_command_list_->Close();

    second_command_list_->ResourceBarrier(1, &resource_barrier);
    second_command_list_->Close();
}

void CubeSample::BottomRightViewport::ResetForNextPass()
{
    gpa_command_list_for_second_command_list_ = gpa_command_list_for_bundle_ = gpa_command_list_ = nullptr;
}

void CubeSample::BottomRightViewport::IterateSamples(std::function<void(const unsigned& sample_index)> func) const
{
    if (kUndefinedSampleId != bundle_sample_id_on_primary_command_list_)
    {
        func(bundle_sample_id_on_primary_command_list_);
    }

    if (kUndefinedSampleId != sample_id_)
    {
        func(sample_id_);
    }
}

void CubeSample::Draw()
{
    if (profiling_enable_)
    {
        if (current_pass_ <= 0)
        {
            ++frame_counter_;
        }
    }
    else
    {
        ++frame_counter_;
    }

    ID3D12PipelineState* temp_pipeline_state = cube_sample->current_pipeline_state_;

    if (cube_sample->wire_frame_)
    {
        cube_sample->current_pipeline_state_ = wire_frame_pipeline_;
    }
    else
    {
        current_pipeline_state_ = fill_draw_pipeline_;
    }

    if (temp_pipeline_state != current_pipeline_state_)
    {
        pipeline_state_changed_ = true;
    }

    top_left_viewport_.Draw();
    top_right_viewport_.Draw();
    bottom_left_viewport_.Draw();
    bottom_right_viewport_.Draw();

    // Execute command list.
    d3d12_command_queue_->ExecuteCommandLists(static_cast<UINT>(graphics_command_queue_.size()),
                                              reinterpret_cast<ID3D12CommandList* const*>(graphics_command_queue_.data()));

    // Present frame.
    dxgi_swap_chain_3_->Present(1, 0);
    WaitForGpuToFinish();

    pipeline_state_changed_ = false;
}

void CubeSample::Destroy()
{
    while (!app_created_unknown_cache_.empty())
    {
        IUnknownNamePair d3d12_obj_name_pair = app_created_unknown_cache_.top();
        IUnknown*        unknown             = d3d12_obj_name_pair.second;

        if (nullptr != unknown)
        {
            ULONG ref_count = unknown->Release();
            UNREFERENCED_PARAMETER(ref_count);
            app_created_unknown_cache_.pop();
        }
    }
}

void CubeSample::ToggleProfiling()
{
    profiling_enable_ = !profiling_enable_;
}

void CubeSample::ToggleWireFrame()
{
    wire_frame_ = !wire_frame_;
}

void CubeSample::ResetGpaPassInfo()
{
    sample_counter_ = -1;
    top_left_viewport_.ResetForNextPass();
    top_right_viewport_.ResetForNextPass();
    bottom_left_viewport_.ResetForNextPass();
    bottom_right_viewport_.ResetForNextPass();
}

#pragma region GPA_Wrappers

bool CubeSample::GpaInitializeAndOpenContext()
{
    bool success = true;

    profiling_enable_ = args.use_gpa;

    std::remove(gpa_log_file_name_.c_str());

    if (profiling_enable_)
    {
        if (nullptr == gpa_function_table_)
        {
            if (kGpaStatusOk == GpaApiManager::Instance()->LoadApi(kGpaApiDirectx12))
            {
                gpa_function_table_ = GpaApiManager::Instance()->GetFunctionTable(kGpaApiDirectx12);
            }
            else
            {
                LogGPA(kGpaLoggingError, "Unable to load GPA");
            }
        }

        if (nullptr != gpa_function_table_)
        {
            GpaLoggingType gpa_log_types = kGpaLoggingError;
            if (args.confirm_success)
            {
                // Only log message types if confirm_success_ is enabled, because GPA will log a confirmation message
                // that the logging callback was registered, and we don't want to output a log if --verify was enabled
                // but not --confirmsuccess.
                gpa_log_types = kGpaLoggingErrorAndMessage;
            }
            success = kGpaStatusOk == gpa_function_table_->GpaRegisterLoggingCallback(kGpaLoggingError, LogGPA);
            if (!success)
            {
                LogGPA(kGpaLoggingError, "Failed to register GPA logging callback.");
                return false;
            }

            success = success && (kGpaStatusOk == gpa_function_table_->GpaInitialize(kGpaInitializeDefaultBit));
            if (!success)
            {
                LogGPA(kGpaLoggingError, "Failed to initialize GPA.");
                return false;
            }

            GpaOpenContextFlags open_context_flags = args.include_hw_counters ? kGpaOpenContextEnableHardwareCountersBit : kGpaOpenContextDefaultBit;
            success = success && kGpaStatusOk == gpa_function_table_->GpaOpenContext(d3d12_device_, open_context_flags, &gpa_context_id_);
            success = success && kGpaStatusOk == gpa_function_table_->GpaGetDeviceAndRevisionId(gpa_context_id_, &device_id_, &revision_id_);

            char        tmp_device_name[255]{};
            const char* tmp_device_name_ptr = tmp_device_name;

            success = success && kGpaStatusOk == gpa_function_table_->GpaGetDeviceName(gpa_context_id_, &tmp_device_name_ptr);

            if (success)
            {
                device_name_ = tmp_device_name_ptr;
            }

            std::remove(counter_file_name_.c_str());
            counter_data_file_stream_.open(counter_file_name_.c_str(), std::ios_base::out | std::ios_base::app);
        }
    }

    return success;
}

bool CubeSample::GpaReleaseContextAndDestroy()
{
    bool success = true;

    if (nullptr != gpa_function_table_)
    {
        if (gpa_context_id_)
        {
            success = (kGpaStatusOk == gpa_function_table_->GpaCloseContext(gpa_context_id_));
            success = (success && (kGpaStatusOk == gpa_function_table_->GpaDestroy()));
            GpaApiManager::Instance()->UnloadApi(kGpaApiDirectx12);

            if (gpa_log_file_stream_.is_open())
            {
                gpa_log_file_stream_.close();
            }

            counter_data_file_stream_.close();
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GpaEnableCounters()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        if (nullptr != gpa_session_id_)
        {
            if (args.counter_provided)
            {
                std::fstream counter_file_stream;
                counter_file_stream.open(args.counter_file_name.c_str(), std::ios_base::in);
                std::vector<std::string> counter_list;
                char                     temp_counter[256];
                if (counter_file_stream.is_open())
                {
                    while (counter_file_stream.getline(temp_counter, 256))
                    {
                        counter_list.push_back(std::string(temp_counter));
                    }

                    counter_file_stream.close();

                    for (std::vector<std::string>::const_iterator it = counter_list.cbegin(); it != counter_list.cend(); ++it)
                    {
                        gpa_function_table_->GpaEnableCounterByName(gpa_session_id_, it->c_str());
                    }
                }
                else
                {
                    std::stringstream error;
                    error << "Unable to open Counter file " << args.counter_file_name.c_str() << " . Not enabling any counters";
                }
            }
            else
            {
#ifndef AMDT_INTERNAL
                success = (kGpaStatusOk == gpa_function_table_->GpaEnableAllCounters(gpa_session_id_));
#else
                success = (kGpaStatusOk == gpa_function_table_->GpaEnableCounterByName(gpa_session_id_, "GPUTime"));
#endif
            }

            success = success && (kGpaStatusOk == gpa_function_table_->GpaGetPassCount(gpa_session_id_, &num_passes_required_));
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GpaCreateProfilingSession()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        if (nullptr != gpa_context_id_)
        {
            success = kGpaStatusOk == gpa_function_table_->GpaCreateSession(gpa_context_id_, kGpaSessionSampleTypeDiscreteCounter, &gpa_session_id_);
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GpaBeginProfilingSession()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        if (nullptr != gpa_session_id_)
        {
            success = kGpaStatusOk == gpa_function_table_->GpaBeginSession(gpa_session_id_);

            if (success)
            {
                sample_counter_ = -1;
                current_pass_   = -1;
            }
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GpaEndProfilingSession() const
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        if (nullptr != gpa_session_id_)
        {
            success = kGpaStatusOk == gpa_function_table_->GpaEndSession(gpa_session_id_);
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GpaBeginPass()
{
    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        current_pass_++;
    }

    return true;
}

bool CubeSample::GpaEndPass()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_ && nullptr != gpa_session_id_)
    {
        bool           is_ready   = false;
        const uint32_t time_out   = 10000;  // ms
        auto           start_time = std::chrono::high_resolution_clock::now();

        do
        {
            is_ready = kGpaStatusOk == gpa_function_table_->GpaIsPassComplete(gpa_session_id_, current_pass_);

            if (!is_ready)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(0));

                auto                                      end_time     = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;

                if (elapsed_time.count() > time_out)
                {
                    LogGPA(kGpaLoggingError, "GPA_IsPassComplete failed due to elapsed time_out.");
                    success = false;
                    break;
                }
            }
        } while (!is_ready);

        ResetGpaPassInfo();
    }

    return success;
}

bool CubeSample::GpaNextPassNeeded() const
{
    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        return static_cast<unsigned int>(current_pass_ + 1) < num_passes_required_;
    }

    return false;
}

bool CubeSample::GpaDeleteProfilingSession()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_ && nullptr != gpa_session_id_)
    {
        if (nullptr != gpa_context_id_)
        {
            success         = kGpaStatusOk == gpa_function_table_->GpaDeleteSession(gpa_session_id_);
            gpa_session_id_ = nullptr;
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GpaBeginCommandListForSampling(ID3D12GraphicsCommandList* graphics_command_list, GpaCommandListId& gpa_command_list_id) const
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        if (nullptr != gpa_session_id_)
        {
            GpaCommandListType cmdType = graphics_command_list->GetType() == D3D12_COMMAND_LIST_TYPE_DIRECT ? kGpaCommandListPrimary : kGpaCommandListSecondary;
            success                    = (kGpaStatusOk ==
                       gpa_function_table_->GpaBeginCommandList(gpa_session_id_, current_pass_, graphics_command_list, cmdType, &gpa_command_list_id));

            if (!success)
            {
                gpa_command_list_id = nullptr;
            }
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GpaEndCommandListForSampling(GpaCommandListId& gpa_command_list_id) const
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        if (nullptr != gpa_command_list_id)
        {
            success = (kGpaStatusOk == gpa_function_table_->GpaEndCommandList(gpa_command_list_id));
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GpaBeginSample(GpaCommandListId gpa_command_list_id, const unsigned int& sample_id) const
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        success = (kGpaStatusOk == gpa_function_table_->GpaBeginSample(sample_id, gpa_command_list_id));
    }
    else
    {
        success = false;
    }

    return success;
}

bool CubeSample::GpaEndSample(GpaCommandListId gpa_command_list_id) const
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        success = (kGpaStatusOk == gpa_function_table_->GpaEndSample(gpa_command_list_id));
    }
    else
    {
        success = false;
    }

    return success;
}

bool CubeSample::GpaCopyBundleSample(GpaCommandListId       secondary_gpa_command_list,
                                     GpaCommandListId       primary_gpa_command_list,
                                     std::vector<GpaUInt32> sample_id_list) const
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        if (nullptr != secondary_gpa_command_list && nullptr != primary_gpa_command_list)
        {
            success = (kGpaStatusOk ==
                       gpa_function_table_->GpaCopySecondarySamples(
                           secondary_gpa_command_list, primary_gpa_command_list, static_cast<GpaUInt32>(sample_id_list.size()), sample_id_list.data()));
        }
    }

    return success;
}

bool CubeSample::GpaContinueSample(unsigned int src_sample_id, GpaCommandListId gpa_command_list_id) const
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_)
    {
        if (nullptr != gpa_command_list_id)
        {
            success = (kGpaStatusOk == gpa_function_table_->GpaContinueSampleOnCommandList(src_sample_id, gpa_command_list_id));
        }
    }

    return success;
}

bool CubeSample::GpaCounterValueCompare(unsigned int profile_set,
                                        unsigned int sample_index,
                                        const char*  counter_name,
                                        GpaFloat64   counter_value,
                                        CompareType  compare_type,
                                        GpaFloat64   compare_value)
{
    bool              return_value = false;
    std::stringstream output_string;
    std::stringstream error_string;
    std::stringstream success_string;
    std::stringstream compare_string;

    output_string << "Profile " << profile_set << ", sample " << sample_index << ": ";

    error_string << "Incorrect value for counter " << counter_name << ". Value is " << counter_value << ". Expected counter to be ";
    success_string << "Counter " << counter_name << " is correct. Value " << counter_value << " is ";

    switch (compare_type)
    {
    case kCompareTypeEqual:
        return_value = counter_value == compare_value;
        compare_string << "equal to " << compare_value;
        break;

    case kCompareTypeGreaterThan:
        return_value = counter_value > compare_value;
        compare_string << "greater than " << compare_value;
        break;

    case kComapreTypeGreaterThanOrEqualTo:
        return_value = counter_value >= compare_value;
        compare_string << "greater than or equal to " << compare_value;
        break;

    case kCompareTypeLessThan:
        return_value = counter_value < compare_value;
        compare_string << "less than " << compare_value;
        break;

    case kCompareTypeLessThanOrEqualTo:
        return_value = counter_value <= compare_value;
        compare_string << "less than or equal to " << compare_value;
        break;
    }

    if (!return_value)
    {
        output_string << error_string.str() << compare_string.str();
        GpaLog(kGpaLoggingError, output_string.str().c_str());
    }
    else if (args.confirm_success)
    {
        output_string << success_string.str() << compare_string.str();
        GpaLog(kGpaLoggingMessage, output_string.str().c_str());
    }

    return return_value;
}

bool CubeSample::GpaValidateData(unsigned int frame_number,
                                 unsigned int sample_index,
                                 const char*  counter_name,
                                 GpaFloat64   counter_value,
                                 GpaUsageType counter_usage_type)
{
    bool return_value = true;

    std::string local_counter_name(counter_name);

    if (kGpaUsageTypePercentage == counter_usage_type)
    {
        return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kComapreTypeGreaterThanOrEqualTo, 0.0f) &&
                       GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeLessThanOrEqualTo, 100.0f);
    }

    if (return_value)
    {
        if (0 == local_counter_name.compare("GPUTime"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f);
        }
        else if (0 == local_counter_name.compare("GPUBusy"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f);
        }
        else if (0 == local_counter_name.compare("VSBusy"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f);
        }
        else if (0 == local_counter_name.compare("VSTime"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f);
        }
        else if (0 == local_counter_name.compare("PSBusy"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f);
        }
        else if (0 == local_counter_name.compare("PSTime"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f);
        }
        else if (0 == local_counter_name.compare("VSVerticesIn"))
        {
            // Sample 0
            GpaFloat64 expected_vs_vertices_in = 8;

            if (1 == sample_index)
            {
                expected_vs_vertices_in = 16;
            }

            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, expected_vs_vertices_in);
        }
        else if (0 == local_counter_name.compare("PSPixelsOut"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 40000);
        }
        else if (0 == local_counter_name.compare("PreZSamplesPassing"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 40000);
        }
        else if (0 == local_counter_name.compare("PrimitivesIn"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 12);
        }
    }

    return return_value;
}

bool CubeSample::GpaPopulateSessionResult()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && profiling_enable_ && nullptr != gpa_session_id_)
    {
        bool           is_ready   = false;
        const uint32_t time_out   = 10000;  // ms
        auto           start_time = std::chrono::high_resolution_clock::now();

        do
        {
            is_ready = kGpaStatusOk == gpa_function_table_->GpaIsSessionComplete(gpa_session_id_);

            if (!is_ready)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(0));

                auto                                      end_time     = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;

                if (elapsed_time.count() > time_out)
                {
                    break;
                }
            }
        } while (!is_ready);

        size_t sample_data_size = 0u;
        auto   status           = gpa_function_table_->GpaGetSampleResultSize(gpa_session_id_, 0, &sample_data_size);

        UNREFERENCED_PARAMETER(status);

        void* sample_result = malloc(sample_data_size);
        if (nullptr == sample_result)
        {
            return false;
        }

        memset(sample_result, 0, sample_data_size);

        std::stringstream counter_names_header;
        std::string       viewport;
        bool              counter_name_collected = false;
        std::string       wire_frame             = cube_sample->wire_frame_ ? "Yes" : "No";

        auto collect_sample_result = [&](unsigned int sample_index) {
            content_ << frame_counter_ << "," << wire_frame << "," << viewport << "," << sample_index;
            status                     = gpa_function_table_->GpaGetSampleResult(gpa_session_id_, sample_index, sample_data_size, sample_result);
            unsigned int counter_index = 0;

            GpaUInt32 enabled_count = 0;
            status                  = gpa_function_table_->GpaGetNumEnabledCounters(gpa_session_id_, &enabled_count);

            for (GpaUInt32 i = 0; i < enabled_count; i++)
            {
                GpaUInt32 enabled_index = 0;
                status                  = gpa_function_table_->GpaGetEnabledIndex(gpa_session_id_, i, &enabled_index);

                const char* counter_name;
                status = gpa_function_table_->GpaGetCounterName(gpa_context_id_, enabled_index, &counter_name);

                if (!counter_name_collected)
                {
                    counter_names_header << "," << counter_name;
                }

                GpaDataType counter_data_type;
                status = gpa_function_table_->GpaGetCounterDataType(gpa_context_id_, enabled_index, &counter_data_type);

                GpaUsageType counter_usage_type;
                status = gpa_function_table_->GpaGetCounterUsageType(gpa_context_id_, enabled_index, &counter_usage_type);

                if (kGpaDataTypeFloat64 == counter_data_type)
                {
                    GpaFloat64 result = *(reinterpret_cast<GpaFloat64*>(sample_result) + counter_index);

                    content_ << "," << std::fixed << (counter_usage_type == kGpaUsageTypePercentage ? std::setprecision(4) : std::setprecision(0)) << result;

                    if (args.verify_counters || args.confirm_success)
                    {
                        GpaValidateData(frame_counter_, sample_index, counter_name, result, counter_usage_type);
                    }
                }
                else if (kGpaDataTypeUint64 == counter_data_type)
                {
                    GpaUInt64 result = *(reinterpret_cast<GpaUInt64*>(sample_result) + counter_index);

                    content_ << "," << result;

                    if (args.verify_counters || args.confirm_success)
                    {
                        GpaValidateData(frame_counter_, sample_index, counter_name, static_cast<GpaFloat64>(result), counter_usage_type);
                    }
                }

                counter_index++;
            }

            content_ << std::endl;
            counter_name_collected = true;
        };

        viewport = "TopLeft";
        top_left_viewport_.IterateSamples(collect_sample_result);

        viewport = "TopRight";
        top_right_viewport_.IterateSamples(collect_sample_result);

        viewport = "BottomLeft";
        bottom_left_viewport_.IterateSamples(collect_sample_result);

        viewport = "BottomRight";
        bottom_right_viewport_.IterateSamples(collect_sample_result);

        if (counter_data_file_stream_.is_open())
        {
            if (!is_header_written_)
            {
                header_ << "Device Id: " << std::hex << device_id_ << std::endl;
                header_ << "Revision Id: " << std::hex << revision_id_ << std::endl;
                header_ << "Device Name: " << device_name_.c_str() << std::endl;
                header_ << "Frame"
                        << ","
                        << "Wireframe"
                        << ","
                        << "Viewport"
                        << ","
                        << "Sample";
                counter_data_file_stream_ << header_.str() << counter_names_header.str() << std::endl;
                is_header_written_ = true;
            }

            counter_data_file_stream_ << content_.str() << std::endl;
            content_.str(std::string());
            header_.str(std::string());
        }

        free(sample_result);
    }

    return success;
}

bool CubeSample::GpaLog(GpaLoggingType logging_type, const char* log_message)
{
    if (kGpaLoggingError == logging_type)
    {
        any_errors_logged = true;
    }

    if (!gpa_log_file_stream_.is_open())
    {
        gpa_log_file_stream_.open(gpa_log_file_name_.c_str(), std::ios_base::out | std::ios_base::app);
    }

    if (kGpaLoggingError == logging_type)
    {
        gpa_log_file_stream_ << "ERROR: " << log_message << std::endl;
    }
    else
    {
        gpa_log_file_stream_ << log_message << std::endl;
    }
    return true;
}

#pragma endregion
