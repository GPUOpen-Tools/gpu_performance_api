//==============================================================================
// Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.
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

static GpaCounterGeneratorGl* counter_generator_gl = nullptr;  ///< Static instance of GL generator.
static GpaCounterSchedulerGl* counter_scheduler_gl = nullptr;  ///< Static instance of GL scheduler.

IGpaImplementor* CreateImplementor()
{
    counter_generator_gl = new GpaCounterGeneratorGl(kGpaSessionSampleTypeDiscreteCounter);
    counter_scheduler_gl = new GpaCounterSchedulerGl(kGpaSessionSampleTypeDiscreteCounter);

    return GlGpaImplementor::Instance();
}

void DestroyImplementor(IGpaImplementor* impl)
{
    if (counter_generator_gl != nullptr)
    {
        delete counter_generator_gl;
        counter_generator_gl = nullptr;
    }

    if (counter_scheduler_gl != nullptr)
    {
        delete counter_scheduler_gl;
        counter_scheduler_gl = nullptr;
    }

    if (nullptr != impl)
    {
        GlGpaImplementor::DeleteInstance();
    }
}

GpaApiType GlGpaImplementor::GetApiType() const
{
    return kGpaApiOpengl;
}

bool GlGpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(context_info);
    UNREFERENCED_PARAMETER(flags);

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

        // Use the GPIN counters exposed by the driver to identify the hardware.
        ogl_utils::AsicInfo asic_info;

        if (!ogl_utils::GetAsicInfoFromDriver(asic_info))
        {
            GPA_LOG_ERROR("Unable to obtain asic information.");
            return false;
        }

        if (ogl_utils::AsicInfo::kUnassignedAsicInfo != asic_info.device_id)
        {
            hw_info.SetDeviceId(asic_info.device_id);

            if (ogl_utils::AsicInfo::kUnassignedAsicInfo != asic_info.device_rev)
            {
                hw_info.SetRevisionId(asic_info.device_rev);

                GDT_GfxCardInfo card_info = {};
                if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(asic_info.device_id, asic_info.device_rev, card_info))
                {
                    hw_info.SetHwGeneration(card_info.m_generation);
                }
            }

            AMDTDeviceInfoUtils::DeleteInstance();
        }

        if (ogl_utils::AsicInfo::kUnassignedAsicInfo != asic_info.num_se)
        {
            hw_info.SetNumberShaderEngines(static_cast<size_t>(asic_info.num_se));

            if (ogl_utils::AsicInfo::kUnassignedAsicInfo != asic_info.num_sa_per_se)
            {
                hw_info.SetNumberShaderArrays(static_cast<size_t>(asic_info.num_sa_per_se * asic_info.num_se));
            }
        }

        if (ogl_utils::AsicInfo::kUnassignedAsicInfo != asic_info.num_cu)
        {
            hw_info.SetNumberCus(static_cast<size_t>(asic_info.num_cu));
        }

        if (ogl_utils::AsicInfo::kUnassignedAsicInfo != asic_info.num_simd)
        {
            hw_info.SetNumberSimds(static_cast<size_t>(asic_info.num_simd));
        }

        // GPUTime information is returned in nanoseconds, so set the frequency to convert it into seconds.
        hw_info.SetTimeStampFrequency(1000000000);

        return true;
    }

    GPA_LOG_ERROR("A non-AMD graphics card was identified.");
    return false;
}

bool GlGpaImplementor::VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(context_info);
    UNREFERENCED_PARAMETER(flags);
    UNREFERENCED_PARAMETER(hw_info);
    return true;
}

GlGpaImplementor::GlGpaImplementor()
    : is_gl_entry_points_initialized_(false)
{
}

IGpaContext* GlGpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags)
{
    UNREFERENCED_PARAMETER(context_info);
    GlGpaContext* ret_gpa_context = nullptr;

    GlContextPtr gl_context = static_cast<GlContextPtr>(context_info);

    GlGpaContext* gl_gpa_context = new (std::nothrow) GlGpaContext(gl_context, hw_info, flags);

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

bool GlGpaImplementor::CloseApiContext(IGpaContext* context)
{
    assert(nullptr != context);

    GpaStatus set_default_clocks_result = kGpaStatusOk;

    if (nullptr != context)
    {
        GlGpaContext* gl_gpa_context = reinterpret_cast<GlGpaContext*>(context);
        set_default_clocks_result    = gl_gpa_context->SetStableClocks(false);
        if (set_default_clocks_result != kGpaStatusOk)
        {
            assert(!"Unable to set clocks back to default");
            GPA_LOG_ERROR("Unable to set clocks back to default");
        }
        delete gl_gpa_context;
    }

    ogl_utils::UnloadGl();

    return set_default_clocks_result == kGpaStatusOk;
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
        if (ogl_utils::IsMesaDriver())
        {
            GPA_LOG_ERROR("The Mesa driver is not supported.");
            return false;
        }
    }
    else
    {
        is_supported = false;
    }
    return is_supported;
}
