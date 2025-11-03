//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Interface for GPA Command List Object.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_COMMAND_LIST_INTERFACE_H_
#define GPU_PERF_API_COMMON_GPA_COMMAND_LIST_INTERFACE_H_

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_common/gpa_interface_trait_interface.h"
#include "gpu_perf_api_common/gpa_session_interface.h"
#include "gpu_perf_api_common/gpa_pass.h"

/// @brief Interface for GPA Command List.
class IGpaCommandList : public IGpaInterfaceTrait
{
public:
    /// @brief Virtual Destructor.
    virtual ~IGpaCommandList() = default;

    /// @brief Gets the session object on which this CommandList was started.
    ///
    /// @return The session object on which this CommandList was started.
    virtual IGpaSession* GetParentSession() const = 0;

    /// @brief Changes the state of command list to sample recording state.
    ///
    /// @return True if successful otherwise false.
    virtual bool Begin() = 0;

    /// @brief Changes the state of command list from sample recording state to closed state.
    ///
    /// @return True if successful otherwise false.
    virtual bool End() = 0;

    /// @brief Checks whether the command list is running or not.
    ///
    /// @return True if command list is started but not yet ended otherwise false.
    virtual bool IsCommandListRunning() const = 0;

    /// @brief Returns the associated index of the pass.
    ///
    /// @return Index of the pass.
    virtual GpaPass* GetPass() const = 0;

    /// @brief Returns the number of samples created on the command list.
    ///
    /// @return Number of samples.
    virtual GpaUInt32 GetSampleCount() const = 0;

    /// @brief Begins the sample on the command list.
    ///
    /// @param [in] client_sample_index Index of the sample.
    /// @param [in] sample The sample to start.
    ///
    /// @return True if sample was successfully begun, false otherwise.
    virtual bool BeginSample(ClientSampleId client_sample_index, GpaSample* sample) = 0;

    /// @brief Gets the current open sample.
    ///
    /// @return The current open sample or nullptr if no sample is open.
    virtual GpaSample* GetLastSample() const = 0;

    /// @brief Returns the sample with given client sample id if it exists otherwise nullptr.
    ///
    /// @param [in] client_sample_id Client sample id.
    ///
    /// @return Sample id if found, otherwise nullptr.
    virtual GpaSample* GetSample(ClientSampleId client_sample_id) const = 0;

    /// @brief Closes the most recent sample.
    ///
    /// @param [in] closing_by_client Flag indicating if the sample is being closed by the client rather than by GPA itself. Default is true.
    ///
    /// @return True if most recent sample was closed, false otherwise.
    virtual bool CloseLastSample(bool closing_by_client = true) = 0;

    /// @brief Checks whether the last sample has been closed or not.
    ///
    /// @return True if last sample has been closed otherwise false.
    virtual bool IsLastSampleClosed() const = 0;

    /// @brief Checks whether the command list has finished executing and ready for returning the data.
    ///
    /// @return True if command list is finished executing otherwise false.
    virtual bool IsResultReady() const = 0;

    /// @brief Returns the cmd type of the command list.
    ///
    /// @return Cmd type of the command list.
    virtual GpaCommandListType GetCmdType() const = 0;
};

#endif
