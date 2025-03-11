## Copyright (c) 2025 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_DERIVED_COUNTERS_API_HEADERS_GL
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx10.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx103.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx11.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx12.h)

set(PUBLIC_DERIVED_COUNTERS_API_SRC_GL
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx10.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx103.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx11.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_oglp_gfx12.cc)

