.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetCounterName
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetCounterName(
        GPA_ContextId contextId,
        gpa_uint32 index,
        const char** ppName);

Description
%%%%%%%%%%%

Gets the name of the specified counter.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``contextId``", "Unique identifier of a previously-opened context."
    "``index``", "The index of the counter name to query. Must lie between 0 and (GPA_GetNumCounters result - 1)."
    "``ppName``", "The address which will hold the name upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The counter name was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``ppName`` parameter is NULL.
    | The supplied ``contextId`` parameter is NULL."
    "GPA_STATUS_ERROR_CONTEXT_NOT_FOUND", "The supplied ``contextId`` parameter was not recognized as a previously-opened context identifier."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE", "The specified index is out of range."
    "GPA_STATUS_ERROR_FAILED", "The counter name could not be retrieved."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."