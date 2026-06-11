//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Utility macros, constants and function declarations.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_UTILITY_H_
#define GPU_PERF_API_COMMON_UTILITY_H_

#include <string>
#include <string_view>
#include <optional>

/// @brief Namespace for GPA utility methods.
namespace gpa_util
{
    /// @brief Returns the path of the current module.
    ///
    /// @param [out] current_module_path Path of the module from where it was loaded.
    ///
    /// @return True upon successful operation otherwise false.
    [[nodiscard]] bool GetCurrentModulePath(std::string& current_module_path);

    /// @brief Safe version of getenv.
    ///
    /// @param [in] var Variable name to get from the environment.
    ///
    /// @retval std::nullopt if the environment variable is not set or is empty.
    /// @return The value of the environment variable if it exists
    [[nodiscard]] std::optional<std::string> GetEnv(const char* var);

    /// @brief Helper function to determine if an environment variable is set to a value that indicates "true".
    ///
    /// Examples: "1", "TRUE", "True", and "true" are all considered to indicate "true".
    ///
    /// @param [in] var Name of the environment variable.
    ///
    /// @return True if the environment variable is set to a value that indicates "true", false otherwise.
    [[nodiscard]] bool IsEnvVarForceEnabled(const char* var);

    /// @brief Converts wstring_view to a std::string
    ///
    /// @param [in] wide Wide string view to convert.
    ///
    /// @return The converted std::string.
    [[nodiscard]] std::string ConvertToStdString(const std::wstring_view wide);
}  // namespace gpa_util

#endif
