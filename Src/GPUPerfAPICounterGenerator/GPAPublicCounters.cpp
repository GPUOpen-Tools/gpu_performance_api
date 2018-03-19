//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Manages a set of public counters
//==============================================================================


#include <stdio.h>
#include <sstream>
#include <string.h> // for strcpy
#include <algorithm>

#include "Utility.h"
#include "Logging.h"
#include "GPAPublicCounters.h"
#include "GPACommonDefs.h"

GPA_PublicCounter::GPA_PublicCounter(
    unsigned int index,
    const char* pName,
    const char* pGroup,
    const char* pDescription,
    GPA_Data_Type dataType,
    GPA_Usage_Type usageType,
    vector< gpa_uint32 >& internalCountersRequired,
    const char* pComputeExpression,
    const char* pUuid):
    m_index(index),
    m_pName(pName),
    m_pGroup(pGroup),
    m_pDescription(pDescription),
    m_dataType(dataType),
    m_usageType(usageType),
    m_internalCountersRequired(internalCountersRequired),
    m_pComputeExpression(pComputeExpression)
{
    uint32_t bytes[8];
#ifdef _WIN32
    sscanf_s(pUuid, "%08lX-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X",
             &m_uuid.Data1,
             &m_uuid.Data2,
             &m_uuid.Data3,
             &bytes[0],
             &bytes[1],
             &bytes[2],
             &bytes[3],
             &bytes[4],
             &bytes[5],
             &bytes[6],
             &bytes[7]
            );

    for (int i = 0; i < _countof(bytes); ++i)
    {
        m_uuid.Data4[i] = static_cast<unsigned char>(bytes[i]);
    }

#else
    sscanf(pUuid, "%08lX-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X",
           &m_uuid.m_data1,
           &m_uuid.m_data2,
           &m_uuid.m_data3,
           &bytes[0],
           &bytes[1],
           &bytes[2],
           &bytes[3],
           &bytes[4],
           &bytes[5],
           &bytes[6],
           &bytes[7]
          );

    for (int i = 0; i < (sizeof(bytes) / sizeof(bytes[0])); ++i)
    {
        m_uuid.m_data4[i] = static_cast<unsigned char>(bytes[i]);
    }

#endif
}

