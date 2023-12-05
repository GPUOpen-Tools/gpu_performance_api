## Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

find_package(Vulkan)
if(${Vulkan_FOUND})
    set(VK_INC_DIRS "${Vulkan_INCLUDE_DIRS}")
    if(WIN32)
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(VK_LIB "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib")
            find_path(VK_TOOLS_DIR NAMES glslangValidator.exe PATHS "$ENV{VULKAN_SDK}/Bin")
        else()
            set(VK_LIB "$ENV{VULKAN_SDK}/Lib32/vulkan-1.lib")
            find_path(VK_TOOLS_DIR NAMES glslangValidator.exe PATHS "$ENV{VULKAN_SDK}/Bin32")
        endif()
    else()
        set(VK_LIB "${Vulkan_LIBRARIES}")
        find_path(VK_TOOLS_DIR NAMES glslangValidator PATHS "$ENV{VULKAN_SDK}/bin")
    endif()
else()
    if(WIN32)
        set(VK_INC_DIRS ${GPA_SRC_THIRD_PARTY}/Vulkan/Windows/Include)
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(VK_LIB ${GPA_SRC_THIRD_PARTY}/Vulkan/Windows/Lib/vulkan-1.lib)
            set(VK_TOOLS_DIR ${GPA_SRC_THIRD_PARTY}/Vulkan/Windows/Bin)
        else()
            set(VK_LIB ${GPA_SRC_THIRD_PARTY}/Vulkan/Windows/Lib32/vulkan-1.lib)
            set(VK_TOOLS_DIR ${GPA_SRC_THIRD_PARTY}/Vulkan/Windows/Bin32)
        endif()
    else()
        set(VK_INC_DIRS ${GPA_SRC_THIRD_PARTY}/Vulkan/Linux/x86_64/include)
        set(VK_LIB ${GPA_SRC_THIRD_PARTY}/Vulkan/Linux/x86_64/lib/libvulkan.so)
        set(VK_TOOLS_DIR ${GPA_SRC_THIRD_PARTY}/Vulkan/Linux/x86_64/bin/)
    endif()
endif()

set(ADDITIONAL_DEFINTIONS ${ADDITIONAL_DEFINTIONS}
                          -DVK_INC_DIRS="${VK_INC_DIRS}")

set(ADDITIONAL_INCLUDE_DIRECTORIES  ${ADDITIONAL_INCLUDE_DIRECTORIES}
                                    ${VK_INC_DIRS})


