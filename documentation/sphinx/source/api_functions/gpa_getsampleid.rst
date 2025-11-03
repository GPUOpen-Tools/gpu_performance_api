GpaGetSampleId
@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetSampleId(
        GpaSessionId session_id,
        GpaUInt32 index,
        GpaUInt32* sample_id);

Description
%%%%%%%%%%%

Gets the sample id of the sample with the specified index. This is useful if
sample ids are either non-zero-based or non-consecutive.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``index``", "Zero-based index of the sample whose sample id is needed. Must lie between 0 and (GpaGetSampleCount result - 1)."
    "``sample_id``", "The value that will hold the id of the sample upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The sample id was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``session_id`` parameter is NULL.
    | The supplied ``sample_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorSessionNotStarted", "The session has not been started."
    "kGpaStatusErrorSampleNotFound", "The specified sample could not be found."
    "kGpaStatusErrorException", "Exception occurred."