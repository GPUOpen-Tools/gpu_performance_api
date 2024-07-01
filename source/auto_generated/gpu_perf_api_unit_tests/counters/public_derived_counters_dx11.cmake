## Copyright (c) 2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_DERIVED_COUNTERS_API_HEADERS_DX11
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_dx11_gfx10.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_dx11_gfx103.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_dx11_gfx11.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_dx11_gfx8.h
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_dx11_gfx9.h)

set(PUBLIC_DERIVED_COUNTERS_API_SRC_DX11
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_dx11_gfx10.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_dx11_gfx103.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_dx11_gfx11.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_dx11_gfx8.cc
${CMAKE_CURRENT_LIST_DIR}/public_derived_counters_dx11_gfx9.cc)

