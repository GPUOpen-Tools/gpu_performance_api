//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief A Vulkan-specific implementation of the GPA Session interface
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_GPA_SESSION_H_
#define GPU_PERF_API_VK_VK_GPA_SESSION_H_

#include "gpu_perf_api_common/gpa_session.h"

class VkGpaCommandList;

/// @brief Vulkan-Specific implementation of the GpaSession.
class VkGpaSession : public GpaSession
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] parent_context_id Pointer to the IGpaContext on which this session is running.
    /// @param [in] sample_type The sample type that will be created on this session.
    VkGpaSession(IGpaContext* parent_context_id, GpaSessionSampleType sample_type);

    /// @brief Delete default constructor.
    VkGpaSession() = delete;

    /// @brief Destructor.
    ~VkGpaSession() = default;

    /// @copydoc GpaSession::GetApiType()
    GpaApiType GetApiType() const override;

    /// @copydoc GpaSession::ContinueSampleOnCommandList(GpaUInt32 src_sample_id, GpaCommandListId primary_command_list_id)
    GpaStatus ContinueSampleOnCommandList(GpaUInt32 src_sample_id, GpaCommandListId primary_command_list_id) override;

    /// @copydoc GpaSession::CopySecondarySamples(GpaCommandListId, GpaCommandListId, GpaUInt32, GpaUInt32*)
    GpaStatus CopySecondarySamples(GpaCommandListId secondary_command_list_id,
                                   GpaCommandListId primary_command_list_id,
                                   GpaUInt32        num_samples,
                                   GpaUInt32*       new_sample_ids) override;

private:
    /// @copydoc GpaSession::CreateApiPass(PassInex)
    std::unique_ptr<GpaPass> CreateApiPass(PassIndex pass_index) override;
};

#endif
