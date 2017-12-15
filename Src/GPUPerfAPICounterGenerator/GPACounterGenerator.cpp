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
#include "GPAInternalCountersFiji.h"

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

/// Fiji has different MC counters than other GFX8 parts (due to HBM) -- update the MC counters dynamically for Fiji
/// \param pMcCounters the default MC counters
/// \param pMCFijiCounters the Fiji MC counters
void ReplaceMCCountersWithFijiMCCounters(GPA_HardwareCounterDesc* pMcCounters, GPA_HardwareCounterDesc* pMCFijiCounters)
{
    for (int i = 0; i < s_numberOfFijiMCCounters; i++)
    {

        pMcCounters[i] = pMCFijiCounters[i];
    }
}

GPA_Status GenerateCounters(GPA_API_Type desiredAPI, gpa_uint32 vendorId, gpa_uint32 deviceId, gpa_uint32 revisionId, IGPACounterAccessor** ppCounterAccessorOut, IGPACounterScheduler** ppCounterSchedulerOut)
{
    if (nullptr == ppCounterAccessorOut)
    {
        GPA_LogError("Parameter 'ppCounterAccessorOut' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    bool isFiji = false;

    // get hardware generation from device Id
    GDT_HW_GENERATION desiredGeneration = GDT_HW_GENERATION_NONE;

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
        GDT_GfxCardInfo cardInfo;

        if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(deviceId, revisionId, cardInfo))
        {
            isFiji = cardInfo.m_asicType == GDT_FIJI;
            desiredGeneration = cardInfo.m_generation;

            if ((GPA_API_DIRECTX_12 == desiredAPI || (GPA_API_VULKAN == desiredAPI)) && GDT_HW_GENERATION_SEAISLAND == desiredGeneration && GDT_HAWAII != cardInfo.m_asicType)
            {
                // For DX12 and Vulkan, the only CI family part that is supported is Hawaii
                return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
            }
        }

        if (isFiji)
        {
            // This is a bit of a hack to account for the fact that Fiji has different MC counters
            // than the rest of the VI (GFX8) ASICs.  Doing this here avoids needing to define a
            // whole new hardware generation for Fiji just because of the MC counter differences.
            // MC0 -- MC31
            ReplaceMCCountersWithFijiMCCounters(MC0countersGfx8, MC_FIJI0countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC1countersGfx8, MC_FIJI1countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC2countersGfx8, MC_FIJI2countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC3countersGfx8, MC_FIJI3countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC4countersGfx8, MC_FIJI4countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC5countersGfx8, MC_FIJI5countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC6countersGfx8, MC_FIJI6countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC7countersGfx8, MC_FIJI7countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC8countersGfx8, MC_FIJI8countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC9countersGfx8, MC_FIJI9countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC10countersGfx8, MC_FIJI10countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC11countersGfx8, MC_FIJI11countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC12countersGfx8, MC_FIJI12countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC13countersGfx8, MC_FIJI13countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC14countersGfx8, MC_FIJI14countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC15countersGfx8, MC_FIJI15countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC16countersGfx8, MC_FIJI16countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC17countersGfx8, MC_FIJI17countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC18countersGfx8, MC_FIJI18countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC19countersGfx8, MC_FIJI19countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC20countersGfx8, MC_FIJI20countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC21countersGfx8, MC_FIJI21countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC22countersGfx8, MC_FIJI22countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC23countersGfx8, MC_FIJI23countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC24countersGfx8, MC_FIJI24countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC25countersGfx8, MC_FIJI25countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC26countersGfx8, MC_FIJI26countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC27countersGfx8, MC_FIJI27countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC28countersGfx8, MC_FIJI28countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC29countersGfx8, MC_FIJI29countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC30countersGfx8, MC_FIJI30countersGfx8);
            ReplaceMCCountersWithFijiMCCounters(MC31countersGfx8, MC_FIJI31countersGfx8);
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

    status = pTmpAccessor->GenerateCounters(desiredGeneration);

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
