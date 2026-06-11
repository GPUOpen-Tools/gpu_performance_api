#/ Copyright (C) Advanced Micro Devices, Inc. All rights reserved.

get_cmake_property(GPA_IS_MULTI_CONFIG GENERATOR_IS_MULTI_CONFIG)
if(GPA_IS_MULTI_CONFIG)
    set(CMAKE_CONFIGURATION_TYPES Debug Release) ## GPA has only Debug and Release
endif()

set(GPA_ALL_OPEN_SOURCE ON)

set(OUTPUT_SUFFIX _x64)

if(ANDROID)
    set(OUTPUT_SUFFIX ${OUTPUT_SUFFIX}_android)
endif()

# DX11 variable
if(NOT DEFINED skipdx11)
    set(skipdx11 OFF CACHE BOOL "Turn on to skip DX11 in the build" FORCE)
endif()

# DX12 variable
if(NOT DEFINED skipdx12)
    set(skipdx12 OFF CACHE BOOL "Turn on to skip DX12 in the build" FORCE)
endif()

if (NOT WIN32)
    set(skipdx12 ON CACHE BOOL "DX12 is Windows only" FORCE)
    set(skipdx11 ON CACHE BOOL "DX11 is Windows only" FORCE)
endif()

# Vulkan variable
if(NOT DEFINED skipvulkan)
    set(skipvulkan OFF CACHE BOOL "Turn on to skip Vulkan in the build" FORCE)
endif()

# OpenGL variable
if(NOT DEFINED skipopengl)
    set(skipopengl OFF CACHE BOOL "Turn on to skip OpenGL in the build" FORCE)
endif()

# Tests variable
if(NOT DEFINED skiptests)
    set(skiptests OFF CACHE BOOL "Turn on to skip Tests in the build" FORCE)
endif()

# Sphinx documentation
if(NOT DEFINED skipdocs)
    set(skipdocs OFF CACHE BOOL "Turn on to skip sphinx documentation in the build" FORCE)
endif()
