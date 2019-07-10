//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX12 GPA Session declaration
//==============================================================================

#ifndef _DX12_GPA_SESSION_H_
#define _DX12_GPA_SESSION_H_

// AMD DX12 Extension
#pragma warning(push)
#pragma warning(disable : 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning(pop)

// GPA Common
#include "GPASession.h"

class DX12GPAContext;  // forward declaration

/// Class for DX12 GPA Session
class DX12GPASession : public GPASession
{
public:
    /// Constructor
    /// \param[in] pDX12GpaContext DX12 GPA Context
    /// \param[in] sampleType The sample type that will be created on this session
    /// \param[in] pAmdExtGpaSession AMD Extension GpaSession
    DX12GPASession(DX12GPAContext* pDX12GpaContext, GPA_Session_Sample_Type sampleType, IAmdExtGpaInterface* pAmdExtGpaSession);

    /// Delete default constructor
    DX12GPASession() = delete;

    /// Destructor
    virtual ~DX12GPASession();

    /// \copydoc IGPASession::ContinueSampleOnCommandList()
    GPA_Status ContinueSampleOnCommandList(gpa_uint32 srcSampleId, GPA_CommandListId primaryCommandListId) override;

    /// \copydoc IGPASession::CopySecondarySamples()
    GPA_Status CopySecondarySamples(GPA_CommandListId secondaryCmdListId,
                                    GPA_CommandListId primaryCmdListId,
                                    gpa_uint32        numSamples,
                                    gpa_uint32*       pNewSampleIds) override;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// Returns the Amd GPA extension interface
    /// \return amd gpa extension interface
    IAmdExtGpaInterface* GetAmdExtInterface() const;

private:
    /// \copydoc GPASession::CreateAPIPass()
    GPAPass* CreateAPIPass(PassIndex passIndex) override;

    IAmdExtGpaInterface* m_pAmdExtGpaInterface;  ///< AMD Extension Interface
};
#endif  // _DX12_GPA_SESSION_H_
