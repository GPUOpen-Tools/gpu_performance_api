.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetSampleCount
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetSampleCount(
        GPA_SessionId sessionId,
        gpa_uint32* pSampleCount);

Description
%%%%%%%%%%%

Gets the number of samples created for the specified session. This is useful if
samples are conditionally created and a count is not kept. The session must have
been ended by GPA_EndSession before calling this function.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``", "Unique identifier of a previously-created session."
    "``pSampleCount``", "The value which will hold the number of samples contained within the session upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The sample count was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``sessionId`` parameter is NULL.
    | The supplied ``pSampleCount`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_SESSION_NOT_ENDED", "The session has not been ended. A session must have been ended with GPA_EndSession prior to querying the number of samples."
    "GPA_STATUS_ERROR_FAILED", "| The sample count could not be retrieved."
