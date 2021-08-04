.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetCounterDataType
@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterDataType(
        GpaContextId context_id,
        GpaUInt32 index,
        GPA_Data_Type* counter_data_type);

Description
%%%%%%%%%%%

Gets the data type of the specified counter.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``index``", "The index of the counter whose data type is needed. Must lie between 0 and (GpaGetNumCounters result - 1)."
    "``counter_data_type``", "The address which will hold the data type upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter data type was successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``counter_data_type`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "The counter data type could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
