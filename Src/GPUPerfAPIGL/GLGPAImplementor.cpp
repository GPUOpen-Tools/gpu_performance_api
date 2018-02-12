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

GPA_Status GLGPAImplementor::Initialize()
{
    return GPAImplementor::Initialize();
}

GPA_API_Type GLGPAImplementor::GetAPIType() const
{
    return GPA_API_OPENGL;
}

bool GLGPAImplementor::GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo,
                                        GPA_HWInfo& hwInfo) const
{
    UNREFERENCED_PARAMETER(pContextInfo);

    // get the entry points
    m_isGlEntryPointsInitialized = oglUtils::InitializeGLFunctions();

    if (!m_isGlEntryPointsInitialized)
    {
        GPA_LogError("Unable to initialize essential GL functions");
        return m_isGlEntryPointsInitialized;
    }

    const GLubyte* pRenderer = _oglGetString(GL_RENDERER);

    if (nullptr != pRenderer)
    {
        hwInfo.SetDeviceName(reinterpret_cast<const char*>(pRenderer));
    }

    // Handle non-AMD GPU vendors
    const GLubyte* pVendor = _oglGetString(GL_VENDOR);

    //TODO: should at least support GPUTime for these vendors then
    if (nullptr != strstr(reinterpret_cast<const char*>(pVendor), oglUtils::s_pNVIDIARenderer))
    {
        hwInfo.SetVendorID(NVIDIA_VENDOR_ID);
        hwInfo.SetHWGeneration(GDT_HW_GENERATION_NVIDIA);
        return true;
    }
    else if (nullptr != strstr(reinterpret_cast<const char*>(pVendor), oglUtils::s_pIntelRenderer))
    {
        hwInfo.SetVendorID(INTEL_VENDOR_ID);
        hwInfo.SetHWGeneration(GDT_HW_GENERATION_INTEL);
        return true;
    }

    // instead of checking the vendor string to make sure it is ATI / AMD,
    // use the Renderer string - sometimes the GL driver team needs to override
    // the vendor string to make apps and games behave differently, so using
    // the renderer string is a better solution.
    if (strstr(reinterpret_cast<const char*>(pRenderer), oglUtils::s_pATIRenderer) == 0 ||
        strstr(reinterpret_cast<const char*>(pRenderer), oglUtils::s_pAMDRenderer) == 0)
    {
        hwInfo.SetVendorID(AMD_VENDOR_ID);

        bool isDeviceIdKnown = false;

        if (nullptr != _oglXQueryCurrentRendererIntegerMESA)
        {
            // first try to get the device id from the glXQueryCurrentRendererIntegerMESA extension
            unsigned int driverDeviceId;
            _oglXQueryCurrentRendererIntegerMESA(GLX_RENDERER_DEVICE_ID_MESA, &driverDeviceId);

            // check to make sure the device id returned is found in the device info table
            GDT_HW_GENERATION hwGeneration;
            isDeviceIdKnown = AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(driverDeviceId, hwGeneration);

            if (isDeviceIdKnown)
            {
                hwInfo.SetDeviceID(driverDeviceId);
            }
        }

        // if we were unable to use the glCQueryCurrentRendererIntegerMESA extension,
        // then fall back to the GPIN counters exposed by the driver
        if (!isDeviceIdKnown)
        {
            ASICInfo asicInfo;

            if (!GetASICInfo(asicInfo))
            {
                GPA_LogError("Unable to obtain asic information.");
                return false;
            }

            // switch between values in ASICInfo.h and GPAHWInfo.cpp
            switch (asicInfo.eAsicRev)
            {
                case ATIASIC_ID_TAHITI_P:
                    hwInfo.SetDeviceID(0x6779);
                    break;

                case ATIASIC_ID_PITCAIRN_PM:
                    hwInfo.SetDeviceID(0x6818);
                    break;

                case ATIASIC_ID_CAPEVERDE_M:
                    hwInfo.SetDeviceID(0x6838);
                    break;

                case ATIASIC_ID_OLAND_M:
                    hwInfo.SetDeviceID(0x6610);
                    break;

                case ATIASIC_ID_HAINAN_M:
                    hwInfo.SetDeviceID(0x6660);
                    break;

                case ATIASIC_ID_BONAIRE_M:
                    hwInfo.SetDeviceID(0x665C);
                    break;

                case ATIASIC_ID_SPECTRE:
                    hwInfo.SetDeviceID(0x1307);
                    break;

                case ATIASIC_ID_SPOOKY:
                    hwInfo.SetDeviceID(0x1312);
                    break;

                case ATIASIC_ID_KALINDI:
                    hwInfo.SetDeviceID(0x9830);
                    break;

                case ATIASIC_ID_HAWAII_P:
                    hwInfo.SetDeviceID(0x67A0);
                    break;

                case ATIASIC_ID_ICELAND_M:
                    hwInfo.SetDeviceID(0x6900);
                    break;

                case ATIASIC_ID_TONGA_P:
                    hwInfo.SetDeviceID(0x6920);
                    break;

                case ATIASIC_ID_GODAVARI:
                    hwInfo.SetDeviceID(0x9855);
                    break;

                case ATIASIC_ID_CARRIZO:
                    hwInfo.SetDeviceID(0x9870);
                    break;

                case ATIASIC_ID_STONEY:
                    hwInfo.SetDeviceID(0x98E4);
                    break;

                case ATIASIC_ID_FIJI_P:
                    hwInfo.SetDeviceID(0x7300);
                    break;

                case ATIASIC_ID_ELLESMERE:
                    hwInfo.SetDeviceID(0x67DF);
                    break;

                case ATIASIC_ID_BAFFIN:
                    hwInfo.SetDeviceID(0x67FF);
                    break;

                case ATIASIC_ID_LEXA:
                    hwInfo.SetDeviceID(0x699F);
                    break;

                case ATIASIC_ID_VEGA:
                    hwInfo.SetDeviceID(0x687F);
                    break;

                case ATIASIC_ID_VEGA_APU:
                    hwInfo.SetDeviceID(0x15DD);
                    break;

                default:
                    GPA_LogError("Unsupported asic ID.");
                    return false;
            }
        }

        // GPUTime information is returned in nanoseconds, so set the frequency to convert it into seconds
        hwInfo.SetTimeStampFrequency(1000000000);

        if (!hwInfo.UpdateRevisionIdBasedOnDeviceIDAndName())
        {
            // We didn't found any revision Id, set it to REVISION_ID_ANY
            hwInfo.SetRevisionID(REVISION_ID_ANY);
        }

        return true;
    }

    GPA_LogError("A non-AMD graphics card was identified.");
    return false;
}

