## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_DERIVED_COUNTERS_API_HEADERS_DX11
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersDX11Gfx10.h
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersDX11Gfx8.h
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersDX11Gfx9.h)

set(PUBLIC_DERIVED_COUNTERS_API_SRC_DX11
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersDX11Gfx10.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersDX11Gfx8.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicDerivedCountersDX11Gfx9.cpp)

