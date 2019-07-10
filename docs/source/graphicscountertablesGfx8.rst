.. Copyright(c) 2018-2019 Advanced Micro Devices, Inc.All rights reserved.
.. Graphics Performance Counters for Graphics IP v8

.. *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

Graphics IP v8 Counters
+++++++++++++++++++++++

Timing Group
%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "GPUTime", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel."
    "ExecutionDuration", "GPU command execution duration in nanoseconds, from the time the command enters the top of the pipeline (TOP) to the time the command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel."
    "ExecutionStart", "GPU command execution start time in nanoseconds. This is the time the command enters the top of the pipeline (TOP)."
    "ExecutionEnd", "GPU command execution end time in nanoseconds. This is the time the command reaches the bottom of the pipeline (BOP)."
    "GPUBusy", "The percentage of time GPU was busy."
    "GPUBusyCycles", "Number of GPU cycles that the GPU was busy."
    "TessellatorBusy", "The percentage of time the tessellation engine is busy."
    "TessellatorBusyCycles", "Number of GPU cycles that the tessellation engine is busy."
    "VSBusy", "The percentage of time the ShaderUnit has vertex shader work to do."
    "VSBusyCycles", "Number of GPU cycles that the ShaderUnit has vertex shader work to do."
    "VSTime", "Time vertex shaders are busy in nanoseconds."
    "HSBusy", "The percentage of time the ShaderUnit has hull shader work to do."
    "HSBusyCycles", "Number of GPU cycles that the ShaderUnit has hull shader work to do."
    "HSTime", "Time hull shaders are busy in nanoseconds."
    "DSBusy", "The percentage of time the ShaderUnit has domain shader work to do."
    "DSBusyCycles", "Number of GPU cycles that the ShaderUnit has domain shader work to do."
    "DSTime", "Time domain shaders are busy in nanoseconds."
    "GSBusy", "The percentage of time the ShaderUnit has geometry shader work to do."
    "GSBusyCycles", "Number of GPU cycles that the ShaderUnit has geometry shader work to do."
    "GSTime", "Time geometry shaders are busy in nanoseconds."
    "PSBusy", "The percentage of time the ShaderUnit has pixel shader work to do."
    "PSBusyCycles", "Number of GPU cycles that the ShaderUnit has pixel shader work to do."
    "PSTime", "Time pixel shaders are busy in nanoseconds."
    "CSBusy", "The percentage of time the ShaderUnit has compute shader work to do."
    "CSBusyCycles", "Number of GPU cycles that the ShaderUnit has compute shader work to do."
    "CSTime", "Time compute shaders are busy in nanoseconds."
    "PrimitiveAssemblyBusy", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck."
    "PrimitiveAssemblyBusyCycles", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck."
    "TexUnitBusy", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account."
    "TexUnitBusyCycles", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account."
    "DepthStencilTestBusy", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy."
    "DepthStencilTestBusyCount", "Number of GPU cycles spent performing depth and stencil tests."

VertexShader Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "VSVerticesIn", "The number of vertices processed by the VS."
    "VSVALUInstCount", "Average number of vector ALU instructions executed in the VS. Affected by flow control."
    "VSSALUInstCount", "Average number of scalar ALU instructions executed in the VS. Affected by flow control."
    "VSVALUBusy", "The percentage of GPUTime vector ALU instructions are being processed by the VS."
    "VSVALUBusyCycles", "Number of GPU cycles where vector ALU instructions are being processed by the VS."
    "VSSALUBusy", "The percentage of GPUTime scalar ALU instructions are being processed by the VS."
    "VSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are being processed by the VS."

HullShader Group
%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "HSPatches", "The number of patches processed by the HS."
    "HSVALUInstCount", "Average number of vector ALU instructions executed in the HS. Affected by flow control."
    "HSSALUInstCount", "Average number of scalar ALU instructions executed in the HS. Affected by flow control."
    "HSVALUBusy", "The percentage of GPUTime vector ALU instructions are being processed by the HS."
    "HSVALUBusyCycles", "Number of GPU cycles vector where ALU instructions are being processed by the HS."
    "HSSALUBusy", "The percentage of GPUTime scalar ALU instructions are being processed by the HS."
    "HSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are being processed by the HS."

