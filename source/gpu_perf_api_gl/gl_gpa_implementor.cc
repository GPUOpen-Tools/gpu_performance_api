//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL GPA Implementation
//==============================================================================

#include "gpu_perf_api_gl/gl_gpa_implementor.h"

#include <assert.h>

#include "DeviceInfoUtils.h"

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_gl.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_gl.h"

#include "gpu_perf_api_gl/asic_info.h"
#include "gpu_perf_api_gl/gl_gpa_context.h"

IGpaImplementor*             gpa_imp = GlGpaImplementor::Instance();
static GpaCounterGeneratorGl counter_generator_gl;  ///< Static instance of GL generator.
static GpaCounterSchedulerGl counter_scheduler_gl;  ///< Static instance of GL scheduler.

GpaApiType GlGpaImplementor::GetApiType() const
{
    return kGpaApiOpengl;
}

bool GlGpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(context_info);

    // Get the entry points.
    is_gl_entry_points_initialized_ = ogl_utils::InitializeGlFunctions();

    if (!is_gl_entry_points_initialized_)
    {
        GPA_LOG_ERROR("Unable to initialize essential GL functions.");
        return is_gl_entry_points_initialized_;
    }

    const GLubyte* renderer = ogl_utils::ogl_get_string(GL_RENDERER);

    if (nullptr == renderer)
    {
        GPA_LOG_ERROR("Unable to get GL_RENDERER string.");
        return false;
    }

    hw_info.SetDeviceName(reinterpret_cast<const char*>(renderer));

    // Handle non-AMD GPU vendors.
    const GLubyte* vendor        = ogl_utils::ogl_get_string(GL_VENDOR);
    bool           is_amd_vendor = false;

    if (nullptr == vendor)
    {
        GPA_LOG_ERROR("Unable to get GL_VENDOR string.");
        return false;
    }

    if (nullptr != strstr(reinterpret_cast<const char*>(vendor), ogl_utils::kAtiRendererString) ||
        nullptr != strstr(reinterpret_cast<const char*>(vendor), ogl_utils::kAmdRendererString))
    {
        is_amd_vendor = true;
    }
    else if (nullptr != strstr(reinterpret_cast<const char*>(vendor), ogl_utils::kNvidiaRendererString))
    {
        return false;
    }
    else if (nullptr != strstr(reinterpret_cast<const char*>(vendor), ogl_utils::kIntelRendererString))
    {
        return false;
    }

    // In addition to checking the vendor string to make sure it is ATI / AMD,
    // also check the Renderer string - sometimes the GL driver needs to override
    // the vendor string to make apps behave differently, so using the renderer
    // offers a fallback solution.
    if (is_amd_vendor || nullptr != strstr(reinterpret_cast<const char*>(renderer), ogl_utils::kAtiRendererString) ||
        nullptr != strstr(reinterpret_cast<const char*>(renderer), ogl_utils::kAmdRendererString) ||
        nullptr != strstr(reinterpret_cast<const char*>(renderer), ogl_utils::kRadeonRendererString))
    {
        hw_info.SetVendorId(kAmdVendorId);

        bool         is_device_id_known = false;
        unsigned int driver_device_id;

        // First we attempt to retrieve the device ID from platform extensions.
        if (GetDeviceIdFromPlatformExt(driver_device_id))
        {
            // Check to make sure the device id returned is found in the device info table.
            GDT_HW_GENERATION hw_generation;
            is_device_id_known = AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(driver_device_id, hw_generation);

            if (is_device_id_known)
            {
                hw_info.SetDeviceId(driver_device_id);

                if (!hw_info.UpdateRevisionIdBasedOnDeviceIdAndName())
                {
                    // We didn't find a revision Id, set it to REVISION_ID_ANY.
                    hw_info.SetRevisionId(REVISION_ID_ANY);
                }
            }
        }

        // If we were unable to retrieve the device ID using platform extensions,
        // then fall back to the GPIN counters exposed by the driver.
        if (!is_device_id_known)
        {
            ogl_utils::AsicInfo asic_info;

            if (!ogl_utils::GetAsicInfoFromDriver(asic_info))
            {
                GPA_LOG_ERROR("Unable to obtain asic information.");
                return false;
            }

            gl_driver_version_ = asic_info.driver_version;

            bool is_hw_info_valid = false;

            if (ogl_utils::AsicInfo::unassigned_asic_info != asic_info.device_id)
            {
                hw_info.SetDeviceId(asic_info.device_id);

                if (ogl_utils::AsicInfo::unassigned_asic_info != asic_info.device_rev)
                {
                    GDT_GfxCardInfo card_info = {};

                    if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(asic_info.device_id, asic_info.device_rev, card_info))
                    {
                        is_hw_info_valid = true;
                        hw_info.SetRevisionId(asic_info.device_rev);
                    }
                }

                if (!is_hw_info_valid)
                {
                    is_hw_info_valid = hw_info.UpdateRevisionIdBasedOnDeviceIdAndName();
                }
            }

            if (!is_hw_info_valid)
            {
                // This is now a fall-back path when using drivers where the
                // additional GPIN counters are not supported. This if block
                // can be removed once we no longer need to support drivers older
                // than 19.30.
                GDT_HW_ASIC_TYPE asic_type = GDT_ASIC_TYPE_NONE;
                uint32_t         device_id;

                if (ogl_utils::GetFallbackAsicInfo(asic_info.asic_revision, asic_type, device_id))
                {
                    hw_info.SetDeviceId(static_cast<GpaUInt32>(device_id));
                }
                else
                {
                    GPA_LOG_ERROR("Unsupported asic ID.");
                    return false;
                }

                if (!hw_info.UpdateDeviceInfoBasedOnAsicTypeAndName(asic_type))
                {
                    // We didn't find a revision Id, set it to REVISION_ID_ANY.
                    hw_info.SetRevisionId(REVISION_ID_ANY);
                }
            }

            if (ogl_utils::AsicInfo::unassigned_asic_info != asic_info.num_se)
            {
                hw_info.SetNumberShaderEngines(static_cast<size_t>(asic_info.num_se));

                if (ogl_utils::AsicInfo::unassigned_asic_info != asic_info.num_sa_per_se)
                {
                    hw_info.SetNumberShaderArrays(static_cast<size_t>(asic_info.num_sa_per_se * asic_info.num_se));
                }
            }

            if (ogl_utils::AsicInfo::unassigned_asic_info != asic_info.num_cu)
            {
                hw_info.SetNumberCus(static_cast<size_t>(asic_info.num_cu));
            }

            if (ogl_utils::AsicInfo::unassigned_asic_info != asic_info.num_simd)
            {
                hw_info.SetNumberSimds(static_cast<size_t>(asic_info.num_simd));
            }
        }

        // GPUTime information is returned in nanoseconds, so set the frequency to convert it into seconds.
        hw_info.SetTimeStampFrequency(1000000000);

        return true;
    }

    GPA_LOG_ERROR("A non-AMD graphics card was identified.");
    return false;
}

