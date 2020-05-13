//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GL GPA Implementation declarations
//==============================================================================

#ifndef _GL_GPA_IMPLEMENTOR_H_
#define _GL_GPA_IMPLEMENTOR_H_

// Common
#include "TSingleton.h"

// GPA Common
#include "gpa_implementor.h"

/// Class for GL GPA Implementation
class GLGPAImplementor : public GPAImplementor, public TSingleton<GLGPAImplementor>
{
    friend class TSingleton<GLGPAImplementor>;  ///< friend declaration to allow access to the constructor

public:
    /// Destructor
    ~GLGPAImplementor() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override final;

    /// \copydoc GPAImplementor::GetHwInfoFromAPI
    bool GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const override final;

    /// \copydoc GPAImplementor::VerifyAPIHwSupport
    bool VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const override final;

private:
    /// Constructor
    GLGPAImplementor();

    /// \copydoc GPAImplementor::OpenAPIContext
    IGPAContext* OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags) override final;

    /// \copydoc GPAImplementor::CloseAPIContext
    bool CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext) override final;

    /// \copydoc GPAImplementor::GetDeviceIdentifierFromContextInfo()
    GPADeviceIdentifier GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const override final;

    mutable bool m_isGlEntryPointsInitialized;  ///< flag indicating the GL entry point has been initialized or not
    mutable int  m_glDriverVersion;             ///< GL driver version returned in the asic info
};

#endif  // _GL_GPA_IMPLEMENTOR_H_
