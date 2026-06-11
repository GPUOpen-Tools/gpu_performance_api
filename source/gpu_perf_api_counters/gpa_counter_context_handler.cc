//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Implements Gpa counter context related functionality.
//==============================================================================

#include "gpa_counter_context_handler.h"

#include <memory>

#include "gpa_counter_generator_scheduler_manager.h"
#include "gpa_counter_generator.h"

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
            case kGpaHardwareAttributeNumWavesPerSimd:
                gpa_hw_info_.SetWavesPerSimd(attribute_val);
                break;
            case kGpaHardwareAttributeNumRenderBackends:
            case kGpaHardwareAttributeClocksPerPrimitive:
            case kGpaHardwareAttributeNumPrimitivePipes:
            case kGpaHardwareAttributePeakVerticesPerClock:
            case kGpaHardwareAttributePeakPrimitivesPerClock:
            case kGpaHardwareAttributePeakPixelsPerClock:
                GpaLogger::Instance().LogDebugMessage("Unused attributes");
            }
        }
    }
}

bool GpaCounterContextHandler::InitCounters(GpaDriverInfo const& driver_info)
{
    if (!initialized_)
    {
        if (gpa_hw_info_.IsUnsupportedDevice(gpa_api_type_, driver_info))
        {
            return false;
        }

        if (gpa_hw_info_.UpdateDeviceInfoBasedOnDeviceDescription())
        {
            // If this is SQTT, there's no counter scheduler or accessor.
            assert(sample_type_ != kGpaSessionSampleTypeSqtt);

            const GpaStatus status =
                GenerateCounters(gpa_api_type_, sample_type_, gpa_hw_info_, gpa_open_context_flags_, &gpa_counter_accessor_, &gpa_counter_scheduler_);

            assert(gpa_counter_accessor_ != nullptr);
            assert(gpa_counter_scheduler_ != nullptr);

            if (kGpaStatusOk == status)
            {
                initialized_ = true;
            }
        }
    }

    return initialized_;
}

const GpaHwInfo& GpaCounterContextHandler::GetHardwareInfo() const
{
    return gpa_hw_info_;
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

_GpaCounterContext::_GpaCounterContext(std::unique_ptr<GpaCounterContextHandler> gpa_counter_context)
    : gpa_counter_context_handler(std::move(gpa_counter_context))
{
}

GpaCounterContextHandler* _GpaCounterContext::operator->() const
{
    return gpa_counter_context_handler.get();
}

GpaCounterContextManager& GpaCounterContextManager::Instance()
{
    static GpaCounterContextManager instance;
    return instance;
}

GpaStatus GpaCounterContextManager::OpenCounterContext(const GpaApiType&                    api_type,
                                                       const GpaSessionSampleType           sample_type,
                                                       const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                                                       const GpaOpenContextFlags&           context_flags,
                                                       GpaCounterContext*                   gpa_counter_context,
                                                       GpaDriverInfo const&                 driver_info)
{
    Init(api_type, sample_type);

    auto gpa_new_counter_context = std::make_unique<GpaCounterContextHandler>(api_type, sample_type, gpa_counter_context_hardware_info, context_flags);

    if (gpa_new_counter_context->InitCounters(driver_info))
    {
        auto              gpa_counter_context_struct = std::make_unique<_GpaCounterContext>(std::move(gpa_new_counter_context));
        GpaCounterContext raw_context                = gpa_counter_context_struct.get();
        gpa_counter_context_map_.emplace(raw_context, CounterContextEntry{std::move(gpa_counter_context_struct), api_type});
        *gpa_counter_context = raw_context;
        return kGpaStatusOk;
    }

    return kGpaStatusErrorHardwareNotSupported;
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
        // Erasing from the map destroys the owned unique_ptr, which destroys the counter context.
        gpa_counter_context_map_.erase(iter);
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
    InitCounterAccessor(api_type, sample_type);
    InitCounterScheduler(api_type, sample_type);
}

void GpaCounterContextManager::InitCounterAccessor(const GpaApiType& api_type, const GpaSessionSampleType sample_type)
{
    if (auto sample_iter = gpa_counter_accessor_map_.find(sample_type); sample_iter != gpa_counter_accessor_map_.end())
    {
        if (auto api_iter = sample_iter->second.find(api_type); api_iter != sample_iter->second.end() && api_iter->second != nullptr)
        {
            return;
        }
    }

    switch (api_type)
    {
    case kGpaApiDirectx11:
#ifdef ENABLE_GPA_DX11
        gpa_counter_accessor_map_[sample_type][kGpaApiDirectx11] = std::make_unique<GpaCounterGeneratorDx11>(sample_type);
#endif
        break;
    case kGpaApiDirectx12:
#ifdef ENABLE_GPA_DX12
        gpa_counter_accessor_map_[sample_type][kGpaApiDirectx12] = std::make_unique<GpaCounterGeneratorDx12>(sample_type);
#endif
        break;
    case kGpaApiOpengl:
#ifdef ENABLE_GPA_GL
        gpa_counter_accessor_map_[sample_type][kGpaApiOpengl] = std::make_unique<GpaCounterGeneratorGl>(sample_type);
#endif
        break;
    case kGpaApiVulkan:
#ifdef ENABLE_GPA_VK
        gpa_counter_accessor_map_[sample_type][kGpaApiVulkan] = std::make_unique<GpaCounterGeneratorVk>(sample_type);
#endif
        break;
    default:
        break;
    }
}

void GpaCounterContextManager::InitCounterScheduler(const GpaApiType& api_type, const GpaSessionSampleType sample_type)
{
    if (auto sample_iter = gpa_counter_scheduler_map_.find(sample_type); sample_iter != gpa_counter_scheduler_map_.end())
    {
        if (auto api_iter = sample_iter->second.find(api_type); api_iter != sample_iter->second.end() && api_iter->second != nullptr)
        {
            return;
        }
    }

    switch (api_type)
    {
    case kGpaApiDirectx11:
#ifdef ENABLE_GPA_DX11
        gpa_counter_scheduler_map_[sample_type][kGpaApiDirectx11] = std::make_unique<GpaCounterSchedulerDx11>(sample_type);
#endif
        break;
    case kGpaApiDirectx12:
#ifdef ENABLE_GPA_DX12
        gpa_counter_scheduler_map_[sample_type][kGpaApiDirectx12] = std::make_unique<GpaCounterSchedulerDx12>(sample_type);
#endif
        break;
    case kGpaApiOpengl:
#ifdef ENABLE_GPA_GL
        gpa_counter_scheduler_map_[sample_type][kGpaApiOpengl] = std::make_unique<GpaCounterSchedulerGl>(sample_type);
#endif
        break;
    case kGpaApiVulkan:
#ifdef ENABLE_GPA_VK
        gpa_counter_scheduler_map_[sample_type][kGpaApiVulkan] = std::make_unique<GpaCounterSchedulerVk>(sample_type);
#endif
        break;
    default:
        break;
    }
}
