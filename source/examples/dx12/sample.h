//==============================================================================
// Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Sample implementation.
//==============================================================================

#ifndef GPU_PERF_API_EXAMPLES_DX12_SAMPLE_H_
#define GPU_PERF_API_EXAMPLES_DX12_SAMPLE_H_

#include "examples/common/cmdline_parser.h"
#include "examples/common/gpa_sample_app.h"

namespace gpa_example
{
    /// @brief Sample GPA Application using DirectX 12.
    class Dx12SampleApp : public GpaSampleApp
    {
    public:
        /// @brief Constructor.
        ///
        /// @param app_name The name of the application.
        /// @param cmdline_parser The command line parser to be used by this application.
        Dx12SampleApp(const std::string app_name, CmdlineParser& cmdline_parser);

        /// @brief Destructor.
        ~Dx12SampleApp() override = default;

        /// @brief Specifies whether or not GPA should be used by this application.
        ///
        /// @return true if specified on the command line, false otherwise.
        bool NoGpa();

        /// @brief Specifies whether or no DirectX 12 Bundles features should be profiled.
        ///
        /// Starting with the Adrenalin 19.1.1 driver, profiling bundles is no longer supported.
        /// @return true if specified on the command line, false otherwise.
        bool ProfileBundle();

    private:
        /// @brief Specifies whether or not GPA should be used by this application.
        bool nogpa_;

        /// @brief Specifies whether or no DirectX 12 Bundles features should be profiled.
        bool profile_bundle_;
    };
}  // namespace gpa_example

#endif // GPU_PERF_API_EXAMPLES_DX12_SAMPLE_H_
