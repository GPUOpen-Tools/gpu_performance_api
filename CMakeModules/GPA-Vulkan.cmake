## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

if(${GPA_ALL_OPEN_SOURCE})
    if(DEFINED ENV{VULKAN_SDK})
        set(VULKAN_SDK $ENV{VULKAN_SDK})
        if(WIN32)
            set(ADDITIONAL_INCLUDE_DIRECTORIES ${ADDITIONAL_INCLUDE_DIRECTORIES}
                                           ${VULKAN_SDK}/Include)
        else()
            set(ADDITIONAL_INCLUDE_DIRECTORIES ${ADDITIONAL_INCLUDE_DIRECTORIES}
                                   ${VULKAN_SDK}/include)
        endif()

        set(ADDITIONAL_DEFINTIONS ${ADDITIONAL_DEFINTIONS}
                          -DVULKAN_SDK="${VULKAN_SDK}")

        if(WIN32)
            if(CMAKE_SIZEOF_VOID_P EQUAL 8)
                set(ADDITIONAL_LINK_DIRECTORIES ${ADDITIONAL_LINK_DIRECTORIES}
                                                ${VULKAN_SDK}/Lib)
            else()
                set(ADDITIONAL_LINK_DIRECTORIES ${ADDITIONAL_LINK_DIRECTORIES}
                                                ${VULKAN_SDK}/Lib32)
            endif()
        else()
            set(ADDITIONAL_LINK_DIRECTORIES ${ADDITIONAL_LINK_DIRECTORIES}
                                            ${VULKAN_SDK}/lib)
        endif()
    else()
        message("CMake: Vulkan SDK not found")
    endif()
else()
    include(${CMAKE_COMMON_LIB_GLOBAL_EXT_VULKAN})
endif()