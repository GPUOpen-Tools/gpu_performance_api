//==============================================================================
// Copyright (c) 2010-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions ASIC file for DX12_GFX8
//==============================================================================

#ifndef GPA_AUTO_GEN_COUNTER_GEN_PUBLIC_COUNTER_DEFINITIONS_DX12_GFX8_ASICS_H_
#define GPA_AUTO_GEN_COUNTER_GEN_PUBLIC_COUNTER_DEFINITIONS_DX12_GFX8_ASICS_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpu_perf_api_counter_generator/gpa_derived_counter.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx8.h"

#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx8_baffin.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx8_carrizo.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx8_ellesmere.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx8_fiji.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx8_iceland.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx8_tonga.h"

namespace dx12_gfx8_asics
{
    /// @brief Updates default GPU generation derived counters with ASIC specific derived counters if available.
    ///
    /// @param [in] desired_generation Hardware generation currently in use.
    /// @param [in] asic_type The ASIC type that is currently in use.
    /// @param [out] c Returned set of derived counters, if available.
    ///
    /// @return True if the ASIC matched one available, and c was updated.
    inline void UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c)
    {
        // Override max block events first so we could chain these if we want
        counter_dx12_gfx8::OverrideMaxBlockEvents(asic_type);

        if (dx12_gfx8_baffin::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (dx12_gfx8_carrizo::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (dx12_gfx8_ellesmere::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (dx12_gfx8_fiji::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (dx12_gfx8_iceland::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (dx12_gfx8_tonga::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

    }

}  // namespace dx12_gfx8asics

#endif  // GPA_AUTO_GEN_COUNTER_GEN_PUBLIC_COUNTER_DEFINITIONS_DX12_GFX8_ASICS_H_
