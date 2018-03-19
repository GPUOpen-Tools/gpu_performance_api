.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetDataTypeAsStr
@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetDataTypeAsStr(
        GPA_Data_Type counterDataType,
        const char** ppTypeStr);

Description
%%%%%%%%%%%

Gets a string representation of the specified counter data type. This could be
used to display counter types along with their name or value. For example the
GPA_DATA_TYPE_UINT64 ``counterDataType`` would return ``gpa_uint64``.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``counterDataType``", "The data type whose string representation is needed."
    "``ppTypeStr``", "The address which will hold the string representation upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The string representation was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``ppTypeStr`` parameter is NULL."
    "GPA_STATUS_ERROR_INVALID_PARAMETER", "The ``counterDataType`` parameter has an invalid value."
