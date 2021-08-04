//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 GPA Command List Declarations
//==============================================================================

#ifndef GPU_PERF_API_DX11_DX11_GPA_COMMAND_LIST_H_
#define GPU_PERF_API_DX11_DX11_GPA_COMMAND_LIST_H_

#include "gpu_perf_api_common/gpa_command_list.h"

/// @brief Class for DX11 GPA Command List.
class Dx11GpaCommandList : public GpaCommandList
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] gpa_session GPA session pointer.
    /// @param [in] gpa_pass Pass object pointer.
    /// @param [in] command_list_id Command list id.
    Dx11GpaCommandList(IGpaSession* gpa_session, GpaPass* gpa_pass, CommandListId command_list_id);

    /// @brief Delete default constructor.
    Dx11GpaCommandList() = delete;

    /// @brief Destructor.
    ~Dx11GpaCommandList() = default;

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
};

#endif  // GPU_PERF_API_DX11_DX11_GPA_COMMAND_LIST_H_
