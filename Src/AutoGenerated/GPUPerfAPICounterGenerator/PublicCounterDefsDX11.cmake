## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_COUNTER_DEF_HEADERS_DX11
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx10.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx10Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Baffin.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Carrizo.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Ellesmere.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Fiji.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Iceland.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Tonga.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx9.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx9Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx9_Gfx906.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx9_Placeholder4.h)

set(PUBLIC_COUNTER_DEF_SRC_DX11
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx10.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Baffin.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Carrizo.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Ellesmere.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Fiji.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Iceland.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx8_Tonga.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx9.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx9_Gfx906.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsDX11Gfx9_Placeholder4.cpp)

