//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA Sample Header.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_SAMPLE_H_
#define GPU_PERF_API_COMMON_GPA_SAMPLE_H_

#include <mutex>
#include <vector>

#include "gpu_perf_api_common/gpa_common_defs.h"

class IGpaCommandList;
class IGpaContext;
class GpaPass;

using CounterIndex   = unsigned int;  ///< Type alias for counter index.
using ClientSampleId = unsigned int;  ///< Type alias for sample index.
using DriverSampleId = unsigned int;  ///< Type alias for index of the sample created by the driver extensions.

/// @brief Stores counter results after they are returned from the sample.
struct GpaCounterSampleResult;
struct GpaTraceSampleResult;

/// @brief Pure virtual base class for sample results.
///
/// This allows support for other types of GpaSampleResult derived results.
struct GpaSampleResult
{
    /// @brief Get the number of bytes in the buffer.
    ///
    /// @return The number of bytes in the buffer.
    virtual size_t GetBufferBytes() const = 0;

    /// @brief Get sample result as a counter sample result.
    ///
    /// @return A counter sample result, or nullptr if the sample result is not a valid counter sample result.
    virtual GpaCounterSampleResult* GetAsCounterSampleResult()
    {
        return nullptr;
    }

    virtual GpaTraceSampleResult* GetAsTraceSampleResult()
    {
        assert(0);
        return nullptr;
    }

    /// @brief Virtual destructor.
    virtual ~GpaSampleResult() = default;

protected:
    /// @brief Protected constructor.
    GpaSampleResult()
    {
    }
};

/// @brief The result of a counter sample.
struct GpaCounterSampleResult : public GpaSampleResult
{
    /// @brief Constructor.
    ///
    /// @param [in] num_of_counters Number of counters.
    GpaCounterSampleResult(size_t num_of_counters)
    {
        SetNumCounters(num_of_counters);
    }

    /// @copydoc GpaSampleResult::GetBufferBytes()
    virtual size_t GetBufferBytes() const override
    {
        return sizeof(uint64_t) * result_buffer_.size();
    }

    /// @copydoc GpaSampleResult::GetAsCounterSampleResult()
    virtual GpaCounterSampleResult* GetAsCounterSampleResult() override
    {
        return this;
    }

    /// @brief Sets the number of counters.
    ///
    /// @param [in] num_of_counters Number of counters.
    void SetNumCounters(size_t num_of_counters)
    {
        result_buffer_.clear();

        if (num_of_counters)
        {
            result_buffer_.resize(num_of_counters);
        }
    }

    /// @brief Returns the number of counters.
    ///
    /// @return Returns the number of counters.
    size_t GetNumCounters() const
    {
        return result_buffer_.size();
    }

    /// @brief Returns the output buffer.
    ///
    /// @return Returns the output buffer.
    GpaUInt64* GetResultBuffer()
    {
        return result_buffer_.data();
    }

private:
    std::vector<GpaUInt64> result_buffer_;  ///< An array of counter results.
};

/// Stores trace data after it is return from the sample
struct GpaTraceSampleResult : public GpaSampleResult
{
    /// Constructor
    GpaTraceSampleResult()
    {
    }

    /// Destructor
    virtual ~GpaTraceSampleResult()
    {
    }

    virtual GpaTraceSampleResult* GetAsTraceSampleResult() override
    {
        return this;
    }

    virtual size_t GetBufferBytes() const override
    {
        return m_resultBuffer.size();
    }

    void SetResultBufferSize(size_t numberOfBytes)
    {
        assert(numberOfBytes);
        m_resultBuffer.resize(numberOfBytes);
    }

    uint8_t* GetResultBuffer()
    {
        return m_resultBuffer.data();
    }

private:
    std::vector<uint8_t> m_resultBuffer;
};

/// @brief Enum for GPA Sample type.
enum class GpaSampleType
{
    kSoftware,  ///< Enum value for software samples.
    kHardware,  ///< Enum value for hardware samples.
    kSqtt,      ///< Enum value for SQTT samples.
    kSpm        ///< Enum value for SPM samples.
};

