## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(COUNTER_GENERATOR_HEADERS_DX12
    GPACounterGeneratorDX12.h
    GPACounterGeneratorDX12Base.h
    GPACounterGeneratorDX12NonAMD.h)

set(COUNTER_GENERATOR_SRC_DX12
    GPACounterGeneratorDX12.cpp
    GPACounterGeneratorDX12Base.cpp
    GPACounterGeneratorDX12NonAMD.cpp)

set(COUNTER_SCHEDULER_HEADERS_DX12
    GPACounterSchedulerDX12.h)

set(COUNTER_SCHEDULER_SRC_DX12
    GPACounterSchedulerDX12.cpp)