DomainShader Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "DSVerticesIn", "The number of vertices processed by the DS."
    "DSVALUInstCount", "Average number of vector ALU instructions executed in the DS. Affected by flow control."
    "DSSALUInstCount", "Average number of scalar ALU instructions executed in the DS. Affected by flow control."
    "DSVALUBusy", "The percentage of GPUTime vector ALU instructions are being processed by the DS."
    "DSVALUBusyCycles", "Number of GPU cycles where vector ALU instructions are being processed by the DS."
    "DSSALUBusy", "The percentage of GPUTime scalar ALU instructions are being processed by the DS."
    "DSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are being processed by the DS."

GeometryShader Group
%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "GSPrimsIn", "The number of primitives passed into the GS."
    "GSVerticesOut", "The number of vertices output by the GS."
    "GSVALUInstCount", "Average number of vector ALU instructions executed in the GS. Affected by flow control."
    "GSSALUInstCount", "Average number of scalar ALU instructions executed in the GS. Affected by flow control."
    "GSVALUBusy", "The percentage of GPUTime vector ALU instructions are being processed by the GS."
    "GSVALUBusyCycles", "Number of GPU cycles where vector ALU instructions are being processed by the GS."
    "GSSALUBusy", "The percentage of GPUTime scalar ALU instructions are being processed by the GS."
    "GSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are being processed by the GS."

PrimitiveAssembly Group
%%%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "PrimitivesIn", "The number of primitives received by the hardware. This includes primitives generated by tessellation."
    "CulledPrims", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling."
    "ClippedPrims", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes."
    "PAStalledOnRasterizer", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations."
    "PAStalledOnRasterizerCycles", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations."

PixelShader Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "PSPixelsOut", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs."
    "PSExportStalls", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer."
    "PSExportStallsCycles", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer."
    "PSVALUInstCount", "Average number of vector ALU instructions executed in the PS. Affected by flow control."
    "PSSALUInstCount", "Average number of scalar ALU instructions executed in the PS. Affected by flow control."
    "PSVALUBusy", "The percentage of GPUTime vector ALU instructions are being processed by the PS."
    "PSVALUBusyCycles", "Number of GPU cycles where vector ALU instructions are being processed by the PS."
    "PSSALUBusy", "The percentage of GPUTime scalar ALU instructions are being processed by the PS."
    "PSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are being processed by the PS."

ComputeShader Group
%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "CSThreadGroups", "Total number of thread groups."
    "CSWavefronts", "The total number of wavefronts used for the CS."
    "CSThreads", "The number of CS threads processed by the hardware."
    "CSVALUInsts", "The average number of vector ALU instructions executed per work-item (affected by flow control)."
    "CSVALUUtilization", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence)."
    "CSSALUInsts", "The average number of scalar ALU instructions executed per work-item (affected by flow control)."
    "CSVFetchInsts", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control)."
    "CSSFetchInsts", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control)."
    "CSVWriteInsts", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control)."
    "CSFlatVMemInsts", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch."
    "CSVALUBusy", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal)."
    "CSVALUBusyCycles", "Number of GPU cycles where vector ALU instructions are processed."
    "CSSALUBusy", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal)."
    "CSSALUBusyCycles", "Number of GPU cycles where scalar ALU instructions are processed."
    "CSMemUnitBusy", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound)."
    "CSMemUnitBusyCycles", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account."
    "CSMemUnitStalled", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad)."
    "CSMemUnitStalledCycles", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible."
    "CSWriteUnitStalled", "The percentage of GPUTime the write unit is stalled."
    "CSWriteUnitStalledCycles", "Number of GPU cycles the write unit is stalled."
    "CSGDSInsts", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control)."
    "CSLDSInsts", "The average number of LDS read/write instructions executed per work-item (affected by flow control)."
    "CSFlatLDSInsts", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control)."
    "CSALUStalledByLDS", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad)."
    "CSALUStalledByLDSCycles", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible."
    "CSLDSBankConflict", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad)."
    "CSLDSBankConflictCycles", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad)."

