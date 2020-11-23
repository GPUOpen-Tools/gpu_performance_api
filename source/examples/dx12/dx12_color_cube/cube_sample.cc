//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Cube Sample
//==============================================================================

#include <Windows.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <D3DCompiler.h>
#include <cassert>

#include "..\sample.h"
#include "cube_sample.h"

unsigned int      g_windowWidth                   = 800;
unsigned int      g_windowHeight                  = 800;
std::wstring      g_windowClassName               = L"D3D12 Cube Sample";
HWND              g_windowHandle                  = nullptr;
CubeSample*       CubeSample::ms_pCubeSample      = nullptr;
GPAApiManager*    GPAApiManager::m_pGpaApiManager = nullptr;
GPAFuncTableInfo* g_pFuncTableInfo                = nullptr;

bool g_anyGPAErrorsLogged = false;  ///< flag indicating if any GPA errors have been logged

void LogGPA(GPA_Logging_Type loggingType, const char* logMessage)
{
    CubeSample::Instance()->GPA_Log(loggingType, logMessage);
}

#define MAKE_STRING(X) #X

LRESULT CALLBACK SampleWindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    static unsigned int paintCount = 0;

    switch (uMsg)
    {
    case WM_SHOWWINDOW:
    {
        // Initialize app here
        CubeSample::Instance()->Init();

        if (args.m_useGPA)
        {
            bool gpaOk = CubeSample::Instance()->GPA_InitializeAndOpenContext();

            if (!gpaOk)
            {
                PostQuitMessage(-1);
            }
        }

        return 0;
    }

    case WM_PAINT:
    {
        bool sessionCreated = CubeSample::Instance()->GPA_CreateProfilingSession();
        bool sessionStarted = false;

        if (sessionCreated)
        {
            if (CubeSample::Instance()->GPA_EnableCounters())
            {
                sessionStarted = CubeSample::Instance()->GPA_BeginProfilingSession();
            }
            else
            {
                CubeSample::Instance()->GPA_DeleteProfilingSession();
            }
        }
        do
        {
            bool passStarted = false;

            if (sessionStarted)
            {
                passStarted = CubeSample::Instance()->GPA_BeginPass();
            }

            CubeSample::Instance()->Draw();  // draw the cube

            if (passStarted)
            {
                CubeSample::Instance()->GPA_EndPass();
            }
        } while (CubeSample::Instance()->GPA_NextPassNeeded());

        bool sessionEnded = false;

        if (sessionStarted)
        {
            sessionEnded = CubeSample::Instance()->GPA_EndProfilingSession();
        }

        if (sessionEnded)
        {
            CubeSample::Instance()->GPA_PopulateSessionResult();

            if (sessionCreated)
            {
                CubeSample::Instance()->GPA_DeleteProfilingSession();
            }
        }

        paintCount++;

        if (args.m_numberOfFrames > 0 && paintCount >= args.m_numberOfFrames)
        {
            // if the user specified a number of frames, and we've rendered that many frames, then exit
            PostQuitMessage(0);
        }

        return 0;
    }

    case WM_DESTROY:
        // Destroy app here
        if (args.m_useGPA)
        {
            CubeSample::Instance()->GPA_ReleaseContextAndDestroy();
        }

        CubeSample::Instance()->Destroy();
        PostQuitMessage(0);
        return 0;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case 0x50:  // keyboard P for profiling
            CubeSample::Instance()->ToggleProfiling();
            break;

        case 0x57:  // keyboard W for wireframe
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
    if (nullptr == ms_pCubeSample)
    {
        ms_pCubeSample = new (std::nothrow) CubeSample();
    }

    return ms_pCubeSample;
}

CubeSample::CubeSample()
    : m_pd3d12Device(nullptr)
    , m_pD3D12RootSignature(nullptr)
    , m_deviceId(0)
    , m_revisionId(0)
#ifdef _DEBUG
    , m_pd3d12DebugInterface(nullptr)
    , m_pdxgiDebug(nullptr)
#endif
    , m_pdxgiFactory2(nullptr)
    , m_pfillDrawPipeline(nullptr)
    , m_pWireframePipeline(nullptr)
    , m_pVertexBuffer(nullptr)
    , m_vertexBufferView()
    , m_pIndexBuffer(nullptr)
    , m_indexBufferView()
    , m_scissorRect()
    , m_pRTVResource{nullptr, nullptr}
    , m_fenceEvent(nullptr)
    , m_pd3d12Fence(nullptr)
    , m_fenceValue(0u)
    , m_pdxgiSwapChain3(nullptr)
    , m_currentBackBufferIndex(0u)
    , m_pCurrentPipelineState(nullptr)
    , m_pd3d12DescriptorHeap(nullptr)
    , m_RTVdescriptorIncrementSize(0u)
    , m_pd3d12CommandQueue(nullptr)
    , m_pipelineStateChanged(false)
    , m_wireframe(false)
    , m_profilingEnable(true)
    , m_frameCounter(0u)
    , m_isHeaderWritten(false)
    , m_pGpaFunctionTable(nullptr)
    , m_gpaContextId(nullptr)
    , m_gpaSessionId(nullptr)
    , m_passRequired(0u)
    , m_currentPass(-1)
    , m_sampleCounter(-1)
{
}

void CubeSample::Init()
{
    std::vector<char> modulepath(_MAX_PATH);

    ::GetModuleFileNameA(0, modulepath.data(), static_cast<DWORD>(modulepath.size()));

    std::string pathOnly(modulepath.data());

    m_executablePath = pathOnly.substr(0, pathOnly.find_last_of('\\') + 1);

    if (InitializeCommonResource())
    {
        UploadCubeData();

        if (InitializeViewPortResource())
        {
            m_scissorRect.left   = 0l;
            m_scissorRect.top    = 0l;
            m_scissorRect.right  = 800l;
            m_scissorRect.bottom = 800l;

            m_counterFileName = std::string(m_executablePath.begin(), m_executablePath.end()).append("D3D12ColorCube_counterData.csv");
            m_gpaLogFileName  = std::string(m_executablePath.begin(), m_executablePath.end()).append("D3D12ColorCube_gpaLog.txt");

            // wireframe
            m_wireframe = false;
        }
    }
}

