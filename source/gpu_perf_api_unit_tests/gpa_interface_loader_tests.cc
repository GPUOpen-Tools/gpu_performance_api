//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit tests for GPAInterfaceLoader
//==============================================================================

#include <map>
#include <gtest/gtest.h>

#include "gpu_perf_api_interface_loader.h"

GPAApiManager*    GPAApiManager::m_pGpaApiManager = nullptr;
GPAFuncTableInfo* g_pFuncTableInfo                = NULL;

class GPAInterfaceLoaderTest : public ::testing::TestWithParam<GPA_API_Type>
{
public:
    GPAInterfaceLoaderTest()
        : ::testing::TestWithParam<GPA_API_Type>()
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
    m_apiName[GPA_API_OPENGL]     = "OpenGL";
    m_apiName[GPA_API_OPENCL]     = "OpenCL";
    m_apiName[GPA_API_VULKAN]     = "Vulkan";
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
    const char* pApiName = m_apiName.find(Api)->second;

    // check if API loading succeeds
    EXPECT_EQ(GPA_STATUS_OK, GPAApiManager::Instance()->LoadApi(Api)) << "GPAApiManager failed to load API: " << pApiName;

    // the APIs other than the currently loaded API should have null pointer in the function table
    // it is assumed the GPA_API_Type enum values increment by one
    for (int i = GPA_API__START; i < GPA_API__LAST; i++)
    {
        if(GPA_API_DEPRECATED == i)
        {
            continue;
        }

        ASSERT_NE(0u, m_apiName.count(static_cast<GPA_API_Type>(i))) << "API name out of range.";

        if (Api == i)
        {
            EXPECT_NE(nullptr, GPAApiManager::Instance()->GetFunctionTable(Api)) << pApiName << " should have non-null pointer in the GpaApiFunctionTable.";
        }
        else
        {
            EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetFunctionTable(static_cast<GPA_API_Type>(i)))
                << m_apiName.find(static_cast<GPA_API_Type>(i))->second << " should have null pointer in the GpaApiFunctionTable.";
        }
    }

    // erase the API from the GpaApiFunctionTable
    GPAApiManager::Instance()->UnloadApi(Api);
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetFunctionTable(Api)) << "GPAApiManager failed to unload " << pApiName << " API.";
}

TEST_F(GPAInterfaceLoaderTest, TestGetLibraryFileName)
{
    for (int i = GPA_API__START; i < GPA_API_NO_SUPPORT; i++)
    {
        GPA_API_Type apiType     = static_cast<GPA_API_Type>(i);

        if(GPA_API_DEPRECATED == apiType)
        {
            continue;
        }

        LocaleString libFileName = GPAApiManager::Instance()->GetLibraryFileName(apiType);

#ifdef _WIN32

        EXPECT_FALSE(libFileName.empty());
        LocaleString libFileNamePrefix(L"GPUPerfAPI");
        EXPECT_TRUE(0 == libFileName.compare(0, libFileNamePrefix.length(), libFileNamePrefix));

#else

        if (GPA_API_DIRECTX_11 == apiType || GPA_API_DIRECTX_12 == apiType)
        {
            EXPECT_TRUE(libFileName.empty());
        }
        else
        {
            EXPECT_FALSE(libFileName.empty());
            LocaleString libFileNamePrefix(TFORMAT("GPUPerfAPI"));
            libFileNamePrefix = TFORMAT("lib") + libFileNamePrefix;
            EXPECT_TRUE(0 == libFileName.compare(0, libFileNamePrefix.length(), libFileNamePrefix));
        }

#endif
    }
}

TEST_F(GPAInterfaceLoaderTest, TestGetLibraryFullPath)
{
    for (int i = GPA_API__START; i < GPA_API_NO_SUPPORT; i++)
    {
        GPA_API_Type apiType     = static_cast<GPA_API_Type>(i);

        if(GPA_API_DEPRECATED == apiType)
        {
            continue;
        }

        LocaleString libFileName = GPAApiManager::Instance()->GetLibraryFullPath(apiType, TFORMAT("c:/test/"));

#ifdef _WIN32

        EXPECT_FALSE(libFileName.empty());
        LocaleString libFileNamePrefix(L"GPUPerfAPI");
        libFileNamePrefix = L"c:/test/" + libFileNamePrefix;
        EXPECT_TRUE(0 == libFileName.compare(0, libFileNamePrefix.length(), libFileNamePrefix));

#else

        if (GPA_API_DIRECTX_11 == apiType || GPA_API_DIRECTX_12 == apiType)
        {
            EXPECT_TRUE(libFileName.empty());
        }
        else
        {
            EXPECT_FALSE(libFileName.empty());
            LocaleString libFileNamePrefix(TFORMAT("GPUPerfAPI"));
            libFileNamePrefix = TFORMAT("c:/test/lib") + libFileNamePrefix;
            EXPECT_TRUE(0 == libFileName.compare(0, libFileNamePrefix.length(), libFileNamePrefix));
        }

#endif
    }
}

