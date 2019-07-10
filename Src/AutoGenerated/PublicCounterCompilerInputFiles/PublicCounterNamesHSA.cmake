## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_COUNTER_NAMES_HSA
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesHSAGfx8.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesHSAGfx8_Fiji.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesHSAGfx9.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesHSAGfx9_Gfx906.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesHSAGfx9_Placeholder4.txt)