## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(COUNTER_GENERATORS_API_HEADERS
    GPACounterGeneratorDX11.h
    GPACounterGeneratorDX11Base.h
    GPACounterGeneratorDX11NonAMD.h)

set(COUNTER_GENERATORS_API_SRC
    GPACounterGeneratorDX11.cpp
    GPACounterGeneratorDX11Base.cpp
    GPACounterGeneratorDX11NonAMD.cpp)

set(COUNTER_SCHEDULERS_API_HEADERS
    GPACounterSchedulerDX11.h)

set(COUNTER_SCHEDULERS_API_SRC
    GPACounterSchedulerDX11.cpp)

set(INTERNAL_COUNTERS_API_HEADERS
    InternalCountersDX11Gfx6.h
    InternalCountersDX11Gfx7.h
    InternalCountersDX11Gfx8.h
    InternalCountersDX11Gfx9.h
    ${ADDITIONAL_COUNTER_GEN_HEADERS_DX11})

set(INTERNAL_COUNTERS_API_SRC
    InternalCountersDX11Gfx6.cpp
    InternalCountersDX11Gfx7.cpp
    InternalCountersDX11Gfx8.cpp
    InternalCountersDX11Gfx9.cpp
    ${ADDITIONAL_COUNTER_GEN_SOURCES_DX11})

set(PUBLIC_COUNTERS_API_HEADERS
    PublicCounterDefsDX11Gfx6.h
    PublicCounterDefsDX11Gfx6Asics.h
    PublicCounterDefsDX11Gfx7.h
    PublicCounterDefsDX11Gfx7Asics.h
    PublicCounterDefsDX11Gfx8.h
    PublicCounterDefsDX11Gfx8_Baffin.h
    PublicCounterDefsDX11Gfx8_Carrizo.h
    PublicCounterDefsDX11Gfx8_Ellesmere.h
    PublicCounterDefsDX11Gfx8_Fiji.h
    PublicCounterDefsDX11Gfx8_Iceland.h
    PublicCounterDefsDX11Gfx8_Tonga.h
    PublicCounterDefsDX11Gfx8Asics.h
    PublicCounterDefsDX11Gfx9.h
    PublicCounterDefsDX11Gfx9_Placeholder4.h
    PublicCounterDefsDX11Gfx9_Gfx906.h
    PublicCounterDefsDX11Gfx9Asics.h)

set(PUBLIC_COUNTERS_API_SRC
    PublicCounterDefsDX11Gfx6.cpp
    PublicCounterDefsDX11Gfx7.cpp
    PublicCounterDefsDX11Gfx8.cpp
    PublicCounterDefsDX11Gfx8_Baffin.cpp
    PublicCounterDefsDX11Gfx8_Carrizo.cpp
    PublicCounterDefsDX11Gfx8_Ellesmere.cpp
    PublicCounterDefsDX11Gfx8_Fiji.cpp
    PublicCounterDefsDX11Gfx8_Iceland.cpp
    PublicCounterDefsDX11Gfx8_Tonga.cpp
    PublicCounterDefsDX11Gfx9.cpp
    PublicCounterDefsDX11Gfx9_Placeholder4.cpp
    PublicCounterDefsDX11Gfx9_Gfx906.cpp)