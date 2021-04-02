.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaEndCommandList
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaEndCommandList(
        GpaCommandListId command_list_id);

Description
%%%%%%%%%%%

Ends command list for sampling. You will be unable to create samples on the
specified command list after GpaEndCommandList is called. For DirectX 12,
GpaEndCommandList should be called before the application calls Close on the
underlying command list. For Vulkan, it should be called before the application
calls vkEndCommandBuffer on the underlying command buffer.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``command_list_id``", "Unique identifier of a previously-created command list."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The command list was successfully ended."
    "kGpaStatusErrorNullPointer", "The supplied ``command_list_id`` parameter is NULL."
    "kGpaStatusErrorCommandListNotFound", "The supplied ``command_list_id`` parameter was not recognized as a previously-created command list identifier."
    "GpaStatusErrorCommandListAlreadyEnded", "The supplied command list has already been ended."
    "kGpaStatusErrorFailed", "The command list could not be ended."
    "kGpaStatusErrorException", "Exception occurred."