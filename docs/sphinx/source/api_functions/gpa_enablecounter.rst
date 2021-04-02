.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaEnableCounter
@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaEnableCounter(
        GpaSessionId session_id,
        GpaUInt32 index);

Description
%%%%%%%%%%%

Enables the specified counter. Subsequent sampling sessions will provide values
for any enabled counters. Initially all counters are disabled, and must
explicitly be enabled.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``","Unique identifier of a previously-created session."
    "``index``", "The index of the counter to enable. Must lie between 0 and (GpaGetNumCounters result - 1)."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The counter was successfully enabled."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorCannotChangeCountersWhenSampling", "The set of enabled counters cannot be changed after GpaBeginSession is called."
    "kGpaStatusErrorIndexOutOfRange", "The specified index is out of range."
    "kGpaStatusErrorAlreadyEnabled", "The specified counter was already enabled."
    "kGpaStatusErrorIncompatibleSampleTypes", "The supplied session was not created with a GPA_Session_Sample_Type value that supports counter collection."
    "kGpaStatusErrorFailed", "An error occurred while trying to enable the counter."
    "kGpaStatusErrorException", "Exception occurred."
