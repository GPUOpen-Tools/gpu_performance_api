## Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPIDX11)
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

set(AMD_DX_EXT_HEADERS ${AMD_DX_EXT_DIR}/AmdDxExt.h
                       ${AMD_DX_EXT_DIR}/AmdDxExtApi.h
                       ${AMD_DX_EXT_DIR}/AmdDxExtIface.h
                       ${AMD_DX_EXT_DIR}/AmdDxExtPerfProfile.h
                       ${AMD_DX_EXT_DIR}/AmdDxExtPerfProfileApi.h
                       ${AMD_DX_EXT_DIR}/AmdDxExtASICInfo.h
                       ${AMD_DX_EXT_DIR}/AmdDxExtASICInfoApi.h)

set(HEADER_FILES ${AMD_DX_EXT_HEADERS}
                 ${GPA_SRC_COMMON}/dx_get_amd_device_info.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_command_list.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_context.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_implementor.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_pass.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_sample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_session.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_include.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_utils.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/dxx_ext_utils.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_command_list.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_context.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_implementor.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_pass.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_sample.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_gpa_session.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dx11_utils.cc
                 ${CMAKE_CURRENT_SOURCE_DIR}/dxx_ext_utils.cc)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

ADD_SHARED_LIBRARY(${GPA_PROJECT_NAME} ${GPA_SRC_COMMON}/gpa_function_exports.def ${SOURCES})
INCLUDE_WIN_RESOURCE(gpu_perf_api_dx11)
target_link_libraries(${GPA_PROJECT_NAME}
                      d3d11.lib
                      dxguid.lib
                      GPUPerfAPI-Common
                      GPUPerfAPIDX
                      GPUPerfAPICounterGenerator-DX11)

if(${GPA_ALL_OPEN_SOURCE})
    set(GPA_DX11_GET_DEVICE_INFO ${COMMON_DIR_LIB}/AMD/GPUPerfAPI/3_17/Bin/${AMDTPlatform}/GPUPerfAPIDXGetAMDDeviceInfo)
    add_custom_command(TARGET ${GPA_PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy ${GPA_DX11_GET_DEVICE_INFO}${AMDTPlatformSuffix}.dll ${GPA_OUTPUT_DIR}/$<CONFIG>${OUTPUT_SUFFIX}/ VERBATIM
                       COMMENT "Copying GPUPerfAPIDXGetDeviceInfo to output folder...")
endif()

ADD_LINKER_FLAGS()

if(WIN32)
    source_group("AmdDxExt" FILES ${AMD_DX_EXT_HEADERS})
endif()
