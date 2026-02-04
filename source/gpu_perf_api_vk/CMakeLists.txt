## Copyright (C) 2018-2026 Advanced Micro Devices, Inc. All rights reserved. ##

set(GPA_PROJECT_NAME GPUPerfAPIVK)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR}
                    ${GPA_SRC})

if(ANDROID)
    add_compile_options(-Wno-unused-private-field)
endif()

add_library(GPUPerfAPIVK MODULE)
add_lint_passes(GPUPerfAPIVK)
target_sources(GPUPerfAPIVK PRIVATE
    ${GPA_SRC_COMMON}/gpa_function_exports.def
    ${GPA_PUBLIC_HEADER}/gpu_performance_api/gpu_perf_api_vk.h
    vk_entry_points.h
    vk_gpa_command_list.h
    vk_gpa_context.h
    vk_gpa_hardware_sample.h
    vk_gpa_implementor.h
    vk_gpa_pass.h
    vk_gpa_sample.h
    vk_gpa_session.h
    vk_includes.h
    vk_utils.h
    vk_entry_points.cc
    vk_gpa_command_list.cc
    vk_gpa_context.cc
    vk_gpa_hardware_sample.cc
    vk_gpa_implementor.cc
    vk_gpa_pass.cc
    vk_gpa_sample.cc
    vk_gpa_session.cc
    vk_utils.cc
    gpu_perf_api_vk.rc
)

target_link_libraries(GPUPerfAPIVK PRIVATE
    ${GPA_COMMON_LINK_ARCHIVE_FLAG}
    GPUPerfAPI-Common
    ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG}
    GPUPerfAPICounterGenerator-VK
    AMD::device_info
    AMD::tsingleton
)

ADD_LINKER_FLAGS()

install(TARGETS GPUPerfAPIVK DESTINATION ${GPA_INSTALL_BINDIR} COMPONENT GPUPerfAPI)
install(TARGETS GPUPerfAPIVK DESTINATION ${GPA_INSTALL_TESTDIR} COMPONENT GPATestKit)
