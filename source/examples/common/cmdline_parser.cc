//==============================================================================
// Copyright (c) 2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Command Line Parser.
//==============================================================================

#include "examples/common/cmdline_parser.h"

#include "gpu_perf_api_common/logging.h"
#include <utility>

namespace
{
    template <typename T>
    gpa_example::ArgEntry<T>* MakeArgEntry(void* p_destination, const gpa_example::ArgType arg_type, const std::string& doc_string)
    {
        T& destination = *(reinterpret_cast<T*>(p_destination));
        return new gpa_example::ArgEntry<T>(destination, arg_type, doc_string);
    }

    template <typename T>
    void SetDestinationVal(std::unique_ptr<gpa_example::ArgEntryBase>& base_entry, T value)
    {
        gpa_example::ArgEntry<T>* entry = reinterpret_cast<gpa_example::ArgEntry<T>*>(base_entry.get());
        entry->destination              = value;
    }

    template <typename T>
    T ParseArgument(bool& success, char** argv, const int i)
    {
        T parsed_value;

        std::istringstream iss(*(argv + i));
        iss >> parsed_value;

        success = !(iss.fail());

        return parsed_value;
    }
}  // namespace

namespace gpa_example
{
    CmdlineParser::CmdlineParser(const int argc, char** argv)
        : argc_(argc)
        , argv_(argv)
        , parsed_(false)
    {
    }

    void CmdlineParser::AddArg(const std::string& name, void* p_destination, const ArgType arg_type, const std::string& doc_string)
    {
        std::string message;

        if (accepted_args_.find(name) != accepted_args_.end())
        {
            message = "WARNING: The following argument has already been passed to CmdlineParser::AddArg() and will not be added again: ";
            message += name;
            message += ".";
            GPA_LOG_MESSAGE(message.c_str());
            return;
        }

        ArgEntryBase* p_entry = nullptr;

        switch (arg_type)
        {
        case ArgType::ARG_TYPE_BOOL:
            p_entry = MakeArgEntry<bool>(p_destination, arg_type, doc_string);
            break;
        case ArgType::ARG_TYPE_INT:
            p_entry = MakeArgEntry<int>(p_destination, arg_type, doc_string);
            break;
        case ArgType::ARG_TYPE_FILEPATH:
            p_entry = MakeArgEntry<std::string>(p_destination, arg_type, doc_string);
            break;
        default:
            message = "Unknown ArgType provided for ";
            message += name;
            message += ".";
            GPA_LOG_ERROR(message.c_str());
        }

        if (p_entry == nullptr)
        {
            message = "Failed to allocate storage for the following argument: ";
            message += name;
            message += ".";
            GPA_LOG_ERROR(message.c_str());
        }
        else
        {
            accepted_args_.emplace(std::make_pair(name, std::unique_ptr<ArgEntryBase>(p_entry)));
        }
    }

    bool CmdlineParser::ParseArgs()
    {
        if (parsed_)
        {
            GPA_LOG_MESSAGE("WARNING: Parsing command line more than once.");
        }

        for (int i = 1; i < argc_; ++i)
        {
            bool        parse_success = true;
            std::string message;

            auto entry = accepted_args_.find(*(argv_ + i));
            if (entry == accepted_args_.end())
            {
                return false;
            }

            if (entry->second->arg_type != ArgType::ARG_TYPE_BOOL)
            {
                ++i;
                if (i >= argc_)
                {
                    return false;
                }
            }

            switch (entry->second->arg_type)
            {
            case ArgType::ARG_TYPE_BOOL:
                SetDestinationVal<bool>(entry->second, true);
                break;
            case ArgType::ARG_TYPE_INT:
                SetDestinationVal<int>(entry->second, ParseArgument<int>(parse_success, argv_, i));
                break;
            case ArgType::ARG_TYPE_FILEPATH:
                SetDestinationVal<std::string>(entry->second, ParseArgument<std::string>(parse_success, argv_, i));
                break;
            default:
                message = "Unknown ArgType retrieved for ";
                message += entry->first;
                message += ".";
                GPA_LOG_ERROR(message.c_str());
                parse_success = false;
            }

            if (!parse_success)
            {
                return false;
            }
        }

        parsed_ = true;

        return true;
    }

    std::string CmdlineParser::UsageString()
    {
        std::stringstream summary_message;
        std::stringstream detailed_message;

        // argv_[0] contains the image name
        summary_message << *(argv_);

        for (const auto& entry : accepted_args_)
        {
            summary_message << " [" << entry.first;
            detailed_message << entry.first;

            if (entry.second->arg_type == ArgType::ARG_TYPE_INT)
            {
                summary_message << " #";
                detailed_message << " #";
            }
            else if (entry.second->arg_type == ArgType::ARG_TYPE_FILEPATH)
            {
                summary_message << " <file>";
                detailed_message << " <file>";
            }

            summary_message << "]";
            detailed_message << ": " << entry.second->doc_string << std::endl;
        }

        summary_message << std::endl;

        return summary_message.str() + detailed_message.str();
    }

}  // namespace gpa_example
