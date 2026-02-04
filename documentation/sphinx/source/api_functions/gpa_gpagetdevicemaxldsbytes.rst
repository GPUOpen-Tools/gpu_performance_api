GpaGetDeviceMaxLdsBytes
@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetDeviceMaxLdsBytes(
        GpaContextId context_id,
        GpaUInt32* max_lds_bytes);

Description
%%%%%%%%%%%

Gets the max number of LDS bytes on the GPU.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``max_lds_bytes``", "The value that will be set to the total size of LDS memory across the whole GPU."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The device generation was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``max_lds_bytes`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorFailed", "The value could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
    "kGpaStatusErrorHardwareNotSupported", "The HW is not supported."
