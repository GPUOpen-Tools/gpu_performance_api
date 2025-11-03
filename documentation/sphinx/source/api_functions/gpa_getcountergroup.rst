GpaGetCounterGroup
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterGroup(
        GpaSessionId session_id,
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

    "``session_id``", "Unique identifier of a previously-created session."
    "``index``", "The index of the counter whose group is needed. Must lie between 0 and (GpaGetNumCounters result - 1)."
    "``group``", "The address which will hold the group upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter group was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``group`` parameter is NULL.
    | The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound If the supplied ``session_id`` is invalid."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "The counter group could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
