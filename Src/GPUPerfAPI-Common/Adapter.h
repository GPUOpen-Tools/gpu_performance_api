//==============================================================================
// Copyright (c) 2008-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This is the main include file for Adapter.cpp to enumerate adapters
//==============================================================================

#ifndef _GPA_COMMON_ADAPTER_H_
#define _GPA_COMMON_ADAPTER_H_

#include <wtypes.h>
#include <vector>
#include <dxgi.h>

#include "ADLUtil.h"
#include "GPAHWInfo.h"

/// Enumerate adapters in the system.
class Adapter
{
public:
    /// default constructor
    Adapter();

    /// destructor
    ~Adapter();

    /// Get ASIC information for all GPUs in the system
    /// \param[out] asicInfoList the ADLUtil_ASICInfo vector
    /// \return True if ASIC info list was retrieved succcessfully, false if not
    bool getAsicInfoList(AsicInfoList& asicInfoList);

private:
    /// copy constructor
    Adapter(const Adapter& other);

    /// copy assignment operator
    Adapter& operator=(const Adapter& other);

    /// Convert DXGI adapter description to ADL ASIC information
    /// \param[in] dxgiAdapterDesc DXGI adapter description
    /// \param[out] asicInfo ADL ASIC information
    static void dxgiAdapterDescToAsicInfo(const DXGI_ADAPTER_DESC& dxgiAdapterDesc, ADLUtil_ASICInfo& asicInfo);
};

#endif // _GPA_COMMON_ADAPTER_H_
