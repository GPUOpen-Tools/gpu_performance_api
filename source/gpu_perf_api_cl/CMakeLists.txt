## Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPICL)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)
include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_DYNAMIC_LIBRARY_MODULE})
include(${CMAKE_COMMON_LIB_GLOBAL_AMD_OPENCL_NO_LIB})
if(WIN32)
    include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})
endif()

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(ADDITIONAL_SOURCE
    ${DYNAMIC_LIBRARY_MODULE}/OpenCLModule.cpp)

set(ADDITIONAL_SOURCE_HEADERS
    ${DYNAMIC_LIBRARY_MODULE}/OpenCLModule.h)

set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_command_list.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_context.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_implementor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_pass.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_sample.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_session.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_perf_counter_amd_extension.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_perf_counter_block.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_rt_module_loader.h)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_command_list.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_context.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_implementor.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_pass.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_sample.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gpa_session.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_perf_counter_amd_extension.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_perf_counter_block.cc)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${ADDITIONAL_SOURCE}
    ${ADDITIONAL_SOURCE_HEADERS})

if(NOT WIN32)
    add_compile_options("-Wno-deprecated-declarations")
    add_compile_options("-Wno-ignored-attributes")
endif()

ADD_SHARED_LIBRARY(${GPA_PROJECT_NAME} ${GPA_SRC_COMMON}/gpa_function_exports.def ${SOURCES})
INCLUDE_WIN_RESOURCE(gpu_perf_api_cl)
target_link_libraries(${GPA_PROJECT_NAME}
                      ${GPA_COMMON_LINK_ARCHIVE_FLAG}
                      GPUPerfAPI-Common
                      ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG}
                      GPUPerfAPICounterGenerator-CL)

ADD_LINKER_FLAGS()

if(WIN32)
    source_group("Dynamic Library Module" FILES ${ADDITIONAL_SOURCE} ${ADDITIONAL_SOURCE_HEADERS})
endif()
