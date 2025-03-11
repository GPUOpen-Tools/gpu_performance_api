//==============================================================================
// Copyright (c) 2020-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Implements Gpa counter context related functionality.
//==============================================================================

#include "gpa_counter_context_handler.h"
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

GpaCounterContextHandler::GpaCounterContextHandler(const GpaApiType&                    api_type,
                                                   const GpaSessionSampleType           sample_type,
                                                   const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                                                   const GpaOpenContextFlags&           context_flags)
    : gpa_api_type_(api_type)
    , sample_type_(sample_type)
    , gpa_open_context_flags_(context_flags)
    , initialized_(false)
    , gpa_counter_accessor_(nullptr)
    , gpa_counter_scheduler_(nullptr)
{
    gpa_hw_info_.SetVendorId(gpa_counter_context_hardware_info.vendor_id);
    gpa_hw_info_.SetDeviceId(gpa_counter_context_hardware_info.device_id);
    gpa_hw_info_.SetRevisionId(gpa_counter_context_hardware_info.revision_id);

    if (0 < gpa_counter_context_hardware_info.gpa_hardware_attribute_count && nullptr != gpa_counter_context_hardware_info.gpa_hardware_attributes)
    {
        for (unsigned int i = 0; i < gpa_counter_context_hardware_info.gpa_hardware_attribute_count; i++)
        {
            const GpaHardwareAttribute gpa_hardware_attribute = gpa_counter_context_hardware_info.gpa_hardware_attributes[i];
            const GpaUInt32            attribute_val          = gpa_hardware_attribute.gpa_hardware_attribute_value;

            switch (gpa_hardware_attribute.gpa_hardware_attribute_type)
            {
            case kGpaHardwareAttributeNumShaderEngines:
                gpa_hw_info_.SetNumberShaderEngines(attribute_val);
                break;
            case kGpaHardwareAttributeNumShaderArrays:
                gpa_hw_info_.SetNumberShaderArrays(attribute_val);
                break;
            case kGpaHardwareAttributeNumSimds:
                gpa_hw_info_.SetNumberSimds(attribute_val);
                break;
            case kGpaHardwareAttributeNumComputeUnits:
                gpa_hw_info_.SetNumberCus(attribute_val);
                break;
            case kGpaHardwareAttributeTimestampFrequency:
                gpa_hw_info_.SetTimeStampFrequency(attribute_val);
                break;
            case kGpaHardwareAttributeNumRenderBackends:
            case kGpaHardwareAttributeClocksPerPrimitive:
            case kGpaHardwareAttributeNumPrimitivePipes:
            case kGpaHardwareAttributePeakVerticesPerClock:
            case kGpaHardwareAttributePeakPrimitivesPerClock:
            case kGpaHardwareAttributePeakPixelsPerClock:
                GPA_LOG_DEBUG_MESSAGE("Unused attributes");
            }
        }
    }
}

bool GpaCounterContextHandler::InitCounters()
{
    if (!initialized_)
    {
        if (gpa_hw_info_.UpdateDeviceInfoBasedOnDeviceId())
        {
            if (gpa_hw_info_.IsUnsupportedDeviceId())
            {
                return false;
            }

            GpaUInt32 vendorId;
            GpaUInt32 deviceId;
            GpaUInt32 revisionId;

            if (gpa_hw_info_.GetVendorId(vendorId) && gpa_hw_info_.GetDeviceId(deviceId) && gpa_hw_info_.GetRevisionId(revisionId))
            {
                const GpaStatus status = GenerateCounters(
                    gpa_api_type_,
                    sample_type_,
                    vendorId, deviceId, revisionId, gpa_open_context_flags_, &gpa_counter_accessor_, &gpa_counter_scheduler_);

                if (kGpaStatusOk == status)
                {
                    initialized_ = true;
                }
            }
        }
    }

    return initialized_;
}

const GpaHwInfo* GpaCounterContextHandler::GetHardwareInfo() const
{
    return &gpa_hw_info_;
}

const IGpaCounterAccessor* GpaCounterContextHandler::GetCounterAccessor() const
{
    if (initialized_)
    {
        return gpa_counter_accessor_;
    }

    return nullptr;
}

IGpaCounterScheduler* GpaCounterContextHandler::GetCounterScheduler() const
{
    if (initialized_)
    {
        return gpa_counter_scheduler_;
    }

    return nullptr;
}

