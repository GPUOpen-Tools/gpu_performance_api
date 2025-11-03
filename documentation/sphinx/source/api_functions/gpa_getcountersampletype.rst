GpaGetCounterSampleType
@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetCounterSampleType(
        GpaSessionId session_id,
        GpaUInt32 index,
        GpaCounterSampleType* counter_sample_type);

Description
%%%%%%%%%%%

Gets the sample type of the specified counter.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``index``", "The index of the counter whose sample type is needed. Must lie between 0 and (GpaGetNumCounters result - 1)."
    "``counter_sample_type``", "The address which will hold the sample type upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter sample type was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``counter_sample_type`` parameter is NULL.
    | The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound If the supplied ``session_id`` is invalid."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "The counter sample type could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."

