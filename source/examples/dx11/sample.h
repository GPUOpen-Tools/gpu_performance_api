//==============================================================================
// Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Sample implementation.
//==============================================================================

#ifndef GPU_PERF_API_EXAMPLES_DX11_SAMPLE_H_
#define GPU_PERF_API_EXAMPLES_DX11_SAMPLE_H_

#include "examples/common/cmdline_parser.h"
#include "examples/common/gpa_sample_app.h"

#include <string>

namespace gpa_example
{
    /// @brief Sample GPA Application using DirectX 11.
    class Dx11SampleApp : public GpaSampleApp
    {
    public:
        /// @brief Constructor.
        ///
        /// @param app_name The name of the application.
        /// @param cmdline_parser The command line parser to be used by this application.
        Dx11SampleApp(const std::string app_name, CmdlineParser& cmdline_parser);

        /// @brief Destructor.
        ~Dx11SampleApp() override = default;

        /// @brief Specifies whether or not GPA should be used by this application.
        ///
        /// @return true if specified on the command line, false otherwise.
        bool NoGpa();

    private:
        /// @brief Specifies whether or not GPA should be used by this application.
        bool nogpa_;
    };
}  // namespace gpa_example

#endif  // GPU_PERF_API_EXAMPLES_DX11_SAMPLE_H_
