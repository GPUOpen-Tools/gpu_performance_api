.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaIsSessionComplete
@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaIsSessionComplete(
        GpaSessionId session_id);

Description
%%%%%%%%%%%

Checks if results for all samples within a session are available. After a
sampling session results may be available immediately or take a certain amount
of time to become available. This function allows you to determine when the
results of a session can be read. The function does not block, permitting
periodic polling. To block until a sample is ready use GpaGetSampleResult
instead. Execution of all command lists (DirectX 12) or command buffers
(Vulkan) must be complete before results will be available.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``session_id``", "Unique identifier of a previously-created session."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The session is complete and results are ready."
    "kGpaStatusErrorResultNotReady", "The session is not yet ready."
    "kGpaStatusErrorNullPointer", "The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorSessionNotFound", "The supplied ``session_id`` parameter was not recognized as a previously-created session identifier."
    "kGpaStatusErrorSessionNotStarted", "The session has not been started."
    "kGpaStatusErrorSessionNotEnded", "The session has not been ended. A session must have been ended with GpaEndSession prior to retrieving results."
    "kGpaStatusErrorException", "Exception occurred."
