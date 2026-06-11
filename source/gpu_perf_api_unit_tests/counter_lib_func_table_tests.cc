//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit tests for GpaCounterLibGetFuncTable.
//==============================================================================

#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include <gtest/gtest.h>

#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_unit_tests/counter_generator_tests.h"

#ifdef USE_DEBUG_GPA
#include "config_Debug.h"
#else
#include "config_Release.h"
#endif

namespace
{
    /// @brief Load GPUPerfAPICounters and resolve GpaCounterLibGetFuncTable.
    ///
    /// @param [out] lib_guard Receives the loaded library handle; valid only on success.
    /// @param [out] get_func_table Receives the resolved function pointer; valid only on success.
    ///
    /// @return true on success.
    [[nodiscard]] bool ResolveCounterLibGetFuncTable(std::optional<LibHandleGuard>*    lib_guard,
                                                     GpaCounterLibGetFuncTablePtrType* get_func_table)
    {
        const char* lib_name = GpaGetFullPathToCounterLib();
        if (lib_name == nullptr || lib_name[0] == '\0')
        {
            return false;
        }

        LibHandle handle = nullptr;
#ifdef _WIN32
        handle = LoadLibraryA(lib_name);
#else
        handle = dlopen(lib_name, RTLD_NOW);
#endif
        if (handle == nullptr)
        {
            return false;
        }

        *lib_guard      = LibHandleGuard{handle};
        *get_func_table = reinterpret_cast<GpaCounterLibGetFuncTablePtrType>(GetEntryPoint(handle, "GpaCounterLibGetFuncTable"));
        return *get_func_table != nullptr;
    }

}  // namespace

// ---------------------------------------------------------------------------
// GpaCounterLibGetFuncTable — tested by loading GPUPerfAPICounters at runtime.
// ---------------------------------------------------------------------------

class GpaCounterLibFuncTableTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        lib_loaded_ = ResolveCounterLibGetFuncTable(&lib_guard_, &get_func_table_);
        ASSERT_TRUE(lib_loaded_) << "GPUPerfAPICounters could not be loaded; skipping.";
    }

    bool                             lib_loaded_     = false;
    std::optional<LibHandleGuard>    lib_guard_;
    GpaCounterLibGetFuncTablePtrType get_func_table_ = nullptr;
};

TEST_F(GpaCounterLibFuncTableTest, NullPointerReturnsError)
{
    EXPECT_EQ(kGpaStatusErrorNullPointer, get_func_table_(nullptr));
}

TEST_F(GpaCounterLibFuncTableTest, WrongMajorVersionReturnsError)
{
    GpaCounterLibFuncTable table = {};
    table.gpa_counter_lib_major_version = GPA_COUNTER_LIB_FUNC_TABLE_MAJOR_VERSION + 1;
    table.gpa_counter_lib_minor_version = GPA_COUNTER_LIB_FUNC_TABLE_MINOR_VERSION;

    const GpaStatus status = get_func_table_(&table);
    EXPECT_EQ(kGpaStatusErrorLibLoadMajorVersionMismatch, status);
}

TEST_F(GpaCounterLibFuncTableTest, MinorVersionTooLargeReturnsError)
{
    GpaCounterLibFuncTable table = {};
    table.gpa_counter_lib_major_version = GPA_COUNTER_LIB_FUNC_TABLE_MAJOR_VERSION;
    table.gpa_counter_lib_minor_version = GPA_COUNTER_LIB_FUNC_TABLE_MINOR_VERSION + static_cast<GpaUInt32>(sizeof(void*));

    const GpaStatus status = get_func_table_(&table);
    EXPECT_EQ(kGpaStatusErrorLibLoadMinorVersionMismatch, status);
}

TEST_F(GpaCounterLibFuncTableTest, FullSizeCopyPopulatesAllPointers)
{
    GpaCounterLibFuncTable table = {};
    table.gpa_counter_lib_major_version = GPA_COUNTER_LIB_FUNC_TABLE_MAJOR_VERSION;
    table.gpa_counter_lib_minor_version = GPA_COUNTER_LIB_FUNC_TABLE_MINOR_VERSION;

    ASSERT_EQ(kGpaStatusOk, get_func_table_(&table));
    EXPECT_TRUE(table.IsInit()) << "All function pointers must be non-null after a full-size GpaCounterLibGetFuncTable call.";
}

TEST_F(GpaCounterLibFuncTableTest, PartialCopyOldCallerSucceeds)
{
    // Simulate a caller built against an older version of GpaCounterLibFuncTable that is
    // exactly one pointer smaller than the current struct.  The library must:
    //   (a) return kGpaStatusOk,
    //   (b) populate all pointers within the advertised size,
    //   (c) not write past the end of the caller's buffer.

    // Allocate a zero-initialized buffer sized to the full current struct, then stamp a
    // canary pattern over the bytes beyond the "old" caller's advertised size so that any
    // out-of-bounds write by the library will be detected.
    constexpr GpaUInt32 kOldSize = static_cast<GpaUInt32>(sizeof(GpaCounterLibFuncTable)) - static_cast<GpaUInt32>(sizeof(void*));
    std::vector<std::byte> buffer(sizeof(GpaCounterLibFuncTable), std::byte{0x00});

    auto* table                          = reinterpret_cast<GpaCounterLibFuncTable*>(buffer.data());
    table->gpa_counter_lib_major_version = GPA_COUNTER_LIB_FUNC_TABLE_MAJOR_VERSION;
    table->gpa_counter_lib_minor_version = kOldSize;

    const std::byte kCanary = std::byte{0xCD};
    for (GpaUInt32 i = kOldSize; i < static_cast<GpaUInt32>(sizeof(GpaCounterLibFuncTable)); ++i)
    {
        buffer[i] = kCanary;
    }

    ASSERT_EQ(kGpaStatusOk, get_func_table_(table));

    // GpaCounterlibComputeDerivedSpmCounterResults is the pointer immediately before the
    // truncation boundary; it falls within the copied range and must be populated.
    EXPECT_NE(nullptr, table->GpaCounterlibComputeDerivedSpmCounterResults)
        << "GpaCounterLibGetFuncTable must populate all pointers within the caller's advertised minor_version.";

    // Canary bytes past the advertised size must be intact — the library must not write
    // beyond copy_size bytes into the caller's buffer.
    for (GpaUInt32 i = kOldSize; i < static_cast<GpaUInt32>(sizeof(GpaCounterLibFuncTable)); ++i)
    {
        EXPECT_EQ(kCanary, buffer[i]) << "GpaCounterLibGetFuncTable wrote past the caller's advertised buffer size at byte " << i;
    }
}
