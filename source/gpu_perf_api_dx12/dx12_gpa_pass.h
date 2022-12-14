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

class Dx12GpaCommandList;  // Forward declaration.

#pragma warning(push, 3)
#pragma warning(disable : 4201)  // Nonstandard extension used: nameless struct/union.

/// @brief Input structure for CmdBeginGpuProfilerSample on drivers older than 18.50.
///
/// Defines a set of global performance counters and/or SQ thread trace data to be sampled
/// struct declaration for pre-18.50 drivers.
struct AmdExtGpaSampleConfigPre1850
{
    /// Selects what type of data should be gathered for this sample.  This can either be _cumulative_ to gather
    /// simple deltas for the specified set of perf counters over the sample period, or it can be _trace_ to generate
    /// a blob of RGP-formatted data containing SQ thread trace and/or streaming performance monitor data.
    AmdExtGpaSampleType type;

    /// @brief Bit flags controlling sample operation for all sample types.
    union
    {
        struct
        {
            /// Include BLTs and internal driver operations in the results.
            UINT32 sample_internal_operations : 1;

            /// Insert cache flush and invalidate events before and after every sample.
            UINT32 cache_flush_on_counter_collection : 1;

            /// Whether or not the contents of sq_shader_mask are valid.
            UINT32 sq_shader_mask : 1;

            /// Reserved for future use.
            UINT32 reserved : 29;
        };

        /// Bit flags packed as uint32.
        UINT32 u32_all;
    } flags_;

    /// Indicates which hardware shader stages should be sampled. Only valid if flags.sq_shader_mask is set to 1.
    AmdExtPerfExperimentShaderFlags sq_shader_mask;

    /// @brief Performance counter selection (valid for both _cumulative_ and _trace_ samples).
    struct
    {
        /// Number of entries in perf_counter_id.
        UINT32 num_counters;

        /// List of performance counters to be gathered for a sample.  If the sample type is _cumulative_ this will
        /// result in "global" perf counters being sampled at the beginning of the sample period; if the sample type
        /// is _trace_ this will result in SPM data being added to the sample's resulting RGP blob.
        ///
        /// Note that it is up to the client to respect the hardware counter limit per block.  This can be
        /// determined by the maxGlobalOnlyCounters, maxGlobalSharedCounters, and maxSpmCounters fields of
        /// @ref AmdExtGpuBlockPerfProperties.
        const AmdExtPerfCounterId* perf_counter_ids;

        /// Period for SPM sample collection in cycles.  Only relevant for _trace_ samples.
        UINT32 spm_trace_sample_interval;

        /// Maximum amount of GPU memory in bytes this sample can allocate for SPM data.  Only relevant for _trace_ samples.
        UINT64 gpu_memory_limit;
    } perf_counters_;

    /// @brief SQ thread trace configuration (only valid for _trace_ samples).
    struct
    {
        /// Bit flags controlling SQTT samples.
        union
        {
            struct
            {
                /// Include SQTT data in the trace.
                UINT32 enable : 1;

                /// Prevents capturing instruction-level SQTT tokens, significantly reducing the amount of sample data.
                UINT32 supress_instruction_tokens : 1;

                /// Reserved for future use.
                UINT32 reserved : 30;
            };

            /// Bit flags packed as uint32.
            UINT32 u32_all;
        } flags;

        /// Maximum amount of GPU memory in bytes this sample can allocate for the SQTT buffer.
        /// If 0, allocate maximum size to prevent dropping tokens toward the end of the sample.
        UINT64 gpu_memory_limit;

    } sqtt_;

    /// @brief Timestamp configuration. (only valid for timing samples)
    struct
    {
        /// The point in the GPU pipeline where the begin timestamp should take place.
        AmdExtHwPipePoint pre_sample;

        /// The point in the GPU pipeline where the end timestamp should take place.
        AmdExtHwPipePoint post_sample;
    } timing_;

    /// @brief Translate from newer configuration to this older configuration.
    ///
    /// @param [in] updated_config Updated GPA sample configuration.
    ///
    /// @return This AmdExtGpaSampleConfigPre1850 instance.
    AmdExtGpaSampleConfigPre1850& operator=(const AmdExtGpaSampleConfig& updated_config)
    {
        // Query type is not supported by pre-18.50 configuration.
        type = updated_config.type;

        if (type == AmdExtGpaSampleType::Query)
        {
            type = AmdExtGpaSampleType::None;
        }

        flags_.u32_all = updated_config.flags.u32All;
        sq_shader_mask = updated_config.sqShaderMask;

        memcpy(&perf_counters_, &updated_config.perfCounters, sizeof(perf_counters_));

        // Sqtt struct differs between older and newer configuration.
        sqtt_.flags.u32_all    = updated_config.sqtt.flags.u32All;
        sqtt_.gpu_memory_limit = updated_config.sqtt.gpuMemoryLimit;

        memcpy(&timing_, &updated_config.timing, sizeof(timing_));

        return *this;
    }
};

