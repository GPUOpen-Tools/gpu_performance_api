.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetNumCounters
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetNumCounters(
        GpaContextId context_id,
        GpaUInt32* count);

Description
%%%%%%%%%%%

Gets the number of counters available.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``count``", "The value which will hold the count upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The number of counters was successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``count`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorFailed", "The number of counters could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
