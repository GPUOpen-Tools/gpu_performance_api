//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA_ContextStateDX12 declaration
//==============================================================================

#ifndef _GPA_CONTEXT_STATE_DX12_H_
#define _GPA_CONTEXT_STATE_DX12_H_

#include <Windows.h>
#include <D3D12.h>
#include <unordered_map>
#include <vector>

#include <AMDTMutex.h>
#include <GPAContextState.h>

#include "DX12CommandListSwQueries.h"
#include "DX12ComSmartPtrs.h"
#include "DX12SoftwareCountersResults.h"

/// GPA DX12 context state
class GPA_ContextStateDX12 : public GPA_ContextState
{
public:
    /// Construct a GPA DX12 context state instance
    GPA_ContextStateDX12();

    /// Destroy this GPA DX12 context state instance
    virtual ~GPA_ContextStateDX12();

    /// Cleanup DX12 GPA context resources
    void Cleanup();

    /// Set the command list for this context state
    bool SetCommandList(ID3D12GraphicsCommandListPtr pCommandList);

    /// Get the time stamp frequencey
    /// \return GPA_STATUS_OK if time stampe frequencey access succeeded, GPA_STATUS_ERROR_FAILED if it failed
    /// \param[out] timestampFrequency The timestamp frequencey
    GPA_Status GetTimestampFrequency(UINT64& timestampFrequency);

    /// Begin sampling session
    /// \return GPA_STATUS_OK if session start succeeded, GPA_STATUS_ERROR_FAILED if it failed
    GPA_Status BeginSession();

    /// End sampling session
    /// \return GPA_STATUS_OK if session end succeeded, GPA_STATUS_ERROR_FAILED if it failed
    GPA_Status EndSession();

    /// Begin SW sample
    ///
    /// Acquire a sample ID
    /// \return True if sampling started, false if not
    /// \param[out] commandList The command list the SW sample (query) the is executed on
    /// \param[out] swSampleId The SW sample ID - unique to the context
    bool BeginSwSample(ID3D12GraphicsCommandListPtr& commandList, gpa_uint32& swSampleId);

    /// End SW sample
    ///
    /// Signal the end of sample event
    /// \see GetSwSampleResults
    /// \param[in] commandList The command list the SW sample (query) the is executed on
    /// \param[in] swSampleId The SW sample ID
    void EndSwSample(ID3D12GraphicsCommandListPtr& commandList, const gpa_uint32 swSampleId);

    /// Release the given SW sample.
    /// \param[in] commandList The command list the SW sample (query) the is executed on
    /// \param[in] swSampleId The SW sample ID
    void ReleaseSwSample(ID3D12GraphicsCommandListPtr& commandList, const gpa_uint32 swSampleId);

    /// Begin single SW query sampling
    /// \param[in] commandList The command list the SW sample (query) the is executed on
    /// \param[in] swSampleId The SW sample ID
    /// \param[in] queryType The query type
    void BeginSwQuery(
        ID3D12GraphicsCommandListPtr& commandList,
        const gpa_uint32 swSampleId,
        const D3D12_QUERY_TYPE queryType);

    /// End single SW query sampling
    /// \param[in] commandList The command list the SW sample (query) the is executed on
    /// \param[in] swSampleId The SW sample ID
    /// \param[in] queryType The query type
    void EndSwQuery(
        ID3D12GraphicsCommandListPtr& commandList,
        const gpa_uint32 swSampleId,
        const D3D12_QUERY_TYPE queryType);

    /// Get SW sample results
    /// \return True if results are avilable, false if results are not available
    /// \param[in] commandList The command list the SW sample (query) the is executed on
    /// \param[in] swSampleId The SW sample ID
    /// \param[out] queryResults The SW countes results
    bool GetSwSampleResults(
        ID3D12GraphicsCommandListPtr& commandList,
        const gpa_uint32 swSampleId,
        DX12SoftwareCountersResults& queryResults);

private:
    typedef std::unordered_map<ID3D12CommandList*, DX12CommandListSwQueries> CommandListQueriesType; ///< Typedef for map from command list to queries

    ID3D12DevicePtr              m_device;             ///< The device queries and counters are created on
    ID3D12GraphicsCommandListPtr m_commandList;        ///< The command list queries and counters are inserted to
    CommandListQueriesType       m_commandListQueries; ///< Map from command list to queries
    AMDTMutex                    m_mutex;              ///< Context access mutex

    /// Enable/disable the stable power state
    /// \return GPA_STATUS_OK if stable power is enabled/disable, GPA_STATUS_ERROR_FAILED if it's not
    /// \param[in] state TRUE to enable stable power state, false to disable stable power state
    inline GPA_Status SetStablePowerState(BOOL state);

}; // end of class GPA_ContextStateDX12

#endif // _GPA_CONTEXT_STATE_DX12_H_

