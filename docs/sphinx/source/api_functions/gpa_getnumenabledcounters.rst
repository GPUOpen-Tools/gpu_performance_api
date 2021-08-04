.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetNumEnabledCounters
@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetNumEnabledCounters(
        GpaSessionId session_id,
        GpaUInt32* count);

Description
%%%%%%%%%%%

Gets the number of enabled counters.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``count``", "The value which will hold the number of enabled counters contained within the session upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The number of enabled counters was successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``session_id`` parameter is NULL.
    | The supplied ``count`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied session's parent context is not currently open."
    "kGpaStatusErrorFailed", "The number of enabled counters could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