TextureUnit Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "TexTriFilteringPct", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified)."
    "TexTriFilteringCount", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified)."
    "NoTexTriFilteringCount", "Count of pixels that did not receive trilinear filtering."
    "TexVolFilteringPct", "Percentage of pixels that received volume filtering."
    "TexVolFilteringCount", "Count of pixels that received volume filtering."
    "NoTexVolFilteringCount", "Count of pixels that did not receive volume filtering."
    "TexAveAnisotropy", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy."

DepthAndStencil Group
%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "HiZTilesAccepted", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers."
    "HiZTilesAcceptedCount", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers."
    "HiZTilesRejectedCount", "Count of tiles not accepted by HiZ."
    "PreZTilesDetailCulled", "Percentage of tiles rejected because the associated prim had no contributing area."
    "PreZTilesDetailCulledCount", "Count of tiles rejected because the associated primitive had no contributing area."
    "PreZTilesDetailSurvivingCount", "Count of tiles surviving because the associated primitive had contributing area."
    "HiZQuadsCulled", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized."
    "HiZQuadsCulledCount", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized."
    "HiZQuadsAcceptedCount", "Count of quads that did continue on in the pipeline after HiZ."
    "PreZQuadsCulled", "Percentage of quads rejected based on the detailZ and earlyZ tests."
    "PreZQuadsCulledCount", "Count of quads rejected based on the detailZ and earlyZ tests."
    "PreZQuadsSurvivingCount", "Count of quads surviving detailZ and earlyZ tests."
    "PostZQuads", "Percentage of quads for which the pixel shader will run and may be postZ tested."
    "PostZQuadCount", "Count of quads for which the pixel shader will run and may be postZ tested."
    "PreZSamplesPassing", "Number of samples tested for Z before shading and passed."
    "PreZSamplesFailingS", "Number of samples tested for Z before shading and failed stencil test."
    "PreZSamplesFailingZ", "Number of samples tested for Z before shading and failed Z test."
    "PostZSamplesPassing", "Number of samples tested for Z after shading and passed."
    "PostZSamplesFailingS", "Number of samples tested for Z after shading and failed stencil test."
    "PostZSamplesFailingZ", "Number of samples tested for Z after shading and failed Z test."
    "ZUnitStalled", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations."
    "ZUnitStalledCycles", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations."
    "DBMemRead", "Number of bytes read from the depth buffer."
    "DBMemWritten", "Number of bytes written to the depth buffer."

ColorBuffer Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "CBMemRead", "Number of bytes read from the color buffer."
    "CBColorAndMaskRead", "Total number of bytes read from the color and mask buffers."
    "CBMemWritten", "Number of bytes written to the color buffer."
    "CBColorAndMaskWritten", "Total number of bytes written to the color and mask buffers."
    "CBSlowPixelPct", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format."
    "CBSlowPixelCount", "Number of pixels written to the color buffer using a half-rate or quarter-rate format."

GlobalMemory Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Brief Description"
    :widths: 15, 80

    "FetchSize", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account."
    "WriteSize", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account."
    "CacheHit", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal)."
    "CacheMiss", "The percentage of fetch, write, atomic, and other instructions that miss the data cache. Value range: 0% (optimal) to 100% (all miss)."
    "CacheHitCount", "Count of fetch, write, atomic, and other instructions that hit the data cache."
    "CacheMissCount", "Count of fetch, write, atomic, and other instructions that miss the data cache."
    "MemUnitBusy", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound)."
    "MemUnitBusyCycles", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account."
    "MemUnitStalled", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad)."
    "MemUnitStalledCycles", "Number of GPU cycles the memory unit is stalled."
    "WriteUnitStalled", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad)."
    "WriteUnitStalledCycles", "Number of GPU cycles the Write unit is stalled."
