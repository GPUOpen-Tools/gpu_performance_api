//==============================================================================
// Copyright (c) 2018-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA ROCm Context declarations
//==============================================================================

#ifndef _ROCM_GPA_CONTEXT_H_
#define _ROCM_GPA_CONTEXT_H_

// HSA
#include "HSARTModuleLoader.h"

// GPA Common
#include "GPUPerfAPI-ROCm.h"
#include "GPAContext.h"

class ROCmGPASample;  // forward Declaration

/// Class for ROCm GPA Context
class ROCmGPAContext : public GPAContext
{
public:
    /// Constructor
    /// \param[in] pHwInfo the hardware info used to create the context
    /// \param[in] contextFlags the flags used to create the context
    ROCmGPAContext(GPA_HWInfo& pHwInfo, GPA_OpenContextFlags contextFlags);

    /// Destructor
    ~ROCmGPAContext();

    /// \copydoc IGPAContext::CreateSession()
    GPA_SessionId CreateSession(GPA_Session_Sample_Type sampleType) override;

    /// \copydoc IGPAContext::DeleteSession()
    bool DeleteSession(GPA_SessionId sessionId) override;

    /// \copydoc IGPAContext::GetMaxGPASessions()
    gpa_uint32 GetMaxGPASessions() const override;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// \copydoc IGPAContext::OpenCounters()
    bool OpenCounters() override;

    /// Initializes the ROCm context
    /// \param[in] pROCmContext the ROCm context struct for this context
    /// \return true if initialization is successful otherwise false
    bool Initialize(GPA_ROCm_Context* pROCmContext);

    /// Get the accessor of the ROCm Context
    /// \return the ROCm Context
    GPA_ROCm_Context& ROCmContext();

    /// Gets the ROCm sample which has been started from the user/client
    /// \return pointer to ROCm sample
    ROCmGPASample* GetRunningROCmSample() const;

    /// Sets the ROCm sample
    /// \param[in] pRunningROCmSample pointer to ROCm sample
    /// \return false if current value of running sample is null otherwise false
    bool SetRunningROCmSample(ROCmGPASample* pRunningROCmSample);

    /// Sets the running sample to null
    void CloseROCmSample();

    /// \copydoc IGPAContext::SetStableClocks()
    GPA_Status SetStableClocks(bool useProfilingClocks) override;

private:
    GPA_ROCm_Context m_rocmContext;         ///< ROCm Context object for this context
    ROCmGPASample*   m_pRunningROCmSample;  ///< ROCm sample for which begin had been called
};

#endif  // _ROCM_GPA_CONTEXT_H_
