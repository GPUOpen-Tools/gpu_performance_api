//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief A base-class implementation of the GPA Session interface.
//==============================================================================

#include "gpu_perf_api_common/gpa_session.h"

#include <chrono>
#include <thread>
#include <variant>

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter_group_accessor.h"
#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"
#include "gpu_perf_api_counter_generator/gpa_split_counters_interfaces.h"

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/gpa_context_counter_mediator.h"
#include "gpu_perf_api_common/gpa_pass.h"
#include "gpu_perf_api_common/gpa_unique_object.h"

/// Default SPM sampling interval (4096 clock cycles) (estimate).
static const GpaUInt32 kDefaultSpmInterval = 4096;

/// Default SPM memory limit size (16 MB) (estimate).
static const GpaUInt64 kDefaultSpmMemoryLimit = 16 * 1024 * 1024;

/// Default SQTT memory limit size (80 MB) -- will likely need to be larger (512MB) if instruction-level trace is performed (estimate).
static const GpaUInt64 kDefaultSqttMemoryLimit = 80 * 1024 * 1024;

GpaSession::GpaSession(IGpaContext* parent_context, GpaSessionSampleType sample_type)
    : gpa_session_state_(kGpaSessionStateNotStarted)
    , parent_context_(parent_context)
    , max_pass_index_(0u)
    , sample_type_(sample_type)
    , spm_interval_(kDefaultSpmInterval)
    , spm_memory_limit_(kDefaultSpmMemoryLimit)
    , sqtt_instruction_mask_(kGpaSqttInstructionTypeNone)
    , sqtt_compute_unit_id_(0)
    , sqtt_memory_limit_(kDefaultSqttMemoryLimit)
    , pass_required_(0u)
    , counter_set_changed_(false)
    , context_flags_(parent_context->GetContextFlags())
{
    TRACE_PRIVATE_FUNCTION(GpaSession::CONSTRUCTOR);

    OpenCounters();
}

GpaSession::~GpaSession()
{
    TRACE_PRIVATE_FUNCTION(GpaSession::DESTRUCTOR);

    std::lock_guard<std::mutex> lock_resources(gpa_session_mutex_);

    // Clean up the passes.
    for (auto pass_iter = passes_.begin(); pass_iter != passes_.end(); ++pass_iter)
    {
        const GpaCommandLists pass_cmd_list = (*pass_iter)->GetCmdList();

        for (auto cmd_list_iter = pass_cmd_list.cbegin(); cmd_list_iter != pass_cmd_list.cend(); ++cmd_list_iter)
        {
            GpaUniqueObjectManager::Instance()->DeleteObject(*cmd_list_iter);
        }

        delete *pass_iter;
    }

    passes_.clear();

    GpaContextCounterMediator::Instance()->RemoveContext(this);
}

GpaObjectType GpaSession::ObjectType() const
{
    return GpaObjectType::kGpaObjectTypeSession;
}

IGpaContext* GpaSession::GetParentContext() const
{
    return parent_context_;
}

GpaSessionState GpaSession::GetState() const
{
    return gpa_session_state_;
}

bool GpaSession::OpenCounters()
{
    bool success = (kGpaStatusOk == GpaContextCounterMediator::Instance()->GenerateCounters(this, context_flags_));
    return success;
}

GpaStatus GpaSession::GetNumCounters(GpaUInt32* counter_count) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_count);
    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_count = counter_accessor->GetNumCounters();
    return kGpaStatusOk;
}

GpaStatus GpaSession::GetCounterName(GpaUInt32 index, const char** counter_name) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_name);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_name = counter_accessor->GetCounterName(index);
    return kGpaStatusOk;
}

GpaStatus GpaSession::GetCounterGroup(GpaUInt32 index, const char** counter_group) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_group);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_group = counter_accessor->GetCounterGroup(index);
    return kGpaStatusOk;
}

GpaStatus GpaSession::GetCounterDescription(GpaUInt32 index, const char** counter_description) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_description);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_description = counter_accessor->GetCounterDescription(index);
    return kGpaStatusOk;
}

GpaStatus GpaSession::GetCounterDataType(GpaUInt32 index, GpaDataType* counter_data_type) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_data_type);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_data_type = counter_accessor->GetCounterDataType(index);
    return kGpaStatusOk;
}

GpaStatus GpaSession::GetCounterUsageType(GpaUInt32 index, GpaUsageType* counter_usage_type) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_usage_type);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_usage_type = counter_accessor->GetCounterUsageType(index);
    return kGpaStatusOk;
}

GpaStatus GpaSession::GetCounterUuid(GpaUInt32 index, GpaUuid* counter_uuid) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_uuid);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_uuid = counter_accessor->GetCounterUuid(index);
    return kGpaStatusOk;
}

GpaStatus GpaSession::GetCounterSampleType(GpaUInt32 index, GpaCounterSampleType* counter_sample_type) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_sample_type);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_sample_type = counter_accessor->GetCounterSampleType(index);
    return kGpaStatusOk;
}

