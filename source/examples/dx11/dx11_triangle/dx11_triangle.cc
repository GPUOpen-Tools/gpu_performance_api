//==============================================================================
// Copyright (c) 2019-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief D3D11 Triangle Sample.
//==============================================================================

#include "examples/dx11/dx11_triangle/dx11_triangle.h"

#include <Windows.h>

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cassert>
#include <locale>
#include <codecvt>

#include <d3dcompiler.h>

#include "examples/dx11/sample.h"

extern const unsigned int kWindowWidth     = 800;
extern const unsigned int kWindowHeight    = 800;
extern const std::wstring kWindowClassName = L"D3D11 Triangle Sample";

HWND              window_handle                   = nullptr;
D3D11Triangle*    D3D11Triangle::dx11_triangle_   = nullptr;
GpaApiManager*    GpaApiManager::gpa_api_manager_ = nullptr;
GpaFuncTableInfo* gpa_function_table_info         = nullptr;

bool any_errors_logged = false;  ///< Flag indicating if any GPA errors have been logged.
int  num_errors_logged = 0;      ///< Indicates the number of GPA errors that have been logged.

/// @brief Converts string from wide to utf-8 encoding.
///
/// @return The converted utf-8 encoded string.
static std::wstring utf8_to_wide_converter(const std::string utf8)
{
    int          num_characters_needed = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), (int)utf8.size(), nullptr, 0);
    std::wstring wide;
    wide.resize(num_characters_needed);
    MultiByteToWideChar(CP_UTF8, 0, utf8.data(), (int)utf8.size(), wide.data(), num_characters_needed);
    return wide;
}

void LogGPA(GpaLoggingType logging_type, const char* log_message)
{
    D3D11Triangle::Instance()->GpaLog(logging_type, log_message);
}

#define MAKE_STRING(X) #X

