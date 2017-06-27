//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A class for managing data requests for an entire session
//==============================================================================

#ifndef _GPA_SESSION_REQUESTS_H_
#define _GPA_SESSION_REQUESTS_H_

#include "GPUPerfAPITypes.h"
#include "GPADataRequest.h"
#include <map>
#include <sstream>
#include <vector>

/// Contains the data requests which are each sample of the profile session.
struct GPA_PassRequests
{
    /// Maps a sample ID to the data request which handled that sample.
    std::map<gpa_uint32, GPA_DataRequest*> m_samples;

    /// Maps a sample ID to a set of counter results.
    /// The results will get stored in here after the corresponding GPA_DataRequest::IsComplete() returns true.
    /// This should allow us to delete the data request and save memory.
    std::map<gpa_uint32, GPA_CounterResults> m_results;
};

/// Maintains all the data requests needed for an entire session.
class GPA_SessionRequests
{
public:

    /// Initializes a new instance of the GPA_SessionRequests class.
    GPA_SessionRequests();

    /// Destructor which flushes and deletes all tracked requests
    virtual ~GPA_SessionRequests();

    /// Waits for all data requests to be complete (blocking).
    virtual void Flush();

    /// Checks each of the data requests in the specified pass to see if their results are available.
    /// \param passIndex The 0-based index of the pass to check for available results.
    void CheckForAvailableResults(gpa_uint32 passIndex);

    /// Set the number of passes that will be needed for the session.
    /// \param passCount The necessary number of passes.
    void SetPassCount(gpa_uint32 passCount);

    /// Get the number of necessary passes for the session.
    /// \return The number of passes.
    gpa_uint32 GetPassCount();

    /// Get the number of samples that should be in each pass.
    /// \param[in,out] pSamples Will contain the number of samples if function call returns successfully.
    /// \return GPA_STATUS_ERROR_NULL_POINTER if pSamples is nullptr; GPA_STATUS_ERROR_NOT_FOUND if there are no passes in the session; GPA_STATUS_OK on success.
    GPA_Status GetSampleCount(gpa_uint32* pSamples);

    /// Indicate that the supplied request has been started for the given pass and sample.
    /// \param passIndex The pass in which the request has been started.
    /// \param sampleId The sample for which the request was started.
    /// \param pRequest Pointer to the request which was started.
    void Begin(gpa_uint32 passIndex, gpa_uint32 sampleId, GPA_DataRequest* pRequest);

    /// Ends the request that was started at a specific sample of a particular pass.
    /// \param passIndex The pass which contains the request to end.
    /// \param sampleId The sample ID of the request to end.
    /// \return true if the sample could be ended; false otherwise.
    bool End(gpa_uint32 passIndex, gpa_uint32 sampleId);

    /// Checks whether or not the sample is ready in all available passes.
    /// \param sampleId The sample to look for.
    /// \param[in,out] pIsSampleReady Indicates whether or not the sample is ready
    /// \return GPA_STATUS_ERROR_SAMPLE_NOT_FOUND_IN_ALL_PASSES if one or more passes does not contain the specified sample,
    ///    this may still result in isSampleReady being true if those passes which contain the sample all indicate that it is ready;
    ///    GPA_STATUS_OK if the sample is contained in all passes, the isSampleReady parameter may be true or false even if the function returnes GPA_STATUS_OK.
    GPA_Status IsSampleReady(gpa_uint32 sampleId, bool* pIsSampleReady);

    /// Indicates whether or not all the samples in the session are complete.
    /// \return true if all the samples are complete; false if one or more samples is not complete.
    bool IsComplete();

    /// Get a specific counter result from within a data request for the specified pass and sample.
    /// \param passIndex The pass index which contains the desired sample.
    /// \param sampleId The sample ID which contains the desired counter result.
    /// \param counterOffset The offset of the counter within the data request for which to get the result.
    /// \param[in,out] pResult Will point to the memory which contains the counter result.
    /// \return GPA_STATUS_ERROR_NULL_POINTER if pResult is nullptr;
    ///    GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE if the pass index is not valid;
    ///    GPA_STATUS_ERROR_SAMPLE_NOT_FOUND if the sample ID is not contained in the pass;
    ///    GPA_STATUS_ERROR_READING_COUNTER_RESULT if an error occurred while attempting to read back the specific counter result;
    ///    GPA_STATUS_OK on success and pResult will point to the counter result.
    GPA_Status GetResult(gpa_uint32 passIndex, gpa_uint32 sampleId, gpa_uint16 counterOffset, void* pResult);

    /// Checks whether or not the session contains the specified pass and sample request.
    /// \param passIndex The pass index to check for.
    /// \param sampleId The sample ID to check for.
    /// \return true if the session contains the sample in the pass; false otherwise.
    bool ContainsSampleRequest(gpa_uint32 passIndex, gpa_uint32 sampleId);

    /// The session ID of this session.
    unsigned int m_sessionID;

private:
    /// Checks whether or not the session contains the specified pass and sample result.
    /// \param passIndex The pass index to check for.
    /// \param sampleId The sample ID to check for.
    /// \return true if the session contains a result for the sample in the pass; false otherwise.
    bool ContainsSampleResult(gpa_uint32 passIndex, gpa_uint32 sampleId);

    /// List of passes, which are defined by a list of samples,
    /// which are defined by a set of individual counter data requests.
    /// (ie, a 'session' is a set of 'passes' is a set of 'samples' is a set of 'requests').
    /// sorted by pass to allow consecutive session requests on same counters
    /// to reuse resources from a previous request
    /// there should only ever be one "owner" pointer to these requests
    /// here or in the expired session requests
    std::vector<GPA_PassRequests> m_passes;

    /// vector to save allocated result.pResultBuffer
    /// this vector will be used to delete all allocated result.pResultBuffer memory
    std::vector<gpa_uint64*> m_allocatedResultBuffer;

    /// List of memory references for this session's data requests
    std::vector<void*> m_memoryRefs;
};

#endif //_GPA_SESSION_REQUESTS_H_
