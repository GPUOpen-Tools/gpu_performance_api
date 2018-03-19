//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL GPA Sample Header
//==============================================================================

#ifndef _GL_GPA_SAMPLE_H_
#define _GL_GPA_SAMPLE_H_

#include <vector>

#include "GPASample.h"
#include "GLGPAPass.h"

/// Class for GL Specific sample
class GLGPASample : public GPASample
{
public:

    /// Constructor
    /// \param[in] pPass GPA Pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleType gpa sample type
    /// \param[in] sampleId user-supplied sample id
    GLGPASample(GPAPass* pPass,
                IGPACommandList* pCmdList,
                GpaSampleType sampleType,
                ClientSampleId sampleId);

    /// Delete default constructor
    GLGPASample() = delete;

    /// Destructor
    ~GLGPASample();

    /// \copydoc GPASample::UpdateResults
    bool UpdateResults() override final;

    /// \copydoc GPASample::BeginRequest
    bool BeginRequest() override final;

    /// \copydoc GPASample::EndRequest
    bool EndRequest() override final;

    /// \copydoc GPASample::ReleaseCounters
    void ReleaseCounters() override final;

private:

    /// Copies the result from the driver to sample result buffer
    /// \return true upon successful operation otherwise false
    bool CopyResults();

    /// Creates the GPU time query
    /// \return true upon successful operation otherwise false
    bool CreateGPUTimeQuery();

    /// Deletes the GPU time query
    /// \return true upon successful operation otherwise false
    bool DeleteGPUTimeQueries();

    /// Union
    union SampleDataBuffer
    {
        /// constructor
        SampleDataBuffer():
            m_glPerfMonitorId(0u)
        {
            m_gpuTimeQuery[0] = m_gpuTimeQuery[1] = 0u;
        }

        GLuint                        m_gpuTimeQuery[2];        ///< The Query used to get GPUTime results
        GLPerfMonitorId               m_glPerfMonitorId;        ///< Sample perf monitor Id for hardware counters
    };

    GLGPAPass*                      m_pGlGpaPass;               ///< Cache the GPA pass pointer
    SampleDataBuffer                m_sampleDataBuffer;         ///< Buffer for getting data from driver
};

#endif  // _GL_GPA_SAMPLE_H_