bool GlGpaImplementor::VerifyApiHwSupport(const GpaContextInfoPtr context_info, const GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(context_info);

    bool is_supported = false;

    GDT_HW_GENERATION generation = GDT_HW_GENERATION_NONE;

    if (!hw_info.GetHwGeneration(generation))
    {
        GPA_LOG_ERROR("Unable to get hardware generation.");
    }
    else
    {
        is_supported = true;
    }

    return is_supported;
}

GlGpaImplementor::GlGpaImplementor()
    : is_gl_entry_points_initialized_(false)
    , gl_driver_version_(INT_MAX)
{
}

IGpaContext* GlGpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, GpaHwInfo& hw_info, GpaOpenContextFlags flags)
{
    UNREFERENCED_PARAMETER(context_info);
    GlGpaContext* ret_gpa_context = nullptr;

    GlContextPtr gl_context = static_cast<GlContextPtr>(context_info);

    GlGpaContext* gl_gpa_context = new (std::nothrow) GlGpaContext(gl_context, hw_info, flags, gl_driver_version_);

    if (nullptr == gl_gpa_context)
    {
        GPA_LOG_ERROR("Unable to allocate memory for the context.");
    }
    else
    {
        if (gl_gpa_context->Initialize())
        {
            ret_gpa_context = gl_gpa_context;
        }
        else
        {
            delete gl_gpa_context;
            GPA_LOG_ERROR("Unable to open a context.");
        }
    }

    return ret_gpa_context;
}

bool GlGpaImplementor::CloseApiContext(GpaDeviceIdentifier device_identifier, IGpaContext* context)
{
    UNREFERENCED_PARAMETER(device_identifier);
    assert(nullptr != device_identifier);
    assert(nullptr != context);

    if (nullptr != context)
    {
        delete reinterpret_cast<GlGpaContext*>(context);
        context = nullptr;
    }

    ogl_utils::UnloadGl();

    return true;
}

GpaDeviceIdentifier GlGpaImplementor::GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const
{
    return context_info;
}

bool GlGpaImplementor::IsDriverSupported(GpaContextInfoPtr context_info) const
{
    ogl_utils::InitializeGlCoreFunctions();
    bool is_supported = true;
    if (context_info != nullptr)
    {
        const GLubyte* driver_byte = ogl_utils::ogl_get_string(GL_VERSION);
        std::string driver_string(reinterpret_cast<const char *>(driver_byte));
        if (driver_string.find("Mesa") != std::string::npos)
        {
            GPA_LOG_ERROR("The Mesa driver is not currently supported.");
            return false;
        }
    }
    else
    {
        is_supported = false;
    }
    return is_supported;
}


bool GlGpaImplementor::GetDeviceIdFromPlatformExt(unsigned int& driver_device_id) const
{
    bool device_id_retrieved = false;
#ifdef _LINUX
#ifndef GLES
    if (nullptr != ogl_utils::ogl_x_query_current_renderer_integer_mesa)
    {
        if (ogl_utils::ogl_x_query_current_renderer_integer_mesa(GLX_RENDERER_DEVICE_ID_MESA, &driver_device_id))
        {
            GPA_LOG_MESSAGE("GLX renderer device ID is 0x%04X.", driver_device_id);
            device_id_retrieved = true;
        }
        else
        {
            GPA_LOG_TRACE(
                "glXQueryCurrentRendererIntegerMESA extension is available, but was unable "
                "to retrieve the renderer device ID.");
        }
    }
    else
    {
        GPA_LOG_TRACE("glXQueryCurrentRendererIntegerMESA extension is unavailable.");
    }
#else
    UNREFERENCED_PARAMETER(driver_device_id);
#endif
#else
    UNREFERENCED_PARAMETER(driver_device_id);
#endif

    return device_id_retrieved;
}
