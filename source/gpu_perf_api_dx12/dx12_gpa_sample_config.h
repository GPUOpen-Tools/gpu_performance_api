//==============================================================================
// Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Sample Configuration Header.
//==============================================================================

#ifndef GPU_PERF_API_DX12_DX12_GPA_SAMPLE_CONFIG_H_
#define GPU_PERF_API_DX12_DX12_GPA_SAMPLE_CONFIG_H_

#include <assert.h>

#include <AmdExtGpaInterfaceApi.h>

#include "gpa_counter_accessor_interface.h"
#include "gpa_pass.h"
#include "gpa_session_interface.h"
#include "logging.h"

#if defined(_MSC_VER)
#pragma warning(push)
// AmdExtGpaSampleConfigPre1850 and AmdExtGpaSampleConfigPre2240 employ nonstandard nameless struct/union extension.
#pragma warning(disable : 4201)
#endif

/// @brief Input structure for CmdBeginGpuProfilerSample on drivers older than 18.50.
///
/// Defines a set of global performance counters and/or SQ thread trace data to be sampled.
/// struct declaration for pre-18.50 drivers.
struct AmdExtGpaSampleConfigPre1850
{
    /// Selects what type of data should be gathered for this sample.  This can either be _cumulative_ to gather
    /// simple deltas for the specified set of perf counters over the sample period, or it can be _trace_ to generate
    /// a blob of RGP-formatted data containing SQ thread trace and/or streaming performance monitor data.
    AmdExtGpaSampleType type;

    union
    {
        struct
        {
            UINT32 sampleInternalOperations : 1;       ///< Include BLTs and internal driver operations in the
                                                       ///  results.
            UINT32 cacheFlushOnCounterCollection : 1;  ///< Insert cache flush and invalidate events before and
                                                       ///  after every sample.
            UINT32 sqShaderMask : 1;                   ///< Whether or not the contents of sqShaderMask are valid.
            UINT32 reserved : 29;                      ///< Reserved for future use.
        };
        UINT32 u32All;  ///< Bit flags packed as uint32.
    } flags;            ///< Bit flags controlling sample operation for all sample
                        ///  types.

    AmdExtPerfExperimentShaderFlags sqShaderMask;  ///< Indicates which hardware shader stages should be
                                                   ///  sampled. Only valid if flags.sqShaderMask is set to 1.

    struct
    {
        /// Number of entries in pIds.
        UINT32 numCounters;

        /// List of performance counters to be gathered for a sample.  If the sample type is _cumulative_ this will
        /// result in "global" perf counters being sampled at the beginning of the sample period; if the sample type
        /// is _trace_ this will result in SPM data being added to the sample's resulting RGP blob.
        ///
        /// Note that it is up to the client to respect the hardware counter limit per block.  This can be
        /// determined by the maxGlobalOnlyCounters, maxGlobalSharedCounters, and maxSpmCounters fields of
        /// @ref AmdExtGpuBlockPerfProperties.
        const AmdExtPerfCounterId* pIds;

        /// Period for SPM sample collection in cycles.  Only relevant for _trace_ samples.
        UINT32 spmTraceSampleInterval;

        /// Maximum amount of GPU memory in bytes this sample can allocate for SPM data.  Only relevant for _trace_
        /// samples.
        UINT64 gpuMemoryLimit;
    } perfCounters;  ///< Performance counter selection (valid for both _cumulative_ and _trace_ samples).

    struct
    {
        union
        {
            struct
            {
                UINT32 enable : 1;                    ///< Include SQTT data in the trace.
                UINT32 supressInstructionTokens : 1;  ///< Prevents capturing instruction-level SQTT tokens,
                                                      ///  significantly reducing the amount of sample data.
                UINT32 reserved : 30;                 ///< Reserved for future use.
            };
            UINT32 u32All;      ///< Bit flags packed as uint32.
        } flags;                ///< Bit flags controlling SQTT samples.
        UINT64 gpuMemoryLimit;  ///< Maximum amount of GPU memory in bytes this sample can allocate for the SQTT
                                ///  buffer.  If 0, allocate maximum size to prevent dropping tokens toward the
                                ///  end of the sample.

    } sqtt;  ///< SQ thread trace configuration (only valid for _trace_ samples).

    struct
    {
        AmdExtHwPipePoint preSample;   ///< The point in the GPU pipeline where the begin timestamp should take place.
        AmdExtHwPipePoint postSample;  ///< The point in the GPU pipeline where the end timestamp should take place.
    } timing;                          ///< Timestamp configuration. (only valid for timing samples)

    /// Translate from newer configuration to this older configuration.
    ///
    /// @param [in] updated_config updated GPA sample configuration.
    ///
    /// @return This AmdExtGpaSampleConfigPre1850 instance.
    AmdExtGpaSampleConfigPre1850& operator=(const AmdExtGpaSampleConfig& updated_config)
    {
        // Query type is not supported by older configuration
        type = updated_config.type;

        if (type == AmdExtGpaSampleType::Query)
        {
            GPA_LOG_ERROR("AmdExtGpaSampleType::Query is not supported on pre-18.50 drivers");
            assert(type == AmdExtGpaSampleType::Query);
            type = AmdExtGpaSampleType::None;
        }

        flags.u32All = updated_config.flags.u32All;
        sqShaderMask = updated_config.sqShaderMask;

        memcpy(&perfCounters, &updated_config.perfCounters, sizeof(perfCounters));

        // sqtt struct differs between older and newer configuration
        sqtt.flags.u32All   = updated_config.sqtt.flags.u32All;
        sqtt.gpuMemoryLimit = updated_config.sqtt.gpuMemoryLimit;

        memcpy(&timing, &updated_config.timing, sizeof(timing));

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
        /// Number of entries in perf_counter_ids.
        UINT32 num_counters;

        /// @brief List of performance counters to be gathered for a sample.
        ///
        /// If the sample type is _cumulative_ this will
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

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

struct CounterResultEntry
{
    uint32_t counter_id;
    uint32_t offset;
    uint32_t in_use;
};

class Dx12GpaSampleConfig
{
public:
    Dx12GpaSampleConfig()
        : session_(nullptr)
        , is_sample_config_initialized_(false)
        , sample_type_(kGpaSessionSampleTypeDiscreteCounter)
    {
        amd_ext_sample_config_ = {};
    }

    ~Dx12GpaSampleConfig();

    bool Initialize(IGpaSession* session, GpaCounterSource counter_source, const CounterList* counter_list, GpaPass* gpa_pass, bool is_timing_pass);

    bool UpdateSettings();

    const AmdExtGpaSampleConfig& GetDriverExtSampleConfig() const
    {
        return amd_ext_sample_config_;
    }

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

    const std::vector<CounterResultEntry>& GetSpmCounterResultEntries() const
    {
        return counter_result_entries_;
    }

private:
    bool                  UpdateSpmSettings(const IGpaSession* session);
    const IGpaSession*    session_;                       ///< The GpaSession this sample is being configured for.
    AmdExtGpaSampleConfig amd_ext_sample_config_;         ///< AMD Extension configuration for hardware samples.
    bool                  is_sample_config_initialized_;  ///< Flag indicating whether the sample config is initialized for the hardware samples.
    GpaSessionSampleType  sample_type_;                   ///< The type of samples being collected in this configuration.

    std::vector<CounterResultEntry> counter_result_entries_;
};

#endif
