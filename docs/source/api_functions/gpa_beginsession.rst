.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_BeginSession
@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_BeginSession(
        GPA_SessionId sessionId);

Description
%%%%%%%%%%%

Begins sampling with the currently enabled set of counters. A session must have
been created using GPA_CreateSession before it can be started. A session must
be started before creating any samples. The set of enabled counters for a
session cannot be changed after the session has started.

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

    "GPA_STATUS_OK", "The session was successfully started."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``sessionId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_SESSION_ALREADY_STARTED", "The session has already been started."
    "GPA_STATUS_ERROR_NO_COUNTERS_ENABLED", "There are no counters enabled"
    "GPA_STATUS_ERROR_FAILED", "The session could be be started."
