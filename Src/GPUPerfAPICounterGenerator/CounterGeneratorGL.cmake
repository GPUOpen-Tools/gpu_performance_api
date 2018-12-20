## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(COUNTER_GENERATORS_API_HEADERS
    GLEntryPoints.h
    GPACounterGeneratorGL.h)

set(COUNTER_GENERATORS_API_SRC
    GLEntryPoints.cpp
    GPACounterGeneratorGL.cpp)

set(COUNTER_SCHEDULERS_API_HEADERS
    GPACounterSchedulerGL.h)

set(COUNTER_SCHEDULERS_API_SRC
    GPACounterSchedulerGL.cpp)

set(INTERNAL_COUNTERS_API_HEADERS
    InternalCountersGLGfx6.h
    InternalCountersGLGfx7.h
    InternalCountersGLGfx8.h
    InternalCountersGLGfx9.h
    ${ADDITIONAL_COUNTER_GEN_HEADERS_GL})

set(INTERNAL_COUNTERS_API_SRC
    InternalCountersGLGfx6.cpp
    InternalCountersGLGfx7.cpp
    InternalCountersGLGfx8.cpp
    InternalCountersGLGfx9.cpp
    ${ADDITIONAL_COUNTER_GEN_SOURCES_GL})

set(PUBLIC_COUNTERS_API_HEADERS
    PublicCounterDefsGLGfx6.h
    PublicCounterDefsGLGfx6Asics.h
    PublicCounterDefsGLGfx7.h
    PublicCounterDefsGLGfx7Asics.h
    PublicCounterDefsGLGfx8.h
    PublicCounterDefsGLGfx8_Baffin.h
    PublicCounterDefsGLGfx8_Carrizo.h
    PublicCounterDefsGLGfx8_Ellesmere.h
    PublicCounterDefsGLGfx8_Fiji.h
    PublicCounterDefsGLGfx8_Iceland.h
    PublicCounterDefsGLGfx8_Tonga.h
    PublicCounterDefsGLGfx8Asics.h
    PublicCounterDefsGLGfx9.h
    PublicCounterDefsGLGfx9_Placeholder4.h
    PublicCounterDefsGLGfx9_Gfx906.h
    PublicCounterDefsGLGfx9Asics.h)

set(PUBLIC_COUNTERS_API_SRC
    PublicCounterDefsGLGfx6.cpp
    PublicCounterDefsGLGfx7.cpp
    PublicCounterDefsGLGfx8.cpp
    PublicCounterDefsGLGfx8_Baffin.cpp
    PublicCounterDefsGLGfx8_Carrizo.cpp
    PublicCounterDefsGLGfx8_Ellesmere.cpp
    PublicCounterDefsGLGfx8_Fiji.cpp
    PublicCounterDefsGLGfx8_Iceland.cpp
    PublicCounterDefsGLGfx8_Tonga.cpp
    PublicCounterDefsGLGfx9.cpp
    PublicCounterDefsGLGfx9_Placeholder4.cpp
    PublicCounterDefsGLGfx9_Gfx906.cpp)