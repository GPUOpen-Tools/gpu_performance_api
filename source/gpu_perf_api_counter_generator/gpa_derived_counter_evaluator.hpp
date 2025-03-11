//==============================================================================
// Copyright (c) 2020-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Functions for evaluating derived counter formula.
//==============================================================================

#include <vector>

#include "gpu_performance_api/gpu_perf_api_types.h"
#include "gpu_perf_api_common/gpa_hw_info.h"

/// @brief Performs a sum of the specified number of stack values.
///
/// T is derived counter type.
///
/// @param [in,out] stack RPN counter formula expression stack.
/// @param [in] count Number of stack items.
template <class T>
void SumN(std::vector<T>& stack, int32_t count)
{
    T sum = 0;

    // Pop the last count items and add them together.
    for (int i = 0; i < count; i++)
    {
        T value = stack.back();
        stack.pop_back();

        sum += value;
    }

    stack.push_back(sum);
}

/// Performs a summation of a two blocks of vectors.
///
/// T is derived counter type.
///
/// @param [in,out] stack RPN counter formula expression stack.
/// @param [in] vector_width Width of the vector.
template <class T>
void VecSumN(std::vector<T>& stack, int32_t vector_width)
{
    // Get values2.
    std::vector<T> values2;

    for (int32_t i = 0; i < vector_width; ++i)
    {
        values2.push_back(stack.back());
        stack.pop_back();
    }

    // Get values1.
    std::vector<T> values1;

    for (int32_t i = 0; i < vector_width; ++i)
    {
        values1.push_back(stack.back());
        stack.pop_back();
    }

    // Sum and push back.
    for (int32_t i = vector_width - 1; i >= 0; --i)
    {
        T value = values1[i] + values2[i];
        stack.push_back(value);
    }
}

/// @brief Performs a subtraction of a vector from another vector.
///
/// T is derived counter type.
///
/// @param [in,out] stack RPN counter formula expression stack.
/// @param [in] vector_width Width of the vector.
template <class T>
void VecSubN(std::vector<T>& stack, int32_t vector_width)
{
    // Get values2.
    std::vector<T> values2;

    for (int32_t i = 0; i < vector_width; ++i)
    {
        values2.push_back(stack.back());
        stack.pop_back();
    }

    // Get values1.
    std::vector<T> values1;

    for (int32_t i = 0; i < vector_width; ++i)
    {
        values1.push_back(stack.back());
        stack.pop_back();
    }

    // Subtract and push back.
    for (int32_t i = vector_width - 1; i >= 0; --i)
    {
        T value = values1[i] - values2[i];
        stack.push_back(value);
    }
}

/// @brief Performs a divide of a vector by another vector.
///
/// T is derived counter type.
///
/// @param [in,out] stack RPN counter formula expression stack.
/// @param [in] vector_width Width of the vector.
template <class T>
void VecDivN(std::vector<T>& stack, int32_t vector_width)
{
    // Get the divisors.
    std::vector<T> divisors;

    for (int32_t i = 0; i < vector_width; ++i)
    {
        divisors.push_back(stack.back());
        stack.pop_back();
    }

    // Get the dividends.
    std::vector<T> dividends;

    for (int32_t i = 0; i < vector_width; ++i)
    {
        dividends.push_back(stack.back());
        stack.pop_back();
    }

    // Divide and push back.
    for (int32_t i = vector_width - 1; i >= 0; --i)
    {
        T value = divisors[i] ? (dividends[i] / divisors[i]) : static_cast<T>(0);
        stack.push_back(value);
    }
}

/// @brief Performs an average of the specified number of stack values.
///
/// T is derived counter type.
///
/// @param [in,out] stack RPN counter formula expression stack.
/// @param [in] count Number of stack items.
template <class T>
void AvgN(std::vector<T>& stack, int32_t count)
{
    T value = 0;

    for (int32_t i = 0; i < count; ++i)
    {
        value += stack.back();
        stack.pop_back();
    }

    value /= static_cast<T>(count);

    stack.push_back(value);
}

