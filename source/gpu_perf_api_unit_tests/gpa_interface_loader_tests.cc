//==============================================================================
// Copyright (c) 2017-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit tests for GPAInterfaceLoader.
//==============================================================================

#include <map>

#include <gtest/gtest.h>

#include "gpu_performance_api/gpu_perf_api_interface_loader.h"

GpaApiManager*    GpaApiManager::gpa_api_manager_ = nullptr;
GpaFuncTableInfo* gpa_function_table_info         = NULL;

/// @brief GPA Interface Loader tests.
class GpaInterfaceLoaderTest : public ::testing::TestWithParam<GpaApiType>
{
public:
    /// @brief Constructor.
    GpaInterfaceLoaderTest()
        : ::testing::TestWithParam<GpaApiType>()
    {
    }

    /// @brief Destructor.
    ~GpaInterfaceLoaderTest()
    {
    }

    /// Create and set up test resources.
    virtual void SetUp();

    /// Tear down and cleanup test resources.
    virtual void TearDown();

    /// Tear down and cleanup test resources.
    static void TearDownTestCase();

    /// Run the test.
    void Run();

private:
    std::map<GpaApiType, const char*> api_name_;
};

void GpaInterfaceLoaderTest::SetUp()
{
    api_name_[kGpaApiDirectx11] = "DX11";
    api_name_[kGpaApiDirectx12] = "DX12";
    api_name_[kGpaApiOpengl]    = "OpenGL";
    api_name_[kGpaApiOpencl]    = "OpenCL";
    api_name_[kGpaApiVulkan]    = "Vulkan";
    api_name_[kGpaApiNoSupport] = "ApiNotSupported";
}

void GpaInterfaceLoaderTest::TearDown()
{
}

void GpaInterfaceLoaderTest::TearDownTestCase()
{
    GpaApiManager::DeleteInstance();
}

void GpaInterfaceLoaderTest::Run()
{
    GpaApiType Api = GetParam();
    ASSERT_NE(0u, api_name_.count(Api)) << "API name out of range.";
    const char* api_name = api_name_.find(Api)->second;

    // Skip OpenCL on linux.
#ifndef _WIN32
    if (kGpaApiOpencl == Api)
    {
        return;
    }
#endif

    // Check if API loading succeeds.
    EXPECT_EQ(kGpaStatusOk, GpaApiManager::Instance()->LoadApi(Api)) << "GpaApiManager failed to load API: " << api_name;

    // The APIs other than the currently loaded API should have null pointer in the function table.
    // It is assumed the GpaApiType enum values increment by one.
    for (int i = kGpaApiStart; i < kGpaApiLast; i++)
    {
        if (kGpaApiDeprecated == i)
        {
            continue;
        }

        ASSERT_NE(0u, api_name_.count(static_cast<GpaApiType>(i))) << "API name out of range.";

        if (Api == i)
        {
            EXPECT_NE(nullptr, GpaApiManager::Instance()->GetFunctionTable(Api)) << api_name << " should have non-null pointer in the GpaApiFunctionTable.";
        }
        else
        {
            EXPECT_EQ(nullptr, GpaApiManager::Instance()->GetFunctionTable(static_cast<GpaApiType>(i)))
                << api_name_.find(static_cast<GpaApiType>(i))->second << " should have null pointer in the GpaApiFunctionTable.";
        }
    }

    // Erase the API from the GpaApiFunctionTable.
    GpaApiManager::Instance()->UnloadApi(Api);
    EXPECT_EQ(nullptr, GpaApiManager::Instance()->GetFunctionTable(Api)) << "GpaApiManager failed to unload " << api_name << " API.";
}

TEST_F(GpaInterfaceLoaderTest, TestGetLibraryFileName)
{
    for (int i = kGpaApiStart; i < kGpaApiNoSupport; i++)
    {
        GpaApiType api_type = static_cast<GpaApiType>(i);

        if (kGpaApiDeprecated == api_type)
        {
            continue;
        }

        LocaleString lib_file_name = GpaApiManager::Instance()->GetLibraryFileName(api_type);

#ifdef _WIN32

        EXPECT_FALSE(lib_file_name.empty());
        LocaleString libFileNamePrefix(L"GPUPerfAPI");
        EXPECT_TRUE(0 == lib_file_name.compare(0, libFileNamePrefix.length(), libFileNamePrefix));

#else

        if (kGpaApiDirectx11 == api_type || kGpaApiDirectx12 == api_type || kGpaApiOpencl == api_type)
        {
            EXPECT_TRUE(lib_file_name.empty());
        }
        else
        {
            EXPECT_FALSE(lib_file_name.empty());
            LocaleString lib_file_name_prefix(TFORMAT("GPUPerfAPI"));
            lib_file_name_prefix = TFORMAT("lib") + lib_file_name_prefix;
            EXPECT_TRUE(0 == lib_file_name.compare(0, lib_file_name_prefix.length(), lib_file_name_prefix));
        }

#endif
    }
}

