//==============================================================================
// Copyright (c) 2009-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A utility class for interfacing with the performance counter from the OpenCL runtime.
//==============================================================================

#include <assert.h>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include <CL/cl.h>
#include <CL/internal/cl_profile_amd.h>
#include "CLPerfCounterBlock.h"
#include "CLPerfCounterAMDExtension.h"
#include "CLRTModuleLoader.h"

clPerfCounterBlock::clPerfCounterBlock(cl_device_id    clDevice,
                                       cl_ulong        blockID,
                                       cl_uint         maxActive,
                                       std::vector< cl_ulong > pCounters): m_clDevice(clDevice),
    m_blockID(blockID),
    m_maxActive(maxActive),
    m_pCounters(pCounters),
    m_pclCounters(nullptr),
    m_isResultReady(false)
{
    Create();
}

clPerfCounterBlock::~clPerfCounterBlock()
{
    this->ReleaseCounters();
}

void clPerfCounterBlock::ReleaseCounters()
{
    if (nullptr != m_pclCounters)
    {
        for (cl_uint i = 0; i < m_pCounters.size(); ++i)
        {
            my_clReleasePerfCounterAMD(m_pclCounters[i]);
        }

        delete[] m_pclCounters;
        m_pclCounters = nullptr;
    }
}

void clPerfCounterBlock::Create()
{
    if (m_pCounters.empty())
    {
        return;
    }

    cl_int  error;
    cl_perfcounter_property properties[4][2];

    m_pclCounters = new(std::nothrow) cl_perfcounter_amd[m_pCounters.size()];

    if (nullptr == m_pclCounters)
    {
        std::cerr << "clPerfCounterBlock: Couldn't allocate memory!\n";
        return;
    }

    properties[0][0] = CL_PERFCOUNTER_GPU_BLOCK_INDEX;
    properties[1][0] = CL_PERFCOUNTER_GPU_COUNTER_INDEX;
    properties[2][0] = CL_PERFCOUNTER_GPU_EVENT_INDEX;
    properties[3][0] = CL_PERFCOUNTER_NONE;

    properties[0][1] = m_blockID;

    for (cl_uint i = 0; i < GetNumPasses(); ++i)
    {
        for (cl_uint j = 0; j < m_maxActive; ++j)
        {
            cl_uint index    = i * m_maxActive + j;

            if (index >= m_pCounters.size())
            {
                break;
            }

            properties[1][1] = j;
            properties[2][1] = m_pCounters[index];

            m_pclCounters[index] = my_clCreatePerfCounterAMD(m_clDevice, &properties[0][0], &error);

            if (CL_SUCCESS != error)
            {
                std::cerr << "clPerfCounterBlock(" << i << "," << j << ")=" << error
                          << " failed to create a perfcounter\n";
                return;
            }
        }
    }
}

bool clPerfCounterBlock::CollectData(const cl_event* clEvent)
{
    if (m_isResultReady)
    {
        return true;
    }

    assert(nullptr != m_pclCounters);

    if (m_pCounters.empty() ||
        nullptr == m_pclCounters)
    {
        return false;
    }

    cl_int error;
    cl_ulong result;

    OCLRTModuleLoader::Instance()->GetAPIRTModule()->WaitForEvents(1, clEvent);

    for (cl_uint i = 0; i < m_pCounters.size(); ++i)
    {
        error = my_clGetPerfCounterInfoAMD(m_pclCounters[i],
                                           CL_PERFCOUNTER_DATA,
                                           sizeof(cl_ulong),
                                           &result,
                                           nullptr);

        if (CL_SUCCESS != error)
        {
            std::cerr << "clPerfCounterBlock(" << i << ")=" << error
                      << " failed to get the perf counter data\n";
            return false;
        }

        m_results[m_pCounters[i]] = result;
    }

    m_isResultReady = true;
    return true;
}
