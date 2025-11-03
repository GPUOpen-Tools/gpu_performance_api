GpaContinueSampleOnCommandList
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaContinueSampleOnCommandList(
        GpaUInt32 src_sample_id,
        GpaCommandListId primary_command_list_id);

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

    "``src_sample_id``", "The sample id of the sample being continued on a different command list."
    "``primary_command_list_id``", "Unique identifier of a previously-created primary command list on which the sample is continuing."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The sample was successfully continued on the specified command list."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "The supplied ``primary_command_list_id`` parameter is NULL."
    "kGpaStatusErrorCommandListNotFound", "The supplied ``primary_command_list_id`` parameter was not recognized as a previously-created command list identifier."
    "kGpaStatusErrorSampleNotFound", "The specified sample was not found."
    "kGpaStatusErrorApiNotSupported", "This function is not supported for the current API. Only DirectX 12 and Vulkan support this API."
    "kGpaStatusErrorFailed", "The sample could not be continued on the specified command list."
    "kGpaStatusErrorException", "Exception occurred."
