//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL GPA Command List Declarations
//==============================================================================

#ifndef GPU_PERF_API_GL_GPA_COMMAND_LIST_H_
#define GPU_PERF_API_GL_GPA_COMMAND_LIST_H_

#include "gpu_perf_api_common/gpa_command_list.h"

#include "gpu_perf_api_gl/gl_gpa_sample.h"

/// @brief Class for GL GPA Command List.
class GlGpaCommandList : public GpaCommandList
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] gpa_session GPA session pointer.
    /// @param [in] gpa_pass pass object pointer.
    /// @param [in] command_list_id command list id.
    GlGpaCommandList(IGpaSession* gpa_session, GpaPass* gpa_pass, CommandListId command_list_id);

    /// @brief Delete default constructor.
    GlGpaCommandList() = delete;

    /// @brief Destructor.
    ~GlGpaCommandList() = default;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

private:
    /// @copydoc GpaCommandList::BeginCommandListRequest()
    bool BeginCommandListRequest() override final;

    /// @copydoc GpaCommandList::EndCommandListRequest()
    bool EndCommandListRequest() override final;

    /// @copydoc GpaCommandList::BeginSampleRequest()
    bool BeginSampleRequest(ClientSampleId client_sample_id, GpaSample* gpa_sample) override final;

    /// @copydoc GpaCommandList::CloseLastSampleRequest()
    bool CloseLastSampleRequest() override final;

    GlGpaSample* previous_sample_;  ///< Previous GL sample request.
};

#endif