/// @brief Performs a scalar subtraction of a vector.
///
/// T is derived counter type.
///
/// @param [in,out] stack RPN counter formula expression stack.
/// @param [in] vector_width Width of the vector.
template <class T>
void ScalarSubN(std::vector<T>& stack, int32_t vector_width)
{
    // Get the subtrahends.
    std::vector<T> subtrahends;
    for (int32_t i = 0; i < vector_width; ++i)
    {
        subtrahends.push_back(stack.back());
        stack.pop_back();
    }

    T minuend = stack.back();
    stack.pop_back();

    // Subtract and push back.
    for (int32_t i = vector_width - 1; i >= 0; --i)
    {
        T difference = minuend - subtrahends[i];

        if (difference < 0)
        {
            assert(0);
            difference = 0;
        }

        stack.push_back(difference);
    }
}

/// @brief Performs a scalar divide of a vector.
///
/// T is derived counter type.
///
/// @param [in,out] stack RPN counter formula expression stack.
/// @param [in] vector_width Width of the vector.
template <class T>
void ScalarDivN(std::vector<T>& stack, int32_t vector_width)
{
    T divisor = stack.back();
    stack.pop_back();

    // Get the dividends.
    std::vector<T> dividends;

    for (int32_t i = 0; i < vector_width; ++i)
    {
        dividends.push_back(stack.back());
        stack.pop_back();
    }

    // Divide and push back.
    for (int32_t i = vector_width - 1; i >= 0; --i)
    {
        T value = divisor ? (dividends[i] / divisor) : static_cast<T>(0);
        stack.push_back(value);
    }
}

/// @brief Performs a scalar multiply of a vector.
///
/// T is derived counter type.
///
/// @param [in,out] stack RPN counter formula expression stack.
/// @param [in] vector_width Width of the vector.
template <class T>
void ScalarMulN(std::vector<T>& stack, int32_t vector_width)
{
    // Get the multiplicands.
    std::vector<T> multiplicands;

    for (int32_t i = 0; i < vector_width; ++i)
    {
        multiplicands.push_back(stack.back());
        stack.pop_back();
    }

    T multiplier = stack.back();
    stack.pop_back();

    assert(multiplier != 0);

    // Multiply and push back.
    for (int32_t i = vector_width - 1; i >= 0; --i)
    {
        T value = multiplicands[i] * multiplier;
        stack.push_back(value);
    }
}

