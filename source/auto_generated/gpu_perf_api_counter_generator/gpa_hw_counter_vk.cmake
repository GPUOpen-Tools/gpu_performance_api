## Copyright (c) 2020 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(HW_COUNTER_HEADERS_VK
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx10.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx8.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx9.h)

set(HW_COUNTER_SRC_VK
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx10.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx8.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx9.cc)

