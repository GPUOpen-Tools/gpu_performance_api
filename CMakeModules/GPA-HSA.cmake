## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

if(${AMDTPlatform} STREQUAL "x64")
    set(HSAPlatform "x86_64")
endif()

if(${GPA_ALL_OPEN_SOURCE})
    if(NOT WIN32)
        # HSA path
        find_file(HSA_PATH "hsa.h"
                  HINTS "/opt/rocm/hsa/include/hsa"
                  NO_DEFAULT_PATH)
        if(${HSA_PATH} STREQUAL "HSA_PATH-NOTFOUND")
            message("CMake: HSA not found")
        else()
            set(ADDITIONAL_INCLUDE_DIRECTORIES ${ADDITIONAL_INCLUDE_DIRECTORIES}
                                                "/opt/rocm/hsa/include/hsa")
        endif()

        # ROCm path
        find_file(ROCM_PATH "rocprofiler.h"
                  HINTS "/opt/rocm/include"
                  NO_DEFAULT_PATH)
        if(${ROCM_PATH} STREQUAL "ROCM_PATH-NOTFOUND")
            message("CMake: ROCm Profiler not found")
        else()
            set(ADDITIONAL_INCLUDE_DIRECTORIES ${ADDITIONAL_INCLUDE_DIRECTORIES}
                                                "/opt/rocm/include")
        endif()
    endif()
else()
    include(${CMAKE_COMMON_LIB_GLOBAL_AMD_HSA_NO_LIB})
endif()