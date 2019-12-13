## Copyright (c) 2018-2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

## GPA has only Debug and Release
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(DEPTH "./")

include(${GPA_CMAKE_MODULES_DIR}/CommonDefs.cmake)

if(NOT DEFINED usingscript)
    set(usingscript OFF CACHE BOOL "Turn on to indicate CMake is called using script" FORCE)
endif()

if(NOT DEFINED build-internal)
    set(build-internal OFF CACHE BOOL "Turn on to generate internal build")
endif()

if(${build-internal})
    set(AMDT_INTERNAL_BUILD_FLAG ON)
endif()

if(${usingscript})
    # Platform Control variable
    if(NOT DEFINED build-32bit)
        set(build-32bit OFF CACHE BOOL "Turn on to generate 32 bit project files")
    endif()

    # Config control variable
    if(NOT DEFINED build-debug)
        set(build-debug OFF CACHE BOOL "Turn on to generate debug config of the project")
    endif()

    if(NOT WIN32)
        if(${build-debug})
            set(CMAKE_BUILD_TYPE debug)
        else()
            set(CMAKE_BUILD_TYPE release)
        endif()
    endif()
endif()

if(${build-32bit})
    set(CMAKE_SIZEOF_VOID_P 4)
else()
    set(CMAKE_SIZEOF_VOID_P 8)
endif()

# DX11 variable
if(NOT DEFINED skipdx11)
    set(skipdx11 OFF CACHE BOOL "Turn on to skip DX11 in the build" FORCE)
endif()

# DX12 variable
if(NOT DEFINED skipdx12)
    set(skipdx12 OFF CACHE BOOL "Turn on to skip DX12 in the build" FORCE)
endif()

# Vulkan variable
if(NOT DEFINED skipvulkan)
    set(skipvulkan OFF CACHE BOOL "Turn on to skip Vulkan in the build" FORCE)
endif()

# OpenGL variable
if(NOT DEFINED skipopengl)
    set(skipopengl OFF CACHE BOOL "Turn on to skip OpenGL in the build" FORCE)
endif()

# OpenCL variable
if(NOT DEFINED skipopencl)
    set(skipopencl OFF CACHE BOOL "Turn on to skip OpenCL in the build" FORCE)
endif()

# Tests variable
if(NOT DEFINED skiptests)
    set(skiptests OFF CACHE BOOL "Turn on to skip Tests in the build" FORCE)
endif()

# Sphinx documentation
if(NOT DEFINED skipdocs)
    set(skipdocs OFF CACHE BOOL "Turn on to skip sphinx documentation in the build" FORCE)
endif()

# Default Output directory
if(NOT DEFINED USE_DEFAULT_OUTPUT_DIRECTORY)
    set(USE_DEFAULT_OUTPUT_DIRECTORY ON)
endif()

# Default compiler
if(NOT DEFINED USE_DEFAULT_COMPILER)
    set(USE_DEFAULT_COMPILER ON)
endif()