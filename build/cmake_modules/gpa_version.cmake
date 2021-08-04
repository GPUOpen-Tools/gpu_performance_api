## Copyright (c) 2020-2021 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

include(${CMAKE_CURRENT_LIST_DIR}/defs.cmake)

set(GPA_VERSION_HEADER_FILE "gpa_version.h")
string(TIMESTAMP CURRENT_YEAR %Y)

set(GPA_VERSION_HEADER_FILE_CONTENT "//==============================================================================
// Copyright (c) 2016-${CURRENT_YEAR} Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Macros used for defining GPUPerfAPI version.
//==============================================================================

// Note: This file is auto-generated using gpa_version cmake module.

#ifndef GPU_PERF_API_COMMMON_GPA_VERSION_H_
#define GPU_PERF_API_COMMMON_GPA_VERSION_H_

// Make sure to increment GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER anytime GPA_MAJOR_VERSION is incremented
#define GPA_MAJOR_VERSION ${GPA_MAJOR_VERSION}   ///< Macro for GPA major version.
#define GPA_MINOR_VERSION ${GPA_MINOR_VERSION}   ///< Macro for GPA minor version.
#define GPA_UPDATE_VERSION ${GPA_UPDATE_VERSION}  ///< Macro for GPA update version.

/// Macro for GPA build number
#define GPA_BUILD_NUMBER ${GPA_BUILD_NUMBER}

#define GPA_STR_VALUE(s) #s                     ///< Macro to stringify a value.
#define GPA_VERSION_STRING(s) GPA_STR_VALUE(s)  ///< Macro to stringify a version value.

#define GPA_MAJOR_VERSION_STR GPA_VERSION_STRING(GPA_MAJOR_VERSION)    ///< Macro for major version string.
#define GPA_MINOR_VERSION_STR GPA_VERSION_STRING(GPA_MINOR_VERSION)    ///< Macro for minor version string.
#define GPA_BUILD_NUMBER_STR GPA_VERSION_STRING(GPA_BUILD_NUMBER)      ///< Macro for build number string.
#define GPA_UPDATE_VERSION_STR GPA_VERSION_STRING(GPA_UPDATE_VERSION)  ///< Macro for update version string.

#define AMDT_PROJECT_SUFFIX_STR GPA_VERSION_STRING(AMDT_PROJECT_SUFFIX)  ///< Macro for project suffix string.

#define GPA_COPYRIGHT_CURRENT_YEAR ${CURRENT_YEAR}  ///< Macro for current year.

#define GPA_COPYRIGHT_STR \\
    \"Copyright (c) 2010-\" GPA_VERSION_STRING(GPA_COPYRIGHT_CURRENT_YEAR) \" Advanced Micro Devices, Inc. All rights reserved.\"  ///< Macro for copyright string.

#endif  // GPU_PERF_API_COMMMON_GPA_VERSION_H_\n")

file(WRITE ${GPA_SRC_COMMON}/${GPA_VERSION_HEADER_FILE} ${GPA_VERSION_HEADER_FILE_CONTENT})
