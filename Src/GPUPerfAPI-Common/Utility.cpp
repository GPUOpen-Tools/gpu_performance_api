//==============================================================================
// Copyright (c) 2014-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility macros, constants and function declarations
//==============================================================================

#include <locale>

#include "Utility.h"
#include "GPACommonDefs.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase; ///< __ImageBase symbol exported by MSVC linker
                                       /// the HINSTANCE of the owning module
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)


void GPAUtil::wcstringToString(const wchar_t* pWstr, std::string& str)
{
    const size_t strLen = wcslen(pWstr);
    str.resize(strLen);

    for (size_t ci = 0 ; strLen > ci ; ++ci)
    {
        str[ci] = std::use_facet<std::ctype< wchar_t > >(std::locale()).narrow(pWstr[ci]);
    }
}

void GPAUtil::wstringToString(const std::wstring& wstr, std::string& str)
{
    wcstringToString(wstr.c_str(), str);
}

bool GPAUtil::GetCurrentModulePath(std::string& currentModulePath)
{
    bool success = false;

    char szThisModuleName[MAX_PATH];

    if (0 != GetModuleFileNameA(HINST_THISCOMPONENT, szThisModuleName, MAX_PATH))
    {
        char szThisModulePath[MAX_PATH];
        strncpy_s(szThisModulePath, MAX_PATH, szThisModuleName, strrchr(szThisModuleName, '\\') + 1 - szThisModuleName);
        currentModulePath = szThisModulePath;
        success = true;
    }

    return success;
}