/// @brief Evaluates a counter formula expression.
///
/// T is derived counter type.
///
/// @param [in] expression The counter formula.
/// @param [out] result The result value.
/// @param [in] results List of the hardware counter results.
/// @param [in] result_type The counter result type.
/// @param [in] hw_info The hardware info.
///
/// @return kGpaStatusOk on success, otherwise an error code.
template <class T, class InternalCounterType>
static GpaStatus EvaluateExpression(const char*                          expression,
                                    void*                                result,
                                    const std::vector<const GpaUInt64*>& results,
                                    GpaDataType                          result_type,
                                    const GpaHwInfo*                     hw_info)
{
    GpaStatus status = kGpaStatusOk;

    if (!hw_info)
    {
        assert(nullptr != hw_info);
        return kGpaStatusErrorInvalidParameter;
    }

    size_t            expression_len = strlen(expression) + 1;
    std::vector<char> buffer(expression_len);

    strcpy_s(buffer.data(), expression_len, expression);

    vector<T> stack;
    T*        write_result = reinterpret_cast<T*>(result);

    char* context = nullptr;
    context;  //TODO: gcc is not considering unused in strtok_s
    char* pch = strtok_s(buffer.data(), " ,", &context);

    while (nullptr != pch)
    {
        if (*pch == '*')
        {
            assert(stack.size() >= 2);

            T p2 = stack.back();
            stack.pop_back();
            T p1 = stack.back();
            stack.pop_back();
            stack.push_back(p1 * p2);
        }
        else if (*pch == '/')
        {
            assert(stack.size() >= 2);

            T p2 = stack.back();
            stack.pop_back();
            T p1 = stack.back();
            stack.pop_back();

            if (p2 != static_cast<T>(0))
            {
                stack.push_back(p1 / p2);
            }
            else
            {
                stack.push_back(static_cast<T>(0));
            }
        }
        else if (*pch == '+')
        {
            assert(stack.size() >= 2);

            T p2 = stack.back();
            stack.pop_back();
            T p1 = stack.back();
            stack.pop_back();
            stack.push_back(p1 + p2);
        }
        else if (*pch == '-')
        {
            assert(stack.size() >= 2);

            T p2 = stack.back();
            stack.pop_back();
            T p1 = stack.back();
            stack.pop_back();
            stack.push_back(p1 - p2);
        }
        else if (*pch == '(')
        {
            // constant
            T   constant    = static_cast<T>(0);
            int scan_result = 0;

            if (result_type == kGpaDataTypeFloat64)
            {
#ifdef _LINUX
                scan_result = sscanf(pch, "(%lf)", reinterpret_cast<GpaFloat64*>(&constant));
#else
                scan_result = sscanf_s(pch, "(%lf)", reinterpret_cast<GpaFloat64*>(&constant));
#endif  // _LINUX
            }
            else if (result_type == kGpaDataTypeUint64)
            {
#ifdef _LINUX
                scan_result = sscanf(pch, "(%llu)", reinterpret_cast<GpaUInt64*>(&constant));
#else
                scan_result = sscanf_s(pch, "(%I64u)", reinterpret_cast<GpaUInt64*>(&constant));
#endif  // _LINUX
            }
            else
            {
                // Unsupported derived counter type
                assert(false);
                return kGpaStatusErrorInvalidDataType;
            }

            if (1 != scan_result)
            {
                assert(false);
            }

            stack.push_back(constant);
        }
        else if (_strcmpi(pch, "num_shader_engines") == 0)
        {
            stack.push_back(static_cast<T>(hw_info->GetNumberShaderEngines()));
        }
        else if (_strcmpi(pch, "num_shader_arrays") == 0)
        {
            stack.push_back(static_cast<T>(hw_info->GetNumberShaderArrays()));
        }
        else if (_strcmpi(pch, "num_simds") == 0)
        {
            stack.push_back(static_cast<T>(hw_info->GetNumberSimds()));
        }
        else if (_strcmpi(pch, "su_clocks_prim") == 0)
        {
            stack.push_back(static_cast<T>(hw_info->GetSuClocksPrim()));
        }
        else if (_strcmpi(pch, "num_prim_pipes") == 0)
        {
            stack.push_back(static_cast<T>(hw_info->GetNumberPrimPipes()));
        }
        else if (_strcmpi(pch, "num_cus") == 0)
        {
            stack.push_back(static_cast<T>(hw_info->GetNumberCus()));
        }
        else if (_strcmpi(pch, "MAX_WAVES") == 0)
        {
            stack.push_back(static_cast<T>(hw_info->GetNumberSimds() * hw_info->GetWavesPerSimd()));
        }
        else if (_strcmpi(pch, "TS_FREQ") == 0)
        {
            GpaUInt64 freq = 1u;
            GPA_ASSERT(hw_info->GetTimeStampFrequency(freq));
            stack.push_back(static_cast<T>(freq));
        }
        else if ((tolower(pch[0]) == 'm') && (tolower(pch[1]) == 'a') && (tolower(pch[2]) == 'x') && ((pch[3] == '\0') || isdigit(pch[3])))
        {
            // max
            long value_count = 2;
            if (pch[3] != '\0')
            {
                char* endptr = nullptr;
                errno        = 0;
                value_count  = std::strtol(&pch[3], &endptr, 10);
                assert(endptr != nullptr);
                assert(value_count > 0);
                assert(errno == 0);
            }
            assert(stack.size() >= static_cast<std::size_t>(value_count));

            T max = stack.back();
            stack.pop_back();
            for (long int i = 1; i < value_count; i++)
            {
                max = std::max(max, stack.back());
                stack.pop_back();
            }
            stack.push_back(max);
        }
        else if ((tolower(pch[0]) == 'm') && (tolower(pch[1]) == 'i') && (tolower(pch[2]) == 'n') && ((pch[3] == '\0') || isdigit(pch[3])))
        {
            // min
            long value_count = 2;
            if (pch[3] != '\0')
            {
                char* endptr = nullptr;
                errno        = 0;
                value_count  = std::strtol(&pch[3], &endptr, 10);
                assert(endptr != nullptr);
                assert(value_count > 0);
                assert(errno == 0);
            }
            assert(stack.size() >= static_cast<std::size_t>(value_count));

            T min = stack.back();
            stack.pop_back();
            for (long int i = 1; i < value_count; i++)
            {
                min = std::min(min, stack.back());
                stack.pop_back();
            }
            stack.push_back(min);
        }
        else if (_strcmpi(pch, "ifnotzero") == 0)
        {
            assert(stack.size() >= 3);

            T condition = stack.back();
            stack.pop_back();
            T result_true = stack.back();
            stack.pop_back();
            T result_false = stack.back();
            stack.pop_back();

            if (condition != 0)
            {
                stack.push_back(result_true);
            }
            else
            {
                stack.push_back(result_false);
            }
        }
        else if (_strcmpi(pch, "comparemax2") == 0)
        {
            assert(stack.size() >= 4);

            std::vector<T> values;

            for (int i = 0; i < 2; ++i)
            {
                values.push_back(stack.back());
                stack.pop_back();
            }

            std::vector<T> potential_returns;

            for (int i = 0; i < 2; ++i)
            {
                // Only consider potential returns where the values[i] is non-zero
                if (values[i])
                {
                    potential_returns.push_back(stack.back());
                }

                stack.pop_back();
            }

            if (potential_returns.empty())
            {
                stack.push_back(0);
            }
            else
            {
                auto iter = std::max_element(potential_returns.begin(), potential_returns.end());
                stack.push_back(*iter);
            }
        }
        else if (_strcmpi(pch, "comparemax4") == 0)
        {
            assert(stack.size() >= 8);

            std::vector<T> values;

            for (int i = 0; i < 4; ++i)
            {
                values.push_back(stack.back());
                stack.pop_back();
            }

            std::vector<T> potential_returns;

            for (int i = 0; i < 4; ++i)
            {
                // Only consider potential returns where the values[i] is non-zero
                if (values[i])
                {
                    potential_returns.push_back(stack.back());
                }

                stack.pop_back();
            }

            if (potential_returns.empty())
            {
                stack.push_back(0);
            }
            else
            {
                auto iter = std::max_element(potential_returns.begin(), potential_returns.end());
                stack.push_back(*iter);
            }
        }
        else if (_strcmpi(pch, "comparemax6") == 0)
        {
            assert(stack.size() >= 12);

            std::vector<T> values;

            for (int i = 0; i < 6; ++i)
            {
                values.push_back(stack.back());
                stack.pop_back();
            }

            std::vector<T> potential_returns;

            for (int i = 0; i < 6; ++i)
            {
                // Only consider potential returns where the values[i] is non-zero
                if (values[i])
                {
                    potential_returns.push_back(stack.back());
                }

                stack.pop_back();
            }

            if (potential_returns.empty())
            {
                stack.push_back(0);
            }
            else
            {
                auto iter = std::max_element(potential_returns.begin(), potential_returns.end());
                stack.push_back(*iter);
            }
        }
        else if ((tolower(pch[0]) == 's') && (tolower(pch[1]) == 'u') && (tolower(pch[2]) == 'm') && ((pch[3] == '\0') || isdigit(pch[3])))
        {
            // SumN
            long value_count = 2;
            if (pch[3] != '\0')
            {
                char* endptr = nullptr;
                errno        = 0;
                value_count  = std::strtol(&pch[3], &endptr, 10);
                assert(endptr != nullptr);
                assert(value_count > 0);
                assert(errno == 0);
            }
            assert(stack.size() >= static_cast<std::size_t>(value_count));
            SumN<T>(stack, value_count);
        }
        else if ((tolower(pch[0]) == 'v') && (tolower(pch[1]) == 'e') && (tolower(pch[2]) == 'c') && (tolower(pch[3]) == 's') && (tolower(pch[4]) == 'u') &&
                 (tolower(pch[5]) == 'm') && ((pch[6] == '\0') || isdigit(pch[6])))
        {
            // VecSumN
            long value_count = 2;
            if (pch[6] != '\0')
            {
                char* endptr = nullptr;
                errno        = 0;
                value_count  = std::strtol(&pch[6], &endptr, 10);
                assert(endptr != nullptr);
                assert(value_count > 0);
                assert(errno == 0);
            }
            assert(stack.size() >= static_cast<std::size_t>(value_count) * 2);  // 2 vectors of value_count entries.
            VecSumN<T>(stack, value_count);
        }
        else if ((tolower(pch[0]) == 'v') && (tolower(pch[1]) == 'e') && (tolower(pch[2]) == 'c') && (tolower(pch[3]) == 's') && (tolower(pch[4]) == 'u') &&
                 (tolower(pch[5]) == 'b') && ((pch[6] == '\0') || isdigit(pch[6])))
        {
            // VecSubN
            long value_count = 2;
            if (pch[6] != '\0')
            {
                char* endptr = nullptr;
                errno        = 0;
                value_count  = std::strtol(&pch[6], &endptr, 10);
                assert(endptr != nullptr);
                assert(value_count > 0);
                assert(errno == 0);
            }
            assert(stack.size() >= static_cast<std::size_t>(value_count) * 2);  // 2 vectors of value_count entries.
            VecSubN<T>(stack, value_count);
        }
        else if ((tolower(pch[0]) == 'v') && (tolower(pch[1]) == 'e') && (tolower(pch[2]) == 'c') && (tolower(pch[3]) == 'd') && (tolower(pch[4]) == 'i') &&
                 (tolower(pch[5]) == 'v') && ((pch[6] == '\0') || isdigit(pch[6])))
        {
            // VecDivN
            long value_count = 2;
            if (pch[6] != '\0')
            {
                char* endptr = nullptr;
                errno        = 0;
                value_count  = std::strtol(&pch[6], &endptr, 10);
                assert(endptr != nullptr);
                assert(value_count > 0);
                assert(errno == 0);
            }
            assert(stack.size() >= static_cast<std::size_t>(value_count) * 2);  // 2 vectors of value_count entries.
            VecDivN<T>(stack, value_count);
        }
        else if ((tolower(pch[0]) == 'a') && (tolower(pch[1]) == 'v') && (tolower(pch[2]) == 'g') && ((pch[3] == '\0') || isdigit(pch[3])))
        {
            // AvgN
            long value_count = 2;
            if (pch[3] != '\0')
            {
                char* endptr = nullptr;
                errno        = 0;
                value_count  = std::strtol(&pch[3], &endptr, 10);
                assert(endptr != nullptr);
                assert(value_count > 0);
                assert(errno == 0);
            }
            assert(stack.size() >= static_cast<std::size_t>(value_count));
            AvgN<T>(stack, value_count);
        }
        else if ((tolower(pch[0]) == 's') && (tolower(pch[1]) == 'c') && (tolower(pch[2]) == 'a') && (tolower(pch[3]) == 'l') && (tolower(pch[4]) == 'a') &&
                 (tolower(pch[5]) == 'r') && (tolower(pch[6]) == 's') && (tolower(pch[7]) == 'u') && (tolower(pch[8]) == 'b') &&
                 ((pch[9] == '\0') || isdigit(pch[9])))
        {
            // ScalarSubN
            long value_count = 2;
            if (pch[9] != '\0')
            {
                char* endptr = nullptr;
                errno        = 0;
                value_count  = std::strtol(&pch[9], &endptr, 10);
                assert(endptr != nullptr);
                assert(value_count > 0);
                assert(errno == 0);
            }
            assert(stack.size() >= static_cast<std::size_t>(value_count) + 1);  // 1 scalar + 1 vector of value_count entries.
            ScalarSubN<T>(stack, value_count);
        }
        else if ((tolower(pch[0]) == 's') && (tolower(pch[1]) == 'c') && (tolower(pch[2]) == 'a') && (tolower(pch[3]) == 'l') && (tolower(pch[4]) == 'a') &&
                 (tolower(pch[5]) == 'r') && (tolower(pch[6]) == 'd') && (tolower(pch[7]) == 'i') && (tolower(pch[8]) == 'v') &&
                 ((pch[9] == '\0') || isdigit(pch[9])))
        {
            // ScalarDivN
            long value_count = 2;
            if (pch[9] != '\0')
            {
                char* endptr = nullptr;
                errno        = 0;
                value_count  = std::strtol(&pch[9], &endptr, 10);
                assert(endptr != nullptr);
                assert(value_count > 0);
                assert(errno == 0);
            }
            assert(stack.size() >= static_cast<std::size_t>(value_count) + 1);  // 1 scalar + 1 vector of value_count entries.
            ScalarDivN<T>(stack, value_count);
        }
        else if ((tolower(pch[0]) == 's') && (tolower(pch[1]) == 'c') && (tolower(pch[2]) == 'a') && (tolower(pch[3]) == 'l') && (tolower(pch[4]) == 'a') &&
                 (tolower(pch[5]) == 'r') && (tolower(pch[6]) == 'm') && (tolower(pch[7]) == 'u') && (tolower(pch[8]) == 'l') &&
                 ((pch[9] == '\0') || isdigit(pch[9])))
        {
            // ScalarMulN
            long value_count = 2;
            if (pch[9] != '\0')
            {
                char* endptr = nullptr;
                errno        = 0;
                value_count  = std::strtol(&pch[9], &endptr, 10);
                assert(endptr != nullptr);
                assert(value_count > 0);
                assert(errno == 0);
            }
            assert(stack.size() >= static_cast<std::size_t>(value_count) + 1);  // 1 scalar + 1 vector of value_count entries.
            ScalarMulN<T>(stack, value_count);
        }
        else
        {
            // must be number, reference to internal counter
            GpaUInt32 index;
#ifdef _LINUX
            int scan_result = sscanf(pch, "%d", &index);
#else
            int scan_result = sscanf_s(pch, "%d", &index);
#endif
            UNREFERENCED_PARAMETER(scan_result);

            if (1 != scan_result)
            {
                GPA_LOG_DEBUG_ERROR("Failed for expression %s", expression);
            }
            assert(scan_result == 1);

            if (index < results.size())
            {
                const InternalCounterType internal_val       = *reinterpret_cast<const InternalCounterType*>(results[index]);
                T                         internal_val_float = static_cast<T>(internal_val);
                stack.push_back(internal_val_float);
            }
            else
            {
                // the index was invalid, so the counter result is unknown
                assert(0);
                GPA_LOG_ERROR("counter registerIndex in equation is out of range.");
                status = kGpaStatusErrorInvalidCounterEquation;
                break;
            }
        }

        pch = strtok_s(nullptr, " ,", &context);
    }

    if (stack.size() != 1)
    {
        GPA_LOG_ERROR("Invalid formula: %s", expression);
        status = kGpaStatusErrorInvalidCounterEquation;
    }

    assert(stack.size() == 1);
    *write_result = stack.back();

    return status;
}
