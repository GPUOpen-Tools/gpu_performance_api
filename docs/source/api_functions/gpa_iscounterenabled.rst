.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_IsCounterEnabled
@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_IsCounterEnabled(
        GPA_SessionId sessionId,
        gpa_uint32 counterIndex);

Description
%%%%%%%%%%%

Checks whether or not a counter is enabled.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``", "Unique identifier of a previously-created session."
    "``counterIndex``", "The index of the counter. Must lie between 0 and (GPA_GetNumCounters result - 1)."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The specified counter is enabled."
    "GPA_STATUS_ERROR_COUNTER_NOT_FOUND", "The specified counter is not enabled."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``sessionId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING", "The set of enabled counters cannot be changed after GPA_BeginSession is called."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied session's parent context is not currently open."
    "GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE", "The specified index is out of range."
    "GPA_STATUS_ERROR_FAILED", "An error occurred while trying to retrieve the enabled status of the specified counter."

