.. Copyright(c) 2018-2019 Advanced Micro Devices, Inc.All rights reserved.
.. Compute Performance Counters for Graphics IP v8

.. *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

Graphics IP v8 Counters
+++++++++++++++++++++++

General Group
%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "Wavefronts", "Total wavefronts."
    "VALUInsts", "The average number of vector ALU instructions executed per work-item (affected by flow control)."
    "SALUInsts", "The average number of scalar ALU instructions executed per work-item (affected by flow control)."
    "VFetchInsts", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory."
    "SFetchInsts", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control)."
    "VWriteInsts", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory."
    "FlatVMemInsts", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch."
    "GDSInsts", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control)."
    "VALUUtilization", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence)."
    "VALUBusy", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal)."
    "SALUBusy", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal)."

LocalMemory Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "LDSInsts", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control). Excludes FLAT instructions that read from or write to LDS."
    "FlatLDSInsts", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control)."
    "LDSBankConflict", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad)."

GlobalMemory Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "FetchSize", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account."
    "WriteSize", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account."
    "CacheHit", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal)."
    "MemUnitBusy", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound)."
    "MemUnitStalled", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad)."
    "WriteUnitStalled", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad)."
