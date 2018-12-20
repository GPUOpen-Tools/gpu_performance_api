## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPIGL)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/Common.cmake)

include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_LIB_GLOBAL_EXT_OPENGL})
include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(HEADER_FILES ${GPA_SRC_COUNTER_GENERATOR}/GLInclude.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/ASICInfo.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPACommandList.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPAContext.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPAImplementor.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPAPass.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPASample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPASession.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ASICInfo.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPACommandList.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPAContext.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPAImplementor.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPAPass.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPASample.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GLGPASession.cpp)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

ADD_SHARED_LIBRARY(${GPA_PROJECT_NAME} ${DEPTH}/GPAFunctionExports.def)
INCLUDE_WIN_RESOURCE()

target_link_libraries(${GPA_PROJECT_NAME}
                      ${GPA_COMMON_LINK_ARCHIVE_FLAG}
                      GPUPerfAPI-Common
                      ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG}
                      GPUPerfAPICounterGenerator)

ADD_LINKER_FLAGS()