//==============================================================================
// Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Base class for counter generation
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_BASE_H_
#define _GPA_COUNTER_GENERATOR_BASE_H_

#include <unordered_map>

#include "GPAHardwareCounters.h"
#include "GPASoftwareCounters.h"
#include "IGPACounterAccessor.h"

/// Base class for counter generation
class GPA_CounterGeneratorBase : public IGPACounterAccessor
{
public:
    /// Constructor
    GPA_CounterGeneratorBase();

    /// Destructor
    virtual ~GPA_CounterGeneratorBase() = default;

    /// \copydoc IGPACounterAccessor::SetAllowedCounters()
    void SetAllowedCounters(bool bAllowPublicCounters, bool bAllowHardwareCounters, bool bAllowSoftwareCounters) override;

    /// \copydoc IGPACounterAccessor::GetNumCounters()
    gpa_uint32 GetNumCounters() const override;

    /// \copydoc IGPACounterAccessor::GetCounterName()
    const char* GetCounterName(gpa_uint32 index) const override;

    /// \copydoc IGPACounterAccessor::GetCounterGroup()
    const char* GetCounterGroup(gpa_uint32 index) const override;

    /// \copydoc IGPACounterAccessor::GetCounterDescription()
    const char* GetCounterDescription(gpa_uint32 index) const override;

    /// \copydoc IGPACounterAccessor::GetCounterDataType()
    GPA_Data_Type GetCounterDataType(gpa_uint32 index) const override;

    /// \copydoc IGPACounterAccessor::GetCounterUsageType()
    GPA_Usage_Type GetCounterUsageType(gpa_uint32 index) const override;

    /// \copydoc IGPACounterAccessor::GetCounterUuid()
    GPA_UUID GetCounterUuid(gpa_uint32 index) const override;

    /// \copydoc IGPACounterAccessor::GetCounterSampleType()
    GPA_Counter_Sample_Type GetCounterSampleType(gpa_uint32 index) const override;

    /// \copydoc IGPACounterAccessor::GetPublicCounter()
    const GPA_DerivedCounter* GetPublicCounter(gpa_uint32 index) const override;

    /// \copydoc IGPACounterAccessor::GetHardwareCounterExt()
    const GPA_HardwareCounterDescExt* GetHardwareCounterExt(gpa_uint32 index) const override;

    /// \copydoc IGPACounterAccessor::GetNumPublicCounters()
    gpa_uint32 GetNumPublicCounters() const override;

    /// \copydoc IGPACounterAccessor::GetInternalCountersRequired()
    std::vector<gpa_uint32> GetInternalCountersRequired(gpa_uint32 index) const override;

    /// \copydoc IGPACounterAccessor::ComputePublicCounterValue()
    GPA_Status ComputePublicCounterValue(gpa_uint32                            counterIndex,
                                         const std::vector<const gpa_uint64*>& results,
                                         std::vector<GPA_Data_Type>&           internalCounterTypes,
                                         void*                                 pResult,
                                         const GPA_HWInfo*                     pHwInfo) const override;

    /// \copydoc IGPACounterAccessor::GetCounterSourceInfo()
    GPACounterSourceInfo GetCounterSourceInfo(gpa_uint32 globalIndex) const override;

    /// \copydoc IGPACounterAccessor::GetCounterIndex()
    bool GetCounterIndex(const char* pName, gpa_uint32* pIndex) const override;

    /// \copydoc IGPACounterAccessor::GetHardwareCounters()
    const GPA_HardwareCounters* GetHardwareCounters() const override;

    /// \copydoc IGPACounterAccessor::GetSoftwareCounters()
    const GPA_SoftwareCounters* GetSoftwareCounters() const override;

