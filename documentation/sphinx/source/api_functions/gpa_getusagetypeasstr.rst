GpaGetUsageTypeAsStr
@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetUsageTypeAsStr(
        GpaUsageType counter_usage_type,
        const char** usage_type_str);

Description
%%%%%%%%%%%

Gets a string representation of the specified counter usage type. This could be
used to display counter units along with their name or value. For example, the
kGpaUsageTypePercentage ``usage_type_str`` would return "percentage".

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``counter_usage_type``", "The usage type whose string representation is needed."
    "``usage_type_str``", "The address which will hold the string representation upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The string representation was successfully retrieved."
    "kGpaStatusErrorNullPointer", "The supplied ``usage_type_str`` parameter is NULL."
    "kGpaStatusErrorInvalidParameter", "The ``counter_usage_type`` parameter has an invalid value."
    "kGpaStatusErrorException", "Exception occurred."