GpaStatus GpaSession::GetCounterIndex(const char* counter_name, GpaUInt32* counter_index) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_index);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    return counter_accessor->GetCounterIndex(counter_name, counter_index) ? kGpaStatusOk : kGpaStatusErrorFailed;
}

bool GpaSession::GetCounterSourceLocalIndex(GpaUInt32 exposed_counter_index, GpaCounterSource* counter_source, GpaUInt32* source_local_index) const
{
    assert(nullptr != counter_source);
    assert(nullptr != source_local_index);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);
    assert(nullptr != counter_accessor);

    GpaCounterSourceInfo info = counter_accessor->GetCounterSourceInfo(exposed_counter_index);

    bool isValid = (GpaCounterSource::kUnknown != info.counter_source);

    if (isValid)
    {
        *counter_source     = info.counter_source;
        *source_local_index = info.local_counter_index;
    }

    return isValid;
}

GpaCounterSource GpaSession::GetCounterSource(GpaUInt32 internal_counter_index) const
{
    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);
    GpaCounterSource     source           = GpaCounterSource::kUnknown;

    if (nullptr != counter_accessor)
    {
        const GpaHardwareCounters& hardware_counters = counter_accessor->GetHardwareCounters();

        GpaCounterGroupAccessor counter_group_accessor(hardware_counters.internal_counter_groups_,
                                                       static_cast<unsigned int>(hardware_counters.internal_counter_groups_.size()),
                                                       hardware_counters.additional_groups_,
                                                       hardware_counters.additional_group_count_);

        counter_group_accessor.SetCounterIndex(internal_counter_index);

        if (counter_group_accessor.IsHwCounter())
        {
            source = GpaCounterSource::kHardware;
        }
    }

    return source;
}

GpaStatus GpaSession::EnableCounter(GpaUInt32 index)
{
    if (!GpaContextCounterMediator::Instance()->IsCounterSchedulingSupported(this))
    {
        return kGpaStatusErrorFailed;
    }

    if (kGpaSessionSampleTypeDiscreteCounter != sample_type_ && kGpaSessionSampleTypeStreamingCounter != sample_type_ &&
        kGpaSessionSampleTypeStreamingCounterAndSqtt != sample_type_)
    {
        GPA_LOG_ERROR("Unable to enable counter. Session was not created with a GpaSessionSampleType value that supports counter collection.");
        return kGpaStatusErrorIncompatibleSampleTypes;
    }

    if (IsSessionRunning())
    {
        return kGpaStatusErrorSessionAlreadyStarted;
    }

    SessionCounters::const_iterator counter_iter = std::find(session_counters_.cbegin(), session_counters_.cend(), index);

    if (counter_iter != session_counters_.end())
    {
        return kGpaStatusErrorAlreadyEnabled;
    }

    GpaStatus status = kGpaStatusOk;

    if (((kGpaSessionSampleTypeStreamingCounter == sample_type_) || (kGpaSessionSampleTypeStreamingCounterAndSqtt == sample_type_)))
    {
        // If we're sampling streaming counters, then only enable the counter if the set of counters remains single-pass.
        unsigned int num_passes = 0;
        status                  = GpaContextCounterMediator::Instance()->GetRequiredPassCount(this, session_counters_, num_passes);

        if (kGpaStatusOk == status)
        {
            if (1 < num_passes)
            {
                GPA_LOG_ERROR("Unable to enable counter. Multi-pass counter sets not supported for streaming counters.");
                status = kGpaStatusErrorNotEnabled;
            }
        }
    }

    std::lock_guard<std::mutex> lock(session_counters_mutex_);
    session_counters_.push_back(index);
    counter_set_changed_ = true;
    return status;
}

GpaStatus GpaSession::DisableCounter(GpaUInt32 index)
{
    if (!GpaContextCounterMediator::Instance()->IsCounterSchedulingSupported(this))
    {
        return kGpaStatusErrorFailed;
    }

    if (IsSessionRunning())
    {
        return kGpaStatusErrorSessionAlreadyStarted;
    }

    // There is a bug in gcc-4.8.2 of usage of const_iterators in std::vector::erase().
    SessionCounters::iterator counter_iter = std::find(session_counters_.begin(), session_counters_.end(), index);

    if (counter_iter == session_counters_.cend())
    {
        return kGpaStatusErrorNotEnabled;
    }

    std::lock_guard<std::mutex> lock(session_counters_mutex_);
    session_counters_.erase(counter_iter);
    counter_set_changed_ = true;
    return kGpaStatusOk;
}

GpaStatus GpaSession::DisableAllCounters()
{
    if (!GpaContextCounterMediator::Instance()->IsCounterSchedulingSupported(this))
    {
        return kGpaStatusErrorFailed;
    }

    std::lock_guard<std::mutex> lock(session_counters_mutex_);
    session_counters_.clear();
    counter_set_changed_ = true;
    return kGpaStatusOk;
}

