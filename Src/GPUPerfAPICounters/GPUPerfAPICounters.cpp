//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Implements a library that allows access to the available counters in GPUPerfAPI.
//==============================================================================

/// macro to export public API functions
#ifdef _LINUX
    #define GPUPERFAPI_COUNTERS_DECL extern "C"
#else
    #define GPUPERFAPI_COUNTERS_DECL extern "C" __declspec( dllexport )
#endif

#include "../GPUPerfAPICounterGenerator/GPACounterGenerator.h"
#include "DeviceInfo.h"
#include "DeviceInfoUtils.h"
#include "GPAHWInfo.h"
#include "Logging.h"
#include "GPUPerfAPICounters.h"

GPUPERFAPI_COUNTERS_DECL GPA_Status GPA_GetAvailableCounters(GPA_API_Type api, gpa_uint32 vendorId, gpa_uint32 deviceId, gpa_uint32 revisionId, GPA_ICounterAccessor** ppCounterAccessorOut, GPA_ICounterScheduler** ppCounterSchedulerOut)
{
    return GenerateCounters(api, vendorId, deviceId, revisionId, ppCounterAccessorOut, ppCounterSchedulerOut);
};

GPUPERFAPI_COUNTERS_DECL GPA_Status GPA_GetAvailableCountersByGeneration(GPA_API_Type api, GPA_HW_GENERATION generation, GPA_ICounterAccessor** ppCounterAccessorOut)
{
    // pick a device Id that falls into the desired HW generation.
    gpa_uint32 vendorId = 0;
    gpa_uint32 deviceId = 0;
    gpa_uint32 revisionId = 0;

    if (GPA_HW_GENERATION_NVIDIA == generation)
    {
        vendorId = NVIDIA_VENDOR_ID;
    }
    else if (GPA_HW_GENERATION_INTEL == generation)
    {
        vendorId = INTEL_VENDOR_ID;
    }
    else if (GPA_HW_GENERATION_NONE != generation)
    {
        std::vector<GDT_GfxCardInfo> cardList;

        if (AMDTDeviceInfoUtils::Instance()->GetAllCardsInHardwareGeneration(static_cast<GDT_HW_GENERATION>(generation), cardList))
        {
            if (cardList.size() > 0)
            {
                vendorId = AMD_VENDOR_ID;
                deviceId = static_cast<gpa_uint32>(cardList[0].m_deviceID);
                revisionId = static_cast<gpa_uint32>(cardList[0].m_revID);
            }
        }

        if (deviceId == 0)
        {
            GPA_LogError("Parameter 'generation' does not identify supported hardware.");
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
        }
    }

    return GenerateCounters(api, vendorId, deviceId, revisionId, ppCounterAccessorOut, nullptr);
};
