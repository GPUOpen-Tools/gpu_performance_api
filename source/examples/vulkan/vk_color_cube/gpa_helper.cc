//==============================================================================
// Copyright (c) 2019-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA API Helper class Implementation
//==============================================================================

#include "examples/vulkan/vk_color_cube/gpa_helper.h"
#include "examples/vulkan/vk_color_cube/vk_util.h"

#include <assert.h>

#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

#ifdef _WIN32
#include <codecvt>
#endif

#define REVISION_ID_ANY 0xFFFFFFFF

#ifdef _WIN32
/// @brief Converts string from wide to utf-8 encoding.
///
/// @return The converted utf-8 encoded string.
static std::string wide_to_utf8_converter(const std::wstring wide)
{
    int         num_bytes_needed = WideCharToMultiByte(CP_UTF8, 0, wide.data(), (int)wide.size(), nullptr, 0, nullptr, nullptr);
    std::string utf8;
    utf8.resize(num_bytes_needed);
    WideCharToMultiByte(CP_UTF8, 0, wide.data(), (int)wide.size(), utf8.data(), num_bytes_needed, nullptr, nullptr);
    return utf8;
}
#endif

GpaHelper::GpaHelper()
    : gpa_function_table_(nullptr)
    , is_header_written_(false)
{
}

GpaHelper::~GpaHelper()
{
    if (IsLoaded())
    {
        Unload();
    }
}

bool GpaHelper::IsLoaded() const
{
    return gpa_function_table_ != nullptr;
}

bool GpaHelper::Load()
{
    std::remove(GetGPALogFileName().c_str());

    bool success = kGpaStatusOk == GpaApiManager::Instance()->LoadApi(kGpaApiVulkan);

    if (success)
    {
        gpa_function_table_ = GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan);
    }

    return success;
}

void GpaHelper::Unload()
{
    if (IsLoaded())
    {
        GpaApiManager::Instance()->UnloadApi(kGpaApiVulkan);
        GpaApiManager::DeleteInstance();
    }

    if (gpa_log_file_stream.is_open())
    {
        gpa_log_file_stream.close();
    }

    gpa_function_table_ = nullptr;
}

void GpaHelper::PrintGPACounterInfo(GpaContextId context_id) const
{
    GpaUInt32   device_id, revision_id;
    char        device_name[255];
    const char* device_name_ptr = device_name;

    GpaStatus gpa_status = gpa_function_table_->GpaGetDeviceAndRevisionId(context_id, &device_id, &revision_id);

    if (kGpaStatusOk != gpa_status)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get device and revision id.");
        return;
    }

    gpa_status = gpa_function_table_->GpaGetDeviceName(context_id, &device_name_ptr);

    if (kGpaStatusOk != gpa_status)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get the device name.");
        return;
    }
    std::string device_name_string(device_name_ptr);

    AMDVulkanDemoVkUtils::Log("Device Id: 0x%04X", device_id);
    AMDVulkanDemoVkUtils::Log("Revision Id: %s", FormatRevisionId(revision_id).c_str());
    AMDVulkanDemoVkUtils::Log("Device Name: %s", device_name_string.c_str());

    GpaUInt32 num_counters = 0;
    gpa_status             = gpa_function_table_->GpaGetNumCounters(context_id, &num_counters);

    if (kGpaStatusOk != gpa_status)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get the number of available counters.");
        return;
    }

    for (GpaUInt32 counter_index = 0; counter_index < num_counters; counter_index++)
    {
        const char* name        = NULL;
        GpaStatus   name_status = gpa_function_table_->GpaGetCounterName(context_id, counter_index, &name);

        const char* group        = NULL;
        GpaStatus   group_status = gpa_function_table_->GpaGetCounterGroup(context_id, counter_index, &group);

        const char* description        = NULL;
        GpaStatus   description_status = gpa_function_table_->GpaGetCounterDescription(context_id, counter_index, &description);

        if (kGpaStatusOk == name_status && kGpaStatusOk == group_status && kGpaStatusOk == description_status)
        {
            AMDVulkanDemoVkUtils::Log("%d: %s \"%s\" - %s", counter_index, name, group, description);
        }
        else
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to get counter name, group, or description.");
        }
    }
}

