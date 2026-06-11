//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief CPU-only tests verifying the GL driver group matching logic for GFX11.5.
//==============================================================================

#include <gtest/gtest.h>

#include "gpa_hw_support.h"
#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "gpa_array_view.hpp"
#include <initializer_list>
#include <string>
#include <string_view>
#include <vector>

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx115.h"

namespace
{
    // Simulated entry from the GL_AMD_performance_monitor extension, mirroring
    // GlGpaContext::GpaGlPerfMonitorGroupData but without the GLuint/GLint types.
    struct SimulatedDriverGroup
    {
        const char*  name;
        unsigned int num_instances;
    };

    // The canonical GFX11.5 APU driver group list as observed on a Radeon 8060S.
    // Groups marked [skip] are exposed by the driver but absent from GPA's gfx115 OGLP table.
    // Groups marked [→ X] are translated to X before matching.
    const SimulatedDriverGroup kGfx115DriverGroups[] = {
        {"CPF", 1},    {"PA", 2},  // → PA_SU
        {"SC", 8},                 // → PA_SC
        {"SPI", 2},    {"SQ", 2},  // → SQG  (GFX11+)
        {"SQ_ES", 2},              // [skip GFX11+]
        {"SQ_GS", 2},              // → SQG_GS (GFX11+)
        {"SQ_VS", 2},              // [skip GFX11+]
        {"SQ_PS", 2},              // → SQG_PS (GFX11+)
        {"SQ_LS", 2},              // [skip GFX11+]
        {"SQ_HS", 2},              // → SQG_HS (GFX11+)
        {"SQ_CS", 2},              // → SQG_CS (GFX11+)
        {"SX", 4},     {"TA", 40},       {"TD", 40},       {"TCP", 40},      {"DB", 8},        {"CB", 8},  {"GDS", 1}, {"GRBM", 1}, {"GRBM_SE", 2},  // → GRBMSE
        {"RLC", 1},    {"DMA", 1},                                                           // [skip: no SDMA entry in gfx115 OGLP table]
        {"CPG", 1},    {"CPC", 1},       {"ATC", 1},       {"ATCL2", 1},     {"MCVML2", 1},  // → GCVML2 (GFX11/GFX115)
        {"EA", 8},                                                                           // → GCEA
        {"RPB", 1},                                                                          // [skip: no RPB entry in gfx115 OGLP table]
        {"RMI", 16},   {"UMCCH", 8},                                                         // [skip: no UMC entry in gfx115 OGLP table]
        {"GE", 1},                                                                           // [skip: no GE entry in gfx115 OGLP table]
        {"GL1A", 4},   {"GL1C", 16},     {"GL2A", 4},      {"GL2C", 8},      {"CHA", 1},       {"CHC", 4}, {"GCR", 1}, {"PH", 1},  // → PA_PH
        {"UTCL1", 4},  {"GE_DIST", 1},                                                                                             // → GE2_DIST
        {"GE_SE", 2},  // → GE2_SE (GFX12+, but GFX115 > GFX12 in enum)
        {"SQWGP", 20}, {"SQWGP_GS", 20}, {"SQWGP_PS", 20}, {"SQWGP_HS", 20}, {"SQWGP_CS", 20}, {"PC", 2},
    };

    // Returns the GPA group name (base, without instance suffix) that the driver group name
    // should map to, applying the same translation rules as ValidateAndUpdateGlCounters().
    // Returns empty string if this driver group should be skipped entirely.
    std::string TranslateDriverGroupName(const std::string& driver_name, device_info::HwGeneration generation)
    {
        // GPA does not yet support DF_MALL.
        if (driver_name.find("DF_MALL") == 0)
        {
            return "";
        }

        // On GFX11.5 APUs the driver exposes groups that GPA has no corresponding entries for.
        if (generation == device_info::HwGeneration::kGfx11_5 &&
            (driver_name == "DMA" || driver_name == "RPB" || driver_name == "UMCCH" || driver_name == "GE"))
        {
            return "";
        }

        // On GFX11 and newer (including GFX11.5), SQ_ES, SQ_VS, and SQ_LS are exposed but not supported.
        // This skip is intentionally not gated on the exact generation — it applies to all GFX11+ generations.
        if (driver_name.find("SQ_ES") == 0 || driver_name.find("SQ_VS") == 0 || driver_name.find("SQ_LS") == 0)
        {
            return "";
        }

        if (driver_name == "PA")
            return "PA_SU";
        if (driver_name == "SC")
            return "PA_SC";
        if (driver_name == "GRBM_SE")
            return "GRBMSE";
        if (driver_name == "DMA")
            return "SDMA";
        if (driver_name == "EA")
            return "GCEA";
        if (driver_name == "PH")
            return "PA_PH";
        if (driver_name == "GE_DIST")
            return "GE2_DIST";

        // GFX11.5 enum value (15) is greater than GFX12 (13), so this condition fires for both.
        if (generation >= device_info::HwGeneration::kGfx12 && driver_name == "GE_SE")
            return "GE2_SE";

        // GFX11+ SQ renames
        if (generation >= device_info::HwGeneration::kGfx11)
        {
            if (driver_name == "SQ")
                return "SQG";
            if (driver_name == "SQ_GS")
                return "SQG_GS";
            if (driver_name == "SQ_PS")
                return "SQG_PS";
            if (driver_name == "SQ_HS")
                return "SQG_HS";
            if (driver_name == "SQ_CS")
                return "SQG_CS";
        }

        // GFX11 and GFX11.5 expose MCVML2, GPA uses GCVML2.
        if ((generation == device_info::HwGeneration::kGfx11 || generation == device_info::HwGeneration::kGfx11_5) && driver_name == "MCVML2")
        {
            return "GCVML2";
        }

        return driver_name;
    }

