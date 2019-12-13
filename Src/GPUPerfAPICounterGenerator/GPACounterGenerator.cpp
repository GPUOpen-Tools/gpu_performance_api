//==============================================================================
// Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPUPerfAPI Counter Generator function
//==============================================================================

#include "GPACounterGenerator.h"
#include "Logging.h"
#include "ADLUtil.h"
#include "DeviceInfoUtils.h"
#include "GPAHWInfo.h"
#include "GPACounterGeneratorBase.h"
#include "GPACounterGeneratorSchedulerManager.h"


GPA_Status GenerateCounters(GPA_API_Type           desiredAPI,
                            gpa_uint32             vendorId,
                            gpa_uint32             deviceId,
                            gpa_uint32             revisionId,
                            GPA_OpenContextFlags   flags,
                            gpa_uint8              generateAsicSpecificCounters,
                            IGPACounterAccessor**  ppCounterAccessorOut,
                            IGPACounterScheduler** ppCounterSchedulerOut)
{
    if (nullptr == ppCounterAccessorOut)
    {
        GPA_LogError("Parameter 'ppCounterAccessorOut' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // get hardware generation from device Id
    GDT_HW_GENERATION desiredGeneration = GDT_HW_GENERATION_NONE;

    GDT_GfxCardInfo cardInfo{};

    if (NVIDIA_VENDOR_ID == vendorId)
    {
        desiredGeneration = GDT_HW_GENERATION_NVIDIA;
    }
    else if (INTEL_VENDOR_ID == vendorId)
    {
        desiredGeneration = GDT_HW_GENERATION_INTEL;
    }
    else if (AMD_VENDOR_ID == vendorId)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(deviceId, revisionId, cardInfo))
        {
            desiredGeneration = cardInfo.m_generation;

            if ((GPA_API_DIRECTX_12 == desiredAPI || (GPA_API_VULKAN == desiredAPI)) && GDT_HW_GENERATION_SEAISLAND == desiredGeneration &&
                GDT_HAWAII != cardInfo.m_asicType)
            {
                // For DX12 and Vulkan, the only CI family part that is supported is Hawaii
                return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
            }
        }
    }

    if (desiredGeneration == GDT_HW_GENERATION_NONE)
    {
        GPA_LogError("desiredGeneration is GDT_HW_GENERATION_NONE.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    GPA_Status                status        = GPA_STATUS_OK;
    GPA_CounterGeneratorBase* pTmpAccessor  = nullptr;
    IGPACounterScheduler*     pTmpScheduler = nullptr;

    bool retCode = CounterGeneratorSchedulerManager::Instance()->GetCounterGenerator(desiredAPI, desiredGeneration, pTmpAccessor);

    if (!retCode)
    {
        GPA_LogError("Requesting available counters from an unsupported API or hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    bool allowPublic          = (flags & GPA_OPENCONTEXT_HIDE_PUBLIC_COUNTERS_BIT) == 0;
    bool allowSoftware        = (flags & GPA_OPENCONTEXT_HIDE_SOFTWARE_COUNTERS_BIT) == 0;
    bool allowHardwareExposed = (flags & GPA_OPENCONTEXT_ENABLE_HARDWARE_COUNTERS_BIT) == GPA_OPENCONTEXT_ENABLE_HARDWARE_COUNTERS_BIT;
    bool enableHardware       = allowHardwareExposed;

#ifdef AMDT_INTERNAL
    bool allowAllHardware = (flags & GPA_OPENCONTEXT_HIDE_HARDWARE_COUNTERS_BIT) == 0;
    enableHardware        = allowAllHardware;
#endif

    pTmpAccessor->SetAllowedCounters(allowPublic, enableHardware, allowSoftware);
    status = pTmpAccessor->GenerateCounters(desiredGeneration, cardInfo.m_asicType, generateAsicSpecificCounters);

    if (status == GPA_STATUS_OK)
    {
        *ppCounterAccessorOut = pTmpAccessor;

        if (nullptr != ppCounterSchedulerOut)
        {
            retCode = CounterGeneratorSchedulerManager::Instance()->GetCounterScheduler(desiredAPI, desiredGeneration, pTmpScheduler);

            if (!retCode)
            {
                GPA_LogError("Requesting available counters from an unsupported API or hardware generation.");
                return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
            }

            *ppCounterSchedulerOut = pTmpScheduler;
            pTmpScheduler->SetCounterAccessor(pTmpAccessor, vendorId, deviceId, revisionId);
        }
    }

    return status;
}
