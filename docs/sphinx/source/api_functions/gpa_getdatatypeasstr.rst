.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetDataTypeAsStr
@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetDataTypeAsStr(
        GpaDataType counter_data_type,
        const char** type_str);

Description
%%%%%%%%%%%

Gets a string representation of the specified counter data type. This could be
used to display counter types along with their name or value. For example the
kGpaDataTypeUint64 ``counter_data_type`` would return ``gpa_uint64``.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``counter_data_type``", "The data type whose string representation is needed."
    "``type_str``", "The address which will hold the string representation upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The string representation was successfully retrieved."
    "kGpaStatusErrorNullPointer", "The supplied ``type_str`` parameter is NULL."
    "kGpaStatusErrorInvalidParameter", "The ``counter_data_type`` parameter has an invalid value."
    "kGpaStatusErrorException", "Exception occurred."
