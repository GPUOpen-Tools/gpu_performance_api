## Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.
set(GPA_PROJECT_NAME GPUPerfAPIGL)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)

include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_LIB_GLOBAL_EXT_OPENGL})

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

add_library(GPUPerfAPIGL MODULE)
add_lint_passes(GPUPerfAPIGL)
target_sources(GPUPerfAPIGL PRIVATE
    ${GPA_SRC_COMMON}/gpa_function_exports.def
    asic_info.cc
    gl_gpa_command_list.cc
    gl_gpa_context.cc
    gl_gpa_implementor.cc
    gl_gpa_pass.cc
    gl_gpa_sample.cc
    gl_gpa_session.cc
    asic_info.h
    gl_amd_driver_ext.h
    gl_gpa_command_list.h
    gl_gpa_context.h
    gl_gpa_implementor.h
    gl_gpa_pass.h
    gl_gpa_sample.h
    gl_gpa_session.h
)
INCLUDE_WIN_RESOURCE(gpu_perf_api_gl)

target_link_libraries(GPUPerfAPIGL PRIVATE
    ${GPA_COMMON_LINK_ARCHIVE_FLAG}
    GPUPerfAPI-Common
    ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG}
    GPUPerfAPICounterGenerator-GL
    AMD::adl_util
)

ADD_LINKER_FLAGS()

install(TARGETS GPUPerfAPIGL DESTINATION ${GPA_INSTALL_BINDIR} COMPONENT GPUPerfAPI)