/// @brief Input structure for CmdBeginGpuProfilerSample on drivers older than 22.40.
///
/// Defines a set of global performance counters and/or SQ thread trace data to be sampled
/// struct declaration for pre-22.40 drivers. The latest struct introduces an sqWgpShaderMask
/// that makes the new struct larger than this pre2240 version.
struct AmdExtGpaSampleConfigPre2240
{
    /// Selects what type of data should be gathered for this sample.  This can either be _cumulative_ to gather
    /// simple deltas for the specified set of perf counters over the sample period, or it can be _trace_ to generate
    /// a blob of RGP-formatted data containing SQ thread trace and/or streaming performance monitor data.
    AmdExtGpaSampleType type;

    union
    {
        struct
        {
            UINT32 sample_internal_operations : 1;         ///< Include BLTs and internal driver operations in the
                                                           ///  results.
            UINT32 cache_flush_on_counter_collection : 1;  ///< Insert cache flush and invalidate events before and
                                                           ///  after every sample.
            UINT32 sq_shader_mask : 1;                     ///< Whether or not the contents of sqShaderMask are valid.
            UINT32 reserved : 29;                          ///< Reserved for future use.
        };
        UINT32 u32_all;  ///< Bit flags packed as uint32.
    } flags_;            ///< Bit flags controlling sample operation for all sample
                         ///  types.

    AmdExtPerfExperimentShaderFlags sq_shader_mask;  ///< Indicates which hardware shader stages should be
                                                     ///  sampled. Only valid if flags.sqShaderMask is set to 1.

    struct
    {
        /// Number of entries in pIds.
        UINT32 num_counters;

        /// List of performance counters to be gathered for a sample.  If the sample type is _cumulative_ this will
        /// result in "global" perf counters being sampled at the beginning of the sample period; if the sample type
        /// is _trace_ this will result in SPM data being added to the sample's resulting RGP blob.
        ///
        /// Note that it is up to the client to respect the hardware counter limit per block.  This can be
        /// determined by the maxGlobalOnlyCounters, maxGlobalSharedCounters, and maxSpmCounters fields of
        /// @ref AmdExtGpuBlockPerfProperties.
        const AmdExtPerfCounterId* perf_counter_ids;

        /// Period for SPM sample collection in cycles.  Only relevant for _trace_ samples.
        UINT32 spm_trace_sample_interval;

        /// Maximum amount of GPU memory in bytes this sample can allocate for SPM data.  Only relevant for _trace_
        /// samples.
        UINT64 gpu_memory_limit;
    } perf_counters_;  ///< Performance counter selection (valid for both _cumulative_ and _trace_ samples).

    struct
    {
        union
        {
            struct
            {
                UINT32 enable : 1;                      ///< Include SQTT data in the trace.
                UINT32 supress_instruction_tokens : 1;  ///< Prevents capturing instruction-level SQTT tokens,
                                                        ///  significantly reducing the amount of sample data.
                UINT32 reserved : 30;                   ///< Reserved for future use.
            };
            UINT32 u32_all;       ///< Bit flags packed as uint32.
        } flags;                  ///< Bit flags controlling SQTT samples.
        UINT32 se_mask;           ///< Mask that determines which specific SEs to run thread trace on.
                                  ///  If 0, all SEs are enabled
        UINT64 gpu_memory_limit;  ///< Maximum amount of GPU memory in bytes this sample can allocate for the SQTT
                                  ///  buffer.  If 0, allocate maximum size to prevent dropping tokens toward the
                                  ///  end of the sample.

    } sqtt_;  ///< SQ thread trace configuration (only valid for _trace_ samples).

    struct
    {
        AmdExtHwPipePoint pre_sample;   ///< The point in the GPU pipeline where the begin timestamp should take place.
        AmdExtHwPipePoint post_sample;  ///< The point in the GPU pipeline where the end timestamp should take place.
    } timing_;                          ///< Timestamp configuration. (only valid for timing samples)

    /// @brief Translate from newer configuration to this older configuration.
    ///
    /// @param [in] latest_config Updated GPA sample configuration.
    ///
    /// @return This AmdExtGpaSampleConfigPre2240 instance.
    AmdExtGpaSampleConfigPre2240& operator=(const AmdExtGpaSampleConfig& latest_config)
    {
        type = latest_config.type;

        flags_.u32_all = latest_config.flags.u32All;

        sq_shader_mask = latest_config.sqShaderMask;

        memcpy(&perf_counters_, &latest_config.perfCounters, sizeof(perf_counters_));
        memcpy(&sqtt_, &latest_config.sqtt, sizeof(sqtt_));
        memcpy(&timing_, &latest_config.timing, sizeof(timing_));

        return *this;
    }
};

#pragma warning(pop)

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
