//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility functions used by the counter generator
//==============================================================================

#include "GPACounterGeneratorCommon.h"

UINT CalculateBlockDelta(UINT groupIndex, UINT firstBlockIndex, UINT numBlockInstances)
{
    UINT delta = 0;

    if (groupIndex > firstBlockIndex)
    {
        // this group is either within this block's number of instances, or beyond
        if (groupIndex > (firstBlockIndex + numBlockInstances - 1))
        {
            // this group is beyond this blocks # of instances
            delta = numBlockInstances - 1;
        }
        else
        {
            // this group is an instance of this block
            delta = groupIndex - firstBlockIndex;
        }
    }

    return delta;
}
