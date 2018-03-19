//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  VK GPA Implementation declarations
//==============================================================================

#ifndef _VK_GPA_IMPLEMENTOR_H_
#define _VK_GPA_IMPLEMENTOR_H_

// Common
#include "TSingleton.h"

// GPA Common
#include "GPAImplementor.h"
#include "VkGPAContext.h"

/// Class for Vulkan GPA Implementation
class VkGPAImplementor : public GPAImplementor, public TSingleton<VkGPAImplementor>
{
public:
    /// Constructor
    VkGPAImplementor() = default;

    /// Destructor
    ~VkGPAImplementor() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// \copydoc GPAImplementor::GetHwInfoFromAPI
    bool GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const override final;

    /// \copydoc GPAImplementor::VerifyAPIHwSupport
    bool VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const override final;

private:

    /// Stores the instance that this GPA implementation is using.
    VkInstance m_vkInstance;

    /// \copydoc GPAImplementor::OpenAPIContext
    IGPAContext* OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags) override final;

    /// \copydoc GPAImplementor::CloseAPIContext
    bool CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext) override final;

    /// \copydoc GPAImplementor::GetDeviceIdentifierFromContextInfo()
    GPADeviceIdentifier GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const override final;
};

#endif // _VK_GPA_IMPLEMENTOR_H_