LRESULT CALLBACK SampleWindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    static unsigned int profile_count = 0;

    gpa_example::Dx11SampleApp& app = *(reinterpret_cast<gpa_example::Dx11SampleApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)));

    switch (uMsg)
    {
    case WM_SHOWWINDOW:
    {
        // Initialize app here.
        if (!D3D11Triangle::Instance()->Init(&app))
        {
            exit(-1);
        }

        if (!app.NoGpa())
        {
            bool gpa_ok = D3D11Triangle::Instance()->GpaInitializeAndOpenContext();

            if (!gpa_ok)
            {
                PostQuitMessage(-1);
            }
        }

        return 0;
    }

    case WM_PAINT:
    {
        static bool start_new_session = true;
        static bool session_created   = false;
        static bool session_started   = false;

        if (start_new_session)
        {
            session_created = D3D11Triangle::Instance()->GpaCreateProfilingSession();

            if (session_created)
            {
                if (D3D11Triangle::Instance()->GpaEnableCounters())
                {
                    session_started   = D3D11Triangle::Instance()->GpaBeginProfilingSession();
                    start_new_session = false;
                }
                else
                {
                    D3D11Triangle::Instance()->GpaDeleteProfilingSession();
                }
            }
        }

        bool pass_started   = false;
        bool sample_started = false;

        if (session_started)
        {
            pass_started = D3D11Triangle::Instance()->GpaBeginPass();
        }

        if (pass_started)
        {
            sample_started = D3D11Triangle::Instance()->GpaBeginSample();
        }

        // Draw the triangle.
        D3D11Triangle::Instance()->Draw();

        if (sample_started)
        {
            D3D11Triangle::Instance()->GpaEndSample();
        }

        // Present the backbuffer.
        D3D11Triangle::Instance()->Present();

        if (pass_started)
        {
            D3D11Triangle::Instance()->GpaEndPass();
        }

        if (session_started)
        {
            if (D3D11Triangle::Instance()->GpaNextPassNeeded() == false)
            {
                if (D3D11Triangle::Instance()->GpaEndProfilingSession())
                {
                    session_started = false;
                    D3D11Triangle::Instance()->GpaPopulateSessionResult();

                    ++profile_count;

                    if (session_created)
                    {
                        D3D11Triangle::Instance()->GpaDeleteProfilingSession();
                        session_created = false;

                        if (app.NumberOfFrames() > 0 && profile_count < app.NumberOfFrames())
                        {
                            // Start a new session on the next WM_PAINT.
                            start_new_session = true;
                        }
                    }
                }
            }
        }
        else
        {
            ++profile_count;
        }

        if (app.NumberOfFrames() > 0 && profile_count >= app.NumberOfFrames())
        {
            // If the user specified a number of frames, and we've rendered that many frames, then exit.
            PostQuitMessage(0);
        }

        return 0;
    }

    case WM_DESTROY:

        // Destroy app here.
        if (!app.NoGpa())
        {
            D3D11Triangle::Instance()->GpaReleaseContextAndDestroy();
        }

        D3D11Triangle::Instance()->Destroy();

        PostQuitMessage(0);
        return 0;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case 0x50:  // Keyboard P for profiling.
            D3D11Triangle::Instance()->ToggleProfiling();
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

D3D11Triangle* D3D11Triangle::Instance()
{
    if (nullptr == dx11_triangle_)
    {
        dx11_triangle_ = new (std::nothrow) D3D11Triangle();
    }

    return dx11_triangle_;
}

D3D11Triangle::D3D11Triangle()
    : dx11_device_(nullptr)
    , dx11_immediate_context_(nullptr)
    , dxgi_factory_1_(nullptr)
    , dxgi_swap_chain_(nullptr)
    , vertex_bufffer_(nullptr)
    , vertex_shader_(nullptr)
    , pixel_shader_(nullptr)
    , render_target_view_(nullptr)
    , input_layout_(nullptr)
    , depth_setncil_state_(nullptr)
    , rasterizer_state_(nullptr)
    , view_port_()
    , frame_counter_(0u)
    , is_header_written_(false)
    , gpa_function_table_(nullptr)
    , gpa_context_id_(nullptr)
    , gpa_session_id_(nullptr)
    , gpa_command_list_id_(nullptr)
    , device_id_(0)
    , revision_id_(0)
    , num_passes_required_(0u)
    , current_pass_(-1)
    , sample_counter_(-1)
    , is_profiling_enabled_(true)
{
}

bool D3D11Triangle::Init(gpa_example::Dx11SampleApp* app)
{
    app_ = app;
    std::vector<char> module_path(_MAX_PATH);

    ::GetModuleFileNameA(0, module_path.data(), static_cast<DWORD>(module_path.size()));

    std::string pathOnly(module_path.data());

    executable_path_ = pathOnly.substr(0, pathOnly.find_last_of('\\') + 1);

    counter_file_name_ = app_->Datafile();
    gpa_log_file_name_ = app_->Logfile();

    // DX11 Initialization.

    HRESULT result = S_OK;

    result = CreateDXGIFactory1(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgi_factory_1_));

    if (FAILED(result))
    {
        return false;
    }

    unsigned int                adapter_iter = 0;
    std::vector<IDXGIAdapter1*> dxgi_adapters;
    IDXGIAdapter1*              dxgi_adapter_1 = nullptr;

    // Description flag is only available in type IDXGIAdapter1 and later.
    while (SUCCEEDED(dxgi_factory_1_->EnumAdapters1(adapter_iter, &dxgi_adapter_1)))
    {
        DXGI_ADAPTER_DESC1 adapter_description_1;
        dxgi_adapter_1->GetDesc1(&adapter_description_1);

        if (!(adapter_description_1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE))
        {
            dxgi_adapters.push_back(dxgi_adapter_1);
        }

        adapter_iter++;
        dxgi_adapter_1 = nullptr;
    }

    if (!dxgi_adapters.empty())
    {
        // Pick first supported hardware adapter to create the device.
        bool         found_supported_gpu = false;
        const size_t num_adapters        = dxgi_adapters.size();
        for (size_t i = 0; i < num_adapters; ++i)
        {
            DXGI_ADAPTER_DESC1 adapter_desc_i;
            dxgi_adapters.at(i)->GetDesc1(&adapter_desc_i);
            int candidate_device_id = adapter_desc_i.DeviceId;
            if (!(candidate_device_id == 0x1506 || candidate_device_id == 0x164e))
            {
                found_supported_gpu = true;
                dxgi_adapter_1      = dxgi_adapters.at(i);
                break;
            }
        }
        if (!found_supported_gpu)
        {
            return false;
        };

        D3D_FEATURE_LEVEL feature_levels[] = {D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_11_1};
        D3D_FEATURE_LEVEL feature_level_supported;

        result = D3D11CreateDevice(dxgi_adapter_1,
                                   D3D_DRIVER_TYPE_UNKNOWN,
                                   nullptr,
                                   D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS,
                                   feature_levels,
                                   _countof(feature_levels),
                                   D3D11_SDK_VERSION,
                                   &dx11_device_,
                                   &feature_level_supported,
                                   &dx11_immediate_context_);

        if (FAILED(result))
        {
            return false;
        }

        DXGI_MODE_DESC dxgi_mode_desc          = {};
        dxgi_mode_desc.Width                   = static_cast<UINT>(kWindowWidth);
        dxgi_mode_desc.Height                  = static_cast<UINT>(kWindowHeight);
        dxgi_mode_desc.RefreshRate.Numerator   = 60;  // 60 Hz.
        dxgi_mode_desc.RefreshRate.Denominator = 1;
        dxgi_mode_desc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
        dxgi_mode_desc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        dxgi_mode_desc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;

        DXGI_SWAP_CHAIN_DESC dxgi_swapchain_desc = {};
        dxgi_swapchain_desc.BufferDesc           = dxgi_mode_desc;
        dxgi_swapchain_desc.SampleDesc.Count     = 1;
        dxgi_swapchain_desc.SampleDesc.Quality   = 0;  // Irrelevant.
        dxgi_swapchain_desc.BufferUsage          = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        dxgi_swapchain_desc.BufferCount          = kFrameCount;
        dxgi_swapchain_desc.OutputWindow         = window_handle;
        dxgi_swapchain_desc.Windowed             = TRUE;
        dxgi_swapchain_desc.SwapEffect           = DXGI_SWAP_EFFECT_DISCARD;
        dxgi_swapchain_desc.Flags                = NULL;

        result = dxgi_factory_1_->CreateSwapChain(dx11_device_, &dxgi_swapchain_desc, &dxgi_swap_chain_);

        if (FAILED(result))
        {
            return false;
        }

        // Create RTV with swap chain back buffer.
        ID3D11Texture2D* render_target_view_texture = nullptr;
        result = dxgi_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&render_target_view_texture));

        if (FAILED(result))
        {
            return false;
        }

        result = dx11_device_->CreateRenderTargetView(render_target_view_texture, nullptr, &render_target_view_);

        if (FAILED(result))
        {
            return false;
        }

        // Init vertex data and create vertex buffer.
        VertexData vertex_color_data[] = {
            {{0.0f, 0.75f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},     // 0.
            {{-0.75f, -0.75f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},  // 1.
            {{0.75f, -0.75f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},   // 2.
        };

        D3D11_BUFFER_DESC vertex_buffer_desc;
        vertex_buffer_desc.Usage          = D3D11_USAGE_DEFAULT;
        vertex_buffer_desc.ByteWidth      = sizeof(VertexData) * 3;
        vertex_buffer_desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
        vertex_buffer_desc.CPUAccessFlags = 0;
        vertex_buffer_desc.MiscFlags      = 0;

        D3D11_SUBRESOURCE_DATA vertex_init_data;
        vertex_init_data.pSysMem = vertex_color_data;

        result = dx11_device_->CreateBuffer(&vertex_buffer_desc, &vertex_init_data, &vertex_bufffer_);

        if (FAILED(result))
        {
            return false;
        }

        ID3DBlob* vertex_shader_blob = nullptr;
        ID3DBlob* pixel_shader_blob  = nullptr;
        ID3DBlob* error              = nullptr;

        UINT compile_flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

        std::wstring shader_path = utf8_to_wide_converter(executable_path_);
        shader_path.append(L"dx11_triangle_shaders.hlsl");

        std::ifstream shader_file(shader_path.c_str());
        if (!shader_file.good())
        {
            LogGPA(kGpaLoggingError, "Unable to load shader file.");
            return false;
        }

        result = D3DCompileFromFile(shader_path.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compile_flags, 0, &vertex_shader_blob, &error);

        if (FAILED(result))
        {
            return false;
        }

        result = dx11_device_->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), nullptr, &vertex_shader_);

        if (FAILED(result))
        {
            return false;
        }

        result = D3DCompileFromFile(shader_path.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compile_flags, 0, &pixel_shader_blob, &error);

        if (FAILED(result))
        {
            return false;
        }

        result = dx11_device_->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), nullptr, &pixel_shader_);

        if (FAILED(result))
        {
            return false;
        }

        // Create input layout.
        D3D11_INPUT_ELEMENT_DESC input_layout[2];

        // Vertex position data.
        input_layout[0].SemanticName         = "SCREEN_POSITION";
        input_layout[0].SemanticIndex        = 0;
        input_layout[0].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
        input_layout[0].InputSlot            = 0;
        input_layout[0].AlignedByteOffset    = 0;
        input_layout[0].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
        input_layout[0].InstanceDataStepRate = 0;

        // Vertex color data.
        input_layout[1].SemanticName         = "VERTEX_COLOR";
        input_layout[1].SemanticIndex        = 0;
        input_layout[1].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
        input_layout[1].InputSlot            = 0;
        input_layout[1].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
        input_layout[1].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
        input_layout[1].InstanceDataStepRate = 0;

        result = dx11_device_->CreateInputLayout(input_layout, 2, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), &input_layout_);

        if (FAILED(result))
        {
            return false;
        }

        // D3D11 runtime needs all data for D3D11_DEPTH_STENCIL_DESC to be filled.
        D3D11_DEPTH_STENCIL_DESC depth_stenicl_desc;
        depth_stenicl_desc.DepthEnable      = false;
        depth_stenicl_desc.DepthWriteMask   = D3D11_DEPTH_WRITE_MASK_ZERO;
        depth_stenicl_desc.DepthFunc        = D3D11_COMPARISON_NEVER;
        depth_stenicl_desc.StencilEnable    = false;
        depth_stenicl_desc.StencilReadMask  = 0;
        depth_stenicl_desc.StencilWriteMask = 0;
        depth_stenicl_desc.FrontFace        = {};
        depth_stenicl_desc.BackFace         = {};

        result = dx11_device_->CreateDepthStencilState(&depth_stenicl_desc, &depth_setncil_state_);

        if (FAILED(result))
        {
            return false;
        }

        D3D11_RASTERIZER_DESC rasterizer_desc = {};
        rasterizer_desc.FillMode              = D3D11_FILL_SOLID;
        rasterizer_desc.CullMode              = D3D11_CULL_NONE;

        result = dx11_device_->CreateRasterizerState(&rasterizer_desc, &rasterizer_state_);

        if (FAILED(result))
        {
            return false;
        }

        view_port_.Width    = static_cast<float>(kWindowWidth);
        view_port_.Height   = static_cast<float>(kWindowHeight);
        view_port_.MaxDepth = 1.0f;
        view_port_.MinDepth = 0.0f;
        view_port_.TopLeftX = 0.0f;
        view_port_.TopLeftY = 0.0f;
    }

    return true;
}

