//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12CommandListSwQueries declaration
//==============================================================================

#ifndef _DX12_COMMAND_LIST_SW_QUERIES_H_
#define _DX12_COMMAND_LIST_SW_QUERIES_H_

#include <vector>

#include "DX12CommandListSWQueryGroup.h"

/// Container for SW queries and resources executed on a command list
class DX12CommandListSwQueries
{
public:
    /// Construct a DX12CommandListSwQueries instance
    DX12CommandListSwQueries();

    /// Move constructor
    ///
    /// \param[in] other The command list moved
    DX12CommandListSwQueries(DX12CommandListSwQueries&& other);

    /// Destroy this DX12CommandListSwQueries
    ~DX12CommandListSwQueries();

    /// Move operator
    ///
    /// \return Reference to this DX12CommandListSwQueries
    /// \param[in] other The command list moved
    DX12CommandListSwQueries& operator=(DX12CommandListSwQueries&& other);

    /// Initialize the DX12CommandListSwQueries instance resources
    ///
    /// \return True if initialization succeeded, false if it failed
    /// \param[in] device The device queries are executed on
    /// \param[in] commandList The command list the queries are excuted on
    bool Initialize(ID3D12DevicePtr& device, ID3D12GraphicsCommandListPtr& commandList);

    /// Begin SW sample
    ///
    /// Acquire a sample ID
    /// \return True if sampling started, false if not
    /// \param[out] swSampleId The SW sample ID - unique to the context
    bool BeginSwSample(gpa_uint32& swSampleId);

    /// End SW sample
    ///
    /// Signal the end of sample event
    /// \see GetSwSampleResults
    /// \param[in] swSampleId The SW sample ID
    void EndSwSample(const gpa_uint32 swSampleId);

    /// Release the given SW sample.
    ///
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
    /// Creates and initializes a new group of queries
    ///
    /// \return True if the new query group was created sucessfully
    bool CreateNewQueryGroup();

    /// Copy constructor - private override to prevent usage
    DX12CommandListSwQueries(const DX12CommandListSwQueries&) = delete;

    /// Copy operator - private override to prevent usage
    DX12CommandListSwQueries& operator=(const DX12CommandListSwQueries&) = delete;

    static const size_t          ms_resultGroupSize = 256;  ///< The number of results to store in a group (additional samples will require an additional group)

    typedef std::vector<DX12CommandListSWQueryGroup*> QueryGroupListType; ///< typedef for the list of query groups

    ID3D12GraphicsCommandListPtr m_commandList;             ///< The command list queries and counters are inserted to
    ID3D12DevicePtr              m_device;                  ///< The device which created the command list
    QueryGroupListType           m_queryGroups;             ///< The list of query groups for this command list

}; // end of class DX12CommandListSwQueries

#endif // _DX12_COMMAND_LIST_SW_QUERIES_H_

