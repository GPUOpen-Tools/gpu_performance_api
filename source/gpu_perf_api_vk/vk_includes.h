//==============================================================================
// Copyright (c) 2018-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Vk Includes header
//==============================================================================

#ifndef _VK_INCLUDES_H_
#define _VK_INCLUDES_H_

#include <vulkan/vulkan.h>
#include <vk_amd_gpa_interface.h>

#ifndef VK_AMD_SHADER_CORE_PROPERTIES_SPEC_VERSION
#include <vk_amd_shader_core_properties.h>
#endif

#ifndef VK_AMD_SHADER_CORE_PROPERTIES_2_SPEC_VERSION
#include <vk_amd_shader_core_properties2.h>
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES2_AMD
#endif

#endif  //_VK_INCLUDES_H_
