//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA Sample Header
//==============================================================================


#ifndef _GPA_SAMPLE_H_
#define _GPA_SAMPLE_H_

// std
#include <vector>
#include <mutex>

// GPA Common
#include "GPACommonDefs.h"

class GPAPass;          // forward declaration
class IGPACommandList;  // forward declaration
class IGPAContext;      // forward declaration

using CounterIndex = unsigned int;                  ///< type alias for counter index
using ClientSampleId = unsigned int;                ///< type alias for sample index
using DriverSampleId = unsigned int;                ///< type alias for index of the sample created by the driver extensions

/// Stores counter results after they are returned from the sample.
struct GPASampleResult
{
    size_t      m_numCounters;              ///< Stores the number of items in pResultsBuffer.
    gpa_uint64* m_pResultBuffer;            ///< An array of counter results.

    /// Delete Default Constructor
    GPASampleResult() = delete;

    /// Constructor
    /// \param[in] numOfCounters number of counters
    GPASampleResult(size_t numOfCounters)
    {
        m_numCounters = numOfCounters;
        // We can construct it over here as we are not throwing any exception
        m_pResultBuffer = new(std::nothrow) gpa_uint64[numOfCounters];
    }

    /// Destructor
    ~GPASampleResult()
    {
        delete[] m_pResultBuffer;
    }
};

/// Enum for GPA Sample type
enum class GpaSampleType
{
    Software,               ///< enum value for software samples
    Hardware                ///< enum value for hardware samples
};

/// Enum for the state of the GPA Sample.
enum class GPASampleState
{
    INITIALIZED = 0,        ///< Sample has not yet started
    STARTED,                ///< Sample is active, it has started but not yet ended
    PENDING_RESULTS,        ///< Sample has ended, but results are not yet available
    RESULTS_COLLECTED       ///< Sample results are available, and cached locally
};

/// Class for representing GpaSample object
class GPA_NOT_THREAD_SAFE_OBJECT GPASample
{
public:

    /// Constructor
    /// \param[in] pPass GPA Pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleId user-supplied sample id
    GPASample(GPAPass* pPass,
              IGPACommandList* pCmdList,
              GpaSampleType sampleType,
              ClientSampleId sampleId);

    /// Destructor
    virtual ~GPASample();

    /// Checks whether the sample has linked sample
    /// \return true if sample is linked to another gpa sample
    bool IsSampleContinuing() const;

    /// Returns the command list
    /// \return sample's command list
    IGPACommandList* GetCmdList() const;

    /// Links the continuing sample
    /// \param[in] pContinuingSample pointer to the continuing gpa sample
    /// \return returns true if sample can be linked to the current sample or not otherewise false
    bool LinkContinuingSample(GPASample* pContinuingSample);

    /// Returns the pass Object
    /// \return GPAPAss Object pointer
    GPAPass* GetPass() const;

    /// Should query this sample's results from the driver and store them in local memory.
    /// Once the results have been stored, use MarkAsCompleted() to move the sample into the Completed state, and return true from this method.
    /// \return true if the results from this sample have been updated and cached locally; false if the results are not available and cached locally.
    virtual bool UpdateResults() = 0;

    /// Should confirm that results for this sample have been collected from the driver.
    /// \return true if the sample's results have been copied back from the driver;
    ///         false if any sample is still pending.
    inline virtual bool IsComplete() const;

    /// Start a counter sample.
    /// \param pGpaContext pointer to object containing the context information for this request
    /// \param pCounters the set of counters to enable
    /// \return True if the sample could be started; false otherwise.
    bool Begin(IGPAContext* pGpaContext, const std::vector<gpa_uint32>* pCounters);

    /// Ends a counter sample.
    /// \return True on success; false on error.
    bool End();

    /// Gets the result of a single counter within this sample.
    /// If this sample has secondary samples, or continued samples, they should be included
    /// in this sample's result. Although the return value is typed uint64, it may actually
    /// contain any 64-bit data type (ie: uint64 or float64).
    /// \param[in] counterIndexInSample A counter index within this sample.
    /// \param[out] pResult A pointer to a 64-bit datatype at which to store the counter result if it is available.
    /// \return True if the result is available and could be copied; False if the result is not available or an error occurred.
    virtual bool GetResult(CounterIndex counterIndexInSample, gpa_uint64* pResult) const;

