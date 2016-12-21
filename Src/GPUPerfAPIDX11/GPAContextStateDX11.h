//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA_ContextStateDX11 declaration
//==============================================================================


#ifndef _GPA_CONTEXTSTATE_DX11_H_
#define _GPA_CONTEXTSTATE_DX11_H_

#include "../GPUPerfAPI-Common/GPAContextState.h"
#include <d3d11.h>

/// Maintains the available DX11 internal counters for the currently installed hardware.
class GPA_ContextStateDX11 : public GPA_ContextState
{
public:
    /// Initializes an instance of the GPA_ContextStateDX11 class.
    GPA_ContextStateDX11();

    /// Destroy this instance of GPA_ContextStateDX11
    virtual ~GPA_ContextStateDX11();

    /// Access to the D3D11 device context
    ///
    /// \note This method does _not_ increase the device context ref count
    /// \return Pointer to the D3D11 device context
    inline ID3D11DeviceContext* DX11DeviceContext()
    {
        return m_pDeviceContext;
    }

    /// Set the D3D11 device context
    ///
    /// \param[in] pDeviceContext The D3D11 device context
    void SetDX11DeviceContext(ID3D11DeviceContext* pDeviceContext);

private:
    /// Pointer to the device context to retrieve counter data from
    ID3D11DeviceContext* m_pDeviceContext;
};

#endif // _GPA_CONTEXTSTATE_DX11_H_
