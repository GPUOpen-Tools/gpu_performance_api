## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(COUNTER_GENERATOR_HEADERS_VK
    GPACounterGeneratorVK.h
    GPACounterGeneratorVKBase.h
    GPACounterGeneratorVKNonAMD.h)

set(COUNTER_GENERATOR_SRC_VK
    GPACounterGeneratorVK.cpp
    GPACounterGeneratorVKBase.cpp
    GPACounterGeneratorVKNonAMD.cpp)

set(COUNTER_SCHEDULER_HEADERS_VK
    GPACounterSchedulerVK.h)

set(COUNTER_SCHEDULER_SRC_VK
    GPACounterSchedulerVK.cpp)
