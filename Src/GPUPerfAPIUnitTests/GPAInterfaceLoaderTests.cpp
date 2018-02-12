//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit tests for GPAInterfaceLoader
//==============================================================================

#include <gtest/gtest.h>
#include "GPAInterfaceLoader.h"

GPAApiManager* GPAApiManager::m_pGpaApiManager = nullptr;

class GPAInterfaceLoaderTest : public ::testing::TestWithParam<GPA_API_Type>
{
public:
    GPAInterfaceLoaderTest()
        :
        ::testing::TestWithParam<GPA_API_Type>()
    {
    }

    ~GPAInterfaceLoaderTest()
    {
    }

    /// Create and set up test resources
    virtual void SetUp();

    /// Tear down and cleanup test resources
    virtual void TearDown();

    /// Tear down and cleanup test resources
    static void TearDownTestCase();

    /// Run the test
    void Run();

private:
    std::map<GPA_API_Type, const char*> m_apiName;
};

void GPAInterfaceLoaderTest::SetUp()
{
    m_apiName[GPA_API_DIRECTX_11] = "DX11";
    m_apiName[GPA_API_DIRECTX_12] = "DX12";
    m_apiName[GPA_API_OPENGL] = "OpenGL";
    m_apiName[GPA_API_OPENGLES] = "OpenGLES";
    m_apiName[GPA_API_OPENCL] = "OpenCL";
    m_apiName[GPA_API_HSA] = "HSA";
    m_apiName[GPA_API_VULKAN] = "Vulkan";
    m_apiName[GPA_API_NO_SUPPORT] = "ApiNotSupported";
}

void GPAInterfaceLoaderTest::TearDown()
{
}

void GPAInterfaceLoaderTest::TearDownTestCase()
{
    GPAApiManager::DeleteInstance();
}

void GPAInterfaceLoaderTest::Run()
{
    GPA_API_Type Api = GetParam();
    ASSERT_NE(0u, m_apiName.count(Api)) << "API name out of range.";
    const char *apiName = m_apiName.find(Api)->second;

    // check if API loading succeeds
    EXPECT_EQ(GPA_STATUS_OK, GPAApiManager::Instance()->LoadApi(Api)) << "GPAApiManager failed to load API: " << apiName;

    // the APIs other than the currently loaded API should have null pointer in the function table
    // it is assumed the GPA_API_Type enum values increment by one
    for (int i = GPA_API__START; i < GPA_API__LAST; i++)
    {
        ASSERT_NE(0u, m_apiName.count(static_cast<GPA_API_Type>(i))) << "API name out of range.";

        if (Api == i)
        {
            EXPECT_NE(nullptr, GPAApiManager::Instance()->GetApi(Api)) << apiName << " should have non-null pointer in the GpaApiFunctionTable.";
        }
        else
        {
            EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetApi(static_cast<GPA_API_Type>(i))) << m_apiName.find(static_cast<GPA_API_Type>(i))->second << " should have null pointer in the GpaApiFunctionTable.";
        }
    }

    // erase the API from the GpaApiFunctionTable
    GPAApiManager::Instance()->UnloadApi(Api);
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetApi(Api)) << "GPAApiManager failed to unload " << apiName << " API.";
}

TEST_F(GPAInterfaceLoaderTest, TestDeleteInstance)
{
    // Using Vulkan and OpenCL here, since those exist on all platforms
    GPAApiManager::Instance()->LoadApi(GPA_API_VULKAN);
    EXPECT_NE(nullptr, GPAApiManager::Instance()->GetApi(GPA_API_VULKAN));
    GPAApiManager::DeleteInstance();
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetApi(GPA_API_VULKAN));
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetApi(GPA_API_OPENCL));
    GPAApiManager::DeleteInstance();

    GPAApiManager::Instance()->LoadApi(GPA_API_VULKAN);
    GPAApiManager::Instance()->LoadApi(GPA_API_OPENCL);
    EXPECT_NE(nullptr, GPAApiManager::Instance()->GetApi(GPA_API_VULKAN));
    EXPECT_NE(nullptr, GPAApiManager::Instance()->GetApi(GPA_API_OPENCL));
    GPAApiManager::DeleteInstance();

    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetApi(GPA_API_VULKAN));
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetApi(GPA_API_OPENCL));
    GPAApiManager::DeleteInstance();
}

TEST_P(GPAInterfaceLoaderTest, Api)
{
    Run();
}

#ifdef _WIN32
INSTANTIATE_TEST_CASE_P(
    WindowsAPI,
    GPAInterfaceLoaderTest,
    ::testing::Values(
    GPA_API_DIRECTX_11
    ,GPA_API_DIRECTX_12
    ,GPA_API_VULKAN
    ,GPA_API_OPENCL
    ,GPA_API_OPENGL
    ,GPA_API_OPENGLES
    )
);
#else
INSTANTIATE_TEST_CASE_P(
    LinuxAPI,
    GPAInterfaceLoaderTest,
    ::testing::Values(
    GPA_API_VULKAN
    ,GPA_API_OPENCL
#ifndef X86
    ,GPA_API_HSA
#endif
    ,GPA_API_OPENGL
    ,GPA_API_OPENGLES
    )
);
#endif
