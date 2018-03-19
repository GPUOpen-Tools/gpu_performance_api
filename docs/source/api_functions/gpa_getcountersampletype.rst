.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetCounterSampleType
@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetCounterSampleType(
        GPA_ContextId contextId,
        gpa_uint32 index,
        GPA_Counter_Sample_Type* pCounterSampleType);

Description
%%%%%%%%%%%

Gets the sample type of the specified counter.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``contextId``", "Unique identifier of a previously-opened context."
    "``index``", "The index of the counter whose sample type is needed. Must lie between 0 and (GPA_GetNumCounters result - 1)."
    "``pCounterSampleType``", "The address which will hold the sample type upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The counter sample type was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``pCounterSampleType`` parameter is NULL.
    | The supplied ``contextId`` parameter is NULL."
    "GPA_STATUS_ERROR_CONTEXT_NOT_FOUND", "The supplied ``contextId`` parameter was not recognized as a previously-opened context identifier."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE", "The specified index is out of range."
    "GPA_STATUS_ERROR_FAILED", "The counter sample type could not be retrieved."

