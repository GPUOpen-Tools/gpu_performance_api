## Copyright (C) 2018-2025 Advanced Micro Devices, Inc. All rights reserved. ##

set(CMAKE_FOLDER "Tests")

set(GPA_PROJECT_NAME GPUPerfAPIUnitTests)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/common.cmake)

include(${CMAKE_COMMON_SRC_GLOBAL_AMD_DX_EXT})
include(${CMAKE_COMMON_SRC_GLOBAL_AMD_VK_EXT})
include(${GPA_CMAKE_MODULES_DIR}/gpa_vulkan.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC}
                    ${GPA_SRC_TESTS}/counters
                    ${ADDITIONAL_DERIVED_COUNTERS_INCLUDE})

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/api_error_tests.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/counter_scheduler_tests.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/gpa_interface_loader_tests.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/gpu_perf_api_loader_tests.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/gpu_perf_api_unit_tests.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/counter_generator_tests.cc
                 ${GPA_SRC_COUNTER_GENERATOR}/gpa_derived_counter_evaluator.hpp
                 ${ADDITIONAL_UNIT_TEST_SOURCES})

if(NOT ${skipopengl})
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/counter_generator_gl_tests.cc)
endif()

if(NOT ${skipvulkan})
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/counter_generator_vk_tests.cc)
endif()

if(WIN32)
    if(NOT ${skipdx12})
        set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/counter_generator_dx12_tests.cc)
    endif()

    if(NOT ${skipdx11})
        set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/counter_generator_dx11_tests.cc)
    endif()
endif()

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/counter_generator_tests.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/counters/gpa_counter_desc.h)

foreach(API GL DX11 DX12 VK)
    if(NOT WIN32 AND (${API} STREQUAL "DX11" OR ${API} STREQUAL DX12))
        continue()
    endif()

    if(EXISTS ${GPA_AUTOGEN_SRC_TESTS})
        string(TOLOWER ${API} API_LOWER_STR)
        include (${GPA_AUTOGEN_SRC_TESTS}/counters/public_derived_counters_${API_LOWER_STR}.cmake)
        set(COUNTER_FILES ${COUNTER_FILES}
                          ${PUBLIC_DERIVED_COUNTERS_API_HEADERS_${API}}
                          ${PUBLIC_DERIVED_COUNTERS_API_SRC_${API}}
                          ${ADDITIONAL_DERIVED_COUNTERS_API_HEADERS_${API}}
                          ${ADDITIONAL_DERIVED_COUNTERS_API_SRC_${API}})
        if(WIN32)
            source_group("Source Files\\auto_generated\\${API}" FILES ${PUBLIC_DERIVED_COUNTERS_API_HEADERS_${API}}
                                                                     ${PUBLIC_DERIVED_COUNTERS_API_SRC_${API}}
                                                                     ${ADDITIONAL_DERIVED_COUNTERS_API_HEADERS_${API}}
                                                                     ${ADDITIONAL_DERIVED_COUNTERS_API_SRC_${API}})
        endif()
    endif()
endforeach()

set(UTIL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/utils/gpu_perf_api_loader.h
               ${CMAKE_CURRENT_SOURCE_DIR}/utils/gpu_perf_api_loader.cc)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${COUNTER_FILES}
    ${UTIL_FILES})

if(WIN32)
    set(ADDITIONAL_COMPILE_OPTIONS ${ADDITIONAL_COMPILE_OPTIONS}
                                     -wd4389)
endif()

add_compile_options(${ADDITIONAL_COMPILE_OPTIONS})
link_directories(${ADDITIONAL_LINK_DIRECTORIES})
add_executable(${GPA_PROJECT_NAME} ${SOURCES})
add_dependencies(${GPA_PROJECT_NAME} GPUPerfAPICounters)
ADD_GPA_USER_COMPILE_DEFINITIONS()
add_test(NAME ${GPA_PROJECT_NAME} COMMAND ${GPA_PROJECT_NAME})

if(NOT ${skipvulkan})
    set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-VK)
    add_definitions(-DVK)
endif()

if(NOT ${skipopengl})
    set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-GL)
    add_definitions(-DGL)
endif()

if(WIN32)
    if(NOT ${skipdx12})
        set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-DX12)
        add_definitions(-DDX12)
    endif()

    if(NOT ${skipdx11})
        set(LIB_NAMES ${LIB_NAMES} GPUPerfAPICounterGenerator-DX11)
        add_definitions(-DDX11)
    endif()
endif()

target_link_libraries(${GPA_PROJECT_NAME}
                      GPUPerfAPI-Common
                      ${LIB_NAMES}
                      GTest::gtest
                      $<$<PLATFORM_ID:Linux>:dl>
                      $<$<PLATFORM_ID:Linux>:pthread>
                      $<$<PLATFORM_ID:Windows>:AMD::adl_util>
                      AMD::device_info
                      )

ADD_LINKER_FLAGS()

if(UNIX)
    set_property(TARGET ${GPA_PROJECT_NAME} PROPERTY LINK_FLAGS "-Wl,-rpath=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()

SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})

if(WIN32)
    source_group("Utils" FILES ${UTIL_FILES})
endif()
