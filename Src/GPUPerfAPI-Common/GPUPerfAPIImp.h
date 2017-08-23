//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Declaration of API-specific imlpementation functions
//==============================================================================

#ifndef _GPUPERFAPI_IMP_H_
#define _GPUPERFAPI_IMP_H_

#include <vector>
#include "CircularBuffer.h"

#include "GPADataRequest.h"

#include "GPAHWInfo.h"
#include "GPAICounterAccessor.h"
#include "GPASplitCounterFactory.h"

// Functions which a GPA implementation layer must support

#include "GPAContextState.h"

extern GPA_ContextState* g_pCurrentContext;

// Functions which a GPA implementation layer must support

// Startup / exit

/// Initializes GPA
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_Initialize();

/// Destroys GPA
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_Destroy();

// Context

/// Opens a context
/// \param pContext the context to open
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_OpenContext(void* pContext);

/// Closes current context
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_CloseContext();

/// Selects a context
/// \param pContext the context to select
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_SelectContext(void* pContext);

/// Creates a context
/// \param[out] ppNewContext the created context
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_CreateContext(GPA_ContextState** ppNewContext);

/// Begins a session
/// guaranteed that at least one counter active
/// g_pCurrentContext->m_currentSessionRequests has been set the the required number of passes
/// g_pCurrentContext->m_selectionID holds ID of current counter selection
/// \param[out] pSessionID the session that is created
/// \param counterSelectionChanged flag indicating if the coutner selection has changed
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_BeginSession(gpa_uint32* pSessionID, bool counterSelectionChanged);

/// Ends a session
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_EndSession();

/// Begins a pass
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_BeginPass();

/// Ends a pass
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_EndPass();

/// Begins a sample list
/// \param pSampleList the sample list on which to begin sampling
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_BeginSampleList(void* pSampleList);

/// Ends a sample list
/// \param pSampleList the sample list on which to end sampling
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_EndSampleList(void* pSampleList);

/// Begins a sample in a sample list
/// g_pCurrentContext->m_selectionID holds ID of current counter selection
/// \param sampleID the id of the sample being started
/// \param pSampleList the sample list on which to begin sampling
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_BeginSampleInSampleList(gpa_uint32 sampleID, void* pSampleList);

/// Ends a sample in a sample list
/// \param pSampleList the sample list on which to end sampling
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_EndSampleInSampleList(void* pSampleList);

/// Begins a sample
/// g_pCurrentContext->m_selectionID holds ID of current counter selection
/// \param sampleID the id of the sample being started
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_BeginSample(gpa_uint32 sampleID);

/// Ends a sample
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_EndSample();

/// Gets the default number of max sessions
/// \return The number of max sessions supported
gpa_uint32 GPA_IMP_GetDefaultMaxSessions();

/// The number of samples in between attempts to query sample requests back from the driver. This is done to free up driver resources so that it doesn't have to store the results for GPUPerfAPI.
/// \return The preferred number of samples between collections of counter results.
gpa_uint32 GPA_IMP_GetPreferredCheckResultFrequency();

/// Gets the current hw info for the specified context
/// Called by OpenContext to get current hardware info
/// \param pContext the context
/// \param[out] pHwInfo the hw info
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_GetHWInfo(void* pContext, GPA_HWInfo* pHwInfo);

/// Compares the specified hw info with the hw for the specified context
/// Called by OpenContext to get current hardware info
/// \param pContext the context
/// \param pHwInfo the hw info
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_CompareHWInfo(void* pContext, GPA_HWInfo* pHwInfo);

/// Called after the device information has been obtained and the API-specific implementation needs
/// to confirm that the hardware should be supported.
/// \param pContext the context
/// \param pHwInfo the hw info
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPA_Status GPA_IMP_VerifyHWSupport(void* pContext, GPA_HWInfo* pHwInfo);

#endif // _GPUPERFAPI_IMP_H_
