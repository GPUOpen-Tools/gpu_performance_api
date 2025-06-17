//==============================================================================
// Copyright (c) 2025 Advanced Micro Devices, Inc. All rights reserved.
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
#include <cstddef>

/// @brief Like std::string_view but for arrays of any type
template <class T>
class gpa_array_view
{
public:
    /// @brief Constructs an array view from a std::array
    template <std::size_t Extent>
    constexpr gpa_array_view(std::array<T, Extent> const& arr) noexcept
        : ptr_(arr.data())
        , extent_(Extent)
    {
    }

    /// @brief Constructs an empty array view
    constexpr gpa_array_view() = default;

    /// @brief  Size of the array view
    ///
    /// @return Returns the number of elements
    constexpr std::size_t size() const noexcept
    {
        return extent_;
    }

    /// @brief  Returns a pointer to the beginning
    ///
    /// @return Pointer to the first element
    constexpr const T* begin() const noexcept
    {
        return ptr_;
    }

    /// @brief Returns a pointer to the end
    ///
    /// @return Pointer past the last element.
    constexpr const T* end() const noexcept
    {
        return ptr_ + extent_;
    }

    /// @brief Checks if the sequence is empty
    ///
    /// @return true if the view is empty; false otherwise.
    constexpr bool empty() const noexcept
    {
        return extent_ == 0;
    }

private:
    const T*    ptr_{};     ///< Pointer to array
    std::size_t extent_{};  ///< The extent of the array
};

#endif  // GPA_INTERNAL_COUNTER_DIFF_H_
