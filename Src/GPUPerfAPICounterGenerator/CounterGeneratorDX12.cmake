## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(COUNTER_GENERATORS_API_HEADERS
    GPACounterGeneratorDX12.h
    GPACounterGeneratorDX12Base.h
    GPACounterGeneratorDX12NonAMD.h)

set(COUNTER_GENERATORS_API_SRC
    GPACounterGeneratorDX12.cpp
    GPACounterGeneratorDX12Base.cpp
    GPACounterGeneratorDX12NonAMD.cpp)

set(COUNTER_SCHEDULERS_API_HEADERS
    GPACounterSchedulerDX12.h)

set(COUNTER_SCHEDULERS_API_SRC
    GPACounterSchedulerDX12.cpp)

set(INTERNAL_COUNTERS_API_HEADERS
    InternalCountersDX12Gfx7.h
    InternalCountersDX12Gfx8.h
    InternalCountersDX12Gfx9.h
    ${ADDITIONAL_COUNTER_GEN_HEADERS_DX12})

set(INTERNAL_COUNTERS_API_SRC
    InternalCountersDX12Gfx7.cpp
    InternalCountersDX12Gfx8.cpp
    InternalCountersDX12Gfx9.cpp
    ${ADDITIONAL_COUNTER_GEN_SOURCES_DX12})

set(PUBLIC_COUNTERS_API_HEADERS
    PublicCounterDefsDX12Gfx7.h
    PublicCounterDefsDX12Gfx7Asics.h
    PublicCounterDefsDX12Gfx8.h
    PublicCounterDefsDX12Gfx8_Baffin.h
    PublicCounterDefsDX12Gfx8_Carrizo.h
    PublicCounterDefsDX12Gfx8_Ellesmere.h
    PublicCounterDefsDX12Gfx8_Fiji.h
    PublicCounterDefsDX12Gfx8_Iceland.h
    PublicCounterDefsDX12Gfx8_Tonga.h
    PublicCounterDefsDX12Gfx8Asics.h
    PublicCounterDefsDX12Gfx9.h
    PublicCounterDefsDX12Gfx9_Placeholder4.h
    PublicCounterDefsDX12Gfx9_Gfx906.h
    PublicCounterDefsDX12Gfx9Asics.h)

set(PUBLIC_COUNTERS_API_SRC
    PublicCounterDefsDX12Gfx7.cpp
    PublicCounterDefsDX12Gfx8.cpp
    PublicCounterDefsDX12Gfx8_Baffin.cpp
    PublicCounterDefsDX12Gfx8_Carrizo.cpp
    PublicCounterDefsDX12Gfx8_Ellesmere.cpp
    PublicCounterDefsDX12Gfx8_Fiji.cpp
    PublicCounterDefsDX12Gfx8_Iceland.cpp
    PublicCounterDefsDX12Gfx8_Tonga.cpp
    PublicCounterDefsDX12Gfx9.cpp
    PublicCounterDefsDX12Gfx9_Placeholder4.cpp
    PublicCounterDefsDX12Gfx9_Gfx906.cpp)
