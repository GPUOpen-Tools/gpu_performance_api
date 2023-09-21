//==============================================================================
// Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Unit tests to validate error handling/reporting from GPA APIs
///         These tests are meant to exercise the GPA API without actually
///         creating valid contexts or executing any workloads. Additional unit
///         testing of the APIs is done with real workloads in the GPA
///         functional test suite.
//==============================================================================

#include <gtest/gtest.h>

#include "gpu_performance_api/gpu_perf_api.h"
#include "gpu_performance_api/gpu_perf_api_interface_loader.h"

#include "gpu_perf_api_common/gpa_common_defs.h"

/// @brief GPA API Error Tests.
class GpaApiErrorTest : public ::testing::TestWithParam<GpaApiType>
{
public:
    /// @brief Constructor.
    GpaApiErrorTest()
        : ::testing::TestWithParam<GpaApiType>()
    {
    }

    /// @brief Destructor.
    ~GpaApiErrorTest()
    {
    }

    /// @brief Create and set up test resources.
    static void SetUpTestCase();

    /// @brief Tear down and cleanup test resources.
    static void TearDownTestCase();

    /// @brief Create and set up test resources.
    virtual void SetUp();

    /// @brief Tear down and cleanup test resources.
    virtual void TearDown();

protected:
    /// @brief GPA Logging callback function.
    ///
    /// @param [in] logging_type The type of log message being reported.
    /// @param [in] log_message The log message.
    static void LogFunction(GpaLoggingType logging_type, const char* log_message);

    /// A GPA function table.
    const GpaFunctionTable* gpa_function_table_;

    /// An API that is supposed by GPA.
    GpaApiType api_;

private:
    /// Map of the API names.
    static std::map<GpaApiType, const char*> api_name_map;
};

std::map<GpaApiType, const char*> GpaApiErrorTest::api_name_map;

void GpaApiErrorTest::SetUpTestCase()
{
    api_name_map[kGpaApiDirectx11] = "DX11";
    api_name_map[kGpaApiDirectx12] = "DX12";
    api_name_map[kGpaApiOpengl]    = "OpenGL";
    api_name_map[kGpaApiOpencl]    = "OpenCL";
    api_name_map[kGpaApiVulkan]    = "Vulkan";
    api_name_map[kGpaApiNoSupport] = "ApiNotSupported";
}

void GpaApiErrorTest::TearDownTestCase()
{
    GpaApiManager::DeleteInstance();
}

void GpaApiErrorTest::SetUp()
{
    api_ = GetParam();

    ASSERT_NE(0u, api_name_map.count(api_)) << "API name out of range.";
    const char* api_name = api_name_map.find(api_)->second;

    EXPECT_EQ(kGpaStatusOk, GpaApiManager::Instance()->LoadApi(api_)) << "GPAApiManager failed to load API: " << api_name;
    gpa_function_table_ = GpaApiManager::Instance()->GetFunctionTable(GetParam());
    ASSERT_NE(nullptr, gpa_function_table_);

    GpaStatus status = gpa_function_table_->GpaRegisterLoggingCallback(kGpaLoggingAll, LogFunction);
    EXPECT_EQ(kGpaStatusOk, status);
}

void GpaApiErrorTest::TearDown()
{
    GpaApiManager::Instance()->UnloadApi(api_);
}

void GpaApiErrorTest::LogFunction(GpaLoggingType logging_type, const char* log_message)
{
    UNREFERENCED_PARAMETER(logging_type);
    ASSERT_NE(nullptr, log_message);

    std::string message(log_message);
    ASSERT_LT(0ul, message.length());
    EXPECT_EQ('.', message[message.length() - 1]);
}

TEST_P(GpaApiErrorTest, TestGPA_RegisterLoggingCallback)
{
    GpaStatus status = gpa_function_table_->GpaRegisterLoggingCallback(kGpaLoggingError, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaRegisterLoggingCallback(kGpaLoggingNone, nullptr);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaRegisterLoggingCallback(kGpaLoggingAll, LogFunction);
    EXPECT_EQ(kGpaStatusOk, status);
}

TEST_P(GpaApiErrorTest, TestGPA_InitializeAndDestroy)
{
    GpaStatus status = gpa_function_table_->GpaDestroy();
    EXPECT_EQ(kGpaStatusErrorGpaNotInitialized, status);

    status = gpa_function_table_->GpaInitialize(kGpaInitializeDefaultBit);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaInitialize(kGpaInitializeDefaultBit);
    EXPECT_EQ(kGpaStatusErrorGpaAlreadyInitialized, status);

    status = gpa_function_table_->GpaDestroy();
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaDestroy();
    EXPECT_EQ(kGpaStatusErrorGpaNotInitialized, status);

    status = gpa_function_table_->GpaInitialize(GPA_INITIALIZE_SIMULTANEOUS_QUEUES_ENABLE_BIT);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaDestroy();
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaInitialize(0xBADF00D);
    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);
}

