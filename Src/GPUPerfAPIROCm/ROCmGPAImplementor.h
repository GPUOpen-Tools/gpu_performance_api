//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief ROCm GPA Implementation declarations
//==============================================================================

#ifndef _ROCM_GPA_IMPLEMENTOR_H_
#define _ROCM_GPA_IMPLEMENTOR_H_

// Common
#include "TSingleton.h"

// GPA Common
#include "GPAImplementor.h"

/// Class for ROCm GPA Implementation
class ROCmGPAImplementor : public GPAImplementor, public TSingleton<ROCmGPAImplementor>
{
    friend class TSingleton<ROCmGPAImplementor>;  ///< friend declaration to allow access to the constructor

public:
    /// Destructor
    ~ROCmGPAImplementor() = default;

    /// \copydoc IGPAImplementor::Initialize()
    GPA_Status Initialize(GPA_InitializeFlags flags) override final;

    /// \copydoc IGPAImplementor::Destroy()
    GPA_Status Destroy() override final;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override final;

    /// \copydoc GPAImplementor::GetHwInfoFromAPI
    bool GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const override final;

    /// \copydoc GPAImplementor::VerifyAPIHwSupport
    bool VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const override final;

private:
    /// Constructor
    ROCmGPAImplementor() = default;

    /// \copydoc GPAImplementor::OpenAPIContext
    IGPAContext* OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags) override final;

    /// \copydoc GPAImplementor::CloseAPIContext
    bool CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext) override final;

    /// \copydoc GPAImplementor::GetDeviceIdentifierFromContextInfo()
    GPADeviceIdentifier GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const override final;

    /// Sets the necessary environment variable to enable the HSA runtime and ROC profiler Tools libs
    /// \return true on success
    static bool SetToolsLibEnvVars();

    /// Sets the necessary environment variable to enable ROCP Interception
    /// \param[out] strErrorMsg error message, if env var could not be set
    /// \return true on success
    bool SetROCPInterceptEnvVar(std::string& strErrorMsg) const;

    /// Unsets the necessary environment variable to enable ROCP Interception
    /// \param[out] strErrorMsg error message, if env var could not be unset
    /// \return true on success
    bool UnsetROCPInterceptEnvVar(std::string& strErrorMsg) const;
};

#endif  // _ROCM_GPA_IMPLEMENTOR_H_
