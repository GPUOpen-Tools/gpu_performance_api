.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_BeginSample
@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetSampleResult(
        GPA_SessionId sessionId,
        gpa_uint32 sampleId,
        size_t sampleResultSizeInBytes,
        void* pCounterSampleResults);

Description
%%%%%%%%%%%

Gets the result data for a given sample. This function will block until results
are ready. Use GPA_IsSessionComplete to check if results are ready. For
discrete counter samples, the data will be a set of contiguous 64-bit values,
one for each counter collected for the sample. After the results are returned,
you can iterate through the buffer to read the individual counter values back.
Execution of all command lists (DirectX 12) or command buffers (Vulkan) must be
complete before results will be available. Results for samples created in
secondary command lists will not be available unless GPA_CopySecondarySamples
has been called to copy the samples back to the primary command list.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``", "Unique identifier of a previously-created session."
    "``sampleId``", "Unique identifier of a previously-created sample."
    "``sampleResultSizeInBytes``", "The size of the specified sample's results - this value should have been queried from GPA_GetSampleResultSize."
    "``pCounterSampleResults``", "Address to which the counter data for the sample will be copied to."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The sample result was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``sessionId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_SAMPLE_NOT_FOUND", "The specified sample was not found in the specified session."
    "GPA_STATUS_ERROR_SESSION_NOT_ENDED", "The session has not been ended. A session must have been ended with GPA_EndSession prior to retrieving results."
    "GPA_STATUS_ERROR_READING_SAMPLE_RESULT", "The sample result could not be read."
    "GPA_STATUS_ERROR_SAMPLE_IN_SECONDARY_COMMAND_LIST", "An attempt was made to read a result from a secondary command list. Samples from a secondary command list must copied to the primary command list using GPA_CopySecondarySamples."
    "GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE", "An internal operation to index a particular counter failed."
