//==============================================================================
// Copyright (c) 2012-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Unit tests for GPUPerfAPI.
//==============================================================================

#if defined(_WIN32) && defined(_DEBUG)
// Enable memory leak detection in debug builds on Windows.
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <gtest/gtest.h>

int main(int argc, char** argv)
{
#if defined(_WIN32) && defined(_DEBUG)
    // Automatically output memory leaks when the application exits.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
