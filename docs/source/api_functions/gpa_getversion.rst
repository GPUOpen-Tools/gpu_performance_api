.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetVersion
@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetVersion(
        gpa_uint32* pMajorVersion,
        gpa_uint32* pMinorVersion,
        gpa_uint32* pBuild,
        gpa_uint32* pUpdateVersion);

Description
%%%%%%%%%%%

Gets the GPA version.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``pMajorVersion``", "The value that will hold the major version of GPA upon successful execution."
    "``pMinorVersion``", "The value that will hold the minor version of GPA upon successful execution."
    "``pBuild``", "The value that will hold the build number of GPA upon successful execution."
    "``pUpdateVersion``", "The value that will hold the update version of GPA upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The GPA version was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``pMajorVersion`` parameter is NULL.
    | The supplied ``pMinorVersion`` parameter is NULL.
    | The supplied ``pBuild`` parameter is NULL.
    | The supplied ``pUpdateVersion`` parameter is NULL."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
