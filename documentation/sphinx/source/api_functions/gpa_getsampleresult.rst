.. Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.

GpaGetSampleResult
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetSampleResult(
        GpaSessionId session_id,
        GpaUInt32 sample_id,
        size_t sample_result_size_in_bytes,
        void* counter_sample_results);

Description
%%%%%%%%%%%

Gets the result data for a given sample. This function will block until results
are ready. Use GpaIsSessionComplete to check if results are ready. For
discrete counter samples, the data will be a set of contiguous 64-bit values,
one for each counter collected for the sample. After the results are returned,
you can iterate through the buffer to read the individual counter values back.
Execution of all command lists (DirectX 12) or command buffers (Vulkan) must be
complete before results will be available. Results for samples created in
secondary command lists will not be available unless GpaCopySecondarySamples
has been called to copy the samples back to the primary command list.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``sample_id``", "Unique identifier of a previously-created sample."
    "``sample_result_size_in_bytes``", "The size of the specified sample's results - this value should have been queried from GpaGetSampleResultSize."
    "``counter_sample_results``", "Address to which the counter data for the sample will be copied to."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The sample result was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``session_id`` parameter is NULL.
    | The supplied ``pCounterSampleResults`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorSampleNotFound", "The specified sample was not found in the specified session."
    "kGpaStatusErrorSessionNotEnded", "The session has not been ended. A session must have been ended with GpaEndSession prior to retrieving results."
    "kGpaStatusErrorReadingSampleRequest", "The sample result could not be read."
    "kGpaStatusErrorSampleInSecondaryCommandList", "An attempt was made to read a result from a secondary command list. Samples from a secondary command list must copied to the primary command list using GpaCopySecondarySamples."
    "kGpaStatusErrorIndexOutOfRange", "An internal operation to index a particular counter failed."
    "kGpaStatusErrorException", "Exception occurred."
