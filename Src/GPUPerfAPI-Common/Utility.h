//==============================================================================
// Copyright (c) 2014-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Utility macros, constants and function declarations
//==============================================================================

#ifndef _GPA_COMMON_UTILITY_H_
#define _GPA_COMMON_UTILITY_H_

#include <string>

namespace GPAUtil
{
/// Convert a C wide character string to string
/// \param[in] pWstr Wide character string
/// \param[out] str ASCII string
void wcstringToString(const wchar_t* pWstr, std::string& str);

/// Convert a wide character string to string
/// \param[in] wstr Wide character string
/// \param[out] str ASCII string
void wstringToString(const std::wstring& wstr, std::string& str);

/// Returns the path of the curent module
/// \param[out] currentModulePath path of the module from where it was loaded
/// \return true upon successful operation otherwise false
bool GetCurrentModulePath(std::string& currentModulePath);
}

#endif // _GPA_COMMON_UTILITY_H_
