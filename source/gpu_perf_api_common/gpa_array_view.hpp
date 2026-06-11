//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Similar to string_view but for arrays.
///        Like std::string_view and std::span prefer to pass by value.
///        gpa_array_view is small so passing it by value is efficient.
///        This also helps simplify the function signature and usage.
//==============================================================================
#ifndef GPA_ARRAY_VIEW
#define GPA_ARRAY_VIEW

#include <array>
#include <span>

/// @brief Like std::string_view but for arrays of any type.
template <class T>
using gpa_array_view = std::span<const T>;

#endif
