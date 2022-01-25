//==============================================================================
// Copyright (c) 2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Sample Application header.
//==============================================================================

#ifndef GPU_PERF_API_EXAMPLES_GPA_SAMPLE_APP_H_
#define GPU_PERF_API_EXAMPLES_GPA_SAMPLE_APP_H_

#include "examples/common/cmdline_parser.h"

#include <string>

namespace gpa_example
{
    /// @brief A class implementing tasks common to GPA example applications.
    class GpaSampleApp
    {
    public:
        /// @brief Constructor
        ///
        /// @param app_name The name of the application.
        /// @param cmdline_parser The command line parser to be used by the application.
        GpaSampleApp(const std::string app_name, CmdlineParser& cmdline_parser);

        /// @brief Destructor
        virtual ~GpaSampleApp() = default;

        /// @brief Initializes the application by parsing the command line.
        ///
        /// @return true if initialization succeeds, false otherwise.
        bool Initialize();

        /// @brief The number of frames to be executed by the application.
        ///
        /// @return The number of frames if provided on the command line, 0 otherwise.
        unsigned int NumberOfFrames() const;

        /// @brief Specifies if public hardware counters will be enabled.
        ///
        /// @return true if specified on the command line, false otherwise.
        bool IncludeHwCounters() const;

        /// @brief Specifies if known issues should be included in the counter valiation.
        ///
        /// @return true if specified on the command line, false otherwise.
        bool IncludeKnownIssues() const;

        /// @brief Specifies if the application should verify counters.
        ///
        /// @return true if specified on the command line, false otherwise.
        bool Verify() const;

        /// @brief Specifies if the application should validate counter values.
        ///
        /// @return true if specified on the command line, false otherwise.
        bool ConfirmSuccess() const;

        /// @brief Specifies a file containing a list of counters to profile.
        ///
        /// @return A file path if provided on the command line, an empty string otherwise.
        const std::string& Counterfile() const;

        /// @brief Specifies a file to which GPA log messages shall be written.
        ///
        /// @return A file path if provided on the command line, a default location otherwise.
        const std::string& Logfile() const;

        /// @brief Specifies a file to which GPA counter data will be written.
        ///
        /// @return A file path if provided on the command line, a defautl location otherwise.
        const std::string& Datafile() const;

    protected:
        /// @brief The name of the application.
        const std::string app_name_;

        /// @brief The command line parser which shall be used by this application.
        CmdlineParser& cmdline_parser_;

    private:
        /// @brief The number of frames to be executed by the application.
        unsigned int number_of_frames_;

        /// @brief Specifies if public hardware counters will be enabled.
        bool include_hw_counters_;

        /// @brief Specifies if the known issues should be included in the validation.
        bool include_known_issues_;

        /// @brief Specifies if the application should verify counters.
        bool verify_;

        /// @brief Specifies if the application should validate counter values.
        bool confirm_success_;

        /// @brief A path to a file containing a list of counters to profile.
        std::string counterfile_;

        /// @brief A path to a file to which GPA log messages shall be written.
        std::string logfile_;

        /// @brief A path to a file to which GPA counter data will be written.
        std::string datafile_;
    };

}  // namespace gpa_example

#endif  // GPU_PERF_API_EXAMPLES_GPA_SAMPLE_APP_H_
