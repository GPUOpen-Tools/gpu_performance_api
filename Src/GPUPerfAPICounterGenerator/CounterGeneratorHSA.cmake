## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(COUNTER_GENERATORS_API_HEADERS
    GPACounterGeneratorHSA.h)

set(COUNTER_GENERATORS_API_SRC
    GPACounterGeneratorHSA.cpp)

set(COUNTER_SCHEDULERS_API_HEADERS
    GPACounterSchedulerHSA.h)

set(COUNTER_SCHEDULERS_API_SRC
    GPACounterSchedulerHSA.cpp)

set(INTERNAL_COUNTERS_API_HEADERS
    InternalCountersHSAGfx8.h
    InternalCountersHSAGfx9.h
    ${ADDITIONAL_COUNTER_GEN_HEADERS_HSA})

set(INTERNAL_COUNTERS_API_SRC
    InternalCountersHSAGfx8.cpp
    InternalCountersHSAGfx9.cpp
    ${ADDITIONAL_COUNTER_GEN_SOURCES_HSA})

set(PUBLIC_COUNTERS_API_HEADERS
    PublicCounterDefsHSAGfx8.h
    PublicCounterDefsHSAGfx8_Fiji.h
    PublicCounterDefsHSAGfx8Asics.h
    PublicCounterDefsHSAGfx9.h
    PublicCounterDefsHSAGfx9_Placeholder4.h
    PublicCounterDefsHSAGfx9_Gfx906.h
    PublicCounterDefsHSAGfx9Asics.h)

set(PUBLIC_COUNTERS_API_SRC
    PublicCounterDefsHSAGfx8.cpp
    PublicCounterDefsHSAGfx8_Fiji.cpp
    PublicCounterDefsHSAGfx9.cpp
    PublicCounterDefsHSAGfx9_Placeholder4.cpp
    PublicCounterDefsHSAGfx9_Gfx906.cpp)
