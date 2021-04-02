//==============================================================================
// Copyright (c) 2014-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Utility macros, constants and function declarations.
//==============================================================================

#include "gpu_perf_api_common/utility.h"

#ifdef _LINUX
#include <unistd.h>
#endif

#include <locale>

#include "gpu_perf_api_common/gpa_common_defs.h"

#ifdef _WIN32
EXTERN_C IMAGE_DOS_HEADER __ImageBase;  ///< __ImageBase symbol exported by MSVC linker.

/// Macro for the HINST of the owning module.
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

void gpa_util::WideCharArrayToString(const wchar_t* wide_char_array, std::string& str)
{
    const size_t str_len = wcslen(wide_char_array);
    str.resize(str_len);

    for (size_t ci = 0; str_len > ci; ++ci)
    {
        str[ci] = std::use_facet<std::ctype<wchar_t> >(std::locale()).narrow(wide_char_array[ci], '\0');
    }
}

void gpa_util::WideStringToString(const std::wstring& wide_string, std::string& str)
{
    WideCharArrayToString(wide_string.c_str(), str);
}

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
        strncpy_s(sz_this_module_path, MAX_PATH, sz_this_module_name, strrchr(sz_this_module_name, '\\') + 1 - sz_this_module_name);
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
        strncpy_s(sz_this_module_path, 4096, sz_this_module_name, strrchr(sz_this_module_name, '/') + 1 - sz_this_module_name);
        current_module_path = sz_this_module_path;
    }

#endif

    return success;
}
