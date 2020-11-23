//==============================================================================
// Copyright (c) 2019-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  D3D11 Triangle Sample
//==============================================================================

#include "dx11_triangle.h"
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

#include "..\Sample.h"


unsigned int      g_windowWidth                    = 800;
unsigned int      g_windowHeight                   = 800;
std::wstring      g_windowClassName                = L"D3D11 Triangle Sample";
HWND              g_windowHandle                   = nullptr;
D3D11Triangle*    D3D11Triangle::ms_pDx11Triangle  = nullptr;
GPAApiManager*    GPAApiManager::m_pGpaApiManager  = nullptr;
GPAFuncTableInfo* g_pFuncTableInfo                 = nullptr;

bool g_anyGPAErrorsLogged = false;  ///< flag indicating if any GPA errors have been logged

void LogGPA(GPA_Logging_Type loggingType, const char* logMessage)
{
    D3D11Triangle::Instance()->GPA_Log(loggingType, logMessage);
}

#define MAKE_STRING(X) #X

LRESULT CALLBACK SampleWindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    static unsigned int paintCount = 0;

    switch (uMsg)
    {
    case WM_SHOWWINDOW: {
        // Initialize app here
        if(!D3D11Triangle::Instance()->Init())
        {
            exit(-1);
        }

        if (args.m_useGPA)
        {
            bool gpaOk = D3D11Triangle::Instance()->GPA_InitializeAndOpenContext();

            if (!gpaOk)
            {
                PostQuitMessage(-1);
            }
        }

        return 0;
    }

    case WM_PAINT: {
        bool sessionCreated = D3D11Triangle::Instance()->GPA_CreateProfilingSession();
        bool sessionStarted = false;

        if (sessionCreated)
        {
            if (D3D11Triangle::Instance()->GPA_EnableCounters())
            {
                sessionStarted = D3D11Triangle::Instance()->GPA_BeginProfilingSession();
            }
            else
            {
                D3D11Triangle::Instance()->GPA_DeleteProfilingSession();
            }
        }

        do
        {
            bool passStarted = false;

            if (sessionStarted)
            {
                passStarted = D3D11Triangle::Instance()->GPA_BeginPass();
                D3D11Triangle::Instance()->GPA_BeginSample();
            }

            D3D11Triangle::Instance()->Draw();  // draw the triangle

            if (passStarted)
            {
                D3D11Triangle::Instance()->GPA_EndSample();
                D3D11Triangle::Instance()->GPA_EndPass();
            }
        } while (D3D11Triangle::Instance()->GPA_NextPassNeeded());

        bool sessionEnded = false;

        if (sessionStarted)
        {
            sessionEnded = D3D11Triangle::Instance()->GPA_EndProfilingSession();
        }

        if (sessionEnded)
        {
            D3D11Triangle::Instance()->GPA_PopulateSessionResult();

            if (sessionCreated)
            {
                D3D11Triangle::Instance()->GPA_DeleteProfilingSession();
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
            D3D11Triangle::Instance()->GPA_ReleaseContextAndDestroy();
        }

        D3D11Triangle::Instance()->Destroy();

        PostQuitMessage(0);
        return 0;

    case WM_KEYDOWN: {
        switch (wParam)
        {
        case 0x50:  // keyboard P for profiling
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
    if (nullptr == ms_pDx11Triangle)
    {
        ms_pDx11Triangle = new (std::nothrow) D3D11Triangle();
    }

    return ms_pDx11Triangle;
}

D3D11Triangle::D3D11Triangle()
    : m_pDx11Device(nullptr)
    , m_pDx11ImmediateContext(nullptr)
    , m_pdxgiFactory1(nullptr)
    , m_pdxgiSwapChain(nullptr)
    , m_pVertexBuffer(nullptr)
    , m_pVertexShader(nullptr)
    , m_pPixelShader(nullptr)
    , m_pRTV(nullptr)
    , m_pdx11InputLayout(nullptr)
    , m_pDepthStencilState(nullptr)
    , m_pRasterizerState(nullptr)
    , m_viewPort()
    , m_frameCounter(0u)
    , m_isHeaderWritten(false)
    , m_pGpaFunctionTable(nullptr)
    , m_gpaContextId(nullptr)
    , m_gpaSessionId(nullptr)
    , m_gpaCommandListId(nullptr)
    , m_deviceId(0)
    , m_revisionId(0)
    , m_passRequired(0u)
    , m_currentPass(-1)
    , m_sampleCounter(-1)
    , m_profilingEnable(true)
{
}

bool D3D11Triangle::Init()
{
    std::vector<char> modulepath(_MAX_PATH);

    ::GetModuleFileNameA(0, modulepath.data(), static_cast<DWORD>(modulepath.size()));

    std::string pathOnly(modulepath.data());

    m_executablePath = pathOnly.substr(0, pathOnly.find_last_of('\\') + 1);

    m_counterFileName = m_executablePath + "DX11Triangle_counterData.csv";
    m_gpaLogFileName  = m_executablePath + "DX11Triangle_gpaLog.txt";

    // DX11 Initialization

    HRESULT result           = S_OK;

    result = CreateDXGIFactory1(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&m_pdxgiFactory1));

    if (FAILED(result))
    {
        return false;
    }

    unsigned int                adapterCount = 0;
    std::vector<IDXGIAdapter1*> dxgiAdapters;
    IDXGIAdapter1*              pdxgiAdapter1 = nullptr;

    // description flag is only available in type IDXGIAdapter1 and later
    while (SUCCEEDED(m_pdxgiFactory1->EnumAdapters1(adapterCount, &pdxgiAdapter1)))
    {
        DXGI_ADAPTER_DESC1 adapterDesc1;
        pdxgiAdapter1->GetDesc1(&adapterDesc1);

        if (!(adapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE))
        {
            dxgiAdapters.push_back(pdxgiAdapter1);
        }

        adapterCount++;
        pdxgiAdapter1 = nullptr;
    }

    if (!dxgiAdapters.empty())
    {
        pdxgiAdapter1 = dxgiAdapters.at(0);

        D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_11_1};
        D3D_FEATURE_LEVEL    featureLevelSupported;

        result = D3D11CreateDevice(pdxgiAdapter1,
                                   D3D_DRIVER_TYPE_UNKNOWN,
                                   nullptr,
                                   D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS,
                                   featureLevels,
                                   _countof(featureLevels),
                                   D3D11_SDK_VERSION,
                                   &m_pDx11Device,
                                   &featureLevelSupported,
                                   &m_pDx11ImmediateContext);

        if (FAILED(result))
        {
            return false;
        }

        DXGI_MODE_DESC modesDesc            = {};
        modesDesc.Width                     = static_cast<UINT>(g_windowWidth);
        modesDesc.Height                    = static_cast<UINT>(g_windowHeight);
        modesDesc.RefreshRate.Numerator     = 60; // 60 Hz
        modesDesc.RefreshRate.Denominator   = 1;
        modesDesc.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
        modesDesc.ScanlineOrdering          = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        modesDesc.Scaling                   = DXGI_MODE_SCALING_UNSPECIFIED;

        DXGI_SWAP_CHAIN_DESC swapChainDesc  = {};
        swapChainDesc.BufferDesc            = modesDesc;
        swapChainDesc.SampleDesc.Count      = 1;
        swapChainDesc.SampleDesc.Quality    = 0;  // Irrelevant
        swapChainDesc.BufferUsage           = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount           = ms_frameCount;
        swapChainDesc.OutputWindow          = g_windowHandle;
        swapChainDesc.Windowed              = TRUE;
        swapChainDesc.SwapEffect            = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDesc.Flags                 = NULL;

        result = m_pdxgiFactory1->CreateSwapChain(m_pDx11Device, &swapChainDesc, &m_pdxgiSwapChain);

        if (FAILED(result))
        {
            return false;
        }

        // Create RTV with swap chain back buffer
        ID3D11Texture2D* pRTVTexture = nullptr;
        result                       = m_pdxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pRTVTexture));

        if (FAILED(result))
        {
            return false;
        }

        result = m_pDx11Device->CreateRenderTargetView(pRTVTexture, nullptr, &m_pRTV);

        if (FAILED(result))
        {
            return false;
        }

        // Init vertex data and create vertex buffer
        VertexData vertexColorData[] = {
            {{0.0f, 0.75f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},     // 0
            {{-0.75f, -0.75f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},  // 1
            {{0.75f, -0.75f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},   // 2
        };

        D3D11_BUFFER_DESC vertexBufferDesc;
        vertexBufferDesc.Usage          = D3D11_USAGE_DEFAULT;
        vertexBufferDesc.ByteWidth      = sizeof(VertexData) * 3;
        vertexBufferDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.CPUAccessFlags = 0;
        vertexBufferDesc.MiscFlags      = 0;

        D3D11_SUBRESOURCE_DATA vertexInitData;
        vertexInitData.pSysMem      = vertexColorData;

        result = m_pDx11Device->CreateBuffer(&vertexBufferDesc, &vertexInitData, &m_pVertexBuffer);

        if (FAILED(result))
        {
            return false;
        }

        ID3DBlob* pVertexShaderBlob = nullptr;
        ID3DBlob* pPixelShaderBlob  = nullptr;
        ID3DBlob* pError        = nullptr;

        UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wideToUtf8Converter;

        std::wstring shaderPath = wideToUtf8Converter.from_bytes(m_executablePath);
        shaderPath.append(L"dx11_triangle_shaders.hlsl");

        std::ifstream shader_file(shaderPath.c_str());
        if (!shader_file.good())
        {
            LogGPA(GPA_LOGGING_ERROR, "Unable to load shader file.");
            return false;
        }

        result = D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &pVertexShaderBlob, &pError);

        if (FAILED(result))
        {
            return false;
        }

        result = m_pDx11Device->CreateVertexShader(pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), nullptr, &m_pVertexShader);

        if (FAILED(result))
        {
            return false;
        }

        result = D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pPixelShaderBlob, &pError);

        if (FAILED(result))
        {
            return false;
        }

        result = m_pDx11Device->CreatePixelShader(pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), nullptr, &m_pPixelShader);

        if (FAILED(result))
        {
            return false;
        }

        // Create input layout
        D3D11_INPUT_ELEMENT_DESC iaLayout[2];

        // vertex position data
        iaLayout[0].SemanticName         = "SCREEN_POSITION";
        iaLayout[0].SemanticIndex        = 0;
        iaLayout[0].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
        iaLayout[0].InputSlot            = 0;
        iaLayout[0].AlignedByteOffset    = 0;
        iaLayout[0].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
        iaLayout[0].InstanceDataStepRate = 0;

        // vertex color data
        iaLayout[1].SemanticName         = "VERTEX_COLOR";
        iaLayout[1].SemanticIndex        = 0;
        iaLayout[1].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
        iaLayout[1].InputSlot            = 0;
        iaLayout[1].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
        iaLayout[1].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
        iaLayout[1].InstanceDataStepRate = 0;

        result = m_pDx11Device->CreateInputLayout(iaLayout, 2, pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), &m_pdx11InputLayout);

        if (FAILED(result))
        {
            return false;
        }

        /*D3D11 runtime needs all the data for D3D11_DEPTH_STENCIL_DESC to
         * be filled even depth and stencil are disabled*/
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
        depthStencilDesc.DepthEnable = false;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
        depthStencilDesc.DepthFunc      = D3D11_COMPARISON_NEVER;
        depthStencilDesc.StencilEnable = false;
        depthStencilDesc.StencilReadMask = 0;
        depthStencilDesc.StencilWriteMask = 0;
        depthStencilDesc.FrontFace        = {};
        depthStencilDesc.BackFace         = {};

        result = m_pDx11Device->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState);

        if (FAILED(result))
        {
            return false;
        }

        D3D11_RASTERIZER_DESC d3d11RasterizerDesc = {};
        d3d11RasterizerDesc.FillMode = D3D11_FILL_SOLID;
        d3d11RasterizerDesc.CullMode = D3D11_CULL_NONE;

        result = m_pDx11Device->CreateRasterizerState(&d3d11RasterizerDesc, &m_pRasterizerState);

        if (FAILED(result))
        {
            return false;
        }

        m_viewPort.Width    = static_cast<float>(g_windowWidth);
        m_viewPort.Height   = static_cast<float>(g_windowHeight);
        m_viewPort.MaxDepth = 1.0f;
        m_viewPort.MinDepth = 0.0f;
        m_viewPort.TopLeftX = 0.0f;
        m_viewPort.TopLeftY = 0.0f;
    }

    return true;
}

