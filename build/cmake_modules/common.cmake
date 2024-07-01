## Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

include (${GPA_CMAKE_MODULES_DIR}/utils.cmake)

# Include global cmake common file
include(${CMAKE_COMMON_SRC_GLOBAL_CMAKE_MODULE})

# Check for required variables from other cmake files.
if (${GPA_OUTPUT_DIR} STREQUAL "")
    message(FATAL_ERROR "No output directory is defined, make sure defs.cmake is included before common.cmake")
endif()

# Global compiler options
add_compile_options(${COMMON_COMPILATION_FLAGS})

if(WIN32)
    # The global settings use /MD and /MDd. For GPA, we want to use /MT and /MTd
    add_compile_options("$<$<CONFIG:RELEASE>:/MT>"
                        "$<$<CONFIG:DEBUG>:/MTd>"
                        "/EHsc")
    set(AMDTCrt "MT")
endif()

add_compile_options(-DUNICODE
                    -D_UNICODE)

if(WIN32)
    set(CURRENT_CONFIG "Debug/Release")
else()
    set(CURRENT_CONFIG ${CMAKE_BUILD_TYPE})
endif()

## Handling project
if(NOT ${ProjectName} STREQUAL "")
    message(STATUS "Evaluating and including project ${ProjectName} for config ${CURRENT_CONFIG} for ${AMDTPlatform} platform in ${PROJECT_NAME} solution")
endif()

if(${USE_DEFAULT_OUTPUT_DIRECTORY})
    if(WIN32)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${GPA_OUTPUT_DIR}/release${OUTPUT_SUFFIX})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${GPA_OUTPUT_DIR}/debug${OUTPUT_SUFFIX})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${GPA_OUTPUT_DIR}/release${OUTPUT_SUFFIX})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${GPA_OUTPUT_DIR}/debug${OUTPUT_SUFFIX})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${GPA_OUTPUT_DIR}/release${OUTPUT_SUFFIX})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${GPA_OUTPUT_DIR}/debug${OUTPUT_SUFFIX})
    else()
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${GPA_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}${OUTPUT_SUFFIX})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${GPA_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}${OUTPUT_SUFFIX})
    endif()
else()
    if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY OR NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
        message(FATAL_ERROR "Output Directories are not set.")
    endif()
endif()

add_definitions(-DUSE_POINTER_SINGLETON)

if(NOT WIN32)
    if(${USE_DEFAULT_COMPILER})
        set(CMAKE_C_COMPILER gcc)
        set(CMAKE_CXX_COMPILER g++)
    endif()

if(NOT APPLE)
    set(GPA_COMMON_LINK_ARCHIVE_FLAG -Wl,--whole-archive)
    set(GPA_COMMON_LINK_NO_ARCHIVE_FLAG -Wl,--no-whole-archive)
endif()
    add_compile_options(-Wno-unknown-pragmas -Wno-strict-aliasing -Wno-non-virtual-dtor -Wno-unused-value -msse -fvisibility=hidden)
endif()
