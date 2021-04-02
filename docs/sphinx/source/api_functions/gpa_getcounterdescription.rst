.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetCounterDescription
@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterDescription(
        GpaContextId context_id,
        GpaUInt32 index,
        const char** description);

Description
%%%%%%%%%%%

Gets the description of the specified counter.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``index``", "The index of the counter whose description is needed. Must lie between 0 and (GpaGetNumCounters result - 1)."
    "``description``", "The address which will hold the description upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter description was successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``description`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "The counter description could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
