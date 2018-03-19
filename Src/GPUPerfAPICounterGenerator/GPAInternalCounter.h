//==============================================================================
// Copyright (c) 2016-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  definitions for internal counters
//==============================================================================

#ifndef _GPA_INTERNAL_COUNTER_H_
#define _GPA_INTERNAL_COUNTER_H_

#include "GPUPerfAPITypes.h"
#include "GPASplitCountersInterfaces.h"

/// macro to remove counter names from public builds
#ifdef AMDT_INTERNAL
    #define GPA_HIDE_NAME(_CounterName) (_CounterName)
#else
    #define GPA_HIDE_NAME(_CounterName) ""
#endif

/// Contains all information pertaining to an hardware counter
struct GPA_HardwareCounterDesc
{
    gpa_uint64 m_counterIndexInGroup;   ///< 0-based index of counter within the group
    char* m_pName;                      ///< name of the counter
    char* m_pGroup;                     ///< group containing the counter
    char* m_pDescription;               ///< description of the counter
    GPA_Data_Type m_type;               ///< data type
    gpa_uint64 m_min;                   ///< min possible value
    gpa_uint64 m_max;                   ///< max possible value
};

/// Contains all information pertaining to an internal counter group (aka a hardware block instance).
struct GPA_CounterGroupDesc
{
    gpa_uint32 m_groupIndex;            ///< 0-based index of the group
    char* m_pName;                      ///< name of the group
    gpa_uint32 m_blockInstance;         ///< 0-based index of this block instance
    gpa_uint32 m_numCounters;           ///< number of counters in the group
    gpa_uint32 m_maxActiveCounters;     ///< number of counters that can be active in this group in a single monitor
};

const int maxSoftwareCounterNameLength = 20;                ///< maximum length for a software counter name
const int maxSoftwareCounterGroupLength = 20;               ///< maximum length for a software counter group name
const int maxSoftwareCounterDescriptionLength = 86;         ///< maximum length for a software counter description

/// Contains all information pertaining to an software counter
struct GPA_SoftwareCounterDesc
{
    gpa_uint64 m_counterIndexInGroup;                         ///< 0-based index of counter within the group
    char m_name[maxSoftwareCounterNameLength];                ///< name of the counter
    char m_group[maxSoftwareCounterGroupLength];              ///< group of the counter
    char m_description[maxSoftwareCounterDescriptionLength];  ///< description of the counter
    GPA_Data_Type m_type;                                     ///< data type
};

/// Generates a counter's UUID for hardware and software counters.
/// Public counter UUID generation uses an MD5 hash during the public compiler process.
/// \param counterName name of the counter
/// \param counterDescription description of the counter
/// \return the counter's UUID
inline GPA_UUID GetCounterUuid(const char* counterName, const char* counterDescription)
{
    GPA_UUID uuid{};
#ifdef _WIN32
    *reinterpret_cast<size_t*>(&uuid.Data1) = std::hash<std::string> {}(counterName);
    *reinterpret_cast<size_t*>(&uuid.Data4) = std::hash<std::string> {}(counterDescription);
#else
    *((size_t*)&uuid.m_data1) = std::hash<std::string> {}(counterName);
    *((size_t*)&uuid.m_data4) = std::hash<std::string> {}(counterDescription);
#endif
    return uuid;
}


#endif //_GPA_INTERNAL_COUNTER_H_
