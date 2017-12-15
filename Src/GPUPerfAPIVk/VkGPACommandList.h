//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Interface for Vulkan-specific GPA Command List Object
//==============================================================================

#ifndef _VK_GPA_COMMAND_LIST_H_
#define _VK_GPA_COMMAND_LIST_H_

#include "IGPACommandList.h"
#include "IGPAInterfaceTrait.h"
#include "VkGPASample.h"
#include "VkCommandListSwQueries.h"

#include <vulkan.h>
#include <vk_amd_gpa_interface.h>
#include <unordered_set>

class IGPASession;    ///< Predeclared IGPASession
class VkGPASession;   ///< Predeclared VkGPASession

/// Vulkan-specific GPA Command List
class VkGPACommandList : public IGPACommandList
{
public:
    /// Delete Default Constructor
    VkGPACommandList() = delete;

    /// Constructor
    /// \param[in] pVkGpaSession Vulkan GPA session
    /// \param[in] pPass pass object pointer
    /// \param[in] pCmd VkCommandBuffer pointer
    /// \param[in] cmdType commnad list type
    VkGPACommandList(VkGPASession* pVkGpaSession,
        GPAPass* pPass,
        void* pCmd,
        GPA_Command_List_Type cmdType);

    /// Destructor
    ~VkGPACommandList();

    /// \copydoc IGPACommandList::GetParentSession()
    IGPASession * GetParentSession() const override;

    /// \copydoc IGPACommandList::Begin()
    bool Begin() override;

    /// \copydoc IGPACommandList::End()
    bool End() override;

    /// \copydoc IGPACommandList::IsCommandListRunning()
    bool IsCommandListRunning() const override;

    /// \copydoc IGPACommandList::GetPass()
    GPAPass * GetPass() const override;

    /// \copydoc IGPACommandList::GetSampleCount()
    gpa_uint32 GetSampleCount() const override;

    /// \copydoc IGPACommandList::BeginSample()
    bool BeginSample(ClientSampleId clientSampleIndex, GPASample* pSample, const std::vector<CounterIndex>* pCounterList) override;

    /// Returns the sample with given client sample id if it exists
    /// \param[in] clientSampleId client sample id
    /// \return VK GPA sample if found, nullptr otherwise
    VkGPASample* GetSample(ClientSampleId clientSampleId) const;

    /// \copydoc IGPACommandList::GetLastSample()
    GPASample * GetLastSample() const override;

    /// \copydoc IGPACommandList::CloseLastSample()
    bool CloseLastSample(bool closingByClient = false) override;

    /// \copydoc IGPACommandList::IsLastSampleClosed()
    bool IsLastSampleClosed() const override;

    /// \copydoc IGPACommandList::IsComplete()
    bool IsComplete() const override;

    /// \copydoc IGPACommandList::GetCmdType()
    GPA_Command_List_Type GetCmdType() const override;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// \copydoc IGPAInterfaceTrait::ObjectType()
    GPAObjectType ObjectType() const override;

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
    bool CopySecondarySamples(VkGPACommandList* pPrimaryCmdList, gpa_uint32 numSamples, gpa_uint32 * pNewSampleIds, std::vector<ClientSampleId>& originalSampleIds);

    /// Gets the AMD Extension Session object that was copied to store the results of the specified clientSampleId.
    /// \param clientSampleId A sample Id supplied to GPA through the GPA_CopySecondarySamples() entrypoint.
    /// \return The VkGpaSessionAMD object that corresponds to the supplied clientSampleId; VK_NULL_HANDLE if no corresponding session exists.
    VkGpaSessionAMD GetCopiedAmdExtSession(ClientSampleId clientSampleId) const;

private:

    /// Checks to see if a sample with the supplied ClientSampleId has been started.
    /// Not Threadsafe. Assumes caller has locked m_sampleMapMutex.
    /// \param clientSampleId The sampleId to search for
    /// \return true if the named sample has been started; false otherwise.
    bool DoesSampleExist(ClientSampleId clientSampleId);

    /// Enums for the state of command list
    enum class CommandListState
    {
        UNDEFINED,                          ///< Undefined state
        SAMPLE_RECORDING_BEGIN,             ///< command list is ready to add samples
        SAMPLE_RECORDING_END,               ///< Command List is closed for adding samples
    };

    /// Enums for the state of the sample.
    /// A sample will be initalized in NOT_STARTED started, and as the samples are
    /// Begin/Ended on the command list, the state will alternate between STARTED and ENDED.
    enum class CommandSampleState
    {
        SAMPLE_NOT_STARTED,         ///< Initial state when a sample has not yet started
        SAMPLE_STARTED,             ///< sample has started on a command list
        SAMPLE_ENDED                ///< sample has ended on a command list
    };

    VkGPASession* m_pParentSession;                             ///< The Session which contains this command list
    GPAPass* m_pPass;                                           ///< The pass that contains this command list
    GPA_Command_List_Type m_commandListType;                    ///< Indicates whether this is a primary or secondary command list.
    VkCommandBuffer m_vkCmdBuffer;                              ///< The Vulkan CommandBuffer assocaited with this GPACommandList.
    VkGpaSessionAMD m_gpaExtSessionAMD;                         ///< The AMD Extension session that is being used by this command list. The session may also be in use by other CommandLists.
    CommandListState m_commandListState;                        ///< State of the command list
    CommandSampleState m_cmdSampleState;                        ///< command list sample state
    VkCommandListSwQueries m_swQueries;                         ///< The queries that are needed for each software sample (TODO: Should this be in the software sample class?)

    mutable std::mutex m_sampleMapMutex;                        ///< Mutex to protect the primary and secondary sample maps.
    std::map<ClientSampleId, VkGPASample*> m_primarySampleMap;  ///< Map from the assigned client sample id to the associated VkGPASample object
    std::vector<VkGPASample*> m_primarySampleList;              ///< List of primary samples, in the order they are created from the application.
    VkGPASample* m_pLastSample;                                 ///< The most recently started sample.
    std::list<VkGpaSessionAMD> m_copiedAmdExtSessions;          ///< The list of copied AmdExtSessions that were created for copied samples.

    /// Struct to hold the original SampleId and copied AMD Extension Session
    /// when CopySecondarySamples() is called. This struct is used in the secondarySamplesMap
    /// to correlate a secondarySampleId with the copied Ext Session and the original sample Id
    /// so that the results can be read back from the driver.
    struct CopiedSampleInfo
    {
        ClientSampleId originalSampleId;        ///< The sampleId that was supplied by the user when the secondary CommandBuffer was recorded.
        VkGpaSessionAMD copiedAmdExtSession;    ///< The extension session that was created when CopySecondarySamples() was called; it holds the samples results for one execution of the secondary command buffer.
    };

    std::map<ClientSampleId, CopiedSampleInfo> m_copiedSampleMap;  ///< Map from the newly assigned client sample id to the original sampleId and copied extension session from which to get the result.
};

#endif //_VK_GPA_COMMAND_LIST_H_
