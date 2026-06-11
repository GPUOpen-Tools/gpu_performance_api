#/ Copyright (C) Advanced Micro Devices, Inc. All rights reserved.

set(GPA_PROJECT_NAME GPUPerfAPIUnitTests)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/common.cmake)

add_compile_options(${ADDITIONAL_COMPILE_OPTIONS})
link_directories(${ADDITIONAL_LINK_DIRECTORIES})
add_executable(${GPA_PROJECT_NAME})

target_include_directories(${GPA_PROJECT_NAME} PRIVATE
    ${ADDITIONAL_INCLUDE_DIRECTORIES}
    ${GPA_SRC}
    ${GPA_SRC_TESTS}/counters
    ${ADDITIONAL_DERIVED_COUNTERS_INCLUDE}
)

# API-specific sources are added later in this file
target_sources(${GPA_PROJECT_NAME} PRIVATE
    api_error_tests.cc
    counter_lib_func_table_tests.cc
    counter_scheduler_tests.cc
    counter_generator_tests.cc
    counter_generator_tests.h
    gpa_interface_loader_tests.cc
    gpu_perf_api_loader_tests.cc
    gpu_perf_api_unit_tests.cc
    counters/gpa_counter_desc.h
    utils/gpa_test_apis.h
    utils/gpu_perf_api_loader.cc
    utils/gpu_perf_api_loader.h
    ${GPA_SRC_COUNTER_GENERATOR}/gpa_derived_counter_evaluator.hpp
)

set(API_FILE_PREFIX_GL "oglp")
set(API_FILE_PREFIX_DX11 "dx11")
set(API_FILE_PREFIX_DX12 "dx12")
set(API_FILE_PREFIX_VK "vk")
foreach(API GL DX11 DX12 VK)
    if(NOT WIN32 AND (${API} STREQUAL "DX11" OR ${API} STREQUAL DX12))
        continue()
    endif()

    if(EXISTS ${GPA_AUTOGEN_SRC_TESTS})
        file(GLOB PUBLIC_DERIVED_COUNTERS_API_HEADERS_${API} CONFIGURE_DEPENDS
            ${GPA_AUTOGEN_SRC_TESTS}/counters/public_derived_counters_${API_FILE_PREFIX_${API}}_gfx*.h)
        file(GLOB PUBLIC_DERIVED_COUNTERS_API_SRC_${API} CONFIGURE_DEPENDS
            ${GPA_AUTOGEN_SRC_TESTS}/counters/public_derived_counters_${API_FILE_PREFIX_${API}}_gfx*.cc)
        target_sources(${GPA_PROJECT_NAME} PRIVATE
            ${PUBLIC_DERIVED_COUNTERS_API_HEADERS_${API}}
            ${PUBLIC_DERIVED_COUNTERS_API_SRC_${API}}
            ${ADDITIONAL_DERIVED_COUNTERS_API_HEADERS_${API}}
            ${ADDITIONAL_DERIVED_COUNTERS_API_SRC_${API}}
        )
        if(WIN32)
            source_group("Source Files\\auto_generated\\${API}" FILES ${PUBLIC_DERIVED_COUNTERS_API_HEADERS_${API}}
                                                                      ${PUBLIC_DERIVED_COUNTERS_API_SRC_${API}}
                                                                      ${ADDITIONAL_DERIVED_COUNTERS_API_HEADERS_${API}}
                                                                      ${ADDITIONAL_DERIVED_COUNTERS_API_SRC_${API}})
        endif()
    endif()
endforeach()

# Unit tests load counter library at runtime for testing.
add_dependencies(${GPA_PROJECT_NAME} GPUPerfAPICounters)
ADD_GPA_USER_COMPILE_DEFINITIONS()
add_test(NAME ${GPA_PROJECT_NAME} COMMAND ${GPA_PROJECT_NAME})

target_link_libraries(${GPA_PROJECT_NAME} PRIVATE
    ${CMAKE_DL_LIBS}
    GPUPerfAPI-Common
    GTest::gtest
    AMD::device_info
    AMD::GPUPerfAPI-Headers
)

if(NOT ${skipvulkan})
    target_link_libraries(${GPA_PROJECT_NAME} PRIVATE GPUPerfAPICounterGenerator-VK)
    target_compile_definitions(${GPA_PROJECT_NAME} PRIVATE VK)
    target_sources(${GPA_PROJECT_NAME} PRIVATE counter_generator_vk_tests.cc)
endif()

if(NOT ${skipopengl})
    target_link_libraries(${GPA_PROJECT_NAME} PRIVATE GPUPerfAPICounterGenerator-GL)
    target_compile_definitions(${GPA_PROJECT_NAME} PRIVATE GL)
    target_sources(${GPA_PROJECT_NAME} PRIVATE counter_generator_gl_tests.cc gl_group_matching_tests.cc)
endif()

if(NOT ${skipdx12})
    target_link_libraries(${GPA_PROJECT_NAME} PRIVATE GPUPerfAPICounterGenerator-DX12 AMD::d3dExtensions)
    target_compile_definitions(${GPA_PROJECT_NAME} PRIVATE DX12)
    target_sources(${GPA_PROJECT_NAME} PRIVATE counter_generator_dx12_tests.cc)
endif()

if(NOT ${skipdx11})
    target_link_libraries(${GPA_PROJECT_NAME} PRIVATE GPUPerfAPICounterGenerator-DX11 AMD::d3dExtensions)
    target_compile_definitions(${GPA_PROJECT_NAME} PRIVATE DX11)
    target_sources(${GPA_PROJECT_NAME} PRIVATE counter_generator_dx11_tests.cc)
endif()

ADD_LINKER_FLAGS()

SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})

file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/config_$<CONFIG>.h" INPUT "utils/config.h.in")
target_include_directories(${GPA_PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
