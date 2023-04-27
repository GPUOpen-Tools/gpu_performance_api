//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit tests for GpuPerfApiLoader.
//==============================================================================

#include <map>

#include <gtest/gtest.h>

#include "gpu_perf_api_unit_tests/utils/gpu_perf_api_loader.h"

class GpuPerfApiLoaderTest : public ::testing::TestWithParam<GpaApiType>
{
public:
    GpuPerfApiLoaderTest()
        : ::testing::TestWithParam<GpaApiType>()
    {
    }

    ~GpuPerfApiLoaderTest()
    {
    }

    /// Create and set up test resources
    virtual void SetUp();

    /// Tear down and cleanup test resources
    virtual void TearDown();

    /// Run the test
    void Run();

private:
    std::map<GpaApiType, const char*> api_name_;
};

void GpuPerfApiLoaderTest::SetUp()
{
    api_name_[kGpaApiDirectx11] = "DX11";
    api_name_[kGpaApiDirectx12] = "DX12";
    api_name_[kGpaApiOpengl]    = "OpenGL";
    api_name_[kGpaApiOpencl]    = "OpenCL";
    api_name_[kGpaApiVulkan]    = "Vulkan";
    api_name_[kGpaApiNoSupport] = "ApiNotSupported";
}

void GpuPerfApiLoaderTest::TearDown()
{
}

void GpuPerfApiLoaderTest::Run()
{
    GpaApiType api = GetParam();
    ASSERT_NE(0u, api_name_.count(api)) << "API name out of range.";
    const char* api_name = api_name_.find(api)->second;

    GpuPerfApiLoader gpa_loader;
    const char*      dll_path      = "";
    const char*      error_message = "";

    EXPECT_TRUE(gpa_loader.Load(dll_path, api, &error_message))
        << "GPA loading with the legacy method failed for " << api_name << ". Error message: " << error_message;

    // When the GpuPerfApiLoader is destroyed, it will automatically unload the loaded DLL.
}

TEST_P(GpuPerfApiLoaderTest, api)
{
    Run();
}

#ifdef _WIN32
INSTANTIATE_TEST_CASE_P(WindowsAPI, GpuPerfApiLoaderTest, ::testing::Values(kGpaApiDirectx11, kGpaApiDirectx12, kGpaApiVulkan, kGpaApiOpencl, kGpaApiOpengl));
#else
INSTANTIATE_TEST_CASE_P(LinuxAPI, GpuPerfApiLoaderTest, ::testing::Values(kGpaApiVulkan, kGpaApiOpengl));
#endif