_GpaCounterContext::_GpaCounterContext(GpaCounterContextHandler* gpa_counter_context)
    : gpa_counter_context_handler(gpa_counter_context)
{
}

GpaCounterContextHandler* _GpaCounterContext::operator->() const
{
    return gpa_counter_context_handler;
}

_GpaCounterContext::~_GpaCounterContext()
{
    gpa_counter_context_handler = nullptr;
}

GpaCounterContextManager* GpaCounterContextManager::Instance()
{
    if (nullptr == gpa_counter_context_manager_)
    {
        gpa_counter_context_manager_ = new (std::nothrow) GpaCounterContextManager();
    }

    return gpa_counter_context_manager_;
}

void GpaCounterContextManager::DeleteInstanceIfZero()
{
    if (gpa_counter_context_manager_->gpa_counter_context_map_.size() == 0)
    {
        DeleteInstance();
    }
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

GpaStatus GpaCounterContextManager::OpenCounterContext(const GpaApiType&                    api_type,
                                                       const GpaSessionSampleType           sample_type,
                                                       const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                                                       const GpaOpenContextFlags&           context_flags,
                                                       GpaCounterContext*                   gpa_counter_context)
{
    Init(api_type, sample_type);

    GpaCounterContextHandler* gpa_new_counter_context =
        new (std::nothrow) GpaCounterContextHandler(api_type,
            sample_type,
            gpa_counter_context_hardware_info, context_flags);

    if (nullptr != gpa_new_counter_context)
    {
        if (gpa_new_counter_context->InitCounters())
        {
            GpaCounterContext gpa_counter_context_ret = new (std::nothrow) _GpaCounterContext(gpa_new_counter_context);

            if (nullptr != gpa_counter_context_ret)
            {
                gpa_counter_context_map_.insert(std::pair<GpaCounterContext, GpaApiType>(gpa_counter_context_ret, api_type));
                *gpa_counter_context = gpa_counter_context_ret;
                return kGpaStatusOk;
            }

            *gpa_counter_context = nullptr;
            delete gpa_new_counter_context;
            return kGpaStatusErrorFailed;
        }

        delete gpa_new_counter_context;
        return kGpaStatusErrorHardwareNotSupported;
    }

    return kGpaStatusErrorFailed;
}

const IGpaCounterAccessor* GpaCounterContextManager::GetCounterAccessor(const GpaCounterContext gpa_counter_context)
{
    auto iter = gpa_counter_context_map_.find(gpa_counter_context);
    if (iter != gpa_counter_context_map_.end())
    {
        GpaCounterContext counter_context = iter->first;
        return (*counter_context)->GetCounterAccessor();
    }

    return nullptr;
}

IGpaCounterScheduler* GpaCounterContextManager::GetCounterScheduler(const GpaCounterContext gpa_counter_context)
{
    auto iter = gpa_counter_context_map_.find(gpa_counter_context);
    if (iter != gpa_counter_context_map_.end())
    {
        GpaCounterContext counter_context = iter->first;
        return (*counter_context)->GetCounterScheduler();
    }

    return nullptr;
}

GpaStatus GpaCounterContextManager::CloseCounterContext(const GpaCounterContext gpa_counter_context)
{
    auto iter = gpa_counter_context_map_.find(gpa_counter_context);
    if (iter != gpa_counter_context_map_.end())
    {
        GpaCounterContext counter_context = iter->first;
        delete counter_context->gpa_counter_context_handler;
        delete counter_context;
        counter_context = nullptr;
        gpa_counter_context_map_.erase(gpa_counter_context);
        return kGpaStatusOk;
    }

    return kGpaStatusErrorContextNotFound;
}

bool GpaCounterContextManager::IsCounterContextOpen(GpaCounterContext gpa_counter_context)
{
    if (gpa_counter_context_map_.find(gpa_counter_context) != gpa_counter_context_map_.end())
    {
        return true;
    }

    return false;
}

void GpaCounterContextManager::Init(const GpaApiType& api_type, const GpaSessionSampleType sample_type)
{
    if (gpa_counter_scheduler_map_.empty())
    {
        gpa_counter_scheduler_map_.insert(std::pair<GpaApiType, IGpaCounterScheduler*>(kGpaApiDirectx11, nullptr));
        gpa_counter_scheduler_map_.insert(std::pair<GpaApiType, IGpaCounterScheduler*>(kGpaApiDirectx12, nullptr));
        gpa_counter_scheduler_map_.insert(std::pair<GpaApiType, IGpaCounterScheduler*>(kGpaApiOpengl, nullptr));
        gpa_counter_scheduler_map_.insert(std::pair<GpaApiType, IGpaCounterScheduler*>(kGpaApiVulkan, nullptr));
    }

    if (gpa_counter_accessor_map_.empty())
    {
        gpa_counter_accessor_map_.insert(std::pair<GpaApiType, IGpaCounterAccessor*>(kGpaApiDirectx11, nullptr));
        gpa_counter_accessor_map_.insert(std::pair<GpaApiType, IGpaCounterAccessor*>(kGpaApiDirectx12, nullptr));
        gpa_counter_accessor_map_.insert(std::pair<GpaApiType, IGpaCounterAccessor*>(kGpaApiOpengl, nullptr));
        gpa_counter_accessor_map_.insert(std::pair<GpaApiType, IGpaCounterAccessor*>(kGpaApiVulkan, nullptr));
    }

    InitCounterAccessor(api_type, sample_type);
    InitCounterScheduler(api_type, sample_type);
}

void GpaCounterContextManager::InitCounterAccessor(const GpaApiType& api_type, const GpaSessionSampleType sample_type)
{
    if (nullptr != gpa_counter_accessor_map_[api_type])
    {
        return;
    }

    switch (api_type)
    {
    case kGpaApiDirectx11:
#ifdef ENABLE_GPA_DX11
        gpa_counter_accessor_map_[kGpaApiDirectx11] = new GpaCounterGeneratorDx11(sample_type);
#endif
        break;
    case kGpaApiDirectx12:
#ifdef ENABLE_GPA_DX12
        gpa_counter_accessor_map_[kGpaApiDirectx12] = new GpaCounterGeneratorDx12(sample_type);
#endif
        break;
    case kGpaApiOpengl:
#ifdef ENABLE_GPA_GL
        gpa_counter_accessor_map_[kGpaApiOpengl] = new GpaCounterGeneratorGl(sample_type);
#endif
        break;
    case kGpaApiVulkan:
#ifdef ENABLE_GPA_VK
        gpa_counter_accessor_map_[kGpaApiVulkan] = new GpaCounterGeneratorVk(sample_type);
#endif
        break;
    default:
        break;
    }
}

void GpaCounterContextManager::InitCounterScheduler(const GpaApiType& api_type, const GpaSessionSampleType sample_type)
{
    if (nullptr != gpa_counter_scheduler_map_[api_type])
    {
        return;
    }

    switch (api_type)
    {
    case kGpaApiDirectx11:
#ifdef ENABLE_GPA_DX11
        gpa_counter_scheduler_map_[kGpaApiDirectx11] = new GpaCounterSchedulerDx11(sample_type);
#endif
        break;
    case kGpaApiDirectx12:
#ifdef ENABLE_GPA_DX12
        gpa_counter_scheduler_map_[kGpaApiDirectx12] = new GpaCounterSchedulerDx12(sample_type);
#endif
        break;
    case kGpaApiOpengl:
#ifdef ENABLE_GPA_GL
        gpa_counter_scheduler_map_[kGpaApiOpengl] = new GpaCounterSchedulerGl(sample_type);
#endif
        break;
    case kGpaApiVulkan:
#ifdef ENABLE_GPA_VK
        gpa_counter_scheduler_map_[kGpaApiVulkan] = new GpaCounterSchedulerVk(sample_type);
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
        GpaCounterContext counter_context = iter->first;
        delete counter_context->gpa_counter_context_handler;
        delete counter_context;
    }
    gpa_counter_context_map_.clear();

    for (auto iter = gpa_counter_accessor_map_.begin(); iter != gpa_counter_accessor_map_.end(); ++iter)
    {
        IGpaCounterAccessor* counter_accessor = iter->second;
        delete counter_accessor;
    }
    gpa_counter_accessor_map_.clear();

    for (auto iter = gpa_counter_scheduler_map_.begin(); iter != gpa_counter_scheduler_map_.end(); ++iter)
    {
        IGpaCounterScheduler* counter_scheduler = iter->second;
        delete counter_scheduler;
    }
    gpa_counter_scheduler_map_.clear();
}
