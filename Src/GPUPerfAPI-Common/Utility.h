//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Utility macros, constants and function declarations
//==============================================================================

#ifndef _GPA_COMMON_UTILITY_H_
#define _GPA_COMMON_UTILITY_H_

#include <string>

/// Convert a C wide character string to string
/// \param[in] pWstr Wide character string
/// \param[out] str ASCII string
void wcstringToString(const wchar_t* pWstr, std::string& str);

/// Convert a wide character string to string
/// \param[in] wstr Wide character string
/// \param[out] str ASCII string
void wstringToString(const std::wstring& wstr, std::string& str);

#endif // _GPA_COMMON_UTILITY_H_
