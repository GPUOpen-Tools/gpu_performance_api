//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA CL Context Implementation
//==============================================================================

#include "cl_gpa_context.h"
#include "gpa_unique_object.h"
#include "cl_gpa_implementor.h"
#include "cl_gpa_session.h"
#include "cl_perf_counter_amd_extension.h"
#include "cl_rt_module_loader.h"

ClGpaContext::ClGpaContext(cl_command_queue& cl_command_queue, GpaHwInfo& hw_info, GpaOpenContextFlags context_flags)
    : GpaContext(hw_info, context_flags)
    , cl_command_queue_(cl_command_queue)
    , cl_device_id_(nullptr)
    , clock_mode_(CL_DEVICE_CLOCK_MODE_DEFAULT_AMD)
    , cl_driver_version_(0)
{
}

ClGpaContext::~ClGpaContext()
{
    GpaStatus set_stable_clocks_status = SetStableClocks(false);

    if (kGpaStatusOk != set_stable_clocks_status)
    {
        GPA_LOG_ERROR("Driver was unable to set stable clocks back to default.");
#ifdef __linux__
        GPA_LOG_MESSAGE("In Linux, make sure to run your application with root privileges.");
#endif  //__linux__
    }
}

GpaSessionId ClGpaContext::CreateSession(GpaSessionSampleType sample_type)
{
    GpaSessionId ret_session_id = nullptr;

    ClGpaSession* new_gpa_cl_gpa_session = new (std::nothrow) ClGpaSession(this, sample_type);

    if (nullptr == new_gpa_cl_gpa_session)
    {
        GPA_LOG_ERROR("Unable to allocate memory for the session.");
    }
    else
    {
        AddGpaSession(new_gpa_cl_gpa_session);

        if (nullptr != new_gpa_cl_gpa_session)
        {
            ret_session_id = reinterpret_cast<GpaSessionId>(GpaUniqueObjectManager::Instance()->CreateObject(new_gpa_cl_gpa_session));
        }
    }

    return ret_session_id;
}

bool ClGpaContext::DeleteSession(GpaSessionId session_id)
{
    bool is_deleted = false;

    ClGpaSession* cl_gpa_session = reinterpret_cast<ClGpaSession*>(session_id->Object());

    if (nullptr != cl_gpa_session)
    {
        RemoveGpaSession(cl_gpa_session);
        GpaUniqueObjectManager::Instance()->DeleteObject(cl_gpa_session);
        delete cl_gpa_session;
        is_deleted = true;
    }

    return is_deleted;
}

GpaUInt32 ClGpaContext::GetMaxGpaSessions() const
{
    // maximum latency is 4 for dx10-capable cards
    return 4;
}

GpaApiType ClGpaContext::GetApiType() const
{
    return kGpaApiOpencl;
}

bool ClGpaContext::Initialize(cl_device_id& cl_device_id_param)
{
    cl_device_id_ = cl_device_id_param;

    OpenCLModule* ocl_module = ClRuntimeModuleLoader::Instance()->GetApiRuntimeModule();

    if (nullptr == ocl_module)
    {
        GPA_LOG_ERROR("OpenCL runtime module is NULL.");
    }
    else
    {
        static const GpaUInt32 kMaxStr = 256;
        char                   driver_version[kMaxStr];

        if (CL_SUCCESS != ocl_module->GetDeviceInfo(cl_device_id_, CL_DRIVER_VERSION, kMaxStr, driver_version, nullptr))
        {
            GPA_LOG_ERROR("Unable to get driver version.");
        }
        else
        {
            cl_driver_version_ = ExtractDriverVersion(driver_version);
        }
    }

    GpaStatus set_stable_clocks_status = SetStableClocks(true);

    if (kGpaStatusOk != set_stable_clocks_status)
    {
        GPA_LOG_ERROR("Driver was unable to set stable clocks for profiling.");
#ifdef __linux__
        GPA_LOG_MESSAGE("In Linux, make sure to run your application with root privileges.");
#endif  //__linux__
    }

    bool success = OpenCounters();

    if (success)
    {
        SetAsOpened(true);
    }

    return success;
}

const cl_device_id& ClGpaContext::GetClDeviceId() const
{
    return cl_device_id_;
}

const cl_command_queue& ClGpaContext::GetClCommandQueue() const
{
    return cl_command_queue_;
}

GpaStatus ClGpaContext::SetStableClocks(bool use_profiling_clocks)
{
    GpaStatus result = kGpaStatusOk;

    if (nullptr == my_cl_set_device_clock_mode_amd)
    {
        GPA_LOG_MESSAGE("clSetDeviceClockModeAMD extension is not available.");

        // TODO: return an error once we no longer need to support pre-19.10 drivers
        // result = GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;
    }
    else
    {
        cl_set_device_clock_mode_input_amd clockMode = {};

        if (use_profiling_clocks)
        {
            DeviceClockMode deviceClockMode = GetDeviceClockMode();

            switch (deviceClockMode)
            {
            case DeviceClockMode::kDefault:
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_DEFAULT_AMD;
                break;

            case DeviceClockMode::kProfiling:
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_PROFILING_AMD;
                break;

            case DeviceClockMode::kMinimumMemory:
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_MINIMUMMEMORY_AMD;
                break;

            case DeviceClockMode::kMinimumEngine:
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_MINIMUMENGINE_AMD;
                break;

            case DeviceClockMode::kPeak:
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_PEAK_AMD;
                break;

            default:
                assert(0);
                clockMode.clock_mode = CL_DEVICE_CLOCK_MODE_PROFILING_AMD;
                break;
            }
        }

        if (clockMode.clock_mode != clock_mode_)
        {
            clock_mode_   = clockMode.clock_mode;
            cl_int status = my_cl_set_device_clock_mode_amd(cl_device_id_, clockMode, nullptr);
            result        = (CL_SUCCESS == status) ? kGpaStatusOk : kGpaStatusErrorDriverNotSupported;

            if (CL_SUCCESS != status)
            {
#ifdef _LINUX
                // make sure the driver is new enough to support setting stable clocks
                // on Linux with pre-gfx9 devices, setting the clock mode fails with current drivers
                // in this case, simply act as if the call was successful by returning success
                const GPA_HWInfo* kHwInfo = GetHwInfo();
                GDT_HW_GENERATION gen     = GDT_HW_GENERATION_NONE;

                // CL driver version where stable clocks are working on Linux for pre-GFX9 devices
                static const int s_CL_DRIVER_VER_WITH_LINUX_STABLE_CLOCK_SUPPORT = 2904;

                if ((s_CL_DRIVER_VER_WITH_LINUX_STABLE_CLOCK_SUPPORT > cl_driver_version_) && kHwInfo->GetHWGeneration(gen) && GDT_HW_GENERATION_GFX9 > gen)
                {
                    result = kGpaStatusOk;
                }
                else
#endif
                {
                    GPA_LOG_ERROR("Failed to set ClockMode for profiling.");
                }
            }
        }
    }

    return result;
}

int ClGpaContext::ExtractDriverVersion(const char* version_str) const
{
    int version = 0;

    if (nullptr != version_str)
    {
        std::string str_ver(version_str);

        // the build number ends at the first dot
        size_t end_build = str_ver.find_first_of('.');

        // truncate the input at the first dot
        str_ver = str_ver.substr(0, end_build);

        std::istringstream iss(str_ver);

        // parse the version_str number
        iss >> version;

        if (iss.fail())
        {
            version = 0;
        }
    }

    return version;
}
