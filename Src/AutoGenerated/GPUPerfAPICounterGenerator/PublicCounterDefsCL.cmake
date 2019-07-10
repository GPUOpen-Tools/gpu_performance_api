## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_COUNTER_DEF_HEADERS_CL
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx10.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx10Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Baffin.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Carrizo.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Ellesmere.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Fiji.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Iceland.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Tonga.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx9.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx9Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx9_Gfx906.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx9_Placeholder4.h)

set(PUBLIC_COUNTER_DEF_SRC_CL
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx10.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Baffin.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Carrizo.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Ellesmere.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Fiji.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Iceland.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx8_Tonga.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx9.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx9_Gfx906.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsCLGfx9_Placeholder4.cpp)

