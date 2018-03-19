//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief HSA GPA Command List Declarations
//==============================================================================

#ifndef _HSA_GPA_COMMAND_LIST_H_
#define _HSA_GPA_COMMAND_LIST_H_

// GPA Common
#include "GPACommandList.h"

/// Class for HSA GPA Command List
class HSAGPACommandList : public GPACommandList
{
public:

    /// Constructor
    /// \param[in] pGpaSession GPA session pointer
    /// \param[in] pGpaPass pass object pointer
    /// \param[in] commandListId command list id
    HSAGPACommandList(IGPASession* pGpaSession,
                      GPAPass* pGpaPass,
                      CommandListId commandListId);

    /// Delete default constructor
    HSAGPACommandList() = delete;

    /// Destructor
    ~HSAGPACommandList() = default;

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
};

#endif // _HSA_GPA_COMMAND_LIST_H_
