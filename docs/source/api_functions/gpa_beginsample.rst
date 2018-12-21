.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_BeginSample
@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_BeginSample(
        gpa_uint32 sampleId,
        GPA_CommandListId commandListId);

Description
%%%%%%%%%%%

Begins a sample in a command list. A sample is a particular workload for which
counters will be collected. If the owning session was created with
GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER and one or more counters have been enabled,
then those counters will be collected for this sample. Each sample must be
associated with a GPA command list. The command list must have been previously
started before starting a sample. Samples can be created by multiple threads
provided no two threads are creating samples on same command list. You must
provide a unique id for every new sample. When performing multiple passes,
every sample id must exist in every pass. You may create as many samples as
needed. However, nesting of samples is not allowed. Each sample must be wrapped
in sequence of GPA_BeginSample/GPA_EndSample before starting another one. A
sample can be started in one primary command list and continued/ended on
another primary command list - See GPA_ContinueSampleOnCommandList.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``sampleId``","A unique sample identifier."
    "``commandListId``", "Unique identifier of a previously-created command list."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The sample was successfully started."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``commandListId`` parameter is NULL."
    "GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND", "The supplied ``commandListId`` parameter was not recognized as a previously-created command list identifier."
    "GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE", "The specified command list's pass index is out of range."
    "GPA_STATUS_ERROR_FAILED", "The sample could not be started."
    "GPA_STATUS_ERROR_EXCEPTION", "Exception occurred."
