//==============================================================================
// Copyright (c) 2019-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA API Helper class.
//==============================================================================

#ifndef GPU_PERF_API_EXAMPLES_VULKAN_VK_COLOR_CUBE_GPA_HELPER_H_
#define GPU_PERF_API_EXAMPLES_VULKAN_VK_COLOR_CUBE_GPA_HELPER_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "gpu_performance_api/gpu_perf_api_interface_loader.h"

/// @brief Class that demonstrates one approach to loading GPA into an application.
///
/// It can query the addresses of all GPA entry points, and has utility functions to demonstrate
/// how to access information about the available counters, as well as how to query the profile
/// result for a given sample Id.
class GpaHelper
{
public:
    /// @brief Constructor.
    GpaHelper();

    /// @brief Destructor.
    ~GpaHelper();

    /// @brief Indicates whether or not the GPA library is loaded.
    bool IsLoaded() const;

    /// @brief Loads the necessary GPA library.
    ///
    /// @return True if the library loaded successfully; false otherwise.
    bool Load();

    /// @brief Unloads the GPA library.
    void Unload();

    /// @brief Print the available counters from the specified context.
    ///
    /// @param [in] context_id A valid GPA Context ID.
    void PrintGPACounterInfo(GpaContextId context_id) const;

    /// @brief Gets the path of the running executable
    ///
    /// @return The path of the running executable
    static std::string GetExecutablePath();

    /// @brief Gets the name of the CSV file in which to output profile results.
    ///
    /// @return The name of the CSV file in which to output profile results.
    std::string GetCSVFileName() const;

    /// @brief Gets the name of the GPA log file.
    ///
    /// @return The name of the GPA log file
    static std::string GetGPALogFileName();

    /// @brief Opens the CSV file to output profile results.
    ///
    /// @return True if the csv file was successfully opened; false otherwise.
    bool OpenCSVFile();

    /// @brief Closes the CSV File so that it gets saved to disk.
    void CloseCSVFile();

    /// @brief Callback function for any error messages that GPA produces.
    ///
    /// @param [in] type The type of logging message.
    /// @param [in] msg The message.
    static void gpaLoggingCallback(GpaLoggingType type, const char* msg);

    /// @brief Output a log message and GpaStatus.
    ///
    /// @param [in] status The GpaStatus to output.
    /// @param [in] msg Optional, the message to log alongside the status.
    void LogStatus(GpaStatus status, const char* msg = nullptr);

    /// @brief Enum to define type of counter validation to perform
    typedef enum
    {
        kCompareTypeEqual,                 ///< Counter value must be equal to a specified value.
        kCompareTypeGreaterThan,           ///< Counter value must be greater than a specified value.
        kCompareTypeGreaterThanOrEqualTo,  ///< Counter value must be greater than or equal to a specified value.
        kCompareTypeLessThan,              ///< Counter value must be less than a specified value.
        kCompareTypeLessThanOrEqualTo,     ///< Counter value must be less than or equal to a specified value.
        kCompareTypeEpsilon,               ///< Counter value must be within range of the specified value +/- the epsilon value, inclusive.
        kCompareTypeRangeInclusive,        ///< Counter value must be within the range of the specified values, inclusive.
    } CompareType;

    /// @brief Compare retrieved counter value to an expected value.
    ///
    /// @param [in] profile_set The index of the profile set being validated.
    /// @param [in] sample_index The sample index of the counter being compared.
    /// @param [in] counter_name The name of the counter being compared.
    /// @param [in] counter_value The retrieved counter value.
    /// @param [in] compare_type The type of compare to perform.
    /// @param [in] compare_value The expected counter value (subject to the compare type).
    /// @param [in] compare_value2 A secondary value that may be used depending on the CompareType that is supplied.
    /// @param [in] confirm_success Flag indicating whether or not to confirm successful counter verifications.
    ///
    /// @return True if the Counter value compares successfully, false otherwise.
    bool CounterValueCompare(unsigned int profile_set,
                             unsigned int sample_index,
                             const char*  counter_name,
                             GpaFloat64   counter_value,
                             CompareType  compare_type,
                             GpaFloat64   compare_value,
                             GpaFloat64   compare_value2,
                             bool         confirm_success);

    /// @brief Validate a specified counter in a specified sample.
    ///
    /// @param [in] generation The hardware generation to validate for.
    /// @param [in] profile_set The index of the profile set being validated.
    /// @param [in] sample_index The index of the sample containing the counter.
    /// @param [in] counter_name The name of the counter to validate.
    /// @param [in] counter_value The value of the counter to validate.
    /// @param [in] counter_usage_type The usage type of the counter being compared.
    /// @param [in] confirm_success Flag indicating whether or not to confirm successful counter verifications.
    ///
    /// @return True if the counter value validates successfully, false otherwise.
    bool ValidateData(GpaHwGeneration generation, unsigned int profile_set, unsigned int sample_index, const char* counter_name, GpaFloat64 counter_value, GpaUsageType counter_usage_type, bool confirm_success);

    /// @brief Print counter results from a specific sample. If the CSV file is open, results will be written there too.
    ///
    /// @param [in] context_id A valid Context ID.
    /// @param [in] session_id A valid Session ID.
    /// @param [in] profile_set The index of the profile set being validated.
    /// @param [in] sample_id A valid Sample ID.
    /// @param [in] output_to_console Flag indicating to show on console or not.
    /// @param [in] verify_counters Flag indicating to verify the counters or not.
    /// @param [in] confirm_success Flag indicating whether or not to confirm successful counter verifications.
    void PrintGpaSampleResults(GpaContextId context_id, GpaSessionId session_id, unsigned int profile_set, GpaUInt32 sample_id, bool output_to_console, bool verify_counters, bool confirm_success);

    /// GPA function table pointer.
    GpaFunctionTable* gpa_function_table_;

    /// The name of the csv file that will be written.
    static std::string csv_file_name;

    /// The name of the GPA Log file that will be written.
    static std::string gpa_log_file_name;

    /// GPA log file stream.
    static std::fstream gpa_log_file_stream;

    /// Flag indicating if any errors were output via GPA's logging mechanism.
    static bool gpa_any_errors_logged;

    /// Indicates the number of errors that have been logged by GPA.
    static int gpa_num_errors_logged;

    /// Indicates that known issues should be included in the counter validation.
    static bool include_known_issues;

private:
    /// @brief Format the revision ID as a user-friendly string.
    ///
    /// @param [in] revision_id The revision ID to format.
    ///
    /// @return The formatted revision ID.
    std::string FormatRevisionId(const GpaUInt32 revision_id) const;

    /// The file stream for writing the csv file.
    std::fstream csv_file_;

    /// Flag to indicate if the header has been written in the csv file.
    bool is_header_written_;
};

#endif  // GPU_PERF_API_EXAMPLES_VULKAN_VK_COLOR_CUBE_GPA_HELPER_H_
