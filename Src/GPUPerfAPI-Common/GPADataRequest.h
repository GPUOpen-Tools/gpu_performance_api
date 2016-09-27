//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A base class to manage data requests
//==============================================================================

#ifndef _GPA_COUNTERDATAREQUEST_H_
#define _GPA_COUNTERDATAREQUEST_H_

#include "GPUPerfAPIOS.h"
#include "GPUPerfAPITypes.h"
#include <vector>

#include "Logging.h"

using std::vector;

class GPA_ContextState;

/// Stores counter results after they are returned from the data request.
struct GPA_CounterResults
{
    /// Stores the number of items in pResultsBuffer.
    size_t m_numResults;

    /// An array of counter results.
    gpa_uint64* m_pResultBuffer;
};


/// Abstract class to encapsulate a counter data request
///
/// a list of counters to track is specified by calling begin
/// DataRequest implementations should allow efficient reuse of requests.
/// By default requests are recycled in a way which means the same set
/// of active counters will be requested ( regardless of multi-pass ).
///
/// A selectionID is used to allow trivial testing to see if this set has changed.
/// The selectionID is incremented whenever a different counter set is activated.
/// The value of selectionID is not affected by multi-pass.
///
/// The sampleID records which sample number this request was made for.
/// It is set by GPA_BeginSample.
///
/// Implementations must implement GPA_IMP_CreateDataRequest to create
/// their derived type.
class GPA_DataRequest
{
public:
    /// Initializes a new instance of hte GPA_DataRequest class.
    GPA_DataRequest()
        : m_counterSelectionID(0),
          m_sampleID(0),
          m_activeCounters(0),
          m_areResultsCollected(false),
          m_isRequestStarted(false),
          m_isRequestActive(false),
          m_gpuTimeTopToBottomPresent(false),
          m_gpuTimeTopToBottomOffset(0),
          m_gpuTimeBottomToBottomPresent(false),
          m_gpuTimeBottomToBottomOffset(0),
          m_gpuTimestampTopPresent(false),
          m_gpuTimestampTopOffset(0),
          m_gpuTimestampPreBottomPresent(false),
          m_gpuTimestampPreBottomOffset(0),
          m_gpuTimestampPostBottomPresent(false),
          m_gpuTimestampPostBottomOffset(0)
    {
    }

    /// Virtual destructor
    virtual ~GPA_DataRequest()
    {
    }

    /// Obtain the number of active counters in the data request.
    /// \return The number of active counters.
    size_t NumActiveCounters()
    {
        return m_activeCounters;
    }

    /// Start a counter sample.
    /// Begin must handle the case where a request is reused
    /// try and reuse resources if selectionID matches (which means the same counters are activated).
    /// \param pContextState pointer to object containing the context information for this request
    /// \param selectionID the ID of the counter selection
    /// \param pCounters the set of counters to enable
    /// \return True if the sample could be started; false otherwise.
    bool Begin(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters)
    {
        bool result = BeginRequest(pContextState, selectionID, pCounters);

        if (result)
        {
            m_isRequestStarted = true;
            m_isRequestActive = true;
            m_areResultsCollected = false;
        }

        return result;
    }

    /// Ends a counter sample.
    /// \return True on success; false on error.
    bool End()
    {
        // make sure this request is valid before trying to end it.
        if (m_isRequestStarted == false || m_isRequestActive == false)
        {
            return false;
        }

        bool result = EndRequest();

        if (result)
        {
            // Since the request ended successfully, mark that it is no longer started.
            // The results haven't been collected though, so it is still considered active.
            m_isRequestStarted = false;
        }

        return result;
    }

    /// Non-blocking function which checks to see if the sample results are available.
    /// \param resultStorage the results storage to use if the request is complete
    /// \return True if the results are available and the data requests are complete; false otherwise.
    bool IsRequestComplete(GPA_CounterResults& resultStorage)
    {
        if (m_areResultsCollected)
        {
            // if the results were already collected, no need to check again.
            return true;
        }

        if (m_activeCounters == 0)
        {
            // no counters active means there are no results to collect.
            return true;
        }

        if (!m_isRequestActive)
        {
            // the request is not active (the results were probably already collected), so it must be complete.
            return true;
        }

        // collect results if they are available.
        bool result = CollectResults(resultStorage);

        if (result)
        {
            m_areResultsCollected = true;
            m_isRequestActive = false;
            ReleaseCounters();
        }

        return result;
    }

