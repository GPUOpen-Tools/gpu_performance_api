//==============================================================================
// Copyright (c) 2008-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  This is the main include file for Adapter.cpp to enumerate adapters.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_ADAPTER_H_
#define GPU_PERF_API_COMMON_ADAPTER_H_

#include <vector>
#include <dxgi.h>

#include "ADLUtil.h"

/// @brief Enumerate adapters in the system.
class Adapter
{
public:
    /// @brief Default constructor.
    Adapter() = default;

    /// @brief Destructor.
    ~Adapter() = default;

    /// @brief Get ASIC information for all GPUs in the system.
    ///
    /// @param [out] asic_info_list The ADLUtil_ASICInfo vector.
    ///
    /// @return True if ASIC info list was retrieved successfully, false if not.
    bool GetAsicInfoList(AsicInfoList& asic_info_list) const;

private:
    /// @brief Copy constructor.
    Adapter(const Adapter&) = default;

    /// @brief Copy assignment operator.
    ///
    /// @return Item being assigned.
    Adapter& operator=(const Adapter&) = default;

    /// @brief Convert DXGI adapter description to ADL ASIC information.
    ///
    /// @param [in] dxgi_adapter_desc DXGI adapter description.
    /// @param [out] asic_info ADL ASIC information.
    static void DxgiAdapterDescToAsicInfo(const DXGI_ADAPTER_DESC& dxgi_adapter_desc, ADLUtil_ASICInfo& asic_info);
};

#endif
