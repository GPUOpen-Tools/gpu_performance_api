.. Graphics Performance Counters for RDNA

.. *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

RDNA Counters
+++++++++++++

Timing Group
%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "GPUTime", "Discrete", "Nanoseconds", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel."
    "GPUBusy", "Discrete, Streaming", "Percentage", "The percentage of time the GPU command processor was busy."
    "GPUBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles that the GPU command processor was busy."
    "TessellatorBusy", "Discrete, Streaming", "Percentage", "The percentage of time the tessellation engine is busy."
    "TessellatorBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles that the tessellation engine is busy."
    "VsGsBusy", "Discrete, Streaming", "Percentage", "The percentage of time the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline."
    "VsGsBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles that the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline."
    "VsGsTime", "Discrete", "Nanoseconds", "Time VS or GS are busy in nanoseconds in a VS-[GS-]PS pipeline."
    "PreTessellationBusy", "Discrete, Streaming", "Percentage", "The percentage of time the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation."
    "PreTessellationBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles that the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation."
    "PreTessellationTime", "Discrete", "Nanoseconds", "Time VS and HS are busy in nanoseconds in a pipeline that uses tessellation."
    "PostTessellationBusy", "Discrete, Streaming", "Percentage", "The percentage of time the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation."
    "PostTessellationBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles that the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation."
    "PostTessellationTime", "Discrete", "Nanoseconds", "Time DS or GS are busy in nanoseconds in a pipeline that uses tessellation."
    "PSBusy", "Discrete, Streaming", "Percentage", "The percentage of time the ShaderUnit has pixel shader work to do."
    "PSBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles that the ShaderUnit has pixel shader work to do."
    "PSTime", "Discrete", "Nanoseconds", "Time pixel shaders are busy in nanoseconds."
    "CSBusy", "Discrete, Streaming", "Percentage", "The percentage of time the ShaderUnit has compute shader work to do."
    "CSBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles that the ShaderUnit has compute shader work to do."
    "CSTime", "Discrete", "Nanoseconds", "Time compute shaders are busy in nanoseconds."
    "PrimitiveAssemblyBusy", "Discrete", "Percentage", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck."
    "PrimitiveAssemblyBusyCycles", "Discrete", "Cycles", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck."
    "TexUnitBusy", "Discrete, Streaming", "Percentage", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account."
    "TexUnitBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account."
    "DepthStencilTestBusy", "Discrete, Streaming", "Percentage", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy."
    "DepthStencilTestBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles spent performing depth and stencil tests."
    "ExecutionDuration", "Discrete", "Nanoseconds", "GPU command execution duration in nanoseconds, from the time the command enters the top of the pipeline (TOP) to the time the command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel."
    "ExecutionStart", "Discrete", "Nanoseconds", "GPU command execution start time in nanoseconds. This is the time the command enters the top of the pipeline (TOP)."
    "ExecutionEnd", "Discrete", "Nanoseconds", "GPU command execution end time in nanoseconds. This is the time the command reaches the bottom of the pipeline (BOP)."

VertexGeometry Group
%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "GSVerticesOut", "Discrete, Streaming", "Items", "The number of vertices output by the GS."

PreTessellation Group
%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "PreTessVerticesIn", "Discrete, Streaming", "Items", "The number of vertices processed by the VS and HS when using tessellation."
    "PreTessVALUInstCount", "Discrete, Streaming", "Items", "Average number of vector ALU instructions executed for the VS and HS in a pipeline that uses tessellation. Affected by flow control."
    "PreTessSALUInstCount", "Discrete, Streaming", "Items", "Average number of scalar ALU instructions executed for the VS and HS in a pipeline that uses tessellation. Affected by flow control."
    "PreTessVALUBusy", "Discrete, Streaming", "Percentage", "The percentage of GPUTime vector ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation."
    "PreTessVALUBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles vector where ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation."
    "PreTessSALUBusy", "Discrete, Streaming", "Percentage", "The percentage of GPUTime scalar ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation."
    "PreTessSALUBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles where scalar ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation."

PostTessellation Group
%%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "PostTessPrimsOut", "Discrete, Streaming", "Items", "The number of primitives output by the DS and GS when using tessellation."
    "PostTessVALUInstCount", "Discrete, Streaming", "Items", "Average number of vector ALU instructions executed for the DS and GS in a pipeline that uses tessellation. Affected by flow control."
    "PostTessSALUInstCount", "Discrete", "Items", "Average number of scalar ALU instructions executed for the DS and GS in a pipeline that uses tessellation. Affected by flow control."
    "PostTessVALUBusy", "Discrete, Streaming", "Percentage", "The percentage of GPUTime vector ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation."
    "PostTessVALUBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles vector where ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation."
    "PostTessSALUBusy", "Discrete, Streaming", "Percentage", "The percentage of GPUTime scalar ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation."
    "PostTessSALUBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles where scalar ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation."

