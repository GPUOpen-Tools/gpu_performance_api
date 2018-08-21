//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
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

#include "DX12GPAContext.h"

/// Class for DX12 GPA Implementation
class DX12GPAImplementor : public GPAImplementor, public TSingleton<DX12GPAImplementor>
{
    friend class TSingleton<DX12GPAImplementor>; ///< friend declaration to allow access to the constructor

public:

    /// Destructor
    ~DX12GPAImplementor();

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// \copydoc GPAImplementor::GetHwInfoFromAPI
    bool GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const override final;

    /// \copydoc GPAImplementor::VerifyAPIHwSupport
    bool VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const override final;

    /// \copydoc IGPAImplementor::Destroy()
    GPA_Status Destroy() override;

    /// \copydoc IGPAImplementor::IsCommandListRequired()
    bool IsCommandListRequired() const override;

    /// \copydoc IGPAImplementor::IsContinueSampleOnCommandListSupported()
    bool IsContinueSampleOnCommandListSupported() const override;

    /// \copydoc IGPAImplementor::IsCopySecondarySampleSupported()
    bool IsCopySecondarySampleSupported() const override;

private:

    /// Constructor
    DX12GPAImplementor() = default;

    /// \copydoc GPAImplementor::OpenAPIContext
    IGPAContext* OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags) override final;

    /// \copydoc GPAImplementor::CloseAPIContext
    bool CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext) override final;

    /// \copydoc GPAImplementor::GetDeviceIdentifierFromContextInfo()
    GPADeviceIdentifier GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const override final;

    /// Deletes the GPA contexts
    void DeleteContexts();

    std::vector<DX12GPAContext*> m_dx12GpaContextList; ///< DX12 GPA context list for housekeeping
};

#endif // _DX12_GPA_IMPLEMENTOR_H_
