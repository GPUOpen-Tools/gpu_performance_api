//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 GPA Session declaration
//==============================================================================

#ifndef GPU_PERF_API_DX11_DX11_GPA_SESSION_H_
#define GPU_PERF_API_DX11_DX11_GPA_SESSION_H_

#include "gpu_perf_api_common/gpa_session.h"

class Dx11GpaCommandList;  // Forward declaration.
class Dx11GpaContext;      // Forward declaration.

/// @brief Class for DX11 GPA Session.
class Dx11GpaSession : public GpaSession
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] parent_context The context Id on which this session is created.
    /// @param [in] sample_type The sample type that will be created on this session.
    Dx11GpaSession(IGpaContext* parent_context, GpaSessionSampleType sample_type);

    /// @brief Destructor.
    ~Dx11GpaSession() = default;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

private:
    /// @copydoc GpaSession::CreateApiPass()
    GpaPass* CreateApiPass(PassIndex pass_index) override;
};
#endif  // GPU_PERF_API_DX11_DX11_GPA_SESSION_H_
