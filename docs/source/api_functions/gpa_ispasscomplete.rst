.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_IsPassComplete
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_IsPassComplete(
        GPA_SessionId sessionId,
        gpa_uint32 passIndex);

Description
%%%%%%%%%%%

Checks whether or not a pass has finished. After sampling a workload, results
may be available immediately or take a certain amount of time to become
available. This function allows you to determine when the pass has finished and
associated resources are no longer needed in the application. The function does
not block, permitting periodic polling. The application must not free its
resources until this function returns GPA_STATUS_OK.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``", "Unique identifier of a previously-created session."
    "``passIndex``", "Zero-based index of the pass to check."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The pass is complete and results are ready."
    "GPA_STATUS_RESULT_NOT_READY", "The pass is not yet ready."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``sessionId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_SESSION_NOT_STARTED", "The session has not been started."