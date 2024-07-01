## Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED AMDTPlatform)
    set(AMDTPlatform "x86")
endif()

if(NOT DEFINED AMDTPlatformExt)
    set(AMDTPlatformExt "x86")
endif()

if(NOT DEFINED AMDTPlatformSuffix)
    if(WIN32)
        set(AMDTPlatformSuffix "")
    else()
        set(AMDTPlatformSuffix "32")
    endif()
endif()

if(NOT DEFINED AMDTPlatformSuffixNumBitsOnly)
    set(AMDTPlatformSuffixNumBitsOnly "")
endif()

if(WIN32)
    set(COMMON_LINKER_FLAGS /MACHINE:X86)
else()
    set(COMMON_COMPILATION_FLAGS ${COMMON_COMPILATION_FLAGS} -m32)
    set(COMMON_LINKER_FLAGS -m32)
endif(WIN32)

set(COMMON_PREPROCESSOR_DEFINITION ${COMMON_PREPROCESSOR_DEFINITION} X86)
