.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetCounterUUID
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetCounterUuid(
        GPA_ContextId contextId,
        gpa_uint32 index,
        GPA_UUID* pCounterUuid);

Description
%%%%%%%%%%%

Gets the UUID type of the specified counter. The UUID can be used to uniquely
identify the counter. A counter's unique identifier can change from one version
of GPA to the next.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``contextId``", "Unique identifier of a previously-opened context."
    "``index``", "The index of the counter whose UUID is needed. Must lie between 0 and (GPA_GetNumCounters result - 1)."
    "``pCounterUuid``", "The address which will hold the UUID upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The counter UUID was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``pCounterUuid`` parameter is NULL.
    | The supplied ``contextId`` parameter is NULL."
    "GPA_STATUS_ERROR_CONTEXT_NOT_FOUND", "The supplied ``contextId`` parameter was not recognized as a previously-opened context identifier."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE", "The specified index is out of range."
    "GPA_STATUS_ERROR_FAILED", "The counter UUID could not be retrieved."