PrimitiveAssembly Group
%%%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "PrimitivesIn", "Discrete, Streaming", "Items", "The number of primitives received by the hardware. This includes primitives generated by tessellation."
    "CulledPrims", "Discrete", "Items", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling."
    "ClippedPrims", "Discrete, Streaming", "Items", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes."
    "PAStalledOnRasterizer", "Discrete, Streaming", "Percentage", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations."
    "PAStalledOnRasterizerCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations."

PixelShader Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "PSPixelsOut", "Discrete, Streaming", "Items", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs."
    "PSExportStalls", "Discrete, Streaming", "Percentage", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer."
    "PSExportStallsCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer."

ComputeShader Group
%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "CSThreadGroupsLaunched", "Discrete, Streaming", "Items", "Total number of thread groups launched."
    "CSWavefrontsLaunched", "Discrete, Streaming", "Items", "The total number of wavefronts launched for the CS."
    "CSThreadsLaunched", "Discrete, Streaming", "Items", "The number of CS threads launched and processed by the hardware."
    "CSThreadGroupSize", "Discrete", "Items", "The number of CS threads within each thread group."
    "CSVALUInsts", "Discrete", "Items", "The average number of vector ALU instructions executed per work-item (affected by flow control)."
    "CSVALUUtilization", "Discrete", "Percentage", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence)."
    "CSSALUInsts", "Discrete", "Items", "The average number of scalar ALU instructions executed per work-item (affected by flow control)."
    "CSVFetchInsts", "Discrete", "Items", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control)."
    "CSSFetchInsts", "Discrete", "Items", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control)."
    "CSVWriteInsts", "Discrete", "Items", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control)."
    "CSVALUBusy", "Discrete, Streaming", "Percentage", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal)."
    "CSVALUBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles where vector ALU instructions are processed."
    "CSSALUBusy", "Discrete, Streaming", "Percentage", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal)."
    "CSSALUBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles where scalar ALU instructions are processed."
    "CSGDSInsts", "Discrete", "Items", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control)."
    "CSLDSInsts", "Discrete", "Items", "The average number of LDS read/write instructions executed per work-item (affected by flow control)."
    "CSALUStalledByLDS", "Discrete", "Percentage", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad)."
    "CSALUStalledByLDSCycles", "Discrete", "Cycles", "Number of GPU cycles each wavefronts' ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible."
    "CSLDSBankConflict", "Discrete, Streaming", "Percentage", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad)."
    "CSLDSBankConflictCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad)."
    "CSALUStalledByLDSPerWave", "Streaming", "Percentage", "The average percentage of GPUTime each wavefront's ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad)."

TextureUnit Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "TexTriFilteringPct", "Discrete, Streaming", "Percentage", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified)."
    "TexTriFilteringCount", "Discrete, Streaming", "Items", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified)."
    "NoTexTriFilteringCount", "Discrete, Streaming", "Items", "Count of pixels that did not receive trilinear filtering."
    "TexVolFilteringPct", "Discrete, Streaming", "Percentage", "Percentage of pixels that received volume filtering."
    "TexVolFilteringCount", "Discrete, Streaming", "Items", "Count of pixels that received volume filtering."
    "NoTexVolFilteringCount", "Discrete, Streaming", "Items", "Count of pixels that did not receive volume filtering."
    "TexAveAnisotropy", "Discrete", "Items", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy."

