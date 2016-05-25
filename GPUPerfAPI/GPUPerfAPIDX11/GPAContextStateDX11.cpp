//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA_ContextStateDX11 implementation
//==============================================================================

#include "GPAContextStateDX11.h"

GPA_ContextStateDX11::GPA_ContextStateDX11()
    :
    m_pDeviceContext(nullptr)
{
}

GPA_ContextStateDX11::~GPA_ContextStateDX11()
{
    if (nullptr != m_pDeviceContext)
    {
        m_pDeviceContext->Release();
    }
}

void GPA_ContextStateDX11::SetDX11DeviceContext(ID3D11DeviceContext* pDeviceContext)
{
    if (pDeviceContext != m_pDeviceContext)
    {
        if (nullptr != m_pDeviceContext)
        {
            m_pDeviceContext->Release();
        }

        m_pDeviceContext = pDeviceContext;

        if (nullptr != pDeviceContext)
        {
            m_pDeviceContext->AddRef();
        }
    }
}
