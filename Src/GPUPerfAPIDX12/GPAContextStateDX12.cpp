//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA_ContextStateDX12 implementation
//==============================================================================

#include "GPAContextStateDX12.h"
#include "IGPASession.h"
#include "Logging.h"
#include <cassert>

GPA_ContextStateDX12::GPA_ContextStateDX12()
    :
    m_device(nullptr),
    m_commandListQueries(),
    m_commandListGpaSession(),
    m_mutex(),
    m_pGpaInterface(nullptr),
    m_pAmdExtObject(nullptr)
{
}

GPA_ContextStateDX12::~GPA_ContextStateDX12()
{
    Cleanup();
}

void GPA_ContextStateDX12::Cleanup()
{
    if (GPA_STATUS_OK != SetStableClocks(false))
    {
        GPA_LogError("Unable to restore GPU clocks.");
    }

    // TODO: is it sufficient to destroy all sessions here or do we need a way to
    //       explicitly destroy sessions when we know we're done with them (i.e.
    //       after we gather all results from a session)
    for (auto cmdListGpaSessionPair : m_commandListGpaSession)
    {
        m_pGpaInterface->DestroyGpaSession(cmdListGpaSessionPair.second);
    }

    m_commandListGpaSession.clear();

    if (nullptr != m_pGpaInterface)
    {
        m_pGpaInterface->Release();
        m_pGpaInterface = nullptr;
    }

    if (nullptr != m_pAmdExtObject)
    {
        m_pAmdExtObject->Release();
        m_pAmdExtObject = nullptr;
    }

    if (nullptr != m_device)
    {
        m_device = nullptr;
    }
}

