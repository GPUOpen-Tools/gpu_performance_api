//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Interface representing the GPA Interface Object
//==============================================================================

#ifndef _I_GPA_INTERFACE_TRAIT_H_
#define _I_GPA_INTERFACE_TRAIT_H_

#include "GPUPerfAPITypes.h"

/// Enum for GPA Object types
enum class GPAObjectType : unsigned char
{
    GPA_OBJECT_TYPE_UNDEFINED,      ///< Undefined object
    GPA_OBJECT_TYPE_IMPLEMENTATION, ///< Implementation object
    GPA_OBJECT_TYPE_CONTEXT,        ///< context object
    GPA_OBJECT_TYPE_SESSION,        ///< session object
    GPA_OBJECT_TYPE_COMMAND_LIST    ///< command list object
};


/// Interface for API specific Object
class IGPAInterfaceTrait
{
public:
    /// Virtual Destructor
    virtual ~IGPAInterfaceTrait() = default;

    /// Returns the API type of the object
    /// \return api type of the object
    virtual GPA_API_Type GetAPIType() const = 0;

    /// Returns the type of the Object
    /// \return api object type
    virtual GPAObjectType ObjectType() const = 0;
};

#endif // _I_GPA_INTERFACE_TRAIT_H_
