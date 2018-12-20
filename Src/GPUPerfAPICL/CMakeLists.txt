## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPICL)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/Common.cmake)
include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_DYNAMIC_LIBRARY_MODULE})
include(${CMAKE_COMMON_LIB_GLOBAL_AMD_OPENCL_NO_LIB})
include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(ADDITIONAL_SOURCE
    ${DYNAMIC_LIBRARY_MODULE}/OpenCLModule.cpp)

set(ADDITIONAL_SOURCE_HEADERS
    ${DYNAMIC_LIBRARY_MODULE}/OpenCLModule.h)

set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPACommandList.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPAContext.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPAImplementor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPAPass.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPASample.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPASession.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CLPerfCounterAMDExtension.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CLPerfCounterBlock.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CLRTModuleLoader.h)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPACommandList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPAContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPAImplementor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPAPass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPASample.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CLGPASession.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CLPerfCounterAMDExtension.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CLPerfCounterBlock.cpp)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${ADDITIONAL_SOURCE}
    ${ADDITIONAL_SOURCE_HEADERS})

if(NOT WIN32)
    add_compile_options("-Wno-deprecated-declarations")
    add_compile_options("-Wno-ignored-attributes")
endif()

ADD_SHARED_LIBRARY(${GPA_PROJECT_NAME} ${DEPTH}/GPAFunctionExports.def)
INCLUDE_WIN_RESOURCE()
target_link_libraries(${GPA_PROJECT_NAME}
                      ${GPA_COMMON_LINK_ARCHIVE_FLAG}
                      GPUPerfAPI-Common
                      ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG}
                      GPUPerfAPICounterGenerator)

ADD_LINKER_FLAGS()

if(WIN32)
    source_group("DynamicLibraryModule" FILES ${ADDITIONAL_SOURCE} ${ADDITIONAL_SOURCE_HEADERS})
endif()
