.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_ContinueSampleOnCommandList
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_ContinueSampleOnCommandList(
        gpa_uint32 srcSampleId,
        GPA_CommandListId primaryCommandListId);

Description
%%%%%%%%%%%

Continues a sample from one primary command list on to another primary
command list. This function is only supported for DirectX 12 and Vulkan.
Normally samples must be started and ended on the same command list. Using this
function, samples can be started on one primary command list and continued/ended on
another primary command list, allowing a single sample to span more than one
command list.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``srcSampleId``", "The sample id of the sample being continued on a different command list."
    "``primaryCommandListId``", "Unique identifier of a previously-created primary command list on which the sample is continuing."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The sample was successfully continued on the specified command list."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``primaryCommandListId`` parameter is NULL."
    "GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND", "The supplied ``commandListId`` parameter was not recognized as a previously-created command list identifier."
    "GPA_STATUS_ERROR_SAMPLE_NOT_FOUND", "The specified sample was not found."
    "GPA_STATUS_ERROR_API_NOT_SUPPORTED", "This function is not supported for the current API. Only DirectX 12 and Vulkan support this API."
    "GPA_STATUS_ERROR_FAILED", "The sample could not be continued on the specified command list."
