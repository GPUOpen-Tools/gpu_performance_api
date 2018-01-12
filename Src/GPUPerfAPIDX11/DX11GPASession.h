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
    DX11GPASession(IGPAContext* pParentContext);

    /// Destructor
    ~DX11GPASession();

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

private:

    /// \copydoc GPASession::CreateAPIPass()
    GPAPass * CreateAPIPass(PassIndex passIndex) override;
};
#endif // _DX11_GPA_SESSION_H_
