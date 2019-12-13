//==============================================================================
// Copyright (c) 2018-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GL GPA Implementation
//==============================================================================

#include <assert.h>

#include <DeviceInfoUtils.h>
#include "GLEntryPoints.h"
#include "ASICInfo.h"
#include "GLGPAImplementor.h"
#include "GLGPAContext.h"

#include "GPACounterGeneratorGL.h"
#include "GPACounterSchedulerGL.h"

IGPAImplementor* s_pGpaImp = GLGPAImplementor::Instance();
static GPA_CounterGeneratorGL s_generatorGL;  ///< static instance of GL generator
static GPA_CounterSchedulerGL s_schedulerGL;  ///< static instance of GL scheduler

GPA_API_Type GLGPAImplementor::GetAPIType() const
{
    return GPA_API_OPENGL;
}

bool GLGPAImplementor::GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const
{
    UNREFERENCED_PARAMETER(pContextInfo);

    // get the entry points
    m_isGlEntryPointsInitialized = oglUtils::InitializeGLFunctions();

    if (!m_isGlEntryPointsInitialized)
    {
        GPA_LogError("Unable to initialize essential GL functions.");
        return m_isGlEntryPointsInitialized;
    }

    const GLubyte* pRenderer = oglUtils::_oglGetString(GL_RENDERER);

    if (nullptr == pRenderer)
    {
        GPA_LogError("Unable to get GL_RENDERER string.");
        return false;
    }

    hwInfo.SetDeviceName(reinterpret_cast<const char*>(pRenderer));

    // Handle non-AMD GPU vendors
    const GLubyte* pVendor     = oglUtils::_oglGetString(GL_VENDOR);
    bool           isAmdVendor = false;

    if (nullptr == pVendor)
    {
        GPA_LogError("Unable to get GL_VENDOR string.");
        return false;
    }

    if (nullptr != strstr(reinterpret_cast<const char*>(pVendor), oglUtils::s_pATIRenderer) ||
        nullptr != strstr(reinterpret_cast<const char*>(pVendor), oglUtils::s_pAMDRenderer))
    {
        isAmdVendor = true;
    }
    else if (nullptr != strstr(reinterpret_cast<const char*>(pVendor), oglUtils::s_pNVIDIARenderer))
    {
        //TODO: investigate supporting GPUTime for these vendors
        return false;
    }
    else if (nullptr != strstr(reinterpret_cast<const char*>(pVendor), oglUtils::s_pIntelRenderer))
    {
        //TODO: investigate supporting GPUTime for these vendors
        return false;
    }

    // in addition to checking the vendor string to make sure it is ATI / AMD,
    // also check the Renderer string - sometimes the GL driver needs to override
    // the vendor string to make apps behave differently, so using the renderer
    // offers a fallback solution.
    if (isAmdVendor || nullptr != strstr(reinterpret_cast<const char*>(pRenderer), oglUtils::s_pATIRenderer) ||
        nullptr != strstr(reinterpret_cast<const char*>(pRenderer), oglUtils::s_pAMDRenderer) ||
        nullptr != strstr(reinterpret_cast<const char*>(pRenderer), oglUtils::s_pRadeonRenderer))
    {
        hwInfo.SetVendorID(AMD_VENDOR_ID);

        bool isDeviceIdKnown = false;

        if (nullptr != oglUtils::_oglXQueryCurrentRendererIntegerMESA)
        {
            // first try to get the device id from the glXQueryCurrentRendererIntegerMESA extension
            unsigned int driverDeviceId;
            oglUtils::_oglXQueryCurrentRendererIntegerMESA(GLX_RENDERER_DEVICE_ID_MESA, &driverDeviceId);

            // check to make sure the device id returned is found in the device info table
            GDT_HW_GENERATION hwGeneration;
            isDeviceIdKnown = AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(driverDeviceId, hwGeneration);

            if (isDeviceIdKnown)
            {
                hwInfo.SetDeviceID(driverDeviceId);

                if (!hwInfo.UpdateRevisionIdBasedOnDeviceIDAndName())
                {
                    // We didn't find a revision Id, set it to REVISION_ID_ANY
                    hwInfo.SetRevisionID(REVISION_ID_ANY);
                }
            }
        }

        // if we were unable to use the glXQueryCurrentRendererIntegerMESA extension,
        // then fall back to the GPIN counters exposed by the driver
        if (!isDeviceIdKnown)
        {
            oglUtils::ASICInfo asicInfo;

            if (!oglUtils::AsicInfoManager::Instance()->GetAsicInfoFromDriver(asicInfo))
            {
                GPA_LogError("Unable to obtain asic information.");
                return false;
            }

            m_glDriverVersion = asicInfo.m_driverVersion;

            bool isHwInfoValid = false;

            if (oglUtils::ASICInfo::s_UNASSIGNED_ASIC_INFO != asicInfo.m_deviceId)
            {
                hwInfo.SetDeviceID(asicInfo.m_deviceId);

                if (oglUtils::ASICInfo::s_UNASSIGNED_ASIC_INFO != asicInfo.m_deviceRev)
                {
                    GDT_GfxCardInfo cardInfo = {};

                    if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(asicInfo.m_deviceId, asicInfo.m_deviceRev, cardInfo))
                    {
                        isHwInfoValid = true;
                        hwInfo.SetRevisionID(asicInfo.m_deviceRev);
                    }
                }

                if (!isHwInfoValid)
                {
                    isHwInfoValid = hwInfo.UpdateRevisionIdBasedOnDeviceIDAndName();
                }
            }

            if (!isHwInfoValid)
            {
                // this is now a fallback path when using drivers where the
                // additional GPIN counters are not supported. This if block
                // can be removed once we no longer need to support drivers older
                // than 19.30
                GDT_HW_ASIC_TYPE asic_type = GDT_ASIC_TYPE_NONE;
                uint32_t         device_id;

                if (oglUtils::AsicInfoManager::Instance()->GetFallbackAsicInfo(asicInfo.m_asicID, asic_type, device_id))
                {
                    hwInfo.SetDeviceID(static_cast<gpa_uint32>(device_id));
                }
                else
                {
                    GPA_LogError("Unsupported asic ID.");
                    return false;
                }

                if (!hwInfo.UpdateDeviceInfoBasedOnASICTypeAndName(asic_type))
                {
                    // We didn't find a revision Id, set it to REVISION_ID_ANY
                    hwInfo.SetRevisionID(REVISION_ID_ANY);
                }
            }

            if (oglUtils::ASICInfo::s_UNASSIGNED_ASIC_INFO != asicInfo.m_numSE)
            {
                hwInfo.SetNumberShaderEngines(static_cast<size_t>(asicInfo.m_numSE));
            }

            if (oglUtils::ASICInfo::s_UNASSIGNED_ASIC_INFO != asicInfo.m_numSA)
            {
                hwInfo.SetNumberShaderArrays(static_cast<size_t>(asicInfo.m_numSA));
            }

            if (oglUtils::ASICInfo::s_UNASSIGNED_ASIC_INFO != asicInfo.m_numCU)
            {
                hwInfo.SetNumberCUs(static_cast<size_t>(asicInfo.m_numCU));
            }

            if (oglUtils::ASICInfo::s_UNASSIGNED_ASIC_INFO != asicInfo.m_numSIMD)
            {
                hwInfo.SetNumberSIMDs(static_cast<size_t>(asicInfo.m_numSIMD));
            }
        }

        // GPUTime information is returned in nanoseconds, so set the frequency to convert it into seconds
        hwInfo.SetTimeStampFrequency(1000000000);

        return true;
    }

    GPA_LogError("A non-AMD graphics card was identified.");
    return false;
}

