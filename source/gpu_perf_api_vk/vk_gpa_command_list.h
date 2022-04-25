//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Interface for Vulkan-specific GPA Command List Object
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_GPA_COMMAND_LIST_H_
#define GPU_PERF_API_VK_VK_GPA_COMMAND_LIST_H_

#include "gpu_perf_api_common/gpa_command_list.h"

#include "gpu_perf_api_vk/vk_command_list_sw_queries.h"
#include "gpu_perf_api_vk/vk_gpa_sample.h"
#include "gpu_perf_api_vk/vk_includes.h"

class IGpaSession;   ///< Predeclared IGpaSession.
class VkGpaSession;  ///< Predeclared VkGpaSession.

/// @brief Vulkan-specific GPA Command List
class VkGpaCommandList : public GpaCommandList
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] vk_gpa_session Vulkan GPA session.
    /// @param [in] pass Pass object pointer.
    /// @param [in] command VkCommandBuffer pointer.
    /// @param [in] command_list_id Command list id.
    /// @param [in] command_type Commnad list type.
    VkGpaCommandList(VkGpaSession* vk_gpa_session, GpaPass* pass, void* command, CommandListId command_list_id, GpaCommandListType command_type);

    /// @brief Delete default constructor.
    VkGpaCommandList() = delete;

    /// @brief Destructor.
    ~VkGpaCommandList();

    /// @copydoc IGpaCommandList::IsResultReady()
    bool IsResultReady() const override;

    /// @copydoc IGpaInterfaceTrait::GetAPIType()
    GpaApiType GetApiType() const override;

    /// @brief Accessor to the underlying VkCommandBuffer.
    ///
    /// @return The VkCommandBuffer that is represented by this VkGpaCommandList.
    VkCommandBuffer GetVkCommandBuffer() const;

    /// @brief Sets the AMD Extension session if it has not already been set.
    ///
    /// @param amd_extension_session The AMD Extension session to use on this command list.
    void SetAmdExtSession(VkGpaSessionAMD amd_extension_session);

    /// @brief Accessor to the VkGpaSessionAMD that this command buffer is being profiled on.
    ///
    /// @return The extension session of this command buffer.
    VkGpaSessionAMD GetAmdExtSession() const;

    /// @brief This should be called on secondary CommandLists, so that they make a copy of their own secondary samples.
    ///
    /// @param [in] primary_command_list The primary command list.
    /// @param [in] num_samples The number of samples to be copied.
    /// @param [in] new_sample_ids The array of new sample ids.
    /// @param [in] original_sample_ids The vector of original sample ids.
    ///
    /// @return True if the samples were successfully copied.
    bool CopySecondarySamples(VkGpaCommandList*            primary_command_list,
                              GpaUInt32                    num_samples,
                              GpaUInt32*                   new_sample_ids,
                              std::vector<ClientSampleId>& original_sample_ids);

    /// @brief Gets the AMD Extension Session object that was copied to store the results of the specified client_sample_id.
    ///
    /// @param [in] client_sample_id A sample Id supplied to GPA through the GPA_CopySecondarySamples() entrypoint.
    ///
    /// @return The VkGpaSessionAMD object that corresponds to the supplied client_sample_id; VK_NULL_HANDLE if no corresponding session exists.
    VkGpaSessionAMD GetCopiedAmdExtSession(ClientSampleId client_sample_id) const;

private:
    /// @copydoc GPACommandList::BeginCommandListRequest()
    bool BeginCommandListRequest() override final;

    /// @copydoc GPACommandList::EndCommandListRequest()
    bool EndCommandListRequest() override final;

    /// @copydoc GPACommandList::BeginSampleRequest()
    bool BeginSampleRequest(ClientSampleId client_sample_id, GpaSample* gpa_sample) override final;

    /// @copydoc GPACommandList::CloseLastSampleRequest()
    bool CloseLastSampleRequest() override final;

    /// @brief Struct to hold the original SampleId and copied AMD Extension Session when CopySecondarySamples() is called.
    ///
    /// This struct is used in the secondarySamplesMap to correlate a secondarySampleId with the copied Ext Session and the original sample Id
    /// so that the results can be read back from the driver.
    struct CopiedSampleInfo
    {
        /// The sampleId that was supplied by the user when the secondary CommandBuffer was recorded.
        ClientSampleId original_sample_id;

        /// The extension session that was created when CopySecondarySamples() was called.
        /// It holds the samples results for one execution of the secondary command buffer.
        VkGpaSessionAMD copied_amd_ext_session;
    };

    /// The Vulkan CommandBuffer assocaited with this GPACommandList.
    VkCommandBuffer vk_command_buffer_;

    /// The AMD Extension session that is being used by this command list. The session may also be in use by other CommandLists.
    VkGpaSessionAMD gpa_ext_session_command_list_;

    /// The queries that are needed for each software sample.
    VkCommandListSwQueries sw_queries_;

    /// Flag indicating if the command list has been started in the driver (i.e. if it is in a recording state).
    bool is_command_list_open_in_driver_;

    /// Mutex to protect vulkan GPA command list object members.
    std::mutex vk_command_list_mutex_;

    /// The list of copied AmdExtSessions that were created for copied samples.
    std::list<VkGpaSessionAMD> copied_amd_extensions_;

    /// Map from the newly assigned client sample id to the original sampleId and copied extension session from which to get the result.
    std::map<ClientSampleId, CopiedSampleInfo> copied_sample_map_;
};

#endif  // GPU_PERF_API_VK_VK_GPA_COMMAND_LIST_H_
