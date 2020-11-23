//==============================================================================
// Copyright (c) 2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Implements Gpa counter context related functionalities.
//==============================================================================

#include "gpa_counter_context.h"
#include "gpa_counter_generator_scheduler_manager.h"
#include "gpa_counter_generator.h"

#ifdef WIN32
#include "adapter.h"
#endif

#ifdef ENABLE_GPA_CL
#include "gpa_counter_generator_cl.h"
#include "gpa_counter_scheduler_cl.h"
#endif

#ifdef ENABLE_GPA_GL
#include "gpa_counter_generator_gl.h"
#include "gpa_counter_scheduler_gl.h"
#endif

#ifdef ENABLE_GPA_VK
#include "gpa_counter_generator_vk.h"
#include "gpa_counter_scheduler_vk.h"
#endif

#ifdef WIN32
#ifdef ENABLE_GPA_DX11
#include "gpa_counter_generator_dx11.h"
#include "gpa_counter_scheduler_dx11.h"
#endif

#ifdef ENABLE_GPA_DX12
#include "gpa_counter_generator_dx12.h"
#include "gpa_counter_scheduler_dx12.h"
#endif
#endif

GpaCounterContext::GpaCounterContext(const GPA_API_Type&                  api_type,
                                     const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                                     const GPA_OpenContextFlags&          context_flags,
                                     const gpa_uint8&                     generate_asic_specific_counters)
    : gpa_api_type_(api_type)
    , asic_specific_(generate_asic_specific_counters)
    , gpa_open_context_flags_(context_flags)
    , initialized_(false)
    , gpa_counter_accessor_(nullptr)
    , gpa_counter_scheduler_(nullptr)
{
    gpa_hw_info_.SetVendorID(gpa_counter_context_hardware_info.vendor_id);
    gpa_hw_info_.SetDeviceID(gpa_counter_context_hardware_info.device_id);
    gpa_hw_info_.SetRevisionID(gpa_counter_context_hardware_info.revision_id);

    if (0 < gpa_counter_context_hardware_info.gpa_hardware_attribute_count && nullptr != gpa_counter_context_hardware_info.gpa_hardware_attributes)
    {
        for (unsigned int i = 0; i < gpa_counter_context_hardware_info.gpa_hardware_attribute_count; i++)
        {
            const GpaHardwareAttribute gpa_hardware_attribute = gpa_counter_context_hardware_info.gpa_hardware_attributes[i];
            const gpa_uint32           attribute_val          = gpa_hardware_attribute.gpa_hardware_attribute_value;

            switch (gpa_hardware_attribute.gpa_hardware_attribute_type)
            {
            case GPA_HARDWARE_ATTRIBUTE_NUM_SHADER_ENGINES:
                gpa_hw_info_.SetNumberShaderEngines(attribute_val);
                break;
            case GPA_HARDWARE_ATTRIBUTE_NUM_SHADER_ARRAYS:
                gpa_hw_info_.SetNumberShaderArrays(attribute_val);
                break;
            case GPA_HARDWARE_ATTRIBUTE_NUM_SIMDS:
                gpa_hw_info_.SetNumberSIMDs(attribute_val);
                break;
            case GPA_HARDWARE_ATTRIBUTE_NUM_COMPUTE_UNITS:
                gpa_hw_info_.SetNumberCUs(attribute_val);
                break;
            case GPA_HARDWARE_ATTRIBUTE_TIMESTAMP_FREQUENCY:
                gpa_hw_info_.SetTimeStampFrequency(attribute_val);
                break;
            case GPA_HARDWARE_ATTRIBUTE_NUM_RENDER_BACKENDS:
            case GPA_HARDWARE_ATTRIBUTE_CLOCKS_PER_PRIMITIVE:
            case GPA_HARDWARE_ATTRIBUTE_NUM_PRIMITIVE_PIPES:
            case GPA_HARDWARE_ATTRIBUTE_PEAK_VERTICES_PER_CLOCK:
            case GPA_HARDWARE_ATTRIBUTE_PEAK_PRIMITIVES_PER_CLOCK:
            case GPA_HARDWARE_ATTRIBUTE_PEAK_PIXELS_PER_CLOCK:
                GPA_LogDebugMessage("Unused attributes");
            }
        }
    }
}

bool GpaCounterContext::InitCounters()
{
    if (!initialized_)
    {
        if (gpa_hw_info_.UpdateDeviceInfoBasedOnDeviceID())
        {
            gpa_uint32 vendorId;
            gpa_uint32 deviceId;
            gpa_uint32 revisionId;

            if (gpa_hw_info_.GetVendorID(vendorId) && gpa_hw_info_.GetDeviceID(deviceId) && gpa_hw_info_.GetRevisionID(revisionId))
            {
                const GPA_Status status = ::GenerateCounters(
                    gpa_api_type_, vendorId, deviceId, revisionId, gpa_open_context_flags_, asic_specific_, &gpa_counter_accessor_, &gpa_counter_scheduler_);

                if (GPA_STATUS_OK == status)
                {
                    initialized_ = true;
                }
            }
        }
    }

    return initialized_;
}

