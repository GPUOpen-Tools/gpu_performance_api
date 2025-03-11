.. Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.

GpaEndSample
@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaEndSample(
        GpaCommandListId command_list_id);

Description
%%%%%%%%%%%

Ends a sample in a command list. A sample is a particular workload for which
counters will be collected. If the owning session was created with
kGpaSessionSampleTypeDiscreteCounter and one or more counters have been
enabled, then those counters will be collected for this sample. Each sample
must be associated with a GPA command list. Samples can be created by using
multiple threads provided no two threads are creating samples on same command
list. You must provide a unique Id for every new sample. You may create as many
samples as needed. However, nesting of samples is not allowed. Each sample must
be wrapped in sequence of GpaBeginSample/GpaEndSample before starting another
one. A sample can be started in one primary command list and continued/ended on
another primary command list - See GpaContinueSampleOnCommandList.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``command_list_id``", "Unique identifier of a previously-created command list."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The sample was successfully ended."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "The supplied ``command_list_id`` parameter is NULL."
    "kGpaStatusErrorCommandListNotFound", "The supplied ``command_list_id`` parameter was not recognized as a previously-created command list identifier."
    "kGpaStatusErrorIndexOutOfRange", "The specified command list's pass index is out of range."
    "kGpaStatusErrorFailed", "The sample could not be started."
    "kGpaStatusErrorException", "Exception occurred."
