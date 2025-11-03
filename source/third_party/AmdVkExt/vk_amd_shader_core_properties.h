/* Copyright (C) 2018-2025 Advanced Micro Devices, Inc. All rights reserved. */
/**
 **********************************************************************************************************************
 * @file  vk_amd_shader_core_properties.h
 * @brief Temporary internal header for shader core properties. Should be removed once the extension is published
 *        and the API gets included in the official Vulkan header.
 **********************************************************************************************************************
 */
#ifndef VK_AMD_SHADER_CORE_PROPERTIES_H_
#define VK_AMD_SHADER_CORE_PROPERTIES_H_

#include "vk_internal_ext_helper.h"

#define VK_AMD_SHADER_CORE_PROPERTIES_SPEC_VERSION                1
#define VK_AMD_SHADER_CORE_PROPERTIES_EXTENSION_NAME              "VK_AMD_shader_core_properties"

#define VK_AMD_SHADER_CORE_PROPERTIES_EXTENSION_NUMBER            186

#define VK_AMD_SHADER_CORE_PROPERTIES_ENUM(type, offset) \
    VK_EXTENSION_ENUM(VK_AMD_SHADER_CORE_PROPERTIES_EXTENSION_NUMBER, type, offset)

typedef struct VkPhysicalDeviceShaderCorePropertiesAMD {
    VkStructureType       sType;
    void*                 pNext;
    uint32_t              shaderEngineCount;                  ///< Number of shader engines.
    uint32_t              shaderArraysPerEngineCount;         ///< Number of shader arrays.
    uint32_t              computeUnitsPerShaderArray;         ///< Number of CUs per shader array.
    uint32_t              simdPerComputeUnit;                 ///< Number of SIMDs per compute unit.
    uint32_t              wavefrontsPerSimd;                  ///< Number of wavefront slots in each SIMD.
    uint32_t              wavefrontSize;                      ///< Wavefront size.
    uint32_t              sgprsPerSimd;                       ///< Number of physical SGPRs per SIMD.
    uint32_t              minSgprAllocation;                  ///< Minimum number of SGPRs that can be allocated by a wave.
    uint32_t              maxSgprAllocation;                  ///< Number of available SGPRs.
    uint32_t              sgprAllocationGranularity;          ///< SGPRs are allocated in groups of this size.  Meaning, if your shader
                                                              ///  only uses 1 SGPR, you will still end up reserving this number of
                                                              ///  SGPRs.
    uint32_t              vgprsPerSimd;                       ///< Number of physical VGPRs per SIMD.
    uint32_t              minVgprAllocation;                  ///< Minimum number of VGPRs that can be allocated by a wave.
    uint32_t              maxVgprAllocation;                  ///< Number of available VGPRs.
    uint32_t              vgprAllocationGranularity;          ///< VGPRs are allocated in groups of this size.  Meaning, if your shader
                                                              ///  only uses 1 VGPR, you will still end up reserving this number of
                                                              ///  VGPRs.
} VkPhysicalDeviceShaderCorePropertiesAMD;

#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD   VK_AMD_SHADER_CORE_PROPERTIES_ENUM(VkStructureType, 0)

#endif /* VK_AMD_SHADER_CORE_PROPERTIES_H_ */
