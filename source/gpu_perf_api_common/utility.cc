//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Utility macros, constants and function declarations.
//==============================================================================

#include "gpu_perf_api_common/utility.h"

#include <array>
#include <cstring>
#include <cstdlib>
#include <locale>
#include <string_view>

#include "gpu_perf_api_common/gpa_common_defs.h"

#ifdef _WIN32
EXTERN_C IMAGE_DOS_HEADER __ImageBase;  ///< __ImageBase symbol exported by MSVC linker.

/// Macro for the HINST of the owning module.
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#else
#include <unistd.h>
#endif

bool gpa_util::GetCurrentModulePath(std::string& current_module_path)
{
    bool success = true;

#ifdef _WIN32

    char sz_this_module_name[MAX_PATH] = {0};

    if (0 == ::GetModuleFileNameA(HINST_THISCOMPONENT, sz_this_module_name, MAX_PATH))
    {
        success = false;
    }

    if (success)
    {
        char sz_this_module_path[MAX_PATH] = {0};
        strncpy_s(sz_this_module_path, MAX_PATH, sz_this_module_name, std::strrchr(sz_this_module_name, '\\') + 1 - sz_this_module_name);
        current_module_path = sz_this_module_path;
    }

#else

    char sz_this_module_name[4096] = {0};
    int  len;
    len = readlink("/proc/self/exe", sz_this_module_name, 4096 - 1);

    if (len != -1)
    {
        sz_this_module_name[len] = '\0';
    }
    else
    {
        success = false;
    }

    if (success)
    {
        char sz_this_module_path[4096] = {0};
        strncpy_s(sz_this_module_path, 4096, sz_this_module_name, std::strrchr(sz_this_module_name, '/') + 1 - sz_this_module_name);
        current_module_path = sz_this_module_path;
    }

#endif

    return success;
}

std::optional<std::string> gpa_util::GetEnv(const char* var)
{
    assert(var != nullptr);
    if (var == nullptr) [[unlikely]]
    {
        return std::nullopt;
    }

    std::string result;

#ifdef _WIN32
    if (const DWORD size = ::GetEnvironmentVariableA(var, nullptr, 0); size > 0)
    {
        // 'size' includes space for the null terminator.
        std::string buffer;
        buffer.resize(size);
        const DWORD written = ::GetEnvironmentVariableA(var, buffer.data(), size);
        // On success, 'written' is the number of characters excluding the null terminator.
        // Treat truncation or failure as "no value".
        if (written > 0 && written < size)
        {
            buffer.resize(written);
            result = std::move(buffer);
        }
    }
#else
    if (const char* value = std::getenv(var); value != nullptr)
    {
        result = value;
    }
#endif

    if (result.empty())
    {
        return std::nullopt;
    }

    assert(!result.empty());
    return result;
}

[[nodiscard]] bool gpa_util::IsEnvVarForceEnabled(const char* var)
{
    const std::optional<std::string> env_var = gpa_util::GetEnv(var);
    if (!env_var.has_value())
    {
        return false;
    }

    const std::string& value          = env_var.value();
    constexpr auto     kEnabledValues = std::to_array<std::string_view>({"1", "TRUE", "True", "true"});
    for (const std::string_view enabled_value : kEnabledValues)
    {
        if (value == enabled_value)
        {
            return true;
        }
    }
    return false;
}

std::string gpa_util::ConvertToStdString(const std::wstring_view wide)
{
    const std::locale& loc   = std::locale();
    const auto&        facet = std::use_facet<std::ctype<wchar_t>>(loc);

    std::string str(wide.size(), '\0');
    for (size_t i = 0; i < wide.size(); ++i)
    {
        str[i] = facet.narrow(wide[i], '\0');
    }
    return str;
}
