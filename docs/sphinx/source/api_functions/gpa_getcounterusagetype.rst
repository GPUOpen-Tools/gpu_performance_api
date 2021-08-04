.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetCounterUsageType
@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterUsageType(
        GpaContextId context_id,
        GpaUInt32 index,
        GpaUsageType* counter_usage_type);

Description
%%%%%%%%%%%

Gets the usage type of the specified counter. The usage type indicates the
units used for the counter.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``index``", "The index of the counter whose usage type is needed. Must lie between 0 and (GpaGetNumCounters result - 1)."
    "``counter_usage_type``", "The address which will hold the usage type upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter usage type was successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``counter_usage_type`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "The counter usage type could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."