    /// Generate the counters for the specified generation
    /// \param desiredGeneration the generation whose counters are needed
    /// \param asicType the ASIC type whose counters are needed
    /// \param generateAsicSpecificCounters Flag that indicates whether the counters should be ASIC specific, if available.
    /// \return GPA_STATUS_OK on success
    GPA_Status GenerateCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, gpa_uint8 generateAsicSpecificCounters);

    /// \copydoc IGPACounterAccessor::ComputeSWCounterValue()
    void ComputeSWCounterValue(gpa_uint32 softwareCounterIndex, gpa_uint64 value, void* pResult, const GPA_HWInfo* pHwInfo) const override;

    /// TODO: does this need to be here in the base class?
    /// Get the number of supported AMD counters
    /// \return number of supported AMD counters
    gpa_uint32 GetNumAMDCounters() const;

    /// Generate the public counters for the specified hardware generation
    /// \param desiredGeneration the generation whose counters are needed
    /// \param asicType the ASIC whose counters are needed
    /// \param generateAsicSpecificCounters Flag that indicates whether the counters should be ASIC specific, if available.
    /// \param[out] pPublicCounters the generated counters
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status GeneratePublicCounters(GDT_HW_GENERATION    desiredGeneration,
                                              GDT_HW_ASIC_TYPE     asicType,
                                              gpa_uint8            generateAsicSpecificCounters,
                                              GPA_DerivedCounters* pPublicCounters) = 0;

    /// Generate the hardware counters for the specified hardware generation
    /// \param desiredGeneration the generation whose counters are needed
    /// \param asicType the ASIC whose counters are needed
    /// \param generateAsicSpecificCounters Flag that indicates whether the counters should be ASIC specific, if available.
    /// \param[out] pHardwareCounters the generated counters
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status GenerateHardwareCounters(GDT_HW_GENERATION     desiredGeneration,
                                                GDT_HW_ASIC_TYPE      asicType,
                                                gpa_uint8             generateAsicSpecificCounters,
                                                GPA_HardwareCounters* pHardwareCounters) = 0;

    /// Generate the software counters for the specified hardware generation
    /// \param desiredGeneration the generation whose counters are needed
    /// \param asicType the ASIC whose counters are needed
    /// \param generateAsicSpecificCounters Flag that indicates whether the counters should be ASIC specific, if available.
    /// \param[out] pSoftwareCounters the generated counters
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status GenerateSoftwareCounters(GDT_HW_GENERATION     desiredGeneration,
                                                GDT_HW_ASIC_TYPE      asicType,
                                                gpa_uint8             generateAsicSpecificCounters,
                                                GPA_SoftwareCounters* pSoftwareCounters) = 0;

    /// Generate the hardware exposed counters for the specified hardware generation
    /// \param desiredGeneration the generation whose counters are needed
    /// \param asicType the ASIC whose counters are needed
    /// \param generateAsicSpecificCounters Flag that indicates whether the counters should be ASIC specific, if available.
    /// \param[out] pHardwareCounters the generated counters
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status GenerateHardwareExposedCounters(GDT_HW_GENERATION     desiredGeneration,
                                                       GDT_HW_ASIC_TYPE      asicType,
                                                       gpa_uint8             generateAsicSpecificCounters,
                                                       GPA_HardwareCounters* pHardwareCounters);

    /// Maps the hardware counter and hardware exposed counter
    /// \param pHardwareCounters the generated counters
    /// \return true upon success otherwise false
    virtual bool MapHardwareExposedCounter(GPA_HardwareCounters* pHardwareCounters);

    GPA_DerivedCounters  m_publicCounters;    ///< the generated public counters
    GPA_HardwareCounters m_hardwareCounters;  ///< the generated hardware counters
    GPA_SoftwareCounters m_softwareCounters;  ///< the generated software counters

private:
#ifdef AMDT_INTERNAL
    /// Allow hardware counters to be given an alternate name when they are enabled using the "block:instance:event:alt_name" syntax
    /// \param index The index of a counter, must be between 0 and the value returned from GetNumPublicCounters()
    /// \param pName the alternate counter name to be used for the hardware counter
    /// \return true upon success otherwise false
    bool SetCounterName(gpa_uint32 index, const char* pName);

    /// Entry point to load internal counters
    /// \param desiredGeneration the generation whose counters are needed
    /// \param asicType the ASIC whose counters are needed
    /// \param generateAsicSpecificCounters Flag that indicates whether the counters should be ASIC specific, if available.
    /// \param[out] pPublicCounters the generated counters
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status GenerateInternalDerivedCounters(GDT_HW_GENERATION    desiredGeneration,
                                        GDT_HW_ASIC_TYPE     asicType,
                                        gpa_uint8            generateAsicSpecificCounters,
                                        GPA_DerivedCounters* pPublicCounters);
#endif

    bool m_doAllowPublicCounters;           ///< flag indicating whether or not public counters are allowed
    bool m_doAllowHardwareCounters;         ///< flag indicating whether or not hardware counters are allowed
    bool m_doAllowSoftwareCounters;         ///< flag indicating whether or not software counters are allowed
    bool m_doAllowHardwareExposedCounters;  ///< flag indicating whether or not whitelist counters are allowed

    typedef std::unordered_map<std::string, gpa_uint32> CounterNameIndexMap;  ///< typedef for an unordered_map from counter name to index
    static const gpa_uint32                             ms_COUNTER_NOT_FOUND = static_cast<gpa_uint32>(-1);  ///< const indicating that a counter was not found
    mutable CounterNameIndexMap m_counterIndexCache;  ///< cache of counter indexes, so we don't have to look up a counter more than once (it can be expensive)
};

#endif  //_GPA_COUNTER_GENERATOR_BASE_H_