GPA_PublicCounter::GPA_PublicCounter():
    m_index(0u),
    m_pName(nullptr),
    m_pGroup(nullptr),
    m_pDescription(nullptr),
    m_dataType(GPA_DATA_TYPE__LAST),
    m_usageType(GPA_USAGE_TYPE__LAST),
    m_pComputeExpression(nullptr)
{
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------

void GPA_PublicCounters::DefinePublicCounter(
    const char* pName,
    const char* pGroup,
    const char* pDescription,
    GPA_Data_Type dataType,
    GPA_Usage_Type usageType,
    vector< gpa_uint32 >& internalCountersRequired,
    const char* pComputeExpression,
    const char* pUuid)
{
    assert(pName);
    assert(pGroup);
    assert(pDescription);
    assert(dataType < GPA_DATA_TYPE__LAST);
    assert(internalCountersRequired.size() > 0);
    assert(pComputeExpression);
    assert(strlen(pComputeExpression) > 0);
    assert(pUuid);

    unsigned int index = static_cast<unsigned int>(m_counters.size());

    m_counters.push_back(GPA_PublicCounter(index, pName, pGroup, pDescription, dataType, usageType, internalCountersRequired, pComputeExpression, pUuid));
}

void GPA_PublicCounters::UpdateAsicSpecificPublicCounter(
    const char* pName,
    vector< gpa_uint32 >& internalCountersRequired,
    const char* pComputeExpression)
{
    for (auto& counter : m_counters)
    {
        if (!_strcmpi(pName, counter.m_pName))
        {
            counter.m_internalCountersRequired.clear();
            counter.m_internalCountersRequired = internalCountersRequired;
            counter.m_pComputeExpression = pComputeExpression;
            return;
        }
    }

    // Error - counter name not found. Should not happen in practice.
    assert(0);
}

void GPA_PublicCounters::Clear()
{
    m_counters.clear();
    m_countersGenerated = false;
}


gpa_uint32 GPA_PublicCounters::GetNumCounters() const
{
    return static_cast<gpa_uint32>(m_counters.size());
}


/// Evaluates a counter formula expression
/// T is public counter type
/// \param pExpression the counter formula
/// \param[out] pResult the result value
/// \param results list of the hardware counter results
/// \param internalCounterTypes list of the hardware counter types
/// \param resultType the coutner result type
/// \param pHwInfo the hardware info
template<class T, class InternalCounterType>
static void EvaluateExpression(
    const char* pExpression,
    void* pResult,
    vector< gpa_uint64* >& results,
    vector< GPA_Data_Type >& internalCounterTypes,
    GPA_Data_Type resultType,
    const GPA_HWInfo* pHwInfo)
{
    UNREFERENCED_PARAMETER(internalCounterTypes);

    assert(nullptr != pHwInfo);

    size_t expressionLen = strlen(pExpression) + 1;
    char* pBuf = new(std::nothrow) char[expressionLen];

    strcpy_s(pBuf, expressionLen, pExpression);

    vector< T > stack;
    T* pWriteResult = reinterpret_cast<T*>(pResult);

    char* pContext;
    char* pch = strtok_s(pBuf, " ,", &pContext);

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
            T constant = static_cast<T>(0);
            int scanResult = 0;

            if (resultType == GPA_DATA_TYPE_FLOAT64)
            {
#ifdef _LINUX
                scanResult = sscanf(pch, "(%lf)", reinterpret_cast<gpa_float64*>(&constant));
#else
                scanResult = sscanf_s(pch, "(%lf)", reinterpret_cast<gpa_float64*>(&constant));
#endif // _LINUX
            }
            else if (resultType == GPA_DATA_TYPE_UINT64)
            {
#ifdef _LINUX
                scanResult = sscanf(pch, "(%llu)", reinterpret_cast<gpa_uint64*>(&constant));
#else
                scanResult = sscanf_s(pch, "(%I64u)", reinterpret_cast<gpa_uint64*>(&constant));
#endif // _LINUX
            }
            else
            {
                // Unsupported public counter type
                assert(false);
            }

            assert(scanResult == 1);

            stack.push_back(constant);
        }
        else if (_strcmpi(pch, "num_shader_engines") == 0)
        {
            stack.push_back(static_cast<T>(pHwInfo->GetNumberShaderEngines()));
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
        else if (_strcmpi(pch, "sum4") == 0)
        {
            assert(stack.size() >= 4);
            T sum = 0;

            // pop the last 4 items and add them together
            for (int i = 0; i < 4; i++)
            {
                T value = stack.back();
                stack.pop_back();

                sum += value;
            }

            stack.push_back(sum);
        }
        else if (_strcmpi(pch, "sum8") == 0)
        {
            assert(stack.size() >= 8);
            T sum = 0;

            // pop the last 8 items and add them together
            for (int i = 0; i < 8; i++)
            {
                T value = stack.back();
                stack.pop_back();

                sum += value;
            }

            stack.push_back(sum);
        }
        else if (_strcmpi(pch, "sum10") == 0)
        {
            assert(stack.size() >= 10);
            T sum = 0;

            // pop the last 10 items and add them together
            for (int i = 0; i < 10; i++)
            {
                T value = stack.back();
                stack.pop_back();

                sum += value;
            }

            stack.push_back(sum);
        }
        else if (_strcmpi(pch, "sum11") == 0)
        {
            assert(stack.size() >= 11);
            T sum = 0;

            // pop the last 11 items and add them together
            for (int i = 0; i < 11; i++)
            {
                T value = stack.back();
                stack.pop_back();

                sum += value;
            }

            stack.push_back(sum);
        }
        else if (_strcmpi(pch, "sum12") == 0)
        {
            assert(stack.size() >= 12);
            T sum = 0;

            // pop the last 12 items and add them together
            for (int i = 0; i < 12; i++)
            {
                T value = stack.back();
                stack.pop_back();

                sum += value;
            }

            stack.push_back(sum);
        }
        else if (_strcmpi(pch, "sum16") == 0)
        {
            assert(stack.size() >= 16);
            T sum = 0;

            // pop the last 16 items and add them together
            for (int i = 0; i < 16; i++)
            {
                T value = stack.back();
                stack.pop_back();

                sum += value;
            }

            stack.push_back(sum);
        }
        else if (_strcmpi(pch, "sum32") == 0)
        {
            assert(stack.size() >= 32);
            T sum = 0;

            // pop the last 32 items and add them together
            for (int i = 0; i < 32; i++)
            {
                T value = stack.back();
                stack.pop_back();

                sum += value;
            }

            stack.push_back(sum);
        }
        else if (_strcmpi(pch, "sum44") == 0)
        {
            assert(stack.size() >= 44);
            T sum = 0;

            // pop the last 44 items and add them together
            for (int i = 0; i < 44; i++)
            {
                T value = stack.back();
                stack.pop_back();

                sum += value;
            }

            stack.push_back(sum);
        }
        else if (_strcmpi(pch, "sum64") == 0)
        {
            assert(stack.size() >= 64);
            T sum = 0;

            // pop the last 64 items and add them together
            for (int i = 0; i < 64; i++)
            {
                T value = stack.back();
                stack.pop_back();

                sum += value;
            }

            stack.push_back(sum);
        }
        else if (_strcmpi(pch, "sum256") == 0)
        {
            assert(stack.size() >= 256);
            T sum = 0;

            // pop the last 256 items and add them together
            for (int i = 0; i < 256; i++)
            {
                T value = stack.back();
                stack.pop_back();

                sum += value;
            }

            stack.push_back(sum);
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
            assert(scanResult == 1);

            assert(index < results.size());

            if (index < results.size())
            {
                InternalCounterType internalVal = *reinterpret_cast<InternalCounterType*>(results[index]);
                T internalValFloat = static_cast<T>(internalVal);
                stack.push_back(internalValFloat);
            }
            else
            {
                // the index was invalid, so the counter result is unknown
                assert(!"counter index in equation is out of range");
                stack.push_back(0);
            }
        }

        pch = strtok_s(nullptr, " ,", &pContext);
    }

    if (stack.size() != 1)
    {
        std::stringstream ss;
        ss << "Invalid formula: " << pExpression << ".";
        GPA_LogError(ss.str().c_str());
    }

    assert(stack.size() == 1);
    *pWriteResult = stack.back();

    delete[] pBuf;
}

