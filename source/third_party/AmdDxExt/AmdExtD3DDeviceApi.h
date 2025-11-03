/* Copyright (C) 2016-2025 Advanced Micro Devices, Inc. All rights reserved. */

#pragma once
#include "unknwn.h"
#include <d3d12.h>
#include "AmdExtD3DDeviceApi.h"

/**
***********************************************************************************************************************
* @brief AMD extension structure enumeration supported by the driver
***********************************************************************************************************************
*/
enum AmdExtD3DStructType : UINT
{
    AmdExtD3DStructUnknown,         ///< Unsupported
    AmdExtD3DStructPipelineState,   ///< Pipeline state extension structure (AmdExtD3DPipelineCreateInfo)
};

/**
***********************************************************************************************************************
* @brief Extension create info base structure
***********************************************************************************************************************
*/
struct AmdExtD3DCreateInfo
{
    AmdExtD3DStructType type;       ///< AMD create info structure. Must be one of the supported types.
    void*               pNext;      ///< Pointer to a valid AMD structure. Must be nullptr if using base version.
                                    ///  Structures defined by multiple extensions (or versions) may be chained
                                    ///  together using this field. When chaining, the driver will process the chain
                                    ///  starting from the base parameter onwards.
};

/**
***********************************************************************************************************************
* @brief Extended pipeline flags
***********************************************************************************************************************
*/
struct AmdExtD3DPipelineFlags
{
    unsigned int depthBoundsTestEnable : 1;     ///< Enable depth bounds testing
    unsigned int reserved              : 31;    ///< Reserved bits (must be 0)
};

/**
***********************************************************************************************************************
* @brief Extended pipeline state create info structure
***********************************************************************************************************************
*/
struct AmdExtD3DPipelineCreateInfo : AmdExtD3DCreateInfo
{
    AmdExtD3DPipelineFlags flags;  ///< Pipeline flags
};

/**
***********************************************************************************************************************
* @brief Extension device API object
***********************************************************************************************************************
*/
interface __declspec(uuid("8104C0FC-7413-410F-8E83-AA617E908648"))
IAmdExtD3DDevice : public IUnknown
{
public:
    virtual HRESULT CreateGraphicsPipelineState(
        const AmdExtD3DCreateInfo*                  pAmdExtCreateInfo,
        const D3D12_GRAPHICS_PIPELINE_STATE_DESC*   pDesc,
        REFIID                                      riid,
        void**                                      ppPipelineState) = 0;
};

/**
***********************************************************************************************************************
* @brief Version 1 extension device API object
***********************************************************************************************************************
*/
interface __declspec(uuid("4BBCAF68-EAF7-4FA4-B653-CB458C334A4E"))
IAmdExtD3DDevice1 : public IAmdExtD3DDevice
{
public:
    virtual VOID PushMarker(ID3D12GraphicsCommandList* pGfxCmdList, const char* pMarker) = 0;
    virtual VOID PopMarker(ID3D12GraphicsCommandList* pGfxCmdList) = 0;
    virtual VOID SetMarker(ID3D12GraphicsCommandList* pGfxCmdList, const char* pMarker) = 0;
};
