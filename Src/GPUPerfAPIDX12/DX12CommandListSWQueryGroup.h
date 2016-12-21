//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage the resources used for DX12 SW queries
//==============================================================================

#ifndef _DX12_COMMAND_LIST_SW_QUERY_GROUP_H_
#define _DX12_COMMAND_LIST_SW_QUERY_GROUP_H_

#include "GPUPerfAPITypes.h"
#include "DX12SoftwareCountersResults.h"
#include "DX12ComSmartPtrs.h"

/// Class to manage the resources used for DX12 SW queries
class DX12CommandListSWQueryGroup
{
public:
    /// Construct a DX12CommandListSWQueryGroup instance
    DX12CommandListSWQueryGroup();

    /// Move constructor
    ///
    /// \param[in] other The command list moved
    DX12CommandListSWQueryGroup(DX12CommandListSWQueryGroup&& other);

    /// Destroy this DX12CommandListSWQueryGroup
    ~DX12CommandListSWQueryGroup();

    /// Move operator
    ///
    /// \return Reference to this DX12CommandListSWQueryGroup
    /// \param[in] other The command list moved
    DX12CommandListSWQueryGroup& operator=(DX12CommandListSWQueryGroup&& other);

    /// Initialize the DX12CommandListSWQueryGroup instance resources
    ///
    /// \return True if initialization succeeded, false if it failed
    /// \param[in] device The device queries are executed on
    /// \param[in] commandList The command list the queries are excuted on
    /// \param[in] groupSize The number of queries/results in this group
    bool Initialize(ID3D12DevicePtr& device, ID3D12GraphicsCommandListPtr& commandList, size_t groupSize);

    /// Cleanup the DX12CommandListSwQueries instance resources
    void Cleanup();

    /// Get the active sample count for this group
    ///
    /// \return the number of active samples in this group
    gpa_uint32 GetSampleCount() const;

    /// Begin SW sample
    ///
    /// Increments the sample count for this group
    void BeginSwSample();

    /// End SW sample
    ///
    /// Signals the end of sample event and copies the results into the results buffer
    /// \see GetSwSampleResults
    /// \param[in] swSampleId The SW sample ID
    void EndSwSample(const gpa_uint32 swSampleId);

    /// Release the given SW sample.
    ///
    /// Clears the results buffer for this sample, and decrements the sample count for this group
    /// \param[in] swSampleId The SW sample ID
    void ReleaseSwSample(const gpa_uint32 swSampleId);

    /// Begin single SW query sampling
    ///
    /// \return True if sampling started, false if not
    /// \param[in] swSampleId The SW sample ID
    /// \param[in] queryType The query type
    void BeginSwQuery(const gpa_uint32 swSampleId, const D3D12_QUERY_TYPE queryType);

    /// End single SW query sampling
    ///
    /// \param[in] swSampleId The SW sample ID
    /// \param[in] queryType The query type
    void EndSwQuery(const gpa_uint32 swSampleId, const D3D12_QUERY_TYPE queryType);

    /// Get SW sample results
    ///
    /// \return True if results are avilable, false if results are not available
    /// \param[in] swSampleId The SW sample ID
    /// \param[out] queryResults The SW countes results
    bool GetSwSampleResults(const gpa_uint32 swSampleId, DX12SoftwareCountersResults& queryResults);

private:
    /// Copy constructor - private override to prevent usage
    DX12CommandListSWQueryGroup(const DX12CommandListSWQueryGroup&) = delete;

    /// Copy operator - private override to prevent usage
    DX12CommandListSWQueryGroup& operator=(const DX12CommandListSWQueryGroup&) = delete;

    /// Create SW queries of the given type
    ///
    /// \return True if query heap creation succeeded, false if it failed
    /// \param[in] device The device the heap is created on
    /// \param[in] queryType The SW query type of the heap
    bool CreateSwQueryHeap(ID3D12DevicePtr& device, const D3D12_QUERY_TYPE queryType);

    /// Create the SW queries results resources
    ///
    /// \return True if resource creation succeeded, false if it failed
    /// \param[in] device The device the resource is created on
    bool CreateSwQueriesResultsResources(ID3D12DevicePtr& device);

    /// Create the SW queries IDs resource - used to signal query results are available
    ///
    /// \return True if resource creation succeeded, false if it failed
    /// \param[in] device The device the resource is created on
    bool CreateQueriesIdsResource(ID3D12DevicePtr& device);

    /// Get the session ID for a given session index
    ///
    /// \return The session ID
    /// \param[in] session index
    static UINT64 GetQueryId(const UINT64 session);

    static const D3D12_QUERY_TYPE ms_queryTypes[];              ///< The list of query types used
    static const size_t           ms_queryTypeCount = 4;        ///< The query type list size

    size_t                        m_maxSamples;                 ///< The max number of samples that this group can hold
    gpa_uint32                    m_sampleCount;                ///< The number of active samples in this group
    ID3D12GraphicsCommandListPtr  m_commandList;                ///< The command list that queries and counters are inserted to
    ID3D12ResourcePtr             m_queriesResultsResource;     ///< SW queries results resource
    DX12SoftwareCountersResults*  m_pQueriesResults;            ///< SW queries results
    ID3D12ResourcePtr             m_queriesSessionIdsResource;  ///< SW queries session ID resource - used to signal query results are available
    ID3D12QueryHeapPtr            m_queries[ms_queryTypeCount]; ///< Timestamp queries heap
};  // end of class DX12CommandListSWQueryGroup

#endif // _DX12_COMMAND_LIST_SW_QUERY_GROUP_H_
