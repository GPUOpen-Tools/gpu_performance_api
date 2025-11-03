/* Copyright (C) 2012-2025 Advanced Micro Devices, Inc. All rights reserved. */

/**
***************************************************************************************************
* @file
*   AmdDxExtASICInfoApi.h
*
* @brief
*   AMD D3D Ext ASIC Info API include file.
*   This is the main include file for apps using ASIC Info extension.
*
***************************************************************************************************
*/

#ifndef _AMDDXEXTASICINFOAPI_H_
#define _AMDDXEXTASICINFOAPI_H_

#include "AmdDxExtApi.h"
#include "AmdDxExtIface.h"
#include "AmdDxExtASICInfo.h"

const unsigned int AmdDxASICInfoMajorVersion = 2;
const unsigned int AmdDxASICInfoMinorVersion = 0;
// ASIC Info extension ID passed to IAmdDxExt::GetExtInterface()
const unsigned int AmdDxExtASICInfoID = 9;

/**
***************************************************************************************************
* @brief
*   Abstract ASIC Info extension interface class
*
***************************************************************************************************
*/
class IAmdDxExtASICInfo : public IAmdDxExtInterface
{

public:
    virtual HRESULT GetExtensionVersion(AmdDxExtVersion* pExtVer) = 0;

    virtual HRESULT GetInfoData(const AmdDxASICInfoParam* pParam) = 0;

};

#endif
