//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Interface for Vulkan-specific GPA Command List Object
//==============================================================================

#ifndef _VK_GPA_COMMAND_LIST_H_
#define _VK_GPA_COMMAND_LIST_H_

#include "VkIncludes.h"
#include "GPACommandList.h"
#include "VkGPASample.h"
#include "VkCommandListSwQueries.h"

class IGPASession;   ///< Predeclared IGPASession
class VkGPASession;  ///< Predeclared VkGPASession

/// Vulkan-specific GPA Command List
class VkGPACommandList : public GPACommandList
{
public:
    /// Constructor
    /// \param[in] pVkGpaSession Vulkan GPA session
    /// \param[in] pPass pass object pointer
    /// \param[in] pCmd VkCommandBuffer pointer
    /// \param[in] commandListId command list id
    /// \param[in] cmdType commnad list type
    VkGPACommandList(VkGPASession* pVkGpaSession, GPAPass* pPass, void* pCmd, CommandListId commandListId, GPA_Command_List_Type cmdType);

    /// Delete default constructor
    VkGPACommandList() = delete;

    /// Destructor
    ~VkGPACommandList();

    /// \copydoc IGPACommandList::IsResultReady()
    bool IsResultReady() const override;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// Accessor to the underlying VkCommandBuffer.
    /// \return The VkCommandBuffer that is represented by this VkGPACommandList.
    VkCommandBuffer GetVkCommandBuffer() const;

    /// Sets the AMD Extension session if it has not already been set.
    /// \param gpaExtSessionAMD The AMD Extension session to use on this command list.
    void SetAmdExtSession(VkGpaSessionAMD gpaExtSessionAMD);

    /// Accessor to the VkGpaSessionAMD that this command buffer is being profiled on.
    /// \return The extension session of this command buffer.
    VkGpaSessionAMD GetAmdExtSession() const;

    /// This should be called on secondary CommandLists, so that they make a copy of their own secondary samples.
    /// \param pPrimaryCmdList the primary command list
    /// \param numSamples the number of samples to be copied
    /// \param pNewSampleIds the array of new sample ids
    /// \param originalSampleIds the vector of original sample ids
    /// \return true if the samples were successfully copied
    bool CopySecondarySamples(VkGPACommandList*            pPrimaryCmdList,
                              gpa_uint32                   numSamples,
                              gpa_uint32*                  pNewSampleIds,
                              std::vector<ClientSampleId>& originalSampleIds);

    /// Gets the AMD Extension Session object that was copied to store the results of the specified clientSampleId.
    /// \param clientSampleId A sample Id supplied to GPA through the GPA_CopySecondarySamples() entrypoint.
    /// \return The VkGpaSessionAMD object that corresponds to the supplied clientSampleId; VK_NULL_HANDLE if no corresponding session exists.
    VkGpaSessionAMD GetCopiedAmdExtSession(ClientSampleId clientSampleId) const;

private:
    /// \copydoc GPACommandList::BeginCommandListRequest()
    bool BeginCommandListRequest() override final;

    /// \copydoc GPACommandList::EndCommandListRequest()
    bool EndCommandListRequest() override final;

    /// \copydoc GPACommandList::BeginSampleRequest()
    bool BeginSampleRequest(ClientSampleId clientSampleId, GPASample* pGpaSample) override final;

    /// \copydoc GPACommandList::CloseLastSampleRequest()
    bool CloseLastSampleRequest() override final;

    /// Struct to hold the original SampleId and copied AMD Extension Session
    /// when CopySecondarySamples() is called. This struct is used in the secondarySamplesMap
    /// to correlate a secondarySampleId with the copied Ext Session and the original sample Id
    /// so that the results can be read back from the driver.
    struct CopiedSampleInfo
    {
        ClientSampleId originalSampleId;  ///< The sampleId that was supplied by the user when the secondary CommandBuffer was recorded.
        VkGpaSessionAMD
            copiedAmdExtSession;  ///< The extension session that was created when CopySecondarySamples() was called; it holds the samples results for one execution of the secondary command buffer.
    };

    VkCommandBuffer m_vkCmdBuffer;  ///< The Vulkan CommandBuffer assocaited with this GPACommandList.
    VkGpaSessionAMD
                           m_gpaExtSessionAMD;  ///< The AMD Extension session that is being used by this command list. The session may also be in use by other CommandLists.
    VkCommandListSwQueries m_swQueries;      ///< The queries that are needed for each software sample (TODO: Should this be in the software sample class?)
    bool       m_isCommandListOpenInDriver;  ///< Flag indicating if the command list has been started in the driver (i.e. if it is in a recording state)
    std::mutex m_vkCommandListMutex;         ///< Mutex to protect vulkan GPA command list object members
    std::list<VkGpaSessionAMD> m_copiedAmdExtSessions;  ///< The list of copied AmdExtSessions that were created for copied samples.
    std::map<ClientSampleId, CopiedSampleInfo>
        m_copiedSampleMap;  ///< Map from the newly assigned client sample id to the original sampleId and copied extension session from which to get the result.
};

#endif  //_VK_GPA_COMMAND_LIST_H_
