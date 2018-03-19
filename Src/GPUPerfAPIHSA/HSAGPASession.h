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
    /// \param[in] sampleType The sample type that will be created on this session
    HSAGPASession(IGPAContext* pParentContext, GPA_Session_Sample_Type sampleType);

    /// Destructor
    ~HSAGPASession() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

private:

    /// \copydoc GPASession::CreateAPIPass()
    GPAPass* CreateAPIPass(PassIndex passIndex) override;
};
#endif // _HSA_GPA_SESSION_H_
