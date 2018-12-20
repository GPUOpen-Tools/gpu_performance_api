//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
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

class GPAPass;         // forward declaration
class IGPACommandList; // forward declaration
class IGPAContext;     // forward declaration

using CounterIndex = unsigned int;   ///< type alias for counter index
using ClientSampleId = unsigned int; ///< type alias for sample index
using DriverSampleId = unsigned int; ///< type alias for index of the sample created by the driver extensions

/// Stores counter results after they are returned from the sample.
struct GPACounterSampleResult;

/// Pure virtual base class for sample results
/// This allows support for other types of GPASampleResult derived results in the future
struct GPASampleResult
{
    virtual size_t GetBufferBytes() const = 0;

    virtual GPACounterSampleResult* GetAsCounterSampleResult() { return nullptr; }

    virtual ~GPASampleResult() = default;

protected:
    GPASampleResult() {}
};

struct GPACounterSampleResult : public GPASampleResult
{
    /// Constructor
    /// \param[in] numOfCounters number of counters
    GPACounterSampleResult(size_t numOfCounters)
    {
        SetNumCounters(numOfCounters);
    }

    virtual size_t GetBufferBytes() const override
    {
        return sizeof(uint64_t) * m_resultBuffer.size();
    }

    virtual GPACounterSampleResult* GetAsCounterSampleResult() override
    {
        return this;
    }

    /// Sets the number of counters
    /// \param[in] numOfCounters Number of counters
    void SetNumCounters(size_t numOfCounters)
    {
        m_resultBuffer.clear();

        if (numOfCounters)
        {
            m_resultBuffer.resize(numOfCounters);
        }
    }

    /// Returns the number of counters
    /// \return Returns the number of counters
    size_t GetNumCounters() const
    {
        return m_resultBuffer.size();
    }

    /// Returns the output buffer
    /// \return Returns the output buffer
    gpa_uint64* GetResultBuffer()
    {
        return m_resultBuffer.data();
    }

private:
    std::vector<gpa_uint64> m_resultBuffer; ///< An array of counter results.
};

/// Enum for GPA Sample type
enum class GpaSampleType
{
    Software, ///< enum value for software samples
    Hardware  ///< enum value for hardware samples
};

/// Enum for the state of the GPA Sample.
enum class GPASampleState
{
    INITIALIZED = 0,  ///< Sample has not yet started
    STARTED,          ///< Sample is active, it has started but not yet ended
    PENDING_RESULTS,  ///< Sample has ended, but results are not yet available
    RESULTS_COLLECTED ///< Sample results are available, and cached locally
};

/// Class for representing GPA Sample object
class GPA_NOT_THREAD_SAFE_OBJECT GPASample
{
public:

    /// Constructor
    /// \param[in] pPass GPA Pass object
    /// \param[in] pGpaCmdList GPA command list
    /// \param[in] sampleType type of the sample
    /// \param[in] clientSampleId user-supplied sample id
    GPASample(GPAPass* pPass,
              IGPACommandList* pGpaCmdList,
              GpaSampleType sampleType,
              ClientSampleId clientSampleId);

    /// Delete default constructor
    GPASample() = delete;

    /// Destructor
    virtual ~GPASample();

    /// Checks whether the sample has linked sample
    /// \return true if sample is linked to another GPA sample
    bool IsSampleContinuing() const;

    /// Returns the command list
    /// \return sample's command list
    IGPACommandList* GetCmdList() const;

    /// Links the continuing sample
    /// \param[in] pContinuingSample pointer to the continuing GPA sample
    /// \return returns true if sample can be linked to the current sample
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
    inline virtual bool IsResultCollected() const
    {
        return m_gpaSampleState == GPASampleState::RESULTS_COLLECTED;
    }

    /// Start a counter sample.
    /// \return True if the sample could be started; false otherwise.
    bool Begin();

    /// Ends a counter sample.
    /// \return True on success; false on error.
    bool End();