bool CubeSample::InitializeCommonResource()
{
    HRESULT result           = S_OK;
    UINT    dxgiFactoryFlags = 0;

    // Enable Debug layer
#ifdef _DEBUG
    result = D3D12GetDebugInterface(__uuidof(ID3D12Debug), reinterpret_cast<void**>(&m_pd3d12DebugInterface));

    if (FAILED(result))
    {
        return false;
    }

    m_pd3d12DebugInterface->EnableDebugLayer();
    dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
    AddIUnknown(m_pd3d12DebugInterface, MAKE_STRING(m_pd3d12DebugInterface));

    HMODULE dxgiHandle = GetModuleHandle(L"Dxgidebug.dll");

    if (nullptr != dxgiHandle)
    {
        decltype(DXGIGetDebugInterface)* dxgiDebugFunc =
            reinterpret_cast<decltype(DXGIGetDebugInterface)*>(GetProcAddress(dxgiHandle, "DXGIGetDebugInterface"));

        if (nullptr != dxgiDebugFunc)
        {
            result = dxgiDebugFunc(__uuidof(IDXGIDebug), reinterpret_cast<void**>(&m_pdxgiDebug));

            if (SUCCEEDED(result))
            {
                m_pdxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                AddIUnknown(m_pdxgiDebug, MAKE_STRING(m_pdxgiDebug));
            }
        }
    }

#endif

    result = CreateDXGIFactory2(dxgiFactoryFlags, __uuidof(IDXGIFactory2), reinterpret_cast<void**>(&m_pdxgiFactory2));

    if (FAILED(result))
    {
        return false;
    }

    AddIUnknown(m_pdxgiFactory2, MAKE_STRING(m_pdxgiFactory2));
    unsigned int                adapterCount = 0;
    std::vector<IDXGIAdapter1*> dxgiAdapters;
    IDXGIAdapter1*              pdxgiAdapter1 = nullptr;

    // description flag is only available in type IDXGIAdapter1 and later
    while (SUCCEEDED(m_pdxgiFactory2->EnumAdapters1(adapterCount, &pdxgiAdapter1)))
    {
        DXGI_ADAPTER_DESC1 adapterDesc1;
        pdxgiAdapter1->GetDesc1(&adapterDesc1);

        if (!(adapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE))
        {
            dxgiAdapters.push_back(pdxgiAdapter1);
            AddIUnknown(pdxgiAdapter1, MAKE_STRING(pdxgiAdapter1));
        }

        adapterCount++;
        pdxgiAdapter1 = nullptr;
    }

    if (!dxgiAdapters.empty())
    {
        pdxgiAdapter1 = dxgiAdapters.at(0);  // Pick first hardware adapter to create the device

        // Create the device
        result = D3D12CreateDevice(pdxgiAdapter1, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), reinterpret_cast<void**>(&m_pd3d12Device));

        if (FAILED(result))
        {
            return false;
        }

        AddIUnknown(m_pd3d12Device, MAKE_STRING(m_pd3d12Device));
        result = m_pdxgiFactory2->MakeWindowAssociation(g_windowHandle, DXGI_MWA_NO_ALT_ENTER);  // This will ensure Alt-Enter won't work

        if (FAILED(result))
        {
            return false;
        }

        // Unlike older APIs, DX12 swap chains can only be created
        // on command queue rather than on the device - create a command queue first
        D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
        cmdQueueDesc.Type                     = D3D12_COMMAND_LIST_TYPE_DIRECT;
        cmdQueueDesc.Priority                 = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
        cmdQueueDesc.Flags                    = D3D12_COMMAND_QUEUE_FLAG_NONE;
        cmdQueueDesc.NodeMask                 = 0;

        result = m_pd3d12Device->CreateCommandQueue(&cmdQueueDesc, __uuidof(ID3D12CommandQueue), reinterpret_cast<void**>(&m_pd3d12CommandQueue));

        if (FAILED(result))
        {
            return false;
        }

        AddIUnknown(m_pd3d12CommandQueue, MAKE_STRING(m_pd3d12CommandQueue));

        // Create swap chain
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width                 = g_windowWidth;
        swapChainDesc.Height                = g_windowHeight;
        swapChainDesc.Format                = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.Scaling               = DXGI_SCALING_NONE;
        swapChainDesc.Stereo                = false;
        swapChainDesc.SampleDesc.Count      = 1;
        swapChainDesc.SampleDesc.Quality    = 0;  // Irrelevant
        swapChainDesc.BufferCount           = ms_frameCount;
        swapChainDesc.BufferUsage           = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.SwapEffect            = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.Flags                 = NULL;

        IDXGISwapChain1* pdxgiSwapChain1 = nullptr;
        result = m_pdxgiFactory2->CreateSwapChainForHwnd(m_pd3d12CommandQueue, g_windowHandle, &swapChainDesc, nullptr, nullptr, &pdxgiSwapChain1);

        if (FAILED(result))
        {
            return false;
        }

        result = pdxgiSwapChain1->QueryInterface(__uuidof(IDXGISwapChain3), reinterpret_cast<void**>(&m_pdxgiSwapChain3));

        if (FAILED(result))
        {
            return false;
        }

        m_pdxgiSwapChain3->Release();
        AddIUnknown(m_pdxgiSwapChain3, MAKE_STRING(m_pdxgiSwapChain3));

        // Create a descriptor heap for render targets
        D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptionHeap = {};
        rtvDescriptionHeap.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvDescriptionHeap.NumDescriptors             = ms_frameCount;  // 2 RTVs for each view port
        rtvDescriptionHeap.Flags                      = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        rtvDescriptionHeap.NodeMask                   = 0;
        result = m_pd3d12Device->CreateDescriptorHeap(&rtvDescriptionHeap, __uuidof(ID3D12DescriptorHeap), reinterpret_cast<void**>(&m_pd3d12DescriptorHeap));

        if (FAILED(result))
        {
            return false;
        }

        AddIUnknown(m_pd3d12DescriptorHeap, MAKE_STRING(m_pd3d12DescriptorHeap));

        m_RTVdescriptorIncrementSize                    = m_pd3d12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptorHandle = m_pd3d12DescriptorHeap->GetCPUDescriptorHandleForHeapStart();

        // Create RTV resources for the swap chain RTV
        for (unsigned int i = 0; i < ms_frameCount; i++)
        {
            // Create the render target view resource in swap chain buffer
            result = m_pdxgiSwapChain3->GetBuffer(i, __uuidof(ID3D12Resource), reinterpret_cast<void**>(&m_pRTVResource[i]));

            if (FAILED(result))
            {
                return false;
            }

            m_pd3d12Device->CreateRenderTargetView(m_pRTVResource[i], nullptr, cpuDescriptorHandle);
            cpuDescriptorHandle.ptr = cpuDescriptorHandle.ptr + m_RTVdescriptorIncrementSize;  // offset to next descriptor
            AddIUnknown(m_pRTVResource[i], MAKE_STRING(m_pRTVResource[i]));
        }

        result = m_pd3d12Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), reinterpret_cast<void**>(&m_pd3d12Fence));

        if (FAILED(result))
        {
            return false;
        }

        AddIUnknown(m_pd3d12Fence, MAKE_STRING(m_pd3d12Fence));
        m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

        if (nullptr != m_fenceEvent)
        {
            // Create root signature
            D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
            rootSignatureDesc.NumParameters             = 0;
            rootSignatureDesc.pParameters               = nullptr;
            rootSignatureDesc.NumStaticSamplers         = 0;
            rootSignatureDesc.pStaticSamplers           = nullptr;
            rootSignatureDesc.Flags                     = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

            ID3DBlob* serializedSignature = nullptr;
            ID3DBlob* serailizationError  = nullptr;

            result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &serializedSignature, &serailizationError);

            if (FAILED(result))
            {
                return false;
            }

            result = m_pd3d12Device->CreateRootSignature(0,
                                                         serializedSignature->GetBufferPointer(),
                                                         serializedSignature->GetBufferSize(),
                                                         __uuidof(ID3D12RootSignature),
                                                         reinterpret_cast<void**>(&m_pD3D12RootSignature));

            if (FAILED(result))
            {
                return false;
            }

            AddIUnknown(m_pD3D12RootSignature, MAKE_STRING(m_pD3D12RootSignature));
            ID3DBlob* vertexShader = nullptr;
            ID3DBlob* pixelShader  = nullptr;
            ID3DBlob* error        = nullptr;

            UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wideToUtf8Converter;

            std::wstring shaderPath = wideToUtf8Converter.from_bytes(m_executablePath);
            shaderPath.append(L"shaders.hlsl");

            result = ::D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertexShader, &error);

            if (FAILED(result))
            {
                return false;
            }

            result = ::D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixelShader, &error);

            if (FAILED(result))
            {
                return false;
            }

            D3D12_SHADER_BYTECODE vsByteCode = {vertexShader->GetBufferPointer(), vertexShader->GetBufferSize()};
            D3D12_SHADER_BYTECODE psByteCode = {pixelShader->GetBufferPointer(), pixelShader->GetBufferSize()};

            // Create graphics pipeline using root signature - one for wireframe and another for fill drawing
            D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
            psoDesc.pRootSignature                     = m_pD3D12RootSignature;
            psoDesc.VS                                 = vsByteCode;
            psoDesc.PS                                 = psByteCode;
            psoDesc.BlendState                         = {};

            const D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc = {FALSE,
                                                                                 FALSE,
                                                                                 D3D12_BLEND_ONE,
                                                                                 D3D12_BLEND_ZERO,
                                                                                 D3D12_BLEND_OP_ADD,
                                                                                 D3D12_BLEND_ONE,
                                                                                 D3D12_BLEND_ZERO,
                                                                                 D3D12_BLEND_OP_ADD,
                                                                                 D3D12_LOGIC_OP_NOOP,
                                                                                 D3D12_COLOR_WRITE_ENABLE_ALL};

            psoDesc.BlendState.AlphaToCoverageEnable  = FALSE;
            psoDesc.BlendState.IndependentBlendEnable = FALSE;

            for (auto& psoBlendRenderTargetIter : psoDesc.BlendState.RenderTarget)
            {
                psoBlendRenderTargetIter = defaultRenderTargetBlendDesc;
            }

            psoDesc.RasterizerState.FillMode              = D3D12_FILL_MODE_SOLID;
            psoDesc.RasterizerState.CullMode              = D3D12_CULL_MODE_BACK;
            psoDesc.RasterizerState.FrontCounterClockwise = FALSE;
            psoDesc.RasterizerState.DepthBias             = D3D12_DEFAULT_DEPTH_BIAS;
            psoDesc.RasterizerState.DepthBiasClamp        = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
            psoDesc.RasterizerState.SlopeScaledDepthBias  = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
            psoDesc.RasterizerState.DepthClipEnable       = TRUE;
            psoDesc.RasterizerState.MultisampleEnable     = FALSE;
            psoDesc.RasterizerState.AntialiasedLineEnable = FALSE;
            psoDesc.RasterizerState.ForcedSampleCount     = 0;
            psoDesc.RasterizerState.ConservativeRaster    = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

            psoDesc.DepthStencilState                = {};
            psoDesc.DepthStencilState.DepthEnable    = true;
            psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
            psoDesc.DepthStencilState.DepthFunc      = D3D12_COMPARISON_FUNC_LESS_EQUAL;
            psoDesc.SampleMask                       = UINT_MAX;

            D3D12_INPUT_ELEMENT_DESC vertexInputDescription[] = {
                {"SCREEN_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
                {"VERTEX_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}};

            psoDesc.InputLayout           = {vertexInputDescription, 2};  // passing 2 elements - vertex and color
            psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
            psoDesc.NumRenderTargets      = 1;
            psoDesc.RTVFormats[0]         = DXGI_FORMAT_R8G8B8A8_UNORM;
            psoDesc.SampleDesc.Count      = 1;

            result = m_pd3d12Device->CreateGraphicsPipelineState(&psoDesc, __uuidof(ID3D12PipelineState), reinterpret_cast<void**>(&m_pfillDrawPipeline));

            if (FAILED(result))
            {
                return false;
            }

            AddIUnknown(m_pfillDrawPipeline, MAKE_STRING(m_pfillDrawPipeline));
            m_pCurrentPipelineState = m_pfillDrawPipeline;

            psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
            result = m_pd3d12Device->CreateGraphicsPipelineState(&psoDesc, __uuidof(ID3D12PipelineState), reinterpret_cast<void**>(&m_pWireframePipeline));

            if (FAILED(result))
            {
                return false;
            }

            AddIUnknown(m_pWireframePipeline, MAKE_STRING(m_pWireframePipeline));
            return true;
        }
    }

    return false;
}

bool CubeSample::InitializeViewPortResource()
{
    return m_topLeftViewport.Init() && m_topRightViewport.Init() && m_bottomLeftViewport.Init() && m_bottomRightViewport.Init();
}