std::string GpaHelper::GetExecutablePath()
{
#ifdef _WIN32
    wchar_t module_path[GPA_MAX_PATH];
    ::GetModuleFileNameW(NULL, module_path, _countof(module_path));

    std::wstring module_string(module_path);
    size_t       last_slash_position = module_string.find_last_of('\\');

    std::wstring executable_path = std::wstring(module_string.begin(), module_string.begin() + (last_slash_position + 1));

    std::string utf8_executable_path = wide_to_utf8_converter(executable_path);
#else
    int  len;
    char module_path[GPA_MAX_PATH];
    len = readlink("/proc/self/exe", module_path, GPA_MAX_PATH - 1);

    if (len != -1)
    {
        module_path[len] = '\0';
    }

    std::string module_string(module_path);
    size_t      last_slash_position = module_string.find_last_of('/');

    std::string executable_path(module_path);

    if (std::string::npos != last_slash_position)
    {
        executable_path = std::string(module_string.begin(), module_string.begin() + (last_slash_position + 1));
    }

    std::string utf8_executable_path;
    utf8_executable_path.append(executable_path.begin(), executable_path.end());
#endif

    return utf8_executable_path;
}

std::string GpaHelper::GetCSVFileName() const
{
#ifdef ANDROID
    // This path is dedicated to the app.
    std::string temp_string("/sdcard/Android/data/com.amd.gpa.vkcolorcube/");
    temp_string.append(csv_file_name);
    return temp_string;
#else
    return GetExecutablePath().append(csv_file_name);
#endif
}

std::string GpaHelper::GetGPALogFileName()
{
#ifdef ANDROID
    // This path is dedicated to the app.
    std::string temp_string("/sdcard/Android/data/com.amd.gpa.vkcolorcube/");
    temp_string.append(gpa_log_file_name);
    return temp_string;
#else
    return GetExecutablePath().append(gpa_log_file_name);
#endif
}

bool GpaHelper::OpenCSVFile()
{
    csv_file_.open(GetCSVFileName().c_str(), std::ios_base::out | std::ios_base::app);
    return csv_file_.is_open();
}

void GpaHelper::CloseCSVFile()
{
    csv_file_.close();
}

void GpaHelper::LogStatus(GpaStatus status, const char* msg)
{
    assert(gpa_function_table_ != nullptr);
    if (gpa_function_table_ != nullptr)
    {
        auto status_as_str = gpa_function_table_->GpaGetStatusAsStr(status);
        if (msg != nullptr)
        {
            AMDVulkanDemoVkUtils::Log("%s %s", msg, status_as_str);
        }
        else
        {
            AMDVulkanDemoVkUtils::Log("%s", status_as_str);
        }
    }
}

void GpaHelper::gpaLoggingCallback(GpaLoggingType type, const char* msg)
{
    std::string log_message;

    switch (type)
    {
    case kGpaLoggingError:
        log_message           = "GPA ERROR: ";
        gpa_any_errors_logged = true;
        gpa_num_errors_logged += 1;
        break;

    case kGpaLoggingTrace:
        log_message = "GPA TRACE: ";
        break;

    default:
        log_message = "GPA: ";
        break;
    }

    log_message.append(msg);

    if (!gpa_log_file_stream.is_open())
    {
        gpa_log_file_stream.open(GetGPALogFileName().c_str(), std::ios_base::out | std::ios_base::app);
    }

    gpa_log_file_stream << log_message << std::endl;

#ifdef ANDROID
    // Write the message to logcat
    AMDVulkanDemoVkUtils::Log("%s", log_message.c_str());
#endif
}

