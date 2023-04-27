## Copyright (c) 2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_DERIVED_COUNTERS_API_HEADERS_GL
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_gl_gfx10.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_gl_gfx103.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_gl_gfx8.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_gl_gfx9.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx10.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx103.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx11.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx8.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx9.h)

set(PUBLIC_DERIVED_COUNTERS_API_SRC_GL
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_gl_gfx10.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_gl_gfx103.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_gl_gfx8.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_gl_gfx9.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx10.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx103.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx11.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx8.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx9.cc)

