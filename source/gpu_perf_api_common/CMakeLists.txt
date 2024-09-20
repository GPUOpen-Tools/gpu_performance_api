## Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPI-Common)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/common.cmake)
if(NOT ${skipvulkan})
include(${GPA_CMAKE_MODULES_DIR}/gpa_vulkan.cmake)
endif()
include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_DYNAMIC_LIBRARY_MODULE})


set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC})

set(ADDITIONAL_SOURCE
    ${ADL_UTIL_DIR}/ADLUtil.cpp
    ${DYNAMIC_LIBRARY_MODULE}/DynamicLibraryModule.cpp
    ${DEVICE_INFO_SRC})

set(ADDITIONAL_SOURCE_HEADERS
    ${ADL_UTIL_DIR}/ADLUtil.h
    ${DYNAMIC_LIBRARY_MODULE}/DynamicLibraryModule.h
    ${DEVICE_INFO_HEADERS})

set(PUBLIC_HEADERS  ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api.h
                    ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api_counters.h
                    ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api_functions.h
                    ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api_function_types.h
                    ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api_interface_loader.h
                    ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api_stub.h
                    ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api_types.h
                    ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api_vk.h)

set(DEPRECATED_PUBLIC_HEADERS  ${GPA_PUBLIC_HEADER}/gpu_perf_api.h
                               ${GPA_PUBLIC_HEADER}/gpu_perf_api_counters.h
                               ${GPA_PUBLIC_HEADER}/gpu_perf_api_functions.h
                               ${GPA_PUBLIC_HEADER}/gpu_perf_api_function_types.h
                               ${GPA_PUBLIC_HEADER}/gpu_perf_api_interface_loader.h
                               ${GPA_PUBLIC_HEADER}/gpu_perf_api_stub.h
                               ${GPA_PUBLIC_HEADER}/gpu_perf_api_types.h
                               ${GPA_PUBLIC_HEADER}/gpu_perf_api_vk.h
                               ${GPA_PUBLIC_HEADER}/GPAFunctions.h
                               ${GPA_PUBLIC_HEADER}/GPAInterfaceLoader.h
                               ${GPA_PUBLIC_HEADER}/GPUPerfAPI.h
                               ${GPA_PUBLIC_HEADER}/GPUPerfAPIFunctionTypes.h
                               ${GPA_PUBLIC_HEADER}/GPUPerfAPIStub.h
                               ${GPA_PUBLIC_HEADER}/GPUPerfAPITypes.h
                               ${GPA_PUBLIC_HEADER}/GPUPerfAPI-VK.h)

set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/adapter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/api_rt_module_loader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/circular_buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/dx_get_amd_device_info.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_command_list.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_command_list_interface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_common_defs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_context.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_context_counter_mediator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_context_interface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_counter_data_request_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_custom_hw_validation_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_hw_info.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_implementor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_implementor_interface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_interface_trait_interface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_pass.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_profiler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_sample.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_session.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_session_interface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_unique_object.h
    ${CMAKE_CURRENT_SOURCE_DIR}/logging.h
    ${CMAKE_CURRENT_SOURCE_DIR}/utility.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_version.h)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_command_list.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_context.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_context_counter_mediator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_custom_hw_validation_manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_hw_info.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_implementor.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_pass.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_profiler.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_sample.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_session.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpa_unique_object.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpu_perf_api.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gpu_perf_api_deprecated.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logging.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/utility.cc)

if(WIN32)
    set(SOURCE_FILES ${SOURCE_FILES}
                     ${CMAKE_CURRENT_SOURCE_DIR}/adapter.cc)
    set(LINK_LIBS dxgi.lib)
endif()

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${ADDITIONAL_SOURCE}
    ${ADDITIONAL_SOURCE_HEADERS}
    ${PUBLIC_HEADERS}
    ${DEPRECATED_PUBLIC_HEADERS})

ADD_STATIC_LIBRARY(${GPA_PROJECT_NAME} ${SOURCES})
target_link_libraries(${GPA_PROJECT_NAME}
                      ${LINK_LIBS}
                      $<$<PLATFORM_ID:Linux>:pthread>)

ADD_LINKER_FLAGS()

if(WIN32)
    source_group("Public Header Files" FILES ${PUBLIC_HEADERS})
    source_group("Deprecated Header Files" FILES ${DEPRECATED_PUBLIC_HEADERS})
    source_group("Source Files" FILES ${SOURCE_FILES})
endif()
