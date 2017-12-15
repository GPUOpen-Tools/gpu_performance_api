//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 GPA Sample Header
//==============================================================================

#ifndef _DX11_GPA_SAMPLE_H_
#define _DX11_GPA_SAMPLE_H_

#include "GPASample.h"
#include "DX11GPAContext.h"

/// Class for DX11 Specific sample
class DX11GPASample : public GPASample
{
public:

    /// Delete default constructor
    DX11GPASample() = delete;

    /// Constructor
    /// \param[in] pPass GPA Pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleId user-supplied sample id
    /// \param[in] uiGpaSampleId gpa internal sample id
    DX11GPASample(GPAPass* pPass,
                  IGPACommandList* pCmdList,
                  GpaSampleType sampleType,
                  ClientSampleId sampleId);

    /// \copydoc GPASample::UpdateResults
    bool UpdateResults() override final;

    /// \copydoc GPASample::BeginRequest
    bool BeginRequest(IGPAContext* pContextState, const std::vector<gpa_uint32>* pCounters) override final;

    /// \copydoc GPASample::EndRequest
    bool EndRequest() override final;

    /// \copydoc GPASample::ReleaseCounters
    void ReleaseCounters() override final;

    /// Get the block info for the specified block of the specified GPU
    /// \param[in] gpuID the GPU being queried
    /// \param[in] block the block id being queried
    /// \param[out] pBlockInfo the block info
    /// \return true on success, false otherwise
    bool GetBlockCounterInfo(UINT gpuID, PE_BLOCK_ID block, PE_BLOCK_COUNTER_INFO* pBlockInfo) const;

private:

    /// Creates the sample experiment
    /// \param[in] pCounters list of counters
    /// \return true upon successful operation otherwise false
    bool CreateSampleExperiment(const std::vector<gpa_uint32>* pCounters);

    /// Initializes the counters
    /// \param[in] pCounters list of counters
    /// \return true upon successful operation otherwise false
    bool InitializeCounters(const std::vector<gpa_uint32>* pCounters);

    /// sets the experiment parameters
    /// \param[in] pCounters list of counters
    /// \return true upon successful operation otherwise false
    bool SetExperimentParams(const std::vector<gpa_uint32>* pCounters) const;

    /// Populates the result of the sample from the driver
    /// \return true upon successful operation otherwise false
    bool PopulateResult();

    /// Get the index of the acitve GPU
    /// \return Index of the active GPU or ActiveGpuCF if more than 1 GPU is active
    unsigned int GetActiveGpu() const;

    /// Initialize the block instance limits for the specified GPU
    /// \param[in] activeGpu the gpu index whose block instance limits are needed
    void PopulateBlockInstanceLimits(UINT activeGpu) const;

    typedef std::map<PE_BLOCK_ID, unsigned int>                 BlockInstanceLimitMap;              ///< typedef for a map from block id to number of instances
    typedef std::map<UINT, BlockInstanceLimitMap>               GpuBlockInstanceLimitMap;           ///< typedef for a map from GPU Index to a BlockInstanceLimitMap
    static const unsigned int                                   ms_activeGpuCF = 0xffffffff;        ///< CF/ACF active GPU
    static GpuBlockInstanceLimitMap                             ms_blockInstanceLimits;             ///< map of block instance counts per gpu device
    IAmdDxExtPerfExperiment*                                    m_pExperiment;                      ///< The experiment related to this sample
    IAmdDxExtPerfCounter**                                      m_ppCounters;                       ///< The collection of active perf counters
    ID3D11Counter*                                              m_pGPUTimeCounter;                  ///< Timestamp queries are treated as much like regular counters as possible
                                                                                                    ///  to minimize code impact, and maximize shared code.
                                                                                                    ///  Special case processing added where required.
    DX11GPAContext*                                             m_pDx11GpaContext;                  ///< Cache the context pointer
    unsigned int                                                m_gpuToCheckBlockLimits;            ///< index of the gpu to use to check block limits
};

#endif  // _DX11_GPA_SAMPLE_H_
