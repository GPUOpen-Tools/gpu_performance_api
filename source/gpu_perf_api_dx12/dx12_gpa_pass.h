//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Pass Object Header
//==============================================================================

#ifndef GPU_PERF_API_DX12_DX12_GPA_PASS_H_
#define GPU_PERF_API_DX12_DX12_GPA_PASS_H_

#pragma warning(push)
#pragma warning(disable : 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning(pop)

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/gpa_pass.h"
#include "gpu_perf_api_dx12/dx12_gpa_sample_config.h"

class Dx12GpaCommandList;

/// @brief Class for DirectX 12 GPA pass.
class Dx12GpaPass : public GpaPass
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] gpa_session GPA session object pointer.
    /// @param [in] pass_index Pass index.
    /// @param [in] counter_source Counter source.
    /// @param [in] pass_counters Counter list for the pass.
    Dx12GpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters);

    /// @copydoc GpaPass::CreateApiSpecificSample()
    GpaSample* CreateApiSpecificSample(IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id) override final;

    /// @copydoc GpaPass::UpdateResults()
    bool UpdateResults() override final;

    /// @copydoc GpaPass::CreateApiSpecificCommandList()
    IGpaCommandList* CreateApiSpecificCommandList(void* cmd, CommandListId command_list_id, GpaCommandListType cmd_type) override final;

    /// @copydoc GpaPass::EndSample()
    bool EndSample(IGpaCommandList* cmd_list) override final;

    /// @brief Adds the secondary sample to the primary command list.
    ///
    /// @param [in] client_samples List of the client samples.
    /// @param [in] dx12_primary_gpa_cmd_list DirectX 12 gpa primary command list object pointer.
    /// @param [in] dx12_secondary_gpa_cmd_list DirectX 12 gpa secondary command list object pointer.
    ///
    /// @return True if samples are successfully copied.
    bool CopySecondarySamples(std::vector<ClientSampleId> client_samples,
                              Dx12GpaCommandList*         dx12_primary_gpa_cmd_list,
                              Dx12GpaCommandList*         dx12_secondary_gpa_cmd_list);

    /// @brief Returns the current sample config for the set of counters in the pass.
    ///
    /// @return AMD extension sample config for the set of counters in the pass.
    const AmdExtGpaSampleConfig& GetDriverExtSampleConfig() const
    {
        return amd_ext_sample_config_;
    }

    /// @brief Returns older sample config for the set of counters in the pass.
    ///
    /// @return AMD extension sample config for the set of counters in the pass.
    AmdExtGpaSampleConfigPre1850 GetPre1850DriverExtSampleConfig() const
    {
        AmdExtGpaSampleConfigPre1850 older_config;
        older_config = amd_ext_sample_config_;
        return older_config;
    }

    /// @brief Returns older sample config for the set of counters in the pass.
    ///
    /// @return AMD extension sample config for the set of counters in the pass.
    AmdExtGpaSampleConfigPre2240 GetPre2240DriverExtSampleConfig() const
    {
        AmdExtGpaSampleConfigPre2240 older_config;
        older_config = amd_ext_sample_config_;
        return older_config;
    }

    /// @brief Destructor.
    virtual ~Dx12GpaPass();

private:
    /// @brief Initializes the sample config for the pass if pass counter source is hardware.
    void InitializeSampleConfig();

    /// @brief Removes the irrelevant resources.
    void ResetPass() const;

    /// AMD Extension configuration for hardware samples.
    AmdExtGpaSampleConfig amd_ext_sample_config_;

    /// Flag indicating whether the sample config is initialized or not for the hardware samples.
    bool is_sample_config_initialized_;
};

#endif  // GPU_PERF_API_DX12_DX12_GPA_PASS_H_
