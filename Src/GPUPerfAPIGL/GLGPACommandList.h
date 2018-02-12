//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GL GPA Command List Declarations
//==============================================================================

#ifndef _GL_GPA_COMMAND_LIST_H_
#define _GL_GPA_COMMAND_LIST_H_

// GPA Common
#include "GPACommandList.h"
#include "GLGPASample.h"

/// Class for GL GPA Command List
class GLGPACommandList : public GPACommandList
{
public:

    /// Constructor
    GLGPACommandList() = delete;

    /// Constructor
    /// \param[in] pGpaSession GPA session pointer
    /// \param[in] pGpaPass pass object pointer
    /// \param[in] commandListId command list id
    GLGPACommandList(IGPASession* pGpaSession,
                     GPAPass* pGpaPass,
                     CommandListId commandListId);

    /// Destructor
    ~GLGPACommandList() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

private:

    /// \copydoc GPACommandList::BeginCommandListRequest()
    bool BeginCommandListRequest() override final;

    /// \copydoc GPACommandList::EndCommandListRequest()
    bool EndCommandListRequest() override final;

    /// \copydoc GPACommandList::BeginSampleRequest()
    bool BeginSampleRequest(ClientSampleId clientSampleId,
                            GPASample* pGpaSample) override final;

    /// \copydoc GPACommandList::CloseLastSampleRequest()
    bool CloseLastSampleRequest() override final;

    GLGPASample* m_pPreviousSample;                    ///< Previous GL sample request
};

#endif // _GL_GPA_COMMAND_LIST_H_
