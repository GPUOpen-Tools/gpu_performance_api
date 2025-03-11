//==============================================================================
// Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GL GPA Sample Header
//==============================================================================

#ifndef GPU_PERF_API_GL_GL_GPA_SAMPLE_H_
#define GPU_PERF_API_GL_GL_GPA_SAMPLE_H_

#include <vector>

#include "gpa_sample.h"
#include "gl_gpa_pass.h"

/// @brief Class for GL Specific sample.
class GlGpaSample : public GpaSample
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] pass GPA Pass object.
    /// @param [in] cmd_list GPA command list.
    /// @param [in] sample_type GPA sample type.
    /// @param [in] sample_id User supplied sample id.
    GlGpaSample(GpaPass* pass, IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id);

    /// @brief Delete default constructor.
    GlGpaSample() = delete;

    /// @brief Destructor
    virtual ~GlGpaSample();

    /// @copydoc GpaSample::UpdateResults()
    bool UpdateResults() override final;

    /// @copydoc GpaSample::BeginRequest()
    bool BeginRequest() override final;

    /// @copydoc GpaSample::EndRequest()
    bool EndRequest() override final;

    /// @copydoc GpaSample::ReleaseCounters()
    void ReleaseCounters() override final;

private:
    /// @brief Copies the result from the driver to sample result buffer.
    ///
    /// @return Success status of copying the result from the driver to sample buffer.
    /// @retval True on success.
    /// @retval False on failure.
    bool CopyResults();

    /// @brief Creates the GPU time query.
    ///
    /// @return Success status on creating the GPU time query.
    /// @retval True on success.
    /// @retval False on failure.
    bool CreateGpuTimeQuery();

    /// @brief Deletes the GPU time query.
    ///
    /// @return Success status on deleting the GPU time query.
    /// @retval True on success.
    /// @retval False on failure.
    bool DeleteGpuTimeQueries();

    /// @brief SampleDataBuffer union.
    union SampleDataBuffer
    {
        /// @brief Constructor.
        SampleDataBuffer()
            : gl_perf_monitor_id(0u)
        {
            gpu_time_query[0] = gpu_time_query[1] = 0u;
        }

        GLuint          gpu_time_query[2];   ///< The Query used to get GPUTime results.
        GlPerfMonitorId gl_perf_monitor_id;  ///< Sample perf monitor Id for hardware counters.
    };

    GlGpaPass*       gl_gpa_pass_;         ///< Cache the GPA pass pointer.
    SampleDataBuffer sample_data_buffer_;  ///< Buffer for getting data from driver.
};

#endif  // GPU_PERF_API_GL_GL_GPA_SAMPLE_H_
