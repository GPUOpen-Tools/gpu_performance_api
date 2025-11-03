//==============================================================================
// Copyright (c) 2006-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Utility routines for retrieving ASIC information.
//==============================================================================

#ifndef GPU_PERF_API_GL_ASIC_INFO_H_
#define GPU_PERF_API_GL_ASIC_INFO_H_

#include "limits.h"

namespace ogl_utils
{
    /// @brief ASIC specific information.
    typedef struct _AsicInfo
    {
        static const unsigned int kUnassignedAsicInfo = static_cast<unsigned int>(-1);  ///< Value indicating that AsicInfo member is unassigned.

        int          driver_version = INT_MAX;              ///< The driver version extracted from GL_VERSION.
        unsigned int asic_revision  = kUnassignedAsicInfo;  ///< The driver-dependent Asic Revision ID.
        unsigned int device_id      = kUnassignedAsicInfo;  ///< The PCIE Device ID.
        unsigned int device_rev     = kUnassignedAsicInfo;  ///< The PCIE Revision ID.
        unsigned int num_simd       = kUnassignedAsicInfo;  ///< The number of SIMD units.
        unsigned int num_se         = kUnassignedAsicInfo;  ///< The number of shader engines.
        unsigned int num_sa_per_se  = kUnassignedAsicInfo;  ///< The number of shader arrays per shader engine.
        unsigned int num_cu         = kUnassignedAsicInfo;  ///< The number of compute units.
        unsigned int num_rb         = kUnassignedAsicInfo;  ///< The number of render back-ends (CB / DB).
        unsigned int num_spi        = kUnassignedAsicInfo;  ///< The number of shader processor interpolators.
    } AsicInfo;

    /// @brief Get the ASIC info from the driver using GPIN counter.
    ///
    /// @param [out] asic_info AsicInfo struct populated by GPIN group.
    ///
    /// @return Success status on querying GPIN counters.
    /// @retval True on success.
    /// @retval False on failure.
    bool GetAsicInfoFromDriver(AsicInfo& asic_info);

}  // namespace ogl_utils

#endif