bool GpaHelper::CounterValueCompare(unsigned int profile_set,
                                    unsigned int sample_index,
                                    const char*  counter_name,
                                    GpaFloat64   counter_value,
                                    CompareType  compare_type,
                                    GpaFloat64   compare_value,
                                    GpaFloat64   compare_value2,
                                    bool         confirm_success)
{
    bool              return_value = false;
    std::stringstream output_string;
    std::stringstream error_string;
    std::stringstream success_string;
    std::stringstream compare_string;

    output_string << "Profile " << profile_set << ", sample " << sample_index << ": ";

    error_string << "Incorrect value for counter " << counter_name << ". Value is " << counter_value << ". Expected counter to be ";
    success_string << "Counter " << counter_name << " is correct. Value " << counter_value << " is ";

    switch (compare_type)
    {
    case kCompareTypeEqual:
        return_value = counter_value == compare_value;
        compare_string << "equal to " << compare_value;
        break;

    case kCompareTypeGreaterThan:
        return_value = counter_value > compare_value;
        compare_string << "greater than " << compare_value;
        break;

    case kCompareTypeGreaterThanOrEqualTo:
        return_value = counter_value >= compare_value;
        compare_string << "greater than or equal to " << compare_value;
        break;

    case kCompareTypeLessThan:
        return_value = counter_value < compare_value;
        compare_string << "less than " << compare_value;
        break;

    case kCompareTypeLessThanOrEqualTo:
        return_value = counter_value <= compare_value;
        compare_string << "less than or equal to " << compare_value;
        break;

    case kCompareTypeEpsilon:
    {
        // Treat compare_value2 as a +/- epsilon.
        GpaFloat64 low  = compare_value - compare_value2;
        GpaFloat64 high = compare_value + compare_value2;

        return_value = (counter_value >= low && counter_value <= high);
        compare_string << compare_value << " +/- " << compare_value2 << ".";

        if (compare_value != 0)
        {
            compare_string << " A difference of " << ((counter_value - compare_value) / compare_value) * 100.0f << "%.";
        }

        break;
    }
    case kCompareTypeRangeInclusive:
        // Treat compare_value as the low, and compare_value2 as the high.
        return_value = (counter_value >= compare_value && counter_value <= compare_value2);
        compare_string << "between " << compare_value << " and " << compare_value2 << ", inclusive.";
        break;
    }

    if (!return_value)
    {
        output_string << error_string.str() << compare_string.str();
        gpaLoggingCallback(kGpaLoggingError, output_string.str().c_str());
    }
    else if (confirm_success)
    {
        output_string << success_string.str() << compare_string.str();
        gpaLoggingCallback(kGpaLoggingMessage, output_string.str().c_str());
    }

    return return_value;
}

