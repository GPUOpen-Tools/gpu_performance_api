## Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

if(${GPA_ALL_OPEN_SOURCE})
    find_package(Vulkan REQUIRED)
    if(${Vulkan_FOUND})
        set(VK_INC_DIRS ${Vulkan_INCLUDE_DIRS})
        set(VK_LIB ${Vulkan_LIBRARIES})
        if(WIN32)
            if(CMAKE_SIZEOF_VOID_P EQUAL 8)
                find_path(VK_TOOLS_DIR NAMES glslangValidator.exe PATHS "$ENV{VULKAN_SDK}/Bin")
            else()
                find_path(VK_TOOLS_DIR NAMES glslangValidator.exe PATHS "$ENV{VULKAN_SDK}/Bin32")
            endif()
        else()
            find_path(VK_TOOLS_DIR NAMES glslangValidator PATHS "$ENV{VULKAN_SDK}/bin")
        endif()

        set(ADDITIONAL_DEFINTIONS ${ADDITIONAL_DEFINTIONS}
                                  -DVK_INC_DIRS="${VK_INC_DIRS}")

        set(ADDITIONAL_INCLUDE_DIRECTORIES  ${ADDITIONAL_INCLUDE_DIRECTORIES}
                                            ${VK_INC_DIRS})
    else()
        message(STATUS "Vulkan SDK not found")
    endif()
else()
    include(${CMAKE_COMMON_LIB_GLOBAL_EXT_VULKAN})
endif()

message(STATUS "Using vulkan headers from ${VK_INC_DIRS}, libraries from ${VK_LIB} and tools from ${VK_TOOLS_DIR}")
