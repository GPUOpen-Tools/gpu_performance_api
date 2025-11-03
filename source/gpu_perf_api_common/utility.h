//==============================================================================
// Copyright (c) 2014-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Utility macros, constants and function declarations.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_UTILITY_H_
#define GPU_PERF_API_COMMON_UTILITY_H_

#include <string>

/// @brief Namespace for GPA utility methods.
namespace gpa_util
{
    /// @brief Convert a C wide character string to string.
    ///
    /// @param [in] wide_char_array Wide character string.
    /// @param [out] str ASCII string.
    void WideCharArrayToString(const wchar_t* wide_char_array, std::string& str);

    /// @brief Convert a wide character string to string.
    ///
    /// @param [in] wide_string Wide character string.
    /// @param [out] str ASCII string.
    void WideStringToString(const std::wstring& wide_string, std::string& str);

    /// @brief Returns the path of the current module.
    ///
    /// @param [out] current_module_path Path of the module from where it was loaded.
    ///
    /// @return True upon successful operation otherwise false.
    bool GetCurrentModulePath(std::string& current_module_path);
}

#endif
