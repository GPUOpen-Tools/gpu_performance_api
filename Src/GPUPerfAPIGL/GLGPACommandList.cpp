//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GL GPA Command List Implementation
//==============================================================================

#include "GLGPACommandList.h"

GLGPACommandList::GLGPACommandList(IGPASession* pGpaSession,
                                   GPAPass* pGpaPass,
                                   CommandListId commandListId) :
    GPACommandList(pGpaSession, pGpaPass, commandListId),
    m_pPreviousSample(nullptr)
{
}

GPA_API_Type GLGPACommandList::GetAPIType() const
{
    return GPA_API_OPENGL;
}

bool GLGPACommandList::BeginCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool GLGPACommandList::EndCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool GLGPACommandList::BeginSampleRequest(ClientSampleId clientSampleId,
                                          GPASample* pGpaSample)
{
    UNREFERENCED_PARAMETER(clientSampleId);

    bool success = true;

    if (!GetPass()->IsTimingPass() && nullptr != m_pPreviousSample)
    {
        // Last sample already exist - collect its data first before proceeding
        success &= m_pPreviousSample->UpdateResults();
    }

    if (!GetPass()->IsTimingPass())
    {
        m_pPreviousSample = reinterpret_cast<GLGPASample*>(pGpaSample);
    }

    return success;
}

bool GLGPACommandList::CloseLastSampleRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}