//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
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
    virtual ~GPA_CounterGeneratorVK();

protected:
    /// Overridden methods -- see base for documentation
    virtual GPA_Status GeneratePublicCounters(
        GDT_HW_GENERATION desiredGeneration, GPA_PublicCounters* pPublicCounters) override;

    virtual GPA_Status GenerateHardwareCounters(
        GDT_HW_GENERATION desiredGeneration, GPA_HardwareCounters* pHardwareCounters) override;

private:

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

    /// Copy constructor - private override to prevent usage
    GPA_CounterGeneratorVK(const GPA_CounterGeneratorVK&) = delete;

    /// Move constructor - private override to prevent usage
    GPA_CounterGeneratorVK(GPA_CounterGeneratorVK&&) = delete;

    /// Copy operator - private override to prevent usage
    GPA_CounterGeneratorVK& operator=(const GPA_CounterGeneratorVK&) = delete;

    /// Move operator - private override to prevent usage
    GPA_CounterGeneratorVK& operator=(GPA_CounterGeneratorVK&&) = delete;

};

#endif // _GPA_COUNTER_GENERATOR_VK_H_

