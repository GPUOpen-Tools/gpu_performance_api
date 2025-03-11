## Copyright (c) 2025 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(HW_COUNTER_HEADERS_GL
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_oglp_gfx10.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_oglp_gfx103.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_oglp_gfx11.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_oglp_gfx12.h)

set(HW_COUNTER_SRC_GL
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_oglp_gfx10.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_oglp_gfx103.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_oglp_gfx11.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_oglp_gfx12.cc)

