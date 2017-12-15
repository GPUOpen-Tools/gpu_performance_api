//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Interface for GPA Command List Object
//==============================================================================

#include "VkGPACommandList.h"
#include "VkGPASession.h"
#include <vulkan.h>
#include "VkEntrypoints.h"
#include "VkGPAContext.h"
#include "VkGPASoftwareSample.h"

VkGPACommandList::VkGPACommandList(VkGPASession * pVkGpaSession,
                                   GPAPass * pPass,
                                   void * pCmd,
                                   GPA_Command_List_Type cmdType)
    : m_pParentSession(pVkGpaSession),
    m_pPass(pPass),
    m_vkCmdBuffer(static_cast<VkCommandBuffer>(pCmd)),
    m_commandListType(cmdType),
    m_gpaExtSessionAMD(VK_NULL_HANDLE),
    m_commandListState(CommandListState::UNDEFINED),
    m_cmdSampleState(CommandSampleState::SAMPLE_NOT_STARTED),
    m_pLastSample(nullptr)
{
}

VkGPACommandList::~VkGPACommandList()
{
    VkGPAContext* pVkContext = static_cast<VkGPAContext*>(m_pParentSession->GetParentContext());
    VkDevice device = pVkContext->GetVkDevice();

    if (VK_NULL_HANDLE != m_gpaExtSessionAMD)
    {
        _vkDestroyGpaSessionAMD(device, m_gpaExtSessionAMD, nullptr);
    }
    m_gpaExtSessionAMD = VK_NULL_HANDLE;

    for (auto cIter = m_copiedAmdExtSessions.cbegin(); cIter != m_copiedAmdExtSessions.cend(); ++cIter)
    {
        _vkDestroyGpaSessionAMD(device, *cIter, nullptr);
    }

    m_copiedAmdExtSessions.clear();
    m_copiedSampleMap.clear();
}

GPA_API_Type VkGPACommandList::GetAPIType() const
{
    return GPA_API_VULKAN;
}

GPAObjectType VkGPACommandList::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST;
}

IGPASession * VkGPACommandList::GetParentSession() const
{
    return m_pParentSession;
}

void VkGPACommandList::SetAmdExtSession(VkGpaSessionAMD gpaExtSessionAMD)
{
    if (VK_NULL_HANDLE == m_gpaExtSessionAMD)
    {
        m_gpaExtSessionAMD = gpaExtSessionAMD;
    }
}

VkGpaSessionAMD VkGPACommandList::GetAmdExtSession() const
{
    return m_gpaExtSessionAMD;
}

bool VkGPACommandList::Begin()
{
    bool began = false;

    if (CommandListState::UNDEFINED == m_commandListState)
    {
        if (GPACounterSource::HARDWARE == m_pPass->GetCounterSource())
        {
            VkGPAContext* pVkContext = static_cast<VkGPAContext*>(m_pParentSession->GetParentContext());
            VkDevice device = pVkContext->GetVkDevice();

            bool isReadyToBegin = false;

            if (VK_NULL_HANDLE != m_gpaExtSessionAMD)
            {
                // I don't think we should get into this situation, but just in case...
                if (VK_SUCCESS != _vkResetGpaSessionAMD(device, m_gpaExtSessionAMD))
                {
                    GPA_LogError("Unable to reset extension for new command list.");
                    began = false;
                }
                else
                {
                    isReadyToBegin = true;
                }
            }
            else
            {
                // Create a new extension session
                VkGpaSessionCreateInfoAMD createInfo = { VK_STRUCTURE_TYPE_GPA_SESSION_CREATE_INFO_AMD, nullptr };
                createInfo.secondaryCopySource = VK_NULL_HANDLE;

                if (VK_SUCCESS != _vkCreateGpaSessionAMD(device, &createInfo, nullptr, &m_gpaExtSessionAMD))
                {
                    GPA_LogError("Failed to create a session on the AMD GPA Extension.");
                    began = false;
                }
                else
                {
                    isReadyToBegin = true;
                }

            }

            if (isReadyToBegin)
            {
                // NOTE: We're not calling _vkCmdBeginGpaSessionAMD() because in the case that there
                // are no samples on this vkCommandBuffer, there is a driver bug that would prevent the
                // session from ever reporting that the results are ready (so we'd be stuck in a loop always
                // waiting for results to come back, and would never be "Complete".
                // The solution, is to wait until GPA_BeginSample() is called, and start begin the 
                // CommandLists's GpaSessionAMD at that time if it hasn't already been started.

                // Mark the CommandList as having started though, so we know that Begin should have been called.
                m_commandListState = CommandListState::SAMPLE_RECORDING_BEGIN;
                began = true;
            }
        }
        else // Software Sample
        {
            VkGPAContext* pVkGpaContext = static_cast<VkGPAContext*>(m_pParentSession->GetParentContext());
            bool initialized = m_swQueries.Initialize(pVkGpaContext->GetVkPhysicalDevice(), pVkGpaContext->GetVkDevice(), m_vkCmdBuffer);

            if (initialized)
            {
                m_commandListState = CommandListState::SAMPLE_RECORDING_BEGIN;
                began = true;
            }
        }
        return began;
    }

    GPA_LogError("CommandList already started.");

    return false;
}

