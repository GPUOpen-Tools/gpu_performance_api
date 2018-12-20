## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(PUBLIC_COUNTERS_TEST_API_HEADERS
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersGLGfx6.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersGLGfx7.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersGLGfx8.h
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersGLGfx9.h
    ${ADDITIONAL_TEST_API_HEADERS_GL})


set(PUBLIC_COUNTERS_TEST_API_SRC
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersGLGfx6.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersGLGfx7.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersGLGfx8.cpp
    ${GPA_SRC_TESTS}/counters/PublicDerivedCountersGLGfx9.cpp
    ${ADDITIONAL_TEST_API_SRC_GL})