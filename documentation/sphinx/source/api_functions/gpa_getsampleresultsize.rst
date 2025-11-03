GpaGetSampleResultSize
@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetSampleResultSize(
        GpaSessionId session_id,
        GpaUInt32 sample_id,
        size_t* sample_result_size_in_bytes);

Description
%%%%%%%%%%%

Gets the result size (in bytes) for a given sample. For discrete counter
samples, the size will be the same for all samples, so it would be valid to
retrieve the result size for one sample and use that when retrieving results
for all samples. The retrieved size should be passed to GpaGetSampleResult to
retrieve the actual results. Execution of all command lists (DirectX 12) or
command buffers (Vulkan) must be complete before results will be available.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``sample_id``", "Unique identifier of a previously-created sample."
    "``sample_result_size_in_bytes``", "The value that will be set to the result size upon successful execution  - this value needs to be passed to GpaGetSampleResult."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The sample result size was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``session_id`` parameter is NULL.
    | The supplied ``sample_result_size_in_bytes`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorSessionNotEnded", "The session has not been ended. A session must have been ended with GpaEndSession prior to retrieving results."
    "kGpaStatusErrorSampleNotFound", "The specified sample was not found in the specified session."
    "kGpaStatusErrorException", "Exception occurred."
