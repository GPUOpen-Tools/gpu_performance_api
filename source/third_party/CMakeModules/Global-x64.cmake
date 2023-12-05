## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED AMDTPlatform)
    set(AMDTPlatform "x64")
endif()

if(NOT DEFINED AMDTPlatformExt)
    set(AMDTPlatformExt "x86_64")
endif()

if(NOT DEFINED AMDTPlatformSuffix)
    if(WIN32)
        set(AMDTPlatformSuffix "-x64")
    else()
        set(AMDTPlatformSuffix "")
    endif()
endif()

if(NOT DEFINED AMDTPlatformSuffixNumBitsOnly)
    set(AMDTPlatformSuffixNumBitsOnly "64")
endif()

if(WIN32)
    set(COMMON_LINKER_FLAGS /MACHINE:X64)
else()
    set(COMMON_COMPILATION_FLAGS ${COMMON_COMPILATION_FLAGS} -m64)
    set(COMMON_LINKER_FLAGS -m64)
endif()

set(COMMON_PREPROCESSOR_DEFINITION ${COMMON_PREPROCESSOR_DEFINITION} X64)
