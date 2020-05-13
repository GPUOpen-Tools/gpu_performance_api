.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetSampleId
@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetSampleId(
        GPA_SessionId sessionId,
        gpa_uint32 index,
        gpa_uint32* pSampleId);

Description
%%%%%%%%%%%

Gets the sample id of the sample with the specified index. This is useful if
sample ids are either non-zero-based or non-consecutive.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``", "Unique identifier of a previously-created session."
    "``index``", "Zero-based index of the sample whose sample id is needed. Must lie between 0 and (GPA_GetSampleCount result - 1)."
    "``pSampleId``", "The value that will hold the id of the sample upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The sample id was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``sessionId`` parameter is NULL.
    | The supplied ``pSampleId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_SESSION_NOT_STARTED", "The session has not been started."
    "GPA_STATUS_ERROR_SAMPLE_NOT_FOUND", "The specified sample could not be found."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."