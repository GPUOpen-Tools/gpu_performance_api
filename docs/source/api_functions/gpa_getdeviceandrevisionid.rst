.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetDeviceAndRevisionId
@@@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetDeviceAndRevisionId(
        GPA_ContextId contextId,
        gpa_uint32* pDeviceId,
        gpa_uint32* pRevisionId);

Description
%%%%%%%%%%%

Gets the GPU device id and revision id associated with the specified context.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``contextId``", "Unique identifier of a previously-opened context."
    "``pDeviceId``", "The value that will be set to the device id upon successful execution."
    "``pRevisionId``", "The value that will be set to the device revision id upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The device id and revision id were successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``pDeviceId`` parameter is NULL.
    | The supplied ``pRevisionId`` parameter is NULL.
    | The supplied ``contextId`` parameter is NULL."
    "GPA_STATUS_ERROR_CONTEXT_NOT_OPEN", "The supplied context is not currently open."
    "GPA_STATUS_ERROR_CONTEXT_NOT_FOUND", "The supplied ``contextId`` parameter was not recognized as a previously-opened context identifier."
    "GPA_STATUS_ERROR_FAILED", "The device id and revision id could not be retrieved."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
