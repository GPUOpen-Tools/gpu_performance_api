GpaGetCounterName
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterName(
        GpaSessionId session_id,
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

    "``session_id``", "Unique identifier of a previously-created session."
    "``index``", "The index of the counter name to query. Must lie between 0 and (GpaGetNumCounters result - 1)."
    "``name``", "The address which will hold the name upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter name was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``name`` parameter is NULL.
    | The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound If the supplied ``session_id`` is invalid."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "The counter name could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."