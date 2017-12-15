//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief A Vulkan-specific implementation of the GPA Session interface
//==============================================================================

#include <assert.h>

#include "VkGPASession.h"

#include "GPAUniqueObject.h"
#include "VkGPACommandList.h"
#include "VkGPAPass.h"

VkGPASession::VkGPASession(IGPAContext* parentContextId)
    : GPASession(parentContextId, parentContextId->GetCounterScheduler())
{
}

VkGPASession::~VkGPASession()
{
    for (auto cmdListIter = m_vkGpaCmdLists.begin(); cmdListIter != m_vkGpaCmdLists.end(); ++cmdListIter)
    {
        GPAUniqueObjectManager::Instance()->DeleteObject(*cmdListIter);
        delete *cmdListIter;
    }

    m_vkGpaCmdLists.clear();
}

GPA_API_Type VkGPASession::GetAPIType() const
{
    return GPA_API_VULKAN;
}

GPA_Status VkGPASession::ContinueSampleOnCommandList(gpa_uint32 srcSampleId, GPA_CommandListId primaryCommandListId)
{
    bool succeed = false;

    if (primaryCommandListId->Object()->GetAPIType() == GPA_API_DIRECTX_12 &&
        primaryCommandListId->ObjectType() == GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST)
    {
        VkGPACommandList* pVkGpaCmdList = reinterpret_cast<VkGPACommandList*>(primaryCommandListId->Object());
        VkGPAPass* pVkGpaPass = reinterpret_cast<VkGPAPass*>(pVkGpaCmdList->GetPass());

        if (nullptr != pVkGpaPass)
        {
            // Continue the sample
            if (pVkGpaPass->ContinueSample(srcSampleId, pVkGpaCmdList))
            {
                succeed = true;
            }
            else
            {
                GPA_LogError("Unable to continue sample.");
            }
        }
        else
        {
            GPA_LogError("Pass doesn't exists.");
        }
    }
    else
    {
        GPA_LogError("Invalid Parameter.");
    }

    return true == succeed ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

GPA_Status VkGPASession::CopySecondarySamples(GPA_CommandListId secondaryCmdListId, GPA_CommandListId primaryCmdListId, gpa_uint32 numSamples, gpa_uint32* pNewSampleIds)
{
    bool isCopied = false;

    if (secondaryCmdListId->Object()->GetAPIType() == GPA_API_VULKAN &&
        secondaryCmdListId->ObjectType() == GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST &&
        primaryCmdListId->Object()->GetAPIType() == GPA_API_VULKAN &&
        primaryCmdListId->ObjectType() == GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST)
    {
        VkGPACommandList* pVkPrimaryCmd = reinterpret_cast<VkGPACommandList*>(primaryCmdListId->Object());
        VkGPACommandList* pVkSecondaryCmd = reinterpret_cast<VkGPACommandList*>(secondaryCmdListId->Object());

        VkGPAPass* pVkPass = reinterpret_cast<VkGPAPass*>(pVkPrimaryCmd->GetPass());

        if (nullptr != pVkPass)
        {
            if (pVkPass->CopySecondarySamples(pVkSecondaryCmd, pVkPrimaryCmd, numSamples, pNewSampleIds))
            {
                isCopied = true;
            }
        }
    }
    else
    {
        GPA_LogError("Invalid Parameter.");
    }

    return isCopied ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

GPAPass* VkGPASession::CreateAPIPass(PassIndex passIndex)
{
    GPAPass* pRetPass = nullptr;

    CounterList* passCounters = GetCounterScheduler()->GetCountersForPass(passIndex);
    GPACounterSource counterSource = GetParentContext()->GetCounterSource((*passCounters)[0]);
    VkGPAPass* pVkGpaPass = new(std::nothrow) VkGPAPass(
        this,
        passIndex,
        counterSource,
        GetCounterScheduler(),
        GetParentContext()->GetCounterAccessor());

    if (nullptr != pVkGpaPass)
    {
        pRetPass = pVkGpaPass;
    }

    return pRetPass;
}
