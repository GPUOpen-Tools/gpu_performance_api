//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX12 GPA Command List Declarations
//==============================================================================

#ifndef GPU_PERF_API_DX12_DX12_GPA_COMMAND_LIST_H_
#define GPU_PERF_API_DX12_DX12_GPA_COMMAND_LIST_H_

#include <map>
#include <unordered_set>

#include <d3d12.h>

#pragma warning(push)
#pragma warning(disable : 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning(pop)

#include "gpu_perf_api_common/gpa_command_list.h"
#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_sample.h"

#include "gpu_perf_api_dx12/dx12_gpa_pass.h"

class Dx12GpaSession;  // Forward declaration.

using SampleResultSize = GpaUInt64;  ///< Type alias for size of sample result.
using SampleResult     = GpaUInt64;  ///< Type alias for sample result.

/// @brief Class for DX12 GPA Command List.
class GPA_NOT_THREAD_SAFE_OBJECT Dx12GpaCommandList : public GpaCommandList
{
public:
    using BundleResultAmdExtSession = IAmdExtGpaSession*;  ///< Type alias for bundle result session.
    using SecondaryDx12Cmd          = Dx12GpaCommandList;  ///< Type alias for secondary dx12 command list.

    /// @brief Constructor
    ///
    /// @param [in] dx12_gpa_session Dx12 GPA session.
    /// @param [in] dx12_gpa_pass Pass object pointer.
    /// @param [in] cmd Command list pointer.
    /// @param [in] command_list_id Command list id.
    /// @param [in] cmd_type Command list type.
    Dx12GpaCommandList(Dx12GpaSession* dx12_gpa_session, GpaPass* dx12_gpa_pass, void* cmd, CommandListId command_list_id, GpaCommandListType cmd_type);

    /// @brief Delete default constructor.
    Dx12GpaCommandList() = delete;

    /// @brief Destructor.
    ~Dx12GpaCommandList();

    /// @copydoc IGpaCommandList::IsResultReady()
    bool IsResultReady() const override;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

    /// @brief Get the ID3D12GraphicsCommandList.
    ///
    /// @return ID3D12GraphicsCommandList pointer.
    ID3D12GraphicsCommandList* GetCmdList() const;

    /// @brief Copies the bundle session result from the primary command list.
    ///
    /// @param [in] client_sample_ids client sample id.
    /// @param [in] dx12_secondary_cmd DirectX 12 GPA secondary command list object pointer.
    /// @param [out] original_client_sample_ids List of original client sample ids created on secondary command list.
    ///
    /// @return True upon successful operation otherwise false.
    bool CopyBundleSamples(std::vector<ClientSampleId>  client_sample_ids,
                           SecondaryDx12Cmd*            dx12_secondary_cmd,
                           std::vector<ClientSampleId>& original_client_sample_ids);

    /// @brief Returns the command list GPA extension session.
    ///
    /// @return DirectX 12 AMD GPA extension session.
    IAmdExtGpaSession* GetAmdExtSession() const;

    /// @brief Returns the bundle result GPA extension session for the given sample id.
    ///
    /// @param [in] client_sample_id Client sample id.
    ///
    /// @return DirectX 12 AMD GPA extension session.
    IAmdExtGpaSession* GetBundleResultAmdExtSession(ClientSampleId client_sample_id) const;

    /// @brief Release the graphics command list.
    void ReleaseNonGPAResources();

private:
    /// @copydoc GpaCommandList::BeginCommandListRequest()
    bool BeginCommandListRequest() override final;

    /// @copydoc GpaCommandList::EndCommandListRequest()
    bool EndCommandListRequest() override final;

    /// @copydoc GpaCommandList::BeginSampleRequest()
    bool BeginSampleRequest(ClientSampleId client_sample_id, GpaSample* gpa_sample) override final;

    /// @copydoc GpaCommandList::CloseLastSampleRequest()
    bool CloseLastSampleRequest() override final;

    /// @brief Creates a hardware sample.
    ///
    /// @param [in] client_sample_id Client sample id.
    /// @param [out] driver_sample_id Pointer to write the driver generated sample id.
    ///
    /// @return true upon successful Operation otherwise false.
    bool OpenHwSample(ClientSampleId client_sample_id, DriverSampleId* driver_sample_id) const;

    /// @brief Creates a hardware sample.
    ///
    /// @param [in] client_sample_id Client sample id.
    /// @param [out] driver_sample_id Pointer to write the driver generated sample id.
    ///
    /// @return True upon successful operation otherwise false.
    bool OpenSwSample(ClientSampleId client_sample_id, DriverSampleId* driver_sample_id = nullptr) const;

    /// @brief Closes the previously opened hardware sample.
    ///
    /// @return True upon successful operation otherwise false.
    bool CloseHwSample() const;

    /// @brief Closes the previously opened software sample.
    ///
    /// @return True upon successful operation otherwise false.
    bool CloseSwSample();

    /// Type alias for set of client sample id for bundle samples.
    using BundleSamplesOnPrimaryCmd = std::unordered_set<ClientSampleId>;

    /// Type alias for pair of bundle result session and set of bundle samples.
    using BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdPair = std::pair<BundleResultAmdExtSession, BundleSamplesOnPrimaryCmd>;

    /// Type alias for map of bundle result session and set of bundle samples
    using BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdMap = std::map<BundleResultAmdExtSession, BundleSamplesOnPrimaryCmd>;

    std::mutex                 dx12_cmd_list_mutex_;  ///< Mutex for DX12 cmd List object.
    ID3D12GraphicsCommandList* cmd_list_;             ///< Command list.

    /// Amd Ext Gpa session.
    IAmdExtGpaSession* amd_ext_session_;

    /// Map of bundle result session and client sample id - usage only applicable if the cmd is primary.
    BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdMap secondary_sample_amd_ext_session_map_;

    bool is_command_list_open_in_driver_;  ///< Flag indicating if the command list has been started in the driver (i.e. if it is in a recording state).
    bool is_non_gpa_resource_released_;    ///< Flag indicating ID3DGraphicsCommand list has been released or not.
    bool has_any_hardware_counters_;       ///< Flag indicating if there are any non-skipped hardware counters in this request.
    bool use_pre1850_config_;              ///< Flag indicating whether to use pre-18.50 configuration.
    bool use_pre2240_config_;              ///< Flag indicating whether to use pre-22.40 configuration.
};

#endif  // GPU_PERF_API_DX12_DX12_GPA_COMMAND_LIST_H_