bool GpaHelper::ValidateData(GpaHwGeneration generation,
                             unsigned int    profile_set,
                             unsigned int    sample_index,
                             const char*     counter_name,
                             GpaFloat64      counter_value,
                             GpaUsageType    counter_usage_type,
                             bool            confirm_success)
{
    bool return_value = true;

    std::string local_counter_name(counter_name);

    if (kGpaUsageTypePercentage == counter_usage_type)
    {
        return_value =
            CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThanOrEqualTo, 0.0f, 0.0f, confirm_success) &&
            CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeLessThanOrEqualTo, 100.0f, 0.0f, confirm_success);
    }

    if (return_value)
    {
        if (0 == local_counter_name.compare("GPUTime"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("GPUBusy"))
        {
            return_value =
                CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success) &&
                CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeLessThanOrEqualTo, 100.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("VSBusy"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("VSBusyCycles"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("VSTime"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("VsGsBusy") || 0 == local_counter_name.compare("VsGsBusyCycles") ||
                 0 == local_counter_name.compare("VsGsTime"))
        {
            // Sanity check
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("VsGsVALUInstCount") || 0 == local_counter_name.compare("VsGsSALUInstCount") ||
                 0 == local_counter_name.compare("VsGsVALUBusy") || 0 == local_counter_name.compare("VsGsVALUBusyCycles") ||
                 0 == local_counter_name.compare("VsGsSALUBusy") || 0 == local_counter_name.compare("VsGsSALUBusyCycles"))
        {
            if (include_known_issues && generation == kGpaHwGenerationGfx10)
            {
                // We expect this counter to return a non-zero result, but it is returning 0 for Navi1x devices.
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
            }
            else if (generation <= kGpaHwGenerationGfx103)
            {
                // All samples should be returning non-zero results for these counters.
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
            }
            else if (include_known_issues && generation == kGpaHwGenerationGfx11)
            {
                // We expect this counter to return a non-zero result, but it is returning 0 for Gfx11.
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
            }
        }
        else if (0 == local_counter_name.compare("PreTessellationBusy") || 0 == local_counter_name.compare("PreTessellationBusyCycles") ||
                 0 == local_counter_name.compare("PreTessellationTime") || 0 == local_counter_name.compare("PreTessVALUInstCount") ||
                 0 == local_counter_name.compare("PreTessSALUInstCount") || 0 == local_counter_name.compare("PreTessVALUBusy") ||
                 0 == local_counter_name.compare("PreTessVALUBusyCycles") || 0 == local_counter_name.compare("PreTessSALUBusy") ||
                 0 == local_counter_name.compare("PreTessSALUBusyCycles"))
        {
            // Sanity check
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("PostTessellationBusy") || 0 == local_counter_name.compare("PostTessellationBusyCycles") ||
                 0 == local_counter_name.compare("PostTessellationTime") || 0 == local_counter_name.compare("PostTessVALUInstCount") ||
                 0 == local_counter_name.compare("PostTessSALUInstCount") || 0 == local_counter_name.compare("PostTessVALUBusy") ||
                 0 == local_counter_name.compare("PostTessVALUBusyCycles") || 0 == local_counter_name.compare("PostTessSALUBusy") ||
                 0 == local_counter_name.compare("PostTessSALUBusyCycles"))
        {
            // Sanity check
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("PSBusy") || 0 == local_counter_name.compare("PSBusyCycles") || 0 == local_counter_name.compare("PSTime"))
        {
            // Sanity Check
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("PSVALUInstCount") || 0 == local_counter_name.compare("PSVALUBusy") ||
                 0 == local_counter_name.compare("PSVALUBusy"))
        {
            // Sanity Check
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("PSSALUInstCount") || 0 == local_counter_name.compare("PSSALUBusy") ||
                 0 == local_counter_name.compare("PSSALUBusy"))
        {
            if (sample_index == 1)
            {
                return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, 0.0f, 0.0f, confirm_success);
            }
            else
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
            }
        }
        else if (0 == local_counter_name.compare("L0CacheHit"))
        {
            if (generation == kGpaHwGenerationGfx11)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 85.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx103)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 85.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx10)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 82.0f, confirm_success);
            }
            else
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 50.0f, confirm_success);
            }
        }
        else if (0 == local_counter_name.compare("L0CacheHitCount"))
        {
            if (generation == kGpaHwGenerationGfx11)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 6.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx103)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 35.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx10)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 28.0f, confirm_success);
            }
            else
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 15.0f, confirm_success);
            }
        }
        else if (0 == local_counter_name.compare("L0CacheRequestCount") || 0 == local_counter_name.compare("L0CacheMissCount"))
        {
            // Sanity Check
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("L1CacheRequestCount"))
        {
            // Sanity Check
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("L1CacheHit") || 0 == local_counter_name.compare("L1CacheHitCount"))
        {
            if (generation == kGpaHwGenerationGfx9)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 250.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx8 || generation == kGpaHwGenerationGfx10 || generation == kGpaHwGenerationGfx103)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 15.0f, confirm_success);
            }
            else
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 20.0f, confirm_success);
            }
        }
        else if (0 == local_counter_name.compare("L1CacheMissCount"))
        {
            if (generation == kGpaHwGenerationGfx9)
            {
                // This sample may or may not return 0. This is obvious since they UINTs, but these are valid results.
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThanOrEqualTo, 0.0f, 0.0f, confirm_success);
            }
            else
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
            }
        }
        else if (0 == local_counter_name.compare("L2CacheHit") || 0 == local_counter_name.compare("L2CacheRequestCount") ||
                 0 == local_counter_name.compare("L2CacheHitCount"))
        {
            if (sample_index == 2)
            {
                // This may equal 0 if the other caches perform well. The conditional below is a truism because a UNIT is always >= 0.
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThanOrEqualTo, 0.0f, 0.0f, confirm_success);
            }
            else
            {
                // Sanity Check
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
            }
        }
        else if (0 == local_counter_name.compare("L2CacheMiss"))
        {
            if (generation == kGpaHwGenerationGfx9)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 5.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx10)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 5.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx103)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 15.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx11)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 37.0f, confirm_success);
            }
            else
            {
                // Sanity check, assumes the L2 cache will not miss more than 50% in our test app and still be a valid result.
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 50.0f, confirm_success);
            }
        }
        else if (0 == local_counter_name.compare("L2CacheMissCount"))
        {
            if (generation == kGpaHwGenerationGfx9)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 15.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx10)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 15.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx103)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 15.0f, confirm_success);
            }
            else if (generation == kGpaHwGenerationGfx11)
            {
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeRangeInclusive, 0.0f, 60.0f, confirm_success);
            }
            else
            {
                // Sanity Check
                return_value =
                    CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, 0.0f, confirm_success);
            }
        }
        else if (include_known_issues && 0 == local_counter_name.compare("VSVerticesIn"))
        {
            // Sample 0
            GpaFloat64 expected_vertex_count = 36;

            if (sample_index == 1)
            {
                expected_vertex_count = 36;
            }
            else if (sample_index == 2)
            {
                // In this example, sample 2 vertices = sample 0 vertices + sample 1 vertices.
                expected_vertex_count = 72;
            }

            return_value =
                CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, expected_vertex_count, 0.0f, confirm_success);
        }
        else if (include_known_issues && 0 == local_counter_name.compare("PSPixelsOut"))
        {
            // Sample 0
            GpaFloat64 expected_pixel_count = 11662;

            if (sample_index == 1)
            {
                expected_pixel_count = 2820;
            }
            else if (sample_index == 2)
            {
                // In this example, sample 2 pixels = sample 0 pixels + sample 1 pixels.
                expected_pixel_count = 14482;
            }

            return_value =
                CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, expected_pixel_count, 0.0f, confirm_success);
        }
        else if (include_known_issues && 0 == local_counter_name.compare("PreZSamplesPassing"))
        {
            // Sample 0
            GpaFloat64 expected_passing = 11662;

            if (sample_index == 1)
            {
                expected_passing = 2820;
            }
            else if (sample_index == 2)
            {
                // In this example, sample 2 passing = sample 0 passing + sample 1 passing.
                expected_passing = 14482;
            }

            return_value =
                CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, expected_passing, 0.0f, confirm_success);
        }
        else if (include_known_issues && 0 == local_counter_name.compare("PrimitivesIn"))
        {
            // Sample 0
            GpaFloat64 expected_primitive_count = 12;

            if (sample_index == 1)
            {
                expected_primitive_count = 12;
            }
            else if (sample_index == 2)
            {
                // In this example, sample 2 primitives = sample 0 primitives + sample 1 primitives.
                expected_primitive_count = 24;
            }

            return_value =
                CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, expected_primitive_count, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("CSTime") || 0 == local_counter_name.compare("CSBusy") || 0 == local_counter_name.compare("CSBusyCycles") ||
                 0 == local_counter_name.compare("PAStalledOnRasterizerCycles") || 0 == local_counter_name.compare("CSThreadGroups") ||
                 0 == local_counter_name.compare("CSWavefronts") || 0 == local_counter_name.compare("CSThreads") ||
                 0 == local_counter_name.compare("CSThreadGroupSize") || 0 == local_counter_name.compare("CSVALUInsts") ||
                 0 == local_counter_name.compare("CSVALUUtilization") || 0 == local_counter_name.compare("CSSALUInsts") ||
                 0 == local_counter_name.compare("CSVFetchInsts") || 0 == local_counter_name.compare("CSSFetchInsts") ||
                 0 == local_counter_name.compare("CSVWriteInsts") || 0 == local_counter_name.compare("CSVALUBusy") ||
                 0 == local_counter_name.compare("CSVALUBusyCycles") || 0 == local_counter_name.compare("CSSALUBusy") ||
                 0 == local_counter_name.compare("CSSALUBusyCycles") || 0 == local_counter_name.compare("CSMemUnitBusy") ||
                 0 == local_counter_name.compare("CSMemUnitBusyCycles") || 0 == local_counter_name.compare("CSMemUnitStalled") ||
                 0 == local_counter_name.compare("CSMemUnitStalledCycles") || 0 == local_counter_name.compare("CSWriteUnitStalled") ||
                 0 == local_counter_name.compare("CSWriteUnitStalledCycles") || 0 == local_counter_name.compare("CSGDSInsts") ||
                 0 == local_counter_name.compare("CSLDSInsts") || 0 == local_counter_name.compare("CSALUStalledByLDS") ||
                 0 == local_counter_name.compare("CSALUStalledByLDSCycles") || 0 == local_counter_name.compare("CSLDSBankConflict") ||
                 0 == local_counter_name.compare("CSLDSBankConflictCycles"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, 0.0f, 0.0f, confirm_success);
        }
    }

    return return_value;
}

