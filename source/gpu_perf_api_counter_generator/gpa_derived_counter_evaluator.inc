//==============================================================================
// Copyright (c) 2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Functions for evaluating derived counter formula
//==============================================================================
//
/// Performs a sum of the specified number of stack values
/// T is derived counter type
/// \param[in,out] stack RPN counter formula expression stack
/// \param count number of stack items
template <class T>
void SumN(std::vector<T>& stack, int32_t count)
{
    T sum = 0;

    // pop the last count items and add them together
    for (int i = 0; i < count; i++)
    {
        T value = stack.back();
        stack.pop_back();

        sum += value;
    }

    stack.push_back(sum);
}

/// Performs a summation of a two blocks of vectors
/// T is derived counter type
/// \param[in,out] stack RPN counter formula expression stack
/// \param vectorWidth width of the vector
template <class T>
void VecSumN(std::vector<T>& stack, int32_t vectorWidth)
{
    // Get values2
    std::vector<T> values2;

    for (int32_t i = 0; i < vectorWidth; ++i)
    {
        values2.push_back(stack.back());
        stack.pop_back();
    }

    // Get values1
    std::vector<T> values1;

    for (int32_t i = 0; i < vectorWidth; ++i)
    {
        values1.push_back(stack.back());
        stack.pop_back();
    }

    // Sum and push back
    for (int32_t i = vectorWidth - 1; i >= 0; --i)
    {
        T value = values1[i] + values2[i];
        stack.push_back(value);
    }
}

/// Performs a subtraction of a vector from another vector
/// T is derived counter type
/// \param[in,out] stack RPN counter formula expression stack
/// \param vectorWidth width of the vector
template <class T>
void VecSubN(std::vector<T>& stack, int32_t vectorWidth)
{
    // Get values2
    std::vector<T> values2;

    for (int32_t i = 0; i < vectorWidth; ++i)
    {
        values2.push_back(stack.back());
        stack.pop_back();
    }

    // Get values1
    std::vector<T> values1;

    for (int32_t i = 0; i < vectorWidth; ++i)
    {
        values1.push_back(stack.back());
        stack.pop_back();
    }

    // Subtract and push back
    for (int32_t i = vectorWidth - 1; i >= 0; --i)
    {
        T value = values1[i] - values2[i];
        stack.push_back(value);
    }
}

/// Performs a divide of a vector by another vector
/// T is derived counter type
/// \param[in,out] stack RPN counter formula expression stack
/// \param vectorWidth width of the vector
template <class T>
void VecDivN(std::vector<T>& stack, int32_t vectorWidth)
{
    // Get the divisors
    std::vector<T> divisors;

    for (int32_t i = 0; i < vectorWidth; ++i)
    {
        divisors.push_back(stack.back());
        stack.pop_back();
    }

    // Get the dividends
    std::vector<T> dividends;

    for (int32_t i = 0; i < vectorWidth; ++i)
    {
        dividends.push_back(stack.back());
        stack.pop_back();
    }

    // Divide and push back
    for (int32_t i = vectorWidth - 1; i >= 0; --i)
    {
        T value = divisors[i] ? (dividends[i] / divisors[i]) : static_cast<T>(0);
        stack.push_back(value);
    }
}

/// Performs an average of the specified number of stack values
/// T is derived counter type
/// \param[in,out] stack RPN counter formula expression stack
/// \param count number of stack items
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

/// Performs a scalar subtraction of a vector
/// T is derived counter type
/// \param[in,out] stack RPN counter formula expression stack
/// \param vectorWidth width of the vector
template <class T>
void ScalarSubN(std::vector<T>& stack, int32_t vectorWidth)
{
    T arg = stack.back();
    stack.pop_back();

    // Get the dividends
    std::vector<T> dividends;

    for (int32_t i = 0; i < vectorWidth; ++i)
    {
        dividends.push_back(stack.back());
        stack.pop_back();
    }

    // Divide and push back
    for (int32_t i = vectorWidth - 1; i >= 0; --i)
    {
        T value = arg - dividends[i];

        if (value < 0)
        {
            assert(0);
            value = 0;
        }

        stack.push_back(value);
    }
}