/// @brief Enum for the state of the GPA Sample.
enum class GpaSampleState
{
    kInitialized = 0,  ///< Sample has not yet started.
    kStarted,          ///< Sample is active, it has started but not yet ended.
    kPendingResults,   ///< Sample has ended, but results are not yet available.
    kResultsCollected  ///< Sample results are available, and cached locally.
};

/// @brief Class for representing GPA Sample object.
class GPA_NOT_THREAD_SAFE_OBJECT GpaSample
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] gpa_pass GPA Pass object.
    /// @param [in] gpa_cmd_list GPA command list.
    /// @param [in] sample_type Type of the sample.
    /// @param [in] client_sample_id User-supplied sample id.
    GpaSample(GpaPass* gpa_pass, IGpaCommandList* gpa_cmd_list, GpaSampleType sample_type, ClientSampleId client_sample_id);

    /// @brief Delete default constructor.
    GpaSample() = delete;

    /// @brief Virtual destructor.
    virtual ~GpaSample();

    /// @brief Checks whether the sample has linked sample.
    ///
    /// @return True if sample is linked to another GPA sample.
    bool IsSampleContinuing() const;

    /// @brief Returns the command list.
    ///
    /// @return Sample's command list.
    IGpaCommandList* GetCmdList() const;

    /// @brief Links the continuing sample.
    ///
    /// @param [in] continuing_sample Pointer to the continuing GPA sample.
    ///
    /// @return Returns true if sample can be linked to the current sample.
    bool LinkContinuingSample(GpaSample* continuing_sample);

    /// @brief Returns the pass Object.
    ///
    /// @return GpaPass object pointer.
    GpaPass* GetPass() const;

    /// @brief Should query this sample's results from the driver and store them in local memory.
    ///
    /// Once the results have been stored, use MarkAsCompleted() to move the sample into the Completed state, and return true from this method.
    ///
    /// @return True if the results from this sample have been updated and cached locally; false if the results are not available and cached locally.
    virtual bool UpdateResults() = 0;

    /// @brief Should confirm that results for this sample have been collected from the driver.
    ///
    /// @retval true If the sample's results have been copied back from the driver.
    /// @retval false If any sample is still pending.
    inline virtual bool IsResultCollected() const
    {
        return gpa_sample_state_ == GpaSampleState::kResultsCollected;
    }

    /// @brief Start a counter sample.
    ///
    /// @return True if the sample could be started; false otherwise.
    bool Begin();

    /// @brief Ends a counter sample.
    ///
    /// @return True on success; false on error.
    bool End();

    /// @brief Gets the result of a single counter within this sample.
    ///
    /// If this sample has secondary samples, or continued samples, they should be included
    /// in this sample's result. Although the return value is typed uint64, it may actually
    /// contain any 64-bit data type: uint64 or float64.
    ///
    /// @param [in] counter_index_in_sample A counter index within this sample.
    /// @param [out] counter_result A pointer to a 64-bit data type at which to store the counter result if it is available.
    ///
    /// @return True if the result is available and could be copied; False if the result is not available or an error occurred.
    virtual bool GetResult(CounterIndex counter_index_in_sample, GpaUInt64* counter_result) const;

    /// @brief Sets the driver sample id of the sample.
    ///
    /// @param [in] driver_sample_id Sample id returned by the driver.
    void SetDriverSampleId(const DriverSampleId& driver_sample_id);

    /// @brief Returns the driver sample id.
    ///
    /// @return Driver sample id.
    DriverSampleId GetDriverSampleId() const;

    /// @brief Returns the client sample id.
    ///
    /// @return Client sample id.
    ClientSampleId GetClientSampleId() const;

    /// @brief Sets the sample to be closed on a command list it was created.
    ///
    /// @return True if the sample was marked as closed successfully.
    GPA_THREAD_SAFE_FUNCTION bool SetAsClosedByClient();

    /// @brief Sets the sample to be copied.
    ///
    /// @return True if the sample was marked as copied successfully.
    GPA_THREAD_SAFE_FUNCTION bool SetAsCopied();

    /// @brief Returns a flag indicating whether or not the sample has been copied.
    ///
    /// @return True if the sample has been copied.
    bool IsCopied() const;

    /// @brief Marks the sample as having been continued on a different command list from the one which created it.
    ///
    /// @return True if the sample was marked as continued successfully.
    GPA_THREAD_SAFE_FUNCTION bool SetAsContinuedByClient();

    /// @brief Returns flag indicating whether or not the sample has been continued by client.
    ///
    /// @return True if the sample has been continued by client otherwise false.
    bool IsContinuedByClient() const;

    /// @brief Checks whether the sample is valid or not based on its status.
    ///
    /// @return True if a sample has been opened and either it has been closed on the command list on which it was created or it has been continued on another command list; othewrwise false.
    bool IsSampleValid() const;

    /// @brief Checks whether or not the sample is closed.
    ///
    /// @return True if sample is closed.
    bool IsClosed() const;

    /// @brief Checks whether or not the sample is secondary.
    ///
    /// @return True if sample is secondary otherwise false.
    bool IsSecondary() const;

    /// @brief Return the GPA sample result location.
    ///
    /// @return GPA sample result location.
    GpaSampleResult* GetSampleResultLocation() const;