// TODO: this implementation doesn't do much -- is it needed?
bool GLGPAImplementor::VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const
{
    UNREFERENCED_PARAMETER(pContextInfo);

    bool isSupported = false;

    GDT_HW_GENERATION generation = GDT_HW_GENERATION_NONE;

    if (!hwInfo.GetHWGeneration(generation))
    {
        GPA_LogError("Unable to get hardware generation.");
    }
    else
    {
        isSupported = true;
    }

    return isSupported;
}

GLGPAImplementor::GLGPAImplementor()
    : m_isGlEntryPointsInitialized(false),
      m_glDriverVersion(INT_MAX)
{
}

IGPAContext* GLGPAImplementor::OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags)
{
    UNREFERENCED_PARAMETER(pContextInfo);
    GLGPAContext* pRetGpaContext = nullptr;

    GLContextPtr glContext = static_cast<GLContextPtr>(pContextInfo);

    GLGPAContext* pGLGpaContext = new (std::nothrow) GLGPAContext(glContext, hwInfo, flags, m_glDriverVersion);

    if (nullptr == pGLGpaContext)
    {
        GPA_LogError("Unable to allocate memory for the context.");
    }
    else
    {
        if (pGLGpaContext->Initialize())
        {
            pRetGpaContext = pGLGpaContext;
        }
        else
        {
            delete pGLGpaContext;
            GPA_LogError("Unable to open a context.");
        }
    }

    return pRetGpaContext;
}

bool GLGPAImplementor::CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext)
{
    assert(nullptr != pDeviceIdentifier);
    assert(nullptr != pContext);

    UNREFERENCED_PARAMETER(pDeviceIdentifier);

    if (nullptr != pContext)
    {
        delete reinterpret_cast<GLGPAContext*>(pContext);
    }

    return (nullptr != pContext) && (nullptr != pDeviceIdentifier);
}

GPADeviceIdentifier GLGPAImplementor::GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const
{
    return pContextInfo;
}
