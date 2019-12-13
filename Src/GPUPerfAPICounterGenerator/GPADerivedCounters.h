//==============================================================================
// Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Manages a set of derived counters
//==============================================================================

#ifndef _GPA_DERIVED_COUNTERS_H_
#define _GPA_DERIVED_COUNTERS_H_

#include <assert.h>
#include <vector>
#include "GPAHWInfo.h"
using std::vector;

/// Information about a derived counter that is exposed through the interface
class GPA_DerivedCounter
{
public:
    /// constructor taking a compute expression string
    /// \param index the index of the derived counter
    /// \param pName the name of the derived counter
    /// \param pGroup the group of the derived counter
    /// \param pDescription the description of the derived counter
    /// \param dataType the data type of the derived counter
    /// \param usageType the usage type of the derived counter
    /// \param internalCountersRequired the list of hardware counters required by the derived counter
    /// \param pComputeExpression the formula used to compute the derived counter
    /// \param pUuid UUID string that uniquely and consistently identifies the derived counter
    GPA_DerivedCounter(unsigned int        index,
                       const char*         pName,
                       const char*         pGroup,
                       const char*         pDescription,
                       GPA_Data_Type       dataType,
                       GPA_Usage_Type      usageType,
                       vector<gpa_uint32>& internalCountersRequired,
                       const char*         pComputeExpression,
                       const char*         pUuid);

    /// Default Constructor.
    /// temporary addition of a default constructor to allow vector to build and execute.
    GPA_DerivedCounter();

    unsigned int       m_index;                     ///< index of this counter
    const char*        m_pName;                     ///< The name of the counter
    const char*        m_pGroup;                    ///< A group to which the counter is related
    const char*        m_pDescription;              ///< A description of what the counter means.
    GPA_Data_Type      m_dataType;                  ///< Data type
    GPA_Usage_Type     m_usageType;                 ///< How the counter should be interpreted (percentage, ratio, bytes, etc)
    vector<gpa_uint32> m_internalCountersRequired;  ///< List of internal counters that are needed to calculate this derived counter
    const char*        m_pComputeExpression;        ///< A string expression that shows how to calculate this counter.
    GPA_UUID           m_uuid = {};                 ///< UUID that uniquely and consistently identifies a counter.
};

/// The set of available derived counters
class GPA_DerivedCounters
{
public:
    /// Initializes an instance of the GPA_DerivedCounters class.
    GPA_DerivedCounters()
        : m_countersGenerated(false)
    {
    }

    /// Destructor
    virtual ~GPA_DerivedCounters() = default;

    /// Obtains the number of derived counters
    /// \return the number of derived counters
    virtual gpa_uint32 GetNumCounters() const;

    /// Gets a counter's name
    /// \param index the index of the requested counter
    /// \return the counter's name
    virtual const char* GetCounterName(gpa_uint32 index) const
    {
        assert(index < m_counters.size());
        return m_counters[index].m_pName;
    }

    /// Gets a counter's group name
    /// \param index the index of the requested counter
    /// \return the counter's group name
    virtual const char* GetCounterGroup(gpa_uint32 index) const
    {
        assert(index < m_counters.size());
        return m_counters[index].m_pGroup;
    }

    /// Gets a counter's description
    /// \param index the index of the requested counter
    /// \return the counter's description
    virtual const char* GetCounterDescription(gpa_uint32 index) const
    {
        assert(index < m_counters.size());
        return m_counters[index].m_pDescription;
    }

    /// Gets a counter's usage type
    /// \param index the index of the requested counter
    /// \return the counter's usage type
    virtual GPA_Usage_Type GetCounterUsageType(gpa_uint32 index) const
    {
        assert(index < m_counters.size());
        return m_counters[index].m_usageType;
    }

    /// Gets a counter's data type
    /// \param index the index of the requested counter
    /// \return the counter's data type
    virtual GPA_Data_Type GetCounterDataType(gpa_uint32 index) const
    {
        assert(index < m_counters.size());
        return m_counters[index].m_dataType;
    }

