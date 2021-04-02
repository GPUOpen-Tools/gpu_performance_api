.. Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.

GpaBeginSample
@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaBeginSample(
        gpa_uint32 sample_id,
        GpaCommandListId command_list_id);

Description
%%%%%%%%%%%

Begins a sample in a command list. A sample is a particular workload for which
counters will be collected. If the owning session was created with
kGpaSessionSampleTypeDiscreteCounter and one or more counters have been
enabled, then those counters will be collected for this sample. Each sample
must be associated with a GPA command list. The command list must have been
previously started before starting a sample. Samples can be created by multiple
threads provided no two threads are creating samples on same command list. You
must provide a unique id for every new sample. When performing multiple passes,
every sample id must exist in every pass. You may create as many samples as
needed. However, nesting of samples is not allowed. Each sample must be wrapped
in sequence of GpaBeginSample/GpaEndSample before starting another one. A
sample can be started in one primary command list and continued/ended on
another primary command list - See GpaContinueSampleOnCommandList.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sample_id``","A unique sample identifier."
    "``command_list_id``", "Unique identifier of a previously-created command list."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The sample was successfully started."
    "kGpaStatusErrorNullPointer", "The supplied ``command_list_id`` parameter is NULL."
    "kGpaStatusErrorCommandListNotFound", "The supplied ``command_list_id`` parameter was not recognized as a previously-created command list identifier."
    "kGpaStatusErrorIndexOutOfRange", "The specified command list's pass index is out of range."
    "kGpaStatusErrorFailed", "The sample could not be started."
    "kGpaStatusErrorException", "Exception occurred."
