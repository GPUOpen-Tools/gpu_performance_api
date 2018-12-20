## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(PUBLIC_COUNTERS_TEST_API_HEADERS
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX11Gfx6.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX11Gfx7.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX11Gfx8.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX11Gfx9.h
    ${ADDITIONAL_TEST_API_HEADERS_DX11})

set(PUBLIC_COUNTERS_TEST_API_SRC
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX11Gfx6.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX11Gfx7.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX11Gfx8.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersDX11Gfx9.cpp
    ${ADDITIONAL_TEST_API_SRC_DX11})
