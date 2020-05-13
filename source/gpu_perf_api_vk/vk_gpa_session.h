//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief A Vulkan-specific implementation of the GPA Session interface
//==============================================================================

#ifndef _VK_GPA_SESSION_H_
#define _VK_GPA_SESSION_H_

#include "gpa_session.h"

// Predeclared classes
class VkGPACommandList;

/// Vulkan-Specific implementation of the GPASession
class VkGPASession : public GPASession
{
public:
    /// Constructor
    /// \param parentContextId Pointer to the IGPAContext on which this session is running
    /// \param[in] sampleType The sample type that will be created on this session
    VkGPASession(IGPAContext* parentContextId, GPA_Session_Sample_Type sampleType);

    /// Delete default constructor
    VkGPASession() = delete;

    /// Destructor
    ~VkGPASession() = default;

    /// \copydoc GPASession::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// \copydoc GPASession::ContinueSampleOnCommandList()
    GPA_Status ContinueSampleOnCommandList(gpa_uint32 srcSampleId, GPA_CommandListId primaryCommandListId) override;

    /// \copydoc GPASession::CopySecondarySamples()
    GPA_Status CopySecondarySamples(GPA_CommandListId secondaryCmdListId,
                                    GPA_CommandListId primaryCmdListId,
                                    gpa_uint32        numSamples,
                                    gpa_uint32*       pNewSampleIds) override;

private:
    /// \copydoc GPASession::CreateAPIPass()
    GPAPass* CreateAPIPass(PassIndex passIndex) override;
};

#endif  // _VK_GPA_SESSION_H_
