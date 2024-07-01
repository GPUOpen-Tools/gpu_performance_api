.. Copyright(c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
.. Graphics Performance Counters for Graphics IP v8

.. *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

Graphics IP v8 Counters
+++++++++++++++++++++++

Timing Group
%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "GPUTime", "Nanoseconds", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel."
    "ExecutionDuration", "Nanoseconds", "GPU command execution duration in nanoseconds, from the time the command enters the top of the pipeline (TOP) to the time the command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel."
    "ExecutionStart", "Nanoseconds", "GPU command execution start time in nanoseconds. This is the time the command enters the top of the pipeline (TOP)."
    "ExecutionEnd", "Nanoseconds", "GPU command execution end time in nanoseconds. This is the time the command reaches the bottom of the pipeline (BOP)."
    "GPUBusy", "Percentage", "The percentage of time GPU was busy."
    "GPUBusyCycles", "Cycles", "Number of GPU cycles that the GPU was busy."
    "TessellatorBusy", "Percentage", "The percentage of time the tessellation engine is busy."
    "TessellatorBusyCycles", "Cycles", "Number of GPU cycles that the tessellation engine is busy."
    "VSBusy", "Percentage", "The percentage of time the ShaderUnit has vertex shader work to do."
    "VSBusyCycles", "Cycles", "Number of GPU cycles that the ShaderUnit has vertex shader work to do."
    "VSTime", "Nanoseconds", "Time vertex shaders are busy in nanoseconds."
    "HSBusy", "Percentage", "The percentage of time the ShaderUnit has hull shader work to do."
    "HSBusyCycles", "Cycles", "Number of GPU cycles that the ShaderUnit has hull shader work to do."
    "HSTime", "Nanoseconds", "Time hull shaders are busy in nanoseconds."
    "DSBusy", "Percentage", "The percentage of time the ShaderUnit has domain shader work to do."
    "DSBusyCycles", "Cycles", "Number of GPU cycles that the ShaderUnit has domain shader work to do."
    "DSTime", "Nanoseconds", "Time domain shaders are busy in nanoseconds."
    "GSBusy", "Percentage", "The percentage of time the ShaderUnit has geometry shader work to do."
    "GSBusyCycles", "Cycles", "Number of GPU cycles that the ShaderUnit has geometry shader work to do."
    "GSTime", "Nanoseconds", "Time geometry shaders are busy in nanoseconds."
    "PSBusy", "Percentage", "The percentage of time the ShaderUnit has pixel shader work to do."
    "PSBusyCycles", "Cycles", "Number of GPU cycles that the ShaderUnit has pixel shader work to do."
    "PSTime", "Nanoseconds", "Time pixel shaders are busy in nanoseconds."
    "CSBusy", "Percentage", "The percentage of time the ShaderUnit has compute shader work to do."
    "CSBusyCycles", "Cycles", "Number of GPU cycles that the ShaderUnit has compute shader work to do."
    "CSTime", "Nanoseconds", "Time compute shaders are busy in nanoseconds."
    "PrimitiveAssemblyBusy", "Percentage", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck."
    "PrimitiveAssemblyBusyCycles", "Cycles", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck."
    "TexUnitBusy", "Percentage", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account."
    "TexUnitBusyCycles", "Cycles", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account."
    "DepthStencilTestBusy", "Percentage", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy."
    "DepthStencilTestBusyCycles", "Cycles", "Number of GPU cycles spent performing depth and stencil tests."

VertexShader Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "VSVerticesIn", "Items", "The number of vertices processed by the VS."
    "VSVALUInstCount", "Items", "Average number of vector ALU instructions executed in the VS. Affected by flow control."
    "VSSALUInstCount", "Items", "Average number of scalar ALU instructions executed in the VS. Affected by flow control."
    "VSVALUBusy", "Percentage", "The percentage of GPUTime vector ALU instructions are being processed by the VS."
    "VSVALUBusyCycles", "Cycles", "Number of GPU cycles where vector ALU instructions are being processed by the VS."
    "VSSALUBusy", "Percentage", "The percentage of GPUTime scalar ALU instructions are being processed by the VS."
    "VSSALUBusyCycles", "Cycles", "Number of GPU cycles where scalar ALU instructions are being processed by the VS."

HullShader Group
%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "HSPatches", "Items", "The number of patches processed by the HS."
    "HSVALUInstCount", "Items", "Average number of vector ALU instructions executed in the HS. Affected by flow control."
    "HSSALUInstCount", "Items", "Average number of scalar ALU instructions executed in the HS. Affected by flow control."
    "HSVALUBusy", "Percentage", "The percentage of GPUTime vector ALU instructions are being processed by the HS."
    "HSVALUBusyCycles", "Cycles", "Number of GPU cycles vector where ALU instructions are being processed by the HS."
    "HSSALUBusy", "Percentage", "The percentage of GPUTime scalar ALU instructions are being processed by the HS."
    "HSSALUBusyCycles", "Cycles", "Number of GPU cycles where scalar ALU instructions are being processed by the HS."

DomainShader Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "DSVerticesIn", "Items", "The number of vertices processed by the DS."
    "DSVALUInstCount", "Items", "Average number of vector ALU instructions executed in the DS. Affected by flow control."
    "DSSALUInstCount", "Items", "Average number of scalar ALU instructions executed in the DS. Affected by flow control."
    "DSVALUBusy", "Percentage", "The percentage of GPUTime vector ALU instructions are being processed by the DS."
    "DSVALUBusyCycles", "Cycles", "Number of GPU cycles where vector ALU instructions are being processed by the DS."
    "DSSALUBusy", "Percentage", "The percentage of GPUTime scalar ALU instructions are being processed by the DS."
    "DSSALUBusyCycles", "Cycles", "Number of GPU cycles where scalar ALU instructions are being processed by the DS."

GeometryShader Group
%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "GSPrimsIn", "Items", "The number of primitives passed into the GS."
    "GSVerticesOut", "Items", "The number of vertices output by the GS."
    "GSVALUInstCount", "Items", "Average number of vector ALU instructions executed in the GS. Affected by flow control."
    "GSSALUInstCount", "Items", "Average number of scalar ALU instructions executed in the GS. Affected by flow control."
    "GSVALUBusy", "Percentage", "The percentage of GPUTime vector ALU instructions are being processed by the GS."
    "GSVALUBusyCycles", "Cycles", "Number of GPU cycles where vector ALU instructions are being processed by the GS."
    "GSSALUBusy", "Percentage", "The percentage of GPUTime scalar ALU instructions are being processed by the GS."
    "GSSALUBusyCycles", "Cycles", "Number of GPU cycles where scalar ALU instructions are being processed by the GS."

PrimitiveAssembly Group
%%%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "PrimitivesIn", "Items", "The number of primitives received by the hardware. This includes primitives generated by tessellation."
    "CulledPrims", "Items", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling."
    "ClippedPrims", "Items", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes."
    "PAStalledOnRasterizer", "Percentage", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations."
    "PAStalledOnRasterizerCycles", "Cycles", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations."

PixelShader Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "PSPixelsOut", "Items", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs."
    "PSExportStalls", "Percentage", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer."
    "PSExportStallsCycles", "Cycles", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer."
    "PSVALUInstCount", "Items", "Average number of vector ALU instructions executed in the PS. Affected by flow control."
    "PSSALUInstCount", "Items", "Average number of scalar ALU instructions executed in the PS. Affected by flow control."
    "PSVALUBusy", "Percentage", "The percentage of GPUTime vector ALU instructions are being processed by the PS."
    "PSVALUBusyCycles", "Cycles", "Number of GPU cycles where vector ALU instructions are being processed by the PS."
    "PSSALUBusy", "Percentage", "The percentage of GPUTime scalar ALU instructions are being processed by the PS."
    "PSSALUBusyCycles", "Cycles", "Number of GPU cycles where scalar ALU instructions are being processed by the PS."

ComputeShader Group
%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "CSThreadGroups", "Items", "Total number of thread groups."
    "CSWavefronts", "Items", "The total number of wavefronts used for the CS."
    "CSThreads", "Items", "The number of CS threads processed by the hardware."
    "CSThreadGroupSize", "Items", "The number of CS threads within each thread group."
    "CSVALUInsts", "Items", "The average number of vector ALU instructions executed per work-item (affected by flow control)."
    "CSVALUUtilization", "Percentage", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence)."
    "CSSALUInsts", "Items", "The average number of scalar ALU instructions executed per work-item (affected by flow control)."
    "CSVFetchInsts", "Items", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control)."
    "CSSFetchInsts", "Items", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control)."
    "CSVWriteInsts", "Items", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control)."
    "CSFlatVMemInsts", "Items", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch."
    "CSVALUBusy", "Percentage", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal)."
    "CSVALUBusyCycles", "Cycles", "Number of GPU cycles where vector ALU instructions are processed."
    "CSSALUBusy", "Percentage", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal)."
    "CSSALUBusyCycles", "Cycles", "Number of GPU cycles where scalar ALU instructions are processed."
    "CSMemUnitBusy", "Percentage", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound)."
    "CSMemUnitBusyCycles", "Cycles", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account."
    "CSMemUnitStalled", "Percentage", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad)."
    "CSMemUnitStalledCycles", "Cycles", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible."
    "CSWriteUnitStalled", "Percentage", "The percentage of GPUTime the write unit is stalled."
    "CSWriteUnitStalledCycles", "Cycles", "Number of GPU cycles the write unit is stalled."
    "CSGDSInsts", "Items", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control)."
    "CSLDSInsts", "Items", "The average number of LDS read/write instructions executed per work-item (affected by flow control)."
    "CSFlatLDSInsts", "Items", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control)."
    "CSALUStalledByLDS", "Percentage", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad)."
    "CSALUStalledByLDSCycles", "Cycles", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible."
    "CSLDSBankConflict", "Percentage", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad)."
    "CSLDSBankConflictCycles", "Cycles", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad)."