GpaStatus GpaSession::GetNumEnabledCounters(GpaUInt32* counter_count) const
{
    if (nullptr == counter_count)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaContextCounterMediator::Instance()->IsCounterSchedulingSupported(this))
    {
        return kGpaStatusErrorFailed;
    }

    *counter_count = static_cast<GpaUInt32>(session_counters_.size());
    return kGpaStatusOk;
}

GpaStatus GpaSession::GetEnabledIndex(GpaUInt32 enabled_number, GpaUInt32* enabled_counter_index) const
{
    if (!GpaContextCounterMediator::Instance()->IsCounterSchedulingSupported(this))
    {
        return kGpaStatusErrorFailed;
    }

    if (enabled_number >= session_counters_.size())
    {
        return kGpaStatusErrorIndexOutOfRange;
    }

    unsigned int counter_index = 0u;

    for (SessionCounters::const_iterator it = session_counters_.cbegin(); it != session_counters_.cend(); ++it)
    {
        if (counter_index == enabled_number)
        {
            *enabled_counter_index = *it;
            break;
        }

        ++counter_index;
    }

    return kGpaStatusOk;
}

GpaStatus GpaSession::IsCounterEnabled(GpaUInt32 counter_index) const
{
    if (!GpaContextCounterMediator::Instance()->IsCounterSchedulingSupported(this))
    {
        return kGpaStatusErrorFailed;
    }

    SessionCounters::const_iterator counter_iter = std::find(session_counters_.cbegin(), session_counters_.cend(), counter_index);

    if (counter_iter == session_counters_.cend())
    {
        return kGpaStatusErrorCounterNotFound;
    }

    return kGpaStatusOk;
}

GpaStatus GpaSession::GetNumRequiredPasses(GpaUInt32* num_passes)
{
    if (kGpaSessionSampleTypeSqtt == sample_type_)
    {
        if (nullptr != num_passes)
        {
            *num_passes = 1;
            return kGpaStatusOk;
        }
        else
        {
            return kGpaStatusErrorNullPointer;
        }
    }

    GpaStatus ret_status = kGpaStatusOk;

    if (!counter_set_changed_)
    {
        *num_passes = pass_required_;
    }
    else
    {
        if (!GpaContextCounterMediator::Instance()->IsCounterSchedulingSupported(this))
        {
            return kGpaStatusErrorFailed;
        }

        unsigned int pass_req = 0u;

        ret_status = GpaContextCounterMediator::Instance()->GetRequiredPassCount(this, session_counters_, pass_req);

        if (kGpaStatusOk == ret_status)
        {
            pass_required_       = pass_req;
            *num_passes          = pass_req;
            counter_set_changed_ = false;
        }

        if (kGpaSessionSampleTypeStreamingCounter == sample_type_ && *num_passes > 1)
        {
            GPA_LOG_ERROR("Streaming counters must complete in a single pass.");
            ret_status = kGpaStatusErrorFailed;
        }
    }

    return ret_status;
}

GpaStatus GpaSession::Begin()
{
    GpaStatus status = kGpaStatusOk;

    if (kGpaSessionStateStarted <= gpa_session_state_)
    {
        GPA_LOG_ERROR("Session has already been started.");
        status = kGpaStatusErrorSessionAlreadyStarted;
    }
    else if (kGpaSessionSampleTypeDiscreteCounter == sample_type_ || kGpaSessionSampleTypeStreamingCounter == sample_type_ ||
             kGpaSessionSampleTypeStreamingCounterAndSqtt == sample_type_)
    {
        // Verify that at least one counter is enabled.
        if (session_counters_.empty())
        {
            GPA_LOG_ERROR("The session can't be started without any enabled counters.");
            status = kGpaStatusErrorNoCountersEnabled;
        }

        // If so, we will then check how many passes are required and pre-create passes for the Session.
        if (kGpaStatusOk == status && GpaContextCounterMediator::Instance()->IsCounterSchedulingSupported(this))
        {
            status = GpaContextCounterMediator::Instance()->ScheduleCounters(this, session_counters_);
            if (kGpaStatusOk == status)
            {
                unsigned int pass_count = 0u;

                if (!counter_set_changed_)
                {
                    pass_count = static_cast<unsigned int>(pass_required_);
                }
                else
                {
                    status = GpaContextCounterMediator::Instance()->GetRequiredPassCount(this, session_counters_, pass_count);
                }

                if (kGpaSessionSampleTypeStreamingCounterAndSqtt == sample_type_ && pass_count != 1)
                {
                    GPA_LOG_ERROR("Unable to create pass for session. Sqtt + Spm sessions should only have 1 pass");
                    status = kGpaStatusErrorFailed;
                }

                if (kGpaStatusOk == status)
                {
                    // Assume the loop below will succeed, it will get set to false if the loop fails.
                    bool success = true;

                    for (GpaUInt32 pass_index_iter = 0; pass_index_iter < pass_count && success; pass_index_iter++)
                    {
                        CounterList* pass_counter_list = GpaContextCounterMediator::Instance()->GetCounterForPass(this, pass_index_iter);
                        CounterList  temp_counter_list = *pass_counter_list;
                        pass_counters_map_.insert(PassCountersPair(pass_index_iter, temp_counter_list));

                        GpaPass* current_pass = CreateApiPass(pass_index_iter);

                        if (nullptr != current_pass)
                        {
                            passes_.push_back(current_pass);
                        }
                        else
                        {
                            // Unable to create API specific pass object.
                            success = false;
                            break;
                        }
                    }

                    if (!success)
                    {
                        GPA_LOG_ERROR("Unable to create passes for the session.");
                        status = kGpaStatusErrorFailed;
                    }
                    else
                    {
                        status = kGpaStatusOk;
                    }
                }
                else
                {
                    GPA_LOG_ERROR("The session failed to get the number of required passes.");
                    status = kGpaStatusErrorFailed;
                }
            }
        }
    }
    else if (kGpaSessionSampleTypeSqtt == sample_type_)
    {
        //create one pass for Sqtt data
        GpaPass* current_pass = CreateApiPass(0);

        if (nullptr != current_pass)
        {
            passes_.push_back(current_pass);
        }
        else
        {
            // Unable to create API specific pass object
            GPA_LOG_ERROR("Unable to create passes for session.");
            status = kGpaStatusErrorFailed;
        }
    }
    else
    {
        GPA_LOG_ERROR("Unknown session type.");
        status = kGpaStatusErrorFailed;
    }

    // If we can successfully start the session, then mark the session as started.
    if (kGpaStatusOk == status)
    {
        std::lock_guard<std::mutex> lock_resources(gpa_session_mutex_);
        gpa_session_state_ = kGpaSessionStateStarted;
    }

    return status;
}