void D3D11Triangle::Draw()
{
    UINT stride        = sizeof(VertexData);
    UINT buffer_offset = 0;

    dx11_immediate_context_->IASetVertexBuffers(0, 1, &vertex_bufffer_, &stride, &buffer_offset);
    dx11_immediate_context_->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    dx11_immediate_context_->IASetInputLayout(input_layout_);
    dx11_immediate_context_->VSSetShader(vertex_shader_, nullptr, 0);
    dx11_immediate_context_->RSSetState(rasterizer_state_);
    dx11_immediate_context_->RSSetViewports(1, &view_port_);
    dx11_immediate_context_->PSSetShader(pixel_shader_, nullptr, 0);
    dx11_immediate_context_->OMSetDepthStencilState(depth_setncil_state_, NULL);
    dx11_immediate_context_->OMSetRenderTargets(1, &render_target_view_, nullptr);
    dx11_immediate_context_->Draw(3, 0);
}

void D3D11Triangle::Present()
{
    dxgi_swap_chain_->Present(1, 0);

    if (is_profiling_enabled_)
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
}

void D3D11Triangle::ToggleProfiling()
{
    is_profiling_enabled_ = !is_profiling_enabled_;
}

#define SAFE_RELEASE(X) \
    if (nullptr != (X)) \
    {                   \
        (X)->Release(); \
    }

