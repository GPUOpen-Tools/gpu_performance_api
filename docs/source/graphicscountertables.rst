.. Copyright(c) 2018 Advanced Micro Devices, Inc.All rights reserved.
.. Graphics Performance Counters

.. *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

Timing Group
%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "GPUTime", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "ExecutionDuration", "GPU command execution duration in nanoseconds, from the time the command enters the top of the pipeline (TOP) to the time the command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "ExecutionStart", "GPU command execution start time in nanoseconds. This is the time the command enters the top of the pipeline (TOP).", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "ExecutionEnd", "GPU command execution end time in nanoseconds. This is the time the command reaches the bottom of the pipeline (BOP).", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "GPUBusy", "The percentage of time GPU was busy.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "GPUBusyCycles", "Number of GPU cycles that the GPU was busy.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "TessellatorBusy", "The percentage of time the tessellation engine is busy.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "TessellatorBusyCycles", "Number of GPU cycles that the tessellation engine is busy.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "VSBusy", "The percentage of time the ShaderUnit has vertex shader work to do.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "VSBusyCycles", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "VSTime", "Time vertex shaders are busy in nanoseconds.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "HSBusy", "The percentage of time the ShaderUnit has hull shader work to do.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "HSBusyCycles", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "HSTime", "Time hull shaders are busy in nanoseconds.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "GSBusy", "The percentage of time the ShaderUnit has geometry shader work to do.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "GSBusyCycles", "Number of GPU cycles that the ShaderUnit has geometry shader work to do.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "GSTime", "Time geometry shaders are busy in nanoseconds.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PSBusy", "The percentage of time the ShaderUnit has pixel shader work to do.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PSBusyCycles", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PSTime", "Time pixel shaders are busy in nanoseconds.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSBusy", "The percentage of time the ShaderUnit has compute shader work to do.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSBusyCycles", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "CSTime", "Time compute shaders are busy in nanoseconds.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PrimitiveAssemblyBusy", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PrimitiveAssemblyBusyCycles", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "TexUnitBusy", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "TexUnitBusyCycles", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "DepthStencilTestBusy", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "DepthStencilTestBusyCount", "Number of GPU cycles spent performing depth and stencil tests.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "DSBusy", "The percentage of time the ShaderUnit has domain shader work to do.", "| Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "DSBusyCycles", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", "| Graphics IP v8
    | Graphics IP v7"
    "DSTime", "Time domain shaders are busy in nanoseconds.", "| Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"

VertexShader Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "VSVerticesIn", "The number of vertices processed by the VS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "VSVALUInstCount", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "VSSALUInstCount", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "VSVALUBusy", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "VSVALUBusyCycles", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "VSSALUBusy", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "VSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"

HullShader Group
%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "HSPatches", "The number of patches processed by the HS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "HSVALUInstCount", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "HSSALUInstCount", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "HSVALUBusy", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "HSVALUBusyCycles", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "HSSALUBusy", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "HSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"

GeometryShader Group
%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "GSPrimsIn", "The number of primitives passed into the GS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "GSVerticesOut", "The number of vertices output by the GS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "GSVALUInstCount", "Average number of vector ALU instructions executed in the GS. Affected by flow control.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "GSSALUInstCount", "Average number of scalar ALU instructions executed in the GS. Affected by flow control.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "GSVALUBusy", "The percentage of GPUTime vector ALU instructions are being processed by the GS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "GSVALUBusyCycles", "Number of GPU cycles where vector ALU instructions are being processed by the GS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "GSSALUBusy", "The percentage of GPUTime scalar ALU instructions are being processed by the GS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "GSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are being processed by the GS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"

PrimitiveAssembly Group
%%%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "PrimitivesIn", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CulledPrims", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "ClippedPrims", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PAStalledOnRasterizer", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PAStalledOnRasterizerCycles", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"

PixelShader Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "PSPixelsOut", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PSExportStalls", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PSExportStallsCycles", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PSVALUInstCount", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PSSALUInstCount", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PSVALUBusy", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PSVALUBusyCycles", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PSSALUBusy", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"

ComputeShader Group
%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "CSThreadGroups", "Total number of thread groups.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSWavefronts", "The total number of wavefronts used for the CS.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSThreads", "The number of CS threads processed by the hardware.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSVALUInsts", "The average number of vector ALU instructions executed per work-item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSVALUUtilization", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSSALUInsts", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSVFetchInsts", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSSFetchInsts", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSVWriteInsts", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSFlatVMemInsts", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "CSVALUBusy", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSVALUBusyCycles", "Number of GPU cycles where vector ALU instructions are processed.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "CSSALUBusy", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are processed.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "CSMemUnitBusy", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSMemUnitBusyCycles", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "CSMemUnitStalled", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSMemUnitStalledCycles", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "CSWriteUnitStalledCycles", "Number of GPU cycles the write unit is stalled.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "CSGDSInsts", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSLDSInsts", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSFlatLDSInsts", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "CSALUStalledByLDS", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSALUStalledByLDSCycles", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "CSLDSBankConflict", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CSLDSBankConflictCycles", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "CSFetchSize", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", "| Graphics IP v7
    | Graphics IP v6"
    "CSWriteSize", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", "| Graphics IP v7
    | Graphics IP v6"
    "CSCacheHit", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", "| Graphics IP v7
    | Graphics IP v6"
    "CSCacheHitCount", "Count of fetch, write, atomic, and other instructions that hit the data cache.", "| Graphics IP v7"
    "CSCacheMissCount", "Count of fetch, write, atomic, and other instructions that miss the data cache.", "| Graphics IP v7"
    "CSWriteUnitStalled", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", "| Graphics IP v7
    | Graphics IP v6"

