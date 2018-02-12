//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX11 GPA Implementation declarations
//==============================================================================

#ifndef _DX11_GPA_IMPLEMENTOR_H_
#define _DX11_GPA_IMPLEMENTOR_H_

#include "DX11Include.h"

// Common
#include "TSingleton.h"

// GPA Common
#include "GPAImplementor.h"

/// Class for DX11 GPA Implementation
class DX11GPAImplementor : public GPAImplementor, public TSingleton<DX11GPAImplementor>
{
    friend class TSingleton<DX11GPAImplementor>;

public:

    /// Destructor
    ~DX11GPAImplementor() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override final;

    /// \copydoc GPAImplementor::GetHwInfoFromAPI
    bool GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const override final;

    /// \copydoc GPAImplementor::VerifyAPIHwSupport
    bool VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const override final;

    /// Returns the AMD extension function pointer
    /// \return DirectX 11 AMD extension function pointer
    PFNAmdDxExtCreate11 GetAmdExtFuncPointer() const;

private:

    /// Returns the AMD hardware info for the given device and monitor
    /// \param[in] pD3D11Device DirectX 11 device pointer
    /// \param[in] hMonitor monitor instance
    /// \param[in] primaryVendorId vendor id
    /// \param[in] primaryDeviceId device id
    /// \param[out] hwInfo hardware info
    /// \return true upon successful operation otherwise false
    bool GetAmdHwInfo(ID3D11Device* pD3D11Device,
                      HMONITOR hMonitor,
                      const int& primaryVendorId,
                      const int& primaryDeviceId,
                      GPA_HWInfo& hwInfo) const;

    /// Constructor
    DX11GPAImplementor();

    /// Initializes the AMD extension function pointer
    /// \return true upon successful initialization otherwise false
    bool InitializeAmdExtFunction() const;

    /// \copydoc GPAImplementor::OpenAPIContext
    IGPAContext* OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags) override final;

    /// \copydoc GPAImplementor::CloseAPIContext
    bool CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pGpaContext) override final;

    /// \copydoc GPAImplementor::GetDeviceIdentifierFromContextInfo()
    GPADeviceIdentifier GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const override final;

    mutable PFNAmdDxExtCreate11     m_amdDxExtCreate11FuncPtr;                  ///< AMD DirectX 11 extension Function pointer
};

#endif // _DX11_GPA_IMPLEMENTOR_H_

