//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA HSA Context declarations
//==============================================================================

#ifndef _HSA_GPA_CONTEXT_H_
#define _HSA_GPA_CONTEXT_H_

// std
#include <list>

// HSA
#include <hsa_ext_profiler.h>

// GPA Common
#include "GPUPerfAPI-HSA.h"
#include "GPAContext.h"

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
    GPA_SessionId CreateSession() override;

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

    /// Gets the HSA Context
    /// \return the HSA Context
    const GPA_HSA_Context& GetHSAContext() const;

    /// Gets the HSA PMU
    /// \return the HSA PMU
    const hsa_ext_tools_pmu_t GetHSAPMU() const;

private:
    GPA_HSA_Context     m_hsaContext;  ///< HSA Context obejct for this context
    hsa_ext_tools_pmu_t m_hsaPmu;      ///< HSA PMU for the current device
};

#endif // _HSA_GPA_CONTEXT_H_
