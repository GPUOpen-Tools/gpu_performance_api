//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA DX11 Context declarations
//==============================================================================

#ifndef GPU_PERF_API_DX11_DX11_GPA_CONTEXT_H_
#define GPU_PERF_API_DX11_DX11_GPA_CONTEXT_H_

#include <list>

#include "gpu_perf_api_common/gpa_context.h"

#include "gpu_perf_api_dx11/dx11_include.h"

class Dx11GpaSession;  // Forward declaration.

using Dx11GpaSessionList = std::list<Dx11GpaSession*>;  ///< Type alias for list of DX11GPASession objects.
using GpuIndex           = unsigned int;                ///< Type alias for GPU index.

/// @brief Class for DirectX 11 GPA Context.
class Dx11GpaContext : public GpaContext
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] d3d11_device ID3D11Device pointer.
    /// @param [in] hw_info Hardware info.
    /// @param [in] context_flags Context flags.
    Dx11GpaContext(ID3D11Device* d3d11_device, GpaHwInfo& hw_info, GpaOpenContextFlags context_flags);

    /// @brief Destructor.
    ~Dx11GpaContext();

    /// @copydoc IGpaContext::CreateSession()
    GpaSessionId CreateSession(GpaSessionSampleType sample_type) override;

    /// @copydoc IGpaContext::DeleteSession()
    bool DeleteSession(GpaSessionId session_id) override;

    /// @copydoc IGpaContext::GetMaxGpaSessions()
    GpaUInt32 GetMaxGpaSessions() const override;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

    /// @brief Initializes the DirectX 11 context.
    ///
    /// @return True if initialization is successful otherwise false.
    bool Initialize();

    /// @brief Returns the AMD Dx extension.
    ///
    /// @return AMD Dx extension.
    IAmdDxExt* GetAmdDxExtension() const;

    /// @brief Returns the AMD profile extension.
    ///
    /// @return AMD Profile extension.
    IAmdDxExtPerfProfile* GetAmdProfileExtension() const;

    /// @brief Returns the DirectX 11 device.
    ///
    /// @return DirectX 11 device pointer.
    ID3D11Device* GetDevice() const;

    /// @brief Get the index of the active GPU.
    ///
    /// @return Index of the active GPU or ActiveGpuCF if more than 1 GPU is active.
    GpuIndex GetActiveGpu() const;

    /// @brief Returns the CF active GPU.
    ///
    /// @return CF/ACDF active GPU.
    GpuIndex GetCfActiveGpu() const;

    /// @brief Get the number of instances of the specified block.
    ///
    /// @param [in] block The block whose number of instances is needed.
    ///
    /// @return The number of instances of the specific block. Could be zero if block does not exist.
    GpaUInt32 GetInstanceCount(PE_BLOCK_ID block) const;

    /// @brief Get the max event id of the specified block.
    ///
    /// @param [in] block The block whose max event id is needed.
    ///
    /// @return The max event id of the specified block. Could be zero if block does not exist.
    GpaUInt32 GetMaxEventIdCount(PE_BLOCK_ID block) const;

    /// @copydoc IGpaContext::SetStableClocks()
    GpaStatus SetStableClocks(bool use_profiling_clocks) override;

private:
    /// @brief Initializes the AMD extensions.
    ///
    /// @return True if the AMD extensions were initialized.
    bool InitializeProfileAMDExtension();

    ID3D11Device*         d3d11_device_;                         ///< DirectX 11 Device pointer.
    IAmdDxExt*            dx_ext_;                               ///< The AMD Dx Extension interface.
    IAmdDxExtPerfProfile* dx_ext_pe_;                            ///< The performance Experiment extension interface.
    static const GpuIndex kActiveGpuCf = 0xffffffff;             ///< CF/ACF active GPU.
    PE_BLOCK_COUNTER_INFO block_counter_info_[PE_BLOCK_ID_MAX];  ///< Block counter info.
    bool                  block_info_init_[PE_BLOCK_ID_MAX];     ///< Flags indicating the block info has been initialized or not.
    PE_CAPS_INFO          gpu_caps_;                             ///< GPU capabilities.
    PE_CLOCK_MODE         clock_mode_;                           ///< GPU Clock mode.
};

#endif  // GPU_PERF_API_DX11_DX11_GPA_CONTEXT_H_
