## Copyright (C) 2025-2026 Advanced Micro Devices, Inc. All rights reserved. ##

set(HW_COUNTER_HEADERS_VK
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx10.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx103.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx11.h
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx12.h)

set(HW_COUNTER_SRC_VK
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx10.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx103.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx11.cc
${CMAKE_CURRENT_LIST_DIR}/gpa_hw_counter_vk_gfx12.cc)

