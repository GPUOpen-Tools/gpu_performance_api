.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetCounterName
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterName(
        GpaContextId context_id,
        GpaUInt32 index,
        const char** name);

Description
%%%%%%%%%%%

Gets the name of the specified counter.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``index``", "The index of the counter name to query. Must lie between 0 and (GpaGetNumCounters result - 1)."
    "``name``", "The address which will hold the name upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter name was successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``name`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "The counter name could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."