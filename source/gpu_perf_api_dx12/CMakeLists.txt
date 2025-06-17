## Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.
set(GPA_PROJECT_NAME GPUPerfAPIDX12)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)

include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_AMD_DX_EXT})

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

add_library(GPUPerfAPIDX12 MODULE)
add_lint_passes(GPUPerfAPIDX12)
target_sources(GPUPerfAPIDX12 PRIVATE
    ${GPA_SRC_COMMON}/gpa_function_exports.def
    dx12_gpa_command_list.h
    dx12_gpa_context.h
    dx12_gpa_implementor.h
    dx12_gpa_pass.h
    dx12_gpa_sample.h
    dx12_gpa_session.h
    dx12_gpa_sample_config.h
    dx12_utils.h
    dx12_gpa_command_list.cc
    dx12_gpa_context.cc
    dx12_gpa_implementor.cc
    dx12_gpa_pass.cc
    dx12_gpa_sample.cc
    dx12_gpa_session.cc
    dx12_gpa_sample_config.cc
    dx12_utils.cc
)

INCLUDE_WIN_RESOURCE(gpu_perf_api_dx12)

target_link_libraries(GPUPerfAPIDX12 PRIVATE
    GPUPerfAPI-Common
    GPUPerfAPIDX
    GPUPerfAPICounterGenerator-DX12
    AMD::adl_util
)

ADD_LINKER_FLAGS()

install(TARGETS GPUPerfAPIDX12 DESTINATION ${GPA_INSTALL_BINDIR} COMPONENT GPUPerfAPI)