protected:
    /// @brief Marks the sample as being completed.
    ///
    /// In other words, the results have been copied back to local memory.
    void MarkAsCompleted();

    /// @brief Returns the type of the sample.
    ///
    /// @return GPA sample type.
    GpaSampleType GetGpaSampleType() const;

    /// @brief Returns the state of the sample.
    ///
    /// @return GPA sample state.
    GpaSampleState GetGpaSampleState() const;

    /// @brief Returns the continuing sample.
    ///
    /// @return Pointer to continuing sample if exists otherwise nullptr.
    GpaSample* GetContinuingSample() const;

private:
    /// @brief Checks whether or not the sample has been closed by client.
    ///
    /// @return True if the sample has been closed by client otherwise false.
    bool IsClosedByClient() const;

    /// @brief Allocates resources to store counter results.
    void AllocateSampleResultSpace();

    /// @brief Start a counter sample.
    ///
    /// @return True if the sample could be started; false otherwise.
    virtual bool BeginRequest() = 0;

    /// @brief Ends a counter sample.
    ///
    /// @return True on success; false on error.
    virtual bool EndRequest() = 0;

    /// @brief Release allocated counters.
    virtual void ReleaseCounters() = 0;

    GpaPass*             gpa_pass_;               ///< GPA Pass Object.
    IGpaCommandList*     gpa_cmd_list_;           ///< Pointer to the command list object.
    GpaSampleType        gpa_sample_type_;        ///< Type of the GPA sample.
    ClientSampleId       client_sample_id_;       ///< Client-assigned sample id.
    DriverSampleId       driver_sample_id_;       ///< Driver created sample id.
    GpaSampleState       gpa_sample_state_;       ///< The state of this sample.
    GpaSampleResult*     sample_result_;          ///< Memory for sample Results.
    GpaSample*           continuing_sample_;      ///< Pointer to linked/continuing GpaSample.
    std::recursive_mutex continue_sample_mutex_;  ///< Recursive mutex for continuing sample pointer.
    std::mutex           sample_mutex_;           ///< Mutex for the GPA sample object.
    bool                 is_secondary_;  ///< Flag indicating a sample is a secondary sample; i.e. it has been created on a bundle or secondary command buffer.
    bool                 is_opened_;     ///< Flag indicating a sample is opened.
    bool                 is_closed_by_client_;     ///< Flag indicating a sample is closed by the command list on which it is created.
    bool                 is_continued_by_client_;  ///< Flag indicating a sample has been continued on another command list.
    bool                 is_copied_sample_;        ///< Flag indicating that sample has been copied to primary command list.
};

#endif  // GPU_PERF_API_COMMON_GPA_SAMPLE_H_
