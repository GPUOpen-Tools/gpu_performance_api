.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaDestroy
@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaDestroy();

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

    "kGpaStatusOk", "GPA was destroyed."
    "kGpaStatusErrorGpaNotInitialized", "GpaInitialize was never called."
    "kGpaStatusErrorException", "Exception occurred."