bool CubeSample::UploadCubeData()
{
    bool success = false;

    VertexData vertexColorData[] = {
        {{-0.5, 0.5, -0.5, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},   // 0
        {{0.5, 0.5, -0.5, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},    // 1
        {{0.5, -0.5, -0.5, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},   // 2
        {{-0.5, -0.5, -0.5, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},  // 3
        {{-0.5, 0.5, 0.5, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},    // 4
        {{0.5, 0.5, 0.5, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},     // 5
        {{0.5, -0.5, 0.5, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},    // 6
        {{-0.5, -0.5, 0.5, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}    // 7
    };

    uint32_t indexData[] = {
        0, 1, 3, 3, 1, 2,  // -Z face
        7, 4, 5, 7, 5, 6,  // +Z face

        7, 0, 4, 7, 3, 0,  // -X face
        6, 5, 1, 6, 1, 2,  // +X face

        7, 2, 3, 7, 6, 2,  // -Y face
        4, 0, 5, 5, 0, 1,  // +Y face
    };

#pragma region VertexBuffer
    {
        D3D12_RESOURCE_DESC vertexDataBufferResourceDesc = {};
        vertexDataBufferResourceDesc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
        vertexDataBufferResourceDesc.Alignment           = 0;
        vertexDataBufferResourceDesc.Width               = sizeof(vertexColorData);
        vertexDataBufferResourceDesc.Height = vertexDataBufferResourceDesc.DepthOrArraySize = vertexDataBufferResourceDesc.MipLevels = 1;
        vertexDataBufferResourceDesc.Format                                                                                          = DXGI_FORMAT_UNKNOWN;
        vertexDataBufferResourceDesc.SampleDesc.Count                                                                                = 1;
        vertexDataBufferResourceDesc.SampleDesc.Quality                                                                              = 0;
        vertexDataBufferResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        vertexDataBufferResourceDesc.Flags  = D3D12_RESOURCE_FLAG_NONE;

        D3D12_HEAP_PROPERTIES bufferHeapProp = {};
        bufferHeapProp.Type                  = D3D12_HEAP_TYPE_UPLOAD;
        bufferHeapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        bufferHeapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;
        bufferHeapProp.CreationNodeMask      = 1;
        bufferHeapProp.VisibleNodeMask       = 1;

        // Create vertex data resource
        HRESULT result = m_pd3d12Device->CreateCommittedResource(&bufferHeapProp,
                                                                 D3D12_HEAP_FLAG_NONE,
                                                                 &vertexDataBufferResourceDesc,
                                                                 D3D12_RESOURCE_STATE_GENERIC_READ,
                                                                 nullptr,
                                                                 __uuidof(ID3D12Resource),
                                                                 reinterpret_cast<void**>(&m_pVertexBuffer));

        if (SUCCEEDED(result))
        {
            AddIUnknown(m_pVertexBuffer, MAKE_STRING(m_pVertexBuffer));
            D3D12_RANGE cpuAllowedReadRange = {};
            cpuAllowedReadRange.Begin       = 0;  // we won't be reading this from CPU after uploading the data
            cpuAllowedReadRange.End         = 0;  // we won't be reading this from CPU after uploading the data

            void* pVertexBufferCPULocation = nullptr;
            // Get the CPU pointer where we will upload the vertex data
            result = m_pVertexBuffer->Map(0, &cpuAllowedReadRange, &pVertexBufferCPULocation);

            if (SUCCEEDED(result))
            {
                // copy the vertex data to the CPU location
                memcpy(pVertexBufferCPULocation, vertexColorData, sizeof(vertexColorData));
                D3D12_RANGE* cpuModifiedRange = nullptr;  // nullptr indicates all of the buffer is modified
                m_pVertexBuffer->Unmap(0, cpuModifiedRange);

                m_vertexBufferView.BufferLocation = m_pVertexBuffer->GetGPUVirtualAddress();
                m_vertexBufferView.SizeInBytes    = sizeof(vertexColorData);
                m_vertexBufferView.StrideInBytes  = sizeof(VertexData);
                success                           = true;
            }
        }
    }
#pragma endregion

#pragma region IndexBuffer

    if (success)
    {
        D3D12_RESOURCE_DESC indexDataBufferResourceDesc = {};
        indexDataBufferResourceDesc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
        indexDataBufferResourceDesc.Alignment           = 0;
        indexDataBufferResourceDesc.Width               = sizeof(indexData);
        indexDataBufferResourceDesc.Height = indexDataBufferResourceDesc.DepthOrArraySize = indexDataBufferResourceDesc.MipLevels = 1;
        indexDataBufferResourceDesc.Format                                                                                        = DXGI_FORMAT_UNKNOWN;
        indexDataBufferResourceDesc.SampleDesc.Count                                                                              = 1;
        indexDataBufferResourceDesc.SampleDesc.Quality                                                                            = 0;
        indexDataBufferResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        indexDataBufferResourceDesc.Flags  = D3D12_RESOURCE_FLAG_NONE;

        D3D12_HEAP_PROPERTIES bufferHeapProp = {};
        bufferHeapProp.Type                  = D3D12_HEAP_TYPE_UPLOAD;
        bufferHeapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        bufferHeapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;
        bufferHeapProp.CreationNodeMask      = 1;
        bufferHeapProp.VisibleNodeMask       = 1;

        // Create index data resource
        HRESULT result = m_pd3d12Device->CreateCommittedResource(&bufferHeapProp,
                                                                 D3D12_HEAP_FLAG_NONE,
                                                                 &indexDataBufferResourceDesc,
                                                                 D3D12_RESOURCE_STATE_GENERIC_READ,
                                                                 nullptr,
                                                                 __uuidof(ID3D12Resource),
                                                                 reinterpret_cast<void**>(&m_pIndexBuffer));

        if (SUCCEEDED(result))
        {
            AddIUnknown(m_pIndexBuffer, MAKE_STRING(m_pIndexBuffer));
            D3D12_RANGE cpuAllowedReadRange = {};
            cpuAllowedReadRange.Begin       = 0;  // we won't be reading this from CPU after uploading the data
            cpuAllowedReadRange.End         = 0;  // we won't be reading this from CPU after uploading the data

            void* pIndexBufferCPULocation = nullptr;
            // Get the CPU pointer where we will upload the vertex data
            result = m_pIndexBuffer->Map(0, &cpuAllowedReadRange, &pIndexBufferCPULocation);

            if (SUCCEEDED(result))
            {
                // copy the vertex data to the CPU location
                memcpy(pIndexBufferCPULocation, indexData, sizeof(indexData));
                D3D12_RANGE* cpuModifiedRange = nullptr;  // nullptr indicates all of the buffer is modified
                m_pIndexBuffer->Unmap(0, cpuModifiedRange);

                m_indexBufferView.BufferLocation = m_pIndexBuffer->GetGPUVirtualAddress();
                m_indexBufferView.SizeInBytes    = sizeof(indexData);
                m_indexBufferView.Format         = DXGI_FORMAT_R32_UINT;
                success                          = true;
            }
        }
    }

#pragma endregion

    return success;
}

void CubeSample::AddIUnknown(IUnknown* pUnknown, const std::string& name)
{
    ID3D12Object* pObject = nullptr;
    HRESULT       result  = pUnknown->QueryInterface(__uuidof(ID3D12Object), reinterpret_cast<void**>(&pObject));

    std::wstring widename(name.begin(), name.end());

    if (SUCCEEDED(result))
    {
        result = pObject->SetName(widename.c_str());
        pObject->Release();
    }

    m_appCreatedIUnknown.push(std::pair<std::wstring, IUnknown*>(widename, pUnknown));
}

void CubeSample::AddCommandList(ID3D12GraphicsCommandList* pGraphicsCommandList)
{
    if (nullptr != pGraphicsCommandList)
    {
        m_graphicsCommandListVector.push_back(pGraphicsCommandList);
    }
}

CubeSample::Viewport::Viewport()
    : m_viewport()
    , m_pd3d12CommandList(nullptr)
    , m_pd3d12DirectCmdListAllocator(nullptr)
    , m_viewportInitialized(false)
    , m_viewPortRect()
    , m_gpaCommandListId(nullptr)
    , m_sampleId(ms_undefinedSampleId)
{
    m_viewport.Width    = 400.0f;
    m_viewport.Height   = 400.0f;
    m_viewport.MaxDepth = 1.0f;
    m_viewport.MinDepth = -1.0f;
}

void CubeSample::WaitForGpuToFinish()
{
    // wait for the frame to finish
    m_pd3d12CommandQueue->Signal(m_pd3d12Fence, m_fenceValue);
    m_pd3d12Fence->SetEventOnCompletion(m_fenceValue, m_fenceEvent);

    WaitForSingleObject(m_fenceEvent, INFINITE);
    m_fenceValue++;
    m_currentBackBufferIndex = m_pdxgiSwapChain3->GetCurrentBackBufferIndex();
}

CubeSample::TopLeftViewport::TopLeftViewport()
    : Viewport()
{
    m_viewport.TopLeftX   = 0.0f;
    m_viewport.TopLeftY   = 0.0f;
    m_viewportInitialized = true;

    m_viewPortRect = {static_cast<long>(m_viewport.TopLeftX),
                      static_cast<long>(m_viewport.TopLeftY),
                      static_cast<long>(m_viewport.TopLeftX + m_viewport.Width),
                      static_cast<long>(m_viewport.TopLeftY + m_viewport.Height)};
}

bool CubeSample::TopLeftViewport::Init()
{
    if (m_viewportInitialized)
    {
        HRESULT result = S_OK;

        // Create command allocator
        result = ms_pCubeSample->m_pd3d12Device->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&m_pd3d12DirectCmdListAllocator));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->AddIUnknown(m_pd3d12DirectCmdListAllocator, MAKE_STRING(TopLeftViewport->m_pd3d12DirectmdListAllocator));

        result = ms_pCubeSample->m_pd3d12Device->CreateCommandList(0,
                                                                   D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                                   m_pd3d12DirectCmdListAllocator,
                                                                   ms_pCubeSample->m_pfillDrawPipeline,
                                                                   __uuidof(ID3D12GraphicsCommandList),
                                                                   reinterpret_cast<void**>(&m_pd3d12CommandList));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->m_pCurrentPipelineState = ms_pCubeSample->m_pfillDrawPipeline;
        m_pd3d12CommandList->Close();
        ms_pCubeSample->m_currentBackBufferIndex = ms_pCubeSample->m_pdxgiSwapChain3->GetCurrentBackBufferIndex();
        ms_pCubeSample->AddCommandList(m_pd3d12CommandList);
        ms_pCubeSample->AddIUnknown(m_pd3d12CommandList, MAKE_STRING(TopLeftViewport->m_pd3d12CommandList));
        return true;
    }

    return false;
}

void CubeSample::TopLeftViewport::Draw()
{
    /*
     * In this view port, we will draw a cube on single primary command list
     * and record the performance counter with one sample using GPA
     */

    HRESULT result = m_pd3d12DirectCmdListAllocator->Reset();
    UNREFERENCED_PARAMETER(result);
    result = m_pd3d12CommandList->Reset(m_pd3d12DirectCmdListAllocator, ms_pCubeSample->m_pCurrentPipelineState);

    if (ms_pCubeSample->m_pipelineStateChanged)
    {
        m_pd3d12CommandList->SetPipelineState(ms_pCubeSample->m_pCurrentPipelineState);
    }

    m_pd3d12CommandList->SetGraphicsRootSignature(ms_pCubeSample->m_pD3D12RootSignature);
    m_pd3d12CommandList->RSSetViewports(1, &m_viewport);
    m_pd3d12CommandList->RSSetScissorRects(1, &ms_pCubeSample->m_scissorRect);

    D3D12_RESOURCE_TRANSITION_BARRIER transitionBarrier = {};
    transitionBarrier.pResource                         = ms_pCubeSample->m_pRTVResource[ms_pCubeSample->m_currentBackBufferIndex];
    transitionBarrier.Subresource                       = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    transitionBarrier.StateBefore                       = D3D12_RESOURCE_STATE_PRESENT;
    transitionBarrier.StateAfter                        = D3D12_RESOURCE_STATE_RENDER_TARGET;

    D3D12_RESOURCE_BARRIER resourceBarrier = {};
    resourceBarrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    resourceBarrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    resourceBarrier.Transition             = transitionBarrier;
    m_pd3d12CommandList->ResourceBarrier(1, &resourceBarrier);

    D3D12_CPU_DESCRIPTOR_HANDLE rtvDescriptorHeap;
    rtvDescriptorHeap.ptr = ms_pCubeSample->m_pd3d12DescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr +
                            ms_pCubeSample->m_currentBackBufferIndex * ms_pCubeSample->m_RTVdescriptorIncrementSize;
    m_pd3d12CommandList->OMSetRenderTargets(1, &rtvDescriptorHeap, FALSE, nullptr);

    if (ms_pCubeSample->m_currentPass == 0)
    {
        m_sampleId = ++ms_pCubeSample->m_sampleCounter;
    }

    m_pd3d12CommandList->ClearRenderTargetView(rtvDescriptorHeap, m_clearColor, 1, &m_viewPortRect);
    m_pd3d12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pd3d12CommandList->IASetVertexBuffers(0, 1, &ms_pCubeSample->m_vertexBufferView);
    m_pd3d12CommandList->IASetIndexBuffer(&ms_pCubeSample->m_indexBufferView);

#pragma region GPA_CALL
    bool commandListStarted =
        ms_pCubeSample->GPA_BeginCommandListForSampling(m_pd3d12CommandList, m_gpaCommandListId);  // Request GPA to start recording samples on the command list
    bool sampleStarted = false;

    if (commandListStarted)
    {
        sampleStarted = ms_pCubeSample->GPA_BeginSample(m_gpaCommandListId, m_sampleId);  // Start sample on the command list
    }
#pragma endregion

    m_pd3d12CommandList->DrawIndexedInstanced(36, 1, 0, 0, 0);

    transitionBarrier.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    transitionBarrier.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;

#pragma region GPA_CALL
    if (sampleStarted)
    {
        ms_pCubeSample->GPA_EndSample(m_gpaCommandListId);  // End the sample request

        if (commandListStarted)
        {
            ms_pCubeSample->GPA_EndCommandListForSampling(m_gpaCommandListId);  // End the command list for sample recording before closing the command list
        }
    }
#pragma endregion

    // update transition
    resourceBarrier.Transition = transitionBarrier;
    m_pd3d12CommandList->ResourceBarrier(1, &resourceBarrier);
    m_pd3d12CommandList->Close();
}

void CubeSample::TopLeftViewport::ResetForNextPass()
{
    m_gpaCommandListId = nullptr;
}

void CubeSample::TopLeftViewport::IterateSamples(std::function<void(const unsigned& sampleIndex)> func) const
{
    if (ms_undefinedSampleId != m_sampleId)
    {
        func(m_sampleId);
    }
}

CubeSample::TopRightViewport::TopRightViewport()
    : Viewport()
    , m_pBundleCommandAllocator(nullptr)
    , m_pBundleCmdList(nullptr)
    , m_gpaCmdListForBundle(nullptr)
    , m_bundleSampleId(0xFFFF)
{
    m_viewport.TopLeftX   = 400.0f;
    m_viewport.TopLeftY   = 0.0f;
    m_viewportInitialized = true;

    m_viewPortRect = {static_cast<long>(m_viewport.TopLeftX),
                      static_cast<long>(m_viewport.TopLeftY),
                      static_cast<long>(m_viewport.TopLeftX + m_viewport.Width),
                      static_cast<long>(m_viewport.TopLeftY + m_viewport.Height)};
}

bool CubeSample::TopRightViewport::Init()
{
    if (m_viewportInitialized)
    {
        HRESULT result = S_OK;

        // Create command allocator
        result = ms_pCubeSample->m_pd3d12Device->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&m_pd3d12DirectCmdListAllocator));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->AddIUnknown(m_pd3d12DirectCmdListAllocator, MAKE_STRING(TopRightViewport->m_pd3d12DirectCmdListAllocator));

        // Create command allocator for bundles
        result = ms_pCubeSample->m_pd3d12Device->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_BUNDLE, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&m_pBundleCommandAllocator));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->AddIUnknown(m_pBundleCommandAllocator, MAKE_STRING(TopRightViewport->m_pBundleCommandAllocator));

        result = ms_pCubeSample->m_pd3d12Device->CreateCommandList(0,
                                                                   D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                                   m_pd3d12DirectCmdListAllocator,
                                                                   ms_pCubeSample->m_pfillDrawPipeline,
                                                                   __uuidof(ID3D12GraphicsCommandList),
                                                                   reinterpret_cast<void**>(&m_pd3d12CommandList));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->AddIUnknown(m_pd3d12CommandList, MAKE_STRING(TopRightViewport->m_pd3d12CommandList));

        result = ms_pCubeSample->m_pd3d12Device->CreateCommandList(0,
                                                                   D3D12_COMMAND_LIST_TYPE_BUNDLE,
                                                                   m_pBundleCommandAllocator,
                                                                   ms_pCubeSample->m_pfillDrawPipeline,
                                                                   __uuidof(ID3D12GraphicsCommandList),
                                                                   reinterpret_cast<void**>(&m_pBundleCmdList));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->m_pCurrentPipelineState = ms_pCubeSample->m_pfillDrawPipeline;
        m_pd3d12CommandList->Close();
        m_pBundleCmdList->Close();
        ms_pCubeSample->m_currentBackBufferIndex = ms_pCubeSample->m_pdxgiSwapChain3->GetCurrentBackBufferIndex();
        ms_pCubeSample->AddCommandList(m_pd3d12CommandList);
        ms_pCubeSample->AddIUnknown(m_pBundleCmdList, MAKE_STRING(TopRightViewport->m_pBundleCmdList));
        return true;
    }

    return false;
}

void CubeSample::TopRightViewport::Draw()
{
    /*
     * In this view port, we will be recording drawing of a cube on a bundle and execute it using primary command list
     * Usually, bundle are recorded once and executed multiple times. However in case of multi-pass sampling, GPA must
     * record the set of counters to enable on each pass, we need to record the bundle command as like a direct command list.
     *
     * Performance counter result for the samples on the bundles can't be retrieved directly from GPA in accordance with a fact that
     * bundle can't be executed without a direct command list. To get the result of the bundle sample, app must copy the sample over
     * direct command list with new set of sample ids after each execution of the bundle.
    */

    HRESULT result = m_pd3d12DirectCmdListAllocator->Reset();
    UNREFERENCED_PARAMETER(result);
    result = m_pd3d12CommandList->Reset(m_pd3d12DirectCmdListAllocator, ms_pCubeSample->m_pCurrentPipelineState);

    result = m_pBundleCommandAllocator->Reset();
    result = m_pBundleCmdList->Reset(m_pBundleCommandAllocator, ms_pCubeSample->m_pCurrentPipelineState);

    if (ms_pCubeSample->m_pipelineStateChanged)
    {
        m_pd3d12CommandList->SetPipelineState(ms_pCubeSample->m_pCurrentPipelineState);
        m_pBundleCmdList->SetPipelineState(ms_pCubeSample->m_pCurrentPipelineState);
    }

    if (ms_pCubeSample->m_currentPass == 0)
    {
        if (args.m_profileBundles)
        {
            m_bundleSampleId = ++ms_pCubeSample->m_sampleCounter;  // Bundle sample id - result can't be retrieved using this
            m_sampleId       = ++ms_pCubeSample->m_sampleCounter;  // Copied sample id
        }
    }

#pragma region GPA_CALL
    bool bundleCommandListStarted = false;
    bool sampleStarted            = false;

    if (args.m_profileBundles)
    {
        bundleCommandListStarted =
            ms_pCubeSample->GPA_BeginCommandListForSampling(m_pBundleCmdList, m_gpaCmdListForBundle);  // Request GPA to start recording samples on the bundle

        if (bundleCommandListStarted)
        {
            sampleStarted = ms_pCubeSample->GPA_BeginSample(m_gpaCmdListForBundle, m_bundleSampleId);  // Start sample on the bundle
        }
    }
#pragma endregion

    m_pBundleCmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pBundleCmdList->IASetVertexBuffers(0, 1, &ms_pCubeSample->m_vertexBufferView);
    m_pBundleCmdList->IASetIndexBuffer(&ms_pCubeSample->m_indexBufferView);
    m_pBundleCmdList->DrawIndexedInstanced(36, 1, 0, 0, 0);

#pragma region GPA_CALL
    if (sampleStarted)
    {
        ms_pCubeSample->GPA_EndSample(m_gpaCmdListForBundle);  // End the sample request

        if (bundleCommandListStarted)
        {
            ms_pCubeSample->GPA_EndCommandListForSampling(m_gpaCmdListForBundle);  // End the bundle for sample recording before closing the command list
        }
    }
#pragma endregion

    m_pBundleCmdList->Close();

    m_pd3d12CommandList->SetGraphicsRootSignature(ms_pCubeSample->m_pD3D12RootSignature);
    m_pd3d12CommandList->RSSetViewports(1, &m_viewport);
    m_pd3d12CommandList->RSSetScissorRects(1, &ms_pCubeSample->m_scissorRect);

    D3D12_RESOURCE_TRANSITION_BARRIER transitionBarrier = {};
    transitionBarrier.pResource                         = ms_pCubeSample->m_pRTVResource[ms_pCubeSample->m_currentBackBufferIndex];
    transitionBarrier.Subresource                       = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    transitionBarrier.StateBefore                       = D3D12_RESOURCE_STATE_PRESENT;
    transitionBarrier.StateAfter                        = D3D12_RESOURCE_STATE_RENDER_TARGET;

    D3D12_RESOURCE_BARRIER resourceBarrier = {};
    resourceBarrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    resourceBarrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    resourceBarrier.Transition             = transitionBarrier;
    m_pd3d12CommandList->ResourceBarrier(1, &resourceBarrier);

    D3D12_CPU_DESCRIPTOR_HANDLE rtvDescriptorHeap;
    rtvDescriptorHeap.ptr = ms_pCubeSample->m_pd3d12DescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr +
                            ms_pCubeSample->m_currentBackBufferIndex * ms_pCubeSample->m_RTVdescriptorIncrementSize;
    m_pd3d12CommandList->OMSetRenderTargets(1, &rtvDescriptorHeap, FALSE, nullptr);

    m_pd3d12CommandList->ClearRenderTargetView(rtvDescriptorHeap, m_clearColor, 1, &m_viewPortRect);

#pragma region GPA_CALL
    bool commandListStarted = ms_pCubeSample->GPA_BeginCommandListForSampling(
        m_pd3d12CommandList, m_gpaCommandListId);  // Request GPA to start recording samples on the direct command list
#pragma endregion

    m_pd3d12CommandList->ExecuteBundle(m_pBundleCmdList);

#pragma region GPA_CALL
    if (commandListStarted && bundleCommandListStarted)
    {
        std::vector<unsigned int> tempVector = {m_sampleId};
        ms_pCubeSample->GPA_CopyBundleSample(
            m_gpaCmdListForBundle, m_gpaCommandListId, tempVector);  // Copy the bundle sample to the direct command list after its execution
    }
#pragma endregion

    transitionBarrier.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    transitionBarrier.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;

#pragma region GPA_CALL
    if (commandListStarted)
    {
        ms_pCubeSample->GPA_EndCommandListForSampling(m_gpaCommandListId);  // End the direct command list for sample recording before closing it.
    }
#pragma endregion

    // update transition
    resourceBarrier.Transition = transitionBarrier;
    m_pd3d12CommandList->ResourceBarrier(1, &resourceBarrier);
    m_pd3d12CommandList->Close();
}

void CubeSample::TopRightViewport::ResetForNextPass()
{
    m_gpaCmdListForBundle = m_gpaCommandListId = nullptr;
}

void CubeSample::TopRightViewport::IterateSamples(std::function<void(const unsigned& sampleIndex)> func) const
{
    if (ms_undefinedSampleId != m_sampleId)
    {
        func(m_sampleId);
    }
}

CubeSample::BottomLeftViewport::BottomLeftViewport()
    : Viewport()
    , m_pSecondCmdListAllocator(nullptr)
    , m_pSecondCmdList(nullptr)
    , m_gpaCmdListForSecondCmdList(nullptr)
{
    m_viewport.TopLeftX   = 0.0f;
    m_viewport.TopLeftY   = 400.0f;
    m_viewportInitialized = true;

    m_viewPortRect = {static_cast<long>(m_viewport.TopLeftX),
                      static_cast<long>(m_viewport.TopLeftY),
                      static_cast<long>(m_viewport.TopLeftX + m_viewport.Width),
                      static_cast<long>(m_viewport.TopLeftY + m_viewport.Height)};
}

bool CubeSample::BottomLeftViewport::Init()
{
    if (m_viewportInitialized)
    {
        HRESULT result = S_OK;

        // Create command allocator
        result = ms_pCubeSample->m_pd3d12Device->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&m_pd3d12DirectCmdListAllocator));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->AddIUnknown(m_pd3d12DirectCmdListAllocator, MAKE_STRING(BottomLeftViewport->m_pd3d12DirectCmdListAllocator));

        result = ms_pCubeSample->m_pd3d12Device->CreateCommandList(0,
                                                                   D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                                   m_pd3d12DirectCmdListAllocator,
                                                                   ms_pCubeSample->m_pfillDrawPipeline,
                                                                   __uuidof(ID3D12GraphicsCommandList),
                                                                   reinterpret_cast<void**>(&m_pd3d12CommandList));

        if (FAILED(result))
        {
            return false;
        }

        m_pd3d12CommandList->Close();
        ms_pCubeSample->AddCommandList(m_pd3d12CommandList);
        ms_pCubeSample->AddIUnknown(m_pd3d12CommandList, MAKE_STRING(BottomLeftViewport->m_pd3d12CommandList));

        result = ms_pCubeSample->m_pd3d12Device->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&m_pSecondCmdListAllocator));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->AddIUnknown(m_pSecondCmdListAllocator, MAKE_STRING(BottomLeftViewport->m_pSecondCmdListAllocator));

        result = ms_pCubeSample->m_pd3d12Device->CreateCommandList(0,
                                                                   D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                                   m_pSecondCmdListAllocator,
                                                                   ms_pCubeSample->m_pfillDrawPipeline,
                                                                   __uuidof(ID3D12GraphicsCommandList),
                                                                   reinterpret_cast<void**>(&m_pSecondCmdList));

        if (FAILED(result))
        {
            return false;
        }

        m_pSecondCmdList->Close();
        ms_pCubeSample->AddCommandList(m_pSecondCmdList);
        ms_pCubeSample->AddIUnknown(m_pSecondCmdList, MAKE_STRING(BottomLeftViewport->m_pSecondCmdList));

        ms_pCubeSample->m_pCurrentPipelineState  = ms_pCubeSample->m_pfillDrawPipeline;
        ms_pCubeSample->m_currentBackBufferIndex = ms_pCubeSample->m_pdxgiSwapChain3->GetCurrentBackBufferIndex();

        return true;
    }

    return false;
}

