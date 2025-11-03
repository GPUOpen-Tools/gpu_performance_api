GpaGetNumCounters
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetNumCounters(
        GpaSessionId session_id,
        GpaUInt32* count);

Description
%%%%%%%%%%%

Gets the number of counters available.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``count``", "The value which will hold the count upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The number of counters was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``count`` parameter is NULL.
    | The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound If the supplied ``session_id`` is invalid."
    "kGpaStatusErrorFailed", "The number of counters could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
