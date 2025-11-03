//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Sample Header
//==============================================================================

#ifndef GPU_PERF_API_DX12_DX12_GPA_SAMPLE_H_
#define GPU_PERF_API_DX12_DX12_GPA_SAMPLE_H_

#include "gpu_perf_api_common/gpa_sample.h"

/// @brief Class for DX12 Specific sample.
class Dx12GpaSample : public GpaSample
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] pass GPA Pass object.
    /// @param [in] cmd_list GPA command list.
    /// @param [in] sample_type GPA sample type.
    /// @param [in] sample_id User supplied sample id.
    Dx12GpaSample(GpaPass* pass, IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id);

    /// @copydoc GpaSample::UpdateResults()
    bool UpdateResults() override final;

    /// @copydoc GpaSample::BeginRequest()
    bool BeginRequest() override final;

    /// @copydoc GpaSample::EndRequest()
    bool EndRequest() override final;

    /// @copydoc GpaSample::ReleaseCounters()
    void ReleaseCounters() override final;

private:
    /// @brief Populates the sample result.
    ///
    /// @return The result of the sample.
    GpaSampleResult* PopulateSampleResult();

    /// @brief Returns the result from the driver.
    ///
    /// @param [in] sample_data_size Size of result for the sample in bytes.
    /// @param [in, out] result_buffer Pointer to the buffer where result will be copied.
    ///
    /// @return True if copying of data was successful otherwise false.
    bool CopyResult(size_t sample_data_size, void* result_buffer) const;
};

#endif
