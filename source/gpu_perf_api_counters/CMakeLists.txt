## Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPICounters)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/common.cmake)
include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
if(WIN32)
    include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})
endif()

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC}
                    ${GPA_SRC_COMMON}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(HEADER_FILES ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api_counters.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/gpa_counter_context_handler.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/gpu_perf_api_counters.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/gpa_counter_context_handler.cc)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

ADD_SHARED_LIBRARY_NO_EXPORT(${GPA_PROJECT_NAME})
INCLUDE_WIN_RESOURCE(gpu_perf_api_counters)

if(NOT ${skipvulkan})
    set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-VK)
    add_definitions(-DENABLE_GPA_VK)
endif()

if(NOT ${skipopengl})
    set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-GL)
    add_definitions(-DENABLE_GPA_GL)
endif()

if(NOT ${skipopencl})
    set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-CL)
    add_definitions(-DENABLE_GPA_CL)
endif()

if(WIN32)
    if(NOT ${skipdx12})
        set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-DX12)
        add_definitions(-DENABLE_GPA_DX12)
    endif()

    if(NOT ${skipdx11})
        set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-DX11)
        add_definitions(-DENABLE_GPA_DX11)
    endif()
endif()

target_link_libraries(${GPA_PROJECT_NAME}
                      GPUPerfAPI-Common
                      ${GPA_COMMON_LINK_ARCHIVE_FLAG}
                      ${LIB_NAMES}
                      ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG})

ADD_LINKER_FLAGS()