//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
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

    /// Constructor
    /// \param[in] pParentContext The context Id on which this session is created
    /// \param[in] sampleType The sample type that will be created on this session
    DX11GPASession(IGPAContext* pParentContext, GPA_Session_Sample_Type sampleType);

    /// Destructor
    ~DX11GPASession() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

private:

    /// \copydoc GPASession::CreateAPIPass()
    GPAPass* CreateAPIPass(PassIndex passIndex) override;
};
#endif // _DX11_GPA_SESSION_H_
