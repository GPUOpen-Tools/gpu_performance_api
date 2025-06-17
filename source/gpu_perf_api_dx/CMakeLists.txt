## Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.
set(GPA_PROJECT_NAME GPUPerfAPIDX)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/common.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC}
                    ${GPA_SRC_COMMON})

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/dx_utils.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/dx_utils.cc)

set(SOURCES
    ${HEADER_FILES}
    ${SOURCE_FILES})

ADD_STATIC_LIBRARY(${GPA_PROJECT_NAME} ${SOURCES})
target_link_libraries(${GPA_PROJECT_NAME} AMD::tsingleton)
