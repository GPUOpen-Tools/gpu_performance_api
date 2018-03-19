//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA HSA Context declarations
//==============================================================================

#ifndef _HSA_GPA_CONTEXT_H_
#define _HSA_GPA_CONTEXT_H_

// HSA
#include <hsa_ext_profiler.h>
#include "HSARTModuleLoader.h"

/// Pre-dispatch callback function
/// \param pRTParam the pre-dispatch callback params
/// \param pUserArgs the user arguments
void HSA_PreDispatchCallback(const hsa_dispatch_callback_t* pRTParam, void* pUserArgs);

/// Post-dispatch callback function
/// \param pRTParam the post-dispatch callback params
/// \param pUserArgs the user arguments
void HSA_PostDispatchCallback(const hsa_dispatch_callback_t* pRTParam, void* pUserArgs);

// GPA Common
#include "GPUPerfAPI-HSA.h"
#include "GPAContext.h"

class HSAGPASample;     // forward Declaration

/// Class for HSA GPA Context
class HSAGPAContext : public GPAContext
{
public:

    /// Constructor
    /// \param[in] pHwInfo the hardware info used to create the context
    /// \param[in] contextFlags the flags used to create the context
    HSAGPAContext(GPA_HWInfo& pHwInfo, GPA_OpenContextFlags contextFlags);

    /// Destructor
    ~HSAGPAContext();

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

    /// Initializes the HSA context
    /// \param[in] pHsaContext the HSA context struct for this context
    /// \return true if initialization is successful otherwise false
    bool Initialize(GPA_HSA_Context* pHsaContext);

    /// Get the accessor of the HSA Context
    /// \return the HSA Context
    GPA_HSA_Context& HSAContext();

    /// Gets the HSA PMU
    /// \return the HSA PMU
    const hsa_ext_tools_pmu_t GetHSAPMU() const;

    /// Gets the HSA sample which has been started from the user/client
    /// \return pointer to HSA sample
    HSAGPASample* GetRunningHSASample() const;

    /// Sets the HSA sample
    /// \param[in] pRunningHsaSample pointer to hsa sample
    /// \return false if current value of running sample is null otherwise false
    bool SetRunningHSASample(HSAGPASample* pRunningHsaSample);

    /// Sets the running sample to null
    void CloseHSASample();

private:
    GPA_HSA_Context     m_hsaContext;           ///< HSA Context obejct for this context
    hsa_ext_tools_pmu_t m_hsaPmu;               ///< HSA PMU for the current device
    HSAGPASample*       m_pRunningHsaSample;    ///< HSA sample for which begin had been called
};

#endif // _HSA_GPA_CONTEXT_H_
