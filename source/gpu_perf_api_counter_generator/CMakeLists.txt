## Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

set(DEPTH "../../")

include ("counter_generator_common.cmake")

if(NOT ${skipvulkan})
    include ("counter_generator_vk.cmake")
endif()

if(NOT ${skipopengl})
    include ("counter_generator_gl.cmake")
endif()

if(NOT ${skipopencl})
    include ("counter_generator_cl.cmake")
endif()

if(WIN32)
    if(NOT ${skipdx12})
        include ("counter_generator_dx12.cmake")
    endif()

    if(NOT ${skipdx11})
        include ("counter_generator_dx11.cmake")
    endif()
endif()