GpaStatus GpaSession::End()
{
    GpaStatus status = kGpaStatusErrorFailed;

    if (kGpaSessionStateStarted == gpa_session_state_)
    {
        std::lock_guard<std::mutex> lock_resources(gpa_session_mutex_);

        // Check whether that sufficient command list have been created for all passes.
        if (max_pass_index_ == passes_.size() - 1)
        {
            if (CheckWhetherPassesAreFinishedAndConsistent())
            {
                gpa_session_state_ = kGpaSessionStateEndedPendingResults;
                status             = kGpaStatusOk;
            }
            else
            {
                GPA_LOG_ERROR("Some passes have an incorrect number of samples.");
                status = kGpaStatusErrorVariableNumberOfSamplesInPasses;
            }
        }
        else
        {
            GPA_LOG_ERROR("Not all passes have been executed.");
            status = kGpaStatusErrorNotEnoughPasses;
        }
    }
    else
    {
        GPA_LOG_ERROR("Session has not been started.");
        status = kGpaStatusErrorSessionNotStarted;
    }

    if (kGpaStatusOk == status)
    {
        if (kGpaStatusOk == status && !GatherCounterResultLocations())
        {
            status = kGpaStatusErrorFailed;
        }

        // SQTT does not use counters.
        if (kGpaSessionSampleTypeSqtt != sample_type_)
        {
            status = GpaContextCounterMediator::Instance()->UnscheduleCounters(this, session_counters_);
        }
    }

    return status;
}

GpaStatus GpaSession::Reset()
{
    GpaStatus status = kGpaStatusOk;

    {
        std::lock_guard<std::mutex> lockResources(gpa_session_mutex_);
        gpa_session_state_ = kGpaSessionStateNotStarted;

        DisableAllCounters();
        counter_result_locations_.clear();
        passes_.clear();
        max_pass_index_ = 0;
        pass_counters_map_.clear();
    }

    return status;
}

GpaCommandListId GpaSession::CreateCommandList(GpaUInt32 pass_index, void* cmd_list, GpaCommandListType cmd_type)
{
    GpaCommandListId ret_cmd_id = nullptr;

    // Validate:
    // 1. pass_index is less than the number of passes required.
    // 2. Check for valid command list.

    std::lock_guard<std::mutex> lock_resources(gpa_session_mutex_);

    if (pass_index < passes_.size())
    {
        GpaPass* tmp_pass = passes_[pass_index];

        if (nullptr != tmp_pass)
        {
            IGpaCommandList* gpa_cmd = tmp_pass->CreateCommandList(cmd_list, cmd_type);

            if (nullptr != gpa_cmd)
            {
                ret_cmd_id = reinterpret_cast<GpaCommandListId>(GpaUniqueObjectManager::Instance()->CreateObject(gpa_cmd));
            }
        }

        if (pass_index > max_pass_index_)
        {
            max_pass_index_ = pass_index;
        }
    }
    else
    {
        GPA_LOG_ERROR("Invalid pass index.");
    }

    return ret_cmd_id;
}

GpaUInt32 GpaSession::GetSampleCount() const
{
    TRACE_PRIVATE_FUNCTION(GpaSession::GetSampleCount);

    GpaUInt32 sample_count = 0;

    std::lock_guard<std::mutex> lock_resources(gpa_session_mutex_);

    // Make sure there is at least one request.
    if (!passes_.empty())
    {
        sample_count = static_cast<GpaUInt32>(passes_[0]->GetSampleCount());
    }

    return sample_count;
}

