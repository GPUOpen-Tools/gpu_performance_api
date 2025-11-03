//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX11 GPA Pass Object Header
//==============================================================================

#ifndef GPU_PERF_API_DX11_DX11_GPA_PASS_H_
#define GPU_PERF_API_DX11_DX11_GPA_PASS_H_

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/gpa_pass.h"

#include "gpu_perf_api_dx11/dx11_gpa_context.h"
#include "gpu_perf_api_dx11/dx11_include.h"

using BlockInstanceLimitMap    = std::map<PE_BLOCK_ID, unsigned int>;    ///< Type alias for a map from block id to number of instances.
using GpuBlockInstanceLimitMap = std::map<UINT, BlockInstanceLimitMap>;  ///< Type alias for a map from GPU Index to a BlockInstanceLimitMap.
using SqEngineParamValue       = UINT;                                   ///< Type alias for SQ Engine param value.

/// @brief Class for DirectX 11 GPA pass.
class Dx11GpaPass : public GpaPass
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] gpa_session GPA session object pointer.
    /// @param [in] pass_index Pass index.
    /// @param [in] counter_source Counter source.
    /// @param [in] pass_counters Counter list for the pass.
    Dx11GpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters);

    /// @copydoc GpaPass::CreateApiSpecificSample(IGpaCommandList*, GpaSampleType, ClientSampleId)
    GpaSample* CreateApiSpecificSample(IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id) override final;

    /// @copydoc GpaPass::ContinueSample(ClientSampleId, IGpaCommandList*)
    bool ContinueSample(ClientSampleId src_sample_id, IGpaCommandList* primary_gpa_cmd_list) override final;

    /// @copydoc GpaPass::CreateApiSpecificCommandList(void*, CommandListId, GpaCommandListType)
    IGpaCommandList* CreateApiSpecificCommandList(void* cmd, CommandListId command_list_id, GpaCommandListType cmd_type) override final;

    /// @copydoc GpaPass::EndSample(IGpacommandList)
    bool EndSample(IGpaCommandList* cmd_list) override final;

    /// @brief Returns the cached SQ engine param value for the counter.
    ///
    /// @param [in] counter_index Counter index.
    /// @param [out] sq_engine_param_value SQ block engine value for the counter.
    ///
    /// @return True if counter is enabled otherwise false.
    bool GetSqEngineParamValue(CounterIndex counter_index, SqEngineParamValue& sq_engine_param_value);

    /// @brief Destructor.
    ~Dx11GpaPass() = default;

private:
    /// @brief Initializes the counter information for the pass.
    void InitializeCounterInfo();

    /// @brief Initializes the counter experiment parameters.
    void InitializeCounterExperimentParameters();

    std::map<CounterIndex, SqEngineParamValue> counter_shader_mask_value_map_;  ///< Map of the shader mask value for counter in SQ block the pass.
};

#endif
