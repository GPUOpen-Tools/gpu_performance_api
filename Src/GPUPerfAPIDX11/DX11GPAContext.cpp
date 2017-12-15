//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA DX11 Context Implementation
//==============================================================================

#include "DX11GPAContext.h"
#include "GPAUniqueObject.h"
#include "DX11GPAImplementor.h"

DX11GPAContext::DX11GPAContext(ID3D11Device* pD3D11Device,
                               GPA_HWInfo& pHwInfo,
                               GPA_OpenContextFlags contextFlags):
    GPAContext(pHwInfo, contextFlags)
{
    m_pD3D11Device = pD3D11Device;
    m_pD3D11Device->AddRef();
    m_pDxExt = nullptr;
    m_pDxExtPE = nullptr;
}

DX11GPAContext::~DX11GPAContext()
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
}

GPA_SessionId DX11GPAContext::CreateSession()
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    return nullptr;
}

bool DX11GPAContext::DeleteSession(GPA_SessionId pSessionId)
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    UNREFERENCED_PARAMETER(pSessionId);
    return true;
}

gpa_uint32 DX11GPAContext::GetMaxGPASessions() const
{
    // reported maximum latency was 4 for r6xx cards
    // had issues with this value. Had to switch to 32
    return 32;
}

bool DX11GPAContext::DoesSessionExist(GPA_SessionId pSessionId) const
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    UNREFERENCED_PARAMETER(pSessionId);
    return true;
}

GPA_API_Type DX11GPAContext::GetAPIType() const
{
    return GPA_API_DIRECTX_11;
}

bool DX11GPAContext::Initialize()
{
    bool success = OpenCounters() && InitializeProfileAMDExtension();

    if (success)
    {
        SetAsOpened(true);
    }

    return success;
}

IAmdDxExt* DX11GPAContext::GetAmdDxExtension() const
{
    return m_pDxExt;
}

IAmdDxExtPerfProfile* DX11GPAContext::GetAmdProfileExtension() const
{
    return m_pDxExtPE;
}

ID3D11Device* DX11GPAContext::GetDevice() const
{
    return m_pD3D11Device;
}

bool DX11GPAContext::InitializeProfileAMDExtension()
{
    bool success = false;

    PFNAmdDxExtCreate11 dx11ExtensionFunc = DX11GPAImplementor::Instance()->GetAmdExtFuncPointer();

    if (nullptr != dx11ExtensionFunc)
    {
        HRESULT hr = dx11ExtensionFunc(m_pD3D11Device, &m_pDxExt);

        if (S_OK == hr)
        {
            m_pDxExtPE = static_cast<IAmdDxExtPerfProfile*>(m_pDxExt->GetExtInterface(AmdDxExtPerfProfileID));

            if (nullptr != m_pDxExtPE)
            {
                success = true;
            }
            else
            {
                m_pDxExt->Release();
                m_pDxExt = nullptr;
                GPA_LogError("Unable to initialize because the driver does not support the PerfProfile extension.");
            }
        }
        else
        {
            GPA_LogError("Unable to create DX11 extension.");
        }
    }
    else
    {
        GPA_LogError("AMD extension function is not initialized");
    }

    return success;
}