// TODO: this implementation doesn't do much -- is it needed?
bool GLGPAImplementor::VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo,
                                          const GPA_HWInfo& hwInfo) const
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

GLGPAImplementor::GLGPAImplementor():
    m_isGlEntryPointsInitialized(false)
{
}

IGPAContext* GLGPAImplementor::OpenAPIContext(GPAContextInfoPtr pContextInfo,
                                              GPA_HWInfo& hwInfo,
                                              GPA_OpenContextFlags flags)
{
    UNREFERENCED_PARAMETER(pContextInfo);
    GLGPAContext* pRetGpaContext = nullptr;

    GLContextPtr glContext = static_cast<GLContextPtr>(pContextInfo);

    GLGPAContext* pGLGpaContext = new(std::nothrow) GLGPAContext(glContext, hwInfo, flags);

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

bool GLGPAImplementor::CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pGpaContext)
{
    assert(nullptr != pDeviceIdentifier);
    assert(nullptr != pGpaContext);

    UNREFERENCED_PARAMETER(pDeviceIdentifier);

    if (nullptr != pGpaContext)
    {
        delete reinterpret_cast<GLGPAContext*>(pGpaContext);
    }

    return (nullptr != pGpaContext) && (nullptr != pDeviceIdentifier);
}

GPADeviceIdentifier GLGPAImplementor::GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const
{
    return pContextInfo;
}
