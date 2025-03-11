.. Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.

GpaDeleteSession
@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaDeleteSession(
        GpaSessionId session_id);

Description
%%%%%%%%%%%

Deletes a session object. Deletes the specified session, along with all counter
results associated with the session.

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

    "kGpaStatusOk", "The session was successfully deleted."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorFailed", "The session could not be deleted."
    "kGpaStatusErrorException", "Exception occurred."