void D3D11Triangle::Draw()
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

    UINT stride = sizeof(VertexData);
    UINT bufferOffset = 0;

    m_pDx11ImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &bufferOffset);
    m_pDx11ImmediateContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pDx11ImmediateContext->IASetInputLayout(m_pdx11InputLayout);
    m_pDx11ImmediateContext->VSSetShader(m_pVertexShader, nullptr, 0);
    m_pDx11ImmediateContext->RSSetState(m_pRasterizerState);
    m_pDx11ImmediateContext->RSSetViewports(1, &m_viewPort);
    m_pDx11ImmediateContext->PSSetShader(m_pPixelShader, nullptr, 0);
    m_pDx11ImmediateContext->OMSetDepthStencilState(m_pDepthStencilState, NULL);
    m_pDx11ImmediateContext->OMSetRenderTargets(1, &m_pRTV, nullptr);
    m_pDx11ImmediateContext->Draw(3, 0);
    m_pdxgiSwapChain->Present(1, 0);
}

void D3D11Triangle::ToggleProfiling()
{
    m_profilingEnable = !m_profilingEnable;
}

#define SAFE_RELEASE(X) \
    if (nullptr != (X)) \
    {                   \
        (X)->Release(); \
    }

void D3D11Triangle::Destroy() const
{
    SAFE_RELEASE(m_pRasterizerState);
    SAFE_RELEASE(m_pDepthStencilState);
    SAFE_RELEASE(m_pdx11InputLayout);
    SAFE_RELEASE(m_pRTV);
    SAFE_RELEASE(m_pPixelShader);
    SAFE_RELEASE(m_pVertexShader);
    SAFE_RELEASE(m_pVertexBuffer);
    SAFE_RELEASE(m_pdxgiSwapChain);
    SAFE_RELEASE(m_pdxgiFactory1);
    SAFE_RELEASE(m_pDx11ImmediateContext);
    SAFE_RELEASE(m_pDx11Device);
}

