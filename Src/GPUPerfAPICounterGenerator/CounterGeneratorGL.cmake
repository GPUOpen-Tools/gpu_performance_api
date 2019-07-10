## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(COUNTER_GENERATOR_HEADERS_GL
    GLEntryPoints.h
    GPACounterGeneratorGL.h
    GLFunctions.h
    GLFuncTypes.h)

set(COUNTER_GENERATOR_SRC_GL
    GLEntryPoints.cpp
    GPACounterGeneratorGL.cpp)

set(COUNTER_SCHEDULER_HEADERS_GL
    GPACounterSchedulerGL.h)

set(COUNTER_SCHEDULER_SRC_GL
    GPACounterSchedulerGL.cpp)
