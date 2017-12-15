//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief A Vulkan-specific implementation of the GPA Session interface
//==============================================================================

#ifndef _VK_GPA_SESSION_H_
#define _VK_GPA_SESSION_H_

#include "GPASession.h"
#include "GPACounterSchedulerVK.h"

// Predeclared classes
class VkGPACommandList;

/// Vulkan-Specific implementation of the GPASession
class VkGPASession : public GPASession
{
public:
    /// Deleted default constructor
    VkGPASession() = delete;

    /// Constructor
    /// \param parentContextId Pointer to the IGPAContext on which this session is running
    VkGPASession(IGPAContext* parentContextId);

    /// Destructor
    virtual ~VkGPASession();

    /// \copydoc GPASession::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// \copydoc GPASession::ContinueSampleOnCommandList()
    GPA_Status ContinueSampleOnCommandList(gpa_uint32 srcSampleId, GPA_CommandListId primaryCommandListId) override;

    /// \copydoc GPASession::CopySecondarySamples()
    GPA_Status CopySecondarySamples(GPA_CommandListId secondaryCmdListId, GPA_CommandListId primaryCmdListId, gpa_uint32 numSamples, gpa_uint32* pNewSampleIds) override;

private:

    /// \copydoc GPASession::CreateAPIPass()
    GPAPass* CreateAPIPass(PassIndex passIndex) override;

    mutable std::mutex              m_vkGpasessionMutex;   ///< Mutex for gpa session
    std::list<VkGPACommandList*>    m_vkGpaCmdLists;       ///< List of VkGPACommndLists that are part of this session.
};

#endif // _VK_GPA_SESSION_H_