    // Simulate the matching loop from ValidateAndUpdateGlCounters() using the simulated driver list.
    // Returns a list of GPA group names that could not be matched.
    //
    // gpa_skip_prefixes: name prefixes of GPA groups to skip (equivalent to driver_supports_X_ == false
    // in the production code). For the typical test where all optional blocks are present, pass {}.
    std::vector<std::string> RunMatchingLoop(const gpa_array_view<GpaCounterGroupDesc>& gpa_groups,
                                             const SimulatedDriverGroup*                driver_groups,
                                             size_t                                     driver_group_count,
                                             device_info::HwGeneration                  generation,
                                             std::initializer_list<std::string_view>    gpa_skip_prefixes = {})
    {
        std::vector<std::string> unmatched_gpa_groups;

        size_t driver_idx   = 0;
        bool   is_first_gpa = true;

        for (size_t gpa_idx = 0; gpa_idx < gpa_groups.size(); ++gpa_idx)
        {
            const GpaCounterGroupDesc& gpa_group      = gpa_groups[gpa_idx];
            const std::string          gpa_group_name = gpa_group.name;

            // Software-only groups (GPUTime, GPUTimeStamp, GPIN) are not exposed by the driver.
            // They are typically at the end of the GPA list; when the driver list is exhausted, stop.
            if (driver_idx >= driver_group_count)
            {
                break;
            }

            // Skip GPA groups for optional blocks not present on this hardware
            // (equivalent to the driver_supports_X_ == false guards in ValidateAndUpdateGlCounters).
            bool should_skip_gpa = false;
            for (const std::string_view prefix : gpa_skip_prefixes)
            {
                if (gpa_group_name.compare(0, prefix.size(), prefix) == 0)
                {
                    should_skip_gpa = true;
                    break;
                }
            }
            if (should_skip_gpa)
            {
                continue;
            }

            // Advance driver iterator for new blocks (block_instance == 0), except on the very first GPA group.
            if (!is_first_gpa && gpa_group.block_instance == 0)
            {
                // Find the next non-skipped driver group.
                ++driver_idx;
                while (driver_idx < driver_group_count && TranslateDriverGroupName(driver_groups[driver_idx].name, generation).empty())
                {
                    ++driver_idx;
                }

                if (driver_idx >= driver_group_count)
                {
                    break;
                }
            }
            is_first_gpa = false;

            // Build the extended driver group name (with instance suffix when num_instances > 1).
            std::string driver_name_extended = TranslateDriverGroupName(driver_groups[driver_idx].name, generation);

            if (driver_groups[driver_idx].num_instances > 1)
            {
                driver_name_extended += std::to_string(gpa_group.block_instance);
            }

            // Match: exact or GPA name starts with driver name (the second handles the "ATC"/"ATCL2" ambiguity that the source code notes as a BUG).
            if (gpa_group_name != driver_name_extended && gpa_group_name.find(driver_name_extended) != 0)
            {
                unmatched_gpa_groups.push_back(gpa_group_name + " (expected driver: " + driver_name_extended +
                                               ", actual driver: " + driver_groups[driver_idx].name + ")");
            }
        }

        return unmatched_gpa_groups;
    }
}  // namespace

// This test simulates ValidateAndUpdateGlCounters() without a GPU by:
//   1. Hard-coding the known GFX11.5 APU driver group list (from on-device testing).
//   2. Replicating the translation and skip rules from gl_gpa_context.cc.
//   3. Asserting that every GPA group has a matching driver group.
TEST(GlGroupMatching, Gfx115AllGroupsMatch)
{
    const gpa_array_view<GpaCounterGroupDesc> gpa_groups = counter_oglp_gfx115::kHwOglpGroupsGfx115;

    const std::vector<std::string> unmatched =
        RunMatchingLoop(gpa_groups, kGfx115DriverGroups, std::size(kGfx115DriverGroups), device_info::HwGeneration::kGfx11_5);

    for (const std::string& mismatch : unmatched)
    {
        ADD_FAILURE() << "Unmatched GPA group: " << mismatch;
    }
}

// When adding support for a new hardware generation or fixing a driver name mismatch,
// add or update a corresponding test here so future regressions are caught without
// needing a GPU or on-device test run.
// When a new generation is added to kSupportedGenerations, add a corresponding
// driver group list and RunMatchingLoop call above before updating this count.
static_assert(kSupportedGenerations.size() == 5, "New generation added — add a GL group matching test for it.");
