.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetUsageTypeAsStr
@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetUsageTypeAsStr(
        GPA_Usage_Type counterUsageType,
        const char** ppUsageTypeStr);

Description
%%%%%%%%%%%

Gets a string representation of the specified counter usage type. This could be
used to display counter units along with their name or value. For example, the
GPA_USAGE_TYPE_PERCENTAGE ``counterUsageType`` would return "percentage".

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``counterUsageType``", "The usage type whose string representation is needed."
    "``ppUsageTypeStr``", "The address which will hold the string representation upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The string representation was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``ppUsageTypeStr`` parameter is NULL."
    "GPA_STATUS_ERROR_INVALID_PARAMETER", "The ``counterUsageType`` parameter has an invalid value."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
