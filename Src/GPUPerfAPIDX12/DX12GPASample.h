//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 GPA Sample Header
//==============================================================================

#ifndef _DX12_GPA_SAMPLE_H_
#define _DX12_GPA_SAMPLE_H_

#include "GPASample.h"

/// Class for DX12 Specific sample
class DX12GPASample : public GPASample
{
public:

    /// Constructor
    /// \param[in] pPass GPA Pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleType gpa sample type
    /// \param[in] sampleId user-supplied sample id
    DX12GPASample(GPAPass* pPass,
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

private:

    /// Populates the sample result
    /// \return result of the sample
    GPASampleResult* PopulateSampleResult();

    /// Returns the result from the driver
    /// \param[in] sampleDataSize size of result for the sample in bytes
    /// \param[in, out] pResultBuffer pointer to the buffer where result will be copied
    /// \return true if copying of data was successful otherwise false
    bool CopyResult(size_t sampleDataSize, void* pResultBuffer) const;
};

#endif  // _DX12_GPA_SAMPLE_H_
