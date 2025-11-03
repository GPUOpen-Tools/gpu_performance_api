## Copyright (C) 2023-2025 Advanced Micro Devices, Inc. All rights reserved. ##

cmake_minimum_required(VERSION 3.10)

## Define Vulkan extension directory
set(AMD_VK_EXT_DIR ${GPA_SRC_THIRD_PARTY}/AmdVkExt)

## Include directory
set(ADDITIONAL_INCLUDE_DIRECTORIES ${ADDITIONAL_INCLUDE_DIRECTORIES}
                                   ${AMD_VK_EXT_DIR})
