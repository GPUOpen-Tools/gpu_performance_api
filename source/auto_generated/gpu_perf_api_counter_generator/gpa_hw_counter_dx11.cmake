## Copyright (c) 2024 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(HW_COUNTER_HEADERS_DX11
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_dx11_gfx10.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_dx11_gfx103.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_dx11_gfx11.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_dx11_gfx8.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_dx11_gfx9.h)

set(HW_COUNTER_SRC_DX11
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_dx11_gfx10.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_dx11_gfx103.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_dx11_gfx11.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_dx11_gfx8.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_dx11_gfx9.cc)

