# GPU Performance API
---
The GPU Performance API (GPUPerfAPI, or GPA) is a powerful library which provides access to GPU Performance Counters.
It can help analyze the performance and execution characteristics of applications using a Radeon™ GPU. This library
is used by [Radeon GPU Profiler](https://github.com/GPUOpen-Tools/radeon_gpu_profiler) as well as several third-party tools.

## Table of Contents
* [Downloads](#downloads)
* [Major Features](#major-features)
* [What's New](#whats-new)
* [System Requirements](#system-requirements)
* [Cloning the Repository](#cloning-the-repository)
* [Source Code Directory Layout](#source-code-directory-layout)
* [Documentation](#documentation)
* [Raw Hardware Counters](#raw-hardware-counters)
* [Known Issues](#known-issues)
* [Building the Source Code](BUILD.md)
* [License](LICENSE)
* [Historical Release Notes](ReleaseNotes.md)
* [Style and Format Change](#Style-and-Format-Change)

## Downloads
Prebuilt binaries can be downloaded from the Releases page: https://github.com/GPUOpen-Tools/gpu_performance_api/releases.

## Major Features
* Provides a standard API for accessing GPU Performance counters for both graphics and compute workloads across multiple GPU APIs.
* Supports Vulkan™, DirectX™ 12, DirectX 11, OpenGL, and OpenCL™.
* Supports all current Radeon graphics cards and APUs based on Graphics IP version 8 and newer.
* Supports both Windows and Linux.
* Provides derived "public" counters based on raw hardware counters.
* Provides access to some raw hardware counters. See [Raw Hardware Counters](#raw-hardware-counters) for more information.

## What's New
### Version 3.13 (04/27/2023)
* Add support for AMD Radeon RX 7600 series hardware.
* Add support for AMD Radeon RX 7700 series hardware.
* OpenCL support for AMD Radeon RX 7000 series hardware has been restored if using Adrenalin 23.3.2 or newer.
* Removed implementation related to supporting software counters. They have not been supported since GPA 3.0.
* Update C++ language standard to C++ 17.
* CMake 3.19 or newer is now required.
* 32-bit Linux builds are no longer supported.
* Bug Fixes:
  * Fixed a regression that resulted in a crash on certain hardware variants.
  * Fix a memory leak in the GpaInterfaceLoader if multiple APIs were loaded.
  * Fix a memory leak in GPUPerfAPIUnitTests caused by not closing a context.
  * Marked kGpaOpenContextHideSoftwareCountersBit as obsolete.
  * Marked kGpaOpenContextHideHardwareCountesrBit as obsolete.

## System Requirements
* An AMD Radeon GPU or APU based on Graphics IP version 8 and newer.
* Windows: Radeon Software Adrenalin 2020 Edition 20.11.2 or later (Driver Packaging Version 20.45 or later).
* Linux: Radeon Software for Linux Revision 20.45 or later.
* Radeon GPUs or APUs based on Graphics IP version 6 and 7 are no longer supported by GPUPerfAPI. Please use an older version ([3.3](https://github.com/GPUOpen-Tools/gpu_performance_api/releases/tag/v3.3)) with older hardware.
* Windows 7, 8.1, 10, or 11.
* Ubuntu (16.04 and later) and CentOS/RHEL (7 and later) distributions.

## Cloning the Repository
To clone the GPA repository, execute the following git command
  * git clone https://github.com/GPUOpen-Tools/gpu_performance_api

After cloning the repository, please run the following python script to retrieve the required dependencies and generate the build files (see [BUILD.md](BUILD.md) for more information):
  * python pre_build.py

## Source Code Directory Layout
* [build](build) -- contains build scripts and cmake build modules
* [docs](docs) -- contains sphinx documentation sources and a Doxygen configuration file
* [include/gpu_performance_api](include/gpu_performance_api) -- contains GPUPerfAPI public headers
* [scripts](scripts) -- scripts to use to clone/update dependent repositories
* [source/auto_generated](source/auto_generated) -- contains auto-generated source code used when building GPUPerfAPI
* [source/examples](source/examples) -- contains the source code for a DirectX 12, DirectX 11, Vulkan and OpenGL sample which use GPUPerfAPI
* [source/gpu_perf_api_common](source/gpu_perf_api_common) -- contains source code for a Common library shared by all versions of GPUPerfAPI
* [source/gpu_perf_api_cl](source/gpu_perf_api_cl) -- contains the source for the OpenCL™ version of GPUPerfAPI
* [source/gpu_perf_api_counter_generator](source/gpu_perf_api_counter_generator) -- contains the source code for a Common library providing all counter data
* [source/gpu_perf_api_counters](source/gpu_perf_api_counters) -- contains the source code for a library that can be used to query counters without an active GPUPerfAPI context
* [source/gpu_perf_api_dx](source/gpu_perf_api_dx) -- contains source code shared by the DirectX versions of GPUPerfAPI
* [source/gpu_perf_api_dx11](source/gpu_perf_api_dx11) -- contains the source for the DirectX11 version of GPUPerfAPI
* [source/gpu_perf_api_dx12](source/gpu_perf_api_dx12) -- contains the source for the DirectX12 version of GPUPerfAPI
* [source/gpu_perf_api_gl](source/gpu_perf_api_gl) -- contains the source for the OpenGL version of GPUPerfAPI
* [source/gpu_perf_api_unit_tests](source/gpu_perf_api_unit_tests) -- contains a small set of unit tests for GPUPerfAPI
* [source/gpu_perf_api_vk](source/gpu_perf_api_vk) -- contains the source for the Vulkan version of GPUPerfAPI
* [source/public_counter_compiler](source/public_counter_compiler) -- source code for a tool to generate C++ code for public counters from text files defining the counters.
* [source/public_counter_compiler_input_files](source/public_counter_compiler_input_files) -- input files that can be fed as input to the PublicCounterCompiler tool

## Documentation
The documentation for GPUPerfAPI can be found in each [GitHub release](https://github.com/GPUOpen-Tools/gpu_performance_api/releases). In the release .zip file or .tgz file, there
will be a "docs" directory. Simply open the index.html file in a web browser to view the documentation.

The documentation is hosted publicly at: http://gpuperfapi.readthedocs.io/en/latest/

## Raw Hardware Counters
This release exposes both "Derived" counters and "Raw Hardware" counters. Derived counters are counters that are computed using a set of raw hardware counters.
This version allows you to access the raw hardware counters by simply specifying a flag when calling GpaOpenContext.

## New Pipeline-Based Counters
It was discovered that the improvements introduced in Vega, RDNA, and RDNA2 architectures were not being properly accounted for in GPUPerfAPI v3.9, and caused a lot of known issues to be called out in that release. In certain cases, the driver and hardware are able to make optimizations by combining two shader stages together, which prevented GPUPerfAPI from identifying which instructions where executed for which shader type. As a result of these changes, GPUPerfAPI is no longer able to expose instruction counters for each API-level shader, specifically Vertex Shaders, Hull Shaders, Domain Shaders, and Geometry Shaders. Pixel Shaders and Compute Shaders remain unchanged. We are now exposing these instruction counters based on the type of shader pipeline being used. In pipelines that do not use tessellation, the instruction counts for both the Vertex and Geometry Shaders (if used) will be combined in the VertexGeometry group (ie: counters with the "VsGs" prefix). In pipelines that use tessellation, the instruction counts for both the Vertex and Hull Shaders will be combined in the PreTessellation group (ie: counters with the "PreTessellation" or "PreTess" prefix), and instruction counts for the Domain and Geometry Shaders (if used) will be combined in the PostTessellation group (ie: counters with the "PostTessellation" or "PostTess" prefix). The table below may help to better understand the new mapping between the API-level shaders (across the top), and which prefixes to look for in the GPUPerfAPI counters.

| Pipeline       | Vertex  |  Hull   |  Domain  | Geometry | Pixel | Compute |
|----------------|:-------:|:-------:|:--------:|:--------:|:-----:|:-------:|
| VS-PS          |  VsGs   |         |          |          |  PS   |         |
| VS-GS-PS       |  VsGs   |         |          |   VsGs   |  PS   |         |
| VS-HS-DS-PS    | PreTess | PreTess | PostTess | PostTess |  PS   |         |
| VS-HS-DS-GS-PS | PreTess | PreTess | PostTess | PostTess |  PS   |         |
| CS             |         |         |          |          |       |   CS    |

## Known Issues
### Counter Validity on Specific Hardware
There are some counters that are returning unexpected results on specific hardware with certain APIs.
* AMD Radeon RX 6700M, DX11: CSLDSBankConflict and CSLDSBankConflictCycles may consistently report as much as 30x higher than expected.
* AMD Radeon RX 480, DX12: CulledPrims and PSPixelsOut may inconsistently report higher than expected.

### Counter Validation Errors in D3D12ColorCube Sample App
Due to the extensive counter validation now being done in the D3D12ColorCube sample application, and some expected variation in nondeterministic counters across a wide range of systems, the sample app may report errors on some systems. Likewise, some counters are marked as known issues and we are investigating the underlying causes of the inconsistent results.

### OpenCL Performance Counter Accuracy For Radeon 6000 Series GPUs
The following performance counter values may not be accurate for OpenCL applications running on Radeon 6000 Series GPUs:
* Wavefronts, VALUInsts, SALUInsts, SALUBusy, VALUUtilization: These values should be representative of performance, but may not be 100% accurate.

### OpenGL FetchSize Counter on Radeon RX 6000 Series GPUs
FetchSize counter will show an error when enabled on Radeon RX 6000 Series GPUs using OpenGL.

### Ubuntu 20.04 LTS Vulkan ICD Issue
On Ubuntu 20.04 LTS, Vulkan ICD may not be set to use AMD Vulkan ICD. In this case, it needs to be explicitly set to use AMD Vulkan ICD before using the GPA. It can be done by setting the ```VK_ICD_FILENAMES``` environment variable to ```/etc/vulkan/icd.d/amd_icd64.json```.

### Adjusting Linux Clock Mode
Adjusting the GPU clock mode on Linux is accomplished by writing to: ```/sys/class/drm/card\<N\>/device/power_dpm_force_performance_level```, where \<N\> is the index of the card in question.

By default this file is only modifiable by root, so the application being profiled would have to be run as root in order for it to modify the clock mode. It is possible to modify the permissions for the file instead so that it can be written by unprivileged users. The following command will achieve this: ```sudo chmod ugo+w /sys/class/drm/card0/device/power_dpm_force_performance_level```
* Note that changing the permissions on a system file like this could circumvent security.
* On multi-GPU systems you may have to replace "card0" with the appropriate card number.
* You may have to reboot the system for the change to take effect.
* Setting the GPU clock mode is not working correctly for <b>Radeon 5700 Series GPUs</b>, potentially leading to some inconsistencies in counter values from one run to the next.

### Profiling Bundles
Profiling bundles in DirectX12 and Vulkan is not working properly. It is recommended to remove those GPA Samples from your application, or move the calls out of the bundle for profiling.

## Style and Format Change
The source code of this product is being reformatted to follow the Google C++ Style Guide https://google.github.io/styleguide/cppguide.html.
In the interim you may encounter a mix of both an older C++ coding style, as well as the newer Google C++ Style.
Please refer to the .clang-format file in the root directory of the product for additional style information.
