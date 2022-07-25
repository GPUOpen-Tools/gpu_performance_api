//==============================================================================
// Copyright (c) 2018-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GL GPA Sample Implementation
//==============================================================================

#include "gpu_perf_api_gl/gl_gpa_sample.h"

#include <chrono>
#include <thread>

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

GlGpaSample::GlGpaSample(GpaPass* pass, IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id)
    : GpaSample(pass, cmd_list, sample_type, sample_id)
    , gl_gpa_pass_(reinterpret_cast<GlGpaPass*>(pass))
{
    if (gl_gpa_pass_->IsTimingPass())
    {
        CreateGpuTimeQuery();
    }
}

GlGpaSample::~GlGpaSample()
{
    if (gl_gpa_pass_->IsTimingPass())
    {
        DeleteGpuTimeQueries();
    }
}

bool GlGpaSample::UpdateResults()
{
    bool is_data_collected = IsResultCollected();

    if (!is_data_collected)
    {
        const uint32_t timeout    = 10000;  // ms
        auto           start_time = std::chrono::high_resolution_clock::now();

        do
        {
            is_data_collected = CopyResults();

            if (!is_data_collected)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(0));

                auto                                      end_time     = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;

                if (elapsed_time.count() > timeout)
                {
                    GPA_LOG_ERROR("Failed to collect counter data due to elapsed timeout.");
                    break;
                }
            }
        } while (!is_data_collected);

        if (is_data_collected)
        {
            MarkAsCompleted();
        }
    }

    return is_data_collected;
}

bool GlGpaSample::BeginRequest()
{
    bool success = false;

    if (gl_gpa_pass_->IsTimingPass())
    {
        // Handle timing pass.
        ogl_utils::ogl_query_counter(sample_data_buffer_.gpu_time_query[0], GL_TIMESTAMP);

        if (!ogl_utils::CheckForGlError("Unable to begin the GL timing query."))
        {
            success = true;
        }
    }
    else
    {
        if (gl_gpa_pass_->GetPerfMonitor(sample_data_buffer_.gl_perf_monitor_id))
        {
            ogl_utils::ogl_begin_perf_monitor_amd(sample_data_buffer_.gl_perf_monitor_id);

            if (!ogl_utils::CheckForGlError("Unable to begin the GL perf monitor."))
            {
                success = true;
            }
        }
    }

    return success;
}

bool GlGpaSample::EndRequest()
{
    bool success = false;

    if (gl_gpa_pass_->IsTimingPass())
    {
        // Handle timing pass.
        ogl_utils::ogl_query_counter(sample_data_buffer_.gpu_time_query[1], GL_TIMESTAMP);

        if (!ogl_utils::CheckForGlError("Unable to begin the GL timing query."))
        {
            success = true;
        }
    }
    else
    {
        // Inserting a glFlush() before and after the EndPerfMonitor call appears to make a number of the results more consistent.
        // The effects of the first glFlush() is extremely noticeable with the GLFiveQuarterQuads test and the PostZSamplesPassing counter.
        // The effects of the second glFlush() are noticeable with last draw call of the GLFiveQuarterQuads test and the PreZSamplesPassing counter.
        // The effects of the second glFlush() are also noticeable with last draw call of the GLFiveQuarterQuads test and the CBMemWritten counter.
        ogl_utils::ogl_flush();

        ogl_utils::ogl_end_perf_monitor_amd(sample_data_buffer_.gl_perf_monitor_id);

        if (!ogl_utils::CheckForGlError("Unable to end the GL perf monitor."))
        {
            success = true;
        }

        ogl_utils::ogl_flush();
    }

    return success;
}

void GlGpaSample::ReleaseCounters()
{
    GPA_STUB_FUNCTION;
}

