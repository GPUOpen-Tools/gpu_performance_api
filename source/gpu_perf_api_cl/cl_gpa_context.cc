//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA CL Context Implementation
//==============================================================================

#include "cl_gpa_context.h"
#include "gpa_unique_object.h"
#include "cl_gpa_implementor.h"
#include "cl_gpa_session.h"
#include "cl_perf_counter_amd_extension.h"
#include "cl_rt_module_loader.h"

CLGPAContext::CLGPAContext(cl_command_queue& clCommandQueue, GPA_HWInfo& hwInfo, GPA_OpenContextFlags contextFlags)
    : GPAContext(hwInfo, contextFlags)
    , m_clCommandQueue(clCommandQueue)
    , m_clDeviceId(nullptr)
    , m_clockMode(CL_DEVICE_CLOCK_MODE_DEFAULT_AMD)
    , m_clDriverVersion(0)
{
}

CLGPAContext::~CLGPAContext()
{
    GPA_Status setStableClocksStatus = SetStableClocks(false);

    if (GPA_STATUS_OK != setStableClocksStatus)
    {
        GPA_LogError("Driver was unable to set stable clocks back to default.");
#ifdef __linux__
        GPA_LogMessage("In Linux, make sure to run your application with root privileges.");
#endif  //__linux__
    }
}

GPA_SessionId CLGPAContext::CreateSession(GPA_Session_Sample_Type sampleType)
{
    GPA_SessionId pRetSessionId = nullptr;

    CLGPASession* pNewGpaCLGpaSession = new (std::nothrow) CLGPASession(this, sampleType);

    if (nullptr == pNewGpaCLGpaSession)
    {
        GPA_LogError("Unable to allocate memory for the session.");
    }
    else
    {
        AddGpaSession(pNewGpaCLGpaSession);

        if (nullptr != pNewGpaCLGpaSession)
        {
            pRetSessionId = reinterpret_cast<GPA_SessionId>(GPAUniqueObjectManager::Instance()->CreateObject(pNewGpaCLGpaSession));
        }
    }

    return pRetSessionId;
}

bool CLGPAContext::DeleteSession(GPA_SessionId sessionId)
{
    bool isDeleted = false;

    CLGPASession* pCLSession = reinterpret_cast<CLGPASession*>(sessionId->Object());

    if (nullptr != pCLSession)
    {
        RemoveGpaSession(pCLSession);
        GPAUniqueObjectManager::Instance()->DeleteObject(pCLSession);
        delete pCLSession;
        isDeleted = true;
    }

    return isDeleted;
}

gpa_uint32 CLGPAContext::GetMaxGPASessions() const
{
    // maximum latency is 4 for dx10-capable cards
    return 4;
}

GPA_API_Type CLGPAContext::GetAPIType() const
{
    return GPA_API_OPENCL;
}

bool CLGPAContext::Initialize(cl_device_id& clDeviceId)
{
    m_clDeviceId = clDeviceId;

    OpenCLModule* pOclModule = OCLRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pOclModule)
    {
        GPA_LogError("OpenCL runtime module is NULL.");
    }
    else
    {
        static const gpa_uint32 MAX_STR = 256;
        char driverVersion[MAX_STR];

        if (CL_SUCCESS != pOclModule->GetDeviceInfo(m_clDeviceId, CL_DRIVER_VERSION, MAX_STR, driverVersion, nullptr))
        {
            GPA_LogError("Unable to get driver version.");
        }
        else
        {
            m_clDriverVersion = ExtractDriverVersion(driverVersion);
        }
    }

    GPA_Status setStableClocksStatus = SetStableClocks(true);

    if (GPA_STATUS_OK != setStableClocksStatus)
    {
        GPA_LogError("Driver was unable to set stable clocks for profiling.");
#ifdef __linux__
        GPA_LogMessage("In Linux, make sure to run your application with root privileges.");
#endif  //__linux__
    }

    bool success = OpenCounters();

    if (success)
    {
        SetAsOpened(true);
    }

    return success;
}

const cl_device_id& CLGPAContext::GetCLDeviceId() const
{
    return m_clDeviceId;
}

const cl_command_queue& CLGPAContext::GetCLCommandQueue() const
{
    return m_clCommandQueue;
}

GPA_Status CLGPAContext::SetStableClocks(bool useProfilingClocks)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == my_clSetDeviceClockModeAMD)
    {
        GPA_LogMessage("clSetDeviceClockModeAMD extension is not available.");

        // TODO: return an error once we no longer need to support pre-19.10 drivers
        // result = GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;
    }
    else
    {
        cl_set_device_clock_mode_input_amd clockMode = {};

        if (useProfilingClocks)
        {
            DeviceClockMode deviceClockMode = GetDeviceClockMode();

            switch (deviceClockMode)
            {
            case DeviceClockMode::Default:
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_DEFAULT_AMD;
                break;

            case DeviceClockMode::Profiling:
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_PROFILING_AMD;
                break;

            case DeviceClockMode::MinimumMemory:
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_MINIMUMMEMORY_AMD;
                break;

            case DeviceClockMode::MinimumEngine:
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_MINIMUMENGINE_AMD;
                break;

            case DeviceClockMode::Peak:
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_PEAK_AMD;
                break;

            default:
                assert(0);
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_PROFILING_AMD;
                break;
            }
        }

        if (clockMode.clock_mode != m_clockMode)
        {
            m_clockMode   = clockMode.clock_mode;
            cl_int status = my_clSetDeviceClockModeAMD(m_clDeviceId, clockMode, nullptr);
            result        = (CL_SUCCESS == status) ? GPA_STATUS_OK : GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;

            if (CL_SUCCESS != status)
            {
#ifdef _LINUX
                // make sure the driver is new enough to support setting stable clocks
                // on Linux with pre-gfx9 devices, setting the clock mode fails with current drivers
                // in this case, simply act as if the call was successful by returning success
                const GPA_HWInfo* pHwInfo = GetHwInfo();
                GDT_HW_GENERATION gen = GDT_HW_GENERATION_NONE;
                static const int s_CL_DRIVER_VER_WITH_LINUX_STABLE_CLOCK_SUPPORT = 2904;  // CL driver version where stable clocks are working on Linux for pre-GFX9 devices

                if ((s_CL_DRIVER_VER_WITH_LINUX_STABLE_CLOCK_SUPPORT > m_clDriverVersion) && pHwInfo->GetHWGeneration(gen) && GDT_HW_GENERATION_GFX9 > gen)
                {
                    result = GPA_STATUS_OK;
                }
                else
#endif
                {
                    GPA_LogError("Failed to set ClockMode for profiling.");
                }
            }
        }
    }

    return result;
}

int CLGPAContext::ExtractDriverVersion(const char* pVersion) const
{
    int version = 0;

    if (nullptr != pVersion)
    {
        std::string strVer(pVersion);

        // the build number ends at the first dot
        size_t endBuild = strVer.find_first_of('.');

        // truncate the input at the first dot
        strVer = strVer.substr(0, endBuild);

        std::istringstream iss(strVer);

        // parse the version number
        iss >> version;

        if (iss.fail())
        {
            version = 0;
        }
    }

    return version;
}
