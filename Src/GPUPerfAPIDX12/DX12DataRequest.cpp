//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 Counter Data Request
//==============================================================================

/// \author GPU Developer Tools
/// \brief DX12DataRequest implementation

#include "DX12DataRequest.h"

DX12DataRequest::~DX12DataRequest()
{
} // end of DX12DataRequest::~DX12DataRequest

DX12DataRequest::DX12DataRequest()
    :
    GPA_DataRequest()
{
} // end of DX12DataRequest::DX12DataRequest

size_t DX12DataRequest::GetActiveCountersCount() const
{
    return m_activeCounters;
} // end of DX12DataRequest::GetActiveCountersCount

void DX12DataRequest::SetActiveCountersCount(const size_t activeCountersCount)
{
    m_activeCounters = activeCountersCount;
} // end of DX12DataRequest::SetActiveCountersCount
