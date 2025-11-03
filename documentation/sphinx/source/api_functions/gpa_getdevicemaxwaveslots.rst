GpaGetDeviceMaxWaveSlots
@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetDeviceMaxWaveSlots(
        GpaContextId gpa_context_id,
        GpaUInt32* max_wave_slots);

Description
%%%%%%%%%%%

Gets the total number of wave slots on the GPU.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``max_wave_slots``", "The value that will be set to the maximum number of waves slots."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The device generation was successfully retrieved."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``max_wave_slots`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorFailed", "The max wave slots could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
