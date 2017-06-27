//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL version of GPUPerfAPI
//==============================================================================

#ifndef _GPUPERFAPI_GL_H_
#define _GPUPERFAPI_GL_H_

#include "GPUPerfAPI.h"

#include "GLEntryPoints.h"
#include "GPAContextStateGL.h"

/// Gets the current GL ContextState
GPA_ContextStateGL* getCurrentContext();

// define this to introduce calls to glGetError.
// it is being removed because it makes profiling slower
//#define DEBUG_GL_ERRORS

#ifdef DEBUG_GL_ERRORS
/// checks for OpenGL errors, logs the specified message if there is an error, and return true / false to indicate an error.
/// This can be used anywhere, but should only be used in conditionals where the return value is needed; otherwise, use the
/// CheckForGLErrors macro below, which will better report the file and line numbers in the asserts.
/// \param pcsErrMsg the error message to put in the log
/// \return true if there is an error; false if there is no error
bool CheckForGLErrorsCond(const char* pcsErrMsg);

/// This macro is essentially the same thing as the CheckForGLErrorsCond function above,
/// but as a macro, the file and line numbers in the asserts are displayed correctly.
/// This makes it easier when debugging to know where the asserts are coming from.
extern GLenum g_glError;
#define CheckForGLErrors(pcsErrMsg) \
    g_glError = glGetError();\
    if ( g_glError != GL_NO_ERROR ) {\
        GPA_LogDebugError( pcsErrMsg );\
        switch ( g_glError )\
        {\
            case GL_INVALID_ENUM:\
            case GL_INVALID_VALUE:\
            case GL_INVALID_OPERATION:\
            case GL_STACK_OVERFLOW:\
            case GL_STACK_UNDERFLOW:\
            case GL_OUT_OF_MEMORY:\
                assert( g_glError != GL_INVALID_ENUM );\
                assert( g_glError != GL_INVALID_VALUE );\
                assert( g_glError != GL_INVALID_OPERATION );\
                assert( g_glError != GL_STACK_OVERFLOW );\
                assert( g_glError != GL_STACK_UNDERFLOW );\
                assert( g_glError != GL_OUT_OF_MEMORY );\
                break;\
            default:\
                assert( g_glError == GL_NO_ERROR );\
                break;\
        }\
    }

#endif // DEBUG_GL_ERRORS

#endif // _GPUPERFAPI_GL_H_
