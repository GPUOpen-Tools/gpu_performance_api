## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(PUBLIC_COUNTERS_TEST_API_HEADERS
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersHSAGfx8.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersHSAGfx9.h
    ${ADDITIONAL_TEST_API_HEADERS_HSA})

set(PUBLIC_COUNTERS_TEST_API_SRC
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersHSAGfx8.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersHSAGfx9.cpp
    ${ADDITIONAL_TEST_API_SRC_HSA})