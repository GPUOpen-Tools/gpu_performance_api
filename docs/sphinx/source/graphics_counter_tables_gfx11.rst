.. Copyright(c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
.. Graphics Performance Counters for RDNA3

.. *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

RDNA3 Counters
++++++++++++++

Timing Group
%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "GPUTime", "Nanoseconds", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel."
    "ExecutionDuration", "Nanoseconds", "GPU command execution duration in nanoseconds, from the time the command enters the top of the pipeline (TOP) to the time the command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel."
    "ExecutionStart", "Nanoseconds", "GPU command execution start time in nanoseconds. This is the time the command enters the top of the pipeline (TOP)."
    "ExecutionEnd", "Nanoseconds", "GPU command execution end time in nanoseconds. This is the time the command reaches the bottom of the pipeline (BOP)."
    "GPUBusy", "Percentage", "The percentage of time the GPU command processor was busy."
    "GPUBusyCycles", "Cycles", "Number of GPU cycles that the GPU command processor was busy."
    "TessellatorBusy", "Percentage", "The percentage of time the tessellation engine is busy."
    "TessellatorBusyCycles", "Cycles", "Number of GPU cycles that the tessellation engine is busy."
    "VsGsBusy", "Percentage", "The percentage of time the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline."
    "VsGsBusyCycles", "Cycles", "Number of GPU cycles that the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline."
    "VsGsTime", "Nanoseconds", "Time VS or GS are busy in nanoseconds in a VS-[GS-]PS pipeline."
    "PreTessellationBusy", "Percentage", "The percentage of time the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation."
    "PreTessellationBusyCycles", "Cycles", "Number of GPU cycles that the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation."
    "PreTessellationTime", "Nanoseconds", "Time VS and HS are busy in nanoseconds in a pipeline that uses tessellation."
    "PostTessellationBusy", "Percentage", "The percentage of time the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation."
    "PostTessellationBusyCycles", "Cycles", "Number of GPU cycles that the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation."
    "PostTessellationTime", "Nanoseconds", "Time DS or GS are busy in nanoseconds in a pipeline that uses tessellation."
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

VertexGeometry Group
%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "VsGsVerticesIn", "Items", "The number of unique vertices processed by the VS and GS."
    "VsGsPrimsIn", "Items", "The number of primitives passed into the GS."

PreTessellation Group
%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "PreTessVerticesIn", "Items", "The number of unique vertices processed by the VS and HS when using tessellation."

PostTessellation Group
%%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "PostTessPrimsOut", "Items", "The number of primitives output by the DS and GS when using tessellation."

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

ComputeShader Group
%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "CSThreadGroups", "Items", "Total number of thread groups."
    "CSWavefronts", "Items", "The total number of wavefronts used for the CS."
    "CSThreads", "Items", "The number of CS threads processed by the hardware."
    "CSThreadGroupSize", "Items", "The number of CS threads within each thread group."
    "CSMemUnitBusy", "Percentage", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound)."
    "CSMemUnitBusyCycles", "Cycles", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account."
    "CSMemUnitStalled", "Percentage", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad)."
    "CSMemUnitStalledCycles", "Cycles", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible."
    "CSWriteUnitStalled", "Percentage", "The percentage of GPUTime the write unit is stalled."
    "CSWriteUnitStalledCycles", "Cycles", "Number of GPU cycles the write unit is stalled."
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

MemoryCache Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "L0CacheHit", "Percentage", "The percentage of read requests that hit the data in the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal)."
    "L0CacheRequestCount", "Items", "The number of read requests made to the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size."
    "L0CacheHitCount", "Items", "The number of read requests which result in a cache hit from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size."
    "L0CacheMissCount", "Items", "The number of read requests which result in a cache miss from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size."
    "ScalarCacheHit", "Percentage", "The percentage of read requests made from executing shader code that hit the data in the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size. Value range: 0% (no hit) to 100% (optimal)."
    "ScalarCacheRequestCount", "Items", "The number of read requests made from executing shader code to the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size."
    "ScalarCacheHitCount", "Items", "The number of read requests made from executing shader code which result in a cache hit from the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size."
    "ScalarCacheMissCount", "Items", "The number of read requests made from executing shader code which result in a cache miss from the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size."
    "InstCacheHit", "Percentage", "The percentage of read requests made that hit the data in the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size. Value range: 0% (no hit) to 100% (optimal)."
    "InstCacheRequestCount", "Items", "The number of read requests made to the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size."
    "InstCacheHitCount", "Items", "The number of read requests which result in a cache hit from the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size."
    "InstCacheMissCount", "Items", "The number of read requests which result in a cache miss from the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size."
    "L1CacheHit", "Percentage", "The percentage of read or write requests that hit the data in the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal)."
    "L1CacheRequestCount", "Items", "The number of read or write requests made to the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size."
    "L1CacheHitCount", "Items", "The number of read or write requests which result in a cache hit from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size."
    "L1CacheMissCount", "Items", "The number of read or write requests which result in a cache miss from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size."
    "L2CacheHit", "Percentage", "The percentage of read or write requests that hit the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal)."
    "L2CacheMiss", "Percentage", "The percentage of read or write requests that miss the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (optimal) to 100% (all miss)."
    "L2CacheRequestCount", "Items", "The number of read or write requests made to the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size."
    "L2CacheHitCount", "Items", "The number of read or write requests which result in a cache hit from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size."
    "L2CacheMissCount", "Items", "The number of read or write requests which result in a cache miss from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size."
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
    "MemUnitBusy", "Percentage", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound)."
    "MemUnitBusyCycles", "Cycles", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account."
    "MemUnitStalled", "Percentage", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad)."
    "MemUnitStalledCycles", "Cycles", "Number of GPU cycles the memory unit is stalled."
    "WriteUnitStalled", "Percentage", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad)."
    "WriteUnitStalledCycles", "Cycles", "Number of GPU cycles the Write unit is stalled."
    "LocalVidMemBytes", "Bytes", "Number of bytes read from or written to the Infinity Cache (if available) or local video memory"
    "PcieBytes", "Bytes", "Number of bytes sent and received over the PCIe bus"

RayTracing Group
%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Usage", "Brief Description"
    :widths: 15, 10, 75

    "RayTriTests", "Items", "The number of ray triangle intersection tests."
    "RayBoxTests", "Items", "The number of ray box intersection tests."
    "TotalRayTests", "Items", "Total number of ray intersection tests, includes both box and triangle intersections."
    "RayTestsPerWave", "Items", "The number of ray intersection tests per wave."
