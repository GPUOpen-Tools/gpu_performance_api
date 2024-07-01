## Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

set(DEPTH "./")

message(STATUS "Generating project files for GPA....")
set(GPA_CMAKE_MODULES_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake_modules)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT DEFINED build)
    set(GPA_BUILD_NUMBER 0)
else()
    set(GPA_BUILD_NUMBER ${build})
endif()

include(${GPA_CMAKE_MODULES_DIR}/gpa_version.cmake)
include(${GPA_CMAKE_MODULES_DIR}/defs.cmake)
include(${GPA_CMAKE_MODULES_DIR}/build_flags.cmake)

if (WIN32)
    if (${build-32bit})
        set(PlatformSuffix "-x86")
    else()
        set(PlatformSuffix "-x64")
    endif()
endif()

set(GPA_ALL_OPEN_SOURCE ON)

if(${BUILD_ANDROID})
    include (${GPA_CMAKE_MODULES_DIR}/android.cmake)
endif()

## Define the GPA solution name
project(GPUPerfAPI${PlatformSuffix} VERSION ${GPA_MAJOR_VERSION}.${GPA_MINOR_VERSION} LANGUAGES C CXX)

include(${GPA_CMAKE_MODULES_DIR}/targets.cmake)
message(STATUS "Finished generating project files for GPA.")
