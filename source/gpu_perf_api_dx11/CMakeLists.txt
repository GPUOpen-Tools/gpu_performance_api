## Copyright (C) 2018-2026 Advanced Micro Devices, Inc. All rights reserved. ##

set(GPA_PROJECT_NAME GPUPerfAPIDX11)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

add_library(GPUPerfAPIDX11 MODULE)
add_lint_passes(GPUPerfAPIDX11)
target_sources(GPUPerfAPIDX11 PRIVATE
    ${GPA_SRC_COMMON}/gpa_function_exports.def
    dx11_gpa_command_list.h
    dx11_gpa_context.h
    dx11_gpa_implementor.h
    dx11_gpa_pass.h
    dx11_gpa_sample.h
    dx11_gpa_session.h
    dx11_include.h
    dx11_utils.h
    dxx_ext_utils.h
    dx11_gpa_command_list.cc
    dx11_gpa_context.cc
    dx11_gpa_implementor.cc
    dx11_gpa_pass.cc
    dx11_gpa_sample.cc
    dx11_gpa_session.cc
    dx11_utils.cc
    dxx_ext_utils.cc
    gpu_perf_api_dx11.rc
)

target_link_libraries(GPUPerfAPIDX11 PRIVATE
    d3d11.lib
    dxguid.lib
    GPUPerfAPI-Common
    GPUPerfAPIDX
    GPUPerfAPICounterGenerator-DX11
    AMD::device_info
    AMD::tsingleton
    AMD::d3dExtensions
)

ADD_LINKER_FLAGS()

install(TARGETS GPUPerfAPIDX11 DESTINATION ${GPA_INSTALL_BINDIR} COMPONENT GPUPerfAPI)
install(TARGETS GPUPerfAPIDX11 DESTINATION ${GPA_INSTALL_TESTDIR} COMPONENT GPATestKit)
