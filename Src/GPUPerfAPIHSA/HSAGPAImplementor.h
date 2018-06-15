//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief HSA GPA Implementation declarations
//==============================================================================

#ifndef _HSA_GPA_IMPLEMENTOR_H_
#define _HSA_GPA_IMPLEMENTOR_H_

// Common
#include "TSingleton.h"

// GPA Common
#include "GPAImplementor.h"

/// Class for HSA GPA Implementation
class HSAGPAImplementor : public GPAImplementor, public TSingleton<HSAGPAImplementor>
{
    friend class TSingleton<HSAGPAImplementor>; ///< friend declaration to allow access to the constructor

public:

    /// Destructor
    ~HSAGPAImplementor() = default;

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
    HSAGPAImplementor() = default;

    /// \copydoc GPAImplementor::OpenAPIContext
    IGPAContext* OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags) override final;

    /// \copydoc GPAImplementor::CloseAPIContext
    bool CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext) override final;

    /// \copydoc GPAImplementor::GetDeviceIdentifierFromContextInfo()
    GPADeviceIdentifier GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const override final;

    /// Sets the necessary environment variable to enable the HSA runtime Tools lib
    /// \return true on success
    bool SetHSAToolsLibEnvVar() const;

    /// Sets the necessary environment variable to enable SoftCP mode
    /// \param[out] strErrorMsg error message, if env var could not be set
    /// \return true on success
    bool SetHSASoftCPEnvVar(std::string& strErrorMsg) const;

    /// Unsets the necessary environment variable to enable SoftCP mode
    /// \param[out] strErrorMsg error message, if env var could not be unset
    /// \return true on success
    bool UnsetHSASoftCPEnvVar(std::string strErrorMsg) const;
};

#endif // _HSA_GPA_IMPLEMENTOR_H_
