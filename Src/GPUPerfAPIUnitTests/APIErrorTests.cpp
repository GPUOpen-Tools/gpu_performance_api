//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit tests to validate error handling/reporting from GPA APIs
///         These tests are meant to exercise the GPA API without actually
///         creating valid contexts or executing any workloads. Additional unit
///         testing of the APIs is done with real workloads in the GPA
///         functional test suite.
//==============================================================================

#include <gtest/gtest.h>
#include "GPUPerfAPI.h"
#include "GPAInterfaceLoader.h"
#include "GPACommonDefs.h"

class GPAAPIErrorTest : public ::testing::TestWithParam<GPA_API_Type>
{
public:
    GPAAPIErrorTest()
        :
        ::testing::TestWithParam<GPA_API_Type>()
    {
    }

    ~GPAAPIErrorTest()
    {
    }

    /// Create and set up test resources
    static void SetUpTestCase();

    /// Tear down and cleanup test resources
    static void TearDownTestCase();

    /// Create and set up test resources
    virtual void SetUp();

    /// Tear down and cleanup test resources
    virtual void TearDown();

protected:
    static void LogFunction(GPA_Logging_Type loggingType, const char* pLogMessage);

    const GPAFunctionTable* m_pGpaFuncTable;
    GPA_API_Type m_api;

private:
    static std::map<GPA_API_Type, const char*> ms_apiName;
};


std::map<GPA_API_Type, const char*> GPAAPIErrorTest::ms_apiName;

void GPAAPIErrorTest::SetUpTestCase()
{
    ms_apiName[GPA_API_DIRECTX_11] = "DX11";
    ms_apiName[GPA_API_DIRECTX_12] = "DX12";
    ms_apiName[GPA_API_OPENGL] = "OpenGL";
    ms_apiName[GPA_API_OPENCL] = "OpenCL";
    ms_apiName[GPA_API_HSA] = "HSA";
    ms_apiName[GPA_API_VULKAN] = "Vulkan";
    ms_apiName[GPA_API_NO_SUPPORT] = "ApiNotSupported";
}

void GPAAPIErrorTest::TearDownTestCase()
{
    GPAApiManager::DeleteInstance();
}

void GPAAPIErrorTest::SetUp()
{
    m_api = GetParam();

    ASSERT_NE(0u, ms_apiName.count(m_api)) << "API name out of range.";
    const char* pApiName = ms_apiName.find(m_api)->second;

    EXPECT_EQ(GPA_STATUS_OK, GPAApiManager::Instance()->LoadApi(m_api)) << "GPAApiManager failed to load API: " << pApiName;
    m_pGpaFuncTable = GPAApiManager::Instance()->GetFunctionTable(GetParam());
    ASSERT_NE(nullptr, m_pGpaFuncTable);

    GPA_Status status = m_pGpaFuncTable->GPA_RegisterLoggingCallback(GPA_LOGGING_ALL, LogFunction);
    EXPECT_EQ(GPA_STATUS_OK, status);
}

void GPAAPIErrorTest::TearDown()
{
    GPAApiManager::Instance()->UnloadApi(m_api);
}

void GPAAPIErrorTest::LogFunction(GPA_Logging_Type loggingType, const char* pLogMessage)
{
    UNREFERENCED_PARAMETER(loggingType);
    ASSERT_NE(nullptr, pLogMessage);

    std::string message(pLogMessage);
    ASSERT_LT(0ul, message.length());
    EXPECT_EQ('.', message[message.length() - 1]);
}

TEST_P(GPAAPIErrorTest, TestGPA_RegisterLoggingCallback)
{
    GPA_Status status = m_pGpaFuncTable->GPA_RegisterLoggingCallback(GPA_LOGGING_ERROR, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_RegisterLoggingCallback(GPA_LOGGING_NONE, nullptr);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_RegisterLoggingCallback(GPA_LOGGING_ALL, LogFunction);
    EXPECT_EQ(GPA_STATUS_OK, status);
}

TEST_P(GPAAPIErrorTest, TestGPA_InitializeAndDestroy)
{
    GPA_Status status = m_pGpaFuncTable->GPA_Destroy();
    EXPECT_EQ(GPA_STATUS_ERROR_GPA_NOT_INITIALIZED, status);

    status = m_pGpaFuncTable->GPA_Initialize(GPA_INITIALIZE_DEFAULT_BIT);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_Initialize(GPA_INITIALIZE_DEFAULT_BIT);
    EXPECT_EQ(GPA_STATUS_ERROR_GPA_ALREADY_INITIALIZED, status);

    status = m_pGpaFuncTable->GPA_Destroy();
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_Destroy();
    EXPECT_EQ(GPA_STATUS_ERROR_GPA_NOT_INITIALIZED, status);

    status = m_pGpaFuncTable->GPA_Initialize(GPA_INITIALIZE_SIMULTANEOUS_QUEUES_ENABLE_BIT);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_Destroy();
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_Initialize(0xBADF00D);
    EXPECT_EQ(GPA_STATUS_ERROR_INVALID_PARAMETER, status);
}

TEST_P(GPAAPIErrorTest, TestGPA_OpenAndCloseContext)
{
    GPA_ContextId badContextId = reinterpret_cast<GPA_ContextId>(0xBADF00D);

    GPA_Status status = m_pGpaFuncTable->GPA_Initialize(GPA_INITIALIZE_DEFAULT_BIT);
    ASSERT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_CloseContext(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    GPA_ContextId contextId;
    status = m_pGpaFuncTable->GPA_OpenContext(nullptr, GPA_OPENCONTEXT_DEFAULT_BIT, &contextId);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CloseContext(badContextId);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);
}

TEST_P(GPAAPIErrorTest, TestGPA_ContextInterrogation)
{
    GPA_ContextId badContextId = reinterpret_cast<GPA_ContextId>(0xBADF00D);

    // GPA_GetSupportedSampleTypes
    GPA_Status status = m_pGpaFuncTable->GPA_GetSupportedSampleTypes(nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    GPA_ContextSampleTypeFlags sampleTypes;
    status = m_pGpaFuncTable->GPA_GetSupportedSampleTypes(nullptr, &sampleTypes);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSupportedSampleTypes(badContextId, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSupportedSampleTypes(badContextId, &sampleTypes);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_GetDeviceAndRevisionId
    status = m_pGpaFuncTable->GPA_GetDeviceAndRevisionId(nullptr, nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 deviceId = 0;
    gpa_uint32 revisionId = 0;
    status = m_pGpaFuncTable->GPA_GetDeviceAndRevisionId(nullptr, &deviceId, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetDeviceAndRevisionId(nullptr, nullptr, &revisionId);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetDeviceAndRevisionId(nullptr, &deviceId, &revisionId);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetDeviceName(nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    const char* pDeviceName = nullptr;
    status = m_pGpaFuncTable->GPA_GetDeviceName(nullptr, &pDeviceName);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetDeviceAndRevisionId(badContextId, nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    deviceId = 0;
    revisionId = 0;
    status = m_pGpaFuncTable->GPA_GetDeviceAndRevisionId(badContextId, &deviceId, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetDeviceAndRevisionId(badContextId, nullptr, &revisionId);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetDeviceAndRevisionId(badContextId, &deviceId, &revisionId);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetDeviceName(badContextId, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pDeviceName = nullptr;
    status = m_pGpaFuncTable->GPA_GetDeviceName(badContextId, &pDeviceName);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);
}

TEST_P(GPAAPIErrorTest, TestGPA_CounterInterrogation)
{
    GPA_ContextId badContextId = reinterpret_cast<GPA_ContextId>(0xBADF00D);

    // GPA_GetNumCounters
    GPA_Status status = m_pGpaFuncTable->GPA_GetNumCounters(nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 numCounters;
    status = m_pGpaFuncTable->GPA_GetNumCounters(nullptr, &numCounters);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetNumCounters(badContextId, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetNumCounters(badContextId, &numCounters);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_GetCounterName
    status = m_pGpaFuncTable->GPA_GetCounterName(nullptr, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    const char* pCounterName = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterName(nullptr, 0, &pCounterName);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterName(nullptr, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pCounterName = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterName(nullptr, static_cast<gpa_uint32>(-1), &pCounterName);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterName(badContextId, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pCounterName = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterName(badContextId, 0, &pCounterName);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetCounterName(badContextId, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pCounterName = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterName(badContextId, static_cast<gpa_uint32>(-1), &pCounterName);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_GetCounterIndex
    status = m_pGpaFuncTable->GPA_GetCounterIndex(nullptr, nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 index = 0;
    status = m_pGpaFuncTable->GPA_GetCounterIndex(nullptr, nullptr, &index);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterIndex(nullptr, "foo", nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    index = 0;
    status = m_pGpaFuncTable->GPA_GetCounterIndex(nullptr, "GPUTime", &index);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    index = 0;
    status = m_pGpaFuncTable->GPA_GetCounterIndex(nullptr, "Wavefronts", &index);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterIndex(badContextId, nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    index = 0;
    status = m_pGpaFuncTable->GPA_GetCounterIndex(badContextId, nullptr, &index);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterIndex(badContextId, "foo", nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    index = 0;
    status = m_pGpaFuncTable->GPA_GetCounterIndex(badContextId, "GPUTime", &index);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    index = 0;
    status = m_pGpaFuncTable->GPA_GetCounterIndex(badContextId, "Wavefronts", &index);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_GetCounterGroup
    status = m_pGpaFuncTable->GPA_GetCounterGroup(nullptr, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    const char* pCounterGroup = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterGroup(nullptr, 0, &pCounterGroup);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterGroup(nullptr, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pCounterGroup = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterGroup(nullptr, static_cast<gpa_uint32>(-1), &pCounterGroup);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterGroup(badContextId, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pCounterGroup = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterGroup(badContextId, 0, &pCounterGroup);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetCounterGroup(badContextId, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pCounterGroup = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterGroup(badContextId, static_cast<gpa_uint32>(-1), &pCounterGroup);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_GetCounterDescription
    status = m_pGpaFuncTable->GPA_GetCounterDescription(nullptr, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    const char* pCounterDescription = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterDescription(nullptr, 0, &pCounterDescription);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterDescription(nullptr, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pCounterDescription = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterDescription(nullptr, static_cast<gpa_uint32>(-1), &pCounterDescription);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterDescription(badContextId, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pCounterDescription = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterDescription(badContextId, 0, &pCounterDescription);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetCounterDescription(badContextId, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pCounterDescription = nullptr;
    status = m_pGpaFuncTable->GPA_GetCounterDescription(badContextId, static_cast<gpa_uint32>(-1), &pCounterDescription);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_GetCounterDataType
    status = m_pGpaFuncTable->GPA_GetCounterDataType(nullptr, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    GPA_Data_Type counterDataType = GPA_DATA_TYPE__LAST;
    status = m_pGpaFuncTable->GPA_GetCounterDataType(nullptr, 0, &counterDataType);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterDataType(nullptr, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    counterDataType = GPA_DATA_TYPE__LAST;
    status = m_pGpaFuncTable->GPA_GetCounterDataType(nullptr, static_cast<gpa_uint32>(-1), &counterDataType);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterDataType(badContextId, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    counterDataType = GPA_DATA_TYPE__LAST;
    status = m_pGpaFuncTable->GPA_GetCounterDataType(badContextId, 0, &counterDataType);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetCounterDataType(badContextId, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    counterDataType = GPA_DATA_TYPE__LAST;
    status = m_pGpaFuncTable->GPA_GetCounterDataType(badContextId, static_cast<gpa_uint32>(-1), &counterDataType);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_GetCounterUsageType
    status = m_pGpaFuncTable->GPA_GetCounterUsageType(nullptr, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    GPA_Usage_Type counterUsageType = GPA_USAGE_TYPE__LAST;
    status = m_pGpaFuncTable->GPA_GetCounterUsageType(nullptr, 0, &counterUsageType);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterUsageType(nullptr, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    counterUsageType = GPA_USAGE_TYPE__LAST;
    status = m_pGpaFuncTable->GPA_GetCounterUsageType(nullptr, static_cast<gpa_uint32>(-1), &counterUsageType);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterUsageType(badContextId, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    counterUsageType = GPA_USAGE_TYPE__LAST;
    status = m_pGpaFuncTable->GPA_GetCounterUsageType(badContextId, 0, &counterUsageType);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetCounterUsageType(badContextId, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    counterUsageType = GPA_USAGE_TYPE__LAST;
    status = m_pGpaFuncTable->GPA_GetCounterUsageType(badContextId, static_cast<gpa_uint32>(-1), &counterUsageType);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_GetCounterUuid
    status = m_pGpaFuncTable->GPA_GetCounterUuid(nullptr, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    GPA_UUID counterUUID = {};
    status = m_pGpaFuncTable->GPA_GetCounterUuid(nullptr, 0, &counterUUID);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterUuid(nullptr, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    counterUUID = {};
    status = m_pGpaFuncTable->GPA_GetCounterUuid(nullptr, static_cast<gpa_uint32>(-1), &counterUUID);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterUuid(badContextId, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    counterUUID = {};
    status = m_pGpaFuncTable->GPA_GetCounterUuid(badContextId, 0, &counterUUID);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetCounterUuid(badContextId, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    counterUUID = {};
    status = m_pGpaFuncTable->GPA_GetCounterUuid(badContextId, static_cast<gpa_uint32>(-1), &counterUUID);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_GetCounterSampleTypes
    status = m_pGpaFuncTable->GPA_GetCounterSampleType(nullptr, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    GPA_Counter_Sample_Type sampleType;
    status = m_pGpaFuncTable->GPA_GetCounterSampleType(nullptr, 0, &sampleType);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterSampleType(nullptr, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterSampleType(nullptr, static_cast<gpa_uint32>(-1), &sampleType);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterSampleType(badContextId, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterSampleType(badContextId, 0, &sampleType);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetCounterSampleType(badContextId, static_cast<gpa_uint32>(-1), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetCounterSampleType(badContextId, static_cast<gpa_uint32>(-1), &sampleType);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_GetDataTypeAsStr
    status = m_pGpaFuncTable->GPA_GetDataTypeAsStr(GPA_DATA_TYPE_FLOAT64, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetDataTypeAsStr(GPA_DATA_TYPE_UINT64, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetDataTypeAsStr(GPA_DATA_TYPE__LAST, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetDataTypeAsStr(static_cast<GPA_Data_Type>(0xFFFF), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    const char* pTypeStr = nullptr;
    status = m_pGpaFuncTable->GPA_GetDataTypeAsStr(GPA_DATA_TYPE_FLOAT64, &pTypeStr);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_GetDataTypeAsStr(GPA_DATA_TYPE_UINT64, &pTypeStr);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_GetDataTypeAsStr(GPA_DATA_TYPE__LAST, &pTypeStr);
    EXPECT_EQ(GPA_STATUS_ERROR_INVALID_PARAMETER, status);

    status = m_pGpaFuncTable->GPA_GetDataTypeAsStr(static_cast<GPA_Data_Type>(0xFFFF), &pTypeStr);
    EXPECT_EQ(GPA_STATUS_ERROR_INVALID_PARAMETER, status);

    // GPA_GetUsageTypeAsStr
    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_RATIO, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_PERCENTAGE, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_CYCLES, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_MILLISECONDS, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_BYTES, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_ITEMS, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_KILOBYTES, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE__LAST, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(static_cast<GPA_Usage_Type>(0xFFFF), nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    const char* pUsageStr = nullptr;
    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_RATIO, &pUsageStr);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_PERCENTAGE, &pUsageStr);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_CYCLES, &pUsageStr);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_MILLISECONDS, &pUsageStr);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_BYTES, &pUsageStr);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_ITEMS, &pUsageStr);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE_KILOBYTES, &pUsageStr);
    EXPECT_EQ(GPA_STATUS_OK, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(GPA_USAGE_TYPE__LAST, &pUsageStr);
    EXPECT_EQ(GPA_STATUS_ERROR_INVALID_PARAMETER, status);

    status = m_pGpaFuncTable->GPA_GetUsageTypeAsStr(static_cast<GPA_Usage_Type>(0xFFFF), &pUsageStr);
    EXPECT_EQ(GPA_STATUS_ERROR_INVALID_PARAMETER, status);
}

TEST_P(GPAAPIErrorTest, TestGPA_SessionHandling)
{
    GPA_ContextId badContextId = reinterpret_cast<GPA_ContextId>(0xBADF00D);

    // GPA_CreateSession
    GPA_Status status = m_pGpaFuncTable->GPA_CreateSession(nullptr, GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    GPA_SessionId sessionId;
    status = m_pGpaFuncTable->GPA_CreateSession(nullptr, GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER, &sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CreateSession(nullptr, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CreateSession(nullptr, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER, &sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CreateSession(nullptr, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CreateSession(nullptr, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT, &sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CreateSession(nullptr, static_cast<GPA_Session_Sample_Type>(0xFFFFFFFF), &sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CreateSession(badContextId, GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CreateSession(badContextId, GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER, &sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_CreateSession(badContextId, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CreateSession(badContextId, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER, &sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_CreateSession(badContextId, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CreateSession(badContextId, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT, &sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_CreateSession(badContextId, static_cast<GPA_Session_Sample_Type>(0xFFFFFFFF), &sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, status);

    // GPA_DeleteSession
    status = m_pGpaFuncTable->GPA_DeleteSession(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    sessionId = reinterpret_cast<GPA_SessionId>(0xBADF00D);
    status = m_pGpaFuncTable->GPA_DeleteSession(sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_BeginSession
    status = m_pGpaFuncTable->GPA_BeginSession(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_BeginSession(sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_EndSession
    status = m_pGpaFuncTable->GPA_EndSession(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_EndSession(sessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);
}

TEST_P(GPAAPIErrorTest, TestGPA_CounterScheduling)
{
    GPA_SessionId badSessionId = reinterpret_cast<GPA_SessionId>(0xBADF00D);

    // GPA_EnableCounter
    GPA_Status status = m_pGpaFuncTable->GPA_EnableCounter(nullptr, 0);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_EnableCounter(nullptr, 0x7FFFFFFF);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_EnableCounter(badSessionId, 0);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_EnableCounter(badSessionId, 0x7FFFFFFF);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_DisableCounter
    status = m_pGpaFuncTable->GPA_DisableCounter(nullptr, 0);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_DisableCounter(nullptr, 0x7FFFFFFF);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_DisableCounter(badSessionId, 0);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_DisableCounter(badSessionId, 0x7FFFFFFF);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_EnableCounterByName
    status = m_pGpaFuncTable->GPA_EnableCounterByName(nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_EnableCounterByName(nullptr, "noCounter");
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_EnableCounterByName(nullptr, "GPUTime");
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_EnableCounterByName(nullptr, "Wavefronts");
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_EnableCounterByName(badSessionId, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_EnableCounterByName(badSessionId, "noCounter");
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_EnableCounterByName(badSessionId, "GPUTime");
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_EnableCounterByName(badSessionId, "Wavefronts");
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_DisableCounterByName
    status = m_pGpaFuncTable->GPA_DisableCounterByName(nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_DisableCounterByName(nullptr, "noCounter");
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_DisableCounterByName(nullptr, "GPUTime");
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_DisableCounterByName(nullptr, "Wavefronts");
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_DisableCounterByName(badSessionId, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_DisableCounterByName(badSessionId, "noCounter");
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_DisableCounterByName(badSessionId, "GPUTime");
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_DisableCounterByName(badSessionId, "Wavefronts");
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_EnableAllCounters
    status = m_pGpaFuncTable->GPA_EnableAllCounters(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_EnableAllCounters(badSessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_DisableAllCounters
    status = m_pGpaFuncTable->GPA_DisableAllCounters(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_DisableAllCounters(badSessionId);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);
}

TEST_P(GPAAPIErrorTest, TestGPA_QueryCounterScheduling)
{
    GPA_SessionId badSessionId = reinterpret_cast<GPA_SessionId>(0xBADF00D);

    // GPA_GetPassCount
    GPA_Status status = m_pGpaFuncTable->GPA_GetPassCount(nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 passCount = 0;
    status = m_pGpaFuncTable->GPA_GetPassCount(nullptr, &passCount);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetPassCount(badSessionId, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    passCount = 0;
    status = m_pGpaFuncTable->GPA_GetPassCount(badSessionId, &passCount);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_GetNumEnabledCounters
    status = m_pGpaFuncTable->GPA_GetNumEnabledCounters(nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 numEnabledCounters = 0;
    status = m_pGpaFuncTable->GPA_GetNumEnabledCounters(nullptr, &numEnabledCounters);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetNumEnabledCounters(badSessionId, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    numEnabledCounters = 0;
    status = m_pGpaFuncTable->GPA_GetNumEnabledCounters(badSessionId, &numEnabledCounters);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_GetEnabledIndex
    status = m_pGpaFuncTable->GPA_GetEnabledIndex(nullptr, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 enabledIndex = 0;
    status = m_pGpaFuncTable->GPA_GetEnabledIndex(nullptr, 0, &enabledIndex);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetEnabledIndex(nullptr, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    enabledIndex = 0;
    status = m_pGpaFuncTable->GPA_GetEnabledIndex(nullptr, 0x7FFFFFFF, &enabledIndex);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetEnabledIndex(badSessionId, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    enabledIndex = 0;
    status = m_pGpaFuncTable->GPA_GetEnabledIndex(badSessionId, 0, &enabledIndex);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetEnabledIndex(badSessionId, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    enabledIndex = 0;
    status = m_pGpaFuncTable->GPA_GetEnabledIndex(badSessionId, 0x7FFFFFFF, &enabledIndex);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_IsCounterEnabled
    status = m_pGpaFuncTable->GPA_IsCounterEnabled(nullptr, 0);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_IsCounterEnabled(nullptr, 0x7FFFFFFF);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_IsCounterEnabled(badSessionId, 0);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_IsCounterEnabled(badSessionId, 0x7FFFFFFF);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);
}

TEST_P(GPAAPIErrorTest, TestGPA_SampleHandling)
{
    GPA_SessionId badSession = reinterpret_cast<GPA_SessionId>(0xBADF00D);
    GPA_CommandListId badCommandList = reinterpret_cast<GPA_CommandListId>(0xBADF00D);
    GPA_CommandListId badCommandList2 = reinterpret_cast<GPA_CommandListId>(0xBA4F00D);

    // GPA_BeginCommandList
    GPA_Status status = m_pGpaFuncTable->GPA_BeginCommandList(nullptr, 0, nullptr, GPA_COMMAND_LIST_NONE, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_BeginCommandList(nullptr, 0x7FFFFFFF, this, GPA_COMMAND_LIST_NONE, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_BeginCommandList(nullptr, 0x7FFFFFFF, nullptr, GPA_COMMAND_LIST_PRIMARY, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    GPA_CommandListId commandListId;
    status = m_pGpaFuncTable->GPA_BeginCommandList(nullptr, 0x7FFFFFFF, this, GPA_COMMAND_LIST_PRIMARY, &commandListId);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_BeginCommandList(badSession, 0x7FFFFFFF, this, GPA_COMMAND_LIST_PRIMARY, &commandListId);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_BeginCommandList(badSession, 0, nullptr, GPA_COMMAND_LIST_NONE, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_BeginCommandList(badSession, 0x7FFFFFFF, this, GPA_COMMAND_LIST_NONE, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_BeginCommandList(badSession, 0x7FFFFFFF, nullptr, GPA_COMMAND_LIST_PRIMARY, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_BeginCommandList(badSession, 0x7FFFFFFF, this, GPA_COMMAND_LIST_PRIMARY, &commandListId);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_EndCommandList
    status = m_pGpaFuncTable->GPA_EndCommandList(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_EndCommandList(badCommandList);
    EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);

    // GPA_BeginSample
    status = m_pGpaFuncTable->GPA_BeginSample(0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_BeginSample(0, badCommandList);
    EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);

    // GPA_EndSample
    status = m_pGpaFuncTable->GPA_EndSample(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_EndSample(badCommandList);
    EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);

    // GPA_ContinueSampleOnCommandList
    status = m_pGpaFuncTable->GPA_ContinueSampleOnCommandList(0, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_ContinueSampleOnCommandList(0, badCommandList);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_ContinueSampleOnCommandList(0x7FFFFFFF, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_ContinueSampleOnCommandList(0x7FFFFFFF, badCommandList);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    // GPA_CopySecondarySamples
    status = m_pGpaFuncTable->GPA_CopySecondarySamples(nullptr, nullptr, 0, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(badCommandList, nullptr, 0, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    GPA_CommandListId commandListId2;
    status = m_pGpaFuncTable->GPA_BeginCommandList(nullptr, 0x7FFFFFFF, this, GPA_COMMAND_LIST_PRIMARY, &commandListId2);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(badCommandList, badCommandList, 0, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(badCommandList, badCommandList2, 0, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(nullptr, badCommandList2, 0, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(nullptr, nullptr, 0x7FFFFFFF, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(badCommandList, nullptr, 0x7FFFFFFF, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(badCommandList, badCommandList2, 0x7FFFFFFF, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(nullptr, badCommandList2, 0x7FFFFFFF, nullptr);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    gpa_uint32 newSampleIds = 0;
    status = m_pGpaFuncTable->GPA_CopySecondarySamples(nullptr, nullptr, 0, &newSampleIds);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(badCommandList, nullptr, 0, &newSampleIds);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(badCommandList, badCommandList, 0, &newSampleIds);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(nullptr, badCommandList, 0, &newSampleIds);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(nullptr, nullptr, 1, &newSampleIds);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(badCommandList, nullptr, 1, &newSampleIds);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(badCommandList, badCommandList, 1, &newSampleIds);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    status = m_pGpaFuncTable->GPA_CopySecondarySamples(nullptr, badCommandList, 1, &newSampleIds);

    if (GPA_API_DIRECTX_12 == m_api || GPA_API_VULKAN == m_api)
    {
        EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);
    }
    else
    {
        EXPECT_EQ(GPA_STATUS_ERROR_API_NOT_SUPPORTED, status);
    }

    // GPA_GetSampleCount
    status = m_pGpaFuncTable->GPA_GetSampleCount(nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 sampleCount;
    status = m_pGpaFuncTable->GPA_GetSampleCount(nullptr, &sampleCount);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleCount(badSession, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleCount(badSession, &sampleCount);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_GetSampleId
    status = m_pGpaFuncTable->GPA_GetSampleId(nullptr, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 sampleId;
    status = m_pGpaFuncTable->GPA_GetSampleId(nullptr, 0, &sampleId);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleId(badSession, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleId(badSession, 0, &sampleId);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);
}

TEST_P(GPAAPIErrorTest, TestGPA_QueryResults)
{
    GPA_SessionId badSession = reinterpret_cast<GPA_SessionId>(0xBADF00D);

    // GPA_IsPassComplete
    GPA_Status status = m_pGpaFuncTable->GPA_IsPassComplete(nullptr, 0);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_IsPassComplete(nullptr, 0x7FFFFFFF);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_IsPassComplete(badSession, 0);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_IsPassComplete(badSession, 0x7FFFFFFF);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_IsSessionComplete
    status = m_pGpaFuncTable->GPA_IsSessionComplete(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_IsSessionComplete(badSession);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_GetSampleResultSize
    status = m_pGpaFuncTable->GPA_GetSampleResultSize(nullptr, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResultSize(nullptr, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    size_t resultSize = 0;
    status = m_pGpaFuncTable->GPA_GetSampleResultSize(nullptr, 0, &resultSize);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResultSize(nullptr, 0x7FFFFFFF, &resultSize);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResultSize(badSession, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResultSize(badSession, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResultSize(badSession, 0, &resultSize);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetSampleResultSize(badSession, 0x7FFFFFFF, &resultSize);
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    // GPA_GetSampleResult
    status = m_pGpaFuncTable->GPA_GetSampleResult(nullptr, 0, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(nullptr, 0x7FFFFFFF, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(nullptr, 0, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(nullptr, 0, 0, reinterpret_cast<void*>(this));
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(nullptr, 0x7FFFFFFF, 0, reinterpret_cast<void*>(this));
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(nullptr, 0, 0x7FFFFFFF, reinterpret_cast<void*>(this));
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(badSession, 0, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(badSession, 0x7FFFFFFF, 0, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(badSession, 0, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(badSession, 0, 0, reinterpret_cast<void*>(this));
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(badSession, 0x7FFFFFFF, 0, reinterpret_cast<void*>(this));
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);

    status = m_pGpaFuncTable->GPA_GetSampleResult(badSession, 0, 0x7FFFFFFF, reinterpret_cast<void*>(this));
    EXPECT_EQ(GPA_STATUS_ERROR_SESSION_NOT_FOUND, status);
}


TEST_P(GPAAPIErrorTest, TestGPA_StatusErrorQuery)
{
    // GPA_GetStatusAsStr
    std::string gpaPrefixStr("GPA Status:");
    std::string statusStr = m_pGpaFuncTable->GPA_GetStatusAsStr(GPA_STATUS_OK);
    EXPECT_NE(0, statusStr.compare("GPA Status: Unknown Status."));
    EXPECT_EQ(0, statusStr.compare(0, gpaPrefixStr.length(), gpaPrefixStr));
    statusStr = m_pGpaFuncTable->GPA_GetStatusAsStr(GPA_STATUS_MAX);
    EXPECT_NE(0, statusStr.compare("GPA Status: Unknown Status."));
    EXPECT_EQ(0, statusStr.compare(0, gpaPrefixStr.length(), gpaPrefixStr));
    statusStr = m_pGpaFuncTable->GPA_GetStatusAsStr(static_cast<GPA_Status>(1024));
    EXPECT_EQ(0, statusStr.compare("GPA Status: Unknown Status."));

    gpaPrefixStr = "GPA Error:";
    statusStr = m_pGpaFuncTable->GPA_GetStatusAsStr(GPA_STATUS_ERROR_NULL_POINTER);
    EXPECT_NE(0, statusStr.compare("GPA Error: Unknown Error."));
    EXPECT_EQ(0, statusStr.compare(0, gpaPrefixStr.length(), gpaPrefixStr));
    statusStr = m_pGpaFuncTable->GPA_GetStatusAsStr(GPA_STATUS_MIN);
    EXPECT_NE(0, statusStr.compare("GPA Error: Unknown Error."));
    EXPECT_EQ(0, statusStr.compare(0, gpaPrefixStr.length(), gpaPrefixStr));
    statusStr = m_pGpaFuncTable->GPA_GetStatusAsStr(static_cast<GPA_Status>(-1024));
    EXPECT_EQ(0, statusStr.compare("GPA Error: Unknown Error."));
}

TEST_P(GPAAPIErrorTest, TestGPA_APIVersion)
{
    // GPA_GetVersion
    GPA_Status status = m_pGpaFuncTable->GPA_GetVersion(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 majorVer = 0;
    status = m_pGpaFuncTable->GPA_GetVersion(&majorVer, nullptr, nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 minorVer = 0;
    status = m_pGpaFuncTable->GPA_GetVersion(&majorVer, &minorVer, nullptr, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 build = 0;
    status = m_pGpaFuncTable->GPA_GetVersion(&majorVer, &minorVer, &build, nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    gpa_uint32 updateVer = 0;
    status = m_pGpaFuncTable->GPA_GetVersion(&majorVer, &minorVer, &build, &updateVer);
    EXPECT_EQ(GPA_STATUS_OK, status);
}

TEST_P(GPAAPIErrorTest, TestGPA_GPAFunctionTable)
{
    // GPA_GetFuncTable
    GPA_Status status = m_pGpaFuncTable->GPA_GetFuncTable(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    GPAFunctionTable* pFuncTable = nullptr;
    status = m_pGpaFuncTable->GPA_GetFuncTable(nullptr);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, status);

    pFuncTable = new GPAFunctionTable();
    status = m_pGpaFuncTable->GPA_GetFuncTable(reinterpret_cast<void*>(pFuncTable));
    ASSERT_EQ(GPA_STATUS_OK, status);
    EXPECT_EQ(pFuncTable->m_majorVer, GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER);
    EXPECT_EQ(pFuncTable->m_minorVer, GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER);

    pFuncTable->m_majorVer = 1024;
    pFuncTable->m_minorVer = 0;
    status = m_pGpaFuncTable->GPA_GetFuncTable(reinterpret_cast<void*>(pFuncTable));
    ASSERT_EQ(GPA_STATUS_ERROR_LIB_LOAD_MAJOR_VERSION_MISMATCH, status);
    EXPECT_EQ(pFuncTable->m_majorVer, GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER);
    EXPECT_EQ(pFuncTable->m_minorVer, GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER);

    pFuncTable->m_majorVer = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
    pFuncTable->m_minorVer = GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER + 1024;
    status = pFuncTable->GPA_GetFuncTable(reinterpret_cast<void*>(pFuncTable));
    ASSERT_EQ(GPA_STATUS_ERROR_LIB_LOAD_MINOR_VERSION_MISMATCH, status);
    EXPECT_EQ(pFuncTable->m_majorVer, GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER);
    EXPECT_EQ(pFuncTable->m_minorVer, GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER);

    delete pFuncTable;
    pFuncTable = new GPAFunctionTable();
    pFuncTable->m_minorVer -= sizeof(void*);
    status = m_pGpaFuncTable->GPA_GetFuncTable(reinterpret_cast<void*>(pFuncTable));
    ASSERT_EQ(GPA_STATUS_OK, status);
    EXPECT_EQ(m_pGpaFuncTable->m_majorVer, GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER);
    EXPECT_EQ(m_pGpaFuncTable->m_minorVer, GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER);
    // Note: Whenever GPA function table changes, we need to update this with the last function in the GPA function table
    EXPECT_EQ(nullptr, pFuncTable->GPA_GetVersion);

    delete pFuncTable;
}

#ifdef _WIN32
INSTANTIATE_TEST_CASE_P(
    WindowsAPI,
    GPAAPIErrorTest,
    ::testing::Values(
        GPA_API_DIRECTX_11
        , GPA_API_DIRECTX_12
        , GPA_API_VULKAN
        , GPA_API_OPENCL
        , GPA_API_OPENGL
    )
);
#else
INSTANTIATE_TEST_CASE_P(
    LinuxAPI,
    GPAAPIErrorTest,
    ::testing::Values(
        GPA_API_VULKAN
        , GPA_API_OPENCL
#ifndef X86
    , GPA_API_HSA
#endif
        , GPA_API_OPENGL
    )
);
#endif