TEST_F(GpaInterfaceLoaderTest, TestGetLibraryFullPath)
{
    for (int i = kGpaApiStart; i < kGpaApiNoSupport; i++)
    {
        GpaApiType api_type = static_cast<GpaApiType>(i);

        if (kGpaApiDeprecated == api_type)
        {
            continue;
        }

        LocaleString lib_file_name = GpaApiManager::Instance()->GetLibraryFullPath(api_type, TFORMAT("c:/test/"));

#ifdef _WIN32

        EXPECT_FALSE(lib_file_name.empty());
        LocaleString lib_file_name_prefix(L"GPUPerfAPI");
        lib_file_name_prefix = L"c:/test/" + lib_file_name_prefix;
        EXPECT_TRUE(0 == lib_file_name.compare(0, lib_file_name_prefix.length(), lib_file_name_prefix));

#else

        if (kGpaApiDirectx11 == api_type || kGpaApiDirectx12 == api_type || kGpaApiOpencl == api_type)
        {
            EXPECT_TRUE(lib_file_name.empty());
        }
        else
        {
            EXPECT_FALSE(lib_file_name.empty());
            LocaleString lib_file_name_prefix(TFORMAT("GPUPerfAPI"));
            lib_file_name_prefix = TFORMAT("c:/test/lib") + lib_file_name_prefix;
            EXPECT_TRUE(0 == lib_file_name.compare(0, lib_file_name_prefix.length(), lib_file_name_prefix));
        }

#endif
    }
}

TEST_F(GpaInterfaceLoaderTest, TestDeleteInstance)
{
    GpaApiType second_api = kGpaApiOpengl;

    // Using Vulkan and OpenCL here, since those exist on all platforms.
    GpaApiManager::Instance()->LoadApi(kGpaApiVulkan);
    GpaFunctionTable* function_table = GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan);
    EXPECT_NE(nullptr, function_table);
    // Deleting the instance below should also cause the API to be unloaded, so it does not need to explicitly unloaded.
    GpaApiManager::DeleteInstance();
    function_table = GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan);
    EXPECT_EQ(nullptr, function_table);
    function_table = GpaApiManager::Instance()->GetFunctionTable(second_api);
    EXPECT_EQ(nullptr, function_table);
    GpaApiManager::DeleteInstance();

    GpaApiManager::Instance()->LoadApi(kGpaApiVulkan);
    GpaApiManager::Instance()->LoadApi(second_api);
    function_table = GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan);
    EXPECT_NE(nullptr, function_table);
    function_table = GpaApiManager::Instance()->GetFunctionTable(second_api);
    EXPECT_NE(nullptr, function_table);
    // Deleting the instance below should also cause the API to be unloaded, so it does not need to explicitly unloaded.
    GpaApiManager::DeleteInstance();

    function_table = GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan);
    EXPECT_EQ(nullptr, function_table);
    function_table = GpaApiManager::Instance()->GetFunctionTable(second_api);
    EXPECT_EQ(nullptr, function_table);
    GpaApiManager::DeleteInstance();
}

TEST_F(GpaInterfaceLoaderTest, TestLoadAPIWithPath)
{
    GpaApiType second_api = kGpaApiOpengl;

    LocaleString cwd = GpaInterfaceLoaderGetWorkingDirectoryPath();
    // Using Vulkan and OpenCL here, since those exist on all platforms.
    GpaApiManager::Instance()->LoadApi(kGpaApiVulkan, cwd);
    EXPECT_NE(nullptr, GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan));
    GpaApiManager::DeleteInstance();
    EXPECT_EQ(nullptr, GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan));
    EXPECT_EQ(nullptr, GpaApiManager::Instance()->GetFunctionTable(second_api));
    GpaApiManager::DeleteInstance();

    GpaApiManager::Instance()->LoadApi(kGpaApiVulkan, cwd);
    GpaApiManager::Instance()->LoadApi(second_api, cwd);
    EXPECT_NE(nullptr, GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan));
    EXPECT_NE(nullptr, GpaApiManager::Instance()->GetFunctionTable(second_api));
    GpaApiManager::DeleteInstance();

    EXPECT_EQ(nullptr, GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan));
    EXPECT_EQ(nullptr, GpaApiManager::Instance()->GetFunctionTable(second_api));
    GpaApiManager::DeleteInstance();

    if ('/' == cwd[cwd.length() - 1])
    {
        cwd.pop_back();
    }

    GpaApiManager::Instance()->LoadApi(kGpaApiVulkan, cwd);
    EXPECT_NE(nullptr, GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan));
    GpaApiManager::DeleteInstance();
    EXPECT_EQ(nullptr, GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan));
    EXPECT_EQ(nullptr, GpaApiManager::Instance()->GetFunctionTable(second_api));
    GpaApiManager::DeleteInstance();

    GpaApiManager::Instance()->LoadApi(kGpaApiVulkan, cwd);
    GpaApiManager::Instance()->LoadApi(second_api, cwd);
    EXPECT_NE(nullptr, GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan));
    EXPECT_NE(nullptr, GpaApiManager::Instance()->GetFunctionTable(second_api));
    GpaApiManager::DeleteInstance();

    EXPECT_EQ(nullptr, GpaApiManager::Instance()->GetFunctionTable(kGpaApiVulkan));
    EXPECT_EQ(nullptr, GpaApiManager::Instance()->GetFunctionTable(second_api));
    GpaApiManager::DeleteInstance();
}

TEST_P(GpaInterfaceLoaderTest, Api)
{
    Run();
}

#ifdef _WIN32
INSTANTIATE_TEST_CASE_P(WindowsAPI, GpaInterfaceLoaderTest, ::testing::Values(kGpaApiDirectx11, kGpaApiDirectx12, kGpaApiVulkan, kGpaApiOpencl, kGpaApiOpengl));
#else
INSTANTIATE_TEST_CASE_P(LinuxAPI, GpaInterfaceLoaderTest, ::testing::Values(kGpaApiVulkan, kGpaApiOpengl));
#endif