    /// Collects the results if they are available.
    /// \param[out] resultStorage
    /// \return true if the results were collected; false if they are not available.
    virtual bool CollectResults(GPA_CounterResults& resultStorage) = 0;

    /// Sets the sample ID.
    /// \param sampleID the ID to assign this data request.
    virtual void SetSampleID(gpa_uint32 sampleID)
    {
        m_sampleID = sampleID;
    }

    /// Gets the sample ID
    /// \return the sample ID of this data request.
    inline gpa_uint32 GetSampleID()
    {
        return m_sampleID;
    }

    /// Checks to see if the data request is a time stamp and for a specific counter activeCounterOffset
    /// \param activeCounterOffset The counter offset
    /// \return true if time stamp and offset match - false if not
    bool IsTimeStamp(gpa_uint32 activeCounterOffset)
    {
        if ((m_gpuTimeBottomToBottomPresent && activeCounterOffset == m_gpuTimeBottomToBottomOffset) ||
            (m_gpuTimeTopToBottomPresent && activeCounterOffset == m_gpuTimeTopToBottomOffset) ||
            (m_gpuTimestampTopPresent && activeCounterOffset == m_gpuTimestampTopOffset) ||
            (m_gpuTimestampPreBottomPresent && activeCounterOffset == m_gpuTimestampPreBottomOffset) ||
            (m_gpuTimestampPostBottomPresent && activeCounterOffset == m_gpuTimestampPostBottomOffset))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// Gets the top to bottom time stamp bool
    /// \return true if the data request is a top to bottom time stamp
    inline bool GPUTimeTopToBottomPresent()
    {
        return m_gpuTimeTopToBottomPresent;
    }

    /// Gets the bottom to bottom time stamp bool
    /// \return true if the data request is a bottom to bottom time stamp
    inline bool GPUTimeBottomToBottomPresent()
    {
        return m_gpuTimeBottomToBottomPresent;
    }

    /// Gets the pre-event top timestamp bool
    /// \return true if the data request is a pre-event top timestamp
    inline bool GPUTimestampTopPresent()
    {
        return m_gpuTimestampTopPresent;
    }

    /// Gets the pre-event bottom timestamp bool
    /// \return true if the data request is a pre-event bottom timestamp
    inline bool GPUTimestampPreBottomPresent()
    {
        return m_gpuTimestampPreBottomPresent;
    }

    /// Gets the post-event bottom timestamp bool
    /// \return true if the data request is a post-event bottom timestamp
    inline bool GPUTimestampPostBottomPresent()
    {
        return m_gpuTimestampPostBottomPresent;
    }

    /// Gets the top to bottom counter offset
    /// \return The counter offset
    inline gpa_uint32 GPUTimeBottomToBottomOffset()
    {
        return m_gpuTimeBottomToBottomOffset;
    }

    /// Gets the bottom to bottom counter offset
    /// \return The counter offset
    inline gpa_uint32 GPUTimeTopToBottomOffset()
    {
        return m_gpuTimeTopToBottomOffset;
    }

    /// Gets the pre-event top timestamp counter offset
    /// \return The counter offset
    inline gpa_uint32 GPUTimestampTopOffset()
    {
        return m_gpuTimestampTopOffset;
    }

    /// Gets the pre-event bottom timestamp counter offset
    /// \return The counter offset
    inline gpa_uint32 GPUTimestampPreBottomOffset()
    {
        return m_gpuTimestampPreBottomOffset;
    }

    /// Gets the post-event bottom timestamp counter offset
    /// \return The counter offset
    inline gpa_uint32 GPUTimestampPostBottomOffset()
    {
        return m_gpuTimestampPostBottomOffset;
    }

    /// Gets a bool indicating if the request has been started
    /// \return True if started - false if not
    bool IsRequestStarted()
    {
        return m_isRequestStarted;
    }

    /// Gets a bool indicating if the request is active
    /// \return True if active - false if not
    bool IsRequestActive()
    {
        return m_isRequestActive;
    }

    /// Gets the current counter selection ID
    /// \return The current counter selection ID
    gpa_uint32 GetCounterSelectionID()
    {
        return m_counterSelectionID;
    }

    /// Sets the current counter selection ID
    void SetCounterSelectionID(gpa_uint32 selectionID)
    {
        m_counterSelectionID = selectionID;
    }

    /// Sets the number of active counters
    /// \param count The number of active counters
    void SetNumActiveCounters(size_t count)
    {
        m_activeCounters = count;
    }

    /// Resets the GPUTimes counter state
    void ResetGPUTimeState(const vector<gpa_uint32>* pCounters, const gpa_uint32 topToBottomCounterIndex, const gpa_uint32 bottomToBottomCounterIndex,
                           const gpa_uint32 topTimestampCounterIndex, const gpa_uint32 preBottomTimestampCounterIndex, const gpa_uint32 postBottomTimestampCounterIndex)
    {
        m_gpuTimeTopToBottomPresent = false;
        m_gpuTimeBottomToBottomPresent = false;
        m_gpuTimestampTopPresent = false;
        m_gpuTimestampPreBottomPresent = false;
        m_gpuTimestampPostBottomPresent = false;

        for (gpa_uint32 i = 0 ; i < (gpa_uint32)pCounters->size() ; i++)
        {
            if ((*pCounters)[i] == topToBottomCounterIndex)
            {
                m_gpuTimeTopToBottomPresent = true;
                m_gpuTimeTopToBottomOffset = i;
            }
            else if ((*pCounters)[i] == bottomToBottomCounterIndex)
            {
                m_gpuTimeBottomToBottomPresent = true;
                m_gpuTimeBottomToBottomOffset = i;
            }
            else if ((*pCounters)[i] == topTimestampCounterIndex)
            {
                m_gpuTimestampTopPresent = true;
                m_gpuTimestampTopOffset = i;
            }
            else if ((*pCounters)[i] == preBottomTimestampCounterIndex)
            {
                m_gpuTimestampPreBottomPresent = true;
                m_gpuTimestampPreBottomOffset = i;
            }
            else if ((*pCounters)[i] == postBottomTimestampCounterIndex)
            {
                m_gpuTimestampPostBottomPresent = true;
                m_gpuTimestampPostBottomOffset = i;
            }
        }
    }

    /// Gets the list of memory references for this data request
    /// \param memoryRefs the list of memory references
    /// \return true on success, otherwise false
    virtual bool GetRequiredMemRefs(vector<void*>& memoryRefs)
    {
        UNREFERENCED_PARAMETER(memoryRefs);
        return false;
    }

private:

    bool m_gpuTimeTopToBottomPresent;          ///< Indicates if the GPUTime top to bottom is being requested
    gpa_uint32 m_gpuTimeTopToBottomOffset;     ///< Which index within this request is the top to bottom counter

    bool m_gpuTimeBottomToBottomPresent;       ///< Indicates if the GPUTime bottom to bottom is being requested
    gpa_uint32 m_gpuTimeBottomToBottomOffset;  ///< Which index within this request is the bottom to bottom counter

    bool m_gpuTimestampTopPresent;             ///< Indicates if the GPUTimestamp pre-event top is being requested
    gpa_uint32 m_gpuTimestampTopOffset;        ///< Which index within this request is the pre-event top timestamp counter

    bool m_gpuTimestampPreBottomPresent;       ///< Indicates if the GPUTimestamp pre-event bottom is being requested
    gpa_uint32 m_gpuTimestampPreBottomOffset;  ///< Which index within this request is the pre-event bottom timestamp counter

    bool m_gpuTimestampPostBottomPresent;      ///< Indicates if the GPUTimestamp post-event bottom is being requested
    gpa_uint32 m_gpuTimestampPostBottomOffset; ///< Which index within this request is the post-event bottom timestamp counter

protected:

    /// Start a counter sample.
    /// Begin must handle the case where a request is reused
    /// try and reuse resources if selectionID matches (which means the same counters are activated).
    /// \param pContextState pointer to object containing the context information for this request
    /// \param selectionID the ID of the counter selection
    /// \param pCounters the set of counters to enable
    /// \return True if the sample could be started; false otherwise.
    virtual bool BeginRequest(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters) = 0;

    /// Ends a counter sample.
    /// \return True on success; false on error.
    virtual bool EndRequest() = 0;

    /// Release allocated counters
    virtual void ReleaseCounters() = 0;

    /// Stores the result of the CollectResults() method so that it does not get called twice.
    bool m_areResultsCollected;

    /// true between calls to request begin and end
    bool m_isRequestStarted;

    /// true between begin and receipt of data
    bool m_isRequestActive;

    /// The id of the set of active counters
    gpa_uint32 m_counterSelectionID;

    /// The ID of this profile sample. Set by GPA_BeginSample
    gpa_uint32 m_sampleID;

    /// The number of active counters in this request.
    size_t m_activeCounters;
};

#endif //_GPA_COUNTERDATAREQUEST_H_
