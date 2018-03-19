//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
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
using GPUIndex = unsigned int;                                    ///< type alias for GPU index

/// Class for DirectX 11 GPA Context
class DX11GPAContext : public GPAContext
{
public:

    /// Constructor
    /// \param[in] pD3D11Device ID3D11Device pointer
    /// \param[in] hwInfo hardware info
    /// \param[in] contextFlags context flags
    DX11GPAContext(ID3D11Device* pD3D11Device,
                   GPA_HWInfo& hwInfo,
                   GPA_OpenContextFlags contextFlags);

    /// Destructor
    ~DX11GPAContext();

    /// \copydoc IGPAContext::CreateSession()
    GPA_SessionId CreateSession(GPA_Session_Sample_Type sampleType) override;

    /// \copydoc IGPAContext::DeleteSession()
    bool DeleteSession(GPA_SessionId sessionId) override;

    /// \copydoc IGPAContext::GetMaxGPASessions()
    gpa_uint32 GetMaxGPASessions() const override;

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

    /// Get the index of the acitve GPU
    /// \return Index of the active GPU or ActiveGpuCF if more than 1 GPU is active
    GPUIndex GetActiveGpu() const;

    /// Returns the CF active GPU
    /// \return CF/ACDF active GPU
    GPUIndex GetCFActiveGpu() const;

private:

    /// Initializes the AMD extensions
    /// \return true if the AMD extensions were initialized
    bool InitializeProfileAMDExtension();

    ID3D11Device*         m_pD3D11Device;              ///< DirectX 11 Device pointer
    IAmdDxExt*            m_pDxExt;                    ///< The AMD Dx Extension interface
    IAmdDxExtPerfProfile* m_pDxExtPE;                  ///< The Perf Experiment extension interface
    static const GPUIndex ms_activeGpuCF = 0xffffffff; ///< CF/ACF active GPU
};

#endif // _DX11_GPA_CONTEXT_H_
