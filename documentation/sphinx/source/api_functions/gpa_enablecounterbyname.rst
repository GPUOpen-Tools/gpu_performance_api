.. Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.

GpaEnableCounterByName
@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaEnableCounterByName(
        GpaSessionId session_id,
        const char* counter_name);

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

    "``session_id``","Unique identifier of a previously-created session."
    "``counter_name``", "The name of the counter to enable."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The specified counter was successfully enabled."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorCannotChangeCountersWhenSampling", "The set of enabled counters cannot be changed after GpaBeginSession is called."
    "kGpaStatusErrorContextNotOpen", "The supplied session's parent context is not currently open."
    "kGpaStatusErrorAlreadyEnabled", "The specified counter was already enabled."
    "kGpaStatusErrorIncompatibleSampleTypes", "The supplied session was not created with a GpaSessionSampleType value that supports counter collection."
    "kGpaStatusErrorCounterNotFound", "The specified counter name is not valid."
    "kGpaStatusErrorFailed", "An error occurred while trying to enable the counter."
    "kGpaStatusErrorException", "Exception occurred."
