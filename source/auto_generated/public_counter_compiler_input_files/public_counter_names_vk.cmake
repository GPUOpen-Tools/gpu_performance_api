## Copyright (c) 2022 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_COUNTER_NAMES_VK
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx10.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx103.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx103_gfx1031_gfx1032.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx8.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx8_baffin.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx8_carrizo.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx8_ellesmere.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx8_fiji.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx8_iceland.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx8_tonga.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx9.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx9_gfx906.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx9_gfx909.txt
${CMAKE_CURRENT_LIST_DIR}/public_counter_names_vk_gfx9_placeholder4.txt)