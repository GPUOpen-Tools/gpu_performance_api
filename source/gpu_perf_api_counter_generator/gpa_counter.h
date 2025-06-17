//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Definitions for GPA counters.
//==============================================================================

#ifndef GPA_COUNTER_GENERATOR_COMMON_GPA_COUNTER_H_
#define GPA_COUNTER_GENERATOR_COMMON_GPA_COUNTER_H_

#include <cstring>
#include <string>
#include <memory>

#include "gpu_performance_api/gpu_perf_api_types.h"
#include "gpa_split_counters_interfaces.h"

/// Macro to remove counter names from public builds.
#define GPA_HIDE_NAME(counter_name) ""

/// @brief Contains the hardware exposed counter information.
struct GpaCounterGroupExposedCounterDesc
{
    GpaUInt32              group_index;                 ///< Index of the exposed counter group.
    GpaUInt32              hardware_block_start_index;  ///< Start index of the counter in this counter group.
};

/// @brief Contains the GPA padded counter information.
struct GpaPaddedCounterDesc
{
    GpaUInt32              group_index;                 ///< Group index.
    GpaUInt32              hardware_block_start_index;  ///< Start index of the counter in this counter group.
    std::vector<GpaUInt32> padded_counter_list;         ///< List of block padded counter.
};

/// @brief Contains all information pertaining to a hardware counter.
struct GpaHardwareCounterDesc
{
    GpaUInt64   counter_index_in_group;  ///< 0-based index of counter within the group.
    const char* name;                    ///< Name of the counter.
    const char* group;                   ///< Group containing the counter.
    const char* description;             ///< Description of the counter.
    GpaDataType type;                    ///< Data type.
    GpaUInt64   min;                     ///< Min possible value.
    GpaUInt64   max;                     ///< Max possible value.
};

/// @brief Contains all information pertaining to an internal counter group (aka a hardware block instance).
struct GpaCounterGroupDesc
{
    GpaUInt32   group_index;                   ///< 0-based index of the group.
    const char* name;                          ///< Name of the group.
    GpaUInt32   block_instance;                ///< 0-based index of this block instance.
    GpaUInt32   num_counters;                  ///< Number of counters in the group.
    GpaUInt32   max_active_discrete_counters;  ///< Max number of discrete counters that can be active in this group in a single pass.
    GpaUInt32   max_active_spm_counters;       ///< Max number of SPM counters that can be active in this group in a single pass.
};

const int kMaxSoftwareCounterNameLength        = 20;  ///< Maximum length for a software counter name.
const int kMaxSoftwareCounterGroupLength       = 20;  ///< Maximum length for a software counter group name.
const int kMaxSoftwareCounterDescriptionLength = 86;  ///< Maximum length for a software counter description.

/// @brief Contains all information pertaining to a software counter
struct GpaSoftwareCounterDesc
{
    GpaUInt64   counter_index_in_group;                             ///< 0-based index of counter within the group.
    char        name[kMaxSoftwareCounterNameLength];                ///< Name of the counter.
    char        group[kMaxSoftwareCounterGroupLength];              ///< Group of the counter.
    char        description[kMaxSoftwareCounterDescriptionLength];  ///< Description of the counter.
    GpaDataType type;                                               ///< Data type.
};

/// @brief Generates a counter's UUID for hardware and software counters.
///
/// Public counter UUID generation uses an MD5 hash during the public compiler process.
///
/// @param [in] counter_name Name of the counter.
/// @param [in] counter_description Description of the counter.
///
/// @return The counter's UUID.
inline GpaUuid GetCounterUuid(const char* counter_name, const char* counter_description)
{
    GpaUuid uuid{};
#ifdef _WIN32
    *reinterpret_cast<size_t*>(&uuid.Data1) = std::hash<std::string>{}(counter_name);
    *reinterpret_cast<size_t*>(&uuid.Data4) = std::hash<std::string>{}(counter_description);
#else
    // We need 4 32-bit hash to generate UUID.
    {
        size_t hash = std::hash<std::string>{}(counter_name);
        memset(&uuid.data_1, 0, sizeof(uuid.data_1));
        memcpy(&uuid.data_1, &hash, sizeof(uint32_t));
    }

    {
        std::string temp_string = counter_name;
        temp_string.append(counter_description);
        size_t hash = std::hash<std::string>{}(temp_string);
        // Assign data_2 and data_3.
        memcpy(&uuid.data_2, &hash, sizeof(uint32_t));
    }

    {
        std::string temp_string = counter_description;
        temp_string.append(counter_name);
        size_t hash = std::hash<std::string>{}(temp_string);
        // Assign 4 byte data to first 4 byte of data_4.
        memcpy(&uuid.data_4, &hash, sizeof(uint32_t));
    }

    {
        size_t hash = std::hash<std::string>{}(counter_description);
        // Assign 4 byte data to last 4 byte of data_4.
        memcpy(&uuid.data_4[4], &hash, sizeof(uint32_t));
    }

#endif
    return uuid;
}

/// Forward declaration.
class BlockMap;

/// @brief Builds ASIC block map for updating max discrete and SPM events.
///
/// @param [in] counter_group_list List of counters.
/// @param [in] max_count Count of items in list.
///
/// @return shared pointer to BlockMap.
std::shared_ptr<BlockMap> BuildBlockMap(std::vector<GpaCounterGroupDesc>& counter_group_list, uint32_t max_count);

/// @brief Update max discrete events for a block.
///
/// @param [in] block_map The block map.
/// @param [in] block_name Name of the block to update.
/// @param [in] max_discrete_events New maximum discrete events value.
void UpdateMaxDiscreteBlockEvents(BlockMap* block_map, const char* block_name, uint32_t max_discrete_events);

/// @brief Update max SPM events for a block.
///
/// @param [in] block_map The block map.
/// @param [in] block_name Name of the block to update.
/// @param [in] max_spm_events New maximum SPM events value.
void UpdateMaxSpmBlockEvents(BlockMap* block_map, const char* block_name, uint32_t max_spm_events);

#endif  // GPA_COUNTER_GENERATOR_COMMON_GPA_COUNTER_H_
