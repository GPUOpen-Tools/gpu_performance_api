//==============================================================================
// Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Helper class.
//==============================================================================

#ifndef GPU_PERF_API_EXAMPLES_OPENGL_GL_TRIANGLE_GPA_HELPER_H_
#define GPU_PERF_API_EXAMPLES_OPENGL_GL_TRIANGLE_GPA_HELPER_H_

#define DISABLE_GPA 0

#include <fstream>
#include <map>
#include <sstream>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
typedef HGLRC GlContext;  ///< Typedef for Windows GL context.
#else
#include <GL/glx.h>
typedef GLXContext GlContext;  ///< Typedef for Linux GL context.
#endif

#include "gpu_performance_api/gpu_perf_api_interface_loader.h"

/// @brief Enum for application errors.
enum AppErrors
{
    kGlError = kGpaLoggingDebugAll + 1,  ///< GL errors.
    kWinError,                           ///< Windows error.
    kXServerError,                       ///< X server error on Linux.
    kGeneralError                        ///< Any app error unrelated to GPA and platform.
};

/// @brief Logging function to register with GPA.
///
/// @param [in] log_type The type of log message being recorded.
/// @param [in] log_msg The log message.
extern void GpaLogger(GpaLoggingType log_type, const char* log_msg);

/// @brief Class that demonstrates one approach to loading GPA into an application.
///
/// It can query the addresses of all GPA entry points, and has utility functions to demonstrate
/// how to access information about the available counters, as well as how to query the profile
/// result for a given sample Id.
class GpaHelper
{
public:
    /// @brief Returns the static instance of the GPA Helper.
    ///
    /// @return Static instance of the GPA Helper.
    static GpaHelper* Instance();

    /// @brief Indicates whether or not to confirm successfully verified counters.
    ///
    /// @param confirm_success True to confirm success; false to not confirm them.
    void SetConfirmSuccess(bool confirm_success);

    /// @brief Setups the GPA.
    ///
    /// @return True upon successful operation otherwise false.
    bool SetupGpa();

    /// @brief Opens the GPA context.
    ///
    /// @param [in] gl_context GL context.
    /// @param [in] include_hw_counters Flag indicating whether or not to include hardware counters in the non-internal build.
    ///
    /// @return True upon successful operation otherwise false.
    bool OpenContext(GlContext gl_context, bool include_hw_counters);

    /// @brief Closes the context.
    ///
    /// @return True upon successful operation otherwise false.
    bool CloseContext();

    /// @brief Create the GPA session.
    ///
    /// @return True upon successful operation otherwise false.
    bool CreateGpaSession();

    /// @brief Destroys the GPA session.
    ///
    /// @return True upon successful operation otherwise false.
    bool DestroyGpaSession();

    /// @brief Enables all the counters.
    ///
    /// @return True upon successful operation otherwise false.
    bool EnableAllCounters();

    /// @brief Enables counter by name.
    ///
    /// @param [in] name The name of the counter to enable.
    ///
    /// @return True upon successful operation otherwise false.
    bool EnableCounterByName(const char* name);

    /// @brief Begins the GPA session.
    ///
    /// @return True upon successful operation otherwise false.
    bool OnGpaSessionStart();

    /// @brief Ends the GPA session.
    ///
    /// @return True upon successful operation otherwise false.
    bool OnGpaSessionEnd();

    /// @brief Starts the GPA pass.
    ///
    /// @return True upon successful operation otherwise false.
    bool OnPassStart();

    /// @brief Ends the GPA pass.
    ///
    /// @return True upon successful operation otherwise false.
    bool OnPassEnd();

    /// @brief Begins the sample.
    ///
    /// @return True upon successful operation otherwise false.
    bool BeginSample();

    /// @brief Ends the sample.
    ///
    /// @return True upon successful operation otherwise false.
    bool EndSample();

    /// @brief Enum to define type of counter validation to perform
    typedef enum
    {
        kCompareTypeEqual,                 ///< Counter value must be equal to a specified value.
        kCompareTypeGreaterThan,           ///< Counter value must be greater than a specified value.
        kCompareTypeGreaterThanOrEqualTo,  ///< Counter value must be greater than or equal to a specified value.
        kCompareTypeLessThan,              ///< Counter value must be less than a specified value.
        kCompareTypeLessThanOrEqualTo,     ///< Counter value must be less than or equal to a specified value.
    } CompareType;

    /// @brief Compare retrieved counter value to an expected value.
    ///
    /// @param [in] profile_set The index of the profile set being validated.
    /// @param [in] sample_index The sample index of the counter being compared.
    /// @param [in] counter_name The name of the counter being compared.
    /// @param [in] counter_value The retrieved counter value.
    /// @param [in] compare_type The type of compare to perform.
    /// @param [in] compare_value The expected counter value (subject to the compare type).
    ///
    /// @return True if the Counter value compares successfully, false otherwise.
    bool CounterValueCompare(unsigned int profile_set, unsigned int sample_index, const char* counter_name, GpaFloat64 counter_value, CompareType compare_type, GpaFloat64 compare_value);

