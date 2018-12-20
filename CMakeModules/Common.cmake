## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

include(${GPA_CMAKE_MODULES_DIR}/CommonDefs.cmake)
include (${GPA_CMAKE_MODULES_DIR}/CommonMacros.cmake)

# Include global cmake common file
include(${CMAKE_COMMON_SRC_GLOBAL_CMAKE_MODULE})

# Global compiler options
add_compile_options(${COMMON_COMPILATION_FLAGS})

if(WIN32)
    # The global settings use /MD and /MDd. For GPA, we want to use /MT and /MTd
    add_compile_options("$<$<CONFIG:RELEASE>:/MT>"
                        "$<$<CONFIG:DEBUG>:/MTd>")
    set(AMDTCrt "MT")
    add_compile_options(-DUNICODE
                        -D_UNICODE)
endif()

if(WIN32)
    set(CURRENT_CONFIG "Debug/Release")
else()
    set(CURRENT_CONFIG ${CMAKE_BUILD_TYPE})
endif()

## Handling project
if(NOT ${ProjectName} STREQUAL "")
    message("CMake: Evaluating and including project ${ProjectName} for config ${CURRENT_CONFIG} for ${AMDTPlatform} platform in ${PROJECT_NAME} solution")
endif()

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${GPA_OUTPUT_DIR}/Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${GPA_OUTPUT_DIR}/Debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${GPA_OUTPUT_DIR}/Release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${GPA_OUTPUT_DIR}/Debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${GPA_OUTPUT_DIR}/Release)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${GPA_OUTPUT_DIR}/Debug)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${GPA_OUTPUT_DIR}/${CMAKE_BUILD_TYPE})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${GPA_OUTPUT_DIR}/${CMAKE_BUILD_TYPE})
endif()

add_definitions(-DUSE_POINTER_SINGLETON)

if(NOT WIN32)
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
    set(GPA_COMMON_LINK_ARCHIVE_FLAG -Wl,--whole-archive)
    set(GPA_COMMON_LINK_NO_ARCHIVE_FLAG -Wl,--no-whole-archive)
    add_compile_options(-Wno-unknown-pragmas -Wno-strict-aliasing -Wno-non-virtual-dtor -Wno-unused-value -msse)
endif()