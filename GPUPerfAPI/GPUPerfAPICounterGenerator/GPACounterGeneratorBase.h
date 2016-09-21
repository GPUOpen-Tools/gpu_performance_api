//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Base class for counter generation
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_BASE_H_
#define _GPA_COUNTER_GENERATOR_BASE_H_

#include <unordered_map>

#include "GPAHardwareCounters.h"
#include "GPASoftwareCounters.h"
#include "GPAICounterAccessor.h"

/// Base class for counter generation
class GPA_CounterGeneratorBase : public GPA_ICounterAccessor
{
public:
    /// Constructor
    GPA_CounterGeneratorBase();

    /// Destructor
    virtual ~GPA_CounterGeneratorBase();

    // Implementation of GPA_ICounterAccessor -- see base class for documentation
    virtual gpa_uint32 GetNumCounters();
    virtual const char* GetCounterName(gpa_uint32 index);
    virtual const char* GetCounterDescription(gpa_uint32 index);
    virtual GPA_Type GetCounterDataType(gpa_uint32 index);
    virtual GPA_Usage_Type GetCounterUsageType(gpa_uint32 index);
    virtual const GPA_PublicCounter* GetPublicCounter(gpa_uint32 index);
    virtual GPA_HardwareCounterDescExt* GetHardwareCounterExt(gpa_uint32 index);
    virtual gpa_uint32 GetNumPublicCounters();
    virtual vector<gpa_uint32> GetInternalCountersRequired(gpa_uint32 index);
    virtual void ComputePublicCounterValue(gpa_uint32 counterIndex, std::vector<char*>& results, std::vector<GPA_Type>& internalCounterTypes, void* pResult, GPA_HWInfo* pHwInfo);
    virtual GPACounterTypeInfo GetCounterTypeInfo(gpa_uint32 globalIndex);
    virtual bool GetCounterIndex(const char* pName, gpa_uint32* pIndex);
    // end Implementation of GPA_ICounterAccessor

    /// Generate the counters for the specified generation
    /// \param desiredGeneration the generation whose counters are needed
    /// \return GPA_STATUS_OK on success
    GPA_Status GenerateCounters(GDT_HW_GENERATION desiredGeneration);

    /// Compute a software counter value
    /// \param counterIndex the index of the counter whose value is needed
    /// \param value the value of the counter
    /// \param[out] pResult the resulting value
    /// \param pHwInfo the hardware info
    virtual void ComputeSWCounterValue(gpa_uint32 counterIndex, gpa_uint64 value, void* pResult, GPA_HWInfo* pHwInfo);

    /// TODO: does this need to be here in the base class?
    /// Get the number of supported AMD counters
    gpa_uint32 GetNumAMDCounters();

    /// Get the hardware counters
    /// \return the hardware counters
    GPA_HardwareCounters* GetHardwareCounters();

    /// Get the softwarecounters
    /// \return the software counters
    GPA_SoftwareCounters* GetSoftwareCounters();

    /// Generate the public counters for the specified hardware generation
    /// \param desiredGeneration the generation whose counters are needed
    /// \param[out] pPublicCounters the generated counters
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status GeneratePublicCounters(GDT_HW_GENERATION desiredGeneration, GPA_PublicCounters* pPublicCounters) = 0;

    /// Generate the hardware counters for the specified hardware generation
    /// \param desiredGeneration the generation whose counters are needed
    /// \param[out] pHardwareCounters the generated counters
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status GenerateHardwareCounters(GDT_HW_GENERATION desiredGeneration, GPA_HardwareCounters* pHardwareCounters) = 0;

    /// Generate the software counters for the specified hardware generation
    /// \param desiredGeneration the generation whose counters are needed
    /// \param[out] pSoftwareCounters the generated counters
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status GenerateSoftwareCounters(GDT_HW_GENERATION desiredGeneration, GPA_SoftwareCounters* pSoftwareCounters) = 0;

    /// Set the flags indicating which counters are allowed
    /// \param bAllowPublicCounters flag indicating whether or not public counters are allowed
    /// \param bAllowHardwareCounters flag indicating whether or not hardware counters are allowed
    /// \param bAllowSoftwareCounters flag indicating whether or not software counters are allowed
    void SetAllowedCounters(bool bAllowPublicCounters, bool bAllowHardwareCounters, bool bAllowSoftwareCounters);

    GPA_PublicCounters   m_publicCounters;   ///< the generated public counters
    GPA_HardwareCounters m_hardwareCounters; ///< the generated hardware counters
    GPA_SoftwareCounters m_softwareCounters; ///< the generated software counters

private:

    bool m_doAllowPublicCounters;   ///< flag indicating whether or not public counters are allowed
    bool m_doAllowHardwareCounters; ///< flag indicating whether or not hardware counters are allowed
    bool m_doAllowSoftwareCounters; ///< flag indicating whether or not software counters are allowed

    typedef std::unordered_map<std::string, gpa_uint32> CounterNameIndexMap;    ///< typedef for an unordered_map from counter name to index
    static const gpa_uint32 ms_COUNTER_NOT_FOUND = static_cast<gpa_uint32>(-1); ///< const indicating that a counter was not found
    CounterNameIndexMap m_counterIndexCache;                                    ///< cache of counter indexes, so we don't have to look up a counter more than once (it can be expensive)
};

#endif //_GPA_COUNTER_GENERATOR_BASE_H_
