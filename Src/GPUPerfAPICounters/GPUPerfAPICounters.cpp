//==============================================================================
// Copyright (c) 2012-2017 Advanced Micro Devices, Inc. All rights reserved.
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

#include "GPACounterGenerator.h"
#include "DeviceInfo.h"
#include "DeviceInfoUtils.h"
#include "GPAHWInfo.h"
#include "Logging.h"
#include "GPUPerfAPICounters.h"
#include "GPAContextState.h"

GPUPERFAPI_COUNTERS_DECL GPA_Status GPA_GetAvailableCounters(GPA_API_Type api,
    gpa_uint32 vendorId,
    gpa_uint32 deviceId,
    gpa_uint32 revisionId,
    GPA_OpenContextFlags flags,
    gpa_uint8 generateAsicSpecificCounters,
    IGPACounterAccessor** ppCounterAccessorOut,
    IGPACounterScheduler** ppCounterSchedulerOut)
{
    GPA_Status retVal = GenerateCounters(api, vendorId, deviceId, revisionId, generateAsicSpecificCounters, ppCounterAccessorOut, ppCounterSchedulerOut);

    if (GPA_STATUS_OK == retVal)
    {
        (*ppCounterAccessorOut)->SetAllowedCounters(::ExposePublicCounters(flags),
            ::ExposeHardwareCounters(flags),
            ::ExposeSoftwareCounters(flags));
    }

    return retVal;
}

GPUPERFAPI_COUNTERS_DECL GPA_Status GPA_GetAvailableCountersByGeneration(GPA_API_Type api,
    GPA_Hw_Generation generation,
    GPA_OpenContextFlags flags,
    gpa_uint8 generateAsicSpecificCounters,
    IGPACounterAccessor** ppCounterAccessorOut)
{
    GPA_Status retVal = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;

    // pick a device Id that falls into the desired HW generation.
    gpa_uint32 vendorId = 0;
    gpa_uint32 deviceId = 0;
    gpa_uint32 revisionId = 0;

    if (GPA_HW_GENERATION_NVIDIA == generation)
    {
        vendorId = NVIDIA_VENDOR_ID;
        retVal = GenerateCounters(api, vendorId, deviceId, revisionId, generateAsicSpecificCounters, ppCounterAccessorOut, nullptr);
    }
    else if (GPA_HW_GENERATION_INTEL == generation)
    {
        vendorId = INTEL_VENDOR_ID;
        retVal = GenerateCounters(api, vendorId, deviceId, revisionId, generateAsicSpecificCounters, ppCounterAccessorOut, nullptr);
    }
    else if (GPA_HW_GENERATION_NONE != generation)
    {
        std::vector<GDT_GfxCardInfo> cardList;

        if (AMDTDeviceInfoUtils::Instance()->GetAllCardsInHardwareGeneration(static_cast<GDT_HW_GENERATION>(generation), cardList))
        {
            vendorId = AMD_VENDOR_ID;

            for (auto card : cardList)
            {
                deviceId = static_cast<gpa_uint32>(card.m_deviceID);
                revisionId = static_cast<gpa_uint32>(card.m_revID);
                retVal = GenerateCounters(api, vendorId, deviceId, revisionId, generateAsicSpecificCounters, ppCounterAccessorOut, nullptr);

                if (GPA_STATUS_OK == retVal)
                {
                    break;
                }
            }
        }

        if (deviceId == 0)
        {
            GPA_LogError("Parameter 'generation' does not identify supported hardware.");
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
        }
    }

    if (GPA_STATUS_OK == retVal)
    {
        (*ppCounterAccessorOut)->SetAllowedCounters(::ExposePublicCounters(flags),
            ::ExposeHardwareCounters(flags),
            ::ExposeSoftwareCounters(flags));
    }

    return retVal;
};
