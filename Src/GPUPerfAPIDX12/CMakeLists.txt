## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPIDX12)
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

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPACommandList.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPAContext.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPAImplementor.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPAPass.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPASample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPASession.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12Utils.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPACommandList.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPAContext.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPAImplementor.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPAPass.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPASample.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12GPASession.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/DX12Utils.cpp)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

ADD_SHARED_LIBRARY(${GPA_PROJECT_NAME} ${DEPTH}/GPAFunctionExports.def)
INCLUDE_WIN_RESOURCE()

target_link_libraries(${GPA_PROJECT_NAME}
                      GPUPerfAPI-Common
                      GPUPerfAPIDX
                      GPUPerfAPICounterGenerator)

ADD_LINKER_FLAGS()