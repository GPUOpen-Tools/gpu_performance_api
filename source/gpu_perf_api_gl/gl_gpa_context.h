//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA GL Context declarations
//==============================================================================

#ifndef _GL_GPA_CONTEXT_H_
#define _GL_GPA_CONTEXT_H_

#include "gl_entry_points.h"
#include "gl_amd_driver_ext.h"

// GPA Common
#include "gpa_context.h"

#ifndef GLES
#ifdef _WIN32
using GLContextPtr = HGLRC;  ///< type alias for GL Context
#else
using GLContextPtr = GLXContext;  ///< type alias for GL Context
#endif
#else
using GLContextPtr = EGLContext;  ///< type alias for GL Context
#endif  // GLES

/// Class for OpenGL GPA Context
class GLGPAContext : public GPAContext
{
public:
    /// Constructor
    /// \param[in] context context pointer
    /// \param[in] pHwInfo the hardware info used to create the context
    /// \param[in] contextFlags the flags used to create the context
    /// \param[in] driverVersion the version number of the GL driver
    GLGPAContext(GLContextPtr context, GPA_HWInfo& pHwInfo, GPA_OpenContextFlags contextFlags, int driverVersion);

    /// Destructor
    ~GLGPAContext();

    /// \copydoc IGPAContext::CreateSession()
    GPA_SessionId CreateSession(GPA_Session_Sample_Type sampleType) override;

    /// \copydoc IGPAContext::DeleteSession()
    bool DeleteSession(GPA_SessionId sessionId) override;

    /// \copydoc IGPAContext::GetMaxGPASessions()
    gpa_uint32 GetMaxGPASessions() const override;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// Initializes the OpenGL context
    /// \return true if initialization is successful otherwise false
    bool Initialize();

    /// Gets the GL rendering context
    /// \return the GL rendering context
    const GLContextPtr& GetGLContext() const;

    /// \copydoc IGPAContext::SetStableClocks()
    GPA_Status SetStableClocks(bool useProfilingClocks) override;

private:
    /// Validates the counter from counter generator and gl driver counters and updates it if necessary
    /// \return true upon successful operation otherwise false
    bool ValidateAndUpdateGLCounters() const;

    GLContextPtr            m_glContext;      ///< GL rendering context pointer
    oglUtils::AMDXClockMode m_clockMode;      ///< GPU Clock mode
    int                     m_driverVersion;  ///< GL driver version
};

#endif  // _CL_GPA_CONTEXT_H_
