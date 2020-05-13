## Copyright (c) 2020 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(HW_COUNTER_HEADERS
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx10.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_baffin.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_carrizo.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_ellesmere.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_fiji.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_iceland.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_tonga.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx9.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx9_gfx906.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx9_gfx909.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx9_placeholder4.h)

set(HW_COUNTER_SRC
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx10.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_baffin.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_carrizo.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_ellesmere.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_fiji.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_iceland.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx8_tonga.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx9.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx9_gfx906.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx9_gfx909.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_gfx9_placeholder4.cc)

