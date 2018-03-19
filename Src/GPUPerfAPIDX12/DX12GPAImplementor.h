//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 GPA Implementation declarations
//==============================================================================

#ifndef _DX12_GPA_IMPLEMENTOR_H_
#define _DX12_GPA_IMPLEMENTOR_H_

// Common
#include "TSingleton.h"

// GPA Common
#include "GPAImplementor.h"

/// Class for DX12 GPA Implementation
class DX12GPAImplementor : public GPAImplementor, public TSingleton<DX12GPAImplementor>
{
    friend class TSingleton<DX12GPAImplementor>; ///< friend declaration to allow access to the constructor

public:

    /// Destructor
    ~DX12GPAImplementor() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// \copydoc GPAImplementor::GetHwInfoFromAPI
    bool GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const override final;

    /// \copydoc GPAImplementor::VerifyAPIHwSupport
    bool VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const override final;

private:

    /// Constructor
    DX12GPAImplementor() = default;

    /// \copydoc GPAImplementor::OpenAPIContext
    IGPAContext* OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags) override final;

    /// \copydoc GPAImplementor::CloseAPIContext
    bool CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext) override final;

    /// \copydoc GPAImplementor::GetDeviceIdentifierFromContextInfo()
    GPADeviceIdentifier GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const override final;
};

#endif // _DX12_GPA_IMPLEMENTOR_H_
