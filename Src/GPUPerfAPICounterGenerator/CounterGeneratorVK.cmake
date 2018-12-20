## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(COUNTER_GENERATORS_API_HEADERS
    GPACounterGeneratorVK.h
    GPACounterGeneratorVKBase.h
    GPACounterGeneratorVKNonAMD.h)

set(COUNTER_GENERATORS_API_SRC
    GPACounterGeneratorVK.cpp
    GPACounterGeneratorVKBase.cpp
    GPACounterGeneratorVKNonAMD.cpp)

set(COUNTER_SCHEDULERS_API_HEADERS
    GPACounterSchedulerVK.h)

set(COUNTER_SCHEDULERS_API_SRC
    GPACounterSchedulerVK.cpp)

set(INTERNAL_COUNTERS_API_HEADERS
    InternalCountersVKGfx7.h
    InternalCountersVKGfx8.h
    InternalCountersVKGfx9.h
    ${ADDITIONAL_COUNTER_GEN_HEADERS_VK})

set(INTERNAL_COUNTERS_API_SRC
    InternalCountersVKGfx7.cpp
    InternalCountersVKGfx8.cpp
    InternalCountersVKGfx9.cpp
    ${ADDITIONAL_COUNTER_GEN_SOURCES_VK})

set(PUBLIC_COUNTERS_API_HEADERS
    PublicCounterDefsVKGfx7.h
    PublicCounterDefsVKGfx7Asics.h
    PublicCounterDefsVKGfx8.h
    PublicCounterDefsVKGfx8_Baffin.h
    PublicCounterDefsVKGfx8_Carrizo.h
    PublicCounterDefsVKGfx8_Ellesmere.h
    PublicCounterDefsVKGfx8_Fiji.h
    PublicCounterDefsVKGfx8_Iceland.h
    PublicCounterDefsVKGfx8_Tonga.h
    PublicCounterDefsVKGfx8Asics.h
    PublicCounterDefsVKGfx9.h
    PublicCounterDefsVKGfx9_Placeholder4.h
    PublicCounterDefsVKGfx9_Gfx906.h
    PublicCounterDefsVKGfx9Asics.h)

set(PUBLIC_COUNTERS_API_SRC
    PublicCounterDefsVKGfx7.cpp
    PublicCounterDefsVKGfx8.cpp
    PublicCounterDefsVKGfx8_Baffin.cpp
    PublicCounterDefsVKGfx8_Carrizo.cpp
    PublicCounterDefsVKGfx8_Ellesmere.cpp
    PublicCounterDefsVKGfx8_Fiji.cpp
    PublicCounterDefsVKGfx8_Iceland.cpp
    PublicCounterDefsVKGfx8_Tonga.cpp
    PublicCounterDefsVKGfx9.cpp
    PublicCounterDefsVKGfx9_Placeholder4.cpp
    PublicCounterDefsVKGfx9_Gfx906.cpp)
