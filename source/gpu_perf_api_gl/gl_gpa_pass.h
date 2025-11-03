//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GL GPA Pass Object Header
//==============================================================================

#ifndef GPU_PERF_API_GL_GL_GPA_PASS_H_
#define GPU_PERF_API_GL_GL_GPA_PASS_H_

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/gpa_pass.h"

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

using GlPerfMonitorId = GLuint;  ///< Type alias for GL performance monitor id.

/// @brief GLCounter Struct.
///
/// Structure used to store data that is needed to retrieve and store the
/// results for a counter.
struct GlCounter
{
    /// @brief Initializes a new instance of the GLCounter class
    GlCounter()
        : counter_id(0)
        , counter_type(0)
        , counter_group(0)
        , counter_group_instance(0)
        , counter_index(0)
        , is_counter_result_ready(false)
    {
    }

    GLuint counter_id;               ///< ID that is calculated in the CounterDefinition files.
    GLenum counter_type;             ///< Data type that GL specifies the result will be.
    GLuint counter_group;            ///< Group that this counter is in.
    GLuint counter_group_instance;   ///< Instance of the group that this counter is in.
    GLuint counter_index;            ///< Index to this counter within its group.
    bool   is_counter_result_ready;  ///< Indicates whether the result has been stored in the pCounterResult buffer.
};

/// @brief Class for OpenGL GPA pass.
class GlGpaPass : public GpaPass
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] gpa_session GPA session object pointer.
    /// @param [in] pass_index Pass index.
    /// @param [in] counter_source Counter source.
    /// @param [in] pass_counters Counter list for the pass.
    GlGpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters);

    /// @brief Destructor.
    ~GlGpaPass();

    /// @copydoc GpaPass::CreateApiSpecificSample()
    GpaSample* CreateApiSpecificSample(IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id) override final;

    /// @copydoc GpaPass::ContinueSample()
    bool ContinueSample(ClientSampleId src_sample_id, IGpaCommandList* primary_gpa_cmd_list) override final;

    /// @copydoc GpaPass::CreateApiSpecificCommandList()
    IGpaCommandList* CreateApiSpecificCommandList(void* cmd, CommandListId command_list_id, GpaCommandListType cmd_type) override final;

    /// @copydoc GpaPass::EndSample()
    bool EndSample(IGpaCommandList* cmd_list) override final;

    /// @brief Returns the existing GL performance monitor or creates a new one.
    ///
    /// @param [out] gl_perf_monitor_id Cached/new performance monitor Id.
    ///
    /// @return Success status of obtaining a GL performance monitor.
    /// @retval True on success.
    /// @retval False on failure.
    bool GetPerfMonitor(GlPerfMonitorId& gl_perf_monitor_id);

    /// @brief Marks the data for the passed performance monitor to be collected and it can be used as for cache.
    ///
    /// @param [in] gl_perf_monitor_id Performance monitor Id.
    void MarkDataCollected(const GlPerfMonitorId gl_perf_monitor_id);

    /// @brief Returns the GL counter in the pass.
    ///
    /// @param [in] counter_group Group of the counter.
    /// @param [in] counter_group_instance Group instance of the counter.
    /// @param [in] counter_index Index of the counter.
    /// @param [out] index_of_counter_within_pass Index of the counter within pass.
    ///
    /// @return Pointer to the GL counter if found otherwise nullptr.
    const GlCounter* GetGLCounter(const GLuint& counter_group,
                                  const GLuint& counter_group_instance,
                                  const GLuint& counter_index,
                                  unsigned int& index_of_counter_within_pass) const;

private:
    /// @brief Initializes the counter info for the passed performance Id.
    ///
    /// @param [in] gl_perf_monitor_id Performance monitor Id.
    ///
    /// @return Success status of initializing counters.
    /// @retval True on success.
    /// @retval False on failure.
    bool InitializeCounters(const GlPerfMonitorId& gl_perf_monitor_id);

    /// @brief Class for handling performance monitor.
    class GlPerfMonitor
    {
    public:
        /// @brief Constructor.
        GlPerfMonitor();

        /// @brief Initializes the performance monitor id.
        ///
        /// @return true upon successful operation otherwise false.
        bool Initialize();

        /// @brief Returns the performance monitor Id.
        ///
        /// @return GL performance monitor Id.
        GlPerfMonitorId GetPerfMonitorId() const;

        /// @brief Checks whether or not the data has been collected from the monitor.
        ///
        /// @return Success status on monitor data collection.
        /// @retval True on success.
        /// @retval False on failure.
        bool IsDataCollected() const;

        /// @brief Adds/increments the reference of the monitor.
        ///
        /// @return Value of the monitor reference after adding.
        unsigned int AddRef();

        /// @brief Release/decrements the reference of the monitor.
        ///
        /// @return value of the reference after releasing
        unsigned int Release();

        /// @brief Deletes the performance monitor in the driver if it's not being used.
        ///
        /// @param [in] force_clear Flag indicating whether the monitor needs to be deleted even if it's data is not populated.
        ///
        /// @return Success status on deleting the performance counter.
        /// @retval True on success.
        /// @retval False on failure.
        bool Clear(bool force_clear = false);

        /// @brief Destructor.
        ~GlPerfMonitor() = default;

    private:
        GlPerfMonitorId gl_perf_monitor_id_;  ///< Performance monitor ID.
        unsigned int    ref_count_;           ///< Reference count.
    };

    std::map<GlPerfMonitorId, GlPerfMonitor> gl_perf_monitor_info_list_;  ///< Map of performance monitor Id and GlPerfMonitor.
    mutable std::vector<GlCounter>           gl_counter_list_;            ///< List of counters in the pass.
};

#endif
