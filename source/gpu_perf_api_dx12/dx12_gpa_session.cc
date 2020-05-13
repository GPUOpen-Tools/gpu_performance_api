//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX12 GPA Session implementation
//==============================================================================

#include "dx12_gpa_session.h"
#include "dx12_gpa_command_list.h"
#include "gpa_common_defs.h"
#include "gpa_unique_object.h"
#include "dx12_utils.h"
#include "dx12_gpa_context.h"
#include "dx12_gpa_pass.h"
#include "gpa_sample.h"

DX12GPASession::DX12GPASession(DX12GPAContext* pDX12GpaContext, GPA_Session_Sample_Type sampleType, IAmdExtGpaInterface* pAmdExtGpaSession)
    : GPASession(pDX12GpaContext, sampleType)
{
    m_pAmdExtGpaInterface = pAmdExtGpaSession;
    m_pAmdExtGpaInterface->AddRef();
}

DX12GPASession::~DX12GPASession()
{
    if (nullptr != m_pAmdExtGpaInterface)
    {
        m_pAmdExtGpaInterface->Release();
    }
}

GPA_Status DX12GPASession::ContinueSampleOnCommandList(gpa_uint32 srcSampleId, GPA_CommandListId primaryCommandListId)
{
    bool succeed = false;

    if (primaryCommandListId->Object()->GetAPIType() == GPA_API_DIRECTX_12 && primaryCommandListId->ObjectType() == GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST)
    {
        DX12GPACommandList* pDx12Cmd     = reinterpret_cast<DX12GPACommandList*>(primaryCommandListId->Object());
        DX12GPAPass*        pDx12GpaPass = reinterpret_cast<DX12GPAPass*>(pDx12Cmd->GetPass());

        if (nullptr != pDx12GpaPass)
        {
            // Continue the sample
            if (pDx12GpaPass->ContinueSample(srcSampleId, pDx12Cmd))
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
            GPA_LogError("Pass doesn't exist.");
        }
    }
    else
    {
        GPA_LogError("Invalid Parameter.");
    }

    return succeed ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

GPA_Status DX12GPASession::CopySecondarySamples(GPA_CommandListId secondaryCmdListId,
                                                GPA_CommandListId primaryCmdListId,
                                                gpa_uint32        numSamples,
                                                gpa_uint32*       pNewSampleIds)
{
    bool succeed = false;

    if (secondaryCmdListId->Object()->GetAPIType() == GPA_API_DIRECTX_12 && secondaryCmdListId->ObjectType() == GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST &&
        primaryCmdListId->Object()->GetAPIType() == GPA_API_DIRECTX_12 && primaryCmdListId->ObjectType() == GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST)
    {
        DX12GPACommandList* pDx12PrimaryCmd     = reinterpret_cast<DX12GPACommandList*>(primaryCmdListId->Object());
        DX12GPACommandList* pDx12SecondaryCmd   = reinterpret_cast<DX12GPACommandList*>(secondaryCmdListId->Object());
        DX12GPAPass*        pDx12PrimaryCmdPass = reinterpret_cast<DX12GPAPass*>(pDx12PrimaryCmd->GetPass());

        if (nullptr != pDx12PrimaryCmdPass)
        {
            // TODO: We'll need to be able to support SOFTWARE counters in secondary passes as well.
            if (GPACounterSource::HARDWARE == pDx12PrimaryCmdPass->GetCounterSource())
            {
                std::vector<ClientSampleId> sampleIndices;

                for (size_t sampleIdIter = 0; sampleIdIter < numSamples; sampleIdIter++)
                {
                    sampleIndices.push_back(pNewSampleIds[sampleIdIter]);
                }

                if (pDx12PrimaryCmdPass->CopySecondarySamples(sampleIndices, pDx12PrimaryCmd, pDx12SecondaryCmd))
                {
                    succeed = true;
                }
            }
        }
    }
    else
    {
        GPA_LogError("Invalid Parameter.");
    }

    return succeed ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

GPA_API_Type DX12GPASession::GetAPIType() const
{
    return GPA_API_DIRECTX_12;
}

IAmdExtGpaInterface* DX12GPASession::GetAmdExtInterface() const
{
    return m_pAmdExtGpaInterface;
}

GPAPass* DX12GPASession::CreateAPIPass(PassIndex passIndex)
{
    GPAPass* pRetPass = nullptr;

    CounterList*     pPassCounters = GetCountersForPass(passIndex);
    GPACounterSource counterSource = GetParentContext()->GetCounterSource((*pPassCounters)[0]);
    DX12GPAPass*     pDx12Pass     = new (std::nothrow) DX12GPAPass(this, passIndex, counterSource, pPassCounters);

    if (nullptr != pDx12Pass)
    {
        pRetPass = pDx12Pass;
    }

    return pRetPass;
}
