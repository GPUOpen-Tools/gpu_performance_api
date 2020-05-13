## Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPIDX)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/common.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${GPA_PUBLIC_HEADER}
                    ${GPA_SRC_COMMON})

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/dx_utils.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/dx_utils.cc)

set(SOURCES
    ${HEADER_FILES}
    ${SOURCE_FILES})

ADD_STATIC_LIBRARY(${GPA_PROJECT_NAME})