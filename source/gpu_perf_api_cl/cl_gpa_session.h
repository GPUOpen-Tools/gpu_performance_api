//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief CL GPA Session declaration
//==============================================================================

#ifndef _CL_GPA_SESSION_H_
#define _CL_GPA_SESSION_H_

// GPA Common
#include "gpa_session.h"

/// Class for CL GPA Session
class ClGpaSession : public GpaSession
{
public:
    /// Constructor
    /// @param [in] parent_context The context Id on which this session is created
    /// @param [in] sample_type The sample type that will be created on this session
    ClGpaSession(IGpaContext* parent_context, GpaSessionSampleType sample_type);

    /// Destructor
    ~ClGpaSession() = default;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

private:
    /// @copydoc GpaSession::CreateApiPass()
    GpaPass* CreateApiPass(PassIndex pass_index) override;
};
#endif  // _CL_GPA_SESSION_H_