bool GpaSession::GetSampleIdByIndex(SampleIndex sample_index, ClientSampleId& client_sample_id) const
{
    TRACE_PRIVATE_FUNCTION(GpaSession::GetSampleIdByIndex);

    std::lock_guard<std::mutex> lock_resources(gpa_session_mutex_);

    // Make sure there is at least one request.
    if (!passes_.empty())
    {
        return passes_[0]->GetSampleIdByIndex(sample_index, client_sample_id);
    }

    return false;
}

bool GpaSession::DoesCommandListExist(GpaUInt32 pass_index, GpaCommandListId gpa_command_list_id) const
{
    bool exists = false;

    if (nullptr != gpa_command_list_id)
    {
        std::lock_guard<std::mutex> lock_resources(gpa_session_mutex_);

        if (pass_index < passes_.size())
        {
            GpaPass* tmp_pass = passes_[pass_index];

            if (nullptr != tmp_pass)
            {
                exists = tmp_pass->DoesCommandListExist(gpa_command_list_id->Object());
            }
        }
        else
        {
            GPA_LOG_ERROR("Invalid pass index.");
        }
    }

    return exists;
}

bool GpaSession::DoesSampleExist(GpaUInt32 sample_id) const
{
    bool ret_val = false;

    if (!passes_.empty())
    {
        ret_val = passes_[0]->DoesSampleExist(sample_id);
    }

    return ret_val;
}

bool GpaSession::UpdateResults()
{
    bool are_all_passes_complete = true;

    for (PassInfo::iterator pass_iter = passes_.begin(); pass_iter != passes_.end(); ++pass_iter)
    {
        are_all_passes_complete &= UpdateResults((*pass_iter)->GetIndex());

        if (!are_all_passes_complete)
        {
            GPA_LOG_DEBUG_MESSAGE("Pass is not complete.");
        }
    }

    if (are_all_passes_complete)
    {
        gpa_session_state_ = kGpaSessionStateResultCollected;
    }

    return are_all_passes_complete;
}

bool GpaSession::UpdateResults(GpaUInt32 pass_index)
{
    bool success = false;

    if (pass_index <= max_pass_index_)
    {
        std::lock_guard<std::mutex> lock_resources(gpa_session_mutex_);
        success = passes_.at(pass_index)->IsResultCollected();

        if (!success)
        {
            success = kGpaStatusOk == passes_.at(pass_index)->IsComplete();

            if (success)
            {
                success = passes_.at(pass_index)->IsResultReady();

                if (success)
                {
                    success = passes_.at(pass_index)->UpdateResults();
                }
            }
            else
            {
                GPA_LOG_ERROR("Some samples in the pass have not finished.");
            }
        }
    }
    else
    {
        GPA_LOG_ERROR("Incorrect pass index.");
    }

    return success;
}

bool GpaSession::IsSessionRunning() const
{
    return kGpaSessionStateStarted == gpa_session_state_;
}

GpaStatus GpaSession::IsPassComplete(GpaUInt32 pass_index) const
{
    GpaStatus ret_status = kGpaStatusErrorIndexOutOfRange;

    if (pass_index < passes_.size() && pass_index <= max_pass_index_)
    {
        ret_status = passes_[pass_index]->IsComplete();
    }

    return ret_status;
}

bool GpaSession::IsResultReady() const
{
    TRACE_PRIVATE_FUNCTION(GpaSession::IsResultReady);
    return kGpaSessionStateResultCollected == gpa_session_state_;
}

size_t GpaSession::GetSampleResultSizeInBytes(GpaUInt32 sample_id) const
{
    size_t size_in_bytes = 0;

    if (!GpaContextCounterMediator::Instance()->IsCounterSchedulingSupported(this))
    {
        GPA_LOG_ERROR("Unable to GetSampleResultSizeInBytes, counter scheduler is invalid.");
    }
    else if (kGpaSessionSampleTypeDiscreteCounter == sample_type_)
    {
        GpaUInt32 enable_counters = 0u;
        GetNumEnabledCounters(&enable_counters);
        size_in_bytes = sizeof(GpaUInt64) * enable_counters;
    }

    else if (kGpaSessionSampleTypeSqtt == sample_type_ || kGpaSessionSampleTypeStreamingCounter == sample_type_)
    {
        GpaSample* first_pass_sample = passes_[0]->GetSampleById(sample_id);
        size_in_bytes                = first_pass_sample->GetSampleResultLocation()->GetBufferBytes();
    }
    else
    {
        UNREFERENCED_PARAMETER(sample_id);
    }

    assert(size_in_bytes);

    return size_in_bytes;
}

