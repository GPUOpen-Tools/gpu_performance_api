## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(PUBLIC_COUNTERS_TEST_API_HEADERS
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersVKGfx7.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersVKGfx8.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersVKGfx9.h
    ${ADDITIONAL_TEST_API_HEADERS_VK})

set(PUBLIC_COUNTERS_TEST_API_SRC
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersVKGfx7.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersVKGfx8.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersVKGfx9.cpp
    ${ADDITIONAL_TEST_API_SRC_VK})
