//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Command List Declarations.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_COMMAND_LIST_H_
#define GPU_PERF_API_COMMON_GPA_COMMAND_LIST_H_

#include <unordered_map>

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/gpa_sample.h"

/// @brief Type alias for pair of client sample id and GPA sample object pointer.
using ClientSampleIdGpaSamplePair = std::pair<ClientSampleId, GpaSample*>;

/// @brief Type alias for map of client sample id and GPA sample object pointer.
using ClientSampleIdGpaSampleUnorderedMap = std::unordered_map<ClientSampleId, GpaSample*>;

/// @brief Class for GPA Command List.
class GpaCommandList : public IGpaCommandList
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] gpa_session GPA session pointer.
    /// @param [in] gpa_pass Pass object pointer.
    /// @param [in] command_list_id Command list id.
    /// @param [in] command_list_type GPA command list type.
    GpaCommandList(IGpaSession* gpa_session, GpaPass* gpa_pass, CommandListId command_list_id, GpaCommandListType command_list_type = kGpaCommandListNone);

    /// @brief Delete default constructor.
    GpaCommandList() = delete;

    /// @brief Virtual Destructor.
    virtual ~GpaCommandList() = default;

    /// @copydoc IGpaCommandList::GetParentSession()
    IGpaSession* GetParentSession() const override;

    /// @copydoc IGpaCommandList::Begin()
    bool Begin() override;

    /// @copydoc IGpaCommandList::End()
    bool End() override;

    /// @copydoc IGpaCommandList::IsCommandListRunning()
    bool IsCommandListRunning() const override;

    /// @copydoc IGpaCommandList::GetPass()
    GpaPass* GetPass() const override;

    /// @copydoc IGpaCommandList::GetSampleCount()
    GpaUInt32 GetSampleCount() const override;

    /// @copydoc IGpaCommandList::BeginSample()
    bool BeginSample(ClientSampleId client_sample_index, GpaSample* sample) override;

    /// @copydoc IGpaCommandList::GetLastSample()
    GpaSample* GetLastSample() const override;

    /// @copydoc IGpaCommandList::GetSample()
    GpaSample* GetSample(ClientSampleId client_sample_id) const override;

    /// @copydoc IGpaCommandList::CloseLastSample()
    bool CloseLastSample(bool closing_by_client) override;

    /// @copydoc IGpaCommandList::IsLastSampleClosed()
    bool IsLastSampleClosed() const override;

    /// @copydoc IGpaCommandList::IsResultReady()
    bool IsResultReady() const override;

    /// @copydoc IGpaCommandList::GetCmdType()
    GpaCommandListType GetCmdType() const override;

    /// @copydoc IGpaInterfaceTrait::ObjectType()
    GpaObjectType ObjectType() const override;

    /// @brief Returns the command list id.
    ///
    /// @return The command list id.
    CommandListId GetId() const;

    /// @brief Iterate over all the samples in the command list.
    ///
    /// @param [in] function Function to be executed for each object in the list. The function may return false to terminate iteration.
    void IterateSampleUnorderedMap(const std::function<bool(ClientSampleIdGpaSamplePair)>& function) const;

private:
    /// @brief Begin API specific command list.
    ///
    /// @return True if successful otherwise false.
    virtual bool BeginCommandListRequest() = 0;

    /// @brief End API specific command list.
    ///
    /// @return True if successful otherwise false.
    virtual bool EndCommandListRequest() = 0;

    /// @brief Begins the sample on the command list.
    ///
    /// @param [in] client_sample_id Index of the sample.
    /// @param [in] gpa_sample The sample to start.
    ///
    /// @return True if sample was successfully begun, false otherwise.
    virtual bool BeginSampleRequest(ClientSampleId client_sample_id, GpaSample* gpa_sample) = 0;

    /// @brief Closes the most recent sample.
    ///
    /// @return True if most recent sample was closed, false otherwise.
    virtual bool CloseLastSampleRequest() = 0;

    /// @brief Add the sample to the command list.
    ///
    /// @param [in] client_sample_id Sample id of the sample.
    /// @param [in] gpa_sample The sample to start.
    void AddSample(ClientSampleId client_sample_id, GpaSample* gpa_sample);

    /// @brief Enum for the state of command list.
    enum class CommandListState
    {
        kUndefined,             ///< Undefined state.
        kSampleRecordingBegin,  ///< Command list is ready to add samples.
        kSampleRecordingEnd,    ///< Command List is closed for adding samples.
    };

    mutable std::mutex                  cmd_list_mutex_;                          ///< Mutex for command list object.
    IGpaSession*                        gpa_session_;                             ///< GPA session.
    GpaPass*                            gpa_pass_;                                ///< GPA Pass.
    GpaSample*                          last_sample_;                             ///< The current open sample on this command list.
    CommandListState                    command_list_state_;                      ///< The command list state.
    ClientSampleIdGpaSampleUnorderedMap client_sample_id_to_gpa_sample_id_umap_;  ///< Unordered map of client sample id and GPA sample object.
    GpaCommandListType                  command_list_type_;                       ///< GPA command list type.
    CommandListId                       command_list_id_;                         ///< The command list id.
};

#endif  // GPU_PERF_API_COMMON_GPA_COMMAND_LIST_H_
