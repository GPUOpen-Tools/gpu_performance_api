## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "./")

message(STATUS "Generating project files for GPA....")
set(GPA_CMAKE_MODULES_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

include(${GPA_CMAKE_MODULES_DIR}/CommonDefs.cmake)
include(${GPA_CMAKE_MODULES_DIR}/BuildFlags.cmake)

if(${AMDT_INTERNAL_BUILD_FLAG})
    include(${CMAKE_COMMON_SRC_GLOBAL_INTERNAL})
endif()

set(GPA_ALL_OPEN_SOURCE ON)

if(${BUILD_ANDROID})
    include (${GPA_CMAKE_MODULES_DIR}/GPA-Android.cmake)

    project(GPUPerfAPI-Full${AMDTInternalSuffix} VERSION ${GPA_MAJOR_VERSION}.${GPA_MINOR_VERSION} LANGUAGES C CXX)
    include(${GPA_CMAKE_MODULES_DIR}/Targets.cmake)

    return()
endif()

## Define the GPA solution name
project(GPUPerfAPI${AMDTInternalSuffix} VERSION ${GPA_MAJOR_VERSION}.${GPA_MINOR_VERSION} LANGUAGES C CXX)

include(${GPA_CMAKE_MODULES_DIR}/Targets.cmake)
message(STATUS "Finished generating project files for GPA.")
