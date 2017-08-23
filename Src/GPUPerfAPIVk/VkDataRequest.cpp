//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Vk Counter Data Request
//==============================================================================

/// \author GPU Developer Tools
/// \brief VkDataRequest implementation

#include "VkDataRequest.h"

VkDataRequest::~VkDataRequest()
{
}

VkDataRequest::VkDataRequest()
    :
    GPA_DataRequest()
{
}

size_t VkDataRequest::GetActiveCountersCount() const
{
    return m_activeCounters;
}

void VkDataRequest::SetActiveCountersCount(const size_t activeCountersCount)
{
    m_activeCounters = activeCountersCount;
}
