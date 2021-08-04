//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA DX12 Context declarations
//==============================================================================

#ifndef GPU_PERF_API_DX12_DX12_GPA_CONTEXT_H_
#define GPU_PERF_API_DX12_DX12_GPA_CONTEXT_H_

#include <mutex>

#pragma warning(push)
#pragma warning(disable : 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning(pop)
#include <AmdExtD3D.h>

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_context.h"

class Dx12GpaSession;  // Forward declaration.

/// @brief Class for DX12 GPA Context.
class GPA_THREAD_SAFE_OBJECT Dx12GpaContext : public GpaContext
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] d3d12_device ID3D12Device pointer.
    /// @param [in] hw_info Hardware info.
    /// @param [in] flags Context flags.
    Dx12GpaContext(ID3D12Device* d3d12_device, GpaHwInfo& hw_info, GpaOpenContextFlags flags);

    /// @brief Destructor.
    virtual ~Dx12GpaContext();

    /// @copydoc IGpaContext::CreateSession()
    GpaSessionId CreateSession(GpaSessionSampleType sample_type) override;

    /// @copydoc IGpaContext::DeleteSession()
    bool DeleteSession(GpaSessionId session_id) override;

    /// @copydoc IGpaContext::GetMaxGpaSessions()
    GpaUInt32 GetMaxGpaSessions() const override;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

    /// @brief Opens the Context.
    ///
    /// @return True if successful otherwise false.
    bool Initialize();

    /// @brief Get the number of instances of the specified block.
    ///
    /// @param [in] block The block whose number of instances is needed.
    ///
    /// @return The number of instances of the specific block. Could be zero if block does not exist.
    GpaUInt32 GetInstanceCount(AmdExtGpuBlock block) const;

    /// @brief Get the max event id of the specified block.
    ///
    /// @param [in] block The block whose max event id is needed.
    ///
    /// @return The max event id of the specified block. Could be zero if block does not exist.
    GpaUInt32 GetMaxEventIdCount(AmdExtGpuBlock block) const;

    /// @brief Obtain the ID3D12Device pointer.
    ///
    /// @return ID3D12Device pointer.
    ID3D12Device* GetD3D12Device() const;

    /// @copydoc IGpaContext::SetStableClocks()
    GpaStatus SetStableClocks(bool use_profiling_clocks) override;

private:
    /// @brief Initializes the AMD Driver extension objects for the context.
    ///
    /// @return True upon successful initialization otherwise false.
    bool InitializeAMDExtension();

    /// @brief Destroys all the allocated resources for the context.
    void CleanUp();

    mutable std::mutex             dx12_gpa_context_mutex_;      ///< Mutex for DX12 GPA Context.
    ID3D12Device*                  d3d12_device_;                ///< D3D12Device pointer.
    IAmdExtD3DFactory*             amd_ext_d3d_factory_object_;  ///< Driver extension object.
    IAmdExtGpaInterface*           gpa_interface_;               ///< The GPA Interface from the driver.
    IAmdExtGpaInterface2*          gpa_interface2_;              ///< The GPA Interface2 from the driver.
    AmdExtPerfExperimentProperties amd_device_props_;            ///< Device properties reported by the driver.
    AmdExtDeviceClockMode          clock_mode_;                  ///< GPU Clock mode.
};

#endif  // GPU_PERF_API_DX12_DX12_GPA_CONTEXT_H_