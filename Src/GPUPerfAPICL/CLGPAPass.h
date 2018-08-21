//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  CL GPA Pass Object Header
//==============================================================================

#ifndef _CL_GPA_PASS_H_
#define _CL_GPA_PASS_H_

// GPA Common
#include "GPAPass.h"
#include "IGPACommandList.h"
#include <CL/cl_platform.h>

using GroupCountersPair = std::pair<gpa_uint32, std::vector<cl_ulong>>; ///< type alias for pair of group and counters in that group
using GroupCountersMap = std::map<gpa_uint32, std::vector<cl_ulong>>;   ///< type alias for map of group and counters in that group

/// Class for OpenCL gpa pass
class CLGPAPass : public GPAPass
{
public:

    /// Constructor
    /// \param[in] pGpaSession GPA session object pointer
    /// \param[in] passIndex pass index
    /// \param[in] counterSource counter source
    /// \param[in] pPassCounters counter list for the pass
    CLGPAPass(IGPASession* pGpaSession,
              PassIndex passIndex,
              GPACounterSource counterSource,
              CounterList* pPassCounters);

    /// Destructor
    ~CLGPAPass() = default;

    /// \copydoc GPAPass::CreateAPISpecificSample
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList,
                                       GpaSampleType sampleType,
                                       ClientSampleId sampleId) override final;

    /// \copydoc GPAPass::ContinueSample
    bool ContinueSample(ClientSampleId srcSampleId, IGPACommandList* pPrimaryGpaCmdList) override final;

    /// \copydoc GPAPass::CreateAPISpecificCommandList
    IGPACommandList* CreateAPISpecificCommandList(void* pCmd,
                                                  CommandListId commandListId,
                                                  GPA_Command_List_Type cmdType) override final;

    /// \copydoc GPAPass::EndSample
    bool EndSample(IGPACommandList* pCmdList) override final;

    /// Iterate over all the CL counter in the pass
    /// \param[in] function function to be executed for each object in the list - function may return false to terminate iteration
    void IterateCLCounterMap(std::function<bool(GroupCountersPair groupCountrsPair)> function) const;

private:

    /// Initializes the CL counter info
    void InitializeCLCounterInfo();

    GroupCountersMap m_groupCountersMap; ///< Map of all the CL counters in the group
};

#endif // _CL_GPA_PASS_H_