void CubeSample::BottomLeftViewport::Draw()
{
    /*
    * In this view port, we will be recording drawing of a cube using two direct command list
    * Each of the command list will draw the half of the triangle, though the GPA sample for
    * performance counters will span over the command list.
    */

    HRESULT result = m_pd3d12DirectCmdListAllocator->Reset();
    UNREFERENCED_PARAMETER(result);
    result = m_pSecondCmdListAllocator->Reset();
    result = m_pd3d12CommandList->Reset(m_pd3d12DirectCmdListAllocator, ms_pCubeSample->m_pCurrentPipelineState);
    result = m_pSecondCmdList->Reset(m_pSecondCmdListAllocator, ms_pCubeSample->m_pCurrentPipelineState);

    if (ms_pCubeSample->m_pipelineStateChanged)
    {
        m_pd3d12CommandList->SetPipelineState(ms_pCubeSample->m_pCurrentPipelineState);
        m_pSecondCmdList->SetPipelineState(ms_pCubeSample->m_pCurrentPipelineState);
    }

    if (ms_pCubeSample->m_currentPass == 0)
    {
        m_sampleId = ++ms_pCubeSample->m_sampleCounter;
    }

    m_pd3d12CommandList->SetGraphicsRootSignature(ms_pCubeSample->m_pD3D12RootSignature);
    m_pd3d12CommandList->RSSetViewports(1, &m_viewport);
    m_pd3d12CommandList->RSSetScissorRects(1, &ms_pCubeSample->m_scissorRect);

    m_pSecondCmdList->SetGraphicsRootSignature(ms_pCubeSample->m_pD3D12RootSignature);
    m_pSecondCmdList->RSSetViewports(1, &m_viewport);
    m_pSecondCmdList->RSSetScissorRects(1, &ms_pCubeSample->m_scissorRect);

    D3D12_RESOURCE_TRANSITION_BARRIER transitionBarrier = {};
    transitionBarrier.pResource                         = ms_pCubeSample->m_pRTVResource[ms_pCubeSample->m_currentBackBufferIndex];
    transitionBarrier.Subresource                       = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    transitionBarrier.StateBefore                       = D3D12_RESOURCE_STATE_PRESENT;
    transitionBarrier.StateAfter                        = D3D12_RESOURCE_STATE_RENDER_TARGET;

    D3D12_RESOURCE_BARRIER resourceBarrier = {};
    resourceBarrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    resourceBarrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    resourceBarrier.Transition             = transitionBarrier;
    m_pd3d12CommandList->ResourceBarrier(1, &resourceBarrier);
    m_pSecondCmdList->ResourceBarrier(1, &resourceBarrier);

    D3D12_CPU_DESCRIPTOR_HANDLE rtvDescriptorHeap;
    rtvDescriptorHeap.ptr = ms_pCubeSample->m_pd3d12DescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr +
                            ms_pCubeSample->m_currentBackBufferIndex * ms_pCubeSample->m_RTVdescriptorIncrementSize;
    m_pd3d12CommandList->OMSetRenderTargets(1, &rtvDescriptorHeap, FALSE, nullptr);
    m_pSecondCmdList->OMSetRenderTargets(1, &rtvDescriptorHeap, FALSE, nullptr);

    m_pd3d12CommandList->ClearRenderTargetView(rtvDescriptorHeap, m_clearColor, 1, &m_viewPortRect);

#pragma region GPA_CALL
    bool commandListStarted = ms_pCubeSample->GPA_BeginCommandListForSampling(
        m_pd3d12CommandList, m_gpaCommandListId);  // Request GPA to start recording samples on the first direct command list
    bool sampleStarted = false;

    if (commandListStarted)
    {
        sampleStarted =
            ms_pCubeSample->GPA_BeginSample(m_gpaCommandListId, m_sampleId);  // Start sample on the first direct command list i.e. m_gpaCommandListId
    }
#pragma endregion

    m_pd3d12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pd3d12CommandList->IASetVertexBuffers(0, 1, &ms_pCubeSample->m_vertexBufferView);
    m_pd3d12CommandList->IASetIndexBuffer(&ms_pCubeSample->m_indexBufferView);
    m_pd3d12CommandList->DrawIndexedInstanced(18, 1, 0, 0, 0);  // Draw half cube

    m_pSecondCmdList->ClearRenderTargetView(rtvDescriptorHeap, m_clearColor, 1, &m_viewPortRect);

#pragma region GPA_CALL
    bool secondCommandListStarted = ms_pCubeSample->GPA_BeginCommandListForSampling(
        m_pSecondCmdList, m_gpaCmdListForSecondCmdList);  // Request GPA to start recording samples on the second direct command list

    if (secondCommandListStarted && sampleStarted)
    {
        ms_pCubeSample->GPA_ContinueSample(m_sampleId, m_gpaCmdListForSecondCmdList);  // Continue the original sample to the second direct command list
    }
#pragma endregion

    m_pSecondCmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pSecondCmdList->IASetVertexBuffers(0, 1, &ms_pCubeSample->m_vertexBufferView);
    m_pSecondCmdList->IASetIndexBuffer(&ms_pCubeSample->m_indexBufferView);
    m_pSecondCmdList->DrawIndexedInstanced(18, 18, 0, 0, 0);  // Draw half cube

    transitionBarrier.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    transitionBarrier.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;

#pragma region GPA_CALL
    if (commandListStarted)
    {
        ms_pCubeSample->GPA_EndCommandListForSampling(m_gpaCommandListId);  // End the first direct command list for sample recording before closing it.
    }
#pragma endregion

#pragma region GPA_CALL
    if (sampleStarted)
    {
        ms_pCubeSample->GPA_EndSample(m_gpaCmdListForSecondCmdList);  // End the continuing sample on the second command list
    }

    if (secondCommandListStarted)
    {
        ms_pCubeSample->GPA_EndCommandListForSampling(
            m_gpaCmdListForSecondCmdList);  // End the second direct command list for sample recording before closing it.
    }
#pragma endregion

    // update transition
    resourceBarrier.Transition = transitionBarrier;
    m_pd3d12CommandList->ResourceBarrier(1, &resourceBarrier);
    m_pd3d12CommandList->Close();

    m_pSecondCmdList->ResourceBarrier(1, &resourceBarrier);
    m_pSecondCmdList->Close();
}

