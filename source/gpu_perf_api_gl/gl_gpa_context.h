//==============================================================================
// Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA GL Context declarations.
//==============================================================================

#ifndef GPU_PERF_API_GL_GPA_CONTEXT_H_
#define GPU_PERF_API_GL_GPA_CONTEXT_H_

#include "gpu_perf_api_common/gpa_context.h"

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

#include "gpu_perf_api_gl/gl_amd_driver_ext.h"

#ifndef GLES
#ifdef _WIN32
using GlContextPtr = HGLRC;  ///< Type alias for GL Context.
#else
using GlContextPtr = GLXContext;  ///< Type alias for GL Context.
#endif
#else
using GlContextPtr = EGLContext;  ///< Type alias for GL Context.
#endif  // GLES

/// @brief Class for OpenGL GPA Context
class GlGpaContext : public GpaContext
{
public:
    /// @brief Constructor
    ///
    /// @param [in] context Context pointer.
    /// @param [in] hw_info The hardware info used to create the context.
    /// @param [in] context_flags The flags used to create the context.
    /// @param [in] driver_version The version number of the GL driver.
    GlGpaContext(GlContextPtr context, GpaHwInfo& hw_info, GpaOpenContextFlags context_flags, int driver_version);

    /// @brief Destructor.
    virtual ~GlGpaContext();

    /// @copydoc IGpaContext::CreateSession()
    GpaSessionId CreateSession(GpaSessionSampleType sample_type) override;

    /// @copydoc IGpaContext::DeleteSession()
    bool DeleteSession(GpaSessionId session_id) override;

    /// @copydoc IGpaContext::GetMaxGpaSessions()
    GpaUInt32 GetMaxGpaSessions() const override;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

    /// @brief Initializes the OpenGL context.
    ///
    /// @return Success status of initialization.
    /// @retval True on success.
    /// @retval False on failure.
    bool Initialize();

    /// @brief Gets the GL rendering context.
    ///
    /// @return The GL rendering context.
    const GlContextPtr& GetGlContext() const;

    /// @copydoc IGpaContext::SetStableClocks()
    GpaStatus SetStableClocks(bool use_profiling_clocks) override;

    /// @brief Get the number of instances of the specified group.
    ///
    /// @param [in] driver_group_id The group id whose number of instances is needed.
    ///
    /// @return The number of instances of the specific group. Could be zero if group does not exist.
    GpaUInt32 GetNumInstances(unsigned int driver_group_id) const;

    /// @brief Get the max event id of the specified group.
    ///
    /// @param [in] block The group id whose max event id is needed.
    ///
    /// @return the max event id of the specified group. Could be zero if group does not exist.
    GpaUInt32 GetMaxEventId(unsigned int driver_group_id) const;

    /// @brief Validates the counter from counter generator and GL driver counters and updates it if necessary.
    ///
    /// @return Success status of validation.
    /// @retval True on success.
    /// @retval False on failure.
    bool ValidateAndUpdateGlCounters(IGpaSession* session) const;

private:
    /// @brief Structure to store the information about a specific counter group exposed from the gl_amd_performance_monitor extension.
    struct GpaGlPerfMonitorGroupData
    {
        static const int kMaxNameLength = 10;  ///< Max number of characters in the group name, including ending NULL character.

        GLuint group_id;                                   ///< The driver-assigned group id.
        GLchar group_name[kMaxNameLength];                 ///< The driver-assigned group name.
        GLuint num_instances;                              ///< The number of instances of this group available on the current hardware.
        GLint  num_counters;                               ///< The number of counter events that are exposed by this group.
        GLint  max_active_discrete_counters_per_instance;  ///< The number of counters that can be enabled simultaneously.
    };

    /// @brief Queries the information exposed by the driver via the performance monitor extension and caches it for later use.
    ///
    /// @retval True If the counter group information could be queried successfully.
    /// @retval False If there were errors or unexpected situations while querying the counter group information.
    bool PopulateDriverCounterGroupInfo();

    GlContextPtr             gl_context_;      ///< GL rendering context pointer.
    ogl_utils::AmdXClockMode clock_mode_;      ///< GPU Clock mode.
    int                      driver_version_;  ///< GL driver version.

    typedef std::vector<GpaGlPerfMonitorGroupData> GpaGlPerfGroupVector;
    GpaGlPerfGroupVector                           driver_counter_group_info_;  ///< All the counter group information from the driver.
    bool                                           driver_supports_GL1CG_;      ///< Not all hardware supports the GL1CG block, so detect when it exists.
    bool                                           driver_supports_ATCL2_;      ///< Not all hardware supports the ATCL2 block, so detect when it exists.
    bool                                           driver_supports_CHCG_;       ///< Not all hardware supports the CHCG block, so detect when it exists.
    bool                                           driver_supports_GUS_;        ///< Not all hardware supports the GUS block, so detect when it exists.
    bool                                           driver_supports_UMC_;        ///< Not all hardware supports the UMC block, so detect when it exists.
    bool                                           driver_supports_RPB_;        ///< Not all hardware supports the RPB block, so detect when it exists.
    bool                                           driver_supports_PC_;         ///< Not all hardware supports the PC block, so detect when it exists.
    bool                                           driver_supports_GRBMSE_;     ///< Not all hardware supports the GRBMSE blocks, so detect when they exist.
};

#endif  // GPU_PERF_API_GL_GPA_CONTEXT_H_