    /// Sets the driver sample id of the sample
    /// \param[in] driverSampleId sample id returned by the driver
    void SetDriverSampleId(const DriverSampleId& driverSampleId);

    /// Returns the driver sample id
    /// \return driver sample id
    DriverSampleId GetDriverSampleId() const;

    /// Returns the client sample id
    /// \return client sample id
    ClientSampleId GetClientSampleId() const;

    /// Sets the sample to be closed on a command list it was created
    GPA_THREAD_SAFE_FUNCTION bool SetAsClosedByClient();

    /// Sets the sample to be copied
    GPA_THREAD_SAFE_FUNCTION bool SetAsCopied();

    /// Returns a flag indicating whether the sample has been copied or not
    bool IsCopied() const;

    /// Marks the sample as having been continued on a different command list from the one which created it
    GPA_THREAD_SAFE_FUNCTION bool SetAsContinuedByClient();

    /// Returns flag indicating whether the sample has been continued by client or not
    /// \return true if the sample has been continued by client otherwise false
    bool IsContinuedByClient() const;

    /// Checks whether the sample is valid sample or not based on its status
    /// \return true if a sample is opened and either it is closed on command list on which it was created or it was continued on another command list; othewrwise false
    bool IsSampleValid() const;

    /// Checks whether the sample is closed or not
    /// \return true if sample is closed
    bool IsClosed() const;

    /// Checks whether the sample is secondary or not
    /// \return true if sample is secondary otherwise false
    bool IsSecondary() const;

protected:

    GPAPass*                    m_pPass;                        ///< GPA Pass Object
    IGPACommandList*            m_pGpaCmdList;                  ///< Pointer to the command list object
    GpaSampleType               m_gpaSampleType;                ///< type of the gpa sample
    ClientSampleId              m_clientSampleId;               ///< Client-assigned sample Id
    DriverSampleId              m_driverSampleId;               ///< Driver created sample id
    size_t                      m_activeCounters;               ///< The number of active counters in this request.
    GPASampleState              m_sampleState;                  ///< The state of this sample
    GPASampleResult*            m_pSampleResult;                ///< memory for sample Results
    GPASample*                  m_pContinuingSample;            ///< Pointer to linked/continuing GpaSample
    std::mutex                  m_sampleMutex;                  ///< mutex for the gpa sample object


    /// Marks the sample as being completed.
    /// Meaning that the results have been copied
    /// back to local memory.
    void MarkAsCompleted();

private:

    /// Delete default constructor
    GPASample() = delete;

    /// Checks whether the sample has been closed by client or not
    /// \return true if the sample has been closed by client otherwise false
    bool IsClosedByClient() const;

    /// Allocates resources to store counter results
    void AllocateSampleResultSpace();

    bool            m_isSecondary;                      ///< flag indicating sample is secondary or not i.e. it has been created on a bundle or not
    bool            m_isOpened;                         ///< flag indicating a sample is opened
    bool            m_isClosedByClient;                 ///< flag indicating a sample is closed or not by the command list on which it is created
    bool            m_isContinuedByClient;              ///< flag indicating a sampe has been continued on another command list
    bool            m_isCopiedSample;                   ///< flag indicating that sample has been copied to primary command list

    /// Start a counter sample.
    /// \param pGpaContext pointer to object containing the context information for this sample
    /// \param pCounters the set of counters to enable
    /// \return True if the sample could be started; false otherwise.
    virtual bool BeginRequest(IGPAContext* pGpaContext, const std::vector<gpa_uint32>* pCounters) = 0;

    /// Ends a counter sample.
    /// \return True on success; false on error.
    virtual bool EndRequest() = 0;

    /// Release allocated counters
    virtual void ReleaseCounters() = 0;
};

#endif // _GPA_SAMPLE_H_
