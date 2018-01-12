//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA DX12 Context declarations
//==============================================================================

#ifndef _DX12_GPA_CONTEXT_H_
#define _DX12_GPA_CONTEXT_H_

// std
#include <map>
#include <mutex>
#include <list>

// AMD Ext
#pragma warning (push)
#pragma warning (disable: 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning (pop)
#include <AmdExtD3D.h>

// GPA Common
#include "GPAContext.h"
#include "GPACommonDefs.h"

class DX12GPASession;   // forward declaration

/// Class for DX12 GPA Context
class GPA_THREAD_SAFE_OBJECT DX12GPAContext : public GPAContext
{
public:

    /// Constructor
    /// \param[in] pD3D12Device ID3D12Device pointer
    /// \param[in] hwInfo hardware info
    /// \param[in] flags context flags
    DX12GPAContext(ID3D12Device* pD3D12Device, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags);

    /// Destructor
    virtual ~DX12GPAContext();

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

    /// Opens the Context
    /// \return true if successful otherwise false
    bool Initialize();

    /// Get the number of instances of the specified block
    /// \param[in] block the block whose number of instances is needed
    /// \return the number of instances of the specific block. Could be zero if block does not exist
    gpa_uint32 GetInstanceCount(AmdExtGpuBlock block) const;

    /// Get the max event id of the specified block
    /// \param[in] block the block whose max event id is needed
    /// \return the max event id of the specified block.  Could be zero if block does not exist
    gpa_uint32 GetMaxEventIdCount(AmdExtGpuBlock block) const;

    /// Returns the ID3D12Device pointer
    /// \return ID3D12Device pointer
    ID3D12Device* GetD3D12Device() const;

private:

    /// Initializes the AMD Driver extension objects for the context
    /// \return true upon successful initialization otherwise false
    bool InitializeAMDExtension();

    /// Destroys all the allocated resources for the context
    void CleanUp();

    /// Enable/disable the stable power state
    /// \param[in] useProfilingClocks true to use GPU clocks for profiling
    void SetStableClocks(bool useProfilingClocks);

    mutable std::mutex                                      m_dx12GpaContextMutex;              ///< Mutex for DX12 GPA Context
    ID3D12Device*                                           m_pD3D12Device;                     ///< D3D12Device pointer
    IAmdExtD3DFactory*                                      m_pAmdExtD3DFactoryObject;          ///< Driver extension object
    IAmdExtGpaInterface*                                    m_pGpaInterface;                    ///< The GPA Interface from the driver
    AmdExtPerfExperimentProperties                          m_amdDeviceProps;                   ///< Device properties reported by the driver
    AmdExtDeviceClockMode                                   m_clockMode;                        ///< GPU Clock mode
};

#endif // _DX12_GPA_CONTEXT_H_
