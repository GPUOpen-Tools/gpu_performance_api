//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 GPA Pass Object Header
//==============================================================================

#ifndef _DX12_GPA_PASS_H_
#define _DX12_GPA_PASS_H_

// AMD Ext
#pragma warning (push)
#pragma warning (disable: 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning (pop)

// GPA Common
#include "GPAPass.h"
#include "IGPACommandList.h"

class DX12GPACommandList;               // forward declaration

/// Class for DirectX 12 gpa pass
class DX12GPAPass : public GPAPass
{
public:

    /// Constructor
    DX12GPAPass(IGPASession* pGpaSession,
                PassIndex passIndex,
                GPACounterSource counterSource,
                IGPACounterScheduler* pCounterScheduler,
                const IGPACounterAccessor* pCounterAccessor);

    /// \copydoc GPAPass::CreateAPISpecificSample
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList,
                                       GpaSampleType sampleType,
                                       ClientSampleId clientSampleId) override final;

    /// \copydoc GPAPass::IsComplete
    bool IsComplete() const override final;

    /// \copydoc GPAPass::UpdateResults
    bool UpdateResults() override final;

    /// \copydoc GPAPass::CreateCommandList
    IGPACommandList* CreateCommandList(void* pCmd, GPA_Command_List_Type cmdType) override final;

    /// \copydoc GPAPass::EndSample
    bool EndSample(IGPACommandList* pDx12GpaCmdList) override final;

    /// Adds the secondary sample to the primary command list
    /// \param[in] clientSamples list of the client samples
    /// \param[in] pDx12PrimaryGpaCmdList DirectX 12 gpa primary command list object pointer
    /// \param[in] pDx12SecondaryGpaCmdList DirectX 12 gpa secondary command list object pointer
    bool CopySecondarySamples(std::vector<ClientSampleId> clientSamples,
                              DX12GPACommandList* pDx12PrimaryGpaCmdList,
                              DX12GPACommandList* pDx12SecondaryGpaCmdList);

    /// Returns the sample config for the set of counters in the pass
    /// \return Amd extension sample config for the set of counters in the pass
    AmdExtGpaSampleConfig GetAmdExtSampleConfig() const;

    /// Destructor
    ~DX12GPAPass();

private:

    /// Initializes the sample config for the pass if pass counter source is hardware
    void InitializeSampleConfig();

    /// Removes the irrelevant resources
    void ResetPass() const;

    AmdExtGpaSampleConfig                                   m_amdExtsampleConfig;                   ///< AMD Extension configuration for hardware samples
    bool                                                    m_isSampleConfigInitialized;            ///< flag indicating whether the sample config is initialized or not for the hardware samples
};

#endif // _DX12_GPA_PASS_H_
