## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(PUBLIC_COUNTERS_TEST_API_HEADERS
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersCLGfx6.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersCLGfx7.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersCLGfx8.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersCLGfx9.h
    ${ADDITIONAL_TEST_API_HEADERS_CL})

set(PUBLIC_COUNTERS_TEST_API_SRC
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersCLGfx6.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersCLGfx7.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersCLGfx8.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersCLGfx9.cpp
    ${ADDITIONAL_TEST_API_SRC_CL})