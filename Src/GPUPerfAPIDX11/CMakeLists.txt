## Copyright (c) 2018-2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPIDX11)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/Common.cmake)

include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_AMD_DX_EXT})
include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
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
                 ${GPA_SRC_COMMON}/DXGetAMDDeviceInfo.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPACommandList.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPAContext.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPAImplementor.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPAPass.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPASample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPASession.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11Include.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11Utils.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DxxExtUtils.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPACommandList.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPAContext.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPAImplementor.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPAPass.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPASample.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11GPASession.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX11Utils.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DxxExtUtils.cpp)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

ADD_SHARED_LIBRARY(${GPA_PROJECT_NAME} ${DEPTH}/GPAFunctionExports.def)
INCLUDE_WIN_RESOURCE()
target_link_libraries(${GPA_PROJECT_NAME}
                      d3d11.lib
                      dxguid.lib
                      GPUPerfAPI-Common
                      GPUPerfAPIDX
                      GPUPerfAPICounterGenerator-DX11)

if(${GPA_ALL_OPEN_SOURCE})
    set(GPA_DX11_GET_DEVICE_INFO ${COMMON_DIR_LIB}/AMD/GPUPerfAPI/3_4/Bin/${AMDTPlatform}/GPUPerfAPIDXGetAMDDeviceInfo)
    add_custom_command(TARGET ${GPA_PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy ${GPA_DX11_GET_DEVICE_INFO}${AMDTPlatformSuffix}.dll ${CMAKE_CURRENT_LIST_DIR}/${DEPTH}/Output/$<CONFIG> VERBATIM
                       COMMENT "Copying GPUPerfAPIDXGetDeviceInfo to output folder...")
endif()

ADD_LINKER_FLAGS()

if(WIN32)
    source_group("AmdDxExt" FILES ${AMD_DX_EXT_HEADERS})
endif()