void CubeSample::BottomLeftViewport::ResetForNextPass()
{
    m_gpaCmdListForSecondCmdList = m_gpaCommandListId = nullptr;
}

void CubeSample::BottomLeftViewport::IterateSamples(std::function<void(const unsigned& sampleIndex)> func) const
{
    if (ms_undefinedSampleId != m_sampleId)
    {
        func(m_sampleId);
    }
}

CubeSample::BottomRightViewport::BottomRightViewport()
    : Viewport()
    , m_pSecondCommandListAllocator(nullptr)
    , m_pBundleCommandListAllocator(nullptr)
    , m_pBundle(nullptr)
    , m_gpaCmdListForBundle(nullptr)
    , m_bundleSampleId(0xFFFF)
    , m_bundleSampleIdOnPrimaryCmdList(ms_undefinedSampleId)
    , m_secondCommandList(nullptr)
    , m_gpaCmdListForSecondCmdList(nullptr)
{
    m_viewport.TopLeftX   = 400.0f;
    m_viewport.TopLeftY   = 400.0f;
    m_viewportInitialized = true;

    m_viewPortRect = {static_cast<long>(m_viewport.TopLeftX),
                      static_cast<long>(m_viewport.TopLeftY),
                      static_cast<long>(m_viewport.TopLeftX + m_viewport.Width),
                      static_cast<long>(m_viewport.TopLeftY + m_viewport.Height)};
}

