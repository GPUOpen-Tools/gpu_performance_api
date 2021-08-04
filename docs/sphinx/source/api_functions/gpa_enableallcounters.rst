.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaEnableAllCounters
@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaEnableAllCounters(
        GpaSessionId session_id);

Description
%%%%%%%%%%%

Enables all counters. Subsequent sampling sessions will provide values for all
counters. Initially all counters are disabled, and must explicitly be enabled.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``","Unique identifier of a previously-created session."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "All counters were successfully enabled."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorCannotChangeCountersWhenSampling", "The set of enabled counters cannot be changed after GpaBeginSession is called."
    "kGpaStatusErrorContextNotOpen", "The supplied session's parent context is not currently open."
    "kGpaStatusErrorIncompatibleSampleTypes", "The supplied session was not created with a GpaSessionSampleType value that supports counter collection."
    "kGpaStatusErrorFailed", "An error occurred while trying to enable all counters."
    "kGpaStatusErrorException", "Exception occurred."