void D3D11Triangle::ResetGpaPassInfo()
{
    m_sampleCounter = -1;
}

#pragma region GPA_Wrappers

bool D3D11Triangle::GPA_InitializeAndOpenContext()
{
    bool success = true;

    m_profilingEnable = args.m_useGPA;

    std::remove(m_gpaLogFileName.c_str());

    if (m_profilingEnable)
    {
        if (nullptr == m_pGpaFunctionTable)
        {
            if (GPA_STATUS_OK == GPAApiManager::Instance()->LoadApi(GPA_API_DIRECTX_11))
            {
                m_pGpaFunctionTable = GPAApiManager::Instance()->GetFunctionTable(GPA_API_DIRECTX_11);
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
            success = success && GPA_STATUS_OK == m_pGpaFunctionTable->GPA_OpenContext(m_pDx11Device, openContextFlags, &m_gpaContextId);
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

bool D3D11Triangle::GPA_ReleaseContextAndDestroy()
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable)
    {
        if (m_gpaContextId)
        {
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_CloseContext(m_gpaContextId);
            success = success && GPA_STATUS_OK == m_pGpaFunctionTable->GPA_Destroy();
            GPAApiManager::Instance()->UnloadApi(GPA_API_DIRECTX_11);

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

bool D3D11Triangle::GPA_EnableCounters()
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

bool D3D11Triangle::GPA_CreateProfilingSession()
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

bool D3D11Triangle::GPA_BeginProfilingSession()
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
                m_sampleList.clear();
            }
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool D3D11Triangle::GPA_EndProfilingSession() const
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

bool D3D11Triangle::GPA_BeginPass()
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        m_currentPass++;
    }

    if (nullptr == m_gpaCommandListId)
    {
        GPA_Status status =
            m_pGpaFunctionTable->GPA_BeginCommandList(m_gpaSessionId, m_currentPass, GPA_NULL_COMMAND_LIST, GPA_COMMAND_LIST_NONE, &m_gpaCommandListId);

        success = GPA_STATUS_OK == status;
    }

    return success;
}

bool D3D11Triangle::GPA_EndPass()
{
    bool success = true;

    if (nullptr != m_pGpaFunctionTable && m_profilingEnable && nullptr != m_gpaSessionId && nullptr != m_gpaCommandListId)
    {

        success                  = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_EndCommandList(m_gpaCommandListId);

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
        m_gpaCommandListId = nullptr;
    }

    return success;
}

bool D3D11Triangle::GPA_NextPassNeeded() const
{
    if (nullptr != m_pGpaFunctionTable && m_profilingEnable)
    {
        return static_cast<unsigned int>(m_currentPass + 1) < m_passRequired;
    }

    return false;
}

bool D3D11Triangle::GPA_DeleteProfilingSession()
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

bool D3D11Triangle::GPA_BeginSample()
{
    bool success = true;

    if (m_profilingEnable)
    {
        if (nullptr != m_pGpaFunctionTable && nullptr != m_gpaCommandListId)
        {
            m_sampleCounter++;
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_BeginSample(m_sampleCounter, m_gpaCommandListId);

            if (success && m_currentPass == 0)
            {
                m_sampleList.push_back(m_sampleCounter);
            }
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool D3D11Triangle::GPA_EndSample()
{
    bool success = true;

    if (m_profilingEnable)
    {
        if (nullptr != m_pGpaFunctionTable && nullptr != m_gpaCommandListId)
        {
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_EndSample(m_gpaCommandListId);
        }
        else
        {
            success = false;
        }
    }

    return success;
}

bool D3D11Triangle::GPA_CounterValueCompare(unsigned int frameNumber,
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

bool D3D11Triangle::GPA_ValidateData(unsigned int   frameNumber,
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
            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_EQUAL, 3);
        }
        else if (0 == counterName.compare("PSPixelsOut"))
        {
            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_EQUAL, 180000);
        }
        else if (0 == counterName.compare("PrimitivesIn"))
        {
            retVal = GPA_CounterValueCompare(frameNumber, sampleIndex, pCounterName, counterValue, COMPARE_TYPE_EQUAL, 1);
        }
    }

    return retVal;
}

bool D3D11Triangle::GPA_PopulateSessionResult()
{
    bool success = true;

    if (m_profilingEnable)
    {
        if (nullptr != m_pGpaFunctionTable && nullptr != m_gpaSessionId)
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
            bool              counterNameCollected = false;

            gpa_uint32 sampleCount;
            success = GPA_STATUS_OK == m_pGpaFunctionTable->GPA_GetSampleCount(m_gpaSessionId, &sampleCount);

            auto CollectSampleResult = [&](unsigned int sampleIndex) {
                m_content << m_frameCounter << "," << sampleIndex;
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

                        m_content << "," << std::fixed << (counterUsageType == GPA_USAGE_TYPE_PERCENTAGE ? std::setprecision(4) : std::setprecision(0))
                                  << result;

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

                counterNameCollected = true;
            };

            if (success && sampleCount == m_sampleList.size())
            {
                for (auto iter = m_sampleList.cbegin(); iter != m_sampleList.cend(); ++iter)
                {
                    CollectSampleResult(*iter);
                }
            }

            if (m_counterDataFileStream.is_open())
            {
                if (!m_isHeaderWritten)
                {
                    m_header << "Device Id: " << std::hex << m_deviceId << std::endl;
                    m_header << "Revision Id: " << std::hex << m_revisionId << std::endl;
                    m_header << "Device Name: " << m_deviceName.c_str() << std::endl;
                    m_header << "Frame"
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
    }

    return success;
}

bool D3D11Triangle::GPA_Log(GPA_Logging_Type loggingType, const char* logMessage)
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
