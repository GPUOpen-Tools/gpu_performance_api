//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief CL GPA Implementation declarations
//==============================================================================

#ifndef _CL_GPA_IMPLEMENTOR_H_
#define _CL_GPA_IMPLEMENTOR_H_

// Common
#include "TSingleton.h"

// GPA Common
#include "GPAImplementor.h"

/// Class for CL GPA Implementation
class CLGPAImplementor : public GPAImplementor, public TSingleton<CLGPAImplementor>
{
    friend class TSingleton<CLGPAImplementor>;  ///< friend declaration to allow access to the constructor

public:
    /// Destructor
    ~CLGPAImplementor() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override final;

    /// \copydoc GPAImplementor::GetHwInfoFromAPI
    bool GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const override final;

    /// \copydoc GPAImplementor::VerifyAPIHwSupport
    bool VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const override final;

private:
    /// Constructor
    CLGPAImplementor() = default;

    /// \copydoc GPAImplementor::OpenAPIContext
    IGPAContext* OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags) override final;

    /// \copydoc GPAImplementor::CloseAPIContext
    bool CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext) override final;

    /// \copydoc GPAImplementor::GetDeviceIdentifierFromContextInfo()
    GPADeviceIdentifier GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const override final;

    bool m_initPerfCounterAMDExtension = false;  ///< flag indicating if the CL extension function pointers have been initialized
};

#endif  // _CL_GPA_IMPLEMENTOR_H_