GpaStatus GpaSession::GetSampleResult(GpaUInt32 sample_id, size_t sample_result_size_in_bytes, void* counter_sample_results)
{
    TRACE_PRIVATE_FUNCTION(GpaSession::GetSampleResult);

    if (sample_result_size_in_bytes < GetSampleResultSizeInBytes(sample_id))
    {
        GPA_LOG_ERROR("The value of sample_result_size_in_bytes indicates that the buffer is too small to contain the results.");
        return kGpaStatusErrorReadingSampleResult;
    }

    if (nullptr == counter_sample_results)
    {
        GPA_LOG_ERROR("counter_sample_results is NULL in GpaSession::GetSampleResult.");
        return kGpaStatusErrorNullPointer;
    }

    // It is not allowed to get sample results from a sample that was done on a secondary command list.
    // The app MUST call GpaCopySecondarySamples() and supply new unique sampleIds, then they may get
    // the results from those copied samples.
    // NOTE: All the passes should have the same SampleIds, so it's safe for us to simply use pass 0 to
    // test for the sample being secondary and/or copied.
    GpaSample* first_pass_sample = passes_[0]->GetSampleById(sample_id);

    if (nullptr != first_pass_sample && first_pass_sample->IsSecondary() && !first_pass_sample->IsCopied())
    {
        GPA_LOG_ERROR("Results cannot be queried from secondary samples.");
        return kGpaStatusErrorSampleInSecondaryCommandList;
    }

    const uint32_t kTimeout = 5 * 1000;  // 5 second timeout.

    if (!Flush(kTimeout))
    {
        GPA_LOG_ERROR("Failed to retrieve sample data due to timeout.");
        return kGpaStatusErrorTimeout;
    }

    // For each counter:
    // Get the internal counter result locations that are needed.
    // Get the necessary results from each pass.
    // Plug them into the counter equation.
    // Put the result in the appropriate spot in the supplied buffer.

    GpaUInt32 num_enabled = 0;
    GetNumEnabledCounters(&num_enabled);

    if (0 == num_enabled || sample_type_ == kGpaSessionSampleTypeStreamingCounter)
    {
        // this is a trace sample
        // using first_pass_sample is not right here......
        memcpy(counter_sample_results, first_pass_sample->GetSampleResultLocation()->GetAsTraceSampleResult()->GetResultBuffer(), sample_result_size_in_bytes);
        return kGpaStatusOk;
    }

    GpaStatus status = kGpaStatusOk;

    for (GpaUInt32 counter_index_iter = 0; counter_index_iter < num_enabled; counter_index_iter++)
    {
        GpaUInt32 exposed_counter_index;

        if (kGpaStatusOk != GetEnabledIndex(counter_index_iter, &exposed_counter_index))
        {
            GPA_LOG_ERROR("Invalid counter found while identifying enabled counter.");
            return kGpaStatusErrorIndexOutOfRange;
        }

        const std::variant<gpa_array_view<GpaUInt32>, GpaUInt32> internal_counters_required =
            GpaContextCounterMediator::Instance()->GetCounterAccessor(this)->GetInternalCountersRequired(exposed_counter_index);
        CounterResultLocationMap result_locations = counter_result_locations_[exposed_counter_index];

        GpaUInt32        source_local_index = 0;
        GpaCounterSource source             = GpaCounterSource::kUnknown;

        if (!GetCounterSourceLocalIndex(exposed_counter_index, &source, &source_local_index))
        {
            GPA_LOG_ERROR("Invalid counter index found while identifying counter source.");
            return kGpaStatusErrorIndexOutOfRange;
        }

        IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

        switch (source)
        {
        case GpaCounterSource::kPublic:
        {
            constexpr uint32_t              kCounterSourcePublic      = static_cast<uint32_t>(GpaCounterSource::kPublic);
            const gpa_array_view<GpaUInt32> require_hardware_counters = std::get<kCounterSourcePublic>(internal_counters_required);
            const size_t                    required_count            = require_hardware_counters.size();

            std::vector<GpaUInt64> results(required_count);

            unsigned int result_index = 0;

            for (const GpaUInt32 counter : require_hardware_counters)
            {
                GpaUInt64* result_buffer = &(results[result_index]);
                ++result_index;

                std::map<unsigned int, GpaCounterResultLocation>::iterator result_location_iter = result_locations.find(counter);

                if (result_location_iter == result_locations.end())
                {
                    GPA_LOG_ERROR("Could not find required counter among the results.");
                    return kGpaStatusErrorReadingSampleResult;
                }

                status = passes_[result_location_iter->second.pass_index_]->GetResult(sample_id, counter, result_buffer);

                if (kGpaStatusOk != status)
                {
                    return status;
                }

            }

            // The code below is only valid while the only data types supported are Float64 and Uint64
            static_assert(kGpaDataTypeLast == 2);

            // Since GpaUInt64 and GpaFloat64 are the same size it doesn't matter which type we use to increment the pointer.
            void* result = reinterpret_cast<GpaUInt64*>(counter_sample_results) + counter_index_iter;

            status = counter_accessor->ComputePublicCounterValue(source_local_index, results, result, parent_context_->GetHwInfo());

            break;
        }

        case GpaCounterSource::kHardware:
        {
            constexpr uint32_t kCounterSourceHardware = static_cast<uint32_t>(GpaCounterSource::kHardware);
            const GpaUInt32    hardware_counter       = std::get<kCounterSourceHardware>(internal_counters_required);
            GpaUInt64* const   uint64_results         = reinterpret_cast<GpaUInt64*>(counter_sample_results) + counter_index_iter;
            const GpaUInt16    counter_result_pass    = result_locations[hardware_counter].pass_index_;
            status                                    = passes_[counter_result_pass]->GetResult(sample_id, hardware_counter, uint64_results);
            break;
        }

        case GpaCounterSource::kUnknown:
            // Handled above.
            break;

        default:
            status = kGpaStatusErrorFailed;
            GPA_LOG_ERROR("Unknown counter source type.");
            assert(0);
            break;
        }

        if (status != kGpaStatusOk)
        {
            break;
        }
    }

    return status;
}

