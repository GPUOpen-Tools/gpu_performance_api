.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetPassCount
@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetPassCount(
        GPA_SessionId sessionId,
        gpa_uint32* pNumPasses);

Description
%%%%%%%%%%%

Gets the number of passes required for the currently enabled set of counters.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sessionId``", "Unique identifier of a previously-created session."
    "``pNumPasses``", "The value which will hold the number of required passes upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The pass count was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``sessionId`` parameter is NULL.
    | The supplied ``pNumPasses`` parameter is NULL."
    "GPA_STATUS_ERROR_SESSION_NOT_FOUND", "The supplied ``sessionId`` parameter was not recognized as a previously-created session identifier."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied session's parent context is not currently open."
    "GPA_STATUS_ERROR_FAILED", "The pass count could not be retrieved."

