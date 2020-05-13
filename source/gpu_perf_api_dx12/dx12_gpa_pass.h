//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 GPA Pass Object Header
//==============================================================================

#ifndef _DX12_GPA_PASS_H_
#define _DX12_GPA_PASS_H_

// AMD Ext
#pragma warning(push)
#pragma warning(disable : 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning(pop)

// GPA Common
#include "gpa_pass.h"
#include "gpa_command_list_interface.h"

class DX12GPACommandList;  // forward declaration

#pragma warning(push, 3)
#pragma warning(disable : 4201)  // nonstandard extension used: nameless struct/union

/// Input structure for CmdBeginGpuProfilerSample.
///
/// Defines a set of global performance counters and/or SQ thread trace data to be sampled.
/// struct declaration for pre-18.50 drivers
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

    /// Translate from newer configuration to this older configuration
    /// \updatedConfig[in] updated GPA sample configuration
    /// \return this AmdExtGpaSampleConfigPre1850 instance
    AmdExtGpaSampleConfigPre1850& operator=(const AmdExtGpaSampleConfig& updatedConfig)
    {
        // Query type is not supported by older configuration
        type = updatedConfig.type;

        if (type == AmdExtGpaSampleType::Query)
        {
            type = AmdExtGpaSampleType::None;
        }

        flags.u32All = updatedConfig.flags.u32All;
        sqShaderMask = updatedConfig.sqShaderMask;

        memcpy(&perfCounters, &updatedConfig.perfCounters, sizeof(perfCounters));

        // sqtt struct differs between older and newer configuration
        sqtt.flags.u32All   = updatedConfig.sqtt.flags.u32All;
        sqtt.gpuMemoryLimit = updatedConfig.sqtt.gpuMemoryLimit;

        memcpy(&timing, &updatedConfig.timing, sizeof(timing));

        return *this;
    }
};

#pragma warning(pop)

/// Class for DirectX 12 gpa pass
class DX12GPAPass : public GPAPass
{
public:
    /// Constructor
    /// \param[in] pGpaSession GPA session object pointer
    /// \param[in] passIndex pass index
    /// \param[in] counterSource counter source
    /// \param[in] pPassCounters counter list for the pass
    DX12GPAPass(IGPASession* pGpaSession, PassIndex passIndex, GPACounterSource counterSource, CounterList* pPassCounters);

    /// \copydoc GPAPass::CreateAPISpecificSample
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList, GpaSampleType sampleType, ClientSampleId sampleId) override final;

    /// \copydoc GPAPass::UpdateResults
    bool UpdateResults() override final;

    /// \copydoc GPAPass::CreateAPISpecificCommandList
    IGPACommandList* CreateAPISpecificCommandList(void* pCmd, CommandListId commandListId, GPA_Command_List_Type cmdType) override final;

    /// \copydoc GPAPass::EndSample
    bool EndSample(IGPACommandList* pCmdList) override final;

    /// Adds the secondary sample to the primary command list
    /// \param[in] clientSamples list of the client samples
    /// \param[in] pDx12PrimaryGpaCmdList DirectX 12 gpa primary command list object pointer
    /// \param[in] pDx12SecondaryGpaCmdList DirectX 12 gpa secondary command list object pointer
    /// \return true if samples are successfully copied
    bool CopySecondarySamples(std::vector<ClientSampleId> clientSamples,
                              DX12GPACommandList*         pDx12PrimaryGpaCmdList,
                              DX12GPACommandList*         pDx12SecondaryGpaCmdList);

    /// Returns the current sample config for the set of counters in the pass
    /// \return AMD extension sample config for the set of counters in the pass
    const AmdExtGpaSampleConfig& GetDriverExtSampleConfig() const
    {
        return m_amdExtsampleConfig;
    }

    /// Returns older sample config for the set of counters in the pass
    /// \return AMD extension sample config for the set of counters in the pass
    AmdExtGpaSampleConfigPre1850 GetPre1850DriverExtSampleConfig() const
    {
        AmdExtGpaSampleConfigPre1850 olderConfig;
        olderConfig = m_amdExtsampleConfig;
        return olderConfig;
    }

    /// Destructor
    ~DX12GPAPass();

private:
    /// Initializes the sample config for the pass if pass counter source is hardware
    void InitializeSampleConfig();

    /// Removes the irrelevant resources
    void ResetPass() const;

    AmdExtGpaSampleConfig m_amdExtsampleConfig;         ///< AMD Extension configuration for hardware samples
    bool                  m_isSampleConfigInitialized;  ///< flag indicating whether the sample config is initialized or not for the hardware samples
};

#endif  // _DX12_GPA_PASS_H_
