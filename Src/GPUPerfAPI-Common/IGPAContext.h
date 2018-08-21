//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Interface representing the GPA context
//==============================================================================

#ifndef _I_GPA_CONTEXT_H_
#define _I_GPA_CONTEXT_H_

#include "GPUPerfAPITypes.h"
#include "GPAHWInfo.h"
#include "IGPAInterfaceTrait.h"
#include "IGPACounterAccessor.h"
#include "IGPACounterScheduler.h"

class IGPASession;  // forward declaration

/// Device clock mode enum used to decode usage of GPA_OpenContext mode flag
enum class DeviceClockMode : uint32_t
{
    Default,        ///< Device clocks and other power settings are restored to default.
    MinimumEngine,  ///< Engine clock is set to the lowest available level. Memory clock is set to thermal and power sustainable level.
    MinimumMemory,  ///< Memory clock is set to the lowest available level. Engine clock is set to thermal and power sustainable level.
    Peak,           ///< Clocks set to maximum when possible. Fan set to maximum. Note: Under power and thermal constraints device will clock down.
    Profiling,      ///< Scale down from peak ratio. Clocks are set to a constant amount which is known to be power and thermal sustainable. The engine/memory clock ratio will be kept the same as much as possible.
};

/// Interface for GPA Context Object
class IGPAContext : public IGPAInterfaceTrait
{
public:

    /// Virtual Destructor
    virtual ~IGPAContext() = default;

    /// Creates a session Container
    /// \param sampleType the sample type that will be created for this session
    /// \return GPA_Session Id object
    virtual GPA_SessionId CreateSession(GPA_Session_Sample_Type sampleType) = 0;

    /// Deletes a session and its associated counter data
    /// \param[in] sessionId pointer to previously created session object
    /// \return true if operation is successful otherwise false
    virtual bool DeleteSession(GPA_SessionId sessionId) = 0;

    /// Returns maximum number of session possible in the context
    /// \return maximum number of possible sessions
    virtual gpa_uint32 GetMaxGPASessions() const = 0;

    /// Returns the count of created sessions in the context
    /// \return number of sessions created in the context
    virtual gpa_uint32 GetSessionCount() const = 0;

    /// Checks whether the session current exist or not
    /// \param[in] pSessionId pointer to GPA Session id object
    /// \return true if session exist otherwise false
    virtual bool DoesSessionExist(GPA_SessionId pSessionId) const = 0;

    /// Returns a mask of the sample types supported by this context
    /// \param[out] pSampleTypes The value that will be set to the the mask of the sample types supported by this context. This will be a combination of GPA_Context_Sample_Type_Bits.
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetSupportedSampleTypes(GPA_ContextSampleTypeFlags* pSampleTypes) const = 0;

    /// Returns the number of available counters in the context
    /// \param[out] pCount number of counters
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetNumCounters(gpa_uint32* pCount) const = 0;

    /// Returns the name of a counter
    /// \param[in] index index of the counter
    /// \param[out] ppName name of the counter
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetCounterName(gpa_uint32 index, const char** ppName) const = 0;

    /// Returns the group of counter
    /// \param[in] index index of the counter
    /// \param[out] ppGroup group of counter
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetCounterGroup(gpa_uint32 index, const char** ppGroup) const = 0;

    /// Returns the description of a counter
    /// \param[in] index index of the counter
    /// \param[out] ppDescription description of a counter
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetCounterDescription(gpa_uint32 index, const char** ppDescription) const = 0;

    /// Returns the data type of a counter
    /// \param[in] index index of the counter
    /// \param[out] pCounterDataType data type of the counter
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetCounterDataType(gpa_uint32 index, GPA_Data_Type* pCounterDataType) const = 0;

    /// Returns the usage type of a counter
    /// \param[in] index index of the counter
    /// \param[out] pCounterUsageType counter usage type
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetCounterUsageType(gpa_uint32 index, GPA_Usage_Type* pCounterUsageType) const = 0;

