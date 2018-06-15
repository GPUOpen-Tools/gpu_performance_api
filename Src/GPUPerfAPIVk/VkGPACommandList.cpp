//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Vulkan GPA Command List Object Implementation
//==============================================================================

#include "VkGPACommandList.h"
#include "VkGPASession.h"
#include <vulkan/vulkan.h>
#include "VkEntrypoints.h"
#include "VkGPAContext.h"
#include "VkGPASoftwareSample.h"

VkGPACommandList::VkGPACommandList(VkGPASession* pVkGpaSession,
                                   GPAPass* pPass,
                                   void* pCmd,
                                   CommandListId commandListId,
                                   GPA_Command_List_Type cmdType)
    : GPACommandList(pVkGpaSession, pPass, commandListId, cmdType),
      m_vkCmdBuffer(static_cast<VkCommandBuffer>(pCmd)),
      m_gpaExtSessionAMD(VK_NULL_HANDLE),
      m_isCommandListOpenInDriver(false)
{
    UNREFERENCED_PARAMETER(commandListId);
}

VkGPACommandList::~VkGPACommandList()
{
    VkGPAContext* pVkContext = reinterpret_cast<VkGPAContext*>(GPACommandList::GetParentSession()->GetParentContext());
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

bool VkGPACommandList::BeginCommandListRequest()
{
    bool began = false;

    if (GPACounterSource::HARDWARE == GetPass()->GetCounterSource())
    {
        VkGPAContext* pVkContext = reinterpret_cast<VkGPAContext*>(GetParentSession()->GetParentContext());
        VkDevice device = pVkContext->GetVkDevice();

        bool isReadyToBegin = false;

        if (VK_NULL_HANDLE != m_gpaExtSessionAMD)
        {
            // I don't think we should get into this situation, but just in case...
            if (VK_SUCCESS == _vkResetGpaSessionAMD(device, m_gpaExtSessionAMD))
            {
                isReadyToBegin = true;
            }
            else
            {
                GPA_LogError("Unable to reset extension for new command list.");
            }
        }
        else
        {
            // Create a new extension session
            VkGpaSessionCreateInfoAMD createInfo = { VK_STRUCTURE_TYPE_GPA_SESSION_CREATE_INFO_AMD, nullptr, VK_NULL_HANDLE };
            createInfo.secondaryCopySource = VK_NULL_HANDLE;

            if (VK_SUCCESS == _vkCreateGpaSessionAMD(device, &createInfo, nullptr, &m_gpaExtSessionAMD))
            {
                isReadyToBegin = true;
            }
            else
            {
                GPA_LogError("Failed to create a session on the AMD GPA Extension.");
            }
        }

        if (isReadyToBegin)
        {
            if (VK_SUCCESS == _vkCmdBeginGpaSessionAMD(m_vkCmdBuffer, m_gpaExtSessionAMD))
            {
                began = true;
                m_vkCommandListMutex.lock();
                m_isCommandListOpenInDriver = true;
                m_vkCommandListMutex.unlock();
            }
            else
            {
                GPA_LogError("Unable to open command list for sampling.");
            }

        }
    }
    else // Software Sample
    {
        VkGPAContext* pVkGpaContext = reinterpret_cast<VkGPAContext*>(GetParentSession()->GetParentContext());
        began = m_swQueries.Initialize(pVkGpaContext->GetVkPhysicalDevice(), pVkGpaContext->GetVkDevice(), m_vkCmdBuffer);
    }

    return began;
}

bool VkGPACommandList::EndCommandListRequest()
{
    bool isEnded = false;

    // _IF_ a sample was started, then it was either previously ended, or it was closed above.
    // If the sample state is now ENDED, then we know we must also end the GPA Extension Session.
    // WORKAROUND: Due to a driver bug, we only want to begin / end the session if it has at least one sample on it.
    if (GPACounterSource::HARDWARE == GetPass()->GetCounterSource() &&
        m_isCommandListOpenInDriver)
    {
        if (VK_SUCCESS == _vkCmdEndGpaSessionAMD(m_vkCmdBuffer, m_gpaExtSessionAMD))
        {
            m_vkCommandListMutex.lock();
            m_isCommandListOpenInDriver = false;
            m_vkCommandListMutex.unlock();
            isEnded = true;
        }
        else
        {
            GPA_LogDebugError("AMD extension is unable to end the command list.");
        }
    }

    return isEnded;
}

bool VkGPACommandList::BeginSampleRequest(ClientSampleId clientSampleId,
                                          GPASample* pGpaSample)
{
    UNREFERENCED_PARAMETER(clientSampleId);
    UNREFERENCED_PARAMETER(pGpaSample);

    if (GPACounterSource::SOFTWARE == GetPass()->GetCounterSource())
    {
        VkGPASoftwareSample* pSwSample = reinterpret_cast<VkGPASoftwareSample*>(pGpaSample);
        pSwSample->AssignQueries(&m_swQueries);
    }

    return true;
}

bool VkGPACommandList::CloseLastSampleRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool VkGPACommandList::IsResultReady() const
{
    bool isResultReady = false;

    VkGPAContext* pVkGPAContext = dynamic_cast<VkGPAContext*>(GetParentSession()->GetParentContext());

    if (nullptr == pVkGPAContext)
    {
        GPA_LogError("Invalid profiling session encountered when checking for available results.");
    }
    else
    {
        VkResult isReady = _vkGetGpaSessionStatusAMD(pVkGPAContext->GetVkDevice(), m_gpaExtSessionAMD);
        isResultReady = VK_SUCCESS == isReady;
    }

    return isResultReady;
}

VkCommandBuffer VkGPACommandList::GetVkCommandBuffer() const
{
    return m_vkCmdBuffer;
}

bool VkGPACommandList::CopySecondarySamples(VkGPACommandList* pPrimaryCmdList,
                                            gpa_uint32 numSamples,
                                            gpa_uint32* pNewSampleIds,
                                            std::vector<ClientSampleId>& originalSampleIds)
{
    UNREFERENCED_PARAMETER(numSamples);
    bool copied = false;

    // For now, we only support copying hardware counters.
    // TODO: We should probably see if are able to support software counters too.
    if (GPACounterSource::HARDWARE == GetPass()->GetCounterSource())
    {
        VkGpaSessionCreateInfoAMD createInfo = { VK_STRUCTURE_TYPE_GPA_SESSION_CREATE_INFO_AMD, nullptr, VK_NULL_HANDLE};
        createInfo.secondaryCopySource = m_gpaExtSessionAMD;

        VkGPAContext* pVkContext = reinterpret_cast<VkGPAContext*>(GetParentSession()->GetParentContext());
        VkDevice device = pVkContext->GetVkDevice();

        VkGpaSessionAMD sessionCopy = VK_NULL_HANDLE;

        if (VK_SUCCESS == _vkCreateGpaSessionAMD(device, &createInfo, nullptr, &sessionCopy))
        {
            m_vkCommandListMutex.lock();
            m_copiedAmdExtSessions.push_back(sessionCopy);

            unsigned int sampleIndex = 0;
            auto ProcessClientSampleId = [&](ClientSampleIdGpaSamplePair clientSampleIdGpaSamplePair)-> bool
            {
                ClientSampleId originalSampleId = clientSampleIdGpaSamplePair.second->GetClientSampleId();
                originalSampleIds.push_back(originalSampleId);

                CopiedSampleInfo copiedInfo = {};
                copiedInfo.originalSampleId = originalSampleId;
                copiedInfo.copiedAmdExtSession = sessionCopy;
                m_copiedSampleMap[pNewSampleIds[sampleIndex]] = copiedInfo;
                originalSampleId = clientSampleIdGpaSamplePair.second->GetClientSampleId();
                sampleIndex++;
                return true;
            };

            IterateSampleUnorderedMap(ProcessClientSampleId);
            m_vkCommandListMutex.unlock();

            // Schedule the data copy on the primary command buffer
            _vkCmdCopyGpaSessionResultsAMD(pPrimaryCmdList->GetVkCommandBuffer(), sessionCopy);
            copied = true;
        }
    }
    else // software counters
    {
        m_vkCommandListMutex.lock();

        unsigned int sampleIndex = 0;
        auto ProcessClientSampleId = [&](ClientSampleIdGpaSamplePair clientSampleIdGpaSamplePair)-> bool
        {
            ClientSampleId originalSampleId = clientSampleIdGpaSamplePair.second->GetClientSampleId();
            originalSampleIds.push_back(originalSampleId);

            // TODO: need to copy the query results back somewhere... not sure where or how yet

            CopiedSampleInfo copiedInfo = {};
            copiedInfo.originalSampleId = originalSampleId;
            copiedInfo.copiedAmdExtSession = VK_NULL_HANDLE;
            m_copiedSampleMap[pNewSampleIds[sampleIndex]] = copiedInfo;
            sampleIndex++;
            return true;
        };

        IterateSampleUnorderedMap(ProcessClientSampleId);
        m_vkCommandListMutex.unlock();
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
