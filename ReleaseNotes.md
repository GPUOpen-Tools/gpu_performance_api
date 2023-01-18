# GPU Performance API Release Notes

## Upcoming Release
  * Renamed kGpaOpenContextHideSoftwareCountesrBit and kGpaOpenContextHideHardwareCountersBit since they are obsolete.

## Version 3.12 (12/14/22)
  * Add support for AMD Radeon™ RX 7900 XTX and AMD Radeon™ RX 7900 XT GPUs.
  * Add support for compiling with Visual Studio 2022.
  * Reduced binary sizes by an average of 75%.
  * Bug Fixes:
    * AMD Radeon RX 6800, DX12: HiZ and PreZ counters are now reporting correct values (requires Adrenalin 22.7.1 or newer driver).
    * AMD Radeon RX 6800: CSThreadgroups is now reporting the correct values (requires Adrenalin 22.7.1 or newer driver).
    * AMD Radeon RX 6000 Series: PostTessellation counters now only show results in pipelines using tessellation.
    * AMD Radeon RX 5000 Series: PreTessellation counters now only show results in pipelines using tessellation.
    * Sample apps: Fix implementation of passes in D3D11Triangle, and improve general error handling.

## Version 3.11.1 (07/27/22)
  * Updated OpenGL support for the Adrenalin 22.7.1 driver.
  * Added L2CacheHit counter for OpenGL on Radeon RX 5000 Series hardware.
  * Improved GPA integration into GLTriangle sample application.

## Version 3.11 (04/25/22)
  * Add support for additional GPUs and APUs.
  * Counter updates for RDNA2 (Radeon RX 6000 Series) hardware:
    * Added ray tracing counters for Vulkan: RayTriTests, RayBoxTests, TotalRayTests, and RayTestsPerWave.
    * Fixed values incorrectly reported by counters PSExportStalls and PSExportStallCycles.
    * On all hardware: renamed counter "DepthStencilTestBusyCount" to "DepthStencilTestBusyCycles" for consistency with other similar counters.
    * External dependent repositories are now cloned into an "external/" subdirectory within the gpu_performance_api repository.
    * Added support for Ninja compiler.
    * Improved error reporting.
    * Improved counter validation.
  * Disabled support for Mesa driver. We hope to re-enable it in a future release.

