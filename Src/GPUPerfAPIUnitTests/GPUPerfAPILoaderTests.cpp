//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit tests for GPUPerfAPILoader
//==============================================================================

#include <gtest/gtest.h>
#include <map>
#include "utils/GPUPerfAPILoader.h"

class GPUPerfAPILoaderTest : public ::testing::TestWithParam<GPA_API_Type>
{
public:
    GPUPerfAPILoaderTest()
        : ::testing::TestWithParam<GPA_API_Type>()
    {
    }

    ~GPUPerfAPILoaderTest()
    {
    }

    /// Create and set up test resources
    virtual void SetUp();

    /// Tear down and cleanup test resources
    virtual void TearDown();

    /// Run the test
    void Run();

private:
    std::map<GPA_API_Type, const char*> m_apiName;
};

void GPUPerfAPILoaderTest::SetUp()
{
    m_apiName[GPA_API_DIRECTX_11] = "DX11";
    m_apiName[GPA_API_DIRECTX_12] = "DX12";
    m_apiName[GPA_API_OPENGL]     = "OpenGL";
    m_apiName[GPA_API_OPENCL]     = "OpenCL";
    m_apiName[GPA_API_ROCM]       = "ROCm";
    m_apiName[GPA_API_VULKAN]     = "Vulkan";
    m_apiName[GPA_API_NO_SUPPORT] = "ApiNotSupported";
}

void GPUPerfAPILoaderTest::TearDown()
{
}

void GPUPerfAPILoaderTest::Run()
{
    GPA_API_Type Api = GetParam();
    ASSERT_NE(0u, m_apiName.count(Api)) << "API name out of range.";
    const char* pApiName = m_apiName.find(Api)->second;

    GPUPerfAPILoader gpaLoader;
    const char*      dllPath      = "";
    const char*      errorMessage = "";

    EXPECT_TRUE(gpaLoader.Load(dllPath, Api, &errorMessage))
        << "GPA loading with the legacy method failed for " << pApiName << ". Error message: " << errorMessage;
}

TEST_P(GPUPerfAPILoaderTest, Api)
{
    Run();
}

#ifdef _WIN32
INSTANTIATE_TEST_CASE_P(WindowsAPI,
                        GPUPerfAPILoaderTest,
                        ::testing::Values(GPA_API_DIRECTX_11, GPA_API_DIRECTX_12, GPA_API_VULKAN, GPA_API_OPENCL, GPA_API_OPENGL));
#else
INSTANTIATE_TEST_CASE_P(LinuxAPI,
                        GPUPerfAPILoaderTest,
                        ::testing::Values(GPA_API_VULKAN
#ifndef X86
                                          ,
                                          GPA_API_OPENCL,
                                          GPA_API_ROCM
#endif
                                          ,
                                          GPA_API_OPENGL));
#endif
