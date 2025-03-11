.. Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.

GpaGetCounterIndex
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterIndex(
        GpaSessionId session_id,
        const char* counter_name,
        GpaUInt32* index);

Description
%%%%%%%%%%%

Gets index of a counter given its name (case insensitive).

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``counter_name``", "The name of the counter whose index is needed."
    "``index``", "The address which will hold the index upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter index was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``counter_name`` parameter is NULL.
    | The supplied ``index`` parameter is NULL.
    | The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound If the supplied ``session_id`` is invalid."
    "kGpaStatusErrorCounterNotFound", "The specified counter could not be found."
    "kGpaStatusErrorException", "Exception occurred."
