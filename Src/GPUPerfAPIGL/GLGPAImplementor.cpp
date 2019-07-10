//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GL GPA Implementation
//==============================================================================

#include <assert.h>

#include <DeviceInfoUtils.h>
#include "GLInclude.h"
#include "ASICInfo.h"
#include "GLGPAImplementor.h"
#include "GLGPAContext.h"

IGPAImplementor* s_pGpaImp = GLGPAImplementor::Instance();

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
    else
    {
        hwInfo.SetDeviceName(reinterpret_cast<const char*>(pRenderer));
    }

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

            if (!oglUtils::GetASICInfo(asicInfo))
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
                GDT_HW_ASIC_TYPE asicType = GDT_ASIC_TYPE_NONE;

                // switch between values in ASICInfo.h and GPAHWInfo.cpp
                switch (asicInfo.m_asicID)
                {
                case oglUtils::ASIC_ID_TAHITI_P:
                    hwInfo.SetDeviceID(0x679A);
                    asicType = GDT_TAHITI_PRO;
                    break;

                case oglUtils::ASIC_ID_PITCAIRN_PM:
                    hwInfo.SetDeviceID(0x6819);
                    asicType = GDT_PITCAIRN_PRO;
                    break;

                case oglUtils::ASIC_ID_CAPEVERDE_M:
                    hwInfo.SetDeviceID(0x6822);
                    asicType = GDT_CAPEVERDE_PRO;
                    break;

                case oglUtils::ASIC_ID_OLAND_M:
                    hwInfo.SetDeviceID(0x6610);
                    asicType = GDT_OLAND;
                    break;

                case oglUtils::ASIC_ID_HAINAN_M:
                    hwInfo.SetDeviceID(0x6660);
                    asicType = GDT_HAINAN;
                    break;

                case oglUtils::ASIC_ID_BONAIRE_M:
                    hwInfo.SetDeviceID(0x665C);
                    asicType = GDT_BONAIRE;
                    break;

                case oglUtils::ASIC_ID_SPECTRE:
                    hwInfo.SetDeviceID(0x130C);
                    asicType = GDT_SPECTRE;
                    break;

                case oglUtils::ASIC_ID_SPOOKY:
                    hwInfo.SetDeviceID(0x130B);
                    asicType = GDT_SPOOKY;
                    break;

                case oglUtils::ASIC_ID_KALINDI:
                    hwInfo.SetDeviceID(0x9830);
                    asicType = GDT_KALINDI;
                    break;

                case oglUtils::ASIC_ID_HAWAII_P:
                    hwInfo.SetDeviceID(0x67B0);
                    asicType = GDT_HAWAII;
                    break;

                case oglUtils::ASIC_ID_ICELAND_M:
                    hwInfo.SetDeviceID(0x6900);
                    asicType = GDT_ICELAND;
                    break;

                case oglUtils::ASIC_ID_TONGA_P:
                    hwInfo.SetDeviceID(0x6920);
                    asicType = GDT_TONGA;
                    break;

                case oglUtils::ASIC_ID_GODAVARI:
                    hwInfo.SetDeviceID(0x9855);
                    asicType = GDT_KALINDI;
                    break;

                case oglUtils::ASIC_ID_CARRIZO:
                    hwInfo.SetDeviceID(0x9874);
                    asicType = GDT_CARRIZO;
                    break;

                case oglUtils::ASIC_ID_STONEY:
                    hwInfo.SetDeviceID(0x98E4);
                    asicType = GDT_STONEY;
                    break;

                case oglUtils::ASIC_ID_FIJI_P:
                    hwInfo.SetDeviceID(0x7300);
                    asicType = GDT_FIJI;
                    break;

                case oglUtils::ASIC_ID_ELLESMERE:
                    hwInfo.SetDeviceID(0x67DF);
                    asicType = GDT_ELLESMERE;
                    break;

                case oglUtils::ASIC_ID_BAFFIN:
                    hwInfo.SetDeviceID(0x67FF);
                    asicType = GDT_BAFFIN;
                    break;

                case oglUtils::ASIC_ID_VEGAM:
                    hwInfo.SetDeviceID(0x694C);
                    asicType = GDT_VEGAM1;
                    break;

                case oglUtils::ASIC_ID_LEXA:
                    hwInfo.SetDeviceID(0x699F);
                    asicType = GDT_GFX8_0_4;
                    break;

                case oglUtils::ASIC_ID_GFX900:
                    hwInfo.SetDeviceID(0x687F);
                    asicType = GDT_GFX9_0_0;
                    break;

                case oglUtils::ASIC_ID_GFX902:
                    hwInfo.SetDeviceID(0x15DD);
                    asicType = GDT_GFX9_0_2;
                    break;

                case oglUtils::ASIC_ID_GFX906:
                    hwInfo.SetDeviceID(0x66A3);
                    asicType = GDT_GFX9_0_6;
                    break;

                case oglUtils::ASIC_ID_GFX1010:
                case oglUtils::ASIC_ID_GFX1010LITE:
                    hwInfo.SetDeviceID(0x7310);
                    asicType = GDT_GFX10_1_0;
                    break;

                default:
                    GPA_LogError("Unsupported asic ID.");
                    return false;
                }

                if (!hwInfo.UpdateDeviceInfoBasedOnASICTypeAndName(asicType))
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
