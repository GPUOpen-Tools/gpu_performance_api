//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for DX12 counter generation
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_DX12_H_
#define _GPA_COUNTER_GENERATOR_DX12_H_

#include "GPACounterGeneratorBase.h"

/// The DX12-specific counter generator
class GPA_CounterGeneratorDX12 : public GPA_CounterGeneratorBase
{
public:
    /// Get the SW counter description for the given SW counter index
    /// \return The SW counter description
    /// \param[in] swCounterIndex The SW counter index
    /// \param[out] swCounterDesc Software counter description
    static bool GetSwCounterDesc(
        const gpa_uint32 swCounterIndex, GPA_SoftwareCounterDesc& swCounterDesc);

    /// Construct a GPA DX12 counter generator
    GPA_CounterGeneratorDX12();

    /// Destroy this GPA DX12 counter generator
    virtual ~GPA_CounterGeneratorDX12();

protected:
    virtual GPA_Status GeneratePublicCounters(
        GDT_HW_GENERATION desiredGeneration, GPA_PublicCounters* pPublicCounters);

    virtual GPA_Status GenerateHardwareCounters(
        GDT_HW_GENERATION desiredGeneration, GPA_HardwareCounters* pHardwareCounters);

    virtual GPA_Status GenerateSoftwareCounters(
        GDT_HW_GENERATION desiredGeneration, GPA_SoftwareCounters* pSoftwareCounters);

    virtual void ComputeSWCounterValue(
        gpa_uint32 counterIndex, gpa_uint64 value, void* pResult, GPA_HWInfo* pHwInfo);

private:
    static const GPA_SoftwareCounterDesc s_dx12SWCounters[]; ///< DX12 SW counters list
    static const size_t s_dx12SWCountersCount; ///< DX12 SW counter list size

    /// Copy constructor - private override to prevent usage
    GPA_CounterGeneratorDX12(const GPA_CounterGeneratorDX12&) = delete;

    /// Move constructor - private override to prevent usage
    GPA_CounterGeneratorDX12(GPA_CounterGeneratorDX12&&) = delete;

    /// Copy operator - private override to prevent usage
    GPA_CounterGeneratorDX12& operator=(const GPA_CounterGeneratorDX12&) = delete;

    /// Mpve operator - private override to prevent usage
    GPA_CounterGeneratorDX12& operator=(GPA_CounterGeneratorDX12&&) = delete;

    /// Generate DX12 API software counters
    /// \return GPA_STATUS_OK if generating counters succeeded, false if it failed
    GPA_Status GenerateDX12SoftwareCounters();

}; // end of class GPA_CounterGeneratorDX12

#endif // _GPA_COUNTER_GENERATOR_DX12_H_

