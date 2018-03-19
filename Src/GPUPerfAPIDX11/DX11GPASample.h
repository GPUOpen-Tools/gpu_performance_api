//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
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

    /// Constructor
    /// \param[in] pPass GPA Pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleType gpa sample type
    /// \param[in] sampleId user-supplied sample id
    DX11GPASample(GPAPass* pPass,
                  IGPACommandList* pCmdList,
                  GpaSampleType sampleType,
                  ClientSampleId sampleId);

    /// Delete default constructor
    DX11GPASample() = delete;

    /// Destructor
    ~DX11GPASample();

    /// \copydoc GPASample::UpdateResults
    bool UpdateResults() override final;

    /// \copydoc GPASample::BeginRequest
    bool BeginRequest() override final;

    /// \copydoc GPASample::EndRequest
    bool EndRequest() override final;

    /// \copydoc GPASample::ReleaseCounters
    void ReleaseCounters() override final;

private:

    /// Creates the sample experiment
    /// \return true upon successful operation otherwise false
    bool CreateSampleExperiment();

    /// Creates the counters and add it to the experiment
    /// \return true upon successful operation otherwise false
    bool CreateAndAddCounterToExperiment();

    /// Populates the result of the sample from the driver
    /// \return true upon successful operation otherwise false
    bool PopulateResult();

    /// Release the non-GPA resources of the sample
    void ReleaseSampleResources();

    IAmdDxExtPerfExperiment* m_pExperiment;     ///< The experiment related to this sample
    IAmdDxExtPerfCounter**   m_ppCounters;      ///< The collection of active perf counters
    ID3D11Counter*           m_pGPUTimeCounter; ///< Timestamp queries are treated as much like regular counters as possible to minimize code impact, and maximize shared code. Special case processing added where required.
};

#endif  // _DX11_GPA_SAMPLE_H_