TextureUnit Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "TexTriFilteringPct", "Percentage", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified)."
    "TexTriFilteringCount", "Items", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified)."
    "NoTexTriFilteringCount", "Items", "Count of pixels that did not receive trilinear filtering."
    "TexVolFilteringPct", "Percentage", "Percentage of pixels that received volume filtering."
    "TexVolFilteringCount", "Items", "Count of pixels that received volume filtering."
    "NoTexVolFilteringCount", "Items", "Count of pixels that did not receive volume filtering."
    "TexAveAnisotropy", "Items", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy."

DepthAndStencil Group
%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "HiZTilesAccepted", "Percentage", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers."
    "HiZTilesAcceptedCount", "Items", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers."
    "HiZTilesRejectedCount", "Items", "Count of tiles not accepted by HiZ."
    "PreZTilesDetailCulled", "Percentage", "Percentage of tiles rejected because the associated prim had no contributing area."
    "PreZTilesDetailCulledCount", "Items", "Count of tiles rejected because the associated primitive had no contributing area."
    "PreZTilesDetailSurvivingCount", "Items", "Count of tiles surviving because the associated primitive had contributing area."
    "HiZQuadsCulled", "Percentage", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized."
    "HiZQuadsCulledCount", "Items", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized."
    "HiZQuadsAcceptedCount", "Items", "Count of quads that did continue on in the pipeline after HiZ."
    "PreZQuadsCulled", "Percentage", "Percentage of quads rejected based on the detailZ and earlyZ tests."
    "PreZQuadsCulledCount", "Items", "Count of quads rejected based on the detailZ and earlyZ tests."
    "PreZQuadsSurvivingCount", "Items", "Count of quads surviving detailZ and earlyZ tests."
    "PostZQuads", "Percentage", "Percentage of quads for which the pixel shader will run and may be postZ tested."
    "PostZQuadCount", "Items", "Count of quads for which the pixel shader will run and may be postZ tested."
    "PreZSamplesPassing", "Items", "Number of samples tested for Z before shading and passed."
    "PreZSamplesFailingS", "Items", "Number of samples tested for Z before shading and failed stencil test."
    "PreZSamplesFailingZ", "Items", "Number of samples tested for Z before shading and failed Z test."
    "PostZSamplesPassing", "Items", "Number of samples tested for Z after shading and passed."
    "PostZSamplesFailingS", "Items", "Number of samples tested for Z after shading and failed stencil test."
    "PostZSamplesFailingZ", "Items", "Number of samples tested for Z after shading and failed Z test."
    "ZUnitStalled", "Percentage", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations."
    "ZUnitStalledCycles", "Cycles", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations."
    "DBMemRead", "Bytes", "Number of bytes read from the depth buffer."
    "DBMemWritten", "Bytes", "Number of bytes written to the depth buffer."

