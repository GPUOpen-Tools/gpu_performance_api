# GPU Performance API
---

## Overview
The GPU Performance API (GPUPerfAPI, or GPA) is a powerful library, providing access to GPU Performance Counters.
It can help analyze the performance and execution characteristics of applications using a Radeon™ GPU. This library
is used by [Radeon Compute Profiler](https://github.com/GPUOpen-Tools/RCP) and [CodeXL](https://github.com/GPUOpen-Tools/CodeXL)
as well as several third-party tools.

## Downloads
Prebuilt binaries can be downloaded from the Releases page: https://github.com/GPUOpen-Tools/GPA/releases

## Table of Contents
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

## Major Features
* Provides a standard API for accessing GPU Performance counters for both graphics and compute workloads across multiple GPU APIs.
* Supports Vulkan™, DirectX™ 12, DirectX 11, OpenGL, and OpenCL™.
* Supports all current Radeon graphics cards and APUs based on Graphics IP version 8 and newer.
* Supports both Windows and Linux.
* Provides derived "public" counters based on raw hardware counters.
* Provides access to some raw hardware counters. See [Raw Hardware Counters](#raw-hardware-counters) for more information.

## What's New
* Version 3.6 (05/14/20)
  * Add support for additional GPUs and APUs, including AMD Ryzen™ 4000 Series APUs.
  * Add two new GFX10 GlobalMemory Counters for graphics using DX12 and Vulkan: LocalVidMemBytes and PcieBytes.
  * Add VS2019 project support to CMake.
  * Restructure of GPA source layout to adhere to google style.

## System Requirements
* An AMD Radeon GPU or APU based on Graphics IP version 8 and newer.
* Windows: Radeon Software Adrenaline 2020 Edition 19.12.2 or later (Driver Packaging Version 19.50 or later).
* Linux: Radeon Software for Linux Revision 19.50 or later.
* Radeon GPUs or APUs based on Graphics IP version 6 and 7 are no longer supported by GPUPerfAPI. Please use an older version ([3.3](https://github.com/GPUOpen-Tools/GPA/releases/tag/v3.3)) with older hardware.
* Windows 7, 8.1, and 10.
* Ubuntu (16.04 and later) and CentOS/RHEL (7 and later) distributions.

## Cloning the Repository
To clone the GPA repository, execute the following git command
  * git clone https://github.com/GPUOpen-Tools/gpu_performance_api

After cloning the repository, please run the following python script to retrieve the required dependencies and generate the build files (see [BUILD.md](BUILD.md) for more information):
  * python PreBuild.py

## Source Code Directory Layout
* [build](build) -- contains build scripts and cmake build modules
* [docs](docs) -- contains sphinx documentation sources and a Doxygen configuration file
* [include](include) -- contains GPUPerfAPI public headers
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
While querying raw hardware counters was possible in earlier GPUPerfAPI releases, the current release makes it much simpler. In previous releases, you had to build
GPUPerfAPI with special build flags in order to produce an "Internal" version that exposed the raw hardware counters. Current versions allow you to access the raw
hardware counters in a default build, by simply specifying a new flag when calling GPA_OpenContext. The current CMake build system still allows you to produce an "Internal"
build of GPUPerfAPI that also exposes the raw hardware counters, but that is a deprecated build and it is likely to be removed in a future release.

## Known Issues
 * Adjusting the GPU clock mode on Linux is accomplished by writing to <br><br>/sys/class/drm/card\<N\>/device/power_dpm_force_performance_level<br><br> where \<N\> is
   the index of the card in question. By default this file is only modifiable by root, so the application being profiled would have to be run as root in order for it to
   modify the clock mode. It is possible to modify the permissions for the file instead so that it can be written by unprivileged users. The following command will
   achieve this. Note, however, that changing the permissions on a system file like this could circumvent security. Also, on multi-GPU systems, you may have to replace
   "card0" with the appropriate card number. Permissions on this file may be reset when rebooting the system:
   * sudo chmod ugo+w /sys/class/drm/card0/device/power_dpm_force_performance_level
 * The following performance counter values may not be accurate for DirectX 11 applications running on a Radeon 5700 Series GPU. This is expected to be addressed in a future
   driver release:
   * VALUInstCount, SALUInstCount, VALUBusy, SALUBusy for all shader stages: These values should be representative of performance, but may not be 100% accurate.
   * Most of the ComputeShader counters (all except the MemUnit and WriteUnit counters): These values should be representative of performance, but may not be 100% accurate.
 * The following performance counter values may not be accurate for OpenGL applications running on a Radeon 5700 Series GPU. This is expected to be addressed in a future
   driver release:
   * VALUInstCount, SALUInstCount, VALUBusy, SALUBusy for all shader stages: These values should be representative of performance, but may not be 100% accurate.
   * Most of the ComputeShader counters (all except the MemUnit and WriteUnit counters): These values should be representative of performance, but may not be 100% accurate.
 * On Linux, setting the GPU clock mode is not working correctly for Radeon 5700 Series GPUs, potentially leading to some inconsistencies in counter values from one run to the
   next. This is expected to be addressed in a future driver release.

## Style and Format Change

The source code of this product is being reformatted to follow the Google C++ Style Guide https://google.github.io/styleguide/cppguide.html.
In the interim you may encounter a mix of both an older C++ coding style, as well as the newer Google C++ Style.
Please refer to the _clang-format file in the root directory of the product for additional style information.
