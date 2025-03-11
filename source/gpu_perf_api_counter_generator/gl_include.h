//==============================================================================
// Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GL include files and common util functions.
//==============================================================================

#ifndef GPA_COUNTER_GENERATOR_GL_INCLUDE_H_
#define GPA_COUNTER_GENERATOR_GL_INCLUDE_H_

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

// By default, GLES uses 32 bits for 64 bit types. GPA extensions require 64 bits.
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
#define GL_STACK_OVERFLOW 0x0503
#endif

#ifndef GL_STACK_UNDERFLOW
#define GL_STACK_UNDERFLOW 0x0504
#endif

#endif

#include <string>
#include <cassert>

#include "gpu_perf_api_common/logging.h"

namespace ogl_utils
{
    extern const int kGlDriverVerSwitchToOglp;  ///< GL driver version where we switched from Ugl to Oglp.

    /// Checks for OpenGL errors, logs the specified message if there is an error, and return true / false to indicate an error.
    ///
    /// This can be used anywhere, but should only be used in conditionals where the return value is needed.
    ///
    /// @param error_message The error message to put in the log.
    ///
    /// @return true if there is an error; false if there is no error.
    extern bool CheckForGlError(const std::string& error_message);
}  // namespace ogl_utils

#endif  // GPA_COUNTER_GENERATOR_GL_INCLUDE_H_

