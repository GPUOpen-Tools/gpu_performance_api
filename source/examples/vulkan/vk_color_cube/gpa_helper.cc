//==============================================================================
// Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA API Helper class Implementation
//==============================================================================

#include "examples/vulkan/vk_color_cube/gpa_helper.h"

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
        std::cout << "ERROR: Failed to get device and revision id.\n";
        return;
    }

    gpa_status = gpa_function_table_->GpaGetDeviceName(context_id, &device_name_ptr);

    if (kGpaStatusOk != gpa_status)
    {
        std::cout << "ERROR: Failed to get the device name.\n";
        return;
    }
    std::string device_name_string(device_name_ptr);

    std::cout << "Device Id: " << std::showbase << std::hex << device_id << std::endl;
    std::cout << "Revision Id: " << FormatRevisionId(revision_id) << std::endl;
    std::cout << "Device Name: " << device_name_string.c_str() << std::endl;

    GpaUInt32 num_counters = 0;
    gpa_status             = gpa_function_table_->GpaGetNumCounters(context_id, &num_counters);

    if (kGpaStatusOk != gpa_status)
    {
        std::cout << "ERROR: Failed to get the number of available counters." << std::endl;
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
            std::cout << counter_index << ": " << name << " \"" << group << "\" - " << description << std::endl;
        }
        else
        {
            std::cout << "ERROR: Failed to get counter name, group, or description." << std::endl;
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

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wide_to_utf8_converter;

    std::string utf8_executable_path = wide_to_utf8_converter.to_bytes(executable_path);
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
    temp_string.append(csv_file_name_);
    return temp_string;
#else
    return GetExecutablePath().append(csv_file_name_);
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
}

bool GpaHelper::CounterValueCompare(unsigned int profile_set,
                                    unsigned int sample_index,
                                    const char*  counter_name,
                                    GpaFloat64   counter_value,
                                    CompareType  compare_type,
                                    GpaFloat64   compare_value,
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

bool GpaHelper::ValidateData(unsigned int profile_set,
                             unsigned int sample_index,
                             const char*  counter_name,
                             GpaFloat64   counter_value,
                             GpaUsageType counter_usage_type,
                             bool         confirm_success)
{
    bool return_value = true;

    std::string local_counter_name(counter_name);

    if (kGpaUsageTypePercentage == counter_usage_type)
    {
        return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThanOrEqualTo, 0.0f, confirm_success) &&
                       CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeLessThanOrEqualTo, 100.0f, confirm_success);
    }

    if (return_value)
    {
        if (0 == local_counter_name.compare("GPUTime"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("GPUBusy"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, confirm_success) &&
                           CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeLessThanOrEqualTo, 100.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("VSBusy"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("VSBusyCycles"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("VSTime"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("PSBusy"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("PSBusyCycles"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, confirm_success);
        }
        else if (0 == local_counter_name.compare("PSTime"))
        {
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeGreaterThan, 0.0f, confirm_success);
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

            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, expected_vertex_count, confirm_success);
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

            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, expected_pixel_count, confirm_success);
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

            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, expected_passing, confirm_success);
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

            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, expected_primitive_count, confirm_success);
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
            return_value = CounterValueCompare(profile_set, sample_index, counter_name, counter_value, kCompareTypeEqual, 0.0f, confirm_success);
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
        std::cout << "ERROR: Failed to get device and revision id.\n";
        return;
    }

    gpa_status = gpa_function_table_->GpaGetDeviceName(context_id, &device_name_ptr);

    if (kGpaStatusOk != gpa_status)
    {
        std::cout << "ERROR: Failed to get the device name.\n";
        return;
    }

    std::string device_name_string(device_name_ptr);

    if (output_to_console)
    {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Device Id: " << std::showbase << std::hex << device_id << std::endl;
        std::cout << "Revision Id: " << FormatRevisionId(revision_id) << std::endl;
        std::cout << "Device Name: " << device_name_string.c_str() << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Profile " << profile_set << ", Sample ID: " << sample_id << std::endl;
    }

    std::stringstream csv_header;

    csv_header << "Device Id: " << std::showbase << std::hex << device_id << std::endl;
    csv_header << "Revision Id: " << FormatRevisionId(revision_id) << std::endl;
    csv_header << "Device Name: " << device_name_string.c_str() << std::endl;

    size_t sample_result_size_in_bytes = 0;
    gpa_status                         = gpa_function_table_->GpaGetSampleResultSize(session_id, sample_id, &sample_result_size_in_bytes);

    if (kGpaStatusOk != gpa_status)
    {
        std::cout << "ERROR: Failed to get GPA sample result size." << std::endl;
        return;
    }

    GpaUInt64* results_buffer = (GpaUInt64*)malloc(sample_result_size_in_bytes);

    if (results_buffer == nullptr)
    {
        std::cout << "ERROR: Failed to allocate memory for GPA results." << std::endl;
        return;
    }

    gpa_status = gpa_function_table_->GpaGetSampleResult(session_id, sample_id, sample_result_size_in_bytes, results_buffer);

    if (kGpaStatusOk != gpa_status)
    {
        std::cout << "ERROR: Failed to get GPA sample results." << std::endl;
    }
    else
    {
        GpaUInt32 enabled_count = 0;
        gpa_status              = gpa_function_table_->GpaGetNumEnabledCounters(session_id, &enabled_count);

        if (kGpaStatusOk != gpa_status)
        {
            std::cout << "ERROR: Failed to get the number of enabled counters from GPA." << std::endl;
        }
        else
        {
            std::stringstream csv_content;

            for (GpaUInt32 i = 0; i < enabled_count; i++)
            {
                GpaUInt32 counter_index = 0;
                gpa_status              = gpa_function_table_->GpaGetEnabledIndex(session_id, i, &counter_index);

                if (kGpaStatusOk != gpa_status)
                {
                    std::cout << "ERROR: Failed to get the exposed GPA counter id of the enabled counter at index " << counter_index << "." << std::endl;
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
                            ValidateData(profile_set, sample_id, counter_name, static_cast<GpaFloat64>(results_buffer[i]), counter_usage_type, confirm_success);
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
                            ValidateData(profile_set, sample_id, counter_name, result, counter_usage_type, confirm_success);
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
