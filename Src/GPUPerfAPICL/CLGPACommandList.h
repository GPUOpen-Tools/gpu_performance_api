//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief CL GPA Command List Declarations
//==============================================================================

#ifndef _CL_GPA_COMMAND_LIST_H_
#define _CL_GPA_COMMAND_LIST_H_

// GPA Common
#include "GPACommandList.h"

/// Class for CL GPA Command List
class CLGPACommandList : public GPACommandList
{
public:

    /// Constructor
    CLGPACommandList() = delete;

    /// Constructor
    /// \param[in] pGpaSession GPA session pointer
    /// \param[in] pGpaPass pass object pointer
    CLGPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass);

    /// Destructor
    ~CLGPACommandList() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;
};

#endif // _CL_GPA_COMMAND_LIST_H_
