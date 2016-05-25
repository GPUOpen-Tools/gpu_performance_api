//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility functions used by the DX/Mantle counter generators
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_COMMON_H_
#define _GPA_COUNTER_GENERATOR_COMMON_H_

#include <windows.h>

#include "GPUPerfAPITypes.h"
#include "GPASplitCountersInterfaces.h"

/// calculates the offset to apply to a groupIndex given the first block index
/// of a set of blocks, and the number of blocks in that set.
/// \param groupIndex the group index that may need to be adjusted
/// \param firstBlockIndex the index of the first block in a set (ie DB0->DB7)
/// \param numBlockInstances the number of blocks in the set (ie 8 for DB0->DB7)
/// \return the offset to apply to groupIndex based on whether it is before,
///         within, or after the supplied set of blocks
UINT CalculateBlockDelta(UINT groupIndex, UINT firstBlockIndex, UINT numBlockInstances);

#endif //_GPA_COUNTER_GENERATOR_COMMON_H_

