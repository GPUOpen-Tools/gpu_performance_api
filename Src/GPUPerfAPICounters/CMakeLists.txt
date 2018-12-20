## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPICounters)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/Common.cmake)
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GPUPerfAPICounters.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GPUPerfAPICounters.cpp)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

ADD_SHARED_LIBRARY_NO_EXPORT(${GPA_PROJECT_NAME})
INCLUDE_WIN_RESOURCE()

target_link_libraries(${GPA_PROJECT_NAME}
                      GPUPerfAPI-Common
                      ${GPA_COMMON_LINK_ARCHIVE_FLAG}
                      GPUPerfAPICounterGenerator
                      ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG})

ADD_LINKER_FLAGS()