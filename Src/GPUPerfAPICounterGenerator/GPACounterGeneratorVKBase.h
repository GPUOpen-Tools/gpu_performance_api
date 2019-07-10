//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for VK Base counter generation
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_VK_BASE_H_
#define _GPA_COUNTER_GENERATOR_VK_BASE_H_

#include "GPACounterGeneratorBase.h"

/// The VK-specific counter generator
class GPA_CounterGeneratorVKBase : public GPA_CounterGeneratorBase
{
public:
    /// Get the SW counter description for the given SW counter index
    /// \return The SW counter description
    /// \param[in] swCounterIndex The SW counter index
    /// \param[out] swCounterDesc Software counter description
    static bool GetSwCounterDesc(const gpa_uint32 swCounterIndex, GPA_SoftwareCounterDesc& swCounterDesc);

    /// Constructor
    GPA_CounterGeneratorVKBase() = default;

    /// Destructor
    virtual ~GPA_CounterGeneratorVKBase() = default;

protected:
    /// \copydoc GPA_CounterGeneratorBase::GeneratePublicCounters
    virtual GPA_Status GeneratePublicCounters(GDT_HW_GENERATION    desiredGeneration,
                                              GDT_HW_ASIC_TYPE     asicType,
                                              gpa_uint8            generateAsicSpecificCounters,
                                              GPA_DerivedCounters* pPublicCounters) override;

    /// \copydoc GPA_CounterGeneratorBase::GenerateHardwareCounters
    virtual GPA_Status GenerateHardwareCounters(GDT_HW_GENERATION     desiredGeneration,
                                                GDT_HW_ASIC_TYPE      asicType,
                                                gpa_uint8             generateAsicSpecificCounters,
                                                GPA_HardwareCounters* pHardwareCounters) override;

    /// \copydoc GPA_CounterGeneratorBase::GenerateSoftwareCounters
    virtual GPA_Status GenerateSoftwareCounters(GDT_HW_GENERATION     desiredGeneration,
                                                GDT_HW_ASIC_TYPE      asicType,
                                                gpa_uint8             generateAsicSpecificCounters,
                                                GPA_SoftwareCounters* pSoftwareCounters) override;

    /// \copydoc GPA_CounterGeneratorBase::ComputeSWCounterValue
    virtual void ComputeSWCounterValue(gpa_uint32 softwareCounterIndex, gpa_uint64 value, void* pResult, const GPA_HWInfo* pHwInfo) const override;

private:
    static const GPA_SoftwareCounterDesc s_VKSWCounters[];     ///< VK SW counters list
    static const size_t                  s_VKSWCountersCount;  ///< VK SW counter list size
    /// Copy constructor - private override to prevent usage
    GPA_CounterGeneratorVKBase(const GPA_CounterGeneratorVKBase&) = delete;

    /// Move constructor - private override to prevent usage
    GPA_CounterGeneratorVKBase(GPA_CounterGeneratorVKBase&&) = delete;

    /// Copy operator - private override to prevent usage
    /// \return reference to object
    GPA_CounterGeneratorVKBase& operator=(const GPA_CounterGeneratorVKBase&) = delete;

    /// Move operator - private override to prevent usage
    /// \return reference to object
    GPA_CounterGeneratorVKBase& operator=(GPA_CounterGeneratorVKBase&&) = delete;

    /// Generate VK API software counters
    /// \return GPA_STATUS_OK if generating counters succeeded, false if it failed
    GPA_Status GenerateVKSoftwareCounters();
};

#endif  // _GPA_COUNTER_GENERATOR_VK_BASE_H_
