.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetSampleResultSize
@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetSampleResultSize(
        GPA_SessionId sessionId,
        gpa_uint32 sampleId,
        size_t* sampleResultSizeInBytes);

Description
%%%%%%%%%%%

Gets the result size (in bytes) for a given sample. For discrete counter
samples, the size will be the same for all samples, so it would be valid to
retrieve the result size for one sample and use that when retrieving results
for all samples. The retrieved size should be passed to GPA_GetSampleResult to
retrieve the actual results. Execution of all command lists (DirectX 12) or
command buffers (Vulkan) must be complete before results will be available.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``", "Unique identifier of a previously-created session."
    "``sampleId``", "Unique identifier of a previously-created sample."
    "``sampleResultSizeInBytes``", "The value that will be set to the result size upon successful execution  - this value needs to be passed to GetSampleResult."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The sample result size was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``sessionId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_SESSION_NOT_ENDED", "The session has not been ended. A session must have been ended with GPA_EndSession prior to retrieving results."
    "GPA_STATUS_ERROR_SAMPLE_NOT_FOUND", "The specified sample was not found in the specified session."