void GpaHelper::PrintGpaSampleResults(GpaContextId context_id,
                                      GpaSessionId session_id,
                                      unsigned int profile_set,
                                      GpaUInt32    sample_id,
                                      bool         output_to_console,
                                      bool         verify_counters,
                                      bool         confirm_success)
{
    GpaUInt32   device_id, revision_id;
    char        device_name[255];
    const char* device_name_ptr = device_name;

    GpaStatus gpa_status = gpa_function_table_->GpaGetDeviceAndRevisionId(context_id, &device_id, &revision_id);

    if (kGpaStatusOk != gpa_status)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get device and revision id.");
        return;
    }

    gpa_status = gpa_function_table_->GpaGetDeviceName(context_id, &device_name_ptr);

    if (kGpaStatusOk != gpa_status)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get the device name.");
        return;
    }

    GpaHwGeneration hardware_generation = kGpaHwGenerationNone;
    gpa_status                          = gpa_function_table_->GpaGetDeviceGeneration(context_id, &hardware_generation);
    if (kGpaStatusOk != gpa_status)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get the device generation.");
        return;
    }

    std::string device_name_string(device_name_ptr);

    if (output_to_console)
    {
        AMDVulkanDemoVkUtils::Log("Device Id: 0x%04X", device_id);
        AMDVulkanDemoVkUtils::Log("Revision Id: %s", FormatRevisionId(revision_id).c_str());
        AMDVulkanDemoVkUtils::Log("Device Name: %s", device_name_string.c_str());
        AMDVulkanDemoVkUtils::Log("--------------------------------------------------");
        AMDVulkanDemoVkUtils::Log("Profile %d, Sample ID: %d", profile_set, sample_id);
    }

    std::stringstream csv_header;

    csv_header << "Device Id: " << std::showbase << std::hex << device_id << std::endl;
    csv_header << "Revision Id: " << FormatRevisionId(revision_id) << std::endl;
    csv_header << "Device Name: " << device_name_string.c_str() << std::endl;

    size_t sample_result_size_in_bytes = 0;
    gpa_status                         = gpa_function_table_->GpaGetSampleResultSize(session_id, sample_id, &sample_result_size_in_bytes);

    if (kGpaStatusOk != gpa_status)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get GPA sample result size.");
        return;
    }

    GpaUInt64* results_buffer = (GpaUInt64*)malloc(sample_result_size_in_bytes);

    if (results_buffer == nullptr)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to allocate memory for GPA results.");
        return;
    }

    gpa_status = gpa_function_table_->GpaGetSampleResult(session_id, sample_id, sample_result_size_in_bytes, results_buffer);

    if (kGpaStatusOk != gpa_status)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get GPA sample results.");
    }
    else
    {
        GpaUInt32 enabled_count = 0;
        gpa_status              = gpa_function_table_->GpaGetNumEnabledCounters(session_id, &enabled_count);

        if (kGpaStatusOk != gpa_status)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to get the number of enabled counters from GPA.");
        }
        else
        {
            std::stringstream csv_content;

            csv_header << "Sample Id,";

            csv_content << sample_id << ",";

            for (GpaUInt32 i = 0; i < enabled_count; i++)
            {
                GpaUInt32 counter_index = 0;
                gpa_status              = gpa_function_table_->GpaGetEnabledIndex(session_id, i, &counter_index);

                if (kGpaStatusOk != gpa_status)
                {
                    AMDVulkanDemoVkUtils::Log("ERROR: Failed to get the exposed GPA counter id of the enabled counter at index %d.", counter_index);
                }
                else
                {
                    GpaDataType counter_type = kGpaDataTypeUint64;
                    gpa_status               = gpa_function_table_->GpaGetCounterDataType(context_id, counter_index, &counter_type);
                    assert(kGpaStatusOk == gpa_status);

                    const char* counter_name = NULL;
                    gpa_status               = gpa_function_table_->GpaGetCounterName(context_id, counter_index, &counter_name);
                    assert(kGpaStatusOk == gpa_status);

                    GpaUsageType counter_usage_type = kGpaUsageTypeLast;
                    gpa_status                      = gpa_function_table_->GpaGetCounterUsageType(context_id, counter_index, &counter_usage_type);
                    assert(kGpaStatusOk == gpa_status);

                    if (output_to_console)
                    {
                        printf("Counter %u %s result: ", counter_index, counter_name);
                    }

                    if (csv_file_.is_open() && !is_header_written_)
                    {
                        csv_header << counter_name << ",";
                    }

                    if (counter_type == kGpaDataTypeUint64)
                    {
                        if (output_to_console)
                        {
                            printf("%llu\n", results_buffer[i]);
                        }

                        if (csv_file_.is_open())
                        {
                            csv_content << results_buffer[i] << ",";
                        }

                        if (verify_counters || confirm_success)
                        {
                            ValidateData(hardware_generation,
                                         profile_set,
                                         sample_id,
                                         counter_name,
                                         static_cast<GpaFloat64>(results_buffer[i]),
                                         counter_usage_type,
                                         confirm_success);
                        }
                    }
                    else if (counter_type == kGpaDataTypeFloat64)
                    {
                        GpaFloat64 result = ((GpaFloat64*)results_buffer)[i];

                        if (output_to_console)
                        {
                            printf("%f\n", result);
                        }

                        if (csv_file_.is_open())
                        {
                            csv_content << result << ",";
                        }

                        if (verify_counters || confirm_success)
                        {
                            ValidateData(hardware_generation, profile_set, sample_id, counter_name, result, counter_usage_type, confirm_success);
                        }
                    }
                    else
                    {
                        if (output_to_console)
                        {
                            printf("unhandled type (%d).\n", counter_type);
                        }

                        if (csv_file_.is_open())
                        {
                            csv_content << "unhandled type,";
                        }
                    }
                }
            }

            // Output the counter results to the csv file.
            if (csv_file_.is_open())
            {
                if (!is_header_written_)
                {
                    csv_file_ << csv_header.str() << std::endl;
                    is_header_written_ = true;
                }

                csv_file_ << csv_content.str() << std::endl;
            }
        }
    }

    free(results_buffer);
}

std::string GpaHelper::FormatRevisionId(const GpaUInt32 revision_id) const
{
    std::stringstream revision_string;

    if (revision_id == REVISION_ID_ANY)
    {
        revision_string << "<not applicable for Vulkan>";
    }
    else
    {
        revision_string << std::showbase << std::hex << revision_id;
    }

    return revision_string.str();
}
