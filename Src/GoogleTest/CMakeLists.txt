## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GoogleTestLib)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/CommonDefs.cmake)
include(${CMAKE_COMMON_SRC_GLOBAL_CMAKE_MODULE})

if(WIN32)
    # Googletest for GPA, we want to use /MT and /MTd
    add_compile_options("$<$<CONFIG:RELEASE>:/MT>"
                        "$<$<CONFIG:DEBUG>:/MTd>")
endif()


# Build GoogleTest libs
set(BUILD_GMOCK OFF CACHE BOOL "disable gmock building" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "disable gtest installation" FORCE)
add_subdirectory(${GOOGLETEST_DIR} ${CMAKE_BINARY_DIR}/googletest)
set_target_properties(gtest PROPERTIES FOLDER Tests/GoogleTest)
set_target_properties(gtest_main PROPERTIES FOLDER Tests/GoogleTest)