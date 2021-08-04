//==============================================================================
// Copyright (c) 2012-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Unit tests for GPUPerfAPI
//==============================================================================

#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    auto result(RUN_ALL_TESTS());
    return result;
}