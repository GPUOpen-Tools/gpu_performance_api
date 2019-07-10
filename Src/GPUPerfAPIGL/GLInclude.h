//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL include files and common util functions
//==============================================================================

#ifndef _GL_INCLUDE_H_
#define _GL_INCLUDE_H_

#include <string>
#include <cassert>

#include "GLEntryPoints.h"
#include "GLAmdDriverExt.h"
#include "Logging.h"

#if defined(GLES)
#ifndef GL_TIMESTAMP
#define GL_TIMESTAMP GL_TIMESTAMP_EXT
#endif  // GL_TIMESTAMP
#endif  // GLES

namespace oglUtils
{
    static const int s_GL_DRIVER_VER_WITH_ONLY_GCN_SUPPORT           = 13452;  ///< GL driver version where pre-GCN hardware was dropped
    static const int s_GL_DRIVER_VER_WITH_LINUX_STABLE_CLOCK_SUPPORT = 13562;  ///< GL driver version where stable clocks are working on Linux
    static const int s_GL_DRIVER_VER_WITH_GPIN_COUNTERS              = 13565;  ///< GL driver version where GPIN counters have been validated

    /// checks for OpenGL errors, logs the specified message if there is an error, and return true / false to indicate an error.
    /// This can be used anywhere, but should only be used in conditionals where the return value is needed; otherwise, use the
    /// \param onErrorMessage the error message to put in the log
    /// \return true if there is an error; false if there is no error
    inline bool CheckForGLError(const std::string& onErrorMessage)
    {
        bool   errorFound = false;
        GLenum glError    = oglUtils::_oglGetError();

        if (glError != GL_NO_ERROR)
        {
            switch (glError)
            {
            case GL_INVALID_ENUM:
            case GL_INVALID_VALUE:
            case GL_INVALID_OPERATION:
            case GL_STACK_OVERFLOW:
            case GL_STACK_UNDERFLOW:
            case GL_OUT_OF_MEMORY:
                errorFound = true;
                GPA_LogError(onErrorMessage.c_str());
                break;

            default:
                assert(glError == GL_NO_ERROR);
                break;
            }
        }

        return errorFound;
    }
}  // namespace oglUtils

#endif  // _GL_INCLUDE_H_