## Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPIVK)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)

include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_AMD_VK_EXT})
if(WIN32)
    include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})
endif()
include(${GPA_CMAKE_MODULES_DIR}/gpa_vulkan.cmake)

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(HEADER_FILES ${GPA_PUBLIC_HEADER}/gpu_perf_api_vk.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_command_list_sw_queries.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_command_list_sw_query_group.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_entry_points.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_command_list.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_context.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_hardware_sample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_implementor.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_pass.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_sample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_session.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_software_sample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_includes.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_software_counters_results.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_utils.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/vk_command_list_sw_queries.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_command_list_sw_query_group.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_entry_points.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_command_list.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_context.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_hardware_sample.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_implementor.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_pass.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_sample.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_session.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_gpa_software_sample.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/vk_utils.cc)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

if(ANDROID)
    add_compile_options(-Wno-unused-private-field)
endif()
ADD_SHARED_LIBRARY(${GPA_PROJECT_NAME} ${GPA_SRC_COMMON}/gpa_function_exports.def)
INCLUDE_WIN_RESOURCE(gpu_perf_api_vk)

target_link_libraries(${GPA_PROJECT_NAME}
                      ${GPA_COMMON_LINK_ARCHIVE_FLAG}
                      GPUPerfAPI-Common
                      ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG}
                      GPUPerfAPICounterGenerator-VK)

ADD_LINKER_FLAGS()






