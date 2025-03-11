.. Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.

GpaEndSession
@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaEndSession(
        GpaSessionId session_id);

Description
%%%%%%%%%%%

Ends sampling with the currently enabled set of counters. This will end the
sampling process. A session must be ended before results for that session can
be queried.

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

    "kGpaStatusOk", "The session was successfully ended."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorVariableNumberOfSamplesInPasses", "There were an inconsistent number of samples created in each pass of the session."
    "kGpaStatusErrorNotEnoughPasses", "There were not enough passes created in the session"
    "kGpaStatusErrorSessionNotStarted", "The session has not been started."
    "kGpaStatusErrorFailed", "The session could be be ended."
    "kGpaStatusErrorOtherSessionActive", "Another session is active."
    "kGpaStatusErrorException", "Exception occurred."
