//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  D3D11 Software counter data request
//==============================================================================

#ifndef _D3D11_SOFTWARE_COUNTER_DATA_REQUEST_H_
#define _D3D11_SOFTWARE_COUNTER_DATA_REQUEST_H_

#include <d3d11.h>
#include "..\GPUPerfAPI-Common\GPUPerfAPIImp.h"
#include "ICounterDataRequest.h"
#include "GPUPerfAPIDX11.h"
#include "DX11ComSmartPtrs.h"

/// Set of query objects for the D3D queries
struct GPA_D3D11Query
{
    ID3D11QueryPtr m_timeStampDisjointQuery;  ///< Query object to get the time stamp frequency value
    ID3D11QueryPtr m_timeStampFirstQuery;     ///< Query object to get the first time stamp value
    ID3D11QueryPtr m_timeStampSecondQuery;    ///< Query object to get the second time stamp value
    ID3D11QueryPtr m_pipelineStatsQuery;      ///< Query object to get pipeline stats
    ID3D11QueryPtr m_occlusionQuery;          ///< Query object to get the number of samples that passed the depth and stencil tests
    ID3D11QueryPtr m_occlusionPredQuery;      ///< Query object to indicate whether or not any samples passed the depth and stencil tests
    ID3D11QueryPtr m_soStatsQuery;            ///< Query object to get streaming output statistics
    ID3D11QueryPtr m_soOverflowPredQuery;     ///< Query object to determines if any of the streaming output buffers overflowed
    ID3D11QueryPtr m_soStatsS0Query;          ///< Query object to get streaming output statistics for stream 0
    ID3D11QueryPtr m_soOverflowPredS0Query;   ///< Query object to determines whether or not the stream 0 output buffers overflowed
    ID3D11QueryPtr m_soStatsS1Query;          ///< Query object to get streaming output statistics for stream 1
    ID3D11QueryPtr m_soOverflowPredS1Query;   ///< Query object to determines whether or not the stream 1 output buffers overflowed
    ID3D11QueryPtr m_soStatsS2Query;          ///< Query object to get streaming output statistics for stream 2
    ID3D11QueryPtr m_soOverflowPredS2Query;   ///< Query object to determines whether or not the stream 2 output buffers overflowed
    ID3D11QueryPtr m_soStatsS3Query;          ///< Query object to get streaming output statistics for stream 3
    ID3D11QueryPtr m_soOverflowPredS3Query;   ///< Query object to determines whether or not the stream 3 output buffers overflowed
};

/// Set of query data for D3D queries
struct GPA_D3D11QueryData
{
    UINT64 m_timeStampFirst;                                  ///< First Time Stamp Value
    UINT64 m_timeStampSecond;                                 ///< Second Time Stamp Value
    D3D11_QUERY_DATA_TIMESTAMP_DISJOINT m_disjointData;       ///< Query information about the reliability of a timestamp query
    UINT64 m_samplesPassed;                                   ///< number of samples that passed the depth and stencil tests
    D3D11_QUERY_DATA_PIPELINE_STATISTICS m_pipelineStats;     ///< pipelineStats struct
    BOOL m_anySamplePassed;                                   ///< any samples passed the depth and stencil tests
    D3D11_QUERY_DATA_SO_STATISTICS m_soStats;                 ///< stream out stats struct
    BOOL m_soOverFlow;                                        ///< any of the streaming output buffers overflowed
    D3D11_QUERY_DATA_SO_STATISTICS m_soStatsS0;               ///< stream out S0 stats struct
    BOOL m_soS0OverFlow;                                      ///< any of the stream0 output buffers overflowed
    D3D11_QUERY_DATA_SO_STATISTICS m_soStatsS1;               ///< stream out S1 stats struct
    BOOL m_soS1OverFlow;                                      ///< any of the stream1 output buffers overflowed
    D3D11_QUERY_DATA_SO_STATISTICS m_soStatsS2;               ///< stream out S2 stats struct
    BOOL m_soS2OverFlow;                                      ///< any of the stream2 output buffers overflowed
    D3D11_QUERY_DATA_SO_STATISTICS m_soStatsS3;               ///< stream out S3 stats struct
    BOOL m_soS3OverFlow;                                      ///< any of the stream3 output buffers overflowed
};

/// \brief Maintains the information pertaining to a single sample of counters.
/// Contains the list of enabled counters, can identify when the data is available,
/// and can return the results of the profile sample.
class D3D11SoftwareCounterDataRequest : public ICounterDataRequest
{
public:

    /// Initializes a new D3D11SoftwareCounterDataRequest object with GPA_DataRequest object
    D3D11SoftwareCounterDataRequest(GPA_DataRequest* pParentCounter);

    /// Destructor
    virtual ~D3D11SoftwareCounterDataRequest();

protected:
    virtual bool BeginRequest(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);
    virtual bool EndRequest();
    virtual void ReleaseCounters();
    virtual void Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);
    virtual bool CollectResults(GPA_CounterResults& resultStorage, size_t numActiveCounters, gpa_uint32 sampleId);

    /// Gets the GPU time data
    /// \return the GPU time data
    gpa_uint64 GetGPUTime();

    /// Gets the data for the D3D query
    /// \param index the index of the query whose data is needed
    /// \return the data for the specified query
    gpa_uint64 GetSWD3DCounterData(gpa_uint32 index);

    /// Checks whether or not the GPUTime counter is active
    /// \return true if the GPUTime counter is active
    bool IsSWGPUTimeCounterActive();

    /// Checks whether a D3D query counter is active
    /// \return true if a D3D query counter is active
    bool IsSWCounterActive();

    ID3D11DevicePtr               m_device             = nullptr;      ///< D3D11 device
    ID3D11DeviceContextPtr        m_D3DContext         = nullptr;      ///< D3D11 device context
    GPA_D3D11Query                m_D3d11Query;                        ///< D3D11 queries
    GPA_D3D11QueryData            m_D3d11QueryData;                    ///< D3D11 query data
    GPA_DataRequest*              m_parentCounter;                     ///< Pointer to the parent counter object - it has data members we need to work on.
    gpa_uint32                    m_numAMDCounters     = 0;            ///< number of AMD counters
    gpa_uint32                    m_numSwCounters      = 0;            ///< number of SW counters
    const EnabledSwCounterSet*    m_pEnabledSwCounters = nullptr;      ///< pointer to s_pSwCounterManager::m_EnabledSwCounters vector
    vector<gpa_uint32>            m_activeSWCountersVec;               ///< active SW counter public index vector in current pass
};

#endif // _D3D11_SOFTWARE_COUNTER_DATA_REQUEST_H_