void D3D11Triangle::Destroy() const
{
    SAFE_RELEASE(rasterizer_state_);
    SAFE_RELEASE(depth_setncil_state_);
    SAFE_RELEASE(input_layout_);
    SAFE_RELEASE(render_target_view_);
    SAFE_RELEASE(pixel_shader_);
    SAFE_RELEASE(vertex_shader_);
    SAFE_RELEASE(vertex_bufffer_);
    SAFE_RELEASE(dxgi_swap_chain_);
    SAFE_RELEASE(dxgi_factory_1_);
    SAFE_RELEASE(dx11_immediate_context_);
    SAFE_RELEASE(dx11_device_);
}

void D3D11Triangle::ResetGpaPassInfo()
{
    sample_counter_ = -1;
}

#pragma region GPA_Wrappers

bool D3D11Triangle::GpaInitializeAndOpenContext()
{
    bool success = true;

    is_profiling_enabled_ = !(app_->NoGpa());

    std::remove(gpa_log_file_name_.c_str());

    if (is_profiling_enabled_)
    {
        if (nullptr == gpa_function_table_)
        {
            if (kGpaStatusOk == GpaApiManager::Instance()->LoadApi(kGpaApiDirectx11))
            {
                gpa_function_table_ = GpaApiManager::Instance()->GetFunctionTable(kGpaApiDirectx11);
            }
            else
            {
                LogGPA(kGpaLoggingError, "Unable to load GPA");
            }
        }

        if (nullptr != gpa_function_table_)
        {
            GpaLoggingType gpa_log_types = kGpaLoggingError;
            if (app_->ConfirmSuccess())
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

            success = success && kGpaStatusOk == gpa_function_table_->GpaInitialize(kGpaInitializeDefaultBit);
            if (!success)
            {
                LogGPA(kGpaLoggingError, "Failed to initialize GPA.");
                return false;
            }

            GpaOpenContextFlags open_context_flags = app_->IncludeHwCounters() ? kGpaOpenContextEnableHardwareCountersBit : kGpaOpenContextDefaultBit;
            success = success && kGpaStatusOk == gpa_function_table_->GpaOpenContext(dx11_device_, open_context_flags, &gpa_context_id_);
            success = success && kGpaStatusOk == gpa_function_table_->GpaGetDeviceAndRevisionId(gpa_context_id_, &device_id_, &revision_id_);

            char        tmp_device_name[255]{};
            const char* temp_device_name_ptr = tmp_device_name;

            success = success && kGpaStatusOk == gpa_function_table_->GpaGetDeviceName(gpa_context_id_, &temp_device_name_ptr);
            if (success)
            {
                device_name_ = temp_device_name_ptr;
            }

            std::remove(counter_file_name_.c_str());
            counter_data_file_stream_.open(counter_file_name_.c_str(), std::ios_base::out | std::ios_base::app);
        }
    }

    return success;
}

