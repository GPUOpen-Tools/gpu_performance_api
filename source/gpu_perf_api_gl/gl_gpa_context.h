//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA GL Context declarations
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
    ~GlGpaContext();

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

private:
    /// @brief Validates the counter from counter generator and gl driver counters and updates it if necessary.
    ///
    /// @return Success status of validation.
    /// @retval True on success.
    /// @retval False on failure.
    bool ValidateAndUpdateGlCounters() const;

    GlContextPtr             gl_context_;      ///< GL rendering context pointer.
    ogl_utils::AmdXClockMode clock_mode_;      ///< GPU Clock mode.
    int                      driver_version_;  ///< GL driver version.
};

#endif  // GPU_PERF_API_GL_GPA_CONTEXT_H_
