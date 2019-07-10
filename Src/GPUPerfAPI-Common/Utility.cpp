//==============================================================================
// Copyright (c) 2014-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility macros, constants and function declarations
//==============================================================================

#include <locale>

#include "Utility.h"
#include "GPACommonDefs.h"

#ifdef _LINUX
#include <unistd.h>
#endif

#ifdef _WIN32
EXTERN_C IMAGE_DOS_HEADER __ImageBase;  ///< __ImageBase symbol exported by MSVC linker

/// Macro for the HINST of the owning module
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

void GPAUtil::wcstringToString(const wchar_t* pWstr, std::string& str)
{
    const size_t strLen = wcslen(pWstr);
    str.resize(strLen);

    for (size_t ci = 0; strLen > ci; ++ci)
    {
        str[ci] = std::use_facet<std::ctype<wchar_t> >(std::locale()).narrow(pWstr[ci], '\0');
    }
}

void GPAUtil::wstringToString(const std::wstring& wstr, std::string& str)
{
    wcstringToString(wstr.c_str(), str);
}

bool GPAUtil::GetCurrentModulePath(std::string& currentModulePath)
{
    bool success = true;

#ifdef _WIN32

    char szThisModuleName[MAX_PATH] = { 0 };

    if (0 == ::GetModuleFileNameA(HINST_THISCOMPONENT, szThisModuleName, MAX_PATH))
    {
        success = false;
    }

    if (success)
    {
        char szThisModulePath[MAX_PATH] = { 0 };
        strncpy_s(szThisModulePath, MAX_PATH, szThisModuleName, strrchr(szThisModuleName, '\\') + 1 - szThisModuleName);
        currentModulePath = szThisModulePath;
    }

#else

    char szThisModuleName[4096] = { 0 };
    int  len;
    len = readlink("/proc/self/exe", szThisModuleName, 4096 - 1);

    if (len != -1)
    {
        szThisModuleName[len] = '\0';
    }
    else
    {
        success = false;
    }

    if (success)
    {
        char szThisModulePath[4096] = { 0 };
        strncpy_s(szThisModulePath, 4096, szThisModuleName, strrchr(szThisModuleName, '/') + 1 - szThisModuleName);
        currentModulePath = szThisModulePath;
    }

#endif

    return success;
}
