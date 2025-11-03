//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL GPA Session declaration
//==============================================================================

#ifndef GPU_PERF_API_GL_GL_GPA_SESSION_H_
#define GPU_PERF_API_GL_GL_GPA_SESSION_H_

#include "gpu_perf_api_common/gpa_session.h"

/// @brief Class for GL GPA Session.
class GlGpaSession : public GpaSession
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] parent_context The context Id on which this session is created.
    /// @param [in] sample_type The sample type that will be created on this session.
    GlGpaSession(IGpaContext* parent_context, GpaSessionSampleType sample_type);

    /// @brief Destructor.
    ~GlGpaSession() = default;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

private:
    /// @copydoc GpaSession::CreateApiPass()
    GpaPass* CreateApiPass(PassIndex pass_index) override;
};
#endif
