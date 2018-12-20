## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(PUBLIC_COUNTERS_TEST_API_HEADERS
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX12Gfx7.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX12Gfx8.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX12Gfx9.h
    ${ADDITIONAL_TEST_API_HEADERS_DX12})

set(PUBLIC_COUNTERS_TEST_API_SRC
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX12Gfx7.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX12Gfx8.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX12Gfx9.cpp
    ${ADDITIONAL_TEST_API_SRC_DX12})
