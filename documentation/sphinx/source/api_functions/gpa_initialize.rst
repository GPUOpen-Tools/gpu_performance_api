GpaInitialize
@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaInitialize(
        GpaInitializeFlags flags);

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

    "``flags``", "Flags used to initialize GPA. This should be a combination of GpaInitializeBits."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "GPA was destroyed."
    "kGpaStatusErrorGpaAlreadyInitialized", "GpaInitialize was already called."
    "kGpaStatusErrorInvalidParameter", "The ``flags`` parameter has an invalid value."
    "kGpaStatusErrorException", "Exception occurred."
