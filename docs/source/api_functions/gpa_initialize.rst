.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_Initialize
@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_Initialize(
        GPA_InitializeFlags flags);

Description
%%%%%%%%%%%

Initializes the driver so that counters are exposed. This function must be
called before the rendering context or device is created. In the case of
DirectX 12 or Vulkan, this function must be called before a queue is created.


Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``flags``", "Flags used to initialize GPA. This should be a combination of GPA_Initialize_Bits."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "GPA  was destroyed."
    "GPA_STATUS_ERROR_GPA_ALREADY_INITIALIZED", "GPA_Initialize was already called."
    "GPA_STATUS_ERROR_INVALID_PARAMETER", "The ``flags`` parameter has an invalid value."
