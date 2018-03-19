.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetCounterIndex
@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetCounterIndex(
        GPA_ContextId contextId,
        const char* pCounterName,
        gpa_uint32* pIndex);

Description
%%%%%%%%%%%

Gets index of a counter given its name (case insensitive).

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``contextId``", "Unique identifier of a previously-opened context."
    "``pCounterName``", "The name of the counter whose index is needed."
    "``pIndex``", "The address which will hold the index upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The counter index was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``pCounterName`` parameter is NULL.
    | The supplied ``pIndex`` parameter is NULL.
    | The supplied ``contextId`` parameter is NULL."
    "GPA_STATUS_ERROR_CONTEXT_NOT_FOUND", "The supplied ``contextId`` parameter was not recognized as a previously-opened context identifier."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_COUNTER_NOT_FOUND", "The specified counter could not be found."