const GPA_HWInfo* GpaCounterContext::GetHardwareInfo() const
{
    return &gpa_hw_info_;
}

const IGPACounterAccessor* GpaCounterContext::GetCounterAccessor() const
{
    if (initialized_)
    {
        return gpa_counter_accessor_;
    }

    return nullptr;
}

IGPACounterScheduler* GpaCounterContext::GetCounterScheduler() const
{
    if (initialized_)
    {
        return gpa_counter_scheduler_;
    }

    return nullptr;
}

_GPA_CounterContext::_GPA_CounterContext(GpaCounterContext* gpa_counter_context)
    : gpa_counter_context(gpa_counter_context)
{
}

GpaCounterContext* _GPA_CounterContext::operator->() const
{
    return gpa_counter_context;
}

_GPA_CounterContext::~_GPA_CounterContext()
{
    gpa_counter_context = nullptr;
}

GpaCounterContextManager* GpaCounterContextManager::Instance()
{
    if (nullptr == gpa_counter_context_manager_)
    {
        gpa_counter_context_manager_ = new (std::nothrow) GpaCounterContextManager();
    }

    return gpa_counter_context_manager_;
}

void GpaCounterContextManager::DeleteInstance()
{
    delete gpa_counter_context_manager_;
    gpa_counter_context_manager_ = nullptr;
}

GpaCounterContextManager::~GpaCounterContextManager()
{
    CloseAllContext();
}

