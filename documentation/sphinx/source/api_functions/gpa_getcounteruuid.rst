GpaGetCounterUuid
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterUuid(
        GpaSessionId session_id,
        GpaUInt32 index,
        GpaUuid* counter_uuid);

Description
%%%%%%%%%%%

Gets the UUID type of the specified counter. The UUID can be used to uniquely
identify the counter. A counter's unique identifier can change from one version
of GPA to the next.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``index``", "The index of the counter whose UUID is needed. Must lie between 0 and (GpaGetNumCounters result - 1)."
    "``counter_uuid``", "The address which will hold the UUID upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter UUID was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``counter_uuid`` parameter is NULL.
    | The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound If the supplied ``session_id`` is invalid."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "The counter UUID could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
