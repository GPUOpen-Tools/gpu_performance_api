.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetEnabledIndex
@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetEnabledIndex(
        GPA_SessionId sessionId,
        gpa_uint32 enabledNumber,
        gpa_uint32* pEnabledCounterIndex);

Description
%%%%%%%%%%%

Gets the counter index for an enabled counter. This is meant to be used with
GPA_GetNumEnabledCounters. Once you determine the number of enabled counters,
you can use GPA_GetEnabledIndex to determine which counters are enabled.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``", "Unique identifier of a previously-created session."
    "``enabledNumber``", "The number of the enabled counter to get the counter index for. Must lie between 0 and (GPA_GetNumEnabledCounters result - 1)."
    "``pEnabledCounterIndex``", "The value that will hold the index of the counter upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The counter index was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``sessionId`` parameter is NULL.
    | The supplied ``pEnabledCounterIndex`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied session's parent context is not currently open."
    "GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE", "The supplied ``enabledNumber`` is out of range."
    "GPA_STATUS_ERROR_FAILED", "The counter index could not be retrieved."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
