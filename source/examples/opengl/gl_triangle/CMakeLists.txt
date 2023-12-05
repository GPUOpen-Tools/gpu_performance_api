## Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GLTriangle)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)
include (${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include (${CMAKE_COMMON_LIB_GLOBAL_EXT_OPENGL})


include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(SOURCES ${GPA_SRC_COMMON}/utility.h
            ${GPA_SRC_COMMON}/utility.cc
            ${GPA_SRC_COMMON}/logging.h
            ${GPA_SRC_COMMON}/logging.cc
            ${GPA_SRC_COUNTER_GENERATOR}/gl_entry_points.h
            ${GPA_SRC_COUNTER_GENERATOR}/gl_entry_points.cc
            ${GPA_SRC_EXAMPLE_COMMON_PATH}/cmdline_parser.h
            ${GPA_SRC_EXAMPLE_COMMON_PATH}/cmdline_parser.cc
            ${GPA_SRC_EXAMPLE_COMMON_PATH}/gpa_sample_app.h
            ${GPA_SRC_EXAMPLE_COMMON_PATH}/gpa_sample_app.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/gl_triangle.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/gpa_helper.h
            ${CMAKE_CURRENT_SOURCE_DIR}/gpa_helper.cc)

add_executable(${GPA_PROJECT_NAME} WIN32 ${SOURCES})
add_dependencies(${GPA_PROJECT_NAME} GPUPerfAPIGL)
ADD_GPA_USER_COMPILE_DEFINITIONS()

target_link_libraries(${GPA_PROJECT_NAME}
                      $<$<PLATFORM_ID:Linux>:dl>
                      $<$<PLATFORM_ID:Linux>:pthread>
                      $<$<PLATFORM_ID:Linux>:X11>)

set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER "Examples/OpenGL")
SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})



