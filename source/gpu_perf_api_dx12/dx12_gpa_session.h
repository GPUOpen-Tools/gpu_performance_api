//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX12 GPA Session declaration
//==============================================================================

#ifndef GPU_PERF_API_DX12_DX12_GPA_SESSION_H_
#define GPU_PERF_API_DX12_DX12_GPA_SESSION_H_

#pragma warning(push)
#pragma warning(disable : 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning(pop)

#include "gpu_perf_api_common/gpa_session.h"

#include "gpu_perf_api_dx12/dx12_gpa_sample_config.h"

class Dx12GpaContext;

/// @brief Class for DX12 GPA Session
class Dx12GpaSession : public GpaSession
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] dx12_gpa_context DX12 GPA Context.
    /// @param [in] sample_type The sample type that will be created on this session.
    /// @param [in] amd_ext_gpa_session AMD Extension GpaSession.
    Dx12GpaSession(Dx12GpaContext* dx12_gpa_context, GpaSessionSampleType sample_type, IAmdExtGpaInterface* amd_ext_gpa_session);

    /// @brief Delete default constructor.
    Dx12GpaSession() = delete;

    /// @brief Destructor.
    virtual ~Dx12GpaSession();

    /// @copydoc IGpaSession::ContinueSampleOnCommandList()
    GpaStatus ContinueSampleOnCommandList(GpaUInt32 src_sample_id, GpaCommandListId primary_command_list_id) override;

    /// @copydoc IGpaSession::CopySecondarySamples()
    GpaStatus CopySecondarySamples(GpaCommandListId secondary_cmd_list_id,
                                   GpaCommandListId primary_cmd_list_id,
                                   GpaUInt32        num_samples,
                                   GpaUInt32*       new_sample_ids) override;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

    /// @brief Returns the AMD GPA extension interface.
    ///
    /// @return AMD GPA extension interface.
    IAmdExtGpaInterface* GetAmdExtInterface() const;

    /// @copydoc IGpaSession::SqttBegin(void*)
    virtual GpaStatus SqttBegin(void* command_list) override;

    /// @copydoc IGpaSession::SqttEnd(void*)
    virtual GpaStatus SqttEnd(void* command_list) override;

    /// @copydoc IGpaSession::SqttGetSampleResultSize(size_t*)
    virtual GpaStatus SqttGetSampleResultSize(size_t* sample_result_size_in_bytes) override;

    /// @copydoc IGpaSession::SqttGetSampleResult(size_t, void*)
    virtual GpaStatus SqttGetSampleResult(size_t sample_result_size_in_bytes, void* sqtt_results) override;

    /// @copydoc IGpaSession::SpmSetSampleInterval(GpaUInt32)
    virtual GpaStatus SpmSetSampleInterval(GpaUInt32 interval) override;

    /// @copydoc IGpaSession::SpmSetDuration(GpaUInt32)
    virtual GpaStatus SpmSetDuration(GpaUInt32 nanosecond_duration) override;

    /// @copydoc IGpaSession::SpmBegin(void*)
    virtual GpaStatus SpmBegin(void* command_list) override;

    /// @copydoc IGpaSession::SpmEnd(void*)
    virtual GpaStatus SpmEnd(void* command_list) override;

    /// @copydoc IGpaSession::SpmGetSampleResultSize(size_t*)
    virtual GpaStatus SpmGetSampleResultSize(size_t* sample_result_size_in_bytes) override;

    /// @copydoc IGpaSession::SpmGetSampleResult(size_t, void*)
    virtual GpaStatus SpmGetSampleResult(size_t sample_result_size_in_bytes, void* spm_results) override;

    /// @copydoc IGpaSession::SpmCalculateDerivedCounters(const GpaSpmData*, GpaUInt32, GpaUInt64*)
    virtual GpaStatus SpmCalculateDerivedCounters(const GpaSpmData* spm_data, GpaUInt32 num_derived_counters, GpaUInt64* derived_counter_results) override;

    uint32_t GetSpmSampleInterval() const
    {
        return spm_sampling_interval_;
    }

    uint32_t GetSpmDuration() const
    {
        return spm_duration_;
    }

    /// @brief Returns the driver version.
    ///
    /// @param [out] major Driver major version number.
    /// @param [out] minor Driver minor version number.
    /// @param [out] sub_minor Driver sub_minor version number.
    void GetDriverVersion(uint32_t& major, uint32_t& minor, uint32_t& sub_minor);

private:
    bool FlushSession(IAmdExtGpaSession* pSession, uint32_t timeout);

    /// @copydoc GpaSession::CreateApiPass()
    GpaPass* CreateApiPass(PassIndex pass_index) override;

    IAmdExtGpaInterface* amd_ext_gpa_interface_;  ///< AMD Extension Interface.

    const uint32_t flush_timeout_ = 5 * 1000;  ///< 5 second timeout

    Dx12GpaSampleConfig session_sample_config_;  ///< Sample configuration.

    bool               sqtt_started_;           ///< Flag indicating SQTT collection started.
    uint32_t           sqtt_driver_sample_id_;  ///< SQTT driver sample id.
    IAmdExtGpaSession* sqtt_amd_ext_session_;   ///< AMD SQTT Ext GPA session.

    bool               spm_started_;            ///< Flag indicated SPM collection started.
    uint32_t           spm_driver_sample_id_;   ///< SPM driver sample id.
    uint32_t           spm_sampling_interval_;  ///< SPM sample interval.
    uint32_t           spm_duration_;           ///< SPM duration.
    IAmdExtGpaSession* spm_amd_ext_session_;    ///< AMD SPM Ext GPA session.
    const GpaSpmData*  spm_data_;               ///< Collected SPM data.
};
#endif  // GPU_PERF_API_DX12_DX12_GPA_SESSION_H_
