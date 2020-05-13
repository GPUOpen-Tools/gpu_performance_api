.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_CreateSession
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_CreateSession(
        GPA_ContextId contextId,
        GPA_Session_Sample_Type sampleType,
        GPA_SessionId* pSessionId);

Description
%%%%%%%%%%%

Creates a session on the specified context. A unique session identifier will be
returned which allows counters to be enabled, samples to be measured, and
stores the results of the profile. The sample type for the session should be
specified by the caller. The requested sample types must be supported by the
supplied context. Use GPA_GetSupportedSampleTypes to determine which sample
types are supported by a context.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``contextId``", "Unique identifier of a previously-opened context."
    "``sampleType``", "The sample type which will be created for this session."
    "``pSessionId``", "On successful execution of this function, this parameter will be set to a GPA-generated unique session identifier. This value can subsequently passed to any GPA function taking a GPA_SessionId as an input parameter."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The session was successfully created."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``pSessionId`` parameter is NULL.
    | The supplied ``contextId`` parameter is NULL."
    "GPA_STATUS_ERROR_CONTEXT_NOT_FOUND", "The supplied ``contextId`` parameter was not recognized as a previously-opened context identifier."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_INVALID_PARAMETER", "The ``sampleType`` parameter has an invalid value."
    "GPA_STATUS_ERROR_INCOMPATIBLE_SAMPLE_TYPES", "The ``sampleType`` is incompatible with the context's supported sample type."
    "GPA_STATUS_ERROR_FAILED", "The session could not be created."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."

