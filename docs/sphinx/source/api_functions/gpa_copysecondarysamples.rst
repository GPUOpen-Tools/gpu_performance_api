.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_CopySecondarySamples
@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_CopySecondarySamples(
        GPA_CommandListId secondaryCommandListId,
        GPA_CommandListId primaryCommandListId,
        gpa_uint32 numSamples,
        gpa_uint32* pNewSampleIds);

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

    "``secondaryCommandListId``", "Unique identifier of a previously-created command list. This represents the secondary command list that acts as the source of the samples being copied."
    "``primaryCommandListId``", "Unique identifier of a previously-created command list. This represents the primary command list that acts as the destination of the samples being copied."
    "``numSamples``", "The number of samples to copy."
    "``pNewSampleIds``", "An array of the sample ids which should be copied from the secondary command list to the primary command list."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The samples were successfully copied."
    "GPA_STATUS_ERROR_NULL_POINTER", "| The supplied ``secondaryCommandListId`` parameter is NULL.
    | The supplied ``primaryCommandListId`` parameter is NULL."
    "GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND", "| The supplied ``secondaryCommandListId`` parameter was not recognized as a previously-created command list identifier.
    | The supplied ``primaryCommandListId`` parameter was not recognized as a previously-created command list identifier."
    "GPA_STATUS_ERROR_API_NOT_SUPPORTED", "This function is not supported for the current API. Only DirectX 12 and Vulkan support this API."
    "GPA_STATUS_ERROR_FAILED", "The samples could not be copied."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
