//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Base class for DX11 counter generation -- add D3D11 Query counters which are supported on all hardware
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_DX11_BASE_H_
#define _GPA_COUNTER_GENERATOR_DX11_BASE_H_

#include "GPACounterGeneratorBase.h"

/// Base class for DX11 counter generation -- add D3D11 Query counters which are supported on all hardware
class GPA_CounterGeneratorDX11Base : public GPA_CounterGeneratorBase
{
public:

    /// Constructor
    GPA_CounterGeneratorDX11Base();

    /// Overridden methods -- see base for documentation
    virtual GPA_Status GeneratePublicCounters(GDT_HW_GENERATION desiredGeneration, GPA_PublicCounters* pPublicCounters) override;
    virtual GPA_Status GenerateHardwareCounters(GDT_HW_GENERATION desiredGeneration, GPA_HardwareCounters* pHardwareCounters) override;
    virtual GPA_Status GenerateSoftwareCounters(GDT_HW_GENERATION desiredGeneration, GPA_SoftwareCounters* pSoftwareCounters) override;
    virtual void ComputeSWCounterValue(gpa_uint32 counterIndex, gpa_uint64 value, void* pResult, GPA_HWInfo* pHwInfo) override;

    /// Get the D3D11_QUERY enum value based on our own software counter index
    /// \param index Our SW counter index
    /// \return a D3D11_QUERY enum value
    gpa_uint32 GetD3D11Enum(gpa_uint32 index);

    /// Add D3D software counters
    /// \param desiredGeneration of GDT_HW_GENERATION
    void GenerateD3DSoftwareCounters(GDT_HW_GENERATION desiredGeneration);

    /// Helper function to indicates whether the specified HW generation represents an AMD GPU
    /// \param generation the hw generation to check
    /// \return true if the specified HW generation represents an AMD GPU
    static bool IsAMDGPU(GDT_HW_GENERATION generation);

private:
    GPA_CounterGroupDesc m_d3dCounterGroup = {0, "D3D11", 0, 0, 0}; ///< description for D3D11 counter group
};

#endif //_GPA_COUNTER_GENERATOR_DX11_BASE_H_