    /// Get the UUID of the specified counter.
    /// \param[in] index index of the counter
    /// \param[out] pCounterUuid The value which will hold the counter UUID upon successful execution.
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetCounterUuid(gpa_uint32 index, GPA_UUID* pCounterUuid) const = 0;

    /// Get the supported sample types of the specified counter.
    /// \param[in] index index of the counter
    /// \param[out] pCounterSampleType The value which will hold the counter's supported sample type upon successful execution.
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetCounterSampleType(gpa_uint32 index, GPA_Counter_Sample_Type* pCounterSampleType) const = 0;

    /// Returns the index of a counter by its name
    /// \param[in] pCounterName name of the counter
    /// \param[out] pIndex index of the counter
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status GetCounterIndex(const char* pCounterName, gpa_uint32* pIndex) const = 0;

    /// Uses the exposedCounterIndex to look up which source the counter comes from and the relative (local)
    /// counter index into that source of counters.
    /// \param[in] exposedCounterIndex The counter index of which to get the source and local index.
    /// \param[out] pSource Pointer to a variable that will hold the counter's source. Cannot be NULL.
    /// \param[out] pSourceLocalIndex Pointer to a variable that will hold the counters index relative to that source. Cannot be NULL.
    /// \return true if the exposedCounterIndex is in the valid range; false otherwise.
    virtual bool GetCounterSourceLocalIndex(gpa_uint32 exposedCounterIndex, GPACounterSource* pSource, gpa_uint32* pSourceLocalIndex) const = 0;

    /// Check to see if public counters should be exposed.
    /// \return true if public counters should be exposed; false otherwise.
    virtual bool ArePublicCountersExposed() const = 0;

    /// Check to see if software counters should be exposed.
    /// \return true if software counters should be exposed; false otherwise.
    virtual bool AreHardwareCountersExposed() const = 0;

    /// Check to see if hardware counters should be exposed.
    /// \return true if hardware counters should be exposed; false otherwise.
    virtual bool AreSoftwareCountersExposed() const = 0;

    /// Gets the source (origin) of the specified internal counter (ie, either hardware or software)
    /// \param internalCounterIndex The index of the counter to find, must be in range of 0 to (NumHWCounters + NumSWCounters).
    /// \return Unknown If the counterIndex is invalid;
    ///         Public If the counter is defined by GPA
    ///         Hardware if the counter comes from our internal extension;
    ///         Software if the counter comes from an API-level entrypoint (ie, queries)
    virtual GPACounterSource GetCounterSource(gpa_uint32 internalCounterIndex) const = 0;

    /// Sets a flag to invalidate and flush the L2 cache around the next counter sample
    /// \param[in] shouldInvalidateAndFlushL2Cache flag indicating to enable invalidation and flushing of the L2 cache
    virtual void SetInvalidateAndFlushL2Cache(bool shouldInvalidateAndFlushL2Cache) = 0;

    /// Returns the status of the flag indicating the invalidation and flushing of L2 cache
    /// \return flag indicating the invalidation and flushing of L2 cache
    virtual bool IsInvalidateAndFlushL2CacheEnabled() const = 0;

    /// Returns the hardware info
    /// \return pointer to the context hardware info
    virtual const GPA_HWInfo* GetHwInfo() const = 0;

    /// Checks whether the context is open or not
    /// \return true if context is open otherwise false
    virtual bool IsOpen() const = 0;

    /// Gets device clock mode behavior
    /// \return DeviceClockMode enum indicating clock mode behavior
    virtual DeviceClockMode GetDeviceClockMode() const = 0;

    /// Opens the counter for the context
    /// \return true if successfully opens the counter otherwise false
    virtual bool OpenCounters() = 0;

    /// Begins the session on current context
    /// \param[in] pGpaSession pointer to previously created session object
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status BeginSession(IGPASession* pGpaSession) = 0;

    /// Ends the session on current context
    /// \param[in] pGpaSession pointer to previously created session object
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status EndSession(IGPASession* pGpaSession) = 0;

    /// Returns the active session for the context
    /// \return active session if any session is active otherwise nullptr
    virtual const IGPASession* GetActiveSession() const = 0;
};

#endif // _I_GPA_CONTEXT_H_
