//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  CL GPA Pass Object Header
//==============================================================================

#ifndef _CL_GPA_PASS_H_
#define _CL_GPA_PASS_H_

#include <CL/cl_platform.h>

// GPA Common
#include "gpa_pass.h"
#include "gpa_command_list_interface.h"

using GroupCountersPair = std::pair<GpaUInt32, std::vector<cl_ulong>>;  ///< type alias for pair of group and counters in that group
using GroupCountersMap  = std::map<GpaUInt32, std::vector<cl_ulong>>;   ///< type alias for map of group and counters in that group

/// Class for OpenCL gpa pass
class ClGpaPass : public GpaPass
{
public:
    /// Constructor
    /// @param [in] gpa_session GPA session object pointer
    /// @param [in] pass_index pass index
    /// @param [in] counter_source counter source
    /// @param [in] pass_counters counter list for the pass
    ClGpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters);

    /// Destructor
    ~ClGpaPass() = default;

    /// @copydoc GpaPass::CreateApiSpecificCommandList
    GpaSample* CreateApiSpecificSample(IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id) override final;

    /// @copydoc GpaPass::ContinueSample
    bool ContinueSample(ClientSampleId src_sample_id, IGpaCommandList* primary_gpa_cmd_list) override final;

    /// @copydoc GpaPass::CreateApiSpecificCommandList
    IGpaCommandList* CreateApiSpecificCommandList(void* cmd, CommandListId command_list_id, GpaCommandListType cmd_type) override final;

    /// @copydoc GpaPass::EndSample
    bool EndSample(IGpaCommandList* cmd_list) override final;

    /// Iterate over all the CL counter in the pass
    /// @param [in] function function to be executed for each object in the list - function may return false to terminate iteration
    void IterateClCounterMap(std::function<bool(GroupCountersPair group_counters_pair)> function) const;

private:
    /// Initializes the CL counter info
    void InitializeClCounterInfo();

    GroupCountersMap group_counters_map_;  ///< Map of all the CL counters in the group
};

#endif  // _CL_GPA_PASS_H_
