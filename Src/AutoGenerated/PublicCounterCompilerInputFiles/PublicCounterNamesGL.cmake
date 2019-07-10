## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_COUNTER_NAMES_GL
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx10.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx8.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx8_Baffin.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx8_Carrizo.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx8_Ellesmere.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx8_Fiji.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx8_Iceland.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx8_Tonga.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx9.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx9_Gfx906.txt
${CMAKE_CURRENT_LIST_DIR}/PublicCounterNamesGLGfx9_Placeholder4.txt)