## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_COUNTER_NAMES_VK
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx10.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx8.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx8_Baffin.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx8_Carrizo.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx8_Ellesmere.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx8_Fiji.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx8_Iceland.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx8_Tonga.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx9.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx9_Gfx906.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesVKGfx9_Placeholder4.txt)