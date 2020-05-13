.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetNumCounters
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetNumCounters(
        GPA_ContextId contextId,
        gpa_uint32* pCount);

Description
%%%%%%%%%%%

Gets the number of counters available.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``contextId``", "Unique identifier of a previously-opened context."
    "``pCount``", "The value which will hold the count upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The number of counters was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``pCount`` parameter is NULL.
    | The supplied ``contextId`` parameter is NULL."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_CONTEXT_NOT_FOUND", "The supplied ``contextId`` parameter was not recognized as a previously-opened context identifier."
    "GPA_STATUS_ERROR_FAILED", "The number of counters could not be retrieved."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
