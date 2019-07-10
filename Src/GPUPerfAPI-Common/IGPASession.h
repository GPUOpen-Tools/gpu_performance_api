//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Interface representing the GPA Session
//==============================================================================

#ifndef _I_GPA_SESSION_H_
#define _I_GPA_SESSION_H_

#include <vector>
#include "GPUPerfAPITypes.h"
#include "GPACommonDefs.h"
#include "IGPAInterfaceTrait.h"

class IGPAContext;  // forward declaration

/// Enum for GPA Session limit
enum GPASessionLimit : uint8_t
{
    GPA_SESSION_NO_LIMIT = 0  ///< GPA session no limit enum value
};

/// Enum to track the state of a GPASession
enum GPASessionState : uint8_t
{
    GPA_SESSION_STATE_NOT_STARTED = 0,        ///< Session has been created, but not yet started. This is when counters can be enabled and disabled.
    GPA_SESSION_STATE_STARTED,                ///< Session has been started, but not yet ended.
    GPA_SESSION_STATE_ENDED_PENDING_RESULTS,  ///< Session has been ended, and is pending results.
    GPA_SESSION_STATE_RESULT_COLLECTED,       ///< Session's results are available.
};

/// Interface for the GPA Session Object
class IGPASession : public IGPAInterfaceTrait
{
public:
    /// Virtual Destructor
    virtual ~IGPASession() = default;

    /// Gets the context which created this session
    /// \return The parent context.
    virtual IGPAContext* GetParentContext() const = 0;

    /// Get the current state of the session.
    /// \return The state of the session.
    virtual GPASessionState GetState() const = 0;

    /// Enables a counter by its index
    /// \param[in] index index of the counter
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status EnableCounter(gpa_uint32 index) = 0;

    /// Disables a counter by its index
    /// \param[in] index index of the counter
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status DisableCounter(gpa_uint32 index) = 0;

    /// Disables all the enabled counters
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status DisableAllCounters() = 0;

    /// Returns the number of enabled counter
    /// \param[out] pCount number of enabled counters
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetNumEnabledCounters(gpa_uint32* pCount) const = 0;

    /// Get the counter index for an enabled counter.
    /// \param[in] enabledNumber The number of the enabled counter to get the counter index for. Must lie between 0 and (GPA_GetNumEnabledCounters result - 1).
    /// \param[out] pEnabledCounterIndex The value that will contain the index of the counter.
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status GetEnabledIndex(gpa_uint32 enabledNumber, gpa_uint32* pEnabledCounterIndex) const = 0;

    /// Checks whether a counter is enabled or not
    /// \param[in] counterIndex index of the counter
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status IsCounterEnabled(gpa_uint32 counterIndex) const = 0;

    /// Returns the number of required passes for enabled counter
    /// \param[out] pNumPasses number of required passes
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetNumRequiredPasses(gpa_uint32* pNumPasses) = 0;

    /// Begins a session
    /// \return GPA_STATUS_OK if session started successfully otherwise an error code
    virtual GPA_Status Begin() = 0;

    /// Ends a session
    /// \return GPA_STATUS_OK if session ended successfully otherwise an error code
    virtual GPA_Status End() = 0;

    /// Creates a command list for sampling
    /// \param[in] passIndex indes of the pass
    /// \param[in] pCmd command list
    /// \param[in] cmdType type of command List
    /// \return unique command list id object
    virtual GPA_CommandListId CreateCommandList(gpa_uint32 passIndex, void* pCmd, GPA_Command_List_Type cmdType) = 0;

    /// Checks whether a command list exists in the specified pass
    /// \param[in] passIndex The pass index in which to look for the command list
    /// \param[in] pCommandListId unique command list id object
    /// \return true if the command list exists in the session otherwise false
    virtual bool DoesCommandListExist(gpa_uint32 passIndex, GPA_CommandListId pCommandListId) const = 0;

    /// Checks whether a sample exists in the session
    /// \param[in] sampleId The sample index to check
    /// \return true if the sample exists in the session otherwise false
    virtual bool DoesSampleExist(gpa_uint32 sampleId) const = 0;

    /// Starts a sample on command list for the passed unique sample id
    /// \param[in] sampleId User-supplied Id of the sample
    /// \param[in] commandListId the CommandlistId on which the sample should be started
    /// \return true if operation was successful otherwise false
    virtual bool BeginSample(gpa_uint32 sampleId, GPA_CommandListId commandListId) = 0;

    /// Ends the current sample on command list
    /// \param[in] commandListId the CommandlistId on which the sample should be ended
    /// \return true if operation was successful otherwise false
    virtual bool EndSample(GPA_CommandListId commandListId) = 0;

    /// Continue a primary command list sample to another primary command list
    /// \param[in] srcSampleId source sample id
    /// \param[in] primaryCommandListId primary command list id on which sample is continuing
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status ContinueSampleOnCommandList(gpa_uint32 srcSampleId, GPA_CommandListId primaryCommandListId) = 0;

