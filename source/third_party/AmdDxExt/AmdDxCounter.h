/* Copyright (C) 2016-2025 Advanced Micro Devices, Inc. All rights reserved. */
/**
***************************************************************************************************
* @file  amddxcounter.h
* @brief
*    AMD D3D counter include file. This file contains definitions of device dependent counters
*    available on AMD hardware.
***************************************************************************************************
*/

#ifndef _AMDDXCOUNTER_H_
#define _AMDDXCOUNTER_H_

#ifdef D3D10_0_DDI_BUILD_VERSION
static const UINT AMDDeviceDependentSWCounterIdStart = D3D10DDI_COUNTER_DEVICE_DEPENDENT_0;
#else
static const UINT AMDDeviceDependentSWCounterIdStart = D3D10_COUNTER_DEVICE_DEPENDENT_0;
#endif
static const UINT AMDDevicecDependentHWCounterIdOffset= 0x20000000;
static const UINT AMDDeviceDependentHWCounterIdStart = AMDDeviceDependentSWCounterIdStart |
                                                       AMDDevicecDependentHWCounterIdOffset;

/**
***************************************************************************************************
* AMDPerfCtr
***************************************************************************************************
*/
typedef union

{
    struct
    {
        UINT typeSpecific      : 24;   // The definition of these is counter-type dependent
        UINT counterType       : 5;    // Select the type of counter
        UINT isHWDeviceCounter : 1;    // Set if this is a hardware counter.
                                       // Cleared if this is a software (driver) counter
        UINT isDeviceCounter   : 1;    // The DDI requires this field to be 1 for a counter to be
                                       // interpreted as a device-dependent counter
        UINT reserved          : 1;    // Reserved bit
    } bitfields, bits;

    UINT    value;

} AMDPerfCtr;

/**
***************************************************************************************************
* The API counter Id is created by the application and is what the driver uses to setup the
* hardware counters.  The application will encode a block Id into the API counter
* using the AmdCtrEncodeApiCounter function provided below.  The block Id should be set to
* one of the AmdCtrBlockId enums.
***************************************************************************************************
*/

/**
***************************************************************************************************
* AmdApiCounterId - Enumerations which are used to set API counter Ids.
***************************************************************************************************
*/
enum AmdApiCounterId
{
    AmdStartOfPipeTimestamp,
    AmdGpuTime,

    AmdCounterIdMax,     // Not a counter Id.
};

/**
***************************************************************************************************
*   AmdCtrEncodeApiCounter
*
*   @brief
*       Use this function to encode the API counter Id. The following is an example of how
*       to use the function from an DX10 application.
*
*           ID3D10Counter* pCounterQuery;
*           D3D10_COUNTER_DESC ctrDesc = {0};
*
*           ctrDesc.Counter = (D3D10_COUNTER)AmdCtrEncodeApiCounter(AmdGpuTime);
*
*           hr = pd3dDevice->CreateCounter(&ctrDesc, &pCounterQuery);
*
*   @return
*       Returns the encoded counter id.
***************************************************************************************************
*/
static inline UINT AmdCtrEncodeApiCounter(
    AmdApiCounterId counterId)                 ///< block id from AmdCtrBlockId enum
{
    AMDPerfCtr counter;
    counter.value = 0;
    counter.bits.typeSpecific = counterId;

    return (counter.value | AMDDeviceDependentHWCounterIdStart);
}

#endif

