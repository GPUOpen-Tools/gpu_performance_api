.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_EnableCounterByName
@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_EnableCounterByName(
        GPA_SessionId sessionId,
        const char* pCounterName);

Description
%%%%%%%%%%%

Enables the counter with the specified counter name (case insensitive).
Subsequent sampling sessions will provide values for any enabled counters.
Initially all counters are disabled, and must explicitly be enabled.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``","Unique identifier of a previously-created session."
    "``pCounterName``", "The name of the counter to enable."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The specified counter was successfully enabled."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``sessionId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING", "The set of enabled counters cannot be changed after GPA_BeginSession is called."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied session's parent context is not currently open."
    "GPA_STATUS_ERROR_ALREADY_ENABLED", "The specified counter was already enabled."
    "GPA_STATUS_ERROR_INCOMPATIBLE_SAMPLE_TYPES", "The supplied session was not created with a GPA_Session_Sample_Type value that supports counter collection."
    "GPA_STATUS_ERROR_FAILED", "| The specified counter name is not valid.
    | An error occurred while trying to enable the counter."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