/// Performs a scalar divide of a vector
/// T is derived counter type
/// \param[in,out] stack RPN counter formula expression stack
/// \param vectorWidth width of the vector
template <class T>
void ScalarDivN(std::vector<T>& stack, int32_t vectorWidth)
{
    T divisor = stack.back();
    stack.pop_back();

    // Get the dividends
    std::vector<T> dividends;

    for (int32_t i = 0; i < vectorWidth; ++i)
    {
        dividends.push_back(stack.back());
        stack.pop_back();
    }

    // Divide and push back
    for (int32_t i = vectorWidth - 1; i >= 0; --i)
    {
        T value = divisor ? (dividends[i] / divisor) : static_cast<T>(0);
        stack.push_back(value);
    }
}

/// Performs a scalar multiply of a vector
/// T is derived counter type
/// \param[in,out] stack RPN counter formula expression stack
/// \param vectorWidth width of the vector
template <class T>
void ScalarMulN(std::vector<T>& stack, int32_t vectorWidth)
{
    // Get the multiplicands
    std::vector<T> multiplicands;

    for (int32_t i = 0; i < vectorWidth; ++i)
    {
        multiplicands.push_back(stack.back());
        stack.pop_back();
    }

    T multiplier = stack.back();
    stack.pop_back();

    assert(multiplier != 0);

    // Multiply and push back
    for (int32_t i = vectorWidth - 1; i >= 0; --i)
    {
        T value = multiplicands[i] * multiplier;
        stack.push_back(value);
    }
}

