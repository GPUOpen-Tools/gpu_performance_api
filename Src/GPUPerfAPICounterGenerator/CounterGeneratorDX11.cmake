## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(COUNTER_GENERATOR_HEADERS_DX11
    GPACounterGeneratorDX11.h
    GPACounterGeneratorDX11Base.h
    GPACounterGeneratorDX11NonAMD.h)

set(COUNTER_GENERATOR_SRC_DX11
    GPACounterGeneratorDX11.cpp
    GPACounterGeneratorDX11Base.cpp
    GPACounterGeneratorDX11NonAMD.cpp)

set(COUNTER_SCHEDULER_HEADERS_DX11
    GPACounterSchedulerDX11.h)

set(COUNTER_SCHEDULER_SRC_DX11
    GPACounterSchedulerDX11.cpp)