bool GlGpaSample::CopyResults()
{
    bool success = false;

    GpaSampleResult* sample_result = GetSampleResultLocation();

    if (gl_gpa_pass_->IsTimingPass())
    {
        // Get the results.
        GLuint64EXT gpu_time_results[2];
        gpu_time_results[0] = 0ull;
        gpu_time_results[1] = 0ull;

        GLuint64 is_ready = GL_FALSE;
        while (!is_ready)
        {
            ogl_utils::ogl_get_query_object_ui_64_v_ext(sample_data_buffer_.gpu_time_query[0], GL_QUERY_RESULT_AVAILABLE, &is_ready);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        ogl_utils::ogl_get_query_object_ui_64_v_ext(sample_data_buffer_.gpu_time_query[0], GL_QUERY_RESULT, &gpu_time_results[0]);

        if (!ogl_utils::CheckForGlError("Unable to get first timing data."))
        {
            ogl_utils::ogl_get_query_object_ui_64_v_ext(sample_data_buffer_.gpu_time_query[1], GL_QUERY_RESULT, &gpu_time_results[1]);

            if (!ogl_utils::CheckForGlError("Unable to get second timing data."))
            {
                GpaUInt64 timing_difference = gpu_time_results[1] - gpu_time_results[0];
                memcpy(sample_result->GetAsCounterSampleResult()->GetResultBuffer(), &timing_difference, sizeof(GpaUInt64));
                success = true;
            }
        }
    }
    else
    {
        GLuint          results_available = GL_FALSE;
        GlPerfMonitorId perf_monitor_id   = sample_data_buffer_.gl_perf_monitor_id;
        ogl_utils::ogl_get_perf_monitor_counter_data_amd(perf_monitor_id, GL_PERFMON_RESULT_AVAILABLE_AMD, sizeof(GLuint), &results_available, nullptr);

        if (!ogl_utils::CheckForGlError("Unable to get the data."))
        {
            if (GL_TRUE == results_available)
            {
                CounterCount counter_count = gl_gpa_pass_->GetEnabledCounterCount();

                // Get size of the results array.
                GLuint result_size = 0;
                ogl_utils::ogl_get_perf_monitor_counter_data_amd(perf_monitor_id, GL_PERFMON_RESULT_SIZE_AMD, sizeof(GLint), &result_size, nullptr);

                if (!ogl_utils::CheckForGlError("Unable to get the counter data size."))
                {
                    // Obtain the actual results.
                    GLuint* counter_data = reinterpret_cast<GLuint*>(malloc(result_size));
                    assert(nullptr != counter_data);

                    GLsizei bytes_written = 0;
                    ogl_utils::ogl_get_perf_monitor_counter_data_amd(perf_monitor_id, GL_PERFMON_RESULT_AMD, result_size, counter_data, &bytes_written);

                    if (!ogl_utils::CheckForGlError("Unable to get the counter data."))
                    {
                        // UGL and OGLP have two different result structures:
                        // UGL:
                        // +----------------------------------------+-----------
                        // |  BlockID  |  CounterID  |  result data |  BlockID ...
                        // +----------------------------------------+-----------
                        //
                        // OGLP:
                        // +---------------------------------------------------------+-----------
                        // |  BlockID  |  BlockInstance |  CounterID  |  result data |  BlockID ...
                        // +---------------------------------------------------------+-----------
                        //
                        // So, it may not be in the same order it was specified.

                        CounterCount num_counter_results = 0;
                        if (ogl_utils::IsOglpDriver())
                        {
                            // OGLP returns 4 GLuint values.
                            num_counter_results = result_size / (4 * sizeof(GLuint));
                        }
                        else
                        {
                            // Other drivers return 3 GLuint values;
                            num_counter_results = result_size / (3 * sizeof(GLuint));
                        }

                        if (num_counter_results != counter_count)
                        {
                            // This is not expected, but seems to be happening.
                            // Update the counter_count to avoid reading past the end of the results buffer.
                            counter_count = num_counter_results;
                        }

                        // Cycle through all the counters and store the data.
                        GLsizei word_index = 0;

                        for (CounterCount counter_count_iter = 0; counter_count_iter < counter_count; counter_count_iter++)
                        {
                            // GL may return the data in a different order than expected.
                            // Find the correct counter to assign the data to.
                            GLuint  group_id       = 0;
                            GLuint  group_instance = 0;
                            GLuint  counter_id     = 0;
                            GLuint* data           = nullptr;

                            if (ogl_utils::IsOglpDriver())
                            {
                                group_id       = counter_data[word_index++];
                                group_instance = counter_data[word_index++];
                                counter_id     = counter_data[word_index++];
                                data           = &counter_data[word_index];
                            }
                            else
                            {
                                group_id       = counter_data[word_index++];
                                group_instance = 0;
                                counter_id     = counter_data[word_index++];
                                data           = &counter_data[word_index];
                            }
                            unsigned int cur_counter_result_index = 0u;

                            const GlCounter* gl_counter = gl_gpa_pass_->GetGLCounter(group_id, group_instance, counter_id, cur_counter_result_index);

                            if (nullptr != gl_counter)
                            {
                                GLuint* dest =
                                    reinterpret_cast<GLuint*>(&sample_result->GetAsCounterSampleResult()->GetResultBuffer()[cur_counter_result_index]);
                                dest[0] = 0;
                                dest[1] = 0;

                                if (gl_counter->counter_type == GL_UNSIGNED_INT64_AMD)
                                {
                                    word_index += 2;
                                    memcpy(dest, data, sizeof(GLuint) * 2);
                                    success = true;
                                }
                                else if (gl_counter->counter_type == GL_FLOAT)
                                {
                                    word_index += 1;
                                    memcpy(dest, data, sizeof(GLfloat));
                                    success = true;
                                }
                                else if (gl_counter->counter_type == GL_UNSIGNED_INT)
                                {
                                    word_index += 1;
                                    memcpy(dest, data, sizeof(GLuint));
                                    success = true;
                                }
                                else if (gl_counter->counter_type == GL_PERCENTAGE_AMD)
                                {
                                    word_index += 1;
                                    memcpy(dest, data, sizeof(GLfloat));
                                    success = true;
                                }
                                else if (gl_counter->counter_type == GL_INT)
                                {
                                    word_index += 1;
                                    memcpy(dest, data, sizeof(GLint));
                                    success = true;
                                }
                                else
                                {
                                    assert(!"CounterType not recognized.");
                                }
                            }
                            else
                            {
                                // Probably indicates that invalid data was in the results buffer from the driver.
                                assert(!"GLCounter not found.");
                            }
                        }
                    }

                    free(counter_data);
                }
            }
        }
    }

    return success;
}

bool GlGpaSample::CreateGpuTimeQuery()
{
    // Create the timer query.
    ogl_utils::ogl_gen_queries(2, sample_data_buffer_.gpu_time_query);
    return !ogl_utils::CheckForGlError("Unable to create GPU time queries.");
}

bool GlGpaSample::DeleteGpuTimeQueries()
{
    bool success = false;

    // Checks added to workaround a potential driver bug. Normally, queries with nameID of 0
    // should be ignored. What is happening though is that deleting a query with name 0 is
    // marking name 0 as free so it can be used again. Subsequent calls to GenQueries will
    // return a name id of 0, which should never happen.
    if (sample_data_buffer_.gpu_time_query[0] != 0)
    {
        ogl_utils::ogl_delete_queries(1, &sample_data_buffer_.gpu_time_query[0]);
        success = !ogl_utils::CheckForGlError("Unable to delete the first GPU time query.");
    }

    if (success && sample_data_buffer_.gpu_time_query[1] != 0)
    {
        ogl_utils::ogl_delete_queries(1, &sample_data_buffer_.gpu_time_query[1]);
        success = !ogl_utils::CheckForGlError("Unable to delete the second GPU time query.");
    }

    sample_data_buffer_.gpu_time_query[0] = 0;
    sample_data_buffer_.gpu_time_query[1] = 0;

    return success;
}
