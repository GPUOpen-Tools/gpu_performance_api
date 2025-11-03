## Copyright (C) 2025 Advanced Micro Devices, Inc. All rights reserved. ##

cmake_minimum_required(VERSION 3.10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(HW_COUNTER_HEADERS
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx10.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx103.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx103_gfx1031_gfx1032.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx103_gfx1033.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx11.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx11_gfx1103.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx11_gfx1150.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx12.h)

set(HW_COUNTER_SRC
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx10.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx103.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx103_gfx1031_gfx1032.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx103_gfx1033.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx11.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx11_gfx1103.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx11_gfx1150.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx12.cc)