bool CubeSample::BottomRightViewport::Init()
{
    if (m_viewportInitialized)
    {
        HRESULT result = S_OK;

        // Create command allocator
        result = ms_pCubeSample->m_pd3d12Device->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&m_pd3d12DirectCmdListAllocator));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->AddIUnknown(m_pd3d12DirectCmdListAllocator, MAKE_STRING(BottomRightViewport->m_pd3d12DirectCmdListAllocator));

        result = ms_pCubeSample->m_pd3d12Device->CreateCommandList(0,
                                                                   D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                                   m_pd3d12DirectCmdListAllocator,
                                                                   ms_pCubeSample->m_pfillDrawPipeline,
                                                                   __uuidof(ID3D12GraphicsCommandList),
                                                                   reinterpret_cast<void**>(&m_pd3d12CommandList));

        if (FAILED(result))
        {
            return false;
        }

        m_pd3d12CommandList->Close();
        ms_pCubeSample->AddCommandList(m_pd3d12CommandList);
        ms_pCubeSample->AddIUnknown(m_pd3d12CommandList, MAKE_STRING(BottomRightViewport->m_pd3d12CommandList));

        // second command list
        result = ms_pCubeSample->m_pd3d12Device->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&m_pSecondCommandListAllocator));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->AddIUnknown(m_pSecondCommandListAllocator, MAKE_STRING(BottomRightViewport->m_pSecondCommandListAllocator));

        result = ms_pCubeSample->m_pd3d12Device->CreateCommandList(0,
                                                                   D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                                   m_pSecondCommandListAllocator,
                                                                   ms_pCubeSample->m_pfillDrawPipeline,
                                                                   __uuidof(ID3D12GraphicsCommandList),
                                                                   reinterpret_cast<void**>(&m_secondCommandList));

        if (FAILED(result))
        {
            return false;
        }

        m_secondCommandList->Close();
        ms_pCubeSample->AddCommandList(m_secondCommandList);
        ms_pCubeSample->AddIUnknown(m_secondCommandList, MAKE_STRING(BottomRightViewport->m_secondCommandList));

        // create and record bundle
        result = ms_pCubeSample->m_pd3d12Device->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_BUNDLE, __uuidof(ID3D12CommandAllocator), reinterpret_cast<void**>(&m_pBundleCommandListAllocator));

        if (FAILED(result))
        {
            return false;
        }

        ms_pCubeSample->AddIUnknown(m_pBundleCommandListAllocator, MAKE_STRING(BottomRightViewport->m_pBundleCommandListAllocator));

        result = ms_pCubeSample->m_pd3d12Device->CreateCommandList(0,
                                                                   D3D12_COMMAND_LIST_TYPE_BUNDLE,
                                                                   m_pBundleCommandListAllocator,
                                                                   ms_pCubeSample->m_pfillDrawPipeline,
                                                                   __uuidof(ID3D12GraphicsCommandList),
                                                                   reinterpret_cast<void**>(&m_pBundle));

        if (FAILED(result))
        {
            return false;
        }

        m_pBundle->Close();
        ms_pCubeSample->AddIUnknown(m_pBundle, MAKE_STRING(BottomRightViewport->m_pBundle));
        ms_pCubeSample->m_currentBackBufferIndex = ms_pCubeSample->m_pdxgiSwapChain3->GetCurrentBackBufferIndex();
        ms_pCubeSample->m_pCurrentPipelineState  = ms_pCubeSample->m_pfillDrawPipeline;
        return true;
    }

    return false;
}

void CubeSample::BottomRightViewport::Draw()
{
    /*
    * In this view port, we will be recording drawing of a cube with a bundle and two direct command list
    * each drawing 1/3rd of the cube.
    */

    HRESULT result = m_pd3d12DirectCmdListAllocator->Reset();
    UNREFERENCED_PARAMETER(result);
    result = m_pSecondCommandListAllocator->Reset();
    result = m_pBundleCommandListAllocator->Reset();

    result = m_pd3d12CommandList->Reset(m_pd3d12DirectCmdListAllocator, ms_pCubeSample->m_pCurrentPipelineState);
    result = m_secondCommandList->Reset(m_pSecondCommandListAllocator, ms_pCubeSample->m_pCurrentPipelineState);
    result = m_pBundle->Reset(m_pBundleCommandListAllocator, ms_pCubeSample->m_pCurrentPipelineState);

    if (ms_pCubeSample->m_pipelineStateChanged)
    {
        m_pd3d12CommandList->SetPipelineState(ms_pCubeSample->m_pCurrentPipelineState);
        m_secondCommandList->SetPipelineState(ms_pCubeSample->m_pCurrentPipelineState);
        m_pBundle->SetPipelineState(ms_pCubeSample->m_pCurrentPipelineState);
    }

    if (ms_pCubeSample->m_currentPass == 0)
    {
        if (args.m_profileBundles)
        {
            m_bundleSampleId                 = ++ms_pCubeSample->m_sampleCounter;  // Bundle sample
            m_bundleSampleIdOnPrimaryCmdList = ++ms_pCubeSample->m_sampleCounter;  // Copied sample of the bundle
            m_sampleId                       = ++ms_pCubeSample->m_sampleCounter;  // This sample will span over two direct command list
        }
    }

#pragma region GPA_CALL
    bool bundleCommandListStarted = false;
    bool sampleStarted            = false;

    if (args.m_profileBundles)
    {
        bundleCommandListStarted =
            ms_pCubeSample->GPA_BeginCommandListForSampling(m_pBundle, m_gpaCmdListForBundle);  // Request GPA to start recording samples on the bundle

        if (bundleCommandListStarted)
        {
            sampleStarted = ms_pCubeSample->GPA_BeginSample(m_gpaCmdListForBundle, m_bundleSampleId);  // Start sample on the bundle
        }
    }
#pragma endregion

    m_pBundle->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pBundle->IASetVertexBuffers(0, 1, &ms_pCubeSample->m_vertexBufferView);
    m_pBundle->IASetIndexBuffer(&ms_pCubeSample->m_indexBufferView);
    m_pBundle->DrawIndexedInstanced(12, 1, 0, 0, 0);  // Draw 1/3 of the cube

#pragma region GPA_CALL
    if (sampleStarted)
    {
        ms_pCubeSample->GPA_EndSample(m_gpaCmdListForBundle);  // End the sample request on the bundle

        if (bundleCommandListStarted)
        {
            ms_pCubeSample->GPA_EndCommandListForSampling(m_gpaCmdListForBundle);  // End the bundle for sample recording before closing it.
        }
    }
#pragma endregion

    m_pBundle->Close();

    m_pd3d12CommandList->SetGraphicsRootSignature(ms_pCubeSample->m_pD3D12RootSignature);
    m_pd3d12CommandList->RSSetViewports(1, &m_viewport);
    m_pd3d12CommandList->RSSetScissorRects(1, &ms_pCubeSample->m_scissorRect);

    m_secondCommandList->SetGraphicsRootSignature(ms_pCubeSample->m_pD3D12RootSignature);
    m_secondCommandList->RSSetViewports(1, &m_viewport);
    m_secondCommandList->RSSetScissorRects(1, &ms_pCubeSample->m_scissorRect);

    D3D12_RESOURCE_TRANSITION_BARRIER transitionBarrier = {};
    transitionBarrier.pResource                         = ms_pCubeSample->m_pRTVResource[ms_pCubeSample->m_currentBackBufferIndex];
    transitionBarrier.Subresource                       = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    transitionBarrier.StateBefore                       = D3D12_RESOURCE_STATE_PRESENT;
    transitionBarrier.StateAfter                        = D3D12_RESOURCE_STATE_RENDER_TARGET;

    D3D12_RESOURCE_BARRIER resourceBarrier = {};
    resourceBarrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    resourceBarrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    resourceBarrier.Transition             = transitionBarrier;

    m_pd3d12CommandList->ResourceBarrier(1, &resourceBarrier);
    m_secondCommandList->ResourceBarrier(1, &resourceBarrier);

    D3D12_CPU_DESCRIPTOR_HANDLE rtvDescriptorHeap;
    rtvDescriptorHeap.ptr = ms_pCubeSample->m_pd3d12DescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr +
                            ms_pCubeSample->m_currentBackBufferIndex * ms_pCubeSample->m_RTVdescriptorIncrementSize;
    m_pd3d12CommandList->OMSetRenderTargets(1, &rtvDescriptorHeap, FALSE, nullptr);
    m_secondCommandList->OMSetRenderTargets(1, &rtvDescriptorHeap, FALSE, nullptr);

    m_pd3d12CommandList->ClearRenderTargetView(rtvDescriptorHeap, m_clearColor, 1, &m_viewPortRect);

    m_pd3d12CommandList->ExecuteBundle(m_pBundle);  // Execute bundle

    m_pd3d12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pd3d12CommandList->IASetVertexBuffers(0, 1, &ms_pCubeSample->m_vertexBufferView);
    m_pd3d12CommandList->IASetIndexBuffer(&ms_pCubeSample->m_indexBufferView);

    m_secondCommandList->ClearRenderTargetView(rtvDescriptorHeap, m_clearColor, 1, &m_viewPortRect);

#pragma region GPA_CALL
    bool commandListStarted = ms_pCubeSample->GPA_BeginCommandListForSampling(
        m_pd3d12CommandList, m_gpaCommandListId);  // Request GPA to start recording samples on the first direct command list

    bool secondCommandListStarted = ms_pCubeSample->GPA_BeginCommandListForSampling(
        m_secondCommandList, m_gpaCmdListForSecondCmdList);  // Request GPA to start recording samples on the second direct command list
#pragma endregion

    m_secondCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_secondCommandList->IASetVertexBuffers(0, 1, &ms_pCubeSample->m_vertexBufferView);
    m_secondCommandList->IASetIndexBuffer(&ms_pCubeSample->m_indexBufferView);

#pragma region GPA_CALL
    if (bundleCommandListStarted && commandListStarted)
    {
        std::vector<unsigned int> tempVector = {m_bundleSampleIdOnPrimaryCmdList};
        ms_pCubeSample->GPA_CopyBundleSample(m_gpaCmdListForBundle,
                                             m_gpaCommandListId,
                                             tempVector);  // Copy the bundle sample to the direct command list after its execution on first direct command list
    }

    if (commandListStarted)
    {
        sampleStarted =
            ms_pCubeSample->GPA_BeginSample(m_gpaCommandListId, m_sampleId);  // Start sample on the first direct command list i.e. m_gpaCommandListId
    }

    if (sampleStarted && secondCommandListStarted)
    {
        ms_pCubeSample->GPA_ContinueSample(m_sampleId, m_gpaCmdListForSecondCmdList);  // Continue the original sample to the second direct command list
    }
#pragma endregion

    m_pd3d12CommandList->DrawIndexedInstanced(12, 12, 0, 0, 0);  // Draw 1/3rd of cube

    m_secondCommandList->DrawIndexedInstanced(24, 12, 0, 0, 0);  // Draw 1/3rd of cube

    transitionBarrier.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    transitionBarrier.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;

#pragma region GPA_CALL
    if (sampleStarted)
    {
        ms_pCubeSample->GPA_EndSample(m_gpaCmdListForSecondCmdList);  // End the continuing sample on the second command list
    }

    if (secondCommandListStarted)
    {
        ms_pCubeSample->GPA_EndCommandListForSampling(
            m_gpaCmdListForSecondCmdList);  // End the second direct command list for sample recording before closing it.
    }

    if (commandListStarted)
    {
        ms_pCubeSample->GPA_EndCommandListForSampling(m_gpaCommandListId);  // End the first direct command list for sample recording before closing it.
    }
#pragma endregion

    // update transition
    resourceBarrier.Transition = transitionBarrier;
    m_pd3d12CommandList->ResourceBarrier(1, &resourceBarrier);
    m_pd3d12CommandList->Close();

    m_secondCommandList->ResourceBarrier(1, &resourceBarrier);
    m_secondCommandList->Close();
}