    /// Copy secondary command list/buffer sample on primary command list/buffer
    /// \param[in] secondaryCmdListId secondary command list on secondary samples were created
    /// \param[in] primaryCmdListId primary command list/buffer in which new samples are getting copied
    /// \param[in] numSamples number of secondary samples
    /// \param[in] pNewSampleIds new sample ids on a primary command list
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status CopySecondarySamples(GPA_CommandListId secondaryCmdListId,
                                            GPA_CommandListId primaryCmdListId,
                                            gpa_uint32        numSamples,
                                            gpa_uint32*       pNewSampleIds) = 0;

    /// Returns the number of samples created in this session
    /// \return number of samples
    virtual gpa_uint32 GetSampleCount() const = 0;

    /// Get the sample id by index
    /// \param[in] sampleIndex index of the sample
    /// \param[out] clientSampleId client sample id
    /// \return true if sample found otherwise false
    virtual bool GetSampleIdByIndex(gpa_uint32 sampleIndex, gpa_uint32& clientSampleId) const = 0;

    /// Checks for newly available sample results
    /// \return true if the results from all samples are now available and cached locally;
    ///         false if none or only some results are updated.
    virtual bool UpdateResults() = 0;

    /// Updates the specified pass' results cache if new results are available.
    /// \param passIndex The specific pass to update.
    /// \return true if the results from all samples on the specified pass
    /// are now available and cached locally; false if none or only some results are updated.
    virtual bool UpdateResults(gpa_uint32 passIndex) = 0;

    /// Checks whether or not the pass is complete for sampling
    /// \param passIndex The specific pass to update.
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status IsPassComplete(gpa_uint32 passIndex) const = 0;

    /// Checks whether the session is ready for querying counter results.
    /// Use IGPASession::UpdateResults() periodically to make sure results are updated,
    /// which will trigger this call to return true.
    /// \return true if session is ready to be queried for counter data, false otherwise.
    virtual bool IsResultReady() const = 0;

    /// Checks whether or not the session is running
    /// \return true if session is started but not yet ended otherwise false
    virtual bool IsSessionRunning() const = 0;

    /// Returns the size of sample result in bytes
    /// \param sampleId the sample whose result size is needed
    /// \return size of the sample result in bytes
    virtual size_t GetSampleResultSizeInBytes(gpa_uint32 sampleId) const = 0;

    /// Get counter data of the sample
    /// \param[in] sampleId The identifier of the sample to get the result for.
    /// \param[in] sampleResultSizeInBytes size of sample in bytes
    /// \param[out] pCounterSampleResults address to which the counter data for the sample will be copied to
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status GetSampleResult(gpa_uint32 sampleId, size_t sampleResultSizeInBytes, void* pCounterSampleResults) = 0;

    /// Gets the supported sample type for this session
    /// \return the supported sample type for this session
    virtual GPA_Session_Sample_Type GetSampleType() const = 0;

    /// Gets the SPM sampling interval (in clock cycles) for this session
    /// \return the SPM sampling interval (in clock cycles) for this session
    virtual gpa_uint32 GetSPMInterval() const = 0;

    /// Sets the SPM sampling interval (in clock cycles) for this session
    /// \param interval the SPM sampling interval (in clock cycles) to set for this session
    virtual void SetSPMInterval(gpa_uint32 interval) = 0;

    /// Gets the SPM memory limit (in bytes) for this session
    /// \return the SPM memory limit (in bytes) for this session
    virtual gpa_uint64 GetSPMMemoryLimit() const = 0;

    /// Sets the SPM memory limit (in bytes) for this session
    /// \param memoryLimit the SPM memory limit (in bytes) to set for this session
    virtual void SetSPMMemoryLimit(gpa_uint64 memoryLimit) = 0;

    /// Gets the mask of instruction types to be included in the SQTT data
    /// \return the mask of instructions included in the SQTT data
    virtual GPA_SQTTInstructionFlags GetSQTTInstructionMask() const = 0;

    /// Sets the mask of instruction types to be included in the SQTT data
    /// \param sqttInstructionMask the mask of instructions included in the SQTT data
    virtual void SetSQTTInstructionMask(GPA_SQTTInstructionFlags sqttInstructionMask) = 0;

    /// Gets the id of the compute unit which should generate the instruction level data
    /// \return the id of the compute unit which should generate the instruction level data
    virtual gpa_uint32 GetSQTTComputeUnitId() const = 0;

    /// Sets the id of the compute unit which should generate the instruction level data
    /// \param sqttComputeUnitId the id of the compute unit which should generate the instruction level data
    virtual void SetSQTTComputeUnitId(gpa_uint32 sqttComputeUnitId) = 0;

    /// Gets the SQTT memory limit (in bytes) for this session
    /// \return the SQTT memory limit (in bytes) for this session
    virtual gpa_uint64 GetSQTTMemoryLimit() const = 0;

    /// Sets the SQTT memory limit (in bytes) for this session
    /// \param memoryLimit the SQTT memory limit (in bytes) to set for this session
    virtual void SetSQTTMemoryLimit(gpa_uint64 memoryLimit) = 0;

    /// Returns the counter list for the given pass in the session
    /// \param[in] passIndex index of the pass
    /// \return counter list for the given pass
    virtual std::vector<unsigned int>* GetCountersForPass(unsigned int passIndex) = 0;
};

#endif  // _I_GPA_SESSION_H_
