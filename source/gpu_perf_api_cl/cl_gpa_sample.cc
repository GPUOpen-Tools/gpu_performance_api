//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  CL GPA Sample Implementation
//==============================================================================

#include "cl_gpa_context.h"
#include "gpa_hardware_counters.h"
#include "gpa_pass.h"
#include "cl_gpa_sample.h"
#include "cl_perf_counter_block.h"
#include "cl_perf_counter_amd_extension.h"
#include "cl_gpa_pass.h"
#include "gpa_context_counter_mediator.h"

ClGpaSample::ClGpaSample(GpaPass* pass, IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id)
    : GpaSample(pass, cmd_list, sample_type, sample_id)
    , cl_counters_(nullptr)
    , cl_event_(nullptr)
    , data_ready_count_(0)
{
    if (nullptr != pass)
    {
        IGpaSession* gpa_session = pass->GetGpaSession();

        if (nullptr != gpa_session)
        {
            cl_gpa_context_ = reinterpret_cast<ClGpaContext*>(gpa_session->GetParentContext());
        }
    }
}

ClGpaSample::~ClGpaSample()
{
    ReleaseBlockCounters();
    DeleteCounterBlocks();
    delete[] cl_counters_;
}

bool ClGpaSample::UpdateResults()
{
    bool is_complete = false;

    CounterCount counter_count = GetPass()->GetEnabledCounterCount();

    if (nullptr != cl_event_)
    {
        // Get the data from opencl interface
        for (GpaUInt32 i = 0; i < cl_counter_blocks_.size(); ++i)
        {
            cl_counter_blocks_[i]->CollectData(&cl_event_);
        }

        // get and set the result to counters_list_
        for (GpaUInt32 i = 0; i < counter_count; ++i)
        {
            if (!cl_counters_[i].is_counter_result_ready)
            {
                GpaUInt32 group_id   = cl_counters_[i].counter_group;
                GpaUInt32 counter_id = cl_counters_[i].counter_index;

                // find the corresponding block with uGroupID
                GpaUInt32 block_id = 0;

                if (!FindBlockId(block_id, group_id))
                {
                    // can't find the corresponding block with the group id
                    // something must be wrong in the block initialization/creation
                    return false;
                }

                if (cl_counter_blocks_[block_id]->IsComplete())
                {
                    GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = cl_counter_blocks_[block_id]->GetResult(counter_id);
                    cl_counters_[i].is_counter_result_ready                                     = true;
                    data_ready_count_++;
                }
            }
        }
    }
    else
    {
        // clEnqueueEndPerfCounterAMD() hasn't been called successfully
    }

    is_complete = data_ready_count_ == counter_count;

    if (is_complete)
    {
        MarkAsCompleted();
    }

    return is_complete;
}

bool ClGpaSample::BeginRequest()
{
    bool success = true;

    if (nullptr != cl_gpa_context_)
    {
        CounterCount counter_count = GetPass()->GetEnabledCounterCount();

        cl_counters_ = new (std::nothrow) ClCounter[counter_count];

        if (nullptr == cl_counters_)
        {
            GPA_LOG_ERROR("Unable to allocate memory for CL counters.");
            return false;
        }

        IGpaCounterAccessor*       counter_accessor  = GpaContextCounterMediator::Instance()->GetCounterAccessor(cl_gpa_context_);
        const GpaHardwareCounters* hardware_counters = counter_accessor->GetHardwareCounters();

        bool         populate_counter_info_status = true;
        unsigned int counter_group_size           = 0u;

        auto populate_cl_perf_counter_info = [&](GroupCountersPair group_counters_pair) -> bool {
            bool counter_status = true;

            GpaUInt32 max_counters_enabled =
                static_cast<GpaUInt32>(hardware_counters->internal_counter_groups_[group_counters_pair.first].max_active_discrete_counters);
            ClPerfCounterBlock* cl_block = nullptr;

            cl_block = new (std::nothrow)
                ClPerfCounterBlock(cl_gpa_context_->GetClDeviceId(), group_counters_pair.first, max_counters_enabled, group_counters_pair.second);

            if (nullptr == cl_block)
            {
                GPA_LOG_ERROR("Unable to allocate memory for CL counter blocks.");
                counter_status = false;
            }
            else
            {
                cl_counter_blocks_.push_back(cl_block);

                // store the opencl counters into an array so we can use one call of clEnqueueBeginPerfCounterAMD for all of them
                cl_perfcounter_amd* cl_counters = cl_block->GetCounterArray(0);

                for (GpaUInt32 i = 0; i < cl_block->GetCounterCount(); ++i)
                {
                    cl_counter_list_.push_back(cl_counters[i]);
                }
            }

            populate_counter_info_status &= counter_status;
            counter_group_size++;
            return counter_status;
        };

        ClGpaPass* cl_gpa_pass = reinterpret_cast<ClGpaPass*>(GetPass());

        // loop through the requested counters and create and enable them
        cl_gpa_pass->IterateClCounterMap(populate_cl_perf_counter_info);

        assert(cl_counter_blocks_.size() == counter_group_size);

        if (CL_SUCCESS != my_cl_enqueue_begin_perf_counter_amd(
                              cl_gpa_context_->GetClCommandQueue(), static_cast<cl_uint>(cl_counter_list_.size()), &cl_counter_list_[0], 0, 0, 0))
        {
            //Reset(selectionID, pCounters);
            return false;
        }

        unsigned int counter_count_iter = 0;

        auto add_cl_counter_to_sample = [&](const CounterIndex& counter_index) -> bool {
            const GpaHardwareCounterDescExt* counter = counter_accessor->GetHardwareCounterExt(counter_index);

            // GPA_LOG_DEBUG_MESSAGE( "ENABLED COUNTER: %x.", counters_list_[i] );
            cl_counters_[counter_count_iter].counter_id    = counter_index;
            cl_counters_[counter_count_iter].counter_group = counter->group_id_driver;
            cl_counters_[counter_count_iter].counter_index = static_cast<GpaUInt32>(counter->hardware_counters->counter_index_in_group);
            counter_count_iter++;
            return true;
        };

        cl_gpa_pass->IterateEnabledCounterList(add_cl_counter_to_sample);
    }
    else
    {
        GPA_LOG_ERROR("CL Context is not initialized.");
        success = false;
    }

    return success;
}

bool ClGpaSample::EndRequest()
{
    bool success =
        (CL_SUCCESS == my_cl_enqueue_end_perf_counter_amd(
                           cl_gpa_context_->GetClCommandQueue(), static_cast<cl_uint>(cl_counter_list_.size()), &cl_counter_list_[0], 0, 0, &cl_event_));

    return success;
}

void ClGpaSample::ReleaseCounters()
{
    ReleaseBlockCounters();
}

bool ClGpaSample::FindBlockId(GpaUInt32& block_id, GpaUInt32 group_id)
{
    for (GpaUInt32 i = 0; i < cl_counter_blocks_.size(); ++i)
    {
        if (group_id == cl_counter_blocks_[i]->GetBlockID())
        {
            block_id = i;
            return true;
        }
    }

    return false;
}

void ClGpaSample::DeleteCounterBlocks()
{
    if (!cl_counter_blocks_.empty())
    {
        for (GpaUInt32 i = 0; i < cl_counter_blocks_.size(); ++i)
        {
            delete cl_counter_blocks_[i];
        }
    }

    cl_counter_blocks_.clear();
}

void ClGpaSample::ReleaseBlockCounters()
{
    for (GpaUInt32 i = 0; i < cl_counter_blocks_.size(); ++i)
    {
        cl_counter_blocks_[i]->ReleaseCounters();
    }
}
