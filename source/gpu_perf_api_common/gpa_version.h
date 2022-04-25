//==============================================================================
// Copyright (c) 2016-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Macros used for defining GPUPerfAPI version.
//==============================================================================

// Note: This file is auto-generated using gpa_version cmake module.

#ifndef GPU_PERF_API_COMMMON_GPA_VERSION_H_
#define GPU_PERF_API_COMMMON_GPA_VERSION_H_

// Make sure to increment GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER anytime GPA_MAJOR_VERSION is incremented
#define GPA_MAJOR_VERSION 3   ///< Macro for GPA major version.
#define GPA_MINOR_VERSION 11  ///< Macro for GPA minor version.
#define GPA_UPDATE_VERSION 0  ///< Macro for GPA update version.

/// Macro for GPA build number
#define GPA_BUILD_NUMBER 0

#define GPA_STR_VALUE(s) #s                     ///< Macro to stringify a value.
#define GPA_VERSION_STRING(s) GPA_STR_VALUE(s)  ///< Macro to stringify a version value.

#define GPA_MAJOR_VERSION_STR GPA_VERSION_STRING(GPA_MAJOR_VERSION)    ///< Macro for major version string.
#define GPA_MINOR_VERSION_STR GPA_VERSION_STRING(GPA_MINOR_VERSION)    ///< Macro for minor version string.
#define GPA_BUILD_NUMBER_STR GPA_VERSION_STRING(GPA_BUILD_NUMBER)      ///< Macro for build number string.
#define GPA_UPDATE_VERSION_STR GPA_VERSION_STRING(GPA_UPDATE_VERSION)  ///< Macro for update version string.

#define AMDT_PROJECT_SUFFIX_STR GPA_VERSION_STRING(AMDT_PROJECT_SUFFIX)  ///< Macro for project suffix string.

#define GPA_COPYRIGHT_CURRENT_YEAR 2022  ///< Macro for current year.

#define GPA_COPYRIGHT_STR \
    "Copyright (c) 2010-" GPA_VERSION_STRING(GPA_COPYRIGHT_CURRENT_YEAR) " Advanced Micro Devices, Inc. All rights reserved."  ///< Macro for copyright string.

#endif  // GPU_PERF_API_COMMMON_GPA_VERSION_H_
