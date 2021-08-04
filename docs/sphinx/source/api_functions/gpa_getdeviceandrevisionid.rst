.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetDeviceAndRevisionId
@@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetDeviceAndRevisionId(
        GpaContextId context_id,
        GpaUInt32* device_id,
        GpaUInt32* revision_id);

Description
%%%%%%%%%%%

Gets the GPU device id and revision id associated with the specified context.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``device_id``", "The value that will be set to the device id upon successful execution."
    "``revision_id``", "The value that will be set to the device revision id upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The device id and revision id were successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``device_id`` parameter is NULL.
    | The supplied ``revision_id`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorFailed", "The device id and revision id could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
