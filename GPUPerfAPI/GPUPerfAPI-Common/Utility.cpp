//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility macros, constants and function declarations
//==============================================================================

#include <locale>

#include "Utility.h"

void wcstringToString(const wchar_t* pWstr, std::string& str)
{
    const size_t strLen = wcslen(pWstr);
    str.resize(strLen);

    for (size_t ci = 0 ; strLen > ci ; ++ci)
    {
        str[ci] = std::use_facet<std::ctype< wchar_t > >(std::locale()).narrow(pWstr[ci]);
    }
}

void wstringToString(const std::wstring& wstr, std::string& str)
{
    wcstringToString(wstr.c_str(), str);
}