    /// @brief Validate a specified counter in a specified sample.
    ///
    /// @param [in] sample_index The index of the sample containing the counter.
    /// @param [in] counter_name The name of the counter to validate.
    /// @param [in] counter_value The value of the counter to validate.
    /// @param [in] counter_usage_type The usage type of the counter being compared.
    ///
    /// @return True if the counter value validates successfully, false otherwise.
    bool ValidateData(unsigned int sample_index, const char* counter_name, GpaFloat64 counter_value, GpaUsageType counter_usage_type);

    /// @brief Populate the sample result.
    ///
    /// @param [in] profile_set The index of the profile set being validated.
    /// @param [in] verify_counters Flag indicating to verify the counters or not.
    ///
    /// @return True upon successful operation otherwise false.
    bool PrintGpaSampleResults(unsigned int profile_set, bool verify_counters = false);

    /// @brief Returns the number of passes required.
    ///
    /// @return Number of passes required.
    unsigned int GetPassRequired() const;

    /// @brief Increments the frame counter.
    void IncrementFrameCounter();

    /// @brief Returns the current frame index.
    ///
    /// @return Current frame index.
    unsigned int GetCurrentFrameCount() const;

    /// @brief Destructor.
    ~GpaHelper();

    std::fstream gpa_log_file_stream_;                         ///< Log file stream.
    std::string  gpa_log_file_name_ = "GLTriangleGpaLog.txt";  ///< Log file name.
    bool         gpa_has_error_occured_;                       ///< Flag indicating if any GPA error occurred.

private:
    /// @brief Struct for GPA counter.
    struct GPACounter
    {
        const char*  counter_name_;         ///< Counter name.
        GpaUInt32    counter_index_;        ///< Counter index.
        const char*  counter_group_;        ///< Counter group.
        const char*  counter_description_;  ///< Counter description.
        GpaDataType  counter_data_type_;    ///< Counter data type.
        GpaUsageType counter_usage_type_;   ///< Counter usage.
        GpaFloat64   counter_value_;        ///< Counter Value.

        /// @brief Constructor.
        GPACounter()
            : counter_name_(nullptr)
            , counter_index_(0u)
            , counter_group_(nullptr)
            , counter_description_(nullptr)
            , counter_data_type_()
            , counter_usage_type_()
            , counter_value_()
        {
        }

        /// @brief Less than operator overloading.
        ///
        /// @param [in] Comparer comparing value.
        ///
        /// @return True if counter value is < comparer.
        bool operator<(const float& comparer) const
        {
            return counter_value_ < comparer;
        }

        /// @brief Less that or equal to operator overloading.
        ///
        /// @param [in] Comparer comparing value.
        ///
        /// @return True if counter value is <= comparer.
        bool operator<=(const float& comparer) const
        {
            return counter_value_ <= comparer;
        }

        /// @brief Equality operator overloading.
        ///
        /// @param [in] Comparer comparing value.
        ///
        /// @return True if counter value is < comparer.
        bool operator==(const float& comparer) const
        {
            return counter_value_ == comparer;
        }

        /// @brief Greater than operator overloading.
        ///
        /// @param [in] Comparer comparing value.
        ///
        /// @return True if counter value is > comparer.
        bool operator>(const float& comparer) const
        {
            return counter_value_ > comparer;
        }

        /// @brief Greater than or equal to operator overloading.
        ///
        /// @param [in] Comparer comparing value.
        ///
        /// @return True if counter value is >= comparer.
        bool operator>=(const float& comparer) const
        {
            return counter_value_ >= comparer;
        }
    };

    /// @brief Constructor.
    GpaHelper();

    static GpaHelper*         gpa_helper_;                                   ///< GPA Helper instance.
    GpaFunctionTable*         gpa_function_table_;                           ///< GPA function table.
    std::vector<unsigned int> sample_list_;                                  ///< Sample list.
    GpaContextId              gpa_context_id_;                               ///< GPA context id.
    GpaSessionId              gpa_session_id_;                               ///< GPA session id.
    GpaCommandListId          gpa_command_list_id_;                          ///< GPA command list id.
    unsigned int              num_passes_required_;                          ///< Required pass count.
    int                       current_pass_index_;                           ///< Current pass.
    int                       sample_counter_ = -1;                          ///< Sample counter.
    std::fstream              counter_data_file_stream_;                     ///< Counter data file stream.
    std::string               counter_file_name_ = "GLTriangleCounter.csv";  ///< Counter file name.
    bool                      is_header_written_ = false;                    ///< Flag indicating status of header.
    std::stringstream         header_;                                       ///< Header stream.
    std::stringstream         content_;                                      ///< Counter data stream.
    unsigned int              frame_counter_ = 0;                            ///< Frame counter.

    /// Flag to indicate whether or not to verify some counter values and confirm successful results.
    bool confirm_success_;
};

#endif  // GPU_PERF_API_EXAMPLES_OPENGL_GL_TRIANGLE_GPA_HELPER_H_