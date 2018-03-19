.. Copyright(c) 2018 Advanced Micro Devices, Inc.All rights reserved.
.. Compute Performance Counters

General Group
%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "Wavefronts", "Total wavefronts.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "VALUInsts", "The average number of vector ALU instructions executed per work-item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "SALUInsts", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "VFetchInsts", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "SFetchInsts", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "VWriteInsts", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "FlatVMemInsts", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "GDSInsts", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "VALUUtilization", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "VALUBusy", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "SALUBusy", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"

LocalMemory Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "LDSInsts", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control). Excludes FLAT instructions that read from or write to LDS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "FlatLDSInsts", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "LDSBankConflict", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"

GlobalMemory Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "FetchSize", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "WriteSize", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "L1CacheHit", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Value range: 0% (no hit) to 100% (optimal).", "| Vega"
    "L2CacheHit", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", "| Vega"
    "MemUnitBusy", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "MemUnitStalled", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "WriteUnitStalled", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CacheHit", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", "| Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
