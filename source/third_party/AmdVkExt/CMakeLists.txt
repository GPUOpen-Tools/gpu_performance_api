## Copyright (C) 2025-2026 Advanced Micro Devices, Inc. All rights reserved. ##

add_library(amd_vulkan_extensions INTERFACE)
add_library(AMD::VulkanExtensions ALIAS amd_vulkan_extensions)

# The Vulkan header files are originally from
# https://github.com/GPUOpen-Drivers/xgl/tree/dev/icd/api/include/khronos/devext
target_sources(amd_vulkan_extensions PUBLIC
    FILE_SET public_headers
    TYPE "HEADERS"
    BASE_DIRS .
    FILES
        vk_amd_gpa_interface.h
        vk_internal_ext_helper.h
)

# The amd header files depend on the vulkan header files to work at all
target_link_libraries(amd_vulkan_extensions INTERFACE Vulkan::Headers)