void GPA_PublicCounters::ComputeCounterValue(gpa_uint32 counterIndex, vector< gpa_uint64* >& results, vector< GPA_Data_Type >& internalCounterTypes, void* pResult, const GPA_HWInfo* pHwInfo) const
{
    if (nullptr != m_counters[counterIndex].m_pComputeExpression)
    {
#ifdef AMDT_INTERNAL
        GPA_LogDebugCounterDefs("'%s' equation is %s.", m_counters[counterIndex].m_pName, m_counters[counterIndex].m_pComputeExpression);
#endif

        if (internalCounterTypes[0] == GPA_DATA_TYPE_UINT64)
        {
            if (m_counters[counterIndex].m_dataType == GPA_DATA_TYPE_FLOAT64)
            {
                EvaluateExpression<gpa_float64, gpa_uint64>(m_counters[counterIndex].m_pComputeExpression, pResult, results, internalCounterTypes, m_counters[counterIndex].m_dataType, pHwInfo);
            }
            else if (m_counters[counterIndex].m_dataType == GPA_DATA_TYPE_UINT64)
            {
                EvaluateExpression<gpa_uint64, gpa_uint64>(m_counters[counterIndex].m_pComputeExpression, pResult, results, internalCounterTypes, m_counters[counterIndex].m_dataType, pHwInfo);
            }
            else
            {
                // public counter type not recognized or not currently supported.
                GPA_LogError("Unable to compute counter value: unrecognized public counter type.");
                assert(false);
            }
        }
        else
        {
            GPA_LogError("Unable to compute counter value: unrecognized internal counter type.");
            assert(false);
        }
    }
    else
    {
        // no method of evaluation specified for counter
        GPA_LogError("Unable to compute counter value: unrecognized compute expression.");
        assert(false);
    }
}


