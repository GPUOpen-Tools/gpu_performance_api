//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA DX11 Context declarations
//==============================================================================

#ifndef _DX11_GPA_CONTEXT_H_
#define _DX11_GPA_CONTEXT_H_

// std
#include <list>

#include "DX11Include.h"

// GPA Common
#include "GPAContext.h"

class DX11GPASession;           // forward Declaration

using DX11GPASessionList = std::list<DX11GPASession*>;            ///< type alias for list of DX11GPASession objects

/// Class for DirectX 11 GPA Context
class DX11GPAContext : public GPAContext
{
public:

    /// Constructor
    DX11GPAContext(ID3D11Device* pD3D11Device, GPA_HWInfo& pHwInfo, GPA_OpenContextFlags contextFlags);

    /// Destructor
    ~DX11GPAContext();

    /// \copydoc IGPAContext::CreateSession()
    GPA_SessionId CreateSession() override;

    /// \copydoc IGPAContext::DeleteSession()
    bool DeleteSession(GPA_SessionId pSessionId) override;

    /// \copydoc IGPAContext::GetMaxGPASessions()
    gpa_uint32 GetMaxGPASessions() const override;

    /// \copydoc IGPAContext::DoesSessionExist()
    bool DoesSessionExist(GPA_SessionId pSessionId) const override;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// Initializes the DirectX 11 context
    /// \return true if initialization is successful otherwise false
    bool Initialize();

    /// Returns the AMD Dx extension
    /// \return AMD Dx extension
    IAmdDxExt* GetAmdDxExtension() const;

    /// Returns the AMD profile extension
    /// \return AMD Profile extension
    IAmdDxExtPerfProfile* GetAmdProfileExtension() const;

    /// Returns the DirectX 11 device
    /// \return DirectX 11 device pointer
    ID3D11Device* GetDevice() const;

private:

    /// Initializes the AMD extensions
    bool InitializeProfileAMDExtension();

    ID3D11Device*                           m_pD3D11Device;         ///< DirectX 11 Device pointer
    IAmdDxExt*                              m_pDxExt;               ///< The AMD Dx Extension interface
    IAmdDxExtPerfProfile*                   m_pDxExtPE;             ///< The Perf Experiment extension interface
};

#endif // _DX11_GPA_CONTEXT_H_
