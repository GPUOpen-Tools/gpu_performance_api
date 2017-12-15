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

#include <AmdExtD3D.h>

#pragma warning (push)
#pragma warning (disable: 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning (pop)

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

    /// Set the device for this context state
    /// \param pDevice the D3D12 device
    /// \param isAMDDevice flag indicating if the device is an AMD device (based on the adapter vendorID)
    /// \return GPA_STATUS_OK if device was set correctly and stable clock mode was entered
    GPA_Status SetD3D12Device(ID3D12Device* pDevice, bool isAMDDevice);

    /// Get the time stamp frequencey
    /// \return GPA_STATUS_OK if time stampe frequencey access succeeded, GPA_STATUS_ERROR_FAILED if it failed
    /// \param[out] timestampFrequency The timestamp frequencey
    GPA_Status GetTimestampFrequency(UINT64& timestampFrequency);

    /// Begin sampling on the specified command list
    /// \param pCommandList the command list on which to begin sampling
    /// \return GPA_STATUS_OK if session start succeeded, GPA_STATUS_ERROR_FAILED if it failed
    GPA_Status BeginCommandList(void* pCommandList);

    /// End sampling on the specified command list
    /// \param pCommandList the command list on which to end sampling
    /// \return GPA_STATUS_OK if session end succeeded, GPA_STATUS_ERROR_FAILED if it failed
    GPA_Status EndCommandList(void* pCommandList);

    /// Gets the GpaSession object for the given command list
    /// \param pCommandList the command list whose GpaSession is needed
    /// \param[out] pGpaSession the GpaSession associated with the command list
    /// \return true if a GpaSession was found for the command list, false otherwise
    bool GetGpaSessionForCommandList(ID3D12GraphicsCommandList* pCommandList, IAmdExtGpaSession** pGpaSession);

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

    /// Get the number of instances of the specified block
    /// \param[in] block the block whose number of instances is needed
    /// \return the number of instances of the specific block.  Could be zero if block does not exist
    gpa_uint32 GetInstanceCount(AmdExtGpuBlock block);

    /// Get the max event id of the specified block
    /// \param[in] block the block whose max event id is needed
    /// \return the max event id of the specified block.  Could be zero if block does not exist
    gpa_uint32 GetMaxEventIdCount(AmdExtGpuBlock block);

private:
    typedef std::unordered_map<ID3D12CommandList*, DX12CommandListSwQueries> CommandListQueriesType; ///< Typedef for map from command list to queries
    typedef std::unordered_map<ID3D12GraphicsCommandList*, IAmdExtGpaSession*> CommandListGpaSessionType; ///< Typedef for map from command list to GPASession interface

    ID3D12Device*                  m_device;                ///< The device queries and counters are created on
    CommandListQueriesType         m_commandListQueries;    ///< Map from command list to queries
    CommandListGpaSessionType      m_commandListGpaSession; ///< Map from command list to gpa session
    AMDTMutex                      m_mutex;                 ///< Context access mutex
    IAmdExtD3DFactory*             m_pAmdExtObject;         ///< Driver extension object
    IAmdExtGpaInterface*           m_pGpaInterface;         ///< The GPA Interface from the driver
    AmdExtPerfExperimentProperties m_props;                 ///< Counter properties reported by the driver


    /// Enable/disable the stable power state
    /// \return GPA_STATUS_OK if stable power is enabled/disabled, GPA_STATUS_ERROR_FAILED if it's not
    /// \param[in] useProfilingClocks true to use GPU clocks for profiling
    inline GPA_Status SetStableClocks(bool useProfilingClocks);
};

#endif // _GPA_CONTEXT_STATE_DX12_H_