/// Evaluates a counter formula expression
/// T is derived counter type
/// \param pExpression the counter formula
/// \param[out] pResult the result value
/// \param results list of the hardware counter results
/// \param resultType the counter result type
/// \param pHwInfo the hardware info
/// \return GPA_STATUS_OK on success, otherwise an error code
template <class T, class InternalCounterType>
static GPA_Status EvaluateExpression(const char*                      pExpression,
                                     void*                            pResult,
                                     const vector<const gpa_uint64*>& results,
                                     GPA_Data_Type                    resultType,
                                     const GPA_HWInfo*                pHwInfo)
{
    GPA_Status status = GPA_STATUS_OK;

    if (!pHwInfo)
    {
        assert(nullptr != pHwInfo);
        return GPA_STATUS_ERROR_INVALID_PARAMETER;
    }

    size_t            expressionLen = strlen(pExpression) + 1;
    std::vector<char> pBuf(expressionLen);

    strcpy_s(pBuf.data(), expressionLen, pExpression);

    vector<T> stack;
    T*        pWriteResult = reinterpret_cast<T*>(pResult);

    char* pContext = nullptr;
    pContext;  //TODO: gcc is not considering unused in strtok_s
    char* pch = strtok_s(pBuf.data(), " ,", &pContext);

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
            T   constant   = static_cast<T>(0);
            int scanResult = 0;

            if (resultType == GPA_DATA_TYPE_FLOAT64)
            {
#ifdef _LINUX
                scanResult = sscanf(pch, "(%lf)", reinterpret_cast<gpa_float64*>(&constant));
#else
                scanResult = sscanf_s(pch, "(%lf)", reinterpret_cast<gpa_float64*>(&constant));
#endif  // _LINUX
            }
            else if (resultType == GPA_DATA_TYPE_UINT64)
            {
#ifdef _LINUX
                scanResult = sscanf(pch, "(%llu)", reinterpret_cast<gpa_uint64*>(&constant));
#else
                scanResult = sscanf_s(pch, "(%I64u)", reinterpret_cast<gpa_uint64*>(&constant));
#endif  // _LINUX
            }
            else
            {
                // Unsupported derived counter type
                assert(false);
                return GPA_STATUS_ERROR_INVALID_DATATYPE;
            }

            if (1 != scanResult)
            {
                assert(false);
            }

            stack.push_back(constant);
        }
        else if (_strcmpi(pch, "num_shader_engines") == 0)
        {
            stack.push_back(static_cast<T>(pHwInfo->GetNumberShaderEngines()));
        }
        else if (_strcmpi(pch, "num_shader_arrays") == 0)
        {
            stack.push_back(static_cast<T>(pHwInfo->GetNumberShaderArrays()));
        }
        else if (_strcmpi(pch, "num_simds") == 0)
        {
            stack.push_back(static_cast<T>(pHwInfo->GetNumberSIMDs()));
        }
        else if (_strcmpi(pch, "su_clocks_prim") == 0)
        {
            stack.push_back(static_cast<T>(pHwInfo->GetSUClocksPrim()));
        }
        else if (_strcmpi(pch, "num_prim_pipes") == 0)
        {
            stack.push_back(static_cast<T>(pHwInfo->GetNumberPrimPipes()));
        }
        else if (_strcmpi(pch, "num_cus") == 0)
        {
            stack.push_back(static_cast<T>(pHwInfo->GetNumberCUs()));
        }
        else if (_strcmpi(pch, "TS_FREQ") == 0)
        {
            gpa_uint64 freq = 1u;
            GPA_ASSERT(pHwInfo->GetTimeStampFrequency(freq));
            stack.push_back(static_cast<T>(freq));
        }
        else if (_strcmpi(pch, "max") == 0)
        {
            assert(stack.size() >= 2);

            T p2 = stack.back();
            stack.pop_back();
            T p1 = stack.back();
            stack.pop_back();

            if (p1 > p2)
            {
                stack.push_back(p1);
            }
            else
            {
                stack.push_back(p2);
            }
        }
        else if (_strcmpi(pch, "max4") == 0)
        {
            assert(stack.size() >= 4);

            // initialize the max value to the 1st item
            T maxValue = stack.back();
            stack.pop_back();

            // pop the last 3 items and compute the max
            for (int i = 0; i < 3; i++)
            {
                T value = stack.back();
                stack.pop_back();

                maxValue = (maxValue > value) ? maxValue : value;
            }

            stack.push_back(maxValue);
        }
        else if (_strcmpi(pch, "max8") == 0)
        {
            assert(stack.size() >= 8);

            // initialize the max value to the 1st item
            T maxValue = stack.back();
            stack.pop_back();

            // pop the last 7 items and compute the max
            for (int i = 0; i < 7; i++)
            {
                T value = stack.back();
                stack.pop_back();

                maxValue = (maxValue > value) ? maxValue : value;
            }

            stack.push_back(maxValue);
        }
        else if (_strcmpi(pch, "max10") == 0)
        {
            assert(stack.size() >= 10);

            // initialize the max value to the 1st item
            T maxValue = stack.back();
            stack.pop_back();

            // pop the last 9 items and compute the max
            for (int i = 0; i < 9; i++)
            {
                T value = stack.back();
                stack.pop_back();

                maxValue = (maxValue > value) ? maxValue : value;
            }

            stack.push_back(maxValue);
        }
        else if (_strcmpi(pch, "max16") == 0)
        {
            assert(stack.size() >= 16);

            // initialize the max value to the 1st item
            T maxValue = stack.back();
            stack.pop_back();

            // pop the last 15 items and compute the max
            for (int i = 0; i < 15; i++)
            {
                T value = stack.back();
                stack.pop_back();

                maxValue = (maxValue > value) ? maxValue : value;
            }

            stack.push_back(maxValue);
        }
        else if (_strcmpi(pch, "max24") == 0)
        {
            assert(stack.size() >= 24);

            // initialize the max value to the 1st item
            T maxValue = stack.back();
            stack.pop_back();

            // pop the last 23 items and compute the max
            for (int i = 0; i < 23; i++)
            {
                T value = stack.back();
                stack.pop_back();

                maxValue = (maxValue > value) ? maxValue : value;
            }

            stack.push_back(maxValue);
        }
        else if (_strcmpi(pch, "max32") == 0)
        {
            assert(stack.size() >= 32);

            // initialize the max value to the 1st item
            T maxValue = stack.back();
            stack.pop_back();

            // pop the last 31 items and compute the max
            for (int i = 0; i < 31; i++)
            {
                T value = stack.back();
                stack.pop_back();

                maxValue = (maxValue > value) ? maxValue : value;
            }

            stack.push_back(maxValue);
        }
        else if (_strcmpi(pch, "max40") == 0)
        {
            assert(stack.size() >= 40);

            // initialize the max value to the 1st item
            T maxValue = stack.back();
            stack.pop_back();

            // pop the last 39 items and compute the max
            for (int i = 0; i < 39; i++)
            {
                T value = stack.back();
                stack.pop_back();

                maxValue = (maxValue > value) ? maxValue : value;
            }

            stack.push_back(maxValue);
        }
        else if (_strcmpi(pch, "max44") == 0)
        {
            assert(stack.size() >= 44);

            // initialize the max value to the 1st item
            T maxValue = stack.back();
            stack.pop_back();

            // pop the last 43 items and compute the max
            for (int i = 0; i < 43; i++)
            {
                T value = stack.back();
                stack.pop_back();

                maxValue = (maxValue > value) ? maxValue : value;
            }

            stack.push_back(maxValue);
        }
        else if (_strcmpi(pch, "max64") == 0)
        {
            assert(stack.size() >= 64);

            // initialize the max value to the 1st item
            T maxValue = stack.back();
            stack.pop_back();

            // pop the last 63 items and compute the max
            for (int i = 0; i < 63; i++)
            {
                T value = stack.back();
                stack.pop_back();

                maxValue = (maxValue > value) ? maxValue : value;
            }

            stack.push_back(maxValue);
        }
        else if (_strcmpi(pch, "max80") == 0)
        {
            assert(stack.size() >= 80);

            // initialize the max value to the 1st item
            T maxValue = stack.back();
            stack.pop_back();

            // pop the last 79 items and compute the max
            for (int i = 0; i < 79; i++)
            {
                T value = stack.back();
                stack.pop_back();

                maxValue = (maxValue > value) ? maxValue : value;
            }

            stack.push_back(maxValue);
        }
        else if (_strcmpi(pch, "min") == 0)
        {
            assert(stack.size() >= 2);

            T p2 = stack.back();
            stack.pop_back();
            T p1 = stack.back();
            stack.pop_back();

            if (p1 < p2)
            {
                stack.push_back(p1);
            }
            else
            {
                stack.push_back(p2);
            }
        }
        else if (_strcmpi(pch, "ifnotzero") == 0)
        {
            assert(stack.size() >= 3);

            T condition = stack.back();
            stack.pop_back();
            T resultTrue = stack.back();
            stack.pop_back();
            T resultFalse = stack.back();
            stack.pop_back();

            if (condition != 0)
            {
                stack.push_back(resultTrue);
            }
            else
            {
                stack.push_back(resultFalse);
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

            std::vector<T> potentialReturns;

            for (int i = 0; i < 2; ++i)
            {
                // Only consider potential returns where the values[i] is non-zero
                if (values[i])
                {
                    potentialReturns.push_back(stack.back());
                }

                stack.pop_back();
            }

            if (potentialReturns.empty())
            {
                stack.push_back(0);
            }
            else
            {
                auto iter = std::max_element(potentialReturns.begin(), potentialReturns.end());
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

            std::vector<T> potentialReturns;

            for (int i = 0; i < 4; ++i)
            {
                // Only consider potential returns where the values[i] is non-zero
                if (values[i])
                {
                    potentialReturns.push_back(stack.back());
                }

                stack.pop_back();
            }

            if (potentialReturns.empty())
            {
                stack.push_back(0);
            }
            else
            {
                auto iter = std::max_element(potentialReturns.begin(), potentialReturns.end());
                stack.push_back(*iter);
            }
        }
        else if (_strcmpi(pch, "sum2") == 0)
        {
            const int valueCount = 2;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum4") == 0)
        {
            const int valueCount = 4;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum8") == 0)
        {
            const int valueCount = 8;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum10") == 0)
        {
            const int valueCount = 10;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum11") == 0)
        {
            const int valueCount = 11;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum12") == 0)
        {
            const int valueCount = 12;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum16") == 0)
        {
            const int valueCount = 16;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum20") == 0)
        {
            const int valueCount = 20;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum24") == 0)
        {
            const int valueCount = 24;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum32") == 0)
        {
            const int valueCount = 32;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum40") == 0)
        {
            const int valueCount = 40;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum44") == 0)
        {
            const int valueCount = 44;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum64") == 0)
        {
            const int valueCount = 64;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum80") == 0)
        {
            const int valueCount = 80;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum128") == 0)
        {
            const int valueCount = 128;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum256") == 0)
        {
            const int valueCount = 256;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "sum320") == 0)
        {
            const int valueCount = 320;
            assert(stack.size() >= valueCount);
            SumN(stack, valueCount);
        }
        else if (_strcmpi(pch, "vecsum2") == 0)
        {
            const int32_t vectorWidth = 2;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec2
            VecSumN<T>(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecsum4") == 0)
        {
            const int32_t vectorWidth = 4;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec4
            VecSumN<T>(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecsum8") == 0)
        {
            const int32_t vectorWidth = 8;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec8
            VecSumN<T>(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecsum16") == 0)
        {
            const int32_t vectorWidth = 16;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec16
            VecSumN<T>(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecsum64") == 0)
        {
            const int32_t vectorWidth = 64;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec64
            VecSumN<T>(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecsub2") == 0)
        {
            const int32_t vectorWidth = 2;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec2
            VecSubN<T>(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecsub16") == 0)
        {
            const int32_t vectorWidth = 16;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec16
            VecSubN<T>(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecdiv2") == 0)
        {
            const int32_t vectorWidth = 2;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec2
            VecDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecdiv4") == 0)
        {
            const int32_t vectorWidth = 4;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec4
            VecDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecdiv8") == 0)
        {
            const int32_t vectorWidth = 8;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec8
            VecDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecdiv10") == 0)
        {
            const int32_t vectorWidth = 10;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec10
            VecDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecdiv16") == 0)
        {
            const int32_t vectorWidth = 16;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec16
            VecDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecdiv20") == 0)
        {
            const int32_t vectorWidth = 20;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec20
            VecDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecdiv32") == 0)
        {
            const int32_t vectorWidth = 32;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec32
            VecDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecdiv64") == 0)
        {
            const int32_t vectorWidth = 64;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec64
            VecDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "vecdiv80") == 0)
        {
            const int32_t vectorWidth = 80;
            assert(stack.size() >= 2 * vectorWidth);  // 2 vectors with vec80
            VecDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "avg2") == 0)
        {
            const int32_t valueCount = 2;
            assert(stack.size() >= valueCount);
            AvgN(stack, valueCount);
        }
        else if (_strcmpi(pch, "avg4") == 0)
        {
            const int32_t valueCount = 4;
            assert(stack.size() >= valueCount);
            AvgN(stack, valueCount);
        }
        else if (_strcmpi(pch, "avg8") == 0)
        {
            const int32_t valueCount = 8;
            assert(stack.size() >= valueCount);
            AvgN(stack, valueCount);
        }
        else if (_strcmpi(pch, "avg16") == 0)
        {
            const int32_t valueCount = 16;
            assert(stack.size() >= valueCount);
            AvgN(stack, valueCount);
        }
        else if (_strcmpi(pch, "avg20") == 0)
        {
            const int32_t valueCount = 20;
            assert(stack.size() >= valueCount);
            AvgN(stack, valueCount);
        }
        else if (_strcmpi(pch, "scalarSub10") == 0)
        {
            const int32_t vectorWidth = 10;
            assert(stack.size() >= (vectorWidth + 1));  // vec10 + 1 scalar
            ScalarSubN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarSub20") == 0)
        {
            const int32_t vectorWidth = 20;
            assert(stack.size() >= (vectorWidth + 1));  // vec20 + 1 scalar
            ScalarSubN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarSub40") == 0)
        {
            const int32_t vectorWidth = 40;
            assert(stack.size() >= (vectorWidth + 1));  // vec40 + 1 scalar
            ScalarSubN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarSub80") == 0)
        {
            const int32_t vectorWidth = 80;
            assert(stack.size() >= (vectorWidth + 1));  // vec80 + 1 scalar
            ScalarSubN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarDiv2") == 0)
        {
            const int32_t vectorWidth = 2;
            assert(stack.size() >= (vectorWidth + 1));  // vec2 + 1 scalar
            ScalarDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarDiv4") == 0)
        {
            const int32_t vectorWidth = 4;
            assert(stack.size() >= (vectorWidth + 1));  // vec4 + 1 scalar
            ScalarDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarDiv8") == 0)
        {
            const int32_t vectorWidth = 8;
            assert(stack.size() >= (vectorWidth + 1));  // vec8 + 1 scalar
            ScalarDivN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarMul2") == 0)
        {
            const int32_t vectorWidth = 2;
            assert(stack.size() >= (vectorWidth + 1));  // vec2 + 1 scalar
            ScalarMulN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarMul4") == 0)
        {
            const int32_t vectorWidth = 4;
            assert(stack.size() >= (vectorWidth + 1));  // vec4 + 1 scalar
            ScalarMulN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarMul8") == 0)
        {
            const int32_t vectorWidth = 8;
            assert(stack.size() >= (vectorWidth + 1));  // vec8 + 1 scalar
            ScalarMulN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarMul16") == 0)
        {
            const int32_t vectorWidth = 16;
            assert(stack.size() >= (vectorWidth + 1));  // vec16 + 1 scalar
            ScalarMulN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarMul20") == 0)
        {
            const int32_t vectorWidth = 20;
            assert(stack.size() >= (vectorWidth + 1));  // vec20 + 1 scalar
            ScalarMulN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarMul32") == 0)
        {
            const int32_t vectorWidth = 32;
            assert(stack.size() >= (vectorWidth + 1));  // vec32 + 1 scalar
            ScalarMulN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarMul40") == 0)
        {
            const int32_t vectorWidth = 40;
            assert(stack.size() >= (vectorWidth + 1));  // vec40 + 1 scalar
            ScalarMulN(stack, vectorWidth);
        }
        else if (_strcmpi(pch, "scalarMul64") == 0)
        {
            const int32_t vectorWidth = 64;
            assert(stack.size() >= (vectorWidth + 1));  // vec64 + 1 scalar
            ScalarMulN(stack, vectorWidth);
        }
        else
        {
            // must be number, reference to internal counter
            gpa_uint32 index;
#ifdef _LINUX
            int scanResult = sscanf(pch, "%d", &index);
#else
            int scanResult = sscanf_s(pch, "%d", &index);
#endif
            UNREFERENCED_PARAMETER(scanResult);

            if(1 != scanResult)
            {
                GPA_LogDebugError("Failed for expression %s", pExpression);
            }
            assert(scanResult == 1);

            if (index < results.size())
            {
                const InternalCounterType internalVal      = *reinterpret_cast<const InternalCounterType*>(results[index]);
                T                         internalValFloat = static_cast<T>(internalVal);
                stack.push_back(internalValFloat);
            }
            else
            {
                // the index was invalid, so the counter result is unknown
                assert(0);
                GPA_LogError("counter registerIndex in equation is out of range.");
                status = GPA_STATUS_ERROR_INVALID_COUNTER_EQUATION;
                break;
            }
        }

        pch = strtok_s(nullptr, " ,", &pContext);
    }

    if (stack.size() != 1)
    {
        std::stringstream ss;
        ss << "Invalid formula: " << pExpression << ".";
        GPA_LogError(ss.str().c_str());
        status = GPA_STATUS_ERROR_INVALID_COUNTER_EQUATION;
    }

    assert(stack.size() == 1);
    *pWriteResult = stack.back();

    return status;
}