## Version 3.10 (01/25/22)
  * Add support for additional GPUs and APUs.
  * Redefined derived counters on GCN (Vega), RDNA, and RDNA2 hardware.
    * New pipeline-based counters to better match hardware behavior.
    * GCN (Polaris) hardware:
      * Added: CSThreadGroupSize.
      * Fixed: CSThreads, CSFlatVMemInsts, HiZTilesAccepted, HiZTilesAcceptedCount, PreZQuadsCulled, PreZQuadsCulledCount, PreZQuadsSurvivingCount.
    * GCN (Radeon Vega Series) hardware:
      * Removed: VSBusy, VSBusyCycles, VSTime, HSBusy, HSBusyCycles, HSTime, DSBusy, DSBusyCycles, DSTime.
      * Added: VsGsBusy, VsGsBusyCycles, VsGsTime, PreTessellationBusy, PreTessellationBusyCycles, PreTessellationTime, PostTessellationBusy, PostTessellationBusyCycles, PostTessellationTime.
      * Removed: VertexShader group (VSVerticesIn, VSVALUInstCount, VSSALUInstCount, VSVALUBusy, VSVALUBusyCycles, VSSALUBusy, VSSALUBusyCycles).
      * Added: VertexGeometry group (VsGsVALUInstCount, VsGsSALUInstCount, VsGsVALUBusy, VsGsVALUBusyCycles, VsGsSALUBusy, VsGsSALUBusyCycles).
        * Represents combined data from vertex and geometry shaders in a VS-PS or VS-GS-PS pipeline.
      * Removed: HullShader group (HSPatches, HSVALUInstCount, HSSALUInstCount, HSVALUBusy, HSVALUBusyCycles, HSSALUBusy, HSSALUBusyCycles).
      * Added: PreTessellation group (PreTessVALUInstCount, PreTessSALUInstCount, PreTessVALUBusy, PreTessVALUBusyCycles, PreTessSALUBusy, PreTessSALUBusyCycles).
        * Represents combined data from vertex and hull shaders in a VS-HS-DS-PS or VS-HS-DS-GS-PS pipeline.
      * Removed: DomainShader group (DSVerticesIn, DSVALUInstCount, DSSALUInstCount, DSVALUBusy, DSVALUBusyCycles, DSSALUBusy, DSSALUBusyCycles).
      * Removed: GeometryShader group (GSPrimsIn, GSVerticesOut, GSVALUInstCount, GSSALUInstCount, GSVALUBusy, GSVALUBusyCycles, GSSALUBusy, GSSALUBusyCycles).
      * Added: PostTessellation group (PostTessVALUInstCount, PostTessSALUInstCount, PostTessVALUBusy, PostTessVALUBusyCycles, PostTessSALUBusy, PostTessSALUBusyCycles).
        * Represents combined data from domain and geometry shaders in a VS-HS-DS-PS or VS-HS-DS-GS-PS pipeline.
      * Added: CSThreadGroupSize.
      * Fixed: PSBusy, PSBusyCycles, PSTime, CSBusy, CSBusyCycles, CSTime, CSThreads, CSFlatVMemInsts, HiZTilesAccepted, HiZTilesAcceptedCount, HiZTilesRejectedCount, HiZQuadsCulled, HiZQuadsCulledCount, HiZQuadsAcceptedCount, PreZQuadsCulled, PreZQuadsCulledCount, PreZQuadsSurvivingCount.
    * RDNA (Radeon RX 5000 Series) hardware:
      * Removed: VSBusy, VSBusyCycles, VSTime, HSBusy, HSBusyCycles, HSTime, DSBusy, DSBusyCycles, DSTime.
      * Added: VsGsBusy, VsGsBusyCycles, VsGsTime, PreTessellationBusy, PreTessellationBusyCycles, PreTessellationTime, PostTessellationBusy, PostTessellationBusyCycles, PostTessellationTime.
      * Removed: VertexShader group (VSVerticesIn, VSVALUInstCount, VSSALUInstCount, VSVALUBusy, VSVALUBusyCycles, VSSALUBusy, VSSALUBusyCycles).
      * Added: VertexGeometry group (VsGsVALUInstCount, VsGsSALUInstCount, VsGsVALUBusy, VsGsVALUBusyCycles, VsGsSALUBusy, VsGsSALUBusyCycles).
        * Represents combined data from vertex and geometry shaders in a VS-PS or VS-GS-PS pipeline.
      * Removed: HullShader group (HSPatches, HSVALUInstCount, HSSALUInstCount, HSVALUBusy, HSVALUBusyCycles, HSSALUBusy, HSSALUBusyCycles).
      * Added: PreTessellation group (PreTessVALUInstCount, PreTessSALUInstCount, PreTessVALUBusy, PreTessVALUBusyCycles, PreTessSALUBusy, PreTessSALUBusyCycles).
        * Represents combined data from vertex and hull shaders in a VS-HS-DS-PS or VS-HS-DS-GS-PS pipeline.
      * Removed: DomainShader group (DSVerticesIn, DSVALUInstCount, DSSALUInstCount, DSVALUBusy, DSVALUBusyCycles, DSSALUBusy, DSSALUBusyCycles).
      * Removed: GeometryShader group (GSPrimsIn, GSVerticesOut, GSVALUInstCount, GSSALUInstCount, GSVALUBusy, GSVALUBusyCycles, GSSALUBusy, GSSALUBusyCycles).
      * Added: PostTessellation group (PostTessVALUInstCount, PostTessSALUInstCount, PostTessVALUBusy, PostTessVALUBusyCycles, PostTessSALUBusy, PostTessSALUBusyCycles).
        * Represents combined data from domain and geometry shaders in a VS-HS-DS-PS or VS-HS-DS-GS-PS pipeline.
      * Removed: PrimitivesIn.
      * Added: CSThreadGroupSize.
      * Fixed: PSBusy, PSBusyCycles, PSTime, CSBusy, CSBusyCycles, CSTime, CSThreads, HiZTilesAccepted, HiZTilesAcceptedCount, HiZTilesRejectedCount, PreZQuadsCulled, PreZQuadsCulledCount, PreZQuadsSurvivingCount.
    * RDNA2 (Radeon RX 6000 Series) hardware:
      * Removed: VSBusy, VSBusyCycles, VSTime, HSBusy, HSBusyCycles, HSTime, DSBusy, DSBusyCycles, DSTime.
      * Removed: VertexShader group, HullShader group, DomainShader group, GeometryShader group.
      * Removed: PrimitivesIn, PSVALUInstCount, PSSALUInstCount, PSVALUBusy, PSVALUBusyCycles, PSSALUBusy, PSSALUBusyCycles.
      * Removed: CSVALUInsts, CSVALUUtilization, CSSALUInsts, CSVFetchInsts, CSSFetchInsts, CSVWriteInsts, CSVALUBusy, CSVALUBusyCycles, CSSALUBusy, CSSALUBusyCycles.
      * Added: CSThreadGroupSize
      * Fixed: CSThreads, HiZTilesAccepted, HiZTilesAcceptedCount, HiZTilesRejectedCount, PreZQuadsCulled, PreZQuadsCulledCount, PreZQuadsSurvivingCount.
  * Integrated clang-tidy and clang-format into cmake build options.
  * New entrypoint added: GpaGetDeviceGeneration. Binary backwards compatibility is maintained.
  * OpenGL on Linux: Fixed hardware detection on MESA drivers.
  * OpenGL: Fixed hardware detection accuracy.
  * Setting GPA_OVERRIDE_LOG_LEVEL env var to an integer equal to a GpaLoggingType enum can be used to increase or decrease logging output.
  * DX11:
    * Fixed Adrenalin driver version detection.
    * Fixed setting the number of shader arrays based on client hardware.
  * Improvements made to the sample applications:
    * Extensive counter validation in DX12.
    * Sample apps can now confirm successful validation tests.
    * Sample apps now support passing in a counter file to specify which counters to enable.
    * Consolidated parameter parsing logic in sample apps.
    * In Vulkan and DX12 samples, the return code now indicates the number of errors that were reported.