GpaSessionSampleType GpaSession::GetSampleType() const
{
    return sample_type_;
}

GpaUInt32 GpaSession::GetSpmInterval() const
{
    return spm_interval_;
}

void GpaSession::SetSpmInterval(GpaUInt32 interval)
{
    spm_interval_ = interval;
}

GpaUInt64 GpaSession::GetSpmMemoryLimit() const
{
    return spm_memory_limit_;
}

void GpaSession::SetSpmMemoryLimit(GpaUInt64 memory_limit)
{
    spm_memory_limit_ = memory_limit;
}

GpaSqttInstructionFlags GpaSession::GetSqttInstructionMask() const
{
    return sqtt_instruction_mask_;
}

void GpaSession::SetSqttInstructionMask(GpaSqttInstructionFlags sqtt_instruction_mask)
{
    sqtt_instruction_mask_ = sqtt_instruction_mask;
}

GpaUInt32 GpaSession::GetSqttComputeUnitId() const
{
    return sqtt_compute_unit_id_;
}

void GpaSession::SetSqttComputeUnitId(GpaUInt32 sqtt_compute_unit_id)
{
    sqtt_compute_unit_id_ = sqtt_compute_unit_id;
}

GpaUInt64 GpaSession::GetSqttMemoryLimit() const
{
    return sqtt_memory_limit_;
}

void GpaSession::SetSqttMemoryLimit(GpaUInt64 memory_limit)
{
    sqtt_memory_limit_ = memory_limit;
}