GPA_Status GPA_ContextStateDX12::SetD3D12Device(ID3D12Device* pDevice, bool isAMDDevice)
{
    GPA_Status result = GPA_STATUS_OK;

    if (pDevice != m_device)
    {
        m_device = pDevice;

        if (nullptr == m_pGpaInterface && isAMDDevice)
        {
            result = GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;

            HMODULE hDll = nullptr;
#ifdef X64
            hDll = GetModuleHandle("amdxc64.dll");
#else
            hDll = GetModuleHandle("amdxc32.dll");
#endif

            if (nullptr == hDll)
            {
                GPA_LogError("Unable to get driver module handle.");
            }
            else
            {
                PFNAmdExtD3DCreateInterface pAmdExtD3dCreateFunc = reinterpret_cast<PFNAmdExtD3DCreateInterface>(GetProcAddress(hDll,
                                                                   "AmdExtD3DCreateInterface"));

                if (nullptr == pAmdExtD3dCreateFunc)
                {
                    GPA_LogError("Unable to get driver extension entry point.");
                }
                else
                {
                    HRESULT hr = pAmdExtD3dCreateFunc(m_device, __uuidof(IAmdExtD3DFactory), reinterpret_cast<void**>(&m_pAmdExtObject));

                    if (FAILED(hr))
                    {
                        GPA_LogError("Unable to get driver extension interface.");
                    }
                    else
                    {
                        hr = m_pAmdExtObject->CreateInterface(m_device,
                                                              __uuidof(IAmdExtGpaInterface),
                                                              reinterpret_cast<void**>(&m_pGpaInterface));

                        if (FAILED(hr))
                        {
                            const GUID prevDriverExtGuid = { 0xA86AE046, 0x9926, 0x44B5, { 0xB8, 0x23, 0x02, 0x2F, 0x45, 0x73, 0xBF, 0xE1} };
                            hr = m_pAmdExtObject->CreateInterface(m_device,
                                                                  prevDriverExtGuid,
                                                                  reinterpret_cast<void**>(&m_pGpaInterface));
                        }

                        if (FAILED(hr))
                        {
                            GPA_LogError("Unable to get driver GPA extension interface.");
                        }
                        else
                        {
                            hr = m_pGpaInterface->GetPerfExperimentProperties(&m_props);

                            if (FAILED(hr))
                            {
                                GPA_LogError("Unable to get current hardware perf experiment properties.");
                            }
                            else
                            {
                                if (0 == m_props.features.counters)
                                {
                                    GPA_LogError("Active GPU hardware does not support performance counters.");
                                    result = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                                }
                                else
                                {
                                    result = SetStableClocks(true);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

GPA_Status GPA_ContextStateDX12::GetTimestampFrequency(UINT64& timestampFrequency)
{
    GPA_Status result = GPA_STATUS_OK;

    ID3D12CommandQueue* pQueue = nullptr;
    D3D12_COMMAND_QUEUE_DESC queueDesc;
    ZeroMemory(&queueDesc, sizeof(queueDesc));
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    HRESULT hr = m_device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (PVOID*)&pQueue);

    if (FAILED(hr) || nullptr == pQueue)
    {
        result = GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        UINT64 frequency = 0;
        hr = pQueue->GetTimestampFrequency(&frequency);

        if (FAILED(hr))
        {
            result = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            timestampFrequency = frequency;
        }

        pQueue->Release();
    }

    return result;
}

GPA_Status GPA_ContextStateDX12::BeginCommandList(void* pCommandList)
{
    GPA_Status retVal = GPA_STATUS_OK;

    IUnknown* pUnknown = static_cast<IUnknown*>(pCommandList);
    ID3D12GraphicsCommandList* pD3DCommandList;
    HRESULT hr = pUnknown->QueryInterface(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void**>(&pD3DCommandList));
    bool result = SUCCEEDED(hr);

    if (result)
    {
        D3D12_COMMAND_LIST_TYPE cmdListType = pD3DCommandList->GetType();

        if (D3D12_COMMAND_LIST_TYPE_COPY == cmdListType)
        {
            GPA_LogError("D3D12_COMMAND_LIST_TYPE_COPY command lists not supported.");
            retVal = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            IAmdExtGpaSession* pGpaSession = nullptr;

            if (m_commandListGpaSession.end() == m_commandListGpaSession.find(pD3DCommandList))
            {
                if (nullptr != m_pGpaInterface)
                {
                    pGpaSession = m_pGpaInterface->CreateGpaSession();
                }
            }
            else
            {
                pGpaSession = m_commandListGpaSession[pD3DCommandList];

                IGPASession* pSessionRequests = FindSession(m_sessionID);

                if (nullptr == pSessionRequests)
                {
                    GPA_LogError("Unable to find session requests.");
                    return GPA_STATUS_ERROR_NULL_POINTER;
                }

                // attempt to collect any outstanding results before resetting the Gpa Session
                if (pSessionRequests->IsComplete())
                {
                    hr = pGpaSession->Reset();

                    if (FAILED(hr))
                    {
                        GPA_LogError("Unable to reset GPA session.");
                        retVal = GPA_STATUS_ERROR_FAILED;
                    }
                }
                else
                {
                    GPA_LogError("Attempt to restart a command list while its previous results have not been collected.");
                    retVal = GPA_STATUS_ERROR_FAILED;
                }
            }

            if (nullptr == pGpaSession)
            {
                GPA_LogError("Unable to create GPA session.");
                retVal = GPA_STATUS_ERROR_NULL_POINTER;
            }
            else
            {
                m_commandListGpaSession[pD3DCommandList] = pGpaSession;

                hr = pGpaSession->Begin(pD3DCommandList);

                if (FAILED(hr))
                {
                    GPA_LogError("Unable to open command list for sampling.");
                    retVal = GPA_STATUS_ERROR_FAILED;
                }
            }
        }

        pD3DCommandList->Release();
    }
    else
    {
        GPA_LogError("Attempted to open an invalid command list for sampling.");
        retVal = GPA_STATUS_ERROR_FAILED;
    }

    return retVal;
}

GPA_Status GPA_ContextStateDX12::EndCommandList(void* pCommandList)
{
    GPA_Status retVal = GPA_STATUS_OK;

    IUnknown* pUnknown = static_cast<IUnknown*>(pCommandList);
    ID3D12GraphicsCommandList* pD3DCommandList;
    HRESULT hr = pUnknown->QueryInterface(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void**>(&pD3DCommandList));
    bool result = SUCCEEDED(hr);

    if (result)
    {
        IAmdExtGpaSession* pGpaSession = nullptr;

        if (m_commandListGpaSession.end() != m_commandListGpaSession.find(pD3DCommandList))
        {
            pGpaSession = m_commandListGpaSession[pD3DCommandList];

            if (nullptr == pGpaSession)
            {
                GPA_LogError("Make sure BeginCommandList is called before EndCommandList for this command list.");
                retVal = GPA_STATUS_ERROR_COMMAND_LIST_NOT_STARTED;
            }
            else
            {
                hr = pGpaSession->End(pD3DCommandList);

                if (FAILED(hr))
                {
                    GPA_LogError("Unable to end command list.");
                    retVal = GPA_STATUS_ERROR_FAILED;
                }
            }
        }
        else
        {
            GPA_LogError("Command List not open for sampling.");
            retVal = GPA_STATUS_ERROR_COMMAND_LIST_NOT_STARTED;
        }

        pD3DCommandList->Release();
    }

    return retVal;
}

bool GPA_ContextStateDX12::GetGpaSessionForCommandList(ID3D12GraphicsCommandList* pCommandList, IAmdExtGpaSession** pGpaSession)
{
    bool retVal = false;

    if (nullptr != pGpaSession)
    {
        if (m_commandListGpaSession.end() != m_commandListGpaSession.find(pCommandList))
        {
            *pGpaSession = m_commandListGpaSession[pCommandList];
            retVal = true;
        }
        else
        {
            *pGpaSession = nullptr;
            GPA_LogError("Unable to get extension object for specified command list.");
        }
    }
    else
    {
        GPA_LogError("Null extension pointer.");
    }

    return retVal;
}

bool GPA_ContextStateDX12::BeginSwSample(
    ID3D12GraphicsCommandListPtr& commandList, gpa_uint32& swSampleId)
{
    UNREFERENCED_PARAMETER(commandList);
    bool result = (nullptr != commandList.GetInterfacePtr());
    CommandListQueriesType::iterator cmdListQueriesIter = m_commandListQueries.end();

    if (result)
    {
        cmdListQueriesIter = m_commandListQueries.find(commandList.GetInterfacePtr());

        if (m_commandListQueries.end() == cmdListQueriesIter)
        {
            DX12CommandListSwQueries cmdListSwQueries;
            result = cmdListSwQueries.Initialize(m_device, commandList);

            if (result)
            {
                std::pair<CommandListQueriesType::iterator, bool> insertResult =
                    m_commandListQueries.insert(CommandListQueriesType::value_type(
                                                    commandList.GetInterfacePtr(), std::move(cmdListSwQueries)));
                result = insertResult.second;

                if (result)
                {
                    cmdListQueriesIter = insertResult.first;
                }
            }
        }
    }

    if (result)
    {
        result = cmdListQueriesIter->second.BeginSwSample(swSampleId);
        //commandList = m_commandList;
    }

    return result;
}

void GPA_ContextStateDX12::EndSwSample(
    ID3D12GraphicsCommandListPtr& commandList, const gpa_uint32 swSampleId)
{
    CommandListQueriesType::iterator cmdListIter =
        m_commandListQueries.find(commandList.GetInterfacePtr());
#ifdef _DEBUG
    assert(m_commandListQueries.end() != cmdListIter);
#endif // _DEBUG

    if ((m_commandListQueries.end() != cmdListIter))
    {
        cmdListIter->second.EndSwSample(swSampleId);
    }
}

void GPA_ContextStateDX12::ReleaseSwSample(
    ID3D12GraphicsCommandListPtr& commandList, const gpa_uint32 swSampleId)
{
    CommandListQueriesType::iterator cmdListIter =
        m_commandListQueries.find(commandList.GetInterfacePtr());
#ifdef _DEBUG
    assert(m_commandListQueries.end() != cmdListIter);
#endif // _DEBUG

    if (m_commandListQueries.end() != cmdListIter)
    {
        cmdListIter->second.ReleaseSwSample(swSampleId);
    }
}

void GPA_ContextStateDX12::BeginSwQuery(
    ID3D12GraphicsCommandListPtr& commandList,
    const gpa_uint32 swSampleId,
    const D3D12_QUERY_TYPE queryType)
{
    CommandListQueriesType::iterator cmdListIter =
        m_commandListQueries.find(commandList.GetInterfacePtr());
#ifdef _DEBUG
    assert(m_commandListQueries.end() != cmdListIter);
#endif // _DEBUG

    if (m_commandListQueries.end() != cmdListIter)
    {
        cmdListIter->second.BeginSwQuery(swSampleId, queryType);
    }
}

void GPA_ContextStateDX12::EndSwQuery(
    ID3D12GraphicsCommandListPtr& commandList,
    const gpa_uint32 swSampleId,
    const D3D12_QUERY_TYPE queryType)
{
    CommandListQueriesType::iterator cmdListIter =
        m_commandListQueries.find(commandList.GetInterfacePtr());
#ifdef _DEBUG
    assert(m_commandListQueries.end() != cmdListIter);
#endif // _DEBUG

    if (m_commandListQueries.end() != cmdListIter)
    {
        cmdListIter->second.EndSwQuery(swSampleId, queryType);
    }
}

bool GPA_ContextStateDX12::GetSwSampleResults(
    ID3D12GraphicsCommandListPtr& commandList,
    const gpa_uint32 swSampleId,
    DX12SoftwareCountersResults& queryResults)
{
    CommandListQueriesType::iterator cmdListIter =
        m_commandListQueries.find(commandList.GetInterfacePtr());
    bool result = (m_commandListQueries.end() != cmdListIter);

    if (result)
    {
        result = cmdListIter->second.GetSwSampleResults(swSampleId, queryResults);
    }

    return result;
}

inline GPA_Status GPA_ContextStateDX12::SetStableClocks(bool useProfilingClocks)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr != m_pGpaInterface)
    {
        AmdExtDeviceClockMode clockMode = useProfilingClocks ? AmdExtDeviceClockMode::Profiling : AmdExtDeviceClockMode::Default;
        m_pGpaInterface->SetClockMode(clockMode, nullptr);
    }
    else
    {
        //if (nullptr != m_device)
        //{
        //    // this will set stable clock for devices that do not support the GpaSession extension
        //    HRESULT hr = m_device->SetStablePowerState(useProfilingClocks ? TRUE : FALSE);

        //    if (S_OK != hr)
        //    {
        //        result = GPA_STATUS_ERROR_FAILED;
        //    }
        //}
    }

    return result;
}

gpa_uint32 GPA_ContextStateDX12::GetInstanceCount(AmdExtGpuBlock block)
{
    gpa_uint32 instanceCount = 0;

    if (block < AmdExtGpuBlock::Count)
    {
        instanceCount = m_props.blocks[static_cast<size_t>(block)].instanceCount;
    }

    return instanceCount;
}

gpa_uint32 GPA_ContextStateDX12::GetMaxEventIdCount(AmdExtGpuBlock block)
{
    gpa_uint32 maxEventId = 0;

    if (block < AmdExtGpuBlock::Count)
    {
        maxEventId = m_props.blocks[static_cast<size_t>(block)].maxEventId;
    }

    return maxEventId;
}