void CubeSample::BottomRightViewport::ResetForNextPass()
{
    m_gpaCmdListForSecondCmdList = m_gpaCmdListForBundle = m_gpaCommandListId = nullptr;
}

void CubeSample::BottomRightViewport::IterateSamples(std::function<void(const unsigned& sampleIndex)> func) const
{
    if (ms_undefinedSampleId != m_bundleSampleIdOnPrimaryCmdList)
    {
        func(m_bundleSampleIdOnPrimaryCmdList);
    }

    if (ms_undefinedSampleId != m_sampleId)
    {
        func(m_sampleId);
    }
}

void CubeSample::Draw()
{
    if (m_profilingEnable)
    {
        if (m_currentPass <= 0)
        {
            ++m_frameCounter;
        }
    }
    else
    {
        ++m_frameCounter;
    }

    ID3D12PipelineState* pTempPipelineState = ms_pCubeSample->m_pCurrentPipelineState;

    if (ms_pCubeSample->m_wireframe)
    {
        ms_pCubeSample->m_pCurrentPipelineState = m_pWireframePipeline;
    }
    else
    {
        m_pCurrentPipelineState = m_pfillDrawPipeline;
    }

    if (pTempPipelineState != m_pCurrentPipelineState)
    {
        m_pipelineStateChanged = true;
    }

    m_topLeftViewport.Draw();
    m_topRightViewport.Draw();
    m_bottomLeftViewport.Draw();
    m_bottomRightViewport.Draw();

    // execute command list
    m_pd3d12CommandQueue->ExecuteCommandLists(static_cast<UINT>(m_graphicsCommandListVector.size()),
                                              reinterpret_cast<ID3D12CommandList* const*>(m_graphicsCommandListVector.data()));

    // present frame
    m_pdxgiSwapChain3->Present(1, 0);
    WaitForGpuToFinish();

    m_pipelineStateChanged = false;
}

void CubeSample::Destroy()
{
    while (!m_appCreatedIUnknown.empty())
    {
        IUnknownNamePair d3d12ObjectNamePair = m_appCreatedIUnknown.top();
        IUnknown*        pUnknown            = d3d12ObjectNamePair.second;

        if (nullptr != pUnknown)
        {
            ULONG refCount = pUnknown->Release();
            UNREFERENCED_PARAMETER(refCount);
            m_appCreatedIUnknown.pop();
        }
    }
}

void CubeSample::ToggleProfiling()
{
    m_profilingEnable = !m_profilingEnable;
}

void CubeSample::ToggleWireFrame()
{
    m_wireframe = !m_wireframe;
}

void CubeSample::ResetGpaPassInfo()
{
    m_sampleCounter = -1;
    m_topLeftViewport.ResetForNextPass();
    m_topRightViewport.ResetForNextPass();
    m_bottomLeftViewport.ResetForNextPass();
    m_bottomRightViewport.ResetForNextPass();
}

#pragma region GPA_Wrappers

bool CubeSample::GPA_InitializeAndOpenContext()
{
    bool success = true;

    m_profilingEnable = args.m_useGPA;

    std::remove(m_gpaLogFileName.c_str());

    if (m_profilingEnable)
    {
        if (nullptr == m_pGpaFunctionTable)
        {
            if (GPA_STATUS_OK == GPAApiManager::Instance()->LoadApi(GPA_API_DIRECTX_12))
            {
                m_pGpaFunctionTable = GPAApiManager::Instance()->GetFunctionTable(GPA_API_DIRECTX_12);
            }
            else
            {
                LogGPA(GPA_LOGGING_ALL, "Unable to load GPA");
            }
        }

        if (nullptr != m_pGpaFunctionTable)
        {
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_Initialize(GPA_INITIALIZE_DEFAULT_BIT);
            success = success && GPA_STATUS_OK == m_pGpaFunctionTable->GPA_RegisterLoggingCallback(GPA_LOGGING_ERROR, LogGPA);

            GPA_OpenContextFlags openContextFlags = args.m_includeHwCounters ? GPA_OPENCONTEXT_ENABLE_HARDWARE_COUNTERS_BIT : GPA_OPENCONTEXT_DEFAULT_BIT;
            success = success && GPA_STATUS_OK == m_pGpaFunctionTable->GPA_OpenContext(m_pd3d12Device, openContextFlags, &m_gpaContextId);
            success = success && GPA_STATUS_OK == m_pGpaFunctionTable->GPA_GetDeviceAndRevisionId(m_gpaContextId, &m_deviceId, &m_revisionId);

            char        tempDeviceName[255]{};
            const char* pTempDeviceName = tempDeviceName;

            success = success && GPA_STATUS_OK == m_pGpaFunctionTable->GPA_GetDeviceName(m_gpaContextId, &pTempDeviceName);
            if (success)
            {
                m_deviceName = pTempDeviceName;
            }

            std::remove(m_counterFileName.c_str());
            m_counterDataFileStream.open(m_counterFileName.c_str(), std::ios_base::out | std::ios_base::app);
        }
    }

    return success;
}

bool CubeSample::GPA_ReleaseContextAndDestroy()
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable)
    {
        if (m_gpaContextId)
        {
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_CloseContext(m_gpaContextId);
            success = success && GPA_STATUS_OK == m_pGpaFunctionTable->GPA_Destroy();
            GPAApiManager::Instance()->UnloadApi(GPA_API_DIRECTX_12);

            if (m_gpaLogFileStream.is_open())
            {
                m_gpaLogFileStream.close();
            }

            m_counterDataFileStream.close();
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GPA_EnableCounters()
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        if (nullptr != m_gpaSessionId)
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
                        m_pGpaFunctionTable->GPA_EnableCounterByName(m_gpaSessionId, it->c_str());
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
                success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_EnableAllCounters(m_gpaSessionId);
#else
                success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_EnableCounterByName(m_gpaSessionId, "GPUTime");
#endif
            }

            success = success && GPA_STATUS_OK == m_pGpaFunctionTable->GPA_GetPassCount(m_gpaSessionId, &m_passRequired);
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GPA_CreateProfilingSession()
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        if (nullptr != m_gpaContextId)
        {
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_CreateSession(m_gpaContextId, GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER, &m_gpaSessionId);
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GPA_BeginProfilingSession()
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        if (nullptr != m_gpaSessionId)
        {
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_BeginSession(m_gpaSessionId);

            if (success)
            {
                m_sampleCounter = -1;
                m_currentPass   = -1;
            }
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GPA_EndProfilingSession() const
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        if (nullptr != m_gpaSessionId)
        {
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_EndSession(m_gpaSessionId);
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GPA_BeginPass()
{
    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        m_currentPass++;
    }

    return true;
}

bool CubeSample::GPA_EndPass()
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable && nullptr != m_gpaSessionId)
    {
        bool           isReady   = false;
        const uint32_t timeout   = 10000;  // ms
        auto           startTime = std::chrono::high_resolution_clock::now();

        do
        {
            isReady = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_IsPassComplete(m_gpaSessionId, m_currentPass);

            if (!isReady)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(0));

                auto                                      endTime     = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

                if (elapsedTime.count() > timeout)
                {
                    LogGPA(GPA_LOGGING_ERROR, "GPA_IsPassComplete failed due to elapsed timeout.");
                    success = false;
                    break;
                }
            }
        } while (!isReady);

        ResetGpaPassInfo();
    }

    return success;
}

bool CubeSample::GPA_NextPassNeeded() const
{
    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        return static_cast<unsigned int>(m_currentPass + 1) < m_passRequired;
    }

    return false;
}