DepthAndStencil Group
%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "HiZTilesAccepted", "Discrete, Streaming", "Percentage", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers."
    "HiZTilesAcceptedCount", "Discrete, Streaming", "Items", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers."
    "HiZTilesRejectedCount", "Discrete, Streaming", "Items", "Count of tiles not accepted by HiZ."
    "PreZTilesDetailCulled", "Discrete, Streaming", "Percentage", "Percentage of tiles rejected because the associated prim had no contributing area."
    "PreZTilesDetailCulledCount", "Discrete, Streaming", "Items", "Count of tiles rejected because the associated primitive had no contributing area."
    "PreZTilesDetailSurvivingCount", "Discrete, Streaming", "Items", "Count of tiles surviving because the associated primitive had contributing area."
    "HiZQuadsCulled", "Discrete", "Percentage", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized."
    "HiZQuadsCulledCount", "Discrete", "Items", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized."
    "HiZQuadsAcceptedCount", "Discrete, Streaming", "Items", "Count of quads that did continue on in the pipeline after HiZ."
    "PreZQuadsCulled", "Discrete", "Percentage", "Percentage of quads rejected based on the detailZ and earlyZ tests."
    "PreZQuadsCulledCount", "Discrete", "Items", "Count of quads rejected based on the detailZ and earlyZ tests."
    "PreZQuadsSurvivingCount", "Discrete", "Items", "Count of quads surviving detailZ and earlyZ tests."
    "PostZQuads", "Discrete", "Percentage", "Percentage of quads for which the pixel shader will run and may be postZ tested."
    "PostZQuadCount", "Discrete, Streaming", "Items", "Count of quads for which the pixel shader will run and may be postZ tested."
    "PreZSamplesPassing", "Discrete, Streaming", "Items", "Number of samples tested for Z before shading and passed."
    "PreZSamplesFailingS", "Discrete, Streaming", "Items", "Number of samples tested for Z before shading and failed stencil test."
    "PreZSamplesFailingZ", "Discrete, Streaming", "Items", "Number of samples tested for Z before shading and failed Z test."
    "PostZSamplesPassing", "Discrete, Streaming", "Items", "Number of samples tested for Z after shading and passed."
    "PostZSamplesFailingS", "Discrete, Streaming", "Items", "Number of samples tested for Z after shading and failed stencil test."
    "PostZSamplesFailingZ", "Discrete, Streaming", "Items", "Number of samples tested for Z after shading and failed Z test."
    "ZUnitStalled", "Discrete, Streaming", "Percentage", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations."
    "ZUnitStalledCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations."
    "DBMemRead", "Discrete, Streaming", "Bytes", "Number of bytes read from the depth buffer."
    "DBMemWritten", "Discrete, Streaming", "Bytes", "Number of bytes written to the depth buffer."

ColorBuffer Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "CBMemRead", "Discrete, Streaming", "Bytes", "Number of bytes read from the color buffer."
    "CBColorAndMaskRead", "Discrete, Streaming", "Bytes", "Total number of bytes read from the color and mask buffers."
    "CBMemWritten", "Discrete, Streaming", "Bytes", "Number of bytes written to the color buffer."
    "CBColorAndMaskWritten", "Discrete, Streaming", "Bytes", "Total number of bytes written to the color and mask buffers."
    "CBSlowPixelPct", "Discrete, Streaming", "Percentage", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format."
    "CBSlowPixelCount", "Discrete, Streaming", "Items", "Number of pixels written to the color buffer using a half-rate or quarter-rate format."

MemoryCache Group
%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "L0CacheHit", "Discrete, Streaming", "Percentage", "The percentage of read requests that hit the data in the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal)."
    "L0CacheRequestCount", "Discrete, Streaming", "Items", "The number of read requests made to the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size."
    "L0CacheHitCount", "Discrete, Streaming", "Items", "The number of read requests which result in a cache hit from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size."
    "L0CacheMissCount", "Discrete, Streaming", "Items", "The number of read requests which result in a cache miss from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size."
    "L1CacheHit", "Discrete, Streaming", "Percentage", "The percentage of read or write requests that hit the data in the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal)."
    "L1CacheRequestCount", "Discrete, Streaming", "Items", "The number of read or write requests made to the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size."
    "L1CacheHitCount", "Discrete, Streaming", "Items", "The number of read or write requests which result in a cache hit from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size."
    "L1CacheMissCount", "Discrete, Streaming", "Items", "The number of read or write requests which result in a cache miss from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size."
    "L2CacheHit", "Discrete, Streaming", "Percentage", "The percentage of read or write requests that hit the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal)."
    "L2CacheMiss", "Discrete, Streaming", "Percentage", "The percentage of read or write requests that miss the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (optimal) to 100% (all miss)."
    "L2CacheRequestCount", "Discrete, Streaming", "Items", "The number of read or write requests made to the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size."
    "L2CacheHitCount", "Discrete, Streaming", "Items", "The number of read or write requests which result in a cache hit from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size."
    "L2CacheMissCount", "Discrete, Streaming", "Items", "The number of read or write requests which result in a cache miss from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size."
    "L0TagConflictReadStalledCycles", "Discrete, Streaming", "Items", "The number of cycles read operations from the L0 cache are stalled due to tag conflicts."
    "L0TagConflictWriteStalledCycles", "Discrete, Streaming", "Items", "The number of cycles write operations to the L0 cache are stalled due to tag conflicts."
    "L0TagConflictAtomicStalledCycles", "Discrete, Streaming", "Items", "The number of cycles atomic operations on the L0 cache are stalled due to tag conflicts."
    "ScalarCacheHit", "Discrete, Streaming", "Percentage", "The percentage of read requests made from executing shader code that hit the data in the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size. Value range: 0% (no hit) to 100% (optimal)."
    "ScalarCacheRequestCount", "Discrete, Streaming", "Items", "The number of read requests made from executing shader code to the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size."
    "ScalarCacheHitCount", "Discrete, Streaming", "Items", "The number of read requests made from executing shader code which result in a cache hit from the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size."
    "ScalarCacheMissCount", "Discrete, Streaming", "Items", "The number of read requests made from executing shader code which result in a cache miss from the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size."
    "InstCacheHit", "Discrete, Streaming", "Percentage", "The percentage of read requests made that hit the data in the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size. Value range: 0% (no hit) to 100% (optimal)."
    "InstCacheRequestCount", "Discrete, Streaming", "Items", "The number of read requests made to the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size."
    "InstCacheHitCount", "Discrete, Streaming", "Items", "The number of read requests which result in a cache hit from the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size."
    "InstCacheMissCount", "Discrete, Streaming", "Items", "The number of read requests which result in a cache miss from the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size."