bool VkGPACommandList::End()
{
    bool isEnded = false;

    if (CommandListState::UNDEFINED == m_commandListState)
    {
        GPA_LogDebugError("Command list is not yet opened for sampling.");
    }
    else if (CommandListState::SAMPLE_RECORDING_END == m_commandListState)
    {
        GPA_LogError("Command List already ended.");
    }
    else if (CommandListState::SAMPLE_RECORDING_BEGIN == m_commandListState)
    {
        // Assume the command list will be ended, and set to false below as needed.
        isEnded = true;

        if (CommandSampleState::SAMPLE_STARTED == m_cmdSampleState)
        {
            // Close any outstanding opened sample and mark it as candidate for continuation
            if (!CloseLastSample(false))
            {
                GPA_LogError("Failed to close the most recent sample on a command list.");
                isEnded = false;
            }
        }

        // _IF_ a sample was started, then it was either previously ended, or it was closed above.
        // If the sample state is now ENDED, then we know we must also end the GPA Extension Session.
        // WORKAROUND: Due to a driver bug, we only want to begin / end the session if it has at least one sample on it.
        if (CommandSampleState::SAMPLE_ENDED == m_cmdSampleState)
        {
            if (GPACounterSource::HARDWARE == m_pPass->GetCounterSource())
            {
                if (VK_SUCCESS != _vkCmdEndGpaSessionAMD(m_vkCmdBuffer, m_gpaExtSessionAMD))
                {
                    GPA_LogDebugError("AMD extension is unable to end the command list.");
                    isEnded = false;
                }
            }
        }

        if (isEnded)
        {
            m_commandListState = CommandListState::SAMPLE_RECORDING_END;
        }
    }

    return isEnded;
}

bool VkGPACommandList::IsCommandListRunning() const
{
    return CommandListState::SAMPLE_RECORDING_BEGIN == m_commandListState;
}

GPAPass * VkGPACommandList::GetPass() const
{
    return m_pPass;
}

gpa_uint32 VkGPACommandList::GetSampleCount() const
{
    return static_cast<gpa_uint32>(m_primarySampleMap.size());
}

bool VkGPACommandList::DoesSampleExist(ClientSampleId clientSampleId)
{
    bool exists = false;

    auto sampleIter = m_primarySampleMap.find(clientSampleId);
    exists = sampleIter != m_primarySampleMap.end();

    return exists;
}

bool VkGPACommandList::BeginSample(ClientSampleId clientSampleIndex, GPASample* pSample, const std::vector<CounterIndex>* pCounterList)
{
    bool isSampleStarted = false;

    m_sampleMapMutex.lock();

    if (CommandListState::SAMPLE_RECORDING_BEGIN != m_commandListState)
    {
        GPA_LogError("Command list must be in recording state to start/end a sample.");
    }
    else if (CommandSampleState::SAMPLE_STARTED == m_cmdSampleState)
    {
        GPA_LogError("Previous sample must be ended before starting a new one.");
    }
    else if (DoesSampleExist(clientSampleIndex))
    {
        GPA_LogError("Sample Id already exists.");
    }
    else
    {
        // If there is an error starting the GPA Session, then don't try to start to the sample.
        bool sessionError = false;

        if (CommandSampleState::SAMPLE_NOT_STARTED == m_cmdSampleState && 
            GPACounterSource::HARDWARE == m_pPass->GetCounterSource())
        {
            // This is the first time a sample is being opened on this CommandList.
            // Due to a driver bug, we have to wait until this point to begin the GpaSession instead
            // of doing it in VkGPACommandList::Begin().
            if (VK_SUCCESS != _vkCmdBeginGpaSessionAMD(m_vkCmdBuffer, m_gpaExtSessionAMD))
            {
                GPA_LogError("Unable to open command list for sampling.");
                sessionError = true;
            }
        }

        // The above code may have started the session if this is the first sample on this command list
        if (!sessionError)
        {
            if (GPACounterSource::SOFTWARE == m_pPass->GetCounterSource())
            {
                VkGPASoftwareSample* pSwSample = static_cast<VkGPASoftwareSample*>(pSample);
                pSwSample->AssignQueries(&m_swQueries);
            }

            isSampleStarted = pSample->Begin(m_pParentSession->GetParentContext(), pCounterList);

            if (isSampleStarted)
            {
                m_cmdSampleState = CommandSampleState::SAMPLE_STARTED;
                VkGPASample* pVkSample = static_cast<VkGPASample*>(pSample);
                m_pLastSample = pVkSample;
                m_primarySampleMap[clientSampleIndex] = pVkSample;
                m_primarySampleList.push_back(pVkSample);
            }
            else
            {
                GPA_LogError("Unable to begin sample in command list.");
            }
        }
    }

    m_sampleMapMutex.unlock();

    return isSampleStarted;
}

