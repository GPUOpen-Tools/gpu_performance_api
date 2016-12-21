//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Implementation for sampling performance counters using the DX
/// Performance Experiment extension.
//==============================================================================

#ifndef _DX11_PERF_EXPERIMENT_DATA_REQUEST_HANDLER_H_
#define _DX11_PERF_EXPERIMENT_DATA_REQUEST_HANDLER_H_

#include <d3d11.h>
#include "..\GPUPerfAPI-Common\GPUPerfAPIImp.h"
#include "GPUPerfAPIDX11.h"
#include "ICounterDataRequest.h"
#include "AmdDxExtPerfProfileApi.h"

/// \brief Maintains the information pertaining to a single sample of counters.
/// Contains the list of enabled counters, can identify when the data is available,
/// and can return the results of the profile sample.
class DX11_PerfExperimentDataRequestHandler : public ICounterDataRequest
{
public:

    /// Initializes a new instance of the DXPerformanceExperimentProfile class.
    DX11_PerfExperimentDataRequestHandler(GPA_DataRequest* pParentCounter);

    /// Destructor
    virtual ~DX11_PerfExperimentDataRequestHandler();

    /// Initialize the extension.
    /// \param context
    /// \return true or false
    bool Initialize(void* context);

    virtual void Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);

    /// Get the block info for the specified block of the specified GPU
    /// \param gpuID the GPU being queried
    /// \param block the block id being queried
    /// \param[out] pBlockInfo the block info
    /// \return true on success, false otherwise
    bool GetBlockCounterInfo(UINT gpuID, PE_BLOCK_ID block, PE_BLOCK_COUNTER_INFO* pBlockInfo);

protected:

    virtual bool BeginRequest(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);

    virtual bool EndRequest();

    virtual bool CollectResults(GPA_CounterResults& resultStorage, size_t m_activeCounters, gpa_uint32 sampleId);

    virtual void ReleaseCounters();

private:

    /// Creates the performance experiment used by this object.
    void CreateExperiment();

    /// Destroys the performance experiment used by this object.
    void DestroyExperiment();

    /// Get the index of the acitve GPU
    /// \return Index of the active GPU or ActiveGpuCF if more than 1 GPU is active
    unsigned int GetActiveGpu() const;

    /// Initialize the block instance limits for the specified GPU
    /// \param activeGpu the gpu index whose block instance limits are needed
    void PopulateBlockInstanceLimits(UINT activeGpu);

    /// CF/ACF active GPU
    static const unsigned int ActiveGpuCF = 0xffffffff;

    IAmdDxExt* m_pExt;               ///< The AMD Dx Extension interface
    IAmdDxExtPerfProfile* m_pExtPE;  ///< The Perf Experiment extension interface

    IAmdDxExtPerfExperiment* m_pExperiment;          ///< The experiment related to this sample
    IAmdDxExtPerfCounter** m_counters;               ///< The collection of active perf counters

    /// Timestamp queries are treated as much like regular counters as possible
    /// to minimize code impact, and maximize shared code.
    /// Special case processing added where required.
    ID3D11Counter* m_GPUTimeCounter;

    /// Pointer to the parent counter object - it has data members we need to work on.
    GPA_DataRequest* m_parentCounter;

    /// typedef for a map from block id to number of instances
    typedef std::map<PE_BLOCK_ID, unsigned int> BlockInstanceLimitMap;

    /// typedef for a map from GPU Index to a BlockInstanceLimitMap
    typedef std::map<UINT, BlockInstanceLimitMap> GpuBlockInstanceLimitMap;

    /// map of block instance counts per gpu device
    static GpuBlockInstanceLimitMap ms_blockInstanceLimits;

    /// index of the gpu to use to check block limits
    unsigned int m_gpuToCheckBlockLimits;
};

#endif // _DX11_PERF_EXPERIMENT_DATA_REQUEST_HANDLER_H_
