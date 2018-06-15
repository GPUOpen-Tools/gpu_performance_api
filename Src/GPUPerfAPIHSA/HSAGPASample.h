//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA GPA Sample Header
//==============================================================================

#ifndef _HSA_GPA_SAMPLE_H_
#define _HSA_GPA_SAMPLE_H_

#include <vector>

#include "GPASample.h"
#include "HSAGPAContext.h"

/// Class for HSA Specific sample
class HSAGPASample : public GPASample
{
public:

    /// Constructor
    /// \param[in] pPass GPA Pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleType gpa sample type
    /// \param[in] sampleId user-supplied sample id
    HSAGPASample(GPAPass* pPass,
                 IGPACommandList* pCmdList,
                 GpaSampleType sampleType,
                 ClientSampleId sampleId);

    /// Delete default constructor
    HSAGPASample() = delete;

    /// Destructor
    ~HSAGPASample();

    /// \copydoc GPASample::UpdateResults
    bool UpdateResults() override final;

    /// \copydoc GPASample::BeginRequest
    bool BeginRequest() override final;

    /// \copydoc GPASample::EndRequest
    bool EndRequest() override final;

    /// \copydoc GPASample::ReleaseCounters
    void ReleaseCounters() override final;

    /// Begins the sample request using hsa extensions
    /// \return true upon successful execution otherwise false
    bool BeginInternalRequest();

    /// Ends the sample request using hsa extensions
    /// \return true upon successful execution otherwise false
    bool EndInternalRequest() const;

private:

    /// Release allocated counters
    void DestroyBlockCounters();

    /// Typedef for a map from counter group index to hsa_ext_tools_counter_block_t
    typedef std::map<gpa_uint32, hsa_ext_tools_counter_block_t> HsaCounterGroupMap;

    /// structure used to store data that is needed to retrieve and store the results for a counter
    struct HSACounter
    {
        /// Initializes a new instance of the HSACounter class
        HSACounter() = default;

        /// Destructor
        virtual ~HSACounter() = default;

        gpa_uint32              m_counterID            = 0;        ///< ID that is calculated in the CounterDefinition files
        gpa_uint32              m_counterGroup         = 0;        ///< index of the counter group
        gpa_uint32              m_counterIndex         = 0;        ///< index to this counter within its group
        bool                    m_isCounterValid       = false;    ///< indicates whether the counter is a valid counter; if not value will be zero
        bool                    m_isCounterResultReady = false;    ///< indicates whether the result has been stored in the pCounterResult buffer
        hsa_ext_tools_counter_t m_hsaPerfCounter       = nullptr;  ///< Handle to the created HSA perf counter
    };

    HSAGPAContext*      m_pHSAGpaContext;     ///< Cache the context pointer
    HSACounter*         m_pHSACounters;       ///< Array of active HSA counters
    HsaCounterGroupMap  m_hsaGrpIdCtrGrpMap;  ///< Store the data to interface with HSA counters per HW block
    gpa_uint32          m_dataReadyCount;     ///< number of counters with data ready
};

#endif  // _HSA_GPA_SAMPLE_H_
