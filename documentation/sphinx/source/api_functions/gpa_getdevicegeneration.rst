GpaGetDeviceGeneration
@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetDeviceGeneration(
        GpaContextId context_id,
        GpaHwGeneration* hardware_generation);

Description
%%%%%%%%%%%

Gets the device generation of the GPU associated with the specified context.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``hardware_generation``", "The value that will be set to the device generation upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The device generation was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``hardware_generation`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorFailed", "The device generation could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
