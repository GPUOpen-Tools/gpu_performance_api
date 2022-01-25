//==============================================================================
// Copyright (c) 2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Sample Application.
//==============================================================================

#include "examples/common/gpa_sample_app.h"

#include <iostream>

namespace gpa_example
{
    GpaSampleApp::GpaSampleApp(const std::string app_name, CmdlineParser& cmdline_parser)
        : app_name_(app_name)
        , cmdline_parser_(cmdline_parser)
        , number_of_frames_(0)
        , include_hw_counters_(false)
        , include_known_issues_(false)
        , verify_(false)
        , confirm_success_(false)
        , counterfile_("")
        , logfile_(app_name_ + "_gpa_log.txt")
        , datafile_(app_name_ + "_counter_data.csv")
    {
        cmdline_parser.AddArg("--numberofframes",
                              &number_of_frames_,
                              ArgType::ARG_TYPE_INT,
                              "The number of profiles to complete. Additional frames will be rendered to complete all the necessary passes required for the "
                              "enabled counters. 0 indicates to continue until the application is closed");

        cmdline_parser.AddArg(
            "--includehwcounters", &include_hw_counters_, ArgType::ARG_TYPE_BOOL, "Public hardware counters will be enabled in non-internal builds");

        cmdline_parser.AddArg(
            "--includeknownissues", &include_known_issues_, ArgType::ARG_TYPE_BOOL, "Known issues will be included in the counter validation");

        cmdline_parser.AddArg("--verify", &verify_, ArgType::ARG_TYPE_BOOL, "Application will verify a few counter values (experimental)");

        cmdline_parser.AddArg(
            "--confirmsuccess", &confirm_success_, ArgType::ARG_TYPE_BOOL, "Implies --verify and confirms successful counter values in addition to errors");

        cmdline_parser.AddArg("--counterfile", &counterfile_, ArgType::ARG_TYPE_FILEPATH, "File containing the list of counters to profile");

        cmdline_parser.AddArg(
            "--logfile",
            &logfile_,
            ArgType::ARG_TYPE_FILEPATH,
            "The full path to the file where GPA log messages will be written; defaults to '<app_name>_gpaLog.txt' in the same directory as this executable");

        cmdline_parser.AddArg("--datafile",
                              &datafile_,
                              ArgType::ARG_TYPE_FILEPATH,
                              "The full path to the file where GPA counter data will be written; defaults to '<app_name>_counterData.csv' in the same "
                              "directory as this executable");
    }

    bool GpaSampleApp::Initialize()
    {
        bool args_parsed = cmdline_parser_.ParseArgs();
        if (!args_parsed)
        {
            std::cout << cmdline_parser_.UsageString() << std::endl;
        }

        return args_parsed;
    }

    unsigned int GpaSampleApp::NumberOfFrames() const
    {
        return number_of_frames_;
    }

    bool GpaSampleApp::IncludeHwCounters() const
    {
        return include_hw_counters_;
    }

    bool GpaSampleApp::IncludeKnownIssues() const
    {
        return include_known_issues_;
    }

    bool GpaSampleApp::Verify() const
    {
        return verify_ || confirm_success_;
    }

    bool GpaSampleApp::ConfirmSuccess() const
    {
        return confirm_success_;
    }

    const std::string& GpaSampleApp::Counterfile() const
    {
        return counterfile_;
    }

    const std::string& GpaSampleApp::Logfile() const
    {
        return logfile_;
    }

    const std::string& GpaSampleApp::Datafile() const
    {
        return datafile_;
    }

}  // namespace gpa_example
