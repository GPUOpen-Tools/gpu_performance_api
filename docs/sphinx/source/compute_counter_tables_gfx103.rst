.. Copyright(c) 2018-2023 Advanced Micro Devices, Inc.All rights reserved.
.. Compute Performance Counters for RDNA2

.. *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

RDNA2 Counters
++++++++++++++

General Group
%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "Wavefronts", "Items", "Total wavefronts."
    "VALUInsts", "Items", "The average number of vector ALU instructions executed per work-item (affected by flow control)."
    "SALUInsts", "Items", "The average number of scalar ALU instructions executed per work-item (affected by flow control)."
    "VFetchInsts", "Items", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory."
    "SFetchInsts", "Items", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control)."
    "VWriteInsts", "Items", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory."
    "GDSInsts", "Items", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control)."
    "VALUUtilization", "Percentage", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence)."
    "VALUBusy", "Percentage", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal)."
    "SALUBusy", "Percentage", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal)."

LocalMemory Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "LDSInsts", "Items", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control)."
    "LDSBankConflict", "Percentage", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad)."

GlobalMemory Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "FetchSize", "Kilobytes", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account."
    "WriteSize", "Kilobytes", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account."
    "L0CacheHit", "Percentage", "The percentage of fetch, write, atomic, and other instructions that hit the data in L0 cache. Value range: 0% (no hit) to 100% (optimal)."
    "L1CacheHit", "Percentage", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal)."
    "L2CacheHit", "Percentage", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal)."
    "MemUnitBusy", "Percentage", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound)."
    "MemUnitStalled", "Percentage", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad)."
    "WriteUnitStalled", "Percentage", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad)."
