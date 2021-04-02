.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaCopySecondarySamples
@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaCopySecondarySamples(
        GpaCommandListId secondary_command_list_id,
        GpaCommandListId primary_command_list_id,
        gpa_uint32 num_samples,
        gpa_uint32* new_sample_ids);

Description
%%%%%%%%%%%

Copies a set of samples from a secondary command list back to the primary
command list that executed the secondary command list. This function is only
supported for DirectX 12 and Vulkan. You cannot collect data for samples
created on secondary command lists unless they are first copied to a new set of
samples on the primary command list.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``secondary_command_list_id``", "Unique identifier of a previously-created command list. This represents the secondary command list that acts as the source of the samples being copied."
    "``primary_command_list_id``", "Unique identifier of a previously-created command list. This represents the primary command list that acts as the destination of the samples being copied."
    "``num_samples``", "The number of samples to copy."
    "``new_sample_ids``", "An array of the sample ids which should be copied from the secondary command list to the primary command list."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The samples were successfully copied."
    "kGpaStatusErrorNullPointer", "| The supplied ``secondary_command_list_id`` parameter is NULL.
    | The supplied ``primary_command_list_id`` parameter is NULL."
    "kGpaStatusErrorCommandListNotFound", "| The supplied ``secondary_command_list_id`` parameter was not recognized as a previously-created command list identifier.
    | The supplied ``primary_command_list_id`` parameter was not recognized as a previously-created command list identifier."
    "kGpaStatusErrorApiNotSupported", "This function is not supported for the current API. Only DirectX 12 and Vulkan support this API."
    "kGpaStatusErrorFailed", "The samples could not be copied."
    "kGpaStatusErrorException", "Exception occurred."
