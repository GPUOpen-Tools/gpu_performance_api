.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_EndSession
@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_EndSession(
        GPA_SessionId sessionId);

Description
%%%%%%%%%%%

Ends sampling with the currently enabled set of counters. This will end the
sampling process. A session must be ended before results for that session can
be queried.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``","Unique identifier of a previously-created session."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The session was successfully ended."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``sessionId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_VARIABLE_NUMBER_OF_SAMPLES_IN_PASSES", "There were an inconsistent number of samples created in each pass of the session."
    "GPA_STATUS_ERROR_NOT_ENOUGH_PASSES", "There were not enough passes created in the session"
    "GPA_STATUS_ERROR_SESSION_NOT_STARTED", "The session has not been started."
    "GPA_STATUS_ERROR_FAILED", "The session could be be ended."
    "GPA_STATUS_ERROR_OTHER_SESSION_ACTIVE", "Another session is active."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
