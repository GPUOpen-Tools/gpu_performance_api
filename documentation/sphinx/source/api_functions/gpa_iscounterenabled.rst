.. Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.

GpaIsCounterEnabled
@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaIsCounterEnabled(
        GpaSessionId session_id,
        GpaUInt32 counter_index);

Description
%%%%%%%%%%%

Checks whether or not a counter is enabled.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``counter_index``", "The index of the counter. Must lie between 0 and (GpaGetNumCounters result - 1)."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The specified counter is enabled."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorCounterNotFound", "The specified counter is not enabled."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorCannotChangeCountersWhenSampling", "The set of enabled counters cannot be changed after GpaBeginSession is called."
    "kGpaStatusErrorContextNotOpen", "The supplied session's parent context is not currently open."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorFailed", "An error occurred while trying to retrieve the enabled status of the specified counter."
    "kGpaStatusErrorException", "Exception occurred."

