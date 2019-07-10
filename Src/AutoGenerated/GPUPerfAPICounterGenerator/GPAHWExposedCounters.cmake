## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(HW_EXPOSED_COUNTER_HEADERS
${CMAKE_CURRENT_LIST_DIR}/GPAHWExposedCountersGfx10.h
${CMAKE_CURRENT_LIST_DIR}/GPAHWExposedCountersGfx8.h
${CMAKE_CURRENT_LIST_DIR}/GPAHWExposedCountersGfx9.h)

set(HW_EXPOSED_COUNTER_SRC
${CMAKE_CURRENT_LIST_DIR}/GPAHWExposedCountersGfx10.cpp
${CMAKE_CURRENT_LIST_DIR}/GPAHWExposedCountersGfx8.cpp
${CMAKE_CURRENT_LIST_DIR}/GPAHWExposedCountersGfx9.cpp)

