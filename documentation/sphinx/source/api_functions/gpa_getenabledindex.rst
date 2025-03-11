.. Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.

GpaGetEnabledIndex
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetEnabledIndex(
        GpaSessionId session_id,
        GpaUInt32 enabled_number,
        GpaUInt32* enabled_counter_index);

Description
%%%%%%%%%%%

Gets the counter index for an enabled counter. This is meant to be used with
GpaGetNumEnabledCounters. Once you determine the number of enabled counters,
you can use GpaGetEnabledIndex to determine which counters are enabled.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``enabled_number``", "The number of the enabled counter to get the counter index for. Must lie between 0 and (GpaGetNumEnabledCounters result - 1)."
    "``enabled_counter_index``", "The value that will hold the index of the counter upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter index was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``session_id`` parameter is NULL.
    | The supplied ``enabled_counter_index`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied session's parent context is not currently open."
    "kGpaStatusErrorIndexOutOfRange", "The supplied ``enabled_number`` is out of range."
    "kGpaStatusErrorFailed", "The counter index could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
