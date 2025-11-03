GpaGetDeviceName
@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetDeviceName(
        GpaContextId context_id,
        const char** device_name);

Description
%%%%%%%%%%%

Gets the device name of the GPU associated with the specified context.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``device_name``", "The value that will be set to the device name upon successful execution."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The device name was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``device_name`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorFailed", "The device name could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
