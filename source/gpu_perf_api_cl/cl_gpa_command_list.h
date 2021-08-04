//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief CL GPA Command List Declarations
//==============================================================================

#ifndef _CL_GPA_COMMAND_LIST_H_
#define _CL_GPA_COMMAND_LIST_H_

// GPA Common
#include "gpa_command_list.h"

/// Class for CL GPA Command List
class ClGpaCommandList : public GpaCommandList
{
public:
    /// Constructor
    /// @param [in] gpa_session GPA session pointer
    /// @param [in] gpa_pass pass object pointer
    /// @param [in] command_list_id command list id
    ClGpaCommandList(IGpaSession* gpa_session, GpaPass* gpa_pass, CommandListId command_list_id);

    /// Delete Default constructor
    ClGpaCommandList() = delete;

    /// Destructor
    ~ClGpaCommandList() = default;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override final;

private:
    /// @copydoc GpaCommandList::BeginCommandListRequest()
    bool BeginCommandListRequest() override final;

    /// @copydoc GpaCommandList::EndCommandListRequest()
    bool EndCommandListRequest() override final;

    /// @copydoc GpaCommandList::BeginSampleRequest()
    bool BeginSampleRequest(ClientSampleId client_sample_id, GpaSample* gpa_sample) override final;

    /// @copydoc GpaCommandList::CloseLastSampleRequest()
    bool CloseLastSampleRequest() override final;
};

#endif  // _CL_GPA_COMMAND_LIST_H_