TEST_F(GPAInterfaceLoaderTest, TestDeleteInstance)
{
    GPA_API_Type secondAPI = GPA_API_OPENCL;

#ifndef _WIN32
#ifdef X86
    secondAPI = GPA_API_OPENGL;
#endif
#endif

    // Using Vulkan and OpenCL here, since those exist on all platforms
    GPAApiManager::Instance()->LoadApi(GPA_API_VULKAN);
    GPAFunctionTable* pTempFuncTable = GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN);
    EXPECT_NE(nullptr, pTempFuncTable);
    GPAApiManager::DeleteInstance();
    pTempFuncTable = GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN);
    EXPECT_EQ(nullptr, pTempFuncTable);
    pTempFuncTable = GPAApiManager::Instance()->GetFunctionTable(secondAPI);
    EXPECT_EQ(nullptr, pTempFuncTable);
    GPAApiManager::DeleteInstance();

    GPAApiManager::Instance()->LoadApi(GPA_API_VULKAN);
    GPAApiManager::Instance()->LoadApi(secondAPI);
    pTempFuncTable = GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN);
    EXPECT_NE(nullptr, pTempFuncTable);
    pTempFuncTable = GPAApiManager::Instance()->GetFunctionTable(secondAPI);
    EXPECT_NE(nullptr, pTempFuncTable);
    GPAApiManager::DeleteInstance();

    pTempFuncTable = GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN);
    EXPECT_EQ(nullptr, pTempFuncTable);
    pTempFuncTable = GPAApiManager::Instance()->GetFunctionTable(secondAPI);
    EXPECT_EQ(nullptr, pTempFuncTable);
    GPAApiManager::DeleteInstance();
}

TEST_F(GPAInterfaceLoaderTest, TestLoadAPIWithPath)
{
    GPA_API_Type secondAPI = GPA_API_OPENCL;

#ifndef _WIN32
#ifdef X86
    secondAPI = GPA_API_OPENGL;
#endif
#endif

    LocaleString cwd = GPAIL_GetWorkingDirectoryPath();
    // Using Vulkan and OpenCL here, since those exist on all platforms
    GPAApiManager::Instance()->LoadApi(GPA_API_VULKAN, cwd);
    EXPECT_NE(nullptr, GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN));
    GPAApiManager::DeleteInstance();
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN));
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetFunctionTable(secondAPI));
    GPAApiManager::DeleteInstance();

    GPAApiManager::Instance()->LoadApi(GPA_API_VULKAN, cwd);
    GPAApiManager::Instance()->LoadApi(secondAPI, cwd);
    EXPECT_NE(nullptr, GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN));
    EXPECT_NE(nullptr, GPAApiManager::Instance()->GetFunctionTable(secondAPI));
    GPAApiManager::DeleteInstance();

    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN));
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetFunctionTable(secondAPI));
    GPAApiManager::DeleteInstance();

    if ('/' == cwd[cwd.length() - 1])
    {
        cwd.pop_back();
    }

    GPAApiManager::Instance()->LoadApi(GPA_API_VULKAN, cwd);
    EXPECT_NE(nullptr, GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN));
    GPAApiManager::DeleteInstance();
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN));
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetFunctionTable(secondAPI));
    GPAApiManager::DeleteInstance();

    GPAApiManager::Instance()->LoadApi(GPA_API_VULKAN, cwd);
    GPAApiManager::Instance()->LoadApi(secondAPI, cwd);
    EXPECT_NE(nullptr, GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN));
    EXPECT_NE(nullptr, GPAApiManager::Instance()->GetFunctionTable(secondAPI));
    GPAApiManager::DeleteInstance();

    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN));
    EXPECT_EQ(nullptr, GPAApiManager::Instance()->GetFunctionTable(secondAPI));
    GPAApiManager::DeleteInstance();
}

TEST_P(GPAInterfaceLoaderTest, Api)
{
    Run();
}

#ifdef _WIN32
INSTANTIATE_TEST_CASE_P(WindowsAPI,
                        GPAInterfaceLoaderTest,
                        ::testing::Values(GPA_API_DIRECTX_11, GPA_API_DIRECTX_12, GPA_API_VULKAN, GPA_API_OPENCL, GPA_API_OPENGL));
#else
INSTANTIATE_TEST_CASE_P(LinuxAPI,
                        GPAInterfaceLoaderTest,
                        ::testing::Values(GPA_API_VULKAN
#ifndef X86
                                          ,GPA_API_OPENCL
#endif
                                          ,GPA_API_OPENGL));
#endif
