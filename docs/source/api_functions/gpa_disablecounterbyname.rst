.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_DisableCounterByName
@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_DisableCounterByName(
        GPA_SessionId sessionId,
        const char* pCounterName);

Description
%%%%%%%%%%%

Disables the counter with the specified counter name (case insensitive).
Subsequent sampling sessions will not provide values for any disabled counters.
Initially all counters are disabled, and must explicitly be enabled.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``","Unique identifier of a previously-created session."
    "``pCounterName``", "The name of the counter to disable."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The specified counter was successfully disabled."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``sessionId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING", "The set of enabled counters cannot be changed after GPA_BeginSession is called."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied session's parent context is not currently open."
    "GPA_STATUS_ERROR_NOT_ENABLED", "The specified counter is not currently enabled."
    "GPA_STATUS_ERROR_FAILED", "| The specified counter name is not valid.
    | An error occurred while trying to disable the counter."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
