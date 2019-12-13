//==============================================================================
// Copyright (c) 2012-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Implements a library that allows access to the available counters
///         in GPUPerfAPI without creating a GPA Context.
//==============================================================================

/// macro to export public API functions
#ifdef _LINUX
#define GPUPERFAPI_COUNTERS_DECL extern "C" __attribute__ ((visibility ("default")))
#else
#define GPUPERFAPI_COUNTERS_DECL extern "C" __declspec(dllexport)
#endif

#include "GPUPerfAPICounters.h"
#include "GPACounterGenerator.h"
#include "DeviceInfo.h"
#include "DeviceInfoUtils.h"
#include "GPAHWInfo.h"
#include "Logging.h"

#include "GPACounterGeneratorCL.h"
#include "GPACounterGeneratorGL.h"
#include "GPACounterGeneratorVK.h"
#include "GPACounterGeneratorVKNonAMD.h"

#ifdef WIN32
#include "GPACounterGeneratorDX11.h"
#include "GPACounterGeneratorDX11NonAMD.h"
#include "GPACounterGeneratorDX12.h"
#include "GPACounterGeneratorDX12NonAMD.h"
#include "Adapter.h"
#endif

#include "GPACounterSchedulerCL.h"
#include "GPACounterSchedulerGL.h"
#include "GPACounterSchedulerVK.h"

#ifdef WIN32
#include "GPACounterSchedulerDX11.h"
#include "GPACounterSchedulerDX12.h"
#endif

#include "GPACounterGeneratorSchedulerManager.h"

// these statics are needed to make sure the generators/schedulers get registered with CounterAccessorSchedulerManager

#ifdef CL
    static GPA_CounterGeneratorCL       s_generatorCL;         ///< static instance of CL generator
    static GPA_CounterSchedulerCL       s_schedulerCL;  ///< static instance of CL scheduler
#endif

#ifdef GL
    static GPA_CounterGeneratorGL       s_generatorGL;         ///< static instance of GL generator
    static GPA_CounterSchedulerGL       s_schedulerGL;  ///< static instance of GL scheduler
#endif

#ifdef VK
    static GPA_CounterGeneratorVK       s_generatorVK;         ///< static instance of VK generator
    static GPA_CounterGeneratorVKNonAMD s_generatorVKNonAMD;  ///< static instance of Vulkan non-AMD generator
    static GPA_CounterSchedulerVK       s_schedulerVK;         ///< static instance of VK scheduler
#endif

#ifdef WIN32
#ifdef DX11
    static GPA_CounterGeneratorDX11       s_generatorDX11;        ///< static instance of DX11 generator
    static GPA_CounterGeneratorDX11NonAMD s_generatorDX11NonAMD;  ///< static instance of DX11 non-AMD generator
    static GPA_CounterSchedulerDX11       s_schedulerDX11;        ///< static instance of DX11 scheduler
#endif

#ifdef DX12
    static GPA_CounterGeneratorDX12       s_generatorDX12;        ///< static instance of DX12 generator
    static GPA_CounterGeneratorDX12NonAMD s_generatorDX12NonAMD;  ///< static instance of DX12 non-AMD generator
    static GPA_CounterSchedulerDX12       s_schedulerDX12;        ///< static instance of DX12 scheduler
#endif
#endif

GPUPERFAPI_COUNTERS_DECL GPA_Status GPA_GetAvailableCounters(GPA_API_Type           api,
                                                             gpa_uint32             vendorId,
                                                             gpa_uint32             deviceId,
                                                             gpa_uint32             revisionId,
                                                             GPA_OpenContextFlags   flags,
                                                             gpa_uint8              generateAsicSpecificCounters,
                                                             IGPACounterAccessor**  ppCounterAccessorOut,
                                                             IGPACounterScheduler** ppCounterSchedulerOut)
{
    try
    {
        // For GPA 3.0 - disable Software counters
        flags |= GPA_OPENCONTEXT_HIDE_SOFTWARE_COUNTERS_BIT;

        GPA_Status retVal =
            GenerateCounters(api, vendorId, deviceId, revisionId, flags, generateAsicSpecificCounters, ppCounterAccessorOut, ppCounterSchedulerOut);
        return retVal;
    }
    catch (...)
    {
        return GPA_STATUS_ERROR_EXCEPTION;
    }
}

GPUPERFAPI_COUNTERS_DECL GPA_Status GPA_GetAvailableCountersByGeneration(GPA_API_Type          api,
                                                                         GPA_Hw_Generation     generation,
                                                                         GPA_OpenContextFlags  flags,
                                                                         gpa_uint8             generateAsicSpecificCounters,
                                                                         IGPACounterAccessor** ppCounterAccessorOut)
{
    try
    {
        GPA_Status retVal = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;

        // pick a device Id that falls into the desired HW generation.
        gpa_uint32 vendorId   = 0;
        gpa_uint32 deviceId   = 0;
        gpa_uint32 revisionId = 0;

        // For GPA 3.0 - disable Software counters
        flags |= GPA_OPENCONTEXT_HIDE_SOFTWARE_COUNTERS_BIT;

        if (GPA_HW_GENERATION_NVIDIA == generation)
        {
            vendorId = NVIDIA_VENDOR_ID;
            retVal   = GenerateCounters(api, vendorId, deviceId, revisionId, flags, generateAsicSpecificCounters, ppCounterAccessorOut, nullptr);
        }
        else if (GPA_HW_GENERATION_INTEL == generation)
        {
            vendorId = INTEL_VENDOR_ID;
            retVal   = GenerateCounters(api, vendorId, deviceId, revisionId, flags, generateAsicSpecificCounters, ppCounterAccessorOut, nullptr);
        }
        else if (GPA_HW_GENERATION_NONE != generation)
        {
            std::vector<GDT_GfxCardInfo> cardList;

            if (AMDTDeviceInfoUtils::Instance()->GetAllCardsInHardwareGeneration(static_cast<GDT_HW_GENERATION>(generation), cardList))
            {
                vendorId = AMD_VENDOR_ID;

                for (auto card : cardList)
                {
                    deviceId   = static_cast<gpa_uint32>(card.m_deviceID);
                    revisionId = static_cast<gpa_uint32>(card.m_revID);
                    retVal     = GenerateCounters(api, vendorId, deviceId, revisionId, flags, generateAsicSpecificCounters, ppCounterAccessorOut, nullptr);

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

        return retVal;
    }
    catch (...)
    {
        return GPA_STATUS_ERROR_EXCEPTION;
    }
};
