## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPIROCm)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/Common.cmake)
include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_DYNAMIC_LIBRARY_MODULE})
include(${GPA_CMAKE_MODULES_DIR}/GPA-HSA.cmake)

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GPUPerfAPIROCmGlobals.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPACommandList.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPAContext.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPAImplementor.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPAPass.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPASample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPASession.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/HSARTModuleLoader.h)


set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GPUPerfAPIROCmAgent.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPACommandList.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPAContext.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPAImplementor.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPAPass.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPASample.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/ROCmGPASession.cpp)

set(ADDITIONAL_SOURCE_HEADERS ${DYNAMIC_LIBRARY_MODULE}/HSAModule.h
                              ${DYNAMIC_LIBRARY_MODULE}/ROCProfilerModule.h)

set(ADDITIONAL_SOURCE ${DYNAMIC_LIBRARY_MODULE}/HSAModule.cpp
                      ${DYNAMIC_LIBRARY_MODULE}/ROCProfilerModule.cpp)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${ADDITIONAL_SOURCE}
    ${ADDITIONAL_SOURCE_HEADERS})

add_definitions(-DAMD_INTERNAL_BUILD)

if(NOT WIN32)
    add_compile_options(-Wno-pmf-conversions)
endif()

ADD_SHARED_LIBRARY(${GPA_PROJECT_NAME} ${DEPTH}/GPAFunctionExports.def)

target_link_libraries(${GPA_PROJECT_NAME}
                      ${GPA_COMMON_LINK_ARCHIVE_FLAG}
                      GPUPerfAPI-Common
                      ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG}
                      GPUPerfAPICounterGenerator)

ADD_LINKER_FLAGS()
