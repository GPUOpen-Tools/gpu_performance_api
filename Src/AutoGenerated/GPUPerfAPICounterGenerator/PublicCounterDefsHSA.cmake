## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_COUNTER_DEF_HEADERS_HSA
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx8.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx8Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx8_Fiji.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx9.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx9Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx9_Gfx906.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx9_Placeholder4.h)

set(PUBLIC_COUNTER_DEF_SRC_HSA
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx8.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx8_Fiji.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx9.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx9_Gfx906.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsHSAGfx9_Placeholder4.cpp)

