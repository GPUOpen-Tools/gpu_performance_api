.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaDisableAllCounters
@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaDisableAllCounters(
        GpaSessionId session_id);

Description
%%%%%%%%%%%

Disables all counters. Subsequent sampling sessions will not provide values for
any disabled counters. Initially all counters are disabled, and must explicitly
be enabled.

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

    "kGpaStatusOk", "All counters were successfully disabled."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorCannotChangeCountersWhenSampling", "The set of enabled counters cannot be changed after GpaBeginSession is called."
    "kGpaStatusErrorContextNotOpen", "The supplied session's parent context is not currently open."
    "kGpaStatusErrorFailed", "An error occurred while trying to disable all counters."
    "kGpaStatusErrorException", "Exception occurred."
