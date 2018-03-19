.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_DeleteSession
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_DeleteSession(
        GPA_SessionId sessionId);

Description
%%%%%%%%%%%

Deletes a session object. Deletes the specified session, along with all counter
results associated with the session.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``","Unique identifier of a previously-created session."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The session was successfully deleted."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``sessionId`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_FAILED", "The session could not be deleted."