    /// Gets a counter's UUID
    /// \param index the index of the requested counter
    /// \return the counter's UUID
    virtual GPA_UUID GetCounterUuid(gpa_uint32 index) const
    {
        assert(index < m_counters.size());
        return m_counters[index].m_uuid;
    }

    /// Gets a counter's supported sample type
    /// \param index the index of the requested counter
    /// \return the counter's supported sample types (a combination of GPA_Counter_Sample_Bits)
    virtual GPA_Counter_Sample_Type GetCounterSampleType(gpa_uint32 index) const
    {
        assert(index < m_counters.size());

        // TODO: Hardcoding to discrete-only counters for now.
        //       Uncomment the below line and remove the following two lines when we have a mechanism
        //       for public counters to specify which sample types they support.

        //return m_counters[index].m_supportedSampleTypes;
        UNREFERENCED_PARAMETER(index);
        return GPA_COUNTER_SAMPLE_TYPE_DISCRETE;
    }

    /// Defines a public counter based on an expression
    /// \param pName the name of the counter
    /// \param pGroup the group that the counter is related to
    /// \param pDescription the description of the counter
    /// \param dataType the data type of the counter
    /// \param usageType the usage type of the counter
    /// \param internalCountersRequired the list of required internal counters
    /// \param pComputeExpression the compute expression of the counter
    /// \param pUuid UUID string that uniquely and consistently identifies the counter
    virtual void DefineDerivedCounter(const char*         pName,
                                      const char*         pGroup,
                                      const char*         pDescription,
                                      GPA_Data_Type       dataType,
                                      GPA_Usage_Type      usageType,
                                      vector<gpa_uint32>& internalCountersRequired,
                                      const char*         pComputeExpression,
                                      const char*         pUuid);

    /// Updates an existing derived counter based on ASIC-specific registers.
    /// \param pName the name of the counter
    /// \param internalCountersRequired the list of required internal counters
    /// \param pComputeExpression the compute expression of the counter
    virtual void UpdateAsicSpecificDerivedCounter(const char* pName, vector<gpa_uint32>& internalCountersRequired, const char* pComputeExpression);

    /// Adds a derived counter to the set of available counters
    /// \param derivedCounter the derived counter to add
    virtual void AddDerivedCounter(GPA_DerivedCounter& derivedCounter)
    {
        m_counters.push_back(derivedCounter);
    }

    /// Get the counter at the specified index
    /// \param index the index of the requested counter
    /// \return the counter at the specified index
    virtual const GPA_DerivedCounter* GetCounter(gpa_uint32 index) const
    {
        assert(index < m_counters.size());
        return &m_counters[index];
    }

    /// Clears the list of available counters
    virtual void Clear();

    /// Gets the list of internal counters that are required for a derived counter
    /// \param index the index of the requested counter
    /// \return the list of internal counters
    virtual const vector<gpa_uint32>& GetInternalCountersRequired(gpa_uint32 index) const
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
    /// \return GPA_STATUS_OK on success, otherwise an error code
    virtual GPA_Status ComputeCounterValue(gpa_uint32                       counterIndex,
                                           const vector<const gpa_uint64*>& results,
                                           vector<GPA_Data_Type>&           internalCounterTypes,
                                           void*                            pResult,
                                           const GPA_HWInfo*                pHwInfo) const;

    bool m_countersGenerated;  ///< indicates that the derived counters have been generated

protected:
    vector<GPA_DerivedCounter> m_counters;  ///< The set of available derived counters
};

#ifdef AMDT_INTERNAL

struct GPACounterDesc;
/// Entry point to get internal derived counters
/// \param apiType the API whose counters are needed
/// \param desiredGeneration the generation whose counters are needed
/// \param ppInternalDerivedCounters[out] pointer to array of internal derived counters
/// \param pInternalDerivedCounterCount[out] pointer to count of internal derived counters
/// \return internalDerivedCounterCount
GPA_Status GPA_GetInternalDerivedCounters(GPA_API_Type           apiType,
                                          GPA_Hw_Generation      desiredGeneration,
                                          const GPACounterDesc** ppInternalDerivedCounters,
                                          size_t*                pInternalDerivedCounterCount);

#endif  // AMDT_INTERNAL


#endif  // _GPA_DERIVED_COUNTERS_H_
