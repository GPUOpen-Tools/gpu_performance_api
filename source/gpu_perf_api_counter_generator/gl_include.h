//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL include files and common util functions
//==============================================================================

#ifndef _GL_INCLUDE_H_
#define _GL_INCLUDE_H_


#ifndef GLES

#ifdef _WIN32
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#endif

#ifdef _LINUX
#include <GL/glx.h>
#include <GL/glxext.h>
#endif

#else

#ifdef _WIN32
typedef unsigned __int64 uint64_t;
#endif

// by default, GLES uses 32 bits for 64 bit types. GPA extensions require 64 bits
#define _USE64BIT
#include <stdint.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>

#ifndef GL_TIMESTAMP
#define GL_TIMESTAMP GL_TIMESTAMP_EXT
#endif

#ifndef APIENTRY
#define APIENTRY GL_APIENTRY
#endif

#ifndef GL_STACK_OVERFLOW
#define GL_STACK_OVERFLOW                 0x0503
#endif

#ifndef GL_STACK_UNDERFLOW
#define GL_STACK_UNDERFLOW                0x0504
#endif

#endif

#include <string>
#include <cassert>

#include "logging.h"

namespace oglUtils
{
    extern const int s_GL_DRIVER_VER_WITH_ONLY_GCN_SUPPORT;             ///< GL driver version where pre-GCN hardware was dropped
    extern const int s_GL_DRIVER_VER_WITH_LINUX_STABLE_CLOCK_SUPPORT;   ///< GL driver version where stable clocks are working on Linux
    extern const int s_GL_DRIVER_VER_WITH_GPIN_COUNTERS;                ///< GL driver version where GPIN counters have been validated

    /// checks for OpenGL errors, logs the specified message if there is an error, and return true / false to indicate an error.
    /// This can be used anywhere, but should only be used in conditionals where the return value is needed; otherwise, use the
    /// \param onErrorMessage the error message to put in the log
    /// \return true if there is an error; false if there is no error
    extern bool CheckForGLError(const std::string& onErrorMessage);
}  // namespace oglUtils

#endif  // _GL_INCLUDE_H_