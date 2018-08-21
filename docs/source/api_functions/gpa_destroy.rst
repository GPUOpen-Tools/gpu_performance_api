.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_Destroy
@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_Destroy();

Description
%%%%%%%%%%%

Undoes any initialization to ensure proper behavior in applications that are
not being profiled. This function must be called before the rendering context or
device is released / destroyed.

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "GPA  was destroyed."
    "GPA_STATUS_ERROR_GPA_NOT_INITIALIZED", "GPA_Initialize was never called."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
