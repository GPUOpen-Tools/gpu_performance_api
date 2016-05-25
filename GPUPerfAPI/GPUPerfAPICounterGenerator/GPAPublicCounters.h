//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Manages a set of public counters
//==============================================================================

#ifndef _GPA_PUBLIC_COUNTERS_H_
#define _GPA_PUBLIC_COUNTERS_H_

#include <assert.h>
#include "GPUPerfAPIOS.h"
#include <vector>
#include "GPAHWInfo.h"
using std::vector;

/// Information about a public counter that is exposed through the interface
class GPA_PublicCounter
{
public:

    /// constructor taking a compute expression string
    GPA_PublicCounter(unsigned int index, const char* pName, const char* pDescription, GPA_Type dataType, GPA_Usage_Type usageType, GPA_CounterType counterType, vector< gpa_uint32 >& internalCountersRequired, const char* pComputeExpression);

    /// Default Constructor.
    /// temporary addition of a default constructor to allow vector to build and execute.
    GPA_PublicCounter()
    {
    }

    /// index of this counter
    unsigned int m_index;

    /// The name of the counter
    const char* m_pName;

    /// A description of what the counter means.
    const char* m_pDescription;

    /// Data type
    GPA_Type m_dataType;

    /// How the counter should be interpreted (percentage, ratio, bytes, etc)
    GPA_Usage_Type m_usageType;

    /// The counter type
    GPA_CounterType m_counterType;

    /// List of internal counters that are needed to calculate this public counter
    vector< gpa_uint32 > m_internalCountersRequired;

    /// A string expression that shows how to calculate this counter.
    const char* m_pComputeExpression;
};

/// The set of available public counters
class GPA_PublicCounters
{
public:

    /// Initializes an instance of the GPA_PublicCounters class.
    GPA_PublicCounters():
        m_countersGenerated(false)
    {
    }

    /// Destructor
    virtual ~GPA_PublicCounters()
    {
    }

    /// Obtains the number of public counters
    virtual gpa_uint32 GetNumCounters();

    /// Gets a counter's name
    /// \param index the index of the requested counter
    /// \return the counter's name
    virtual const char* GetCounterName(gpa_uint32 index)
    {
        assert(index < m_counters.size());
        return m_counters[index].m_pName;
    }

    /// Gets a counter's description
    /// \param index the index of the requested counter
    /// \return the counter's description
    virtual const char* GetCounterDescription(gpa_uint32 index)
    {
        assert(index < m_counters.size());
        return m_counters[index].m_pDescription;
    }

    /// Gets a counter's usage type
    /// \param index the index of the requested counter
    /// \return the counter's usage type
    virtual GPA_Usage_Type GetCounterUsageType(gpa_uint32 index)
    {
        assert(index < m_counters.size());
        return m_counters[index].m_usageType;
    }

    /// Gets a counter's data type
    /// \param index the index of the requested counter
    /// \return the counter's data type
    virtual GPA_Type GetCounterDataType(gpa_uint32 index)
    {
        assert(index < m_counters.size());
        return m_counters[index].m_dataType;
    }

    /// Gets a counter's type
    /// \param index the index of the requested counter
    /// \return the counter's type
    virtual GPA_CounterType GetCounterType(gpa_uint32 index)
    {
        assert(index < m_counters.size());
        return m_counters[index].m_counterType;
    }

    /// Defines a public counter based on an expression
    /// \param pName the name of the counter
    /// \param pDescription the description of the counter
    /// \param dataType the data type of the counter
    /// \param usageType the usage type of the counter
    /// \param counterType the type of the counter
    /// \param internalCountersRequired the list of required internal counters
    /// \param pComputeExpression the compute expression of the counter
    virtual void DefinePublicCounter(const char* pName, const char* pDescription, GPA_Type dataType, GPA_Usage_Type usageType, GPA_CounterType counterType, vector< gpa_uint32 >& internalCountersRequired, const char* pComputeExpression);

    /// Adds a public counter to the set of available counters
    /// \param publicCounter the public counter to add
    virtual void AddPublicCounter(GPA_PublicCounter& publicCounter)
    {
        m_counters.push_back(publicCounter);
    }

    /// Get the counter at the specified index
    /// \param index the index of the requested counter
    /// \return the counter at the specified index
    virtual const GPA_PublicCounter* GetCounter(gpa_uint32 index)
    {
        assert(index < m_counters.size());
        return &m_counters[index];
    }

    /// Clears the list of available counters
    virtual void Clear();

    /// Gets the list of internal counters that are required for a public counter
    /// \param index the index of the requested counter
    /// \return the list of internal counters
    virtual vector< gpa_uint32 >& GetInternalCountersRequired(gpa_uint32 index)
    {
        assert(index < m_counters.size());
        return m_counters[index].m_internalCountersRequired;
    }

    /// Computes a counter's result
    /// \param counterIndex the index of the counter
    /// \param results the counter results buffer
    /// \param internalCounterTypes the list of internal counter types
    /// \param pResult the result of the computation
    /// \param pHwInfo the hardware info for the current hardware
    virtual void ComputeCounterValue(gpa_uint32 counterIndex, vector< char* >& results, vector< GPA_Type >& internalCounterTypes, void* pResult, GPA_HWInfo* pHwInfo);

    /// indicates that the public counters have been generated
    bool m_countersGenerated;

protected:
    /// The set of available public counters
    vector< GPA_PublicCounter > m_counters;
};

#endif // _GPA_PUBLIC_COUNTERS_H_