GpaStatus GpaSession::SqttBegin(void* command_list)
{
    UNREFERENCED_PARAMETER(command_list);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SqttEnd(void* command_list)
{
    UNREFERENCED_PARAMETER(command_list);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SqttGetSampleResultSize(size_t* sample_result_size_in_bytes)
{
    UNREFERENCED_PARAMETER(sample_result_size_in_bytes);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SqttGetSampleResult(size_t sample_result_size_in_bytes, void* sqtt_results)
{
    UNREFERENCED_PARAMETER(sample_result_size_in_bytes);
    UNREFERENCED_PARAMETER(sqtt_results);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SpmSetSampleInterval(GpaUInt32 interval)
{
    UNREFERENCED_PARAMETER(interval);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SpmSetDuration(GpaUInt32 nanosecond_duration)
{
    UNREFERENCED_PARAMETER(nanosecond_duration);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SpmBegin(void* command_list)
{
    UNREFERENCED_PARAMETER(command_list);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SpmEnd(void* command_list)
{
    UNREFERENCED_PARAMETER(command_list);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SqttSpmBegin(void* command_list)
{
    UNREFERENCED_PARAMETER(command_list);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SqttSpmEnd(void* command_list)
{
    UNREFERENCED_PARAMETER(command_list);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SpmGetSampleResultSize(size_t* sample_result_size_in_bytes)
{
    UNREFERENCED_PARAMETER(sample_result_size_in_bytes);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SpmGetSampleResult(size_t sample_result_size_in_bytes, void* spm_results)
{
    UNREFERENCED_PARAMETER(sample_result_size_in_bytes);
    UNREFERENCED_PARAMETER(spm_results);
    return kGpaStatusErrorApiNotSupported;
}

CounterList* GpaSession::GetCountersForPass(PassIndex pass_index)
{
    if (pass_counters_map_.find(pass_index) == pass_counters_map_.end())
    {
        return nullptr;
    }

    return &pass_counters_map_[pass_index];
}

bool GpaSession::Flush(uint32_t timeout)
{
    TRACE_PRIVATE_FUNCTION(GpaSession::Flush);

    bool ret_val = true;

    auto start_time = std::chrono::steady_clock::now();

    // Block until the session is complete or the timeout (if any) is reached.
    while (!IsResultReady())
    {
        if (timeout != kGpaTimeoutInfinite)
        {
            auto current_time = std::chrono::steady_clock::now();
            auto duration     = current_time - start_time;

            if (std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() > timeout)
            {
                GPA_LOG_ERROR("GPA session completion timeout occurred.");
                ret_val = false;
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        UpdateResults();
    }

    return ret_val;
}

bool GpaSession::GatherCounterResultLocations()
{
    bool success = true;

    for (SessionCounters::const_iterator iter = session_counters_.cbegin(); iter != session_counters_.cend(); ++iter)
    {
        CounterResultLocationMap* temp_result_locations = GpaContextCounterMediator::Instance()->GetCounterResultLocations(this, *iter);

        if (nullptr != temp_result_locations)
        {
            CounterResultLocationMap temp_result_location_map;

            for (CounterResultLocationMap::const_iterator inner_iter = temp_result_locations->cbegin(); inner_iter != temp_result_locations->cend();
                 ++inner_iter)
            {
                GpaCounterResultLocation result_location = {inner_iter->second.pass_index_, inner_iter->second.offset_};
                temp_result_location_map.insert(HardwareCounterResultLocationPair(inner_iter->first, result_location));
            }

            counter_result_locations_.insert(CounterResultLocationPair(*iter, temp_result_location_map));
        }
        else
        {
            success = false;
            break;
        }
    }

    return success;
}

bool GpaSession::BeginSample(ClientSampleId sample_id, GpaCommandListId command_list_id)
{
    bool sample_started = false;

    if (command_list_id->Object()->GetApiType() == GetApiType() && command_list_id->ObjectType() == GpaObjectType::kGpaObjectTypeCommandList)
    {
        IGpaCommandList* gpa_cmd_list = command_list_id->Object();

        if (nullptr != gpa_cmd_list)
        {
            GpaPass* cmd_pass = gpa_cmd_list->GetPass();

            if (nullptr != cmd_pass)
            {
                // Create a sample.
                if (nullptr != cmd_pass->CreateAndBeginSample(sample_id, gpa_cmd_list))
                {
                    sample_started = true;
                }
                else
                {
                    GPA_LOG_ERROR("Unable to create sample.");
                }
            }
            else
            {
                GPA_LOG_ERROR("Pass does not exist.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Command List does not exist.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Invalid Parameter.");
    }

    return sample_started;
}

bool GpaSession::CheckWhetherPassesAreFinishedAndConsistent() const
{
    bool is_consistent = true;
    bool is_finished   = true;

    if (passes_.size() > 1)
    {
        unsigned int sample_count = passes_.at(0)->GetSampleCount();

        for (auto pass_iter = passes_.cbegin(); pass_iter != passes_.cend() && is_finished && is_consistent; ++pass_iter)
        {
            is_finished &= (kGpaStatusOk == (*pass_iter)->IsComplete());
            is_consistent &= (*pass_iter)->GetSampleCount() == sample_count;
        }
    }

    if (!is_finished)
    {
        GPA_LOG_ERROR("Some passes have not ended.");
    }

    if (!is_consistent)
    {
        GPA_LOG_ERROR("Some passes have an incorrect number of samples.");
    }

    return is_finished && is_consistent;
}

bool GpaSession::EndSample(GpaCommandListId command_list_id)
{
    bool sample_ended = false;

    if (command_list_id->Object()->GetApiType() == GetApiType() && command_list_id->ObjectType() == GpaObjectType::kGpaObjectTypeCommandList)
    {
        IGpaCommandList* gpa_cmd_list = command_list_id->Object();

        if (nullptr != gpa_cmd_list)
        {
            GpaPass* cmd_pass = gpa_cmd_list->GetPass();

            if (nullptr != cmd_pass)
            {
                // End the sample.
                if (cmd_pass->EndSample(gpa_cmd_list))
                {
                    sample_ended = true;
                }
                else
                {
                    GPA_LOG_ERROR("Unable to end sample.");
                }
            }
            else
            {
                GPA_LOG_ERROR("Pass does not exist.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Command List does not exist.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Invalid Parameter.");
    }

    return sample_ended;
}

GpaStatus GpaSession::ContinueSampleOnCommandList(GpaUInt32 src_sample_id, GpaCommandListId primary_command_list_id)
{
    UNREFERENCED_PARAMETER(src_sample_id);
    UNREFERENCED_PARAMETER(primary_command_list_id);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::CopySecondarySamples(GpaCommandListId secondary_cmd_list_id,
                                           GpaCommandListId primary_cmd_list_id,
                                           GpaUInt32        num_samples,
                                           GpaUInt32*       new_sample_ids)
{
    UNREFERENCED_PARAMETER(secondary_cmd_list_id);
    UNREFERENCED_PARAMETER(primary_cmd_list_id);
    UNREFERENCED_PARAMETER(num_samples);
    UNREFERENCED_PARAMETER(new_sample_ids);
    return kGpaStatusErrorApiNotSupported;
}

GpaStatus GpaSession::SpmCalculateDerivedCounters(const GpaSpmData* spm_data, GpaUInt32 derived_counter_count, GpaUInt64* derived_counter_results)
{
    UNREFERENCED_PARAMETER(spm_data);
    UNREFERENCED_PARAMETER(derived_counter_count);
    UNREFERENCED_PARAMETER(derived_counter_results);
    return kGpaStatusErrorApiNotSupported;
}
