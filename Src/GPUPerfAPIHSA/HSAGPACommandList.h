//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief HSA GPA Command List Declarations
//==============================================================================

#ifndef _HSA_GPA_COMMAND_LIST_H_
#define _HSA_GPA_COMMAND_LIST_H_

// GPA Common
#include "GPACommandList.h"

/// Class for HSA GPA Command List
class HSAGPACommandList : public GPACommandList
{
public:

    /// Constructor
    HSAGPACommandList() = delete;

    /// Constructor
    /// \param[in] pGpaSession GPA session pointer
    /// \param[in] pGpaPass pass object pointer
    HSAGPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass);

    /// Destructor
    ~HSAGPACommandList() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;
};

#endif // _HSA_GPA_COMMAND_LIST_H_