GlobalMemory Group
%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "FetchSize", "Discrete, Streaming", "Bytes", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account."
    "WriteSize", "Discrete, Streaming", "Bytes", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account."
    "MemUnitBusy", "Discrete, Streaming", "Percentage", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound)."
    "MemUnitBusyCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account."
    "MemUnitStalled", "Discrete, Streaming", "Percentage", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad)."
    "MemUnitStalledCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles the memory unit is stalled."
    "WriteUnitStalled", "Discrete, Streaming", "Percentage", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad)."
    "WriteUnitStalledCycles", "Discrete, Streaming", "Cycles", "Number of GPU cycles the Write unit is stalled."
    "LocalVidMemBytes", "Discrete", "Bytes", "Number of bytes read from or written to local video memory"
    "PcieBytes", "Discrete", "Bytes", "Number of bytes sent and received over the PCIe bus"

WaveDistribution Group
%%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "WaveOccupancyPct", "Streaming", "Percentage", "The percentage of the maximum wavefront occupancy that is currently being used."

WaveOccupancyLimiters Group
%%%%%%%%%%%%%%%%%%%%%%%%%%%

.. csv-table::
    :header: "Counter Name", "Sample Type", "Usage", "Brief Description"
    :widths: 15, 10, 10, 65

    "LSHSLimitedByVgpr", "Streaming", "Percentage", "The percentage of LS and HS wave scheduling requests that are limited by VGPR availability."
    "LSHSLimitedByLds", "Streaming", "Percentage", "The percentage of LS and HS wave scheduling requests that are limited by LDS availability."
    "LSHSLimitedByScratch", "Streaming", "Percentage", "The percentage of LS and HS wave scheduling requests that are limited by scratch space availability."
    "HSLimitedByBarriers", "Streaming", "Percentage", "The percentage of HS wave scheduling requests that are limited by barriers."
    "ESGSLimitedByVgpr", "Discrete, Streaming", "Percentage", "The percentage of ES and GS wave scheduling requests that are limited by VGPR availability."
    "ESGSLimitedByLds", "Streaming", "Percentage", "The percentage of ES and GS wave scheduling requests that are limited by LDS availability."
    "ESGSLimitedByScratch", "Streaming", "Percentage", "The percentage of ES and GS wave scheduling requests that are limited by scratch space availability."
    "VSLimitedByVgpr", "Streaming", "Percentage", "The percentage of VS wave scheduling requests that are limited by VGPR availability."
    "VSLimitedByScratch", "Streaming", "Percentage", "The percentage of VS wave scheduling requests that are limited by scractch space availability."
    "VSLimitedByExport", "Streaming", "Percentage", "The percentage of cycles that VS Waves are stalled due to export space availability."
    "PSLimitedByLds", "Streaming", "Percentage", "The percentage of PS wave scheduling requests that are limited by LDS availability."
    "PSLimitedByVgpr", "Streaming", "Percentage", "The percentage of PS wave scheduling requests that are limited by VGPR availability."
    "PSLimitedByScratch", "Streaming", "Percentage", "The percentage of PS wave scheduling requests that are limited by scratch space availability."
    "CSLimitedByLds", "Streaming", "Percentage", "The percentage of CS wave scheduling requests that are limited by LDS availability."
    "CSLimitedByVgpr", "Streaming", "Percentage", "The percentage of CS wave scheduling requests that are limited by VGPR availability."
    "CSLimitedByScratch", "Streaming", "Percentage", "The percentage of CS wave scheduling requests that are limited by scratch space availability."
    "CSLimitedByBarriers", "Streaming", "Percentage", "The percentage of CS wave scheduling requests that are limited by barriers."
    "CSLimitedByThreadGroupLimit", "Streaming", "Percentage", "The percentage of CS wave scheduling requests that are limited by the thread group limit."
