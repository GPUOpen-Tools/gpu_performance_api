## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_DERIVED_COUNTERS_API_HEADERS_GL
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersGLGfx10.h
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersGLGfx8.h
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersGLGfx9.h)

set(PUBLIC_DERIVED_COUNTERS_API_SRC_GL
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersGLGfx10.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersGLGfx8.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersGLGfx9.cpp)

