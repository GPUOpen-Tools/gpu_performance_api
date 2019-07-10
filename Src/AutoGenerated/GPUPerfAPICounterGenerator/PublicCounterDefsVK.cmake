## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_COUNTER_DEF_HEADERS_VK
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx10.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx10Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Baffin.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Carrizo.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Ellesmere.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Fiji.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Iceland.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Tonga.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx9.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx9Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx9_Gfx906.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx9_Placeholder4.h)

set(PUBLIC_COUNTER_DEF_SRC_VK
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx10.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Baffin.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Carrizo.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Ellesmere.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Fiji.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Iceland.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx8_Tonga.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx9.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx9_Gfx906.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsVKGfx9_Placeholder4.cpp)

