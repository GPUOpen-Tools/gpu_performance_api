//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief CL GPA Command List Declarations
//==============================================================================

#ifndef _CL_GPA_COMMAND_LIST_H_
#define _CL_GPA_COMMAND_LIST_H_

// GPA Common
#include "GPACommandList.h"

/// Class for CL GPA Command List
class CLGPACommandList : public GPACommandList
{
public:

    /// Constructor
    CLGPACommandList() = delete;

    /// Constructor
    /// \param[in] pGpaSession GPA session pointer
    /// \param[in] pGpaPass pass object pointer
    /// \param[in] commandListId command list id
    CLGPACommandList(IGPASession* pGpaSession,
        GPAPass* pGpaPass,
        CommandListId commandListId);

    /// Destructor
    ~CLGPACommandList() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override final;

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
};

#endif // _CL_GPA_COMMAND_LIST_H_
