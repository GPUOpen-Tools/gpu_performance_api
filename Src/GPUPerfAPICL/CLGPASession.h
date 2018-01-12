//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief CL GPA Session declaration
//==============================================================================

#ifndef _CL_GPA_SESSION_H_
#define _CL_GPA_SESSION_H_

// GPA Common
#include "GPASession.h"

/// Class for CL GPA Session
class CLGPASession : public GPASession
{
public:

    /// Constructor
    /// \param[in] pParentContext The context Id on which this session is created
    CLGPASession(IGPAContext* pParentContext);

    /// Destructor
    ~CLGPASession();

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

private:

    /// \copydoc GPASession::CreateAPIPass()
    GPAPass* CreateAPIPass(PassIndex passIndex) override;
};
#endif // _CL_GPA_SESSION_H_
