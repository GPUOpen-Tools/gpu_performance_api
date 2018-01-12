//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPUPerfAPI Counter Generator function
//==============================================================================


#include "GPACounterGenerator.h"
#include "Logging.h"
#include "ADLUtil.h"
#include "DeviceInfoUtils.h"
#include "GPACounterGeneratorCL.h"
#include "GPACounterGeneratorGL.h"
#include "GPACounterGeneratorHSA.h"
#include "GPACounterGeneratorVK.h"
#include "GPACounterGeneratorVKNonAMD.h"

#ifdef WIN32
    #include "GPACounterGeneratorDX11.h"
    #include "GPACounterGeneratorDX11NonAMD.h"
    #include "GPACounterGeneratorDX12.h"
    #include "GPACounterGeneratorDX12NonAMD.h"
    #include "Adapter.h"
#endif // WIN32

#include "GPACounterSchedulerCL.h"
#include "GPACounterSchedulerGL.h"
#include "GPACounterSchedulerHSA.h"
#include "GPACounterSchedulerVK.h"

#ifdef WIN32
    #include "GPACounterSchedulerDX11.h"
    #include "GPACounterSchedulerDX12.h"
#endif // WIN32

#include "GPAInternalCountersGfx8.h"

#include "GPACounterGeneratorSchedulerManager.h"

// these statics are needed to make sure the generators/schedulers get registered with CounterAccessorSchedulerManager

static GPA_CounterGeneratorCL s_generatorCL;                        ///< static instance of CL generator
static GPA_CounterGeneratorGL s_generatorGL;                        ///< static instance of GL generator
static GPA_CounterGeneratorHSA s_generatorHSA;                      ///< static instance of HSA generator
static GPA_CounterGeneratorVK s_generatorVK;                        ///< static instance of VK generator
static GPA_CounterGeneratorVKNonAMD s_generatorVKNonAAMD;       ///< static instance of Vulkan non-AMD generator
#ifdef WIN32
    static GPA_CounterGeneratorDX11 s_generatorDX11;                ///< static instance of DX11 generator
    static GPA_CounterGeneratorDX11NonAMD s_generatorDX11NonAMD;    ///< static instance of DX11 non-AMD generator
    static GPA_CounterGeneratorDX12 s_generatorDX12;                ///< static instance of DX12 generator
    static GPA_CounterGeneratorDX12NonAMD s_generatorDX12NonAMD;    ///< static instance of DX12 non-AMD generator
#endif // WIN32

static GPA_CounterSchedulerCL s_schedulerCL;                        ///< static instance of CL scheduler
static GPA_CounterSchedulerGL s_schedulerGL;                        ///< static instance of GL scheduler
static GPA_CounterSchedulerHSA s_schedulerHSA;                      ///< static instance of HSA scheduler
static GPA_CounterSchedulerVK s_schedulerVK;                        ///< static instance of VK scheduler
#ifdef WIN32
    static GPA_CounterSchedulerDX11 s_schedulerDX11;                ///< static instance of DX11 scheduler
    static GPA_CounterSchedulerDX12 s_schedulerDX12;                ///< static instance of DX12 scheduler
#endif // WIN32

static const unsigned int s_numberOfFijiMCCounters = 33;            ///< number of MC counters on Fiji

GPA_Status GenerateCounters(
    GPA_API_Type desiredAPI,
    gpa_uint32 vendorId,
    gpa_uint32 deviceId,
    gpa_uint32 revisionId,
    gpa_uint8 generateAsicSpecificCounters,
    IGPACounterAccessor** ppCounterAccessorOut,
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

            if ((GPA_API_DIRECTX_12 == desiredAPI || (GPA_API_VULKAN == desiredAPI)) && GDT_HW_GENERATION_SEAISLAND == desiredGeneration && GDT_HAWAII != cardInfo.m_asicType)
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

    GPA_Status status = GPA_STATUS_OK;
    GPA_CounterGeneratorBase* pTmpAccessor = nullptr;
    IGPACounterScheduler* pTmpScheduler = nullptr;

    bool retCode = CounterGeneratorSchedulerManager::Instance()->GetCounterGenerator(desiredAPI, desiredGeneration, pTmpAccessor);

    if (!retCode)
    {
        GPA_LogError("Requesting available counters from an unsupported API or hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

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