bool D3D11Triangle::GpaReleaseContextAndDestroy()
{
    bool success = true;

    if (nullptr != gpa_function_table_)
    {
        if (gpa_context_id_)
        {
            success = kGpaStatusOk == gpa_function_table_->GpaCloseContext(gpa_context_id_);
            success = success && kGpaStatusOk == gpa_function_table_->GpaDestroy();
            GpaApiManager::Instance()->UnloadApi(kGpaApiDirectx11);
            GpaApiManager::DeleteInstance();

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

bool D3D11Triangle::GpaEnableCounters()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && is_profiling_enabled_)
    {
        if (nullptr != gpa_session_id_)
        {
            if (!app_->Counterfile().empty())
            {
                std::fstream counter_file_stream;
                counter_file_stream.open(app_->Counterfile().c_str(), std::ios_base::in);
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
                    error << "Unable to open Counter file " << app_->Counterfile().c_str() << " . Not enabling any counters";
                }
            }
            else
            {
                success = kGpaStatusOk == gpa_function_table_->GpaEnableAllCounters(gpa_session_id_);
            }
            success = success && kGpaStatusOk == gpa_function_table_->GpaGetPassCount(gpa_session_id_, &num_passes_required_);
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool D3D11Triangle::GpaCreateProfilingSession()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && is_profiling_enabled_)
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

bool D3D11Triangle::GpaBeginProfilingSession()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && is_profiling_enabled_)
    {
        if (nullptr != gpa_session_id_)
        {
            success = kGpaStatusOk == gpa_function_table_->GpaBeginSession(gpa_session_id_);

            if (success)
            {
                sample_counter_ = -1;
                current_pass_   = -1;
                sample_list_.clear();
            }
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool D3D11Triangle::GpaEndProfilingSession() const
{
    bool success = true;

    if (nullptr != gpa_function_table_ && is_profiling_enabled_)
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

bool D3D11Triangle::GpaBeginPass()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && is_profiling_enabled_)
    {
        current_pass_++;
    }

    if (nullptr == gpa_command_list_id_ && nullptr != gpa_function_table_)
    {
        GpaStatus status =
            gpa_function_table_->GpaBeginCommandList(gpa_session_id_, current_pass_, GPA_NULL_COMMAND_LIST, kGpaCommandListNone, &gpa_command_list_id_);

        success = kGpaStatusOk == status;
    }

    return success;
}

bool D3D11Triangle::GpaEndPass()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && is_profiling_enabled_ && nullptr != gpa_session_id_ && nullptr != gpa_command_list_id_)
    {
        success = kGpaStatusOk == gpa_function_table_->GpaEndCommandList(gpa_command_list_id_);

        bool           is_ready   = false;
        const uint32_t time_out   = 10000;  // ms.
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
        gpa_command_list_id_ = nullptr;
    }

    return success;
}

