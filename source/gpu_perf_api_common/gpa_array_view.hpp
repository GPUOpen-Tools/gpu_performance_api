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
#include <vector>

/// @brief Like std::string_view but for arrays of any type
template <class T>
class gpa_array_view
{
public:
    /// @brief Constructs an array view from a std::array
    ///
    /// @param [in] arr array to construct a view for
    template <std::size_t Extent>
    constexpr gpa_array_view(std::array<T, Extent> const& arr) noexcept
        : ptr_(arr.data())
        , extent_(Extent)
    {
    }

    /// @brief Constructs an array view from a std::vector
    ///
    /// @param [in] vec vector to construct a view for
    constexpr gpa_array_view(std::vector<T> const& vec) noexcept
        : ptr_(vec.data())
        , extent_(vec.size())
    {
    }

    /// @brief Constructs an array view from a ptr + count
    ///
    /// @param [in] ptr Pointer to continuous memory
    /// @param [in] extent Number of elements in the continuous memory
    constexpr gpa_array_view(const T* ptr, const size_t extent) noexcept
        : ptr_(ptr)
        , extent_(extent)
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

    /// @brief  Returns a reference to the element at specified location pos.
    ///
    /// @param [in] pos The index of the element to access
    ///
    /// @return Reference to the requested element.
    const T& operator[](size_t pos) const noexcept
    {
        return *(ptr_ + pos);
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

    /// @brief Direct access to the underlying contiguous storage
    ///
    /// @return Returns a pointer to the beginning of the underlying sequence.
    constexpr const T* data() const noexcept
    {
        return ptr_;
    }

private:
    const T*    ptr_{};     ///< Pointer to array
    std::size_t extent_{};  ///< The extent of the array
};

#endif
