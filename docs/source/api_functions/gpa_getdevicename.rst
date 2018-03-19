.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetDeviceName
@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetDeviceName(
        GPA_ContextId contextId,
        const char** ppDeviceName);

Description
%%%%%%%%%%%

Gets the device name of the GPU associated with the specified context.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``contextId``", "Unique identifier of a previously-opened context."
    "``ppDeviceName``", "The value that will be set to the device name upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The device name was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``ppDeviceName`` parameter is NULL.
    | The supplied ``contextId`` parameter is NULL."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_CONTEXT_NOT_FOUND", "The supplied ``contextId`` parameter was not recognized as a previously-opened context identifier."
    "GPA_STATUS_ERROR_FAILED", "The device name could not be retrieved."