bool D3D11Triangle::GpaNextPassNeeded() const
{
    if (nullptr != gpa_function_table_ && is_profiling_enabled_)
    {
        return static_cast<unsigned int>(current_pass_ + 1) < num_passes_required_;
    }

    return false;
}

bool D3D11Triangle::GpaDeleteProfilingSession()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && is_profiling_enabled_ && nullptr != gpa_session_id_)
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

bool D3D11Triangle::GpaBeginSample()
{
    bool success = true;

    if (is_profiling_enabled_)
    {
        if (nullptr != gpa_function_table_ && nullptr != gpa_command_list_id_)
        {
            sample_counter_++;
            success = kGpaStatusOk == gpa_function_table_->GpaBeginSample(sample_counter_, gpa_command_list_id_);

            if (success && current_pass_ == 0)
            {
                sample_list_.push_back(sample_counter_);
            }
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool D3D11Triangle::GpaEndSample()
{
    bool success = true;

    if (is_profiling_enabled_)
    {
        if (nullptr != gpa_function_table_ && nullptr != gpa_command_list_id_)
        {
            success = kGpaStatusOk == gpa_function_table_->GpaEndSample(gpa_command_list_id_);
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool D3D11Triangle::GpaCounterValueCompare(unsigned int frame_number,
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

    output_string << "Profile " << frame_number << ", sample " << sample_index << ": ";

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

    case kCompareTypeGreaterThanOrEqualTo:
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
    else if (app_->ConfirmSuccess())
    {
        output_string << success_string.str() << compare_string.str();
        GpaLog(kGpaLoggingMessage, output_string.str().c_str());
    }

    return return_value;
}

bool D3D11Triangle::GpaValidateData(unsigned int frame_number,
                                    unsigned int sample_index,
                                    const char*  counter_name,
                                    GpaFloat64   counter_value,
                                    GpaUsageType counter_usage_type)
{
    bool return_value = true;

    std::string local_counter_name(counter_name);

    if (kGpaUsageTypePercentage == counter_usage_type)
    {
        return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeGreaterThanOrEqualTo, 0.0f) &&
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
        else if (0 == local_counter_name.compare("TessellatorBusy") || 0 == local_counter_name.compare("TessellatorBusyCycles"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 0.0f);
        }
        else if (0 == local_counter_name.compare("VsGsVerticesIn"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 3.0f);
        }
        else if (0 == local_counter_name.compare("VsGsPrimsIn"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 1.0f);
        }
        else if (0 == local_counter_name.compare("GSVerticesOut"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 0.0f);
        }
        else if (0 == local_counter_name.compare("PreTessVerticesIn"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 0.0f);
        }
        else if (0 == local_counter_name.compare("GSPrimsIn"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 0.0f);
        }
        else if (0 == local_counter_name.compare("TexTriFilteringPct") || 0 == local_counter_name.compare("TexTriFilteringCount") ||
                 0 == local_counter_name.compare("NoTexTriFilteringCount") || 0 == local_counter_name.compare("TexVolFilteringPct") ||
                 0 == local_counter_name.compare("TexVolFilteringCount") || 0 == local_counter_name.compare("NoTexVolFilteringCount"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 0.0f);
        }
        else if (app_->IncludeKnownIssues() && (0 == local_counter_name.compare("PSSALUInstCount") || 0 == local_counter_name.compare("PSVALUInstCount")))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0);
        }
        else if (app_->IncludeKnownIssues() && (0 == local_counter_name.compare("VsGsSALUInstCount") || 0 == local_counter_name.compare("VsGsVALUInstCount")))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0);
        }
        else if (0 == local_counter_name.compare("CSSALUInstCount") || 0 == local_counter_name.compare("CSVALUInstCount") ||
                 0 == local_counter_name.compare("PreTessSALUInstCount") || 0 == local_counter_name.compare("PreTessVALUInstCount") ||
                 0 == local_counter_name.compare("PostTessSALUInstCount") || 0 == local_counter_name.compare("PostTessVALUInstCount"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 0);
        }
        else if (0 == local_counter_name.compare("PSPixelsOut"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 180000);
        }
        else if (app_->IncludeKnownIssues() && 0 == local_counter_name.compare("PreZSamplesPassing"))
        {
            // Checking for Gfx1103 hardware.
            if (device_id_ == 0x15BF || device_id_ == 0x15C8)
            {
                return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 0);
            }
            else
            {
                return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 18000);
            }
        }
        else if (0 == local_counter_name.compare("PrimitivesIn"))
        {
            return_value = GpaCounterValueCompare(frame_number, sample_index, counter_name, counter_value, kCompareTypeEqual, 1);
        }
    }

    return return_value;
}

