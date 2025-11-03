//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX11 GPA Sample Header
//==============================================================================

#ifndef GPU_PERF_API_DX11_DX11_GPA_SAMPLE_H_
#define GPU_PERF_API_DX11_DX11_GPA_SAMPLE_H_

#include "gpu_perf_api_common/gpa_sample.h"

#include "gpu_perf_api_dx11/dx11_gpa_context.h"

/// @brief Class for DX11 Specific sample.
class Dx11GpaSample : public GpaSample
{
public:
    /// @brief Constructor.
    /// @param [in] pass GPA Pass object.
    /// @param [in] cmd_list GPA command list.
    /// @param [in] sample_type GPA sample type.
    /// @param [in] sample_id User supplied sample id.
    Dx11GpaSample(GpaPass* pass, IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id);

    /// @brief Delete default constructor.
    Dx11GpaSample() = delete;

    /// @brief Destructor.
    ~Dx11GpaSample();

    /// @copydoc GpaSample::UpdateResults()
    bool UpdateResults() override final;

    /// @copydoc GpaSample::BeginRequest()
    bool BeginRequest() override final;

    /// @copydoc GpaSample::EndRequest()
    bool EndRequest() override final;

    /// @copydoc GpaSample::ReleaseCounters()
    void ReleaseCounters() override final;

private:
    /// @brief Creates the sample experiment.
    ///
    /// @return True upon successful operation otherwise false.
    bool CreateSampleExperiment();

    /// @brief Creates the counters and add it to the experiment.
    ///
    /// @return true upon successful operation otherwise false.
    bool CreateAndAddCounterToExperiment();

    /// @brief Populates the result of the sample from the driver.
    ///
    /// @return True upon successful operation otherwise false
    bool PopulateResult();

    /// @brief Release the non-GPA resources of the sample.
    void ReleaseSampleResources();

    IAmdDxExtPerfExperiment* amd_dx_ext_perf_experiment_;  ///< The experiment related to this sample.
    IAmdDxExtPerfCounter**   amd_dx_ext_perf_counters_;    ///< The collection of active performance counters.

    /// Time-stamp queries are treated as much like regular counters as possible to minimize code impact, and maximize shared code.
    /// Special case processing added where required.
    ID3D11Counter* gpu_time_counter_;
};

#endif