## Version 3.9 (07/27/21)
  * Add support for additional GPUs and APUs.
  * Improvements made to the sample applications.

## Version 3.8 (04/01/21)
  * Add support for additional GPUs and APUs, including AMD Radeon™ RX 6700 series GPUs.
  * Code has been updated to adhere to Google C++ Style Guide.
    * New public headers have been added.
    * Old headers are deprecated and will emit a compile-time message if included.
    * Projects loading GPA will need to be recompiled, but no code changes are required unless moving to the new headers.
  * Improvements made to all sample applications.
  * Updated documentation for new codestyle (and https://github.com/GPUOpen-Tools/gpu_performance_api/issues/56).
  * Support for the --internal flag has been removed from the build script.

## Version 3.7 (11/24/20)
  * Add support for additional GPUs and APUs, including AMD Radeon™ RX 6000 series GPUs.
  * New RT counters for DXR workloads on AMD Radeon™ RX 6000 series GPUs.
    * RayTriTests, and RayBoxTests: These counters collect the number of ray intersections for triangles and boxes, respectively.
    * TotalRayTests: This counter collects the aggregated number of ray-box and ray-triangle intersection tests.
    * RayTestsPerWave: This counter collects ray intersection test count at a more granular level – per wave.
  * New Scalar and Instruction cache counters on AMD Radeon™ RX 5000 series GPUs.
    * Scalar cache: ScalarCacheHit, ScalarCacheRequestCount, ScalarCacheHitCount, ScalarCacheMissCount
    * Instruction cache: InstCacheHit, InstCacheRequestCount, InstCacheHitCount, InstCacheMissCount
  * Update the Vulkan® sample to remove the static link and use the system-specific Vulkan® loader.
  * Remove OpenCL™ support from Linux.
  * Remove downloading the Vulkan® SDK by the build script.

## Version 3.6 (05/15/20)
  * Add support for additional GPUs and APUs, including AMD Ryzen™ 4000 Series APUs.
  * Add two new GFX10 GlobalMemory Counters for graphics using DX12 and Vulkan: LocalVidMemBytes and PcieBytes.
  * Add VS2019 project support to CMake.
  * Restructure of GPA source layout to adhere to google style.

## Version 3.5 (12/13/19)
  * Add support for additional GPUs and APUs, including Radeon 5500 and Radeon 5300 Series GPUs.
  * Add DirectX11 sample application using GPUPerfAPI.
  * Add per-API static counter generation.
  * Decrease in GPUPerfAPI binaries size.
  * Add script to package GPUPerfAPI post-build.
  * Remove ROCm/HSA support.
  * Add Unicode support in GPUPerfAPI for Linux.
  * Bugs Fixed:
    * Fixed CMake files to respect supported build flags.
    * Fixed crash when DX12 debug layer was enabled.
    * Fixed an issue with loading of shader in GPA Vulkan sample app.
    * Fixed an issue in Vulkan build with newer Vulkan SDK with amd_shader_core_properties2 extension (https://github.com/GPUOpen-Tools/gpu_performance_api/issues/45)
    * Fixed an issue with crash on unsupported Gfx6 and Gfx7 GPUs.

## Version 3.4 (7/10/19)
  * Add support for additional GPUs and APUs, including Radeon 5700 Series GPUs.
  * Add support for setting stable GPU clocks for DirectX11, OpenGL and OpenCL.
  * Add an OpenGL sample application that uses GPUPerfAPI.
  * Add basic counter validation to sample applications.
  * Add support for enabling individual hardware counters that make up derived counters.
  * Add two new GFX9 GlobalMemory Counters for graphics: LocalVidMemBytes and PcieBytes.
  * Reformat source code using clang-format.
  * Update counter documentation to contain per-hardware-generation tables.
  * Bugs Fixed:
    * Fixed error handling in GPA_GetEnabledIndex, GPA_EnableCounterByName and GPA_DisbleCounterByName.
    * Fixed an issue with Vulkan timing counters (https://github.com/GPUOpen-Tools/gpu_performance_api/issues/40).
    * Fixed an issue with SALUBusy counters.
    * Fixed an issue with HiZQuadsCulledCount and HiZQuadsSurvivingCount counters on GFX8 GPUs.
    * Fixed an issue with MemUnitBusy and MemUnitStalled counters on GFX8 GPUs.
    * Fixed an issue with VSVALUBusyCycles counter on GFX9 GPUs.

## Version 3.3 (12/20/18)
  * Add support for additional GPUs and APUs.
  * New CMake-based build system.
  * Support building on Ubuntu 18.04.
  * ROCm/HSA: uses new librocprofiler64.so rather than deprecated libhsa-runtime-tools64.so library for performance counter collection.
  * Timing-based counters are now reported in nanoseconds instead of milliseconds.
  * New timing counter to report top-of-pipe to bottom-of-pipe duration.
  * GPA now builds GoogleTest libraries on the fly rather than using prebuilt binaries.

## Version 3.2 (8/21/18)
  * Add support for additional GPUs and APUs.
  * Wrapped all GPA entrypoints in try/catch to ensure unhandled exceptions do not escape the GPA library.
  * Add VS2017 project files.
  * Bugs Fixed:
    * Fixed https://github.com/GPUOpen-Tools/gpu_performance_api/issues/18.
    * Fixed support for scheduling counters on multiple sessions.
    * OpenGL: Fixed a bug in GPASample cleanup.

## Version 3.1 (6/15/18)
  * Add support for additional GPUs and APUs.
  * Usability improvements to GPAInterfaceLoader.h.
  * New Vulkan and DirectX 12 sample applications.
  * New GPA_GetSampleId entry point.
  * New GPA_GetVersion entry point.
  * Bugs Fixed:
    * Fixed issues with some counters on 56CU Vega10.
    * Vulkan: Fixed GPA_ContinueSampleOnCommandList.
    * Vulkan: Ensure results are ready before trying to query them.
    * DirectX 12: Fixed incorrect device reference counting issue.

## Version 3.0 (3/19/18)
 * Add support for additional GPUs and APUs.
 * Support for collecting hardware counters for Vulkan and DirectX 12 applications.
 * Redesigned API to support modern graphics APIs.
 * The documentation has been rewritten and is now available in HTML format.
 * New counters added:
   * Cycle and count-based counters in addition to existing percentage-based counters.
   * New Depth Buffer memory read/write counters.
   * Additional Color Buffer memory counters.
   * For graphics, several global memory counters which were previously available only in the Compute Shader stage are now available generically.
 * Support for setting stable GPU clocks.
 * Counter Group Names can now be queried separately from Counter Descriptions.
 * Counters now have a UUID which can be used to uniquely identify a counter.
 * New entry point (GPA_GetFuncTable) to retrieve a table of function pointers for all GPA entry points.
 * New C++ GPAInterfaceLoader.h header file provides an easy way to load and use GPA entry points.
 * Bugs Fixed:
   * Fixed an issue with TesselatorBusy counter on many GFX8 GPUs.
   * Fixed an issue with FlatVMemInsts and CSFlatVMemInsts counters on many GFX8 GPUs.
   * Fixed an issue with LDSInsts counter on Vega GPUs.
   * Fixed some issues with Compute Shader counters on Vega GPUs.
   * Some counter combinations could lead to incorrect counter results.
   * Enabling counters in a certain order can lead to incorrect counter scheduling across multiple passes.
   * ROCm/HSA: GPA_OpenContext crashes if libhsa-runtime64.so.1 can't be found.
   * ROCm/HSA: GPA does not coexist nicely with an application that also sets the HSA_TOOLS_LIB environment variable.
   * OpenGL: Fixed a crash that can occur with an incorrectly-configured OpenGL driver.
   * OpenGL: Fixed some issues with OpenGL device-detection.

## Version 2.23 (6/27/17)
 * Add support for additional GPUs, including Vega series GPUs
 * Allow unit tests to be built and run on Linux

## Version 2.22 (4/26/17)
 * Add support for additional GPUs and APUs, including RX 500 series GPUs

## Version 2.21 (12/21/16)
 * Add support for additional GPUs and APUs.
 * ROCm/HSA: Support for ROCm 1.3 and ROCm 1.4
 * OpenGL: Fixed an issue with GPU/APU detection with newer Radeon Crimson drivers

## Version 2.20 (5/12/16)
 * Add support for additional GPUs and APUs.
 * Initial Public release of ROCm/HSA support
 * Developer Preview for DirectX12 (no hardware-based performance counter support)
 * Removed support for pre-GCN-based devices
 * Improve accuracy of the various *VALUBusy and *SALUBusy counters (all APIs)
 * OpenGL: Fixed possibly wrong GPUTime values for some applications
 * OpenGL: Add support for open source OpenGL driver
 * OpenGL: Fix value of TexUnitBusy counter for 3rd generation GCN hardware
 * DirectX 11: Fix incorrect type returned for D3DGPUTime counter
 * DirectX 11: Fix PSVALUBusy counter on 2nd and 3rd generation GCN hardware
 * DirectX 11: A separate DLL (GPUPerfAPIDXGetAMDDeviceInfo\*.dll) is required in order to support certain multi-GPU configurations. This DLL will need to be deployed alongside GPUPerfAPIDX11\*.dll on multi-GPU systems. See the [User Guide](Doc/GPUPerfAPI-UserGuide.pdf) for more information.

## Version 2.17 (8/12/15)
 * Add support for additional GPUs and APUs.
 * Add OpenGL ES support for both Windows and Linux.
 * DirectX 11/OpenGL: Add CSFlatVMInsts and CSFlatLDSInsts counters to measure flat instructions used for compute shaders on 2nd Generation GCN hardware or newer.
 * DirectX11/OpenGL: Fix CSLDSInsts, CSVWriteInsts, CSVFetchInsts counter on 2nd Generation GCN hardware or newer.
 * DirectX 11: Fixed a crash that could occur on Multi-GPU systems.
 * OpenGL: rework the GPUTime implementation so that GPA no longer needs to stop/start any existing queries that the application may be using.
 * OpenCL™: Add FlatVMInsts and FlatLDSInsts counters to measure flat instructions used for OpenCL kernels on 2nd Generation GCN hardware or newer.
 * OpenCL™: Fix LDSInsts, VWriteInsts, VFetchInsts counter on 2nd Generation GCN hardware or newer.
 * OpenCL™: Fix MemUnitBusy counter on 2nd Generation GCN hardware or newer.
 * Fix a potential crash in GPA_SelectContext.
 * Fix a bug in GPA_DisableCounter that could result in the counter not actually getting disabled.

## Version 2.15 (1/9/15)
 * Add support for additional GPUs and APUs.
 * Improved error handling in the various GPA_GetSample functions
 * Improved algorithm which splits counters into multiple passes.
 * DirectX 11/OpenGL: Added new counters to the Timing group to report total time taken for a particular shader type.
 * DirectX 11: Provided access to various D3D Queries as counters (see the D3D11 counter group).
 * DirectX 11: Fixed some memory leaks when running on pre-GCN hardware.
 * DirectX 11: Fixed some incorrect Compute Shader counter values.
 * DirectX 11: Fixed a crash that could occur when querying some counters on most recent hardware.

## Version 2.14 (9/5/14)
 * Add support for additional GPUs and APUs.
 * DirectX 11: Fixed some memory leaks caused by incorrect reference counting of D3D11 devices and device contexts.
 * OpenGL: Improved memory consumption and performance during profiling.
 * OpenGL: Fixed crash in 32-bit Linux version.
 * OpenGL: Fixed CSMemUnitBusy, CSMemUnitStalled, and TexTriFilteringPct counters on Graphics IP v8 family of GPUs.
 * OpenGL: Fixed CSALUStalledByLDS counter on Graphics IP v7 and v8 families of GPUs.
 * Removed Support for DirectX 10.

## Version 2.13 (4/17/14, updated 6/20/14)
 * 6/20/14: Add support for additional GPUs and APUs.
 * 6/20/14: OpenGL: Fixed some device support.
 * Add support for Volcanic Islands GPUs.
 * Add support for AMD Radeon R9 200 Series GPUs.
 * Add support for Kaveri-based APUs.
 * Add support for more FirePro, Mobility, and APU devices.
 * DirectX 10/DirectX 11: Fix an issue with collecting performance counters using the latest Catalyst Beta Drivers (14.1, 14.2 and 14.3).
 * OpenGL: Add support for Compute Shader counters.
 * OpenGL: New shader-stage-specific ALUBUsy and ALUInstCount counters (both vector and scalar) for Sea Islands GPUs and newer.
 * OpenGL: Improved Linux support.
 * OpenCL™: FastPath, CompletePath, and PathUtilization now report correct value on AMD Radeon HD 6000 series hardware and on Trinity/Richland-based APUs.
 * OpenCL™: Improved results when performing multi-pass profiling.

## Version 2.11 (6/5/13)
 * Add support for AMD Radeon HD 8000 Series hardware.
 * Add support for more AMD Radeon HD 7000 Series devices.
 * Add support for more FirePro, Mobility, and APU devices.
 * Improved performance and counter results when large numbers of counters are enabled on AMD Radeon HD 7000 Series hardware and newer.
 * Improved counter results on systems with both an APU and a discrete GPU.
 * DirectX 11: CSFetchInsts, CSTexBusy, and CSALUFetchRatio now report correct value on AMD Radeon HD 5000-6000 series hardware.
 * OpenGL/DirectX 10/DirectX 11: TexUnitBusy counter now reports correct value on AMD Radeon HD 7000 Series hardware.
 * OpenCL™: WriteSize counter now reports correct value on AMD Radeon HD 7000 Series hardware.

## Version 2.9 (1/18/12)
 * Add support for AMD Radeon 7000 Series hardware.
 * Add support for more FirePro, Mobility, and APU devices.
 * Improved memory consumption and performance during profiling.
 * Reduce memory footprint of the GPUPerfAPI DLLs.
 * Correct counters are now exposed on systems with dual GPUs of different hardware generations.
 * DirectX 10:Fixed shader related counters on AMD Radeon HD 2000-5000 Series hardware.
 * Fixed PrimitivesIn counter on AMD Radeon HD 2000 Series hardware.

## Version 2.8 (4/22/11)
 * DirectX 10: Fixed GPUTime support on AMD Radeon HD 2000 and 3000 Series hardware.
 * DirectX 11: Fixed counter accessibility on AMD Radeon HD 2000 and 3000 Series hardware.

## Version 2.7 (4/6/11)
 * New entrypoint for registering logging callback function for improved troubleshooting.
 * Adds support for AMD Radeon HD 6000 Series hardware.
 * New DepthAndStencil counters give more detailed understanding of HiZ behavior.
 * OpenGL: Improved accuracy of depth, texture, busy, and stalled counters.
 * OpenCL™: FetchSize counter now reports the correct value.
 * DirectX 10/11: Fixed support for AMD Radeon HD 4000 Series hardware; Fixed support for Catalyst 11.2 drivers on AMD Radeon HD 5000 Series hardware.

## Version 2.5 (11/17/10)
 * Adds Linux support for OpenGL and OpenCL.
 * More consistent naming between OpenCL and DX Compute Shader counters.
 * Improved methods for identifying existing hardware.
 * DirectX 10/11: 1) Improved accuracy of DepthAndStencil counters, 2) Improved accuracy of ColorBuffer counters.
 * OpenCL™: New counters: FetchSize, CacheHit, LDSFetchInsts, LDSWriteInsts, FastPath, CompletePath, PathUtilization.
 * OpenGL: Fixed an issue that caused counters to not be available if the application is using queries; Adds tessellation related counters.

## Version 2.3 (6/4/10)
 * Supports DirectX10, DirectX11, OpenGL on ATI Radeon 2000, 3000, 4000, and 5000 series.
 * Supports OpenCL™ on ATI Radeon 4000 and 5000 series.
 * Provides derived counters based on raw HW performance counters.
 * Manages memory automatically – no allocations required.
 * Requires ATI Catalyst driver 10.1 or later.