bool D3D11Triangle::GpaPopulateSessionResult()
{
    bool success = true;

    if (is_profiling_enabled_)
    {
        if (nullptr != gpa_function_table_ && nullptr != gpa_session_id_)
        {
            bool           is_ready   = false;
            const uint32_t time_out   = 10000;  // ms.
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
            bool              counter_name_collected = false;

            GpaUInt32 sample_count;
            success = kGpaStatusOk == gpa_function_table_->GpaGetSampleCount(gpa_session_id_, &sample_count);

            auto collect_sample_result = [&](unsigned int sample_index) {
                content_stream_ << frame_counter_ << "," << sample_index;
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

                        content_stream_ << "," << std::fixed << (counter_usage_type == kGpaUsageTypePercentage ? std::setprecision(4) : std::setprecision(0))
                                        << result;

                        if (app_->Verify())
                        {
                            GpaValidateData(frame_counter_, sample_index, counter_name, result, counter_usage_type);
                        }
                    }
                    else if (kGpaDataTypeUint64 == counter_data_type)
                    {
                        GpaUInt64 result = *(reinterpret_cast<GpaUInt64*>(sample_result) + counter_index);

                        content_stream_ << "," << result;

                        if (app_->Verify())
                        {
                            GpaValidateData(frame_counter_, sample_index, counter_name, static_cast<GpaFloat64>(result), counter_usage_type);
                        }
                    }

                    counter_index++;
                }

                counter_name_collected = true;
            };

            if (success && sample_count == sample_list_.size())
            {
                for (auto iter = sample_list_.cbegin(); iter != sample_list_.cend(); ++iter)
                {
                    collect_sample_result(*iter);
                }
            }

            if (counter_data_file_stream_.is_open())
            {
                if (!is_header_written_)
                {
                    header_stream_ << "Device Id: " << std::hex << device_id_ << std::endl;
                    header_stream_ << "Revision Id: " << std::hex << revision_id_ << std::endl;
                    header_stream_ << "Device Name: " << device_name_.c_str() << std::endl;
                    header_stream_ << "Frame"
                                   << ","
                                   << "Sample";
                    counter_data_file_stream_ << header_stream_.str() << counter_names_header.str() << std::endl;
                    is_header_written_ = true;
                }

                counter_data_file_stream_ << content_stream_.str() << std::endl;
                content_stream_.str(std::string());
                header_stream_.str(std::string());
            }

            free(sample_result);
        }
    }

    return success;
}

bool D3D11Triangle::GpaLog(GpaLoggingType logging_type, const char* log_message)
{
    if (kGpaLoggingError == logging_type)
    {
        any_errors_logged = true;
        num_errors_logged += 1;
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
