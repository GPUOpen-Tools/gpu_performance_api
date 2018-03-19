.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_IsSessionComplete
@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_IsSessionComplete(
        GPA_SessionId sessionId);

Description
%%%%%%%%%%%

Checks if results for all samples within a session are available. After a
sampling session results may be available immediately or take a certain amount
of time to become available. This function allows you to determine when the
results of a session can be read. The function does not block, permitting
periodic polling. To block until a sample is ready use GPA_GetSampleResult
instead. Execution of all command lists (DirectX 12) or command buffers
(Vulkan) must be complete before results will be available.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``", "Unique identifier of a previously-created session."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The session is complete and results are ready."
    "GPA_STATUS_RESULT_NOT_READY", "The session is not yet ready."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``sessionId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_SESSION_NOT_STARTED", "The session has not been started."
    "GPA_STATUS_ERROR_SESSION_NOT_ENDED", "The session has not been ended. A session must have been ended with GPA_EndSession prior to retrieving results."
