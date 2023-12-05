## Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPIDX12)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)

include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_AMD_DX_EXT})
include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_command_list.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_context.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_implementor.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_pass.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_sample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_session.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_sample_config.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_utils.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_command_list.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_context.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_implementor.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_pass.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_sample.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_session.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_gpa_sample_config.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx12_utils.cc)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

ADD_SHARED_LIBRARY(${GPA_PROJECT_NAME} ${GPA_SRC_COMMON}/gpa_function_exports.def ${SOURCES})

INCLUDE_WIN_RESOURCE(gpu_perf_api_dx12)

target_link_libraries(${GPA_PROJECT_NAME}
                      GPUPerfAPI-Common
                      GPUPerfAPIDX
                      GPUPerfAPICounterGenerator-DX12)

ADD_LINKER_FLAGS()
