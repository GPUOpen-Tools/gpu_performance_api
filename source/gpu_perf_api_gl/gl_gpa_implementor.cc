//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL GPA Implementation
//==============================================================================

#include "gpu_perf_api_gl/gl_gpa_implementor.h"

#include <cassert>
#include <memory>

#include "device_info.hpp"

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_gl.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_gl.h"

#include "gpu_perf_api_gl/asic_info.h"
#include "gpu_perf_api_gl/gl_gpa_context.h"

namespace
{
    std::unique_ptr<GpaCounterGeneratorGl> counter_generator_gl;  ///< Static instance of GL generator.
    std::unique_ptr<GpaCounterSchedulerGl> counter_scheduler_gl;  ///< Static instance of GL scheduler.
}  // namespace

IGpaImplementor& CreateImplementor()
{
    counter_generator_gl = std::make_unique<GpaCounterGeneratorGl>(kGpaSessionSampleTypeDiscreteCounter);
    counter_scheduler_gl = std::make_unique<GpaCounterSchedulerGl>(kGpaSessionSampleTypeDiscreteCounter);

    return GlGpaImplementor::Instance();
}

void DestroyImplementor()
{
    counter_generator_gl.reset();
    counter_scheduler_gl.reset();
}

GpaStatus GlGpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(context_info);
    UNREFERENCED_PARAMETER(flags);

    // Get the entry points.
    is_gl_entry_points_initialized_ = ogl_utils::InitializeGlFunctions();

    if (!is_gl_entry_points_initialized_)
    {
        GpaLogger::Instance().LogError("Unable to initialize essential GL functions.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    const GLubyte* renderer = ogl_utils::ogl_get_string(GL_RENDERER);

    if (nullptr == renderer)
    {
        GpaLogger::Instance().LogError("Unable to get GL_RENDERER string.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    hw_info.SetDeviceName(reinterpret_cast<const char*>(renderer));

    const GLubyte* vendor = ogl_utils::ogl_get_string(GL_VENDOR);

    if (nullptr == vendor)
    {
        GpaLogger::Instance().LogError("Unable to get GL_VENDOR string.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    const bool is_amd_vendor = nullptr != strstr(reinterpret_cast<const char*>(vendor), ogl_utils::kAtiRendererString) ||
                               nullptr != strstr(reinterpret_cast<const char*>(vendor), ogl_utils::kAmdRendererString);

    // Also check the renderer string — the GL driver sometimes overrides the vendor string to change app behavior.
    if (is_amd_vendor || nullptr != strstr(reinterpret_cast<const char*>(renderer), ogl_utils::kAtiRendererString) ||
        nullptr != strstr(reinterpret_cast<const char*>(renderer), ogl_utils::kAmdRendererString) ||
        nullptr != strstr(reinterpret_cast<const char*>(renderer), ogl_utils::kRadeonRendererString))
    {
        hw_info.SetVendorId(device_info::kAmdVendorId);

        // Use the GPIN counters exposed by the driver to identify the hardware.
        ogl_utils::AsicInfo asic_info;

        if (!ogl_utils::GetAsicInfoFromDriver(asic_info))
        {
            GpaLogger::Instance().LogError("Unable to obtain asic information.");
            return kGpaStatusErrorHardwareNotSupported;
        }

        if (ogl_utils::AsicInfo::kUnassignedAsicInfo != asic_info.device_id)
        {
            hw_info.SetDeviceId(asic_info.device_id);

            if (ogl_utils::AsicInfo::kUnassignedAsicInfo != asic_info.device_rev)
            {
                hw_info.SetRevisionId(asic_info.device_rev);

                if (const std::optional<device_info::CardInfo> card_info = device_info::GetCardInfo(hw_info.GetDeviceDescription().value());
                    card_info.has_value())
                {
                    hw_info.SetHwGeneration(card_info->generation);
                }
                else
                {
                    GpaLogger::Instance().LogError("Unable to get device info from device_info library.");
                    return kGpaStatusErrorHardwareNotSupported;
                }
            }
            else
            {
                GpaLogger::Instance().LogError("Invalid revision id.");
                return kGpaStatusErrorHardwareNotSupported;
            }
        }
        else
        {
            GpaLogger::Instance().LogError("Invalid device id.");
            return kGpaStatusErrorHardwareNotSupported;
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

        return kGpaStatusOk;
    }

    GpaLogger::Instance().LogError("A non-AMD graphics card was identified.");
    return kGpaStatusErrorHardwareNotSupported;
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

std::unique_ptr<IGpaContext> GlGpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags)
{
    UNREFERENCED_PARAMETER(context_info);
    std::unique_ptr<IGpaContext> ret_gpa_context;

    GlContextPtr gl_context = static_cast<GlContextPtr>(context_info);

    auto gl_gpa_context = std::make_unique<GlGpaContext>(gl_context, hw_info, flags);

    if (gl_gpa_context->Initialize())
    {
        ret_gpa_context = std::move(gl_gpa_context);
    }
    else
    {
        GpaLogger::Instance().LogError("Unable to open a context.");
    }

    return ret_gpa_context;
}

bool GlGpaImplementor::CloseApiContext(std::unique_ptr<IGpaContext> context)
{
    assert(context);

    GlGpaContext*   gl_gpa_context            = reinterpret_cast<GlGpaContext*>(context.get());
    const GpaStatus set_default_clocks_result = gl_gpa_context->SetStableClocks(false);
    if (set_default_clocks_result != kGpaStatusOk)
    {
        assert(!"Unable to set clocks back to default");
        GpaLogger::Instance().LogError("Unable to set clocks back to default");
    }
    // context destroyed when unique_ptr goes out of scope.

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
            GpaLogger::Instance().LogError("The Mesa driver is not supported.");
            return false;
        }
    }
    else
    {
        is_supported = false;
    }
    return is_supported;
}
