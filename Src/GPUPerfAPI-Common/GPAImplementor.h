//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Common GPA Implementation declarations
//==============================================================================

#ifndef _GPA_IMPLEMENTOR_H_
#define _GPA_IMPLEMENTOR_H_

// std
#include <mutex>

// GPA Common
#include "IGPAImplementor.h"
#include "IGPAContext.h"

using GPAContextInfoPtr = void*;                                                               ///< type alias for context info pointer
using GPADeviceIdentifier = void*;                                                             ///< type alias for API-specific device identifier
using GPADeviceIdentifierGPAContextPair = std::pair<GPADeviceIdentifier, IGPAContext*>;        ///< type alias for application and GPA context pair
using GPADeviceIdentifierGPAContextMap = std::map<GPADeviceIdentifier, IGPAContext*>;          ///< type alias for application and GPA context map

/// Class for common GPA Implementation
class GPAImplementor : public IGPAImplementor
{
public:

    /// Constructor
    GPAImplementor();

    /// Destructor
    ~GPAImplementor() = default;

    /// \copydoc IGPAImplementor::Initialize()
    GPA_Status Initialize(GPA_InitializeFlags flags) override;

    /// \copydoc IGPAImplementor::Destroy()
    GPA_Status Destroy() override;

    /// \copydoc IGPAImplementor::OpenContext()
    GPA_Status OpenContext(void* pContext,
                           GPA_OpenContextFlags flags,
                           GPA_ContextId* pContextId) override;

    /// \copydoc IGPAImplementor::CloseContext()
    GPA_Status CloseContext(GPA_ContextId contextId) override;

    /// \copydoc IGPAImplementor::ObjectType()
    GPAObjectType ObjectType() const override;

    /// \copydoc IGPAImplementor::DoesContextExist()
    bool DoesContextExist(GPA_ContextId contextId) const override;

    /// \copydoc IGPAImplementor::DoesSessionExist()
    bool DoesSessionExist(GPA_SessionId sessionId) const override;

    /// \copydoc IGPAImplementor::DoesCommandListExist()
    bool DoesCommandListExist(GPA_CommandListId commandListId) const override;

    /// \copydoc IGPAImplementor::GetInitializeFlags()
    GPA_InitializeFlags GetInitializeFlags() const override;

protected:

    /// Checks whether the device is supported
    /// \param[in] pContextInfo context info pointer
    /// \param[out] pHwInfo hardware information if device is supported
    /// \return GPA_STATUS_OK if operation is successful
    GPA_Status IsDeviceSupported(GPAContextInfoPtr pContextInfo, GPA_HWInfo* pHwInfo) const;

    /// Gets the API level hardware info
    /// \param[in] pContextInfo context info pointer
    /// \param[out] hwInfo hardware info
    /// \return true if operation is successful otherwise false
    virtual bool GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const = 0;

    /// Compares two hardware info objects
    /// \param[in] first first hardware info
    /// \param[in] second second hardware info
    /// \return true if the hardware info objects are identical, otherwise false
    virtual bool CompareHwInfo(const GPA_HWInfo& first, const GPA_HWInfo& second) const;

    /// Verifies the API level hardware support
    /// \param[in] pContextInfo context info object pointer
    /// \param[in] hwInfo hardware info
    /// \return true if API supports the hardware otherwise false
    virtual bool VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const = 0;

    /// Checks whether the context info exists or not
    /// \param[in] pContextInfo context info pointer
    /// \return true if context exist otherwise false
    bool DoesContextInfoExist(GPAContextInfoPtr pContextInfo) const;

private:

    /// Performs the API-specific tasks needed to open a context
    /// \param[in] pContextInfo context info pointer
    /// \param[in] hwInfo hardware info
    /// \param[in] flags context flags
    /// \return IGPAContext pointer if operation is successful otherwise nullptr
    virtual IGPAContext* OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags) = 0;

    /// Performs the API-specific tasks needed to close the context and release the relevant resources
    /// \param[in] pDeviceIdentifier API-Specific device indentifier
    /// \param[in] pContext context object pointer
    /// \return true if closing of the context was successful otherwise false
    virtual bool CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext) = 0;

    /// Returns the API specific device identifier
    /// \param[in] pContextInfo pointer to context info
    /// \return device identifier for the passed context info
    virtual GPADeviceIdentifier GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const = 0;

    mutable std::mutex               m_deviceGpaContextMapMutex;    ///< mutex for context manager
    GPADeviceIdentifierGPAContextMap m_appContextInfoGpaContextMap; ///< map of application context info and GPA context
    bool                             m_isInitialized;               ///< flag indicating if GPA has been initalized or not
    GPA_InitializeFlags              m_initFlags;                   ///< flags specified when initializing GPA
};

#endif // _GPA_IMPLEMENTOR_H_

