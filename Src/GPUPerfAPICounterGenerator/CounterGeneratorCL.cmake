## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(COUNTER_GENERATORS_API_HEADERS
    GPACounterGeneratorCL.h)

set(COUNTER_GENERATORS_API_SRC
    GPACounterGeneratorCL.cpp)

set(COUNTER_SCHEDULERS_API_HEADERS
    GPACounterSchedulerCL.h)

set(COUNTER_SCHEDULERS_API_SRC
    GPACounterSchedulerCL.cpp)

set(INTERNAL_COUNTERS_API_HEADERS
    InternalCountersCLGfx6.h
    InternalCountersCLGfx7.h
    InternalCountersCLGfx8.h
    InternalCountersCLGfx9.h
    ${ADDITIONAL_COUNTER_GEN_HEADERS_CL})

set(INTERNAL_COUNTERS_API_SRC
    InternalCountersCLGfx6.cpp
    InternalCountersCLGfx7.cpp
    InternalCountersCLGfx8.cpp
    InternalCountersCLGfx9.cpp
    ${ADDITIONAL_COUNTER_GEN_SOURCES_CL})

set(PUBLIC_COUNTERS_API_HEADERS
    PublicCounterDefsCLGfx6.h
    PublicCounterDefsCLGfx6Asics.h
    PublicCounterDefsCLGfx7.h
    PublicCounterDefsCLGfx7Asics.h
    PublicCounterDefsCLGfx8.h
    PublicCounterDefsCLGfx8_Baffin.h
    PublicCounterDefsCLGfx8_Carrizo.h
    PublicCounterDefsCLGfx8_Ellesmere.h
    PublicCounterDefsCLGfx8_Fiji.h
    PublicCounterDefsCLGfx8_Iceland.h
    PublicCounterDefsCLGfx8_Tonga.h
    PublicCounterDefsCLGfx8Asics.h
    PublicCounterDefsCLGfx9.h
    PublicCounterDefsCLGfx9_Placeholder4.h
    PublicCounterDefsCLGfx9_Gfx906.h
    PublicCounterDefsCLGfx9Asics.h)

set(PUBLIC_COUNTERS_API_SRC
    PublicCounterDefsCLGfx6.cpp
    PublicCounterDefsCLGfx7.cpp
    PublicCounterDefsCLGfx8.cpp
    PublicCounterDefsCLGfx8_Baffin.cpp
    PublicCounterDefsCLGfx8_Carrizo.cpp
    PublicCounterDefsCLGfx8_Ellesmere.cpp
    PublicCounterDefsCLGfx8_Fiji.cpp
    PublicCounterDefsCLGfx8_Iceland.cpp
    PublicCounterDefsCLGfx8_Tonga.cpp
    PublicCounterDefsCLGfx9.cpp
    PublicCounterDefsCLGfx9_Placeholder4.cpp
    PublicCounterDefsCLGfx9_Gfx906.cpp)