GlobalMemory Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "L1CacheHit", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Value range: 0% (no hit) to 100% (optimal).", "| Vega"
    "L1CacheHitCount", "Count of fetch, write, atomic, and other instructions that hit the data in L1 cache.", "| Vega"
    "L1CacheMissCount", "Count of fetch, write, atomic, and other instructions that miss the data in L1 cache.", "| Vega"
    "FetchSize", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", "| Vega
    | Graphics IP v8"
    "WriteSize", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", "| Vega
    | Graphics IP v8"
    "L2CacheHit", "The percentage of fetch, write, atomic, and other instructions that hit the L2 cache. Value range: 0% (no hit) to 100% (optimal).", "| Vega"
    "L2CacheMiss", "The percentage of fetch, write, atomic, and other instructions that miss the L2 cache. Value range: 0% (optimal) to 100% (all miss).", "| Vega"
    "L2CacheHitCount", "Count of fetch, write, atomic, and other instructions that hit the L2 cache.", "| Vega"
    "L2CacheMissCount", "Count of fetch, write, atomic, and other instructions that miss the L2 cache.", "| Vega"
    "MemUnitBusy", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", "| Vega
    | Graphics IP v8"
    "MemUnitStalled", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", "| Vega
    | Graphics IP v8"
    "WriteUnitStalled", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", "| Vega
    | Graphics IP v8"
    "CacheHit", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", "| Graphics IP v8"
    "CacheMiss", "The percentage of fetch, write, atomic, and other instructions that miss the data cache. Value range: 0% (optimal) to 100% (all miss).", "| Graphics IP v8"
    "CacheHitCount", "Count of fetch, write, atomic, and other instructions that hit the data cache.", "| Graphics IP v8"
    "CacheMissCount", "Count of fetch, write, atomic, and other instructions that miss the data cache.", "| Graphics IP v8"

TextureUnit Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "TexTriFilteringPct", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "TexTriFilteringCount", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "NoTexTriFilteringCount", "Count of pixels that did not receive trilinear filtering.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "TexVolFilteringPct", "Percentage of pixels that received volume filtering.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "TexVolFilteringCount", "Count of pixels that received volume filtering.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "NoTexVolFilteringCount", "Count of pixels that did not receive volume filtering.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "TexAveAnisotropy", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"

DepthAndStencil Group
%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "HiZTilesAccepted", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "HiZTilesAcceptedCount", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "HiZTilesRejectedCount", "Count of tiles not accepted by HiZ.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PreZTilesDetailCulled", "Percentage of tiles rejected because the associated prim had no contributing area.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PreZTilesDetailCulledCount", "Count of tiles rejected because the associated primitive had no contributing area.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PreZTilesDetailSurvivingCount", "Count of tiles surviving because the associated primitive had contributing area.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "HiZQuadsCulled", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "HiZQuadsCulledCount", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "HiZQuadsAcceptedCount", "Count of quads that did continue on in the pipeline after HiZ.", "| Vega
    | Graphics IP v7"
    "PreZQuadsCulled", "Percentage of quads rejected based on the detailZ and earlyZ tests.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PreZQuadsCulledCount", "Count of quads rejected based on the detailZ and earlyZ tests.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PreZQuadsSurvivingCount", "Count of quads surviving detailZ and earlyZ tests.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PostZQuads", "Percentage of quads for which the pixel shader will run and may be postZ tested.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PostZQuadCount", "Count of quads for which the pixel shader will run and may be postZ tested.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "PreZSamplesPassing", "Number of samples tested for Z before shading and passed.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PreZSamplesFailingS", "Number of samples tested for Z before shading and failed stencil test.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PreZSamplesFailingZ", "Number of samples tested for Z before shading and failed Z test.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PostZSamplesPassing", "Number of samples tested for Z after shading and passed.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PostZSamplesFailingS", "Number of samples tested for Z after shading and failed stencil test.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "PostZSamplesFailingZ", "Number of samples tested for Z after shading and failed Z test.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "ZUnitStalled", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "ZUnitStalledCycles", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"
    "DBMemRead", "Number of bytes read from the depth buffer.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "DBMemWritten", "Number of bytes written to the depth buffer.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "HiZQuadsSurvivingCount", "Count of quads that survive in the pipeline after HiZ.", "| Graphics IP v8"

ColorBuffer Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "CBMemRead", "Number of bytes read from the color buffer.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CBColorAndMaskRead", "Total number of bytes read from the color and mask buffers.", "| Vega
    | Graphics IP v8"
    "CBMemWritten", "Number of bytes written to the color buffer.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CBColorAndMaskWritten", "Total number of bytes written to the color and mask buffers.", "| Vega
    | Graphics IP v8"
    "CBSlowPixelPct", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", "| Vega
    | Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "CBSlowPixelCount", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", "| Vega
    | Graphics IP v8
    | Graphics IP v7"

DomainShader Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description", "Availability"
    :widths: 15, 60, 25

    "DSVerticesIn", "The number of vertices processed by the DS.", "| Graphics IP v8
    | Graphics IP v7
    | Graphics IP v6"
    "DSVALUInstCount", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", "| Graphics IP v8
    | Graphics IP v7"
    "DSSALUInstCount", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", "| Graphics IP v8
    | Graphics IP v7"
    "DSVALUBusy", "The percentage of GPUTime vector ALU instructions are being processed by the DS.", "| Graphics IP v8
    | Graphics IP v7"
    "DSVALUBusyCycles", "Number of GPU cycles where vector ALU instructions are being processed by the DS.", "| Graphics IP v8
    | Graphics IP v7"
    "DSSALUBusy", "The percentage of GPUTime scalar ALU instructions are being processed by the DS.", "| Graphics IP v8
    | Graphics IP v7"
    "DSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are being processed by the DS.", "| Graphics IP v8
    | Graphics IP v7"