VkGPASample* VkGPACommandList::GetSample(ClientSampleId clientSampleId) const
{
    VkGPASample* pGPASample = nullptr;

    m_sampleMapMutex.lock();

    std::map<ClientSampleId, VkGPASample*>::const_iterator iter = m_primarySampleMap.find(clientSampleId);

    if (iter != m_primarySampleMap.end())
    {
        pGPASample = iter->second;
    }

    m_sampleMapMutex.unlock();

    return pGPASample;
}

GPASample * VkGPACommandList::GetLastSample() const
{
    return m_pLastSample;
}

bool VkGPACommandList::CloseLastSample(bool closingByClient)
{
    bool isClosed = false;

    if (CommandListState::SAMPLE_RECORDING_BEGIN != m_commandListState)
    {
        GPA_LogError("Command list must be in recording state to start/end a sample.");
    }
    else if (CommandSampleState::SAMPLE_STARTED != m_cmdSampleState)
    {
        GPA_LogError("Sample must be started before ending one.");
    }
    else if (nullptr == m_pLastSample)
    {
        GPA_LogError("Sample has not been added to the list.");
    }
    else
    {
        if (closingByClient)
        {
            m_pLastSample->SetAsClosedByClient();
        }

        if (m_pLastSample->End())
        {
            m_cmdSampleState = CommandSampleState::SAMPLE_ENDED;
            m_pLastSample = nullptr;
            isClosed = true;
        }
    }

    return isClosed;
}

bool VkGPACommandList::IsLastSampleClosed() const
{
    return (CommandSampleState::SAMPLE_ENDED == m_cmdSampleState) ||
        (CommandSampleState::SAMPLE_NOT_STARTED == m_cmdSampleState);
}

bool VkGPACommandList::IsComplete() const
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    return false;
}

GPA_Command_List_Type VkGPACommandList::GetCmdType() const
{
    return m_commandListType;
}

VkCommandBuffer VkGPACommandList::GetVkCommandBuffer() const
{
    return m_vkCmdBuffer;
}

bool VkGPACommandList::CopySecondarySamples(VkGPACommandList* pPrimaryCmdList, gpa_uint32 numSamples, gpa_uint32 * pNewSampleIds, std::vector<ClientSampleId>& originalSampleIds)
{
    bool copied = false;

    // For now, we only support copying hardware counters.
    // TODO: We should probably see if are able to support software counters too.
    if (GPACounterSource::HARDWARE == m_pPass->GetCounterSource())
    {
        VkGpaSessionCreateInfoAMD createInfo = { VK_STRUCTURE_TYPE_GPA_SESSION_CREATE_INFO_AMD, nullptr };
        createInfo.secondaryCopySource = m_gpaExtSessionAMD;

        VkGPAContext* pVkContext = static_cast<VkGPAContext*>(m_pParentSession->GetParentContext());
        VkDevice device = pVkContext->GetVkDevice();

        VkGpaSessionAMD sessionCopy = VK_NULL_HANDLE;
        if (VK_SUCCESS == _vkCreateGpaSessionAMD(device, &createInfo, nullptr, &sessionCopy))
        {
            m_sampleMapMutex.lock();
            m_copiedAmdExtSessions.push_back(sessionCopy);

            for (size_t sampleIdIter = 0; sampleIdIter < numSamples; sampleIdIter++)
            {
                ClientSampleId originalSampleId = m_primarySampleList[sampleIdIter]->GetClientSampleId();
                originalSampleIds.push_back(originalSampleId);

                CopiedSampleInfo copiedInfo = {};
                copiedInfo.originalSampleId = originalSampleId;
                copiedInfo.copiedAmdExtSession = sessionCopy;
                m_copiedSampleMap[pNewSampleIds[sampleIdIter]] = copiedInfo;
            }
            m_sampleMapMutex.unlock();

            // Schedule the data copy on the primary command buffer
            _vkCmdCopyGpaSessionResultsAMD(pPrimaryCmdList->GetVkCommandBuffer(), sessionCopy);

            copied = true;
        }
    }
    else // software counters
    {
        m_sampleMapMutex.lock();
        for (size_t sampleIdIter = 0; sampleIdIter < numSamples; sampleIdIter++)
        {
            ClientSampleId originalSampleId = m_primarySampleList[sampleIdIter]->GetClientSampleId();
            originalSampleIds.push_back(originalSampleId);

            // TODO: need to copy the query results back somewhere... not sure where or how yet

            CopiedSampleInfo copiedInfo = {};
            copiedInfo.originalSampleId = originalSampleId;
            copiedInfo.copiedAmdExtSession = VK_NULL_HANDLE;
            m_copiedSampleMap[pNewSampleIds[sampleIdIter]] = copiedInfo;
        }
        m_sampleMapMutex.unlock();

        copied = false;
    }

    return copied;
}

VkGpaSessionAMD VkGPACommandList::GetCopiedAmdExtSession(ClientSampleId clientSampleId) const
{
    VkGpaSessionAMD copiedExtSession = VK_NULL_HANDLE;

    std::map<ClientSampleId, CopiedSampleInfo>::const_iterator cIter = m_copiedSampleMap.find(clientSampleId);

    if (cIter != m_copiedSampleMap.cend())
    {
        copiedExtSession = cIter->second.copiedAmdExtSession;
    }

    return copiedExtSession;
}
