//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Interface representing the GPA Interface Object.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_INTERFACE_TRAIT_INTERFACE_H_
#define GPU_PERF_API_COMMON_GPA_INTERFACE_TRAIT_INTERFACE_H_

#include "gpu_performance_api/gpu_perf_api_types.h"

/// @brief Enum for GPA Object types.
enum class GpaObjectType : unsigned char
{
    kGpaObjectTypeUndefined,       ///< Undefined object.
    kGpaObjectTypeImplementation,  ///< Implementation object.
    kGpaObjectTypeContext,         ///< Context object.
    kGpaObjectTypeSession,         ///< Session object.
    kGpaObjectTypeCommandList      ///< Command list object.
};

/// @brief Interface for API specific Object.
class IGpaInterfaceTrait
{
public:
    /// @brief Virtual Destructor.
    virtual ~IGpaInterfaceTrait() = default;

    /// @brief Returns the API type of the object.
    ///
    /// @return Api type of the object.
    virtual GpaApiType GetApiType() const = 0;

    /// @brief Returns the type of the Object.
    ///
    /// @return Object type.
    virtual GpaObjectType ObjectType() const = 0;
};

#endif  // GPU_PERF_API_COMMON_GPA_INTERFACE_TRAIT_INTERFACE_H_
