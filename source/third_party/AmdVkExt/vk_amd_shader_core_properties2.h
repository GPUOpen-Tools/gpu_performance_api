/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2019 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 **********************************************************************************************************************/
/**
 **********************************************************************************************************************
 * @file  vk_amd_shader_core_properties2.h
 * @brief Temporary internal header for shader core properties2. Should be removed once the extension is published
 *        and the API gets included in the official Vulkan header.
 **********************************************************************************************************************
 */
#ifndef VK_AMD_SHADER_CORE_PROPERTIES2_H_
#define VK_AMD_SHADER_CORE_PROPERTIES2_H_

#include "vk_internal_ext_helper.h"

#define VK_AMD_shader_core_properties2                             1
#define VK_AMD_SHADER_CORE_PROPERTIES2_SPEC_VERSION                1
#define VK_AMD_SHADER_CORE_PROPERTIES2_EXTENSION_NAME              "VK_AMD_shader_core_properties2"

#define VK_AMD_SHADER_CORE_PROPERTIES2_EXTENSION_NUMBER            228

#define VK_AMD_SHADER_CORE_PROPERTIES2_ENUM(type, offset) \
    VK_EXTENSION_ENUM(VK_AMD_SHADER_CORE_PROPERTIES2_EXTENSION_NUMBER, type, offset)

#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES2_AMD \
    VK_AMD_SHADER_CORE_PROPERTIES2_ENUM(VkStructureType, 0)
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_COMPUTE_RATES_AMD \
    VK_AMD_SHADER_CORE_PROPERTIES2_ENUM(VkStructureType, 1)

typedef enum VkPhysicalDeviceShaderCoreFeaturesFlagBitsAMD {
#if VKI_BUILD_GFX10
    VK_PHYSICAL_DEVICE_SHADER_CORE_FEATURE_WAVEFRONT_SIZE_32_BIT_AMD = 0x00000001, // This flag is experimental
#endif
    VK_PHYSICAL_DEVICE_SHADER_CORE_FEATURE_FLAG_BITS_MAX_ENUM_AMD = 0x7FFFFFFF
} VkPhysicalDeviceShaderCoreFeaturesFlagBitsAMD;
typedef VkFlags VkPhysicalDeviceShaderCoreFeaturesFlagsAMD;

typedef struct VkPhysicalDeviceShaderCoreProperties2AMD {
    VkStructureType                            sType;
    void*                                      pNext;
    VkPhysicalDeviceShaderCoreFeaturesFlagsAMD shaderCoreFeatures;     ///< Supported features of the shader core.
    uint32_t                                   activeComputeUnitCount; ///< Number of CUs that have been enabled.
} VkPhysicalDeviceShaderCoreProperties2AMD;

typedef struct VkPhysicalDeviceShaderCoreComputeRatesAMD {
    VkStructureType                            sType;
    void*                                      pNext;
    float                                      float16Rate; ///< The execution ratio of multiply/add operations using
                                                            ///  16-bit float values relative to 32-bit float values.
    float                                      float64Rate; ///< The execution ratio of multiply/add operations using
                                                            ///  64-bit float values relative to 32-bit float values.
} VkPhysicalDeviceShaderCoreComputeRatesAMD;

#endif /* VK_AMD_SHADER_CORE_PROPERTIES2_H_ */
