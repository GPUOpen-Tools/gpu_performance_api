//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_DX11_DX11_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_DX11_DX11_GPA_IMPLEMENTOR_H_

#include "TSingleton.h"

#include "gpu_perf_api_common/gpa_implementor.h"

#include "gpu_perf_api_dx11/dx11_include.h"

/// @brief Class for DX11 GPA Implementation.
class Dx11GpaImplementor : public GpaImplementor, public TSingleton<Dx11GpaImplementor>
{
    friend class TSingleton<Dx11GpaImplementor>;  ///< Friend declaration to allow access to the constructor.

public:
    /// @brief Destructor.
    virtual ~Dx11GpaImplementor() = default;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override final;

    /// @copydoc GpaImplementor::GetHwInfoFromApi()
    bool GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const override final;

    /// @copydoc GpaImplementor::VerifyApiHwSupport()
    bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hw_info) const override final;

    /// @brief Returns the AMD extension function pointer.
    //
    /// @return DirectX 11 AMD extension function pointer.
    PFNAmdDxExtCreate11 GetAmdExtFuncPointer() const;

private:
    /// @brief Returns the AMD hardware info for the given device and monitor.
    ///
    /// @param [in] d3d11_device DirectX 11 device pointer.
    /// @param [in] primary_vendor_id Vendor id.
    /// @param [in] primary_device_id Device id.
    /// @param [out] hw_info Hardware info.
    ///
    /// @return True upon successful operation otherwise false.
    bool GetAmdHwInfo(ID3D11Device* d3d11_device, const int& primary_vendor_id, const int& primary_device_id, GpaHwInfo& hw_info) const;

    /// @brief Constructor.
    Dx11GpaImplementor();

    /// @brief Initializes the AMD extension function pointer.
    ///
    /// @return True upon successful initialization otherwise false.
    bool InitializeAmdExtFunction() const;

    /// @copydoc GpaImplementor::OpenApiContext(GpaContextInfoPtr, GpaHwInfo&, GpaOpenContextFlags)
    IGpaContext* OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags) override final;

    /// @copydoc GpaImplementor::CloseApiContext(IGpaContext*)
    [[nodiscard]] bool CloseApiContext(IGpaContext* context) override final;

    /// @copydoc GpaImplementor::GetDeviceIdentifierFromContextInfo()
    GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const override final;

    mutable PFNAmdDxExtCreate11 amd_dx_ext_create11_func_ptr_;  ///< AMD DirectX 11 extension Function pointer.
};

#endif
