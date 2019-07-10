## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PUBLIC_COUNTER_DEF_HEADERS_GL
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx10.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx10Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Baffin.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Carrizo.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Ellesmere.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Fiji.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Iceland.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Tonga.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx9.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx9Asics.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx9_Gfx906.h
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx9_Placeholder4.h)

set(PUBLIC_COUNTER_DEF_SRC_GL
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx10.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Baffin.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Carrizo.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Ellesmere.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Fiji.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Iceland.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx8_Tonga.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx9.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx9_Gfx906.cpp
${CMAKE_CURRENT_LIST_DIR}/PublicCounterDefsGLGfx9_Placeholder4.cpp)

