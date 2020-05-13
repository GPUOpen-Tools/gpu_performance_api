.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_EndCommandList
@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_EndCommandList(
        GPA_CommandListId commandListId);

Description
%%%%%%%%%%%

Ends command list for sampling. You will be unable to create samples on the
specified command list after GPA_EndCommandList is called. For DirectX 12,
GPA_EndCommandList should be called before the application calls Close on the
underlying command list. For Vulkan, it should be called before the application
calls vkEndCommandBuffer on the underlying command buffer.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``commandListId``", "Unique identifier of a previously-created command list."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The command list was successfully ended."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``commandListId`` parameter is NULL."
    "GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND", "The supplied ``commandListId`` parameter was not recognized as a previously-created command list identifier."
    "GPA_STATUS_ERROR_COMMAND_LIST_ALREADY_ENDED", "The supplied command list has already been ended."
    "GPA_STATUS_ERROR_FAILED", "The command list could not be ended."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."