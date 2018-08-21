//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 GPA Pass Object Header
//==============================================================================

#ifndef _DX11_GPA_PASS_H_
#define _DX11_GPA_PASS_H_

// GPA Common
#include "GPAPass.h"
#include "IGPACommandList.h"

#include "DX11Include.h"
#include "DX11GPAContext.h"

using BlockInstanceLimitMap = std::map<PE_BLOCK_ID, unsigned int>;              ///< type alias for a map from block id to number of instances
using GpuBlockInstanceLimitMap = std::map<UINT, BlockInstanceLimitMap>;         ///< type alias for a map from GPU Index to a BlockInstanceLimitMap
using SQEngineParamValue = UINT;                                                ///< type alias for SQ Engine param value

/// Class for DirectX 11 gpa pass
class DX11GPAPass : public GPAPass
{
public:

    /// Constructor
    /// \param[in] pGpaSession GPA session object pointer
    /// \param[in] passIndex pass index
    /// \param[in] counterSource counter source
    /// \param[in] pPassCounters counter list for the pass
    DX11GPAPass(IGPASession* pGpaSession,
                PassIndex passIndex,
                GPACounterSource counterSource,
                CounterList* pPassCounters);

    /// \copydoc GPAPass::CreateAPISpecificSample
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList,
                                       GpaSampleType sampleType,
                                       ClientSampleId sampleId) override final;

    /// \copydoc GPAPass::ContinueSample
    bool ContinueSample(ClientSampleId srcSampleId,
                        IGPACommandList* pPrimaryGpaCmdList) override final;

    /// \copydoc GPAPass::CreateAPISpecificCommandList
    IGPACommandList* CreateAPISpecificCommandList(void* pCmd,
                                                  CommandListId commandListId,
                                                  GPA_Command_List_Type cmdType) override final;

    /// \copydoc GPAPass::EndSample
    bool EndSample(IGPACommandList* pCmdList) override final;

    /// Returns the cached SQ engine param value for the counter
    /// \param[in] counterIndex counter index
    /// \param[out] sqEngineParamValue SQ block engine value for the counter
    /// \return true if counter is enabled otherwise false
    bool GetSQEngineParamValue(CounterIndex counterIndex, SQEngineParamValue& sqEngineParamValue);

    /// Destructor
    ~DX11GPAPass() = default;

private:

    /// Initializes the counter information for the pass
    void InitializeCounterInfo();

    /// Initializes the counter experiment parameters
    void InitiliazeCounterExperimentParameters();

    /// Initialize the block instance limits for the specified GPU
    /// \param[in] activeGpu the gpu index whose block instance limits are needed
    void PopulateBlockInstanceLimits(UINT activeGpu) const;

    /// Get the block info for the specified block of the specified GPU
    /// \param[in] gpuID the GPU being queried
    /// \param[in] block the block id being queried
    /// \param[out] pBlockInfo the block info
    /// \return true on success, false otherwise
    bool GetBlockCounterInfo(UINT gpuID, PE_BLOCK_ID block, PE_BLOCK_COUNTER_INFO* pBlockInfo) const;

    static GpuBlockInstanceLimitMap                             ms_blockInstanceLimits;             ///< map of block instance counts per gpu device
    std::map<CounterIndex, SQEngineParamValue>                  m_counterShaderMaskValueMap;        ///< map of the shader mask value for counter in SQ block the pass
};

#endif // _DX11_GPA_PASS_H_
