//==============================================================================
// Copyright (c) 2017-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for VK counter generation
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_VK_H_
#define _GPA_COUNTER_GENERATOR_VK_H_

#include "GPACounterGeneratorVKBase.h"

/// The VK-specific counter generator
class GPA_CounterGeneratorVK : public GPA_CounterGeneratorVKBase
{
public:
    /// Construct a GPA VK counter generator
    GPA_CounterGeneratorVK();

    /// Destroy this GPA VK counter generator
    virtual ~GPA_CounterGeneratorVK() = default;

    /// Copy constructor - private override to prevent usage
    GPA_CounterGeneratorVK(const GPA_CounterGeneratorVK&) = delete;

    /// Move constructor - private override to prevent usage
    GPA_CounterGeneratorVK(GPA_CounterGeneratorVK&&) = delete;

    /// Copy operator - private override to prevent usage
    /// \return reference to object
    GPA_CounterGeneratorVK& operator=(const GPA_CounterGeneratorVK&) = delete;

    /// Move operator - private override to prevent usage
    /// \return reference to object
    GPA_CounterGeneratorVK& operator=(GPA_CounterGeneratorVK&&) = delete;

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

    /// \copydoc GPA_CounterGeneratorBase::GenerateHardwareExposedCounters
    GPA_Status GenerateHardwareExposedCounters(GDT_HW_GENERATION     desiredGeneration,
                                               GDT_HW_ASIC_TYPE      asicType,
                                               gpa_uint8             generateAsicSpecificCounters,
                                               GPA_HardwareCounters* pHardwareCounters) override;

#ifdef AMDT_INTERNAL
    /// \copydoc GPA_CounterGeneratorBase::GenerateInternalDerivedCounters
    GPA_Status GenerateInternalDerivedCounters(GDT_HW_GENERATION    desiredGeneration,
                                               GDT_HW_ASIC_TYPE     asicType,
                                               gpa_uint8            generateAsicSpecificCounters,
                                               GPA_DerivedCounters* pPublicCounters) override;
#endif

private:
    /// Checks if the given hw generation represents an AMD GPU
    /// \param generation the hardware generation to check
    /// \return true if the hardware generation represents and AMD GPU
    static bool IsAMDGPU(GDT_HW_GENERATION generation);

    /// Logic inside this function is based on the AmdExtGpuBlock enum in AmdExtGpaInterface in DXCP driver.
    /// The driver gives each block an ID, but ignores the instance. GPA treats each instance as a different
    /// block, so we need to translate.
    /// \param generation the generation whose block id needs to be calculated
    /// \param pGroup the group for which the block id needs to be calculated
    /// \return the block id according to the driver
    static UINT CalculateBlockIdVK(GDT_HW_GENERATION generation, GPA_CounterGroupDesc* pGroup);

    /// Generates internal counters
    /// \param pHardwareCounters the hardware counters to generate
    /// \param generation the generation for which counters need to be generated
    /// \return true on success
    static bool GenerateInternalCounters(GPA_HardwareCounters* pHardwareCounters, GDT_HW_GENERATION generation);
};

#endif  // _GPA_COUNTER_GENERATOR_VK_H_