ColorBuffer Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "CBMemRead", "Bytes", "Number of bytes read from the color buffer."
    "CBColorAndMaskRead", "Bytes", "Total number of bytes read from the color and mask buffers."
    "CBMemWritten", "Bytes", "Number of bytes written to the color buffer."
    "CBColorAndMaskWritten", "Bytes", "Total number of bytes written to the color and mask buffers."
    "CBSlowPixelPct", "Percentage", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format."
    "CBSlowPixelCount", "Items", "Number of pixels written to the color buffer using a half-rate or quarter-rate format."

MemoryCache Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "L0TagConflictReadStalledCycles", "Items", "The number of cycles read operations from the L0 cache are stalled due to tag conflicts."
    "L0TagConflictWriteStalledCycles", "Items", "The number of cycles write operations to the L0 cache are stalled due to tag conflicts."
    "L0TagConflictAtomicStalledCycles", "Items", "The number of cycles atomic operations on the L0 cache are stalled due to tag conflicts."

GlobalMemory Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "FetchSize", "Bytes", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account."
    "WriteSize", "Bytes", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account."
    "CacheHit", "Percentage", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal)."
    "CacheMiss", "Percentage", "The percentage of fetch, write, atomic, and other instructions that miss the data cache. Value range: 0% (optimal) to 100% (all miss)."
    "CacheHitCount", "Items", "Count of fetch, write, atomic, and other instructions that hit the data cache."
    "CacheMissCount", "Items", "Count of fetch, write, atomic, and other instructions that miss the data cache."
    "MemUnitBusy", "Percentage", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound)."
    "MemUnitBusyCycles", "Cycles", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account."
    "MemUnitStalled", "Percentage", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad)."
    "MemUnitStalledCycles", "Cycles", "Number of GPU cycles the memory unit is stalled."
    "WriteUnitStalled", "Percentage", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad)."
    "WriteUnitStalledCycles", "Cycles", "Number of GPU cycles the Write unit is stalled."
