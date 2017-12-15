//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX11 GPA Session declaration
//==============================================================================

#ifndef _DX11_GPA_SESSION_H_
#define _DX11_GPA_SESSION_H_

// GPA Common
#include "GPASession.h"

class DX11GPACommandList;   // forward declaration
class DX11GPAContext;   // forward declaration

/// Class for DX11 GPA Session
class DX11GPASession : public GPASession
{
public:

    /// Destructor
    ~DX11GPASession();

    /// \copydoc IGPASession::Begin()
    bool Begin() override;

    /// \copydoc IGPASession::End()
    bool End() override;

    /// \copydoc IGPASession::CreateCommandList()
    GPA_CommandListId CreateCommandList(gpa_uint32 passIndex, void* pCmd, GPA_Command_List_Type cmdType) override;

    /// \copydoc IGPASession::BeginSample()
    bool BeginSample(ClientSampleId sampleId, GPA_CommandListId commandListId) override;

    /// \copydoc IGPASession::EndSample()
    bool EndSample(GPA_CommandListId commandListId) override;

    /// \copydoc IGPASession::GetSampleCount()
    gpa_uint32 GetSampleCount() const override;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;
};
#endif // _DX11_GPA_SESSION_H_
