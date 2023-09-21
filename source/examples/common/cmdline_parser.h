//==============================================================================
// Copyright (c) 2021-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Command Line Parser header.
//==============================================================================

#ifndef GPU_PERF_API_EXAMPLES_CMDLINE_PARSER_H_
#define GPU_PERF_API_EXAMPLES_CMDLINE_PARSER_H_

#include <memory>
#include <string>
#include <map>

namespace gpa_example
{
    /// @brief Enumeration specifying the underlying type for a given argument.
    enum class ArgType
    {
        kArgTypeBool,
        kArgTypeInt,
        kArgTypeString,
    };

    /// @brief Structure which describes a given argument.
    struct ArgEntryBase
    {
        /// @brief Constructor
        ///
        /// @param [in] type The type of the argument.
        /// @param [in] doc A description of the argument.
        ArgEntryBase(const ArgType type, const std::string& doc)
            : arg_type(type)
            , doc_string(doc)
        {
        }

        /// @brief Destructor
        virtual ~ArgEntryBase() = default;

        /// @brief The type of the argument.
        ArgType arg_type;

        /// @brief A description of the argument.
        std::string doc_string;
    };

    /// @brief Specialization of ArgEntryBase for a given type T.
    template <typename T>
    struct ArgEntry : public ArgEntryBase
    {
        /// @brief Constructor
        ///
        /// @param [in] dst A reference the the location where the value of the argument will be written
        ///     to, if it is received on the command line.
        /// @param [in] type The type of the argument.
        /// @param [in] doc A description of the argument.
        ArgEntry(T& dst, const ArgType type, const std::string& doc)
            : ArgEntryBase(type, doc)
            , destination(dst)
        {
        }

        /// @brief Destructor
        ~ArgEntry() override = default;

        /// @brief A reference to the location in memory where the value of this argument will be
        ///     written to, if it is received on the command line.
        T& destination;
    };

    /// @brief Class which encapsulates command line parsing.
    class CmdlineParser
    {
    public:
        /// @brief Constructor
        ///
        /// @param argc Argc, as received by the application's main entry point.
        /// @param argv Argv, as received by the application's main entry point.
        CmdlineParser(const int argc, char** argv);

        /// @brief Inform the parser of an argument which should be parsed if detected in argv_.
        ///
        /// @param [in] name The name of the argument, inclusive of any leading '-' characters.
        /// @param [in] destination Pointer to the location in memory where the value of this argument
        ///     will be written to, if parsed as part of ParseArgs().
        /// @param [in] arg_type The type of the argument.
        /// @param [in] doc_string A description of the argument.
        void AddArg(const std::string& name, void* destination, const ArgType arg_type, const std::string& doc_string);

        /// @brief Parse the arguments in argv_.
        ///
        /// Each argument in the command line will be parsed. If a given argument matches an entry name
        /// previously provided via AddArg(), then a value will be written to that argument entry's
        /// destination pointer. If the argument is a boolean, then a value of "true" will be written.
        /// Otherwise, the next value in argv_ will be parsed according to the type provided for the
        /// given argument entry and subsequently written to the destination pointer.
        ///
        /// @return True if no errors are encountered while parsing, and False otherwise.
        bool ParseArgs();

        /// @brief Returns a string containing a summary of the documentation for all argument entries.
        ///
        /// The string contains a one-line summary of all arguments and how they are expected to be
        /// received by the application. Following this summary, an additional line providing the
        /// documentation for each argument is concatenated.
        ///
        /// @return A string summarizing how the application should be invoked with its arguments.
        std::string UsageString();

    private:
        /// @brief Argc, as received by the application's main entry point.
        const int argc_;

        /// @brief Argv, as received by the application's main entry point.
        char** argv_;

        /// @brief True if ParseArgs() has been called at least once, and false otherwise.
        bool parsed_;

        /// @brief Maps the names of arguments to corresponding metadata, as provided by AddArg().
        std::map<std::string, std::unique_ptr<ArgEntryBase>> accepted_args_;
    };

}  // namespace gpa_example

#endif  // GPU_PERF_API_EXAMPLES_CMDLINE_PARSER_H_
