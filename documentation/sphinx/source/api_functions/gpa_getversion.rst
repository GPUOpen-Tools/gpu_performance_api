.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetVersion
@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetVersion(
        GpaUInt32* major_version,
        GpaUInt32* minor_version,
        GpaUInt32* build_version,
        GpaUInt32* update_version);

Description
%%%%%%%%%%%

Gets the GPA version.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``major_version``", "The value that will hold the major version of GPA upon successful execution."
    "``minor_version``", "The value that will hold the minor version of GPA upon successful execution."
    "``build_version``", "The value that will hold the build number of GPA upon successful execution."
    "``update_version``", "The value that will hold the update version of GPA upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The GPA version was successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``major_version`` parameter is NULL.
    | The supplied ``minor_version`` parameter is NULL.
    | The supplied ``build_version`` parameter is NULL.
    | The supplied ``update_version`` parameter is NULL."
    "kGpaStatusErrorException", "Exception occurred."
