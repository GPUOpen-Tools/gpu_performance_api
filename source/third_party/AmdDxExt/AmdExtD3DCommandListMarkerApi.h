/* Copyright (C) 2017-2026 Advanced Micro Devices, Inc. All rights reserved. */

/**
***********************************************************************************************************************
* @file  AmdExtD3DCommandListMarkerApi.h
* @brief
*    AMD D3D Command List Marker API include file.
***********************************************************************************************************************
*/

#pragma once

#include <unknwn.h>

/**
***********************************************************************************************************************
* @brief D3D Command List Marker extension API object
***********************************************************************************************************************
*/
interface __declspec(uuid("735F1F3A-555D-4F70-AB92-7DB4A3AB1D28"))
IAmdExtD3DCommandListMarker : public IUnknown
{
public:
    /// Set a command list marker to indicate the beginning of a rendering pass
    virtual VOID PushMarker(const char* pMarker) = 0;
    /// Set a command list marker to indicate the end of the current rendering pass
    virtual VOID PopMarker() = 0;
    /// Set a command list marker to indicate a rendering activity
    virtual VOID SetMarker(const char* pMarker) = 0;
};
