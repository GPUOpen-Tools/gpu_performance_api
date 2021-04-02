.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaIsPassComplete
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaIsPassComplete(
        GpaSessionId session_id,
        GpaUInt32 pass_index);

Description
%%%%%%%%%%%

Checks whether or not a pass has finished. After sampling a workload, results
may be available immediately or take a certain amount of time to become
available. This function allows you to determine when the pass has finished and
associated resources are no longer needed in the application. The function does
not block, permitting periodic polling. The application must not free its
resources until this function returns kGpaStatusOk.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."
    "``pass_index``", "Zero-based index of the pass to check."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The pass is complete and results are ready."
    "kGpaStatusErrorResultNotReady", "The pass is not yet ready."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorSessionNotStarted", "The session has not been started."
    "kGpaStatusErrorException", "Exception occurred."