GPA_Status GpaCounterContextManager::OpenCounterContext(const GPA_API_Type&                  api_type,
                                                        const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                                                        const GPA_OpenContextFlags&          context_flags,
                                                        const gpa_uint8&                     generate_asic_specific_counters,
                                                        GPA_CounterContext*                  gpa_counter_context)
{
    Init(api_type);

    GpaCounterContext* gpa_new_counter_context =
        new (std::nothrow) GpaCounterContext(api_type, gpa_counter_context_hardware_info, context_flags, generate_asic_specific_counters);

    if (nullptr != gpa_new_counter_context)
    {
        if (gpa_new_counter_context->InitCounters())
        {
            GPA_CounterContext gpa_counter_context_ret = new (std::nothrow) _GPA_CounterContext(gpa_new_counter_context);

            if (nullptr != gpa_counter_context_ret)
            {
                gpa_counter_context_map_.insert(std::pair<GPA_CounterContext, GPA_API_Type>(gpa_counter_context_ret, api_type));
                *gpa_counter_context = gpa_counter_context_ret;
                return GPA_STATUS_OK;
            }

            *gpa_counter_context = nullptr;
            return GPA_STATUS_ERROR_FAILED;
        }

        delete gpa_new_counter_context;
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    return GPA_STATUS_ERROR_FAILED;
}

const IGPACounterAccessor* GpaCounterContextManager::GetCounterAccessor(const GPA_CounterContext gpa_counter_context)
{
    auto iter = gpa_counter_context_map_.find(gpa_counter_context);
    if (iter != gpa_counter_context_map_.end())
    {
        GPA_CounterContext counter_context = iter->first;
        return (*counter_context)->GetCounterAccessor();
    }

    return nullptr;
}

IGPACounterScheduler* GpaCounterContextManager::GetCounterScheduler(const GPA_CounterContext gpa_counter_context)
{
    auto iter = gpa_counter_context_map_.find(gpa_counter_context);
    if (iter != gpa_counter_context_map_.end())
    {
        GPA_CounterContext counter_context = iter->first;
        return (*counter_context)->GetCounterScheduler();
    }

    return nullptr;
}

GPA_Status GpaCounterContextManager::CloseCounterContext(const GPA_CounterContext gpa_counter_context)
{
    auto iter = gpa_counter_context_map_.find(gpa_counter_context);
    if (iter != gpa_counter_context_map_.end())
    {
        GPA_CounterContext counter_context = iter->first;
        delete counter_context->gpa_counter_context;
        delete counter_context;
        counter_context = nullptr;
        gpa_counter_context_map_.erase(gpa_counter_context);
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_CONTEXT_NOT_FOUND;
}

bool GpaCounterContextManager::IsCounterContextOpen(GPA_CounterContext gpa_counter_context)
{
    if (gpa_counter_context_map_.find(gpa_counter_context) != gpa_counter_context_map_.end())
    {
        return true;
    }

    return false;
}

void GpaCounterContextManager::Init(const GPA_API_Type& api_type)
{
    if (gpa_counter_scheduler_map_.empty())
    {
        gpa_counter_scheduler_map_.insert(std::pair<GPA_API_Type, IGPACounterScheduler*>(GPA_API_DIRECTX_11, nullptr));
        gpa_counter_scheduler_map_.insert(std::pair<GPA_API_Type, IGPACounterScheduler*>(GPA_API_DIRECTX_12, nullptr));
        gpa_counter_scheduler_map_.insert(std::pair<GPA_API_Type, IGPACounterScheduler*>(GPA_API_OPENGL, nullptr));
        gpa_counter_scheduler_map_.insert(std::pair<GPA_API_Type, IGPACounterScheduler*>(GPA_API_OPENCL, nullptr));
        gpa_counter_scheduler_map_.insert(std::pair<GPA_API_Type, IGPACounterScheduler*>(GPA_API_VULKAN, nullptr));
    }

    if (gpa_counter_accessor_map_.empty())
    {
        gpa_counter_accessor_map_.insert(std::pair<GPA_API_Type, IGPACounterAccessor*>(GPA_API_DIRECTX_11, nullptr));
        gpa_counter_accessor_map_.insert(std::pair<GPA_API_Type, IGPACounterAccessor*>(GPA_API_DIRECTX_12, nullptr));
        gpa_counter_accessor_map_.insert(std::pair<GPA_API_Type, IGPACounterAccessor*>(GPA_API_OPENGL, nullptr));
        gpa_counter_accessor_map_.insert(std::pair<GPA_API_Type, IGPACounterAccessor*>(GPA_API_OPENCL, nullptr));
        gpa_counter_accessor_map_.insert(std::pair<GPA_API_Type, IGPACounterAccessor*>(GPA_API_VULKAN, nullptr));
    }

    InitCounterAccessor(api_type);
    InitCounterScheduler(api_type);
}

void GpaCounterContextManager::InitCounterAccessor(const GPA_API_Type& api_type)
{
    if (nullptr != gpa_counter_accessor_map_[api_type])
    {
        return;
    }

    switch (api_type)
    {
    case GPA_API_DIRECTX_11:
#ifdef ENABLE_GPA_DX11
        gpa_counter_accessor_map_[GPA_API_DIRECTX_11] = new GPA_CounterGeneratorDX11();
#endif
        break;
    case GPA_API_DIRECTX_12:
#ifdef ENABLE_GPA_DX12
        gpa_counter_accessor_map_[GPA_API_DIRECTX_12] = new GPA_CounterGeneratorDX12();
#endif
        break;
    case GPA_API_OPENGL:
#ifdef ENABLE_GPA_GL
        gpa_counter_accessor_map_[GPA_API_OPENGL] = new GPA_CounterGeneratorGL();
#endif
        break;
    case GPA_API_OPENCL:
#ifdef ENABLE_GPA_CL
        gpa_counter_accessor_map_[GPA_API_OPENCL] = new GPA_CounterGeneratorCL();
#endif
        break;
    case GPA_API_VULKAN:
#ifdef ENABLE_GPA_VK
        gpa_counter_accessor_map_[GPA_API_VULKAN] = new GPA_CounterGeneratorVK();
#endif
        break;
    default:
        break;
    }
}

void GpaCounterContextManager::InitCounterScheduler(const GPA_API_Type& api_type)
{
    if (nullptr != gpa_counter_scheduler_map_[api_type])
    {
        return;
    }

    switch (api_type)
    {
    case GPA_API_DIRECTX_11:
#ifdef ENABLE_GPA_DX11
        gpa_counter_scheduler_map_[GPA_API_DIRECTX_11] = new GPA_CounterSchedulerDX11();
#endif
        break;
    case GPA_API_DIRECTX_12:
#ifdef ENABLE_GPA_DX12
        gpa_counter_scheduler_map_[GPA_API_DIRECTX_11] = new GPA_CounterSchedulerDX12();
#endif
        break;
    case GPA_API_OPENGL:
#ifdef ENABLE_GPA_GL
        gpa_counter_scheduler_map_[GPA_API_OPENGL] = new GPA_CounterSchedulerGL();
#endif
        break;
    case GPA_API_OPENCL:
#ifdef ENABLE_GPA_CL
        gpa_counter_scheduler_map_[GPA_API_OPENCL] = new GPA_CounterSchedulerCL();
#endif
        break;
    case GPA_API_VULKAN:
#ifdef ENABLE_GPA_VK
        gpa_counter_scheduler_map_[GPA_API_VULKAN] = new GPA_CounterSchedulerVK();
#endif
        break;
    default:
        break;
    }
}

void GpaCounterContextManager::CloseAllContext()
{
    for (auto iter = gpa_counter_context_map_.begin(); iter != gpa_counter_context_map_.end(); ++iter)
    {
        GPA_CounterContext counter_context = iter->first;
        delete counter_context->gpa_counter_context;
        delete counter_context;
    }
    gpa_counter_context_map_.clear();

    for (auto iter = gpa_counter_accessor_map_.begin(); iter != gpa_counter_accessor_map_.end(); ++iter)
    {
        IGPACounterAccessor* counter_accessor = iter->second;
        delete counter_accessor;
    }
    gpa_counter_accessor_map_.clear();

    for (auto iter = gpa_counter_scheduler_map_.begin(); iter != gpa_counter_scheduler_map_.end(); ++iter)
    {
        IGPACounterScheduler* counter_scheduler = iter->second;
        delete counter_scheduler;
    }
    gpa_counter_scheduler_map_.clear();
}
