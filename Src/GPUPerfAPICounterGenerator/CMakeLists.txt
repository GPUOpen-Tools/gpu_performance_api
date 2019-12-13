## Copyright (c) 2018-2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

include ("CounterGeneratorCommon.cmake")

if(NOT ${skipvulkan})
    include ("CounterGeneratorVK.cmake")
endif()

if(NOT ${skipopengl})
    include ("CounterGeneratorGL.cmake")
endif()

if(NOT ${skipopencl})
    include ("CounterGeneratorCL.cmake")
endif()

if(WIN32)
    if(NOT ${skipdx12})
        include ("CounterGeneratorDX12.cmake")
    endif()

    if(NOT ${skipdx11})
        include ("CounterGeneratorDX11.cmake")
    endif()
endif()