bool CubeSample::GPA_DeleteProfilingSession()
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable && nullptr != m_gpaSessionId)
    {
        if (nullptr != m_gpaContextId)
        {
            success        = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_DeleteSession(m_gpaSessionId);
            m_gpaSessionId = nullptr;
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GPA_BeginCommandListForSampling(ID3D12GraphicsCommandList* pGraphicsCmdList, GPA_CommandListId& gpaCmdId) const
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        if (nullptr != m_gpaSessionId)
        {
            GPA_Command_List_Type cmdType =
                pGraphicsCmdList->GetType() == D3D12_COMMAND_LIST_TYPE_DIRECT ? GPA_COMMAND_LIST_PRIMARY : GPA_COMMAND_LIST_SECONDARY;
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_BeginCommandList(m_gpaSessionId, m_currentPass, pGraphicsCmdList, cmdType, &gpaCmdId);

            if (!success)
            {
                gpaCmdId = nullptr;
            }
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GPA_EndCommandListForSampling(GPA_CommandListId& gpaCmdListId) const
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        if (nullptr != gpaCmdListId)
        {
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_EndCommandList(gpaCmdListId);
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool CubeSample::GPA_BeginSample(GPA_CommandListId gpaCmdListId, const unsigned int& sampleId) const
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_BeginSample(sampleId, gpaCmdListId);
    }
    else
    {
        success = false;
    }

    return success;
}

bool CubeSample::GPA_EndSample(GPA_CommandListId gpaCmdListId) const
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_EndSample(gpaCmdListId);
    }
    else
    {
        success = false;
    }

    return success;
}

bool CubeSample::GPA_CopyBundleSample(GPA_CommandListId pSecondaryGpaCmdList, GPA_CommandListId pPrimaryGpaCmdList, std::vector<gpa_uint32> sampleIdList) const
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        if (nullptr != pSecondaryGpaCmdList && nullptr != pPrimaryGpaCmdList)
        {
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_CopySecondarySamples(
                                           pSecondaryGpaCmdList, pPrimaryGpaCmdList, static_cast<gpa_uint32>(sampleIdList.size()), sampleIdList.data());
        }
    }

    return success;
}

bool CubeSample::GPA_ContinueSample(unsigned int srcSampleId, GPA_CommandListId gpaCmdId) const
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        if (nullptr != gpaCmdId)
        {
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_ContinueSampleOnCommandList(srcSampleId, gpaCmdId);
        }
    }

    return success;
}

bool CubeSample::GPA_CounterValueCompare(unsigned int frameNumber,
                                         unsigned int sampleIndex,
                                         const char*  pCounterName,
                                         gpa_float64  counterValue,
                                         CompareType  compareType,
                                         gpa_float64  compareVal)
{
    bool              retVal = false;
    std::stringstream errorString;

    errorString << "Incorrect value for counter " << pCounterName << "(sample " << sampleIndex << " in frame " << frameNumber << "). Counter value is "
                << counterValue << ". Expected counter to be ";

    switch (compareType)
    {
    case COMPARE_TYPE_EQUAL:
        retVal = counterValue == compareVal;
        errorString << "equal to " << compareVal;
        break;

    case COMPARE_TYPE_GREATER_THAN:
        retVal = counterValue > compareVal;
        errorString << "greater than " << compareVal;
        break;

    case COMPARE_TYPE_GREATER_THAN_OR_EQUAL_TO:
        retVal = counterValue >= compareVal;
        errorString << "greater than or equal to " << compareVal;
        break;

    case COMPARE_TYPE_LESS_THAN:
        retVal = counterValue < compareVal;
        errorString << "less than " << compareVal;
        break;

    case COMPARE_TYPE_LESS_THAN_OR_EQUAL_TO:
        retVal = counterValue <= compareVal;
        errorString << "less than or equal to " << compareVal;
        break;
    }

    if (!retVal)
    {
        GPA_Log(GPA_LOGGING_ERROR, errorString.str().c_str());
    }

    return retVal;
}

bool CubeSample::GPA_ValidateData(unsigned int   frameNumber,
                                  unsigned int   sampleIndex,
                                  const char*    pCounterName,
                                  gpa_float64    counterValue,
                                  GPA_Usage_Type counterUsageType)
{
    bool retVal = true;

    std::string counterName(pCounterName);

    if (GPA_USAGE_TYPE_PERCENTAGE == counterUsageType)
    {
        retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN_OR_EQUAL_TO, 0.0f) &&
                 GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_LESS_THAN_OR_EQUAL_TO, 100.0f);
    }

    if (retVal)
    {
        if (0 == counterName.compare("GPUTime"))
        {
            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f);
        }
        else if (0 == counterName.compare("GPUBusy"))
        {
            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f);
        }
        /* temporarily disable additional counter validation
        else if (0 == counterName.compare("VSBusy"))
        {
            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f);
        }
        else if (0 == counterName.compare("VSTime"))
        {
            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f);
        }
        else if (0 == counterName.compare("PSBusy"))
        {
            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f);
        }
        else if (0 == counterName.compare("PSTime"))
        {
            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f);
        }
        else if (0 == counterName.compare("VSVerticesIn"))
        {
            gpa_float64 expectedVsVerticesIn = 9;

            if (1 == sampleIndex)
            {
                expectedVsVerticesIn = 154;
            }

            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_EQUAL, expectedVsVerticesIn);
        }
        else if (0 == counterName.compare("PSPixelsOut"))
        {
            gpa_float64 expectedPsPixelsOut = 200000;

            if (1 == sampleIndex)
            {
                expectedPsPixelsOut = 1080000;
            }

            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_EQUAL, expectedPsPixelsOut);
        }
        else if (0 == counterName.compare("PrimitivesIn"))
        {
            gpa_float64 expectedPrimiteivesIn = 12;

            if (1 == sampleIndex)
            {
                expectedPrimiteivesIn = 114;
            }

            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_EQUAL, expectedPrimiteivesIn);
        }
        */
    }

    return retVal;
}

bool CubeSample::GPA_PopulateSessionResult()
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable && nullptr != m_gpaSessionId)
    {
        bool           isReady   = false;
        const uint32_t timeout   = 10000;  // ms
        auto           startTime = std::chrono::high_resolution_clock::now();

        do
        {
            isReady = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_IsSessionComplete(m_gpaSessionId);

            if (!isReady)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(0));

                auto                                      endTime     = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

                if (elapsedTime.count() > timeout)
                {
                    break;
                }
            }
        } while (!isReady);

        size_t m_sampleDataSize = 0u;
        auto   status           = m_pGpaFunctionTable->GPA_GetSampleResultSize(m_gpaSessionId, 0, &m_sampleDataSize);
        UNREFERENCED_PARAMETER(status);

        void* pSampleResult = malloc(m_sampleDataSize);
        if (nullptr == pSampleResult)
        {
            return false;
        }

        memset(pSampleResult, 0, m_sampleDataSize / sizeof(int));

        std::stringstream counterNamesHeader;
        std::string       viewport;
        bool              counterNameCollected = false;
        std::string       wireFrame            = ms_pCubeSample->m_wireframe ? "Yes" : "No";

        auto CollectSampleResult = [&](unsigned int sampleIndex) {
            m_content << m_frameCounter << "," << wireFrame << "," << viewport << "," << sampleIndex;
            status                    = m_pGpaFunctionTable->GPA_GetSampleResult(m_gpaSessionId, sampleIndex, m_sampleDataSize, pSampleResult);
            unsigned int counterIndex = 0;

            gpa_uint32 enabledCount = 0;
            status                  = m_pGpaFunctionTable->GPA_GetNumEnabledCounters(m_gpaSessionId, &enabledCount);

            for (gpa_uint32 i = 0; i < enabledCount; i++)
            {
                gpa_uint32 enabledIndex = 0;
                status                  = m_pGpaFunctionTable->GPA_GetEnabledIndex(m_gpaSessionId, i, &enabledIndex);

                const char* pCounterName;
                status = m_pGpaFunctionTable->GPA_GetCounterName(m_gpaContextId, enabledIndex, &pCounterName);

                if (!counterNameCollected)
                {
                    counterNamesHeader << "," << pCounterName;
                }

                GPA_Data_Type counterDataType;
                status = m_pGpaFunctionTable->GPA_GetCounterDataType(m_gpaContextId, enabledIndex, &counterDataType);

                GPA_Usage_Type counterUsageType;
                status = m_pGpaFunctionTable->GPA_GetCounterUsageType(m_gpaContextId, enabledIndex, &counterUsageType);

                if (GPA_DATA_TYPE_FLOAT64 == counterDataType)
                {
                    gpa_float64 result = *(reinterpret_cast<gpa_float64*>(pSampleResult) + counterIndex);

                    m_content << "," << std::fixed << (counterUsageType == GPA_USAGE_TYPE_PERCENTAGE ? std::setprecision(4) : std::setprecision(0)) << result;

                    if (args.m_verifyCounters)
                    {
                        GPA_ValidateData(m_frameCounter, sampleIndex, pCounterName, result, counterUsageType);
                    }
                }
                else if (GPA_DATA_TYPE_UINT64 == counterDataType)
                {
                    gpa_uint64 result = *(reinterpret_cast<gpa_uint64*>(pSampleResult) + counterIndex);

                    m_content << "," << result;

                    if (args.m_verifyCounters)
                    {
                        GPA_ValidateData(m_frameCounter, sampleIndex, pCounterName, static_cast<gpa_float64>(result), counterUsageType);
                    }
                }

                counterIndex++;
            }

            m_content << std::endl;
            counterNameCollected = true;
        };

        viewport = "TopLeft";
        m_topLeftViewport.IterateSamples(CollectSampleResult);

        viewport = "TopRight";
        m_topRightViewport.IterateSamples(CollectSampleResult);

        viewport = "BottomLeft";
        m_bottomLeftViewport.IterateSamples(CollectSampleResult);

        viewport = "BottomRight";
        m_bottomRightViewport.IterateSamples(CollectSampleResult);

        if (m_counterDataFileStream.is_open())
        {
            if (!m_isHeaderWritten)
            {
                m_header << "Device Id: " << std::hex << m_deviceId << std::endl;
                m_header << "Revision Id: " << std::hex << m_revisionId << std::endl;
                m_header << "Device Name: " << m_deviceName.c_str() << std::endl;
                m_header << "Frame"
                         << ","
                         << "Wireframe"
                         << ","
                         << "Viewport"
                         << ","
                         << "Sample";
                m_counterDataFileStream << m_header.str() << counterNamesHeader.str() << std::endl;
                m_isHeaderWritten = true;
            }

            m_counterDataFileStream << m_content.str() << std::endl;
            m_content.str(std::string());
            m_header.str(std::string());
        }

        free(pSampleResult);
    }

    return success;
}

bool CubeSample::GPA_Log(GPA_Logging_Type loggingType, const char* logMessage)
{
    if (GPA_LOGGING_ERROR == loggingType)
    {
        g_anyGPAErrorsLogged = true;
    }

    if (!m_gpaLogFileStream.is_open())
    {
        m_gpaLogFileStream.open(m_gpaLogFileName.c_str(), std::ios_base::out | std::ios_base::app);
    }

    m_gpaLogFileStream << logMessage << std::endl;
    return true;
}

#pragma endregion
