.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetPassCount
@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetPassCount(
        GpaSessionId session_id,
        GpaUInt32* num_passes);

Description
%%%%%%%%%%%

Gets the number of passes required for the currently enabled set of counters.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``num_passes``", "The value which will hold the number of required passes upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The pass count was successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``session_id`` parameter is NULL.
    | The supplied ``num_passes`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied session's parent context is not currently open."
    "kGpaStatusErrorFailed", "The pass count could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."