    /// Gets the result of a single counter within this sample.
    /// If this sample has secondary samples, or continued samples, they should be included
    /// in this sample's result. Although the return value is typed uint64, it may actually
    /// contain any 64-bit data type: uint64 or float64
    /// \param[in] counterIndexInSample A counter index within this sample.
    /// \param[out] pResult A pointer to a 64-bit data type at which to store the counter result if it is available.
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
    /// \return true if the sample was marked as closed successfully
    GPA_THREAD_SAFE_FUNCTION bool SetAsClosedByClient();

    /// Sets the sample to be copied
    /// \return true if the sample was marked as copied successfully
    GPA_THREAD_SAFE_FUNCTION bool SetAsCopied();

    /// Returns a flag indicating whether or not the sample has been copied
    /// \return true if the sample has been copied
    bool IsCopied() const;

    /// Marks the sample as having been continued on a different command list from the one which created it
    /// \return true if the sample was marked as continued successfully
    GPA_THREAD_SAFE_FUNCTION bool SetAsContinuedByClient();

    /// Returns flag indicating whether or not the sample has been continued by client
    /// \return true if the sample has been continued by client otherwise false
    bool IsContinuedByClient() const;

    /// Checks whether the sample is valid or not based on its status
    /// \return true if a sample has been opened and either it has been closed on the command list on which it was created or it has been continued on another command list; othewrwise false
    bool IsSampleValid() const;

    /// Checks whether or not the sample is closed
    /// \return true if sample is closed
    bool IsClosed() const;

    /// Checks whether or not the sample is secondary
    /// \return true if sample is secondary otherwise false
    bool IsSecondary() const;

protected:

    /// Marks the sample as being completed
    /// Meaning that the results have been copied
    /// back to local memory.
    void MarkAsCompleted();

    /// Returns the type of the sample
    /// \return GPA sample type
    GpaSampleType GetGpaSampleType() const;

    /// Returns the state of the sample
    /// \return GPA sample state
    GPASampleState GetGpaSampleState() const;

    /// Return the GPA sample result location
    /// \return GPA sample result location
    GPASampleResult* GetSampleResultLocation() const;

    /// Returns the continuing sample
    /// \return pointer to continuing sample if exists otherwise nullptr
    GPASample* GetContinuingSample() const;

private:

    /// Checks whether or not the sample has been closed by client
    /// \return true if the sample has been closed by client otherwise false
    bool IsClosedByClient() const;

    /// Allocates resources to store counter results
    void AllocateSampleResultSpace();

    /// Start a counter sample
    /// \return True if the sample could be started; false otherwise
    virtual bool BeginRequest() = 0;

    /// Ends a counter sample
    /// \return True on success; false on error
    virtual bool EndRequest() = 0;

    /// Release allocated counters
    virtual void ReleaseCounters() = 0;

    GPAPass*             m_pPass;               ///< GPA Pass Object
    IGPACommandList*     m_pGpaCmdList;         ///< Pointer to the command list object
    GpaSampleType        m_gpaSampleType;       ///< type of the GPA sample
    ClientSampleId       m_clientSampleId;      ///< Client-assigned sample Id
    DriverSampleId       m_driverSampleId;      ///< Driver created sample id
    GPASampleState       m_gpaSampleState;      ///< The state of this sample
    GPASampleResult*     m_pSampleResult;       ///< memory for sample Results
    GPASample*           m_pContinuingSample;   ///< Pointer to linked/continuing GpaSample
    std::recursive_mutex m_continueSampleMutex; ///< recursive mutex for continuing sample pointer
    std::mutex           m_sampleMutex;         ///< mutex for the GPA sample object
    bool                 m_isSecondary;         ///< flag indicating a sample is a secondary sample; i.e. it has been created on a bundle or secondary command buffer
    bool                 m_isOpened;            ///< flag indicating a sample is opened
    bool                 m_isClosedByClient;    ///< flag indicating a sample is closed by the command list on which it is created
    bool                 m_isContinuedByClient; ///< flag indicating a sample has been continued on another command list
    bool                 m_isCopiedSample;      ///< flag indicating that sample has been copied to primary command list
};

#endif // _GPA_SAMPLE_H_
