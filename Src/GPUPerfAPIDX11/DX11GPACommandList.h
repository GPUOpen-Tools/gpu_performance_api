//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX11 GPA Command List Declarations
//==============================================================================

#ifndef _DX11_GPA_CMD_LIST_H_
#define _DX11_GPA_CMD_LIST_H_

// GPA Common
#include "GPACommandList.h"

/// Class for DX11 GPA Command List
class DX11GPACommandList : public GPACommandList
{
public:

    /// Constructor
    DX11GPACommandList() = delete;

    /// Constructor
    DX11GPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass);

    /// Destructor
    ~DX11GPACommandList() = default;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;
};

#endif // _DX11_GPA_CMD_LIST_H_
