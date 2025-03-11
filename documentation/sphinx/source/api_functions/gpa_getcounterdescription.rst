.. Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.

GpaGetCounterDescription
@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterDescription(
        GpaSessionId session_id,
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

    "``session_id``", "Unique identifier of a previously-created session."
    "``index``", "The index of the counter whose description is needed. Must lie between 0 and (GpaGetNumCounters result - 1)."
    "``description``", "The address which will hold the description upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter description was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``description`` parameter is NULL.
    | The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound If the supplied ``session_id`` is invalid."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "The counter description could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
