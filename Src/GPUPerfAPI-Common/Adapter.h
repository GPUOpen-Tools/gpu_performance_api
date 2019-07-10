//==============================================================================
// Copyright (c) 2008-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This is the main include file for Adapter.cpp to enumerate adapters
//==============================================================================

#ifndef _GPA_COMMON_ADAPTER_H_
#define _GPA_COMMON_ADAPTER_H_

#include <vector>
#include <dxgi.h>

#include "ADLUtil.h"

/// Enumerate adapters in the system.
class Adapter
{
public:
    /// default constructor
    Adapter() = default;

    /// destructor
    ~Adapter() = default;

    /// Get ASIC information for all GPUs in the system
    /// \param[out] asicInfoList the ADLUtil_ASICInfo vector
    /// \return True if ASIC info list was retrieved succcessfully, false if not
    bool getAsicInfoList(AsicInfoList& asicInfoList) const;

private:
    /// copy constructor
    Adapter(const Adapter&) = default;

    /// copy assignment operator
    /// \return item being assigned
    Adapter& operator=(const Adapter&) = default;

    /// Convert DXGI adapter description to ADL ASIC information
    /// \param[in] dxgiAdapterDesc DXGI adapter description
    /// \param[out] asicInfo ADL ASIC information
    static void dxgiAdapterDescToAsicInfo(const DXGI_ADAPTER_DESC& dxgiAdapterDesc, ADLUtil_ASICInfo& asicInfo);
};

#endif  // _GPA_COMMON_ADAPTER_H_
