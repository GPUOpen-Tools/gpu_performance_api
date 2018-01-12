//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief HSA GPA Session declaration
//==============================================================================

#ifndef _HSA_GPA_SESSION_H_
#define _HSA_GPA_SESSION_H_

// GPA Common
#include "GPASession.h"

/// Class for HSA GPA Session
class HSAGPASession : public GPASession
{
public:

    /// Constructor
    /// \param[in] pParentContext The context Id on which this session is created
    HSAGPASession(IGPAContext* pParentContext);

    /// Destructor
    ~HSAGPASession();

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

private:

    /// \copydoc GPASession::CreateAPIPass()
    GPAPass* CreateAPIPass(PassIndex passIndex) override;
};
#endif // _HSA_GPA_SESSION_H_
