.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaGetSupportedSampleTypes
@@@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaGetSupportedSampleTypes(
        GpaContextId context_id,
        GpaContextSampleTypeFlags* sample_types);

Description
%%%%%%%%%%%

Gets a mask of the sample types supported by the specified context. A call to
GPA_CreateSession will fail if the requested sample types are not compatible
with the context's sample types.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``sample_types``", "The value that will be set to the the mask of the supported sample types upon successful execution. This will be a combination of GpaSampleBits."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The supported sample types were successfully retrieved."
    "kGpaStatusErrorNullPointer", "| The supplied ``sample_types`` parameter is NULL.
    | The supplied ``context_id`` parameter is NULL."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorFailed", "The supported sample types could not be retrieved."
    "kGpaStatusErrorException", "Exception occurred."
