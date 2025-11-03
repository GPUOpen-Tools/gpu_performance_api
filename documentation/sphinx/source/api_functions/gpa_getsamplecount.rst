GpaGetSampleCount
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetSampleCount(
        GpaSessionId session_id,
        GpaUInt32* sample_count);

Description
%%%%%%%%%%%

Gets the number of samples created for the specified session. This is useful if
samples are conditionally created and a count is not kept. The session must have
been ended by GpaEndSession before calling this function.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``sample_count``", "The value which will hold the number of samples contained within the session upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The sample count was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``session_id`` parameter is NULL.
    | The supplied ``sample_count`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorSessionNotEnded", "The session has not been ended. A session must have been ended with GpaEndSession prior to querying the number of samples."
    "kGpaStatusErrorFailed", "| The sample count could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
