## Copyright (c) 2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

if (NOT DEFINED AMDT_INTERNAL_BUILD_FLAG)
    set(AMDT_INTERNAL_BUILD_FLAG OFF)
endif()

if(${AMDT_INTERNAL_BUILD_FLAG})
    set(AMDTBuild "AMDT_INTERNAL")
    set(AMDTBuildSuffix "-Internal")
    set(AMDTInternalSuffix "-Internal")
endif()