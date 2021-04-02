.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetCounterGroup
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterGroup(
        GpaContextId context_id,
        GpaUInt32 index,
        const char** group);

Description
%%%%%%%%%%%

Gets the group of the specified counter.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``index``", "The index of the counter whose group is needed. Must lie between 0 and (GpaGetNumCounters result - 1)."
    "``group``", "The address which will hold the group upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter group was successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``group`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "The counter group could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
