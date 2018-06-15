//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for CL counter generation
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_CL_H_
#define _GPA_COUNTER_GENERATOR_CL_H_

#include "GPACounterGeneratorBase.h"

/// The OpenCL-specific counter generator
class GPA_CounterGeneratorCL : public GPA_CounterGeneratorBase
{
public:

    /// Constructor
    GPA_CounterGeneratorCL();

protected:

    /// \copydoc GPA_CounterGeneratorBase::GeneratePublicCounters
    GPA_Status GeneratePublicCounters(
        GDT_HW_GENERATION desiredGeneration,
        GDT_HW_ASIC_TYPE asicType,
        gpa_uint8 generateAsicSpecificCounters,
        GPA_DerivedCounters* pPublicCounters) override;

    /// \copydoc GPA_CounterGeneratorBase::GenerateHardwareCounters
    GPA_Status GenerateHardwareCounters(
        GDT_HW_GENERATION desiredGeneration,
        GDT_HW_ASIC_TYPE asicType,
        gpa_uint8 generateAsicSpecificCounters,
        GPA_HardwareCounters* pHardwareCounters) override;

    /// \copydoc GPA_CounterGeneratorBase::GenerateSoftwareCounters
    GPA_Status GenerateSoftwareCounters(
        GDT_HW_GENERATION desiredGeneration,
        GDT_HW_ASIC_TYPE asicType,
        gpa_uint8 generateAsicSpecificCounters,
        GPA_SoftwareCounters* pSoftwareCounters) override;

private:

    /// Function to map from GPA block index to the OCL driver's block index for a particular hw generation
    /// \param desiredGeneration the hardware generation
    /// \param blockIndex GPA's block index
    /// \return the OCL driver's block index
    int GetDriverGroupId(GDT_HW_GENERATION desiredGeneration, int blockIndex) const;
};

#endif //_GPA_COUNTER_GENERATOR_CL_H_
