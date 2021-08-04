.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaBeginSession
@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaBeginSession(
        GpaSessionId session_id);

Description
%%%%%%%%%%%

Begins sampling with the currently enabled set of counters. A session must have
been created using GpaCreateSession before it can be started. A session must
be started before creating any samples. The set of enabled counters for a
session cannot be changed after the session has started.

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

    "kGpaStatusOk", "The session was successfully started."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorSessionAlreadyStarted", "The session has already been started."
    "kGpaStatusErrorNoCountersEnabled", "There are no counters enabled"
    "kGpaStatusErrorFailed", "The session could be be started."
    "kGpaStatusErrorOtherSessionActive", "Another session is active."
    "kGpaStatusErrorException", "Exception occurred."
