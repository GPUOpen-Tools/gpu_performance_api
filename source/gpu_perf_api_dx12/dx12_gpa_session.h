//==============================================================================
// Copyright (c) 2017-2023 Advanced Micro Devices, Inc. All rights reserved.
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

class Dx12GpaContext;  // Forward declaration.

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

    /// @brief Returns the driver version.
    ///
    /// @param [out] major Driver major version number.
    /// @param [out] minor Driver minor version number.
    /// @param [out] sub_minor Driver sub_minor version number.
    void GetDriverVersion(uint32_t& major, uint32_t& minor, uint32_t& sub_minor);

private:
    /// @copydoc GpaSession::CreateApiPass()
    GpaPass* CreateApiPass(PassIndex pass_index) override;

    IAmdExtGpaInterface* amd_ext_gpa_interface_;  ///< AMD Extension Interface.
};
#endif  // GPU_PERF_API_DX12_DX12_GPA_SESSION_H_
