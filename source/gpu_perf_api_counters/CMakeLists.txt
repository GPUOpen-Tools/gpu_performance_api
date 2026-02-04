## Copyright (C) 2018-2026 Advanced Micro Devices, Inc. All rights reserved. ##

set(GPA_PROJECT_NAME GPUPerfAPICounters)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/common.cmake)

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC}
                    ${GPA_SRC_COMMON}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC_COUNTER_GENERATOR})

add_library(GPUPerfAPICounters MODULE)
add_lint_passes(GPUPerfAPICounters)
target_sources(GPUPerfAPICounters PRIVATE
    ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api_counters.h
    gpa_counter_context_handler.h
    gpa_counter_context_handler.cc
    gpu_perf_api_counters.cc
    gpu_perf_api_counters.rc
)

if(NOT ${skipvulkan})
    set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-VK)
    add_definitions(-DENABLE_GPA_VK)
endif()

if(NOT ${skipopengl})
    set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-GL)
    add_definitions(-DENABLE_GPA_GL)
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

target_link_libraries(GPUPerfAPICounters PRIVATE
    GPUPerfAPI-Common
    ${GPA_COMMON_LINK_ARCHIVE_FLAG}
    ${LIB_NAMES}
    ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG}
    $<$<PLATFORM_ID:Linux>:X11>
    AMD::device_info
    AMD::tsingleton
)

ADD_LINKER_FLAGS()

install(TARGETS GPUPerfAPICounters DESTINATION ${GPA_INSTALL_BINDIR} COMPONENT GPUPerfAPI)
install(TARGETS GPUPerfAPICounters DESTINATION ${GPA_INSTALL_TESTDIR} COMPONENT GPATestKit)