TEST_P(GpaApiErrorTest, TestGPA_OpenAndCloseContext)
{
    GpaContextId bad_context_id = reinterpret_cast<GpaContextId>(0xBADF00D);

    GpaStatus status = gpa_function_table_->GpaInitialize(kGpaInitializeDefaultBit);
    ASSERT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaCloseContext(nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaContextId context_id;
    status = gpa_function_table_->GpaOpenContext(nullptr, kGpaOpenContextDefaultBit, &context_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCloseContext(bad_context_id);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);
}

TEST_P(GpaApiErrorTest, TestGPA_ContextInterrogation)
{
    GpaContextId bad_context_id = reinterpret_cast<GpaContextId>(0xBADF00D);

    GpaStatus status = gpa_function_table_->GpaGetSupportedSampleTypes(nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaContextSampleTypeFlags sample_types;
    status = gpa_function_table_->GpaGetSupportedSampleTypes(nullptr, &sample_types);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSupportedSampleTypes(bad_context_id, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSupportedSampleTypes(bad_context_id, &sample_types);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetDeviceAndRevisionId(nullptr, nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 device_id   = 0;
    GpaUInt32 revision_id = 0;
    status                = gpa_function_table_->GpaGetDeviceAndRevisionId(nullptr, &device_id, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDeviceAndRevisionId(nullptr, nullptr, &revision_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDeviceAndRevisionId(nullptr, &device_id, &revision_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDeviceName(nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    const char* device_name = nullptr;
    status                  = gpa_function_table_->GpaGetDeviceName(nullptr, &device_name);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDeviceAndRevisionId(bad_context_id, nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    device_id   = 0;
    revision_id = 0;
    status      = gpa_function_table_->GpaGetDeviceAndRevisionId(bad_context_id, &device_id, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDeviceAndRevisionId(bad_context_id, nullptr, &revision_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDeviceAndRevisionId(bad_context_id, &device_id, &revision_id);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetDeviceName(bad_context_id, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    device_name = nullptr;
    status      = gpa_function_table_->GpaGetDeviceName(bad_context_id, &device_name);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    GpaHwGeneration hw_generation;
    status = gpa_function_table_->GpaGetDeviceGeneration(nullptr, &hw_generation);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDeviceGeneration(bad_context_id, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDeviceGeneration(nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDeviceGeneration(bad_context_id, &hw_generation);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);
}

TEST_P(GpaApiErrorTest, TestGPA_CounterInterrogation)
{
    GpaContextId bad_context_id = reinterpret_cast<GpaContextId>(0xBADF00D);

    GpaStatus status = gpa_function_table_->GpaGetNumCounters(nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 num_counters;
    status = gpa_function_table_->GpaGetNumCounters(nullptr, &num_counters);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetNumCounters(bad_context_id, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetNumCounters(bad_context_id, &num_counters);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterName(nullptr, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    const char* counter_name = nullptr;
    status                   = gpa_function_table_->GpaGetCounterName(nullptr, 0, &counter_name);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterName(nullptr, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_name = nullptr;
    status       = gpa_function_table_->GpaGetCounterName(nullptr, static_cast<GpaUInt32>(-1), &counter_name);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterName(bad_context_id, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_name = nullptr;
    status       = gpa_function_table_->GpaGetCounterName(bad_context_id, 0, &counter_name);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterName(bad_context_id, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_name = nullptr;
    status       = gpa_function_table_->GpaGetCounterName(bad_context_id, static_cast<GpaUInt32>(-1), &counter_name);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterIndex(nullptr, nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 index = 0;
    status          = gpa_function_table_->GpaGetCounterIndex(nullptr, nullptr, &index);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterIndex(nullptr, "foo", nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    index  = 0;
    status = gpa_function_table_->GpaGetCounterIndex(nullptr, "GPUTime", &index);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    index  = 0;
    status = gpa_function_table_->GpaGetCounterIndex(nullptr, "Wavefronts", &index);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterIndex(bad_context_id, nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    index  = 0;
    status = gpa_function_table_->GpaGetCounterIndex(bad_context_id, nullptr, &index);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterIndex(bad_context_id, "foo", nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    index  = 0;
    status = gpa_function_table_->GpaGetCounterIndex(bad_context_id, "GPUTime", &index);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    index  = 0;
    status = gpa_function_table_->GpaGetCounterIndex(bad_context_id, "Wavefronts", &index);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterGroup(nullptr, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    const char* counter_group = nullptr;
    status                    = gpa_function_table_->GpaGetCounterGroup(nullptr, 0, &counter_group);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterGroup(nullptr, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_group = nullptr;
    status        = gpa_function_table_->GpaGetCounterGroup(nullptr, static_cast<GpaUInt32>(-1), &counter_group);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterGroup(bad_context_id, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_group = nullptr;
    status        = gpa_function_table_->GpaGetCounterGroup(bad_context_id, 0, &counter_group);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterGroup(bad_context_id, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_group = nullptr;
    status        = gpa_function_table_->GpaGetCounterGroup(bad_context_id, static_cast<GpaUInt32>(-1), &counter_group);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterDescription(nullptr, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    const char* counter_description = nullptr;
    status                          = gpa_function_table_->GpaGetCounterDescription(nullptr, 0, &counter_description);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterDescription(nullptr, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_description = nullptr;
    status              = gpa_function_table_->GpaGetCounterDescription(nullptr, static_cast<GpaUInt32>(-1), &counter_description);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterDescription(bad_context_id, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_description = nullptr;
    status              = gpa_function_table_->GpaGetCounterDescription(bad_context_id, 0, &counter_description);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterDescription(bad_context_id, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_description = nullptr;
    status              = gpa_function_table_->GpaGetCounterDescription(bad_context_id, static_cast<GpaUInt32>(-1), &counter_description);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterDataType(nullptr, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaDataType counter_data_type = kGpaDataTypeLast;
    status                        = gpa_function_table_->GpaGetCounterDataType(nullptr, 0, &counter_data_type);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterDataType(nullptr, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_data_type = kGpaDataTypeLast;
    status            = gpa_function_table_->GpaGetCounterDataType(nullptr, static_cast<GpaUInt32>(-1), &counter_data_type);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterDataType(bad_context_id, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_data_type = kGpaDataTypeLast;
    status            = gpa_function_table_->GpaGetCounterDataType(bad_context_id, 0, &counter_data_type);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterDataType(bad_context_id, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_data_type = kGpaDataTypeLast;
    status            = gpa_function_table_->GpaGetCounterDataType(bad_context_id, static_cast<GpaUInt32>(-1), &counter_data_type);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterUsageType(nullptr, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUsageType counter_usage_type = kGpaUsageTypeLast;
    status                          = gpa_function_table_->GpaGetCounterUsageType(nullptr, 0, &counter_usage_type);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterUsageType(nullptr, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_usage_type = kGpaUsageTypeLast;
    status             = gpa_function_table_->GpaGetCounterUsageType(nullptr, static_cast<GpaUInt32>(-1), &counter_usage_type);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterUsageType(bad_context_id, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_usage_type = kGpaUsageTypeLast;
    status             = gpa_function_table_->GpaGetCounterUsageType(bad_context_id, 0, &counter_usage_type);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterUsageType(bad_context_id, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_usage_type = kGpaUsageTypeLast;
    status             = gpa_function_table_->GpaGetCounterUsageType(bad_context_id, static_cast<GpaUInt32>(-1), &counter_usage_type);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterUuid(nullptr, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUuid counter_uuid = {};
    status               = gpa_function_table_->GpaGetCounterUuid(nullptr, 0, &counter_uuid);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterUuid(nullptr, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_uuid = {};
    status       = gpa_function_table_->GpaGetCounterUuid(nullptr, static_cast<GpaUInt32>(-1), &counter_uuid);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterUuid(bad_context_id, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_uuid = {};
    status       = gpa_function_table_->GpaGetCounterUuid(bad_context_id, 0, &counter_uuid);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterUuid(bad_context_id, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    counter_uuid = {};
    status       = gpa_function_table_->GpaGetCounterUuid(bad_context_id, static_cast<GpaUInt32>(-1), &counter_uuid);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterSampleType(nullptr, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaCounterSampleType sample_type;
    status = gpa_function_table_->GpaGetCounterSampleType(nullptr, 0, &sample_type);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterSampleType(nullptr, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterSampleType(nullptr, static_cast<GpaUInt32>(-1), &sample_type);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterSampleType(bad_context_id, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterSampleType(bad_context_id, 0, &sample_type);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetCounterSampleType(bad_context_id, static_cast<GpaUInt32>(-1), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetCounterSampleType(bad_context_id, static_cast<GpaUInt32>(-1), &sample_type);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaGetDataTypeAsStr(kGpaDataTypeFloat64, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDataTypeAsStr(kGpaDataTypeUint64, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDataTypeAsStr(kGpaDataTypeLast, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetDataTypeAsStr(static_cast<GpaDataType>(0xFFFF), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    const char* type_string = nullptr;
    status                  = gpa_function_table_->GpaGetDataTypeAsStr(kGpaDataTypeFloat64, &type_string);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaGetDataTypeAsStr(kGpaDataTypeUint64, &type_string);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaGetDataTypeAsStr(kGpaDataTypeLast, &type_string);
    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

    status = gpa_function_table_->GpaGetDataTypeAsStr(static_cast<GpaDataType>(0xFFFF), &type_string);
    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeRatio, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypePercentage, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeCycles, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeMilliseconds, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeBytes, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeItems, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeKilobytes, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeLast, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(static_cast<GpaUsageType>(0xFFFF), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    const char* usage_string = nullptr;
    status                   = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeRatio, &usage_string);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypePercentage, &usage_string);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeCycles, &usage_string);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeMilliseconds, &usage_string);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeBytes, &usage_string);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeItems, &usage_string);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeKilobytes, &usage_string);
    EXPECT_EQ(kGpaStatusOk, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(kGpaUsageTypeLast, &usage_string);
    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

    status = gpa_function_table_->GpaGetUsageTypeAsStr(static_cast<GpaUsageType>(0xFFFF), &usage_string);
    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);
}

TEST_P(GpaApiErrorTest, TestGPA_SessionHandling)
{
    GpaContextId bad_context_id = reinterpret_cast<GpaContextId>(0xBADF00D);

    GpaStatus status = gpa_function_table_->GpaCreateSession(nullptr, kGpaSessionSampleTypeDiscreteCounter, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaSessionId session_id;
    status = gpa_function_table_->GpaCreateSession(nullptr, kGpaSessionSampleTypeDiscreteCounter, &session_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCreateSession(nullptr, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCreateSession(nullptr, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER, &session_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCreateSession(nullptr, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCreateSession(nullptr, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT, &session_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCreateSession(nullptr, static_cast<GpaSessionSampleType>(0xFFFFFFFF), &session_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCreateSession(bad_context_id, kGpaSessionSampleTypeDiscreteCounter, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCreateSession(bad_context_id, kGpaSessionSampleTypeDiscreteCounter, &session_id);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaCreateSession(bad_context_id, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCreateSession(bad_context_id, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER, &session_id);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaCreateSession(bad_context_id, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCreateSession(bad_context_id, GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT, &session_id);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaCreateSession(bad_context_id, static_cast<GpaSessionSampleType>(0xFFFFFFFF), &session_id);
    EXPECT_EQ(kGpaStatusErrorContextNotFound, status);

    status = gpa_function_table_->GpaDeleteSession(nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    session_id = reinterpret_cast<GpaSessionId>(0xBADF00D);
    status     = gpa_function_table_->GpaDeleteSession(session_id);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaBeginSession(nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaBeginSession(session_id);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaEndSession(nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaEndSession(session_id);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);
}

TEST_P(GpaApiErrorTest, TestGPA_CounterScheduling)
{
    GpaSessionId bad_session_id = reinterpret_cast<GpaSessionId>(0xBADF00D);

    GpaStatus status = gpa_function_table_->GpaEnableCounter(nullptr, 0);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaEnableCounter(nullptr, 0x7FFFFFFF);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaEnableCounter(bad_session_id, 0);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaEnableCounter(bad_session_id, 0x7FFFFFFF);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaDisableCounter(nullptr, 0);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaDisableCounter(nullptr, 0x7FFFFFFF);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaDisableCounter(bad_session_id, 0);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaDisableCounter(bad_session_id, 0x7FFFFFFF);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaEnableCounterByName(nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaEnableCounterByName(nullptr, "noCounter");
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaEnableCounterByName(nullptr, "GPUTime");
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaEnableCounterByName(nullptr, "Wavefronts");
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaEnableCounterByName(bad_session_id, nullptr);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaEnableCounterByName(bad_session_id, "noCounter");
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaEnableCounterByName(bad_session_id, "GPUTime");
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaEnableCounterByName(bad_session_id, "Wavefronts");
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaDisableCounterByName(nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaDisableCounterByName(nullptr, "noCounter");
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaDisableCounterByName(nullptr, "GPUTime");
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaDisableCounterByName(nullptr, "Wavefronts");
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaDisableCounterByName(bad_session_id, nullptr);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaDisableCounterByName(bad_session_id, "noCounter");
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaDisableCounterByName(bad_session_id, "GPUTime");
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaDisableCounterByName(bad_session_id, "Wavefronts");
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaEnableAllCounters(nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaEnableAllCounters(bad_session_id);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaDisableAllCounters(nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaDisableAllCounters(bad_session_id);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);
}

TEST_P(GpaApiErrorTest, TestGPA_QueryCounterScheduling)
{
    GpaSessionId bad_session_id = reinterpret_cast<GpaSessionId>(0xBADF00D);

    GpaStatus status = gpa_function_table_->GpaGetPassCount(nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 pass_count = 0;
    status               = gpa_function_table_->GpaGetPassCount(nullptr, &pass_count);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetPassCount(bad_session_id, nullptr);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    pass_count = 0;
    status     = gpa_function_table_->GpaGetPassCount(bad_session_id, &pass_count);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaGetNumEnabledCounters(nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 num_enabled_counters = 0;
    status                         = gpa_function_table_->GpaGetNumEnabledCounters(nullptr, &num_enabled_counters);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetNumEnabledCounters(bad_session_id, nullptr);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    num_enabled_counters = 0;
    status               = gpa_function_table_->GpaGetNumEnabledCounters(bad_session_id, &num_enabled_counters);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaGetEnabledIndex(nullptr, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 enabled_index = 0;
    status                  = gpa_function_table_->GpaGetEnabledIndex(nullptr, 0, &enabled_index);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetEnabledIndex(nullptr, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    enabled_index = 0;
    status        = gpa_function_table_->GpaGetEnabledIndex(nullptr, 0x7FFFFFFF, &enabled_index);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetEnabledIndex(bad_session_id, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    enabled_index = 0;
    status        = gpa_function_table_->GpaGetEnabledIndex(bad_session_id, 0, &enabled_index);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaGetEnabledIndex(bad_session_id, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    enabled_index = 0;
    status        = gpa_function_table_->GpaGetEnabledIndex(bad_session_id, 0x7FFFFFFF, &enabled_index);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaIsCounterEnabled(nullptr, 0);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaIsCounterEnabled(nullptr, 0x7FFFFFFF);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaIsCounterEnabled(bad_session_id, 0);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaIsCounterEnabled(bad_session_id, 0x7FFFFFFF);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);
}

TEST_P(GpaApiErrorTest, TestGPA_SampleHandling)
{
    GpaSessionId     bad_session                = reinterpret_cast<GpaSessionId>(0xBADF00D);
    GpaCommandListId bad_command_list           = reinterpret_cast<GpaCommandListId>(0xBADF00D);
    GpaCommandListId bad_secondary_command_list = reinterpret_cast<GpaCommandListId>(0xBA4F00D);

    GpaStatus status = gpa_function_table_->GpaBeginCommandList(nullptr, 0, nullptr, kGpaCommandListNone, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaBeginCommandList(nullptr, 0x7FFFFFFF, this, kGpaCommandListNone, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaBeginCommandList(nullptr, 0x7FFFFFFF, nullptr, kGpaCommandListPrimary, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaCommandListId command_list_id;
    status = gpa_function_table_->GpaBeginCommandList(nullptr, 0x7FFFFFFF, this, kGpaCommandListPrimary, &command_list_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaBeginCommandList(bad_session, 0x7FFFFFFF, this, kGpaCommandListPrimary, &command_list_id);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaBeginCommandList(bad_session, 0, nullptr, kGpaCommandListNone, nullptr);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaBeginCommandList(bad_session, 0x7FFFFFFF, this, kGpaCommandListNone, nullptr);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaBeginCommandList(bad_session, 0x7FFFFFFF, nullptr, kGpaCommandListPrimary, nullptr);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaBeginCommandList(bad_session, 0x7FFFFFFF, this, kGpaCommandListPrimary, &command_list_id);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaEndCommandList(nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaEndCommandList(bad_command_list);
    EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);

    status = gpa_function_table_->GpaBeginSample(0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaBeginSample(0, bad_command_list);
    EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);

    status = gpa_function_table_->GpaEndSample(nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaEndSample(bad_command_list);
    EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);

    status = gpa_function_table_->GpaContinueSampleOnCommandList(0, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorNullPointer, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaContinueSampleOnCommandList(0, bad_command_list);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaContinueSampleOnCommandList(0x7FFFFFFF, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorNullPointer, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaContinueSampleOnCommandList(0x7FFFFFFF, bad_command_list);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(nullptr, nullptr, 0, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorNullPointer, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(bad_command_list, nullptr, 0, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    GpaCommandListId secondary_command_list_id;
    status = gpa_function_table_->GpaBeginCommandList(nullptr, 0x7FFFFFFF, this, kGpaCommandListPrimary, &secondary_command_list_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaCopySecondarySamples(bad_command_list, bad_command_list, 0, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(bad_command_list, bad_secondary_command_list, 0, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(nullptr, bad_secondary_command_list, 0, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorNullPointer, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(nullptr, nullptr, 0x7FFFFFFF, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorNullPointer, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(bad_command_list, nullptr, 0x7FFFFFFF, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(bad_command_list, bad_secondary_command_list, 0x7FFFFFFF, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(nullptr, bad_secondary_command_list, 0x7FFFFFFF, nullptr);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorNullPointer, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    GpaUInt32 new_sample_ids = 0;
    status                   = gpa_function_table_->GpaCopySecondarySamples(nullptr, nullptr, 0, &new_sample_ids);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorNullPointer, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(bad_command_list, nullptr, 0, &new_sample_ids);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(bad_command_list, bad_command_list, 0, &new_sample_ids);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(nullptr, bad_command_list, 0, &new_sample_ids);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorNullPointer, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(nullptr, nullptr, 1, &new_sample_ids);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorNullPointer, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(bad_command_list, nullptr, 1, &new_sample_ids);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(bad_command_list, bad_command_list, 1, &new_sample_ids);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorCommandListNotFound, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaCopySecondarySamples(nullptr, bad_command_list, 1, &new_sample_ids);

    if (kGpaApiDirectx12 == api_ || kGpaApiVulkan == api_)
    {
        EXPECT_EQ(kGpaStatusErrorNullPointer, status);
    }
    else
    {
        EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
    }

    status = gpa_function_table_->GpaGetSampleCount(nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 sample_count;
    status = gpa_function_table_->GpaGetSampleCount(nullptr, &sample_count);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleCount(bad_session, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleCount(bad_session, &sample_count);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaGetSampleId(nullptr, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 sample_id;
    status = gpa_function_table_->GpaGetSampleId(nullptr, 0, &sample_id);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleId(bad_session, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleId(bad_session, 0, &sample_id);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);
}

TEST_P(GpaApiErrorTest, TestGPA_QueryResults)
{
    GpaSessionId bad_session = reinterpret_cast<GpaSessionId>(0xBADF00D);

    GpaStatus status = gpa_function_table_->GpaIsPassComplete(nullptr, 0);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaIsPassComplete(nullptr, 0x7FFFFFFF);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaIsPassComplete(bad_session, 0);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaIsPassComplete(bad_session, 0x7FFFFFFF);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaIsSessionComplete(nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaIsSessionComplete(bad_session);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaGetSampleResultSize(nullptr, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResultSize(nullptr, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    size_t result_size = 0;
    status             = gpa_function_table_->GpaGetSampleResultSize(nullptr, 0, &result_size);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResultSize(nullptr, 0x7FFFFFFF, &result_size);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResultSize(bad_session, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResultSize(bad_session, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResultSize(bad_session, 0, &result_size);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaGetSampleResultSize(bad_session, 0x7FFFFFFF, &result_size);
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaGetSampleResult(nullptr, 0, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResult(nullptr, 0x7FFFFFFF, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResult(nullptr, 0, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResult(nullptr, 0, 0, reinterpret_cast<void*>(this));
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResult(nullptr, 0x7FFFFFFF, 0, reinterpret_cast<void*>(this));
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResult(nullptr, 0, 0x7FFFFFFF, reinterpret_cast<void*>(this));
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResult(bad_session, 0, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResult(bad_session, 0x7FFFFFFF, 0, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResult(bad_session, 0, 0x7FFFFFFF, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    status = gpa_function_table_->GpaGetSampleResult(bad_session, 0, 0, reinterpret_cast<void*>(this));
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaGetSampleResult(bad_session, 0x7FFFFFFF, 0, reinterpret_cast<void*>(this));
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);

    status = gpa_function_table_->GpaGetSampleResult(bad_session, 0, 0x7FFFFFFF, reinterpret_cast<void*>(this));
    EXPECT_EQ(kGpaStatusErrorSessionNotFound, status);
}

TEST_P(GpaApiErrorTest, TestGPA_StatusErrorQuery)
{
    std::string gpa_prefix_string("GPA Status:");
    std::string status_string = gpa_function_table_->GpaGetStatusAsStr(kGpaStatusOk);
    EXPECT_NE(0, status_string.compare("GPA Status: Unknown Status."));
    EXPECT_EQ(0, status_string.compare(0, gpa_prefix_string.length(), gpa_prefix_string));
    status_string = gpa_function_table_->GpaGetStatusAsStr(kGpaStatusMax);
    EXPECT_NE(0, status_string.compare("GPA Status: Unknown Status."));
    EXPECT_EQ(0, status_string.compare(0, gpa_prefix_string.length(), gpa_prefix_string));
    status_string = gpa_function_table_->GpaGetStatusAsStr(static_cast<GpaStatus>(1024));
    EXPECT_EQ(0, status_string.compare("GPA Status: Unknown Status."));

    gpa_prefix_string = "GPA Error:";
    status_string     = gpa_function_table_->GpaGetStatusAsStr(kGpaStatusErrorNullPointer);
    EXPECT_NE(0, status_string.compare("GPA Error: Unknown Error."));
    EXPECT_EQ(0, status_string.compare(0, gpa_prefix_string.length(), gpa_prefix_string));
    status_string = gpa_function_table_->GpaGetStatusAsStr(kGpaStatusMin);
    EXPECT_NE(0, status_string.compare("GPA Error: Unknown Error."));
    EXPECT_EQ(0, status_string.compare(0, gpa_prefix_string.length(), gpa_prefix_string));
    status_string = gpa_function_table_->GpaGetStatusAsStr(static_cast<GpaStatus>(-1024));
    EXPECT_EQ(0, status_string.compare("GPA Error: Unknown Error."));
}

TEST_P(GpaApiErrorTest, TestGPA_APIVersion)
{
    GpaStatus status = gpa_function_table_->GpaGetVersion(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 major_version = 0;
    status                  = gpa_function_table_->GpaGetVersion(&major_version, nullptr, nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 minor_version = 0;
    status                  = gpa_function_table_->GpaGetVersion(&major_version, &minor_version, nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 build = 0;
    status          = gpa_function_table_->GpaGetVersion(&major_version, &minor_version, &build, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

    GpaUInt32 update_version = 0;
    status                   = gpa_function_table_->GpaGetVersion(&major_version, &minor_version, &build, &update_version);
    EXPECT_EQ(kGpaStatusOk, status);
}

TEST_P(GpaApiErrorTest, TestGPA_GPAFunctionTable)
{
    GpaStatus status = gpa_function_table_->GpaGetFuncTable(nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, status)
        << "GpaGetFuncTable should return kGpaStatusErrorNullPointer if passed a nullptr";

    GpaFunctionTable* function_table = nullptr;

    function_table = new GpaFunctionTable();
    status         = gpa_function_table_->GpaGetFuncTable(reinterpret_cast<void*>(function_table));
    ASSERT_EQ(kGpaStatusOk, status) << "GpaGetFuncTable should return kGpaStatusOk upon success.";
    EXPECT_EQ(function_table->major_version, GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER)
        << "A GpaFunctionTable properly initialized by GpaGetFuncTable should contain the correct "
           "major version number.";
    EXPECT_EQ(function_table->minor_version, GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER)
        << "A GpaFunctionTable properly initialized by GpaGetFuncTable should contain the correct "
           "minor version number.";

    // The table consists of a certain number of void*'s for each function pointer, as well as
    // two GpaUInt32's for the major_version and minor_version.
    const std::size_t EXPECTED_TABLE_SIZE = (49 * sizeof(void*)) + (2 * sizeof(GpaUInt32));
    EXPECT_EQ(function_table->minor_version, EXPECTED_TABLE_SIZE) << "A GpaFunctionTable properly "
        "initialized by GpaGetFuncTable should contain the expected number of entry points; "
        "additional entry should be appended to the end of the function table in "
        "gpu_perf_api_functions.h to ensure binary compatibility with applications linked against "
        "older versions of GPA.";

    function_table->major_version = 1024;
    function_table->minor_version = 0;
    status                        = gpa_function_table_->GpaGetFuncTable(reinterpret_cast<void*>(function_table));
    ASSERT_EQ(kGpaStatusErrorLibLoadMajorVersionMismatch, status)
        << "GpaGetFuncTable should return kGpaStatusErrorLibLoadMajorVersionMismatch when the "
           "minor_version of the GpaFunctionTable it receives is set to 0.";
    EXPECT_EQ(function_table->major_version, GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER)
        << "GpaGetFuncTable should set the major_version of a GpaFunctionTable to the correct "
           "major version number even if initialized to an incorrect value.";
    EXPECT_EQ(function_table->minor_version, GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER)
        << "GpaGetFuncTable should set the minor_version of a GpaFunctionTable to the correct "
           "minor version number even if initialized to an incorrect value.";

    function_table->major_version = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
    function_table->minor_version = GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER + 1024;
    status                        = function_table->GpaGetFuncTable(reinterpret_cast<void*>(function_table));
    ASSERT_EQ(kGpaStatusErrorLibLoadMinorVersionMismatch, status)
        << "GpaGetFuncTable should return kGpaStatusErrorLibLoadMajorVersionMismatch when the "
           "minor_version of the GpaFunctionTable it receives is set to a value greater than expected.";
    EXPECT_EQ(function_table->major_version, GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER)
        << "GpaGetFuncTable should set the major_version of a GpaFunctionTable to the correct "
           "major version number even if initialized to an incorrect value.";
    EXPECT_EQ(function_table->minor_version, GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER)
        << "GpaGetFuncTable should set the minor_version of a GpaFunctionTable to the correct "
           "minor version number even if initialized to an incorrect value.";

    delete function_table;
    function_table = new GpaFunctionTable();
    function_table->minor_version -= sizeof(void*);
    status = gpa_function_table_->GpaGetFuncTable(reinterpret_cast<void*>(function_table));
    ASSERT_EQ(kGpaStatusOk, status)
        << "GpaGetFuncTable should return kGpaStatusOk when the minor_version of the "
           "GpaFunctionTable it receives is set to a value less than expected.";
    EXPECT_EQ(gpa_function_table_->major_version, GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER)
        << "GpaGetFuncTable should set the major_version of a GpaFunctionTable to the correct "
           "major version number even if initialized to an incorrect value.";
    EXPECT_EQ(gpa_function_table_->minor_version, GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER)
        << "GpaGetFuncTable should set the minor_version of a GpaFunctionTable to the correct "
           "minor version number even if initialized to an incorrect value.";

    // Note: Whenever GPA function table changes, we need to update this with the last function in the GPA function table
    EXPECT_EQ(nullptr, function_table->GpaGetDeviceGeneration)
        << "When GpaGetFuncTable receives a GpaFunctionTable with a minor_version set to a value "
           "that is less than the size of the internal GPA function table, then all entries in the "
           "GpaFunctionTable beyond this value shall be set to a nullptr.";

    delete function_table;
}

#ifdef _WIN32
INSTANTIATE_TEST_CASE_P(WindowsAPI, GpaApiErrorTest, ::testing::Values(kGpaApiDirectx11, kGpaApiDirectx12, kGpaApiVulkan, kGpaApiOpencl, kGpaApiOpengl));
#else
INSTANTIATE_TEST_CASE_P(LinuxAPI, GpaApiErrorTest, ::testing::Values(kGpaApiVulkan, kGpaApiOpengl));
#endif
