# GPU Performance API
---

## Overview
The GPU Performance API (GPUPerfAPI, or GPA) is a powerful library, providing access to GPU Performance Counters.
It can help analyze the performance and execution characteristics of applications using a Radeon™ GPU. This library
is used by [Radeon Compute Profiler](https://github.com/GPUOpen-Tools/RCP) and [CodeXL](https://github.com/GPUOpen-Tools/CodeXL)
as well as several third-party tools.

## Table of Contents
* [Major Features](#major-features)
* [What's New](#whats-new)
* [System Requirements](#system-requirements)
* [Cloning the Repository](#cloning-the-repository)
* [Source Code Directory Layout](#source-code-directory-layout)
* [Documentation](#documentation)
* ["Public" vs "Internal" Versions](#public-vs-internal-versions)
* [Known Issues](#known-issues)
* [Building the Source Code](BUILD.md)
* [License](LICENSE)
* [Historical Release Notes](ReleaseNotes.md)

## Major Features
* Provides a standard API for accessing GPU Performance counters for both graphics and compute workloads across multiple GPU APIs.
* Supports Vulkan™, DirectX™ 12, DirectX 11, OpenGL, OpenCL™, and ROCm/HSA
* Supports all current GCN-based Radeon graphics cards and APUs.
* Supports both Windows and Linux
* Provides derived "public" counters based on raw HW counters
* "Internal" version provides access to some raw hardware counters. See ["Public" vs "Internal" Versions](#public-vs-internal-versions) for more information.

## What's New
* Version 3.0 (3/19/17)
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
  * New C++ GPAInterfaceLoader.h header file provides an easy way to load GPA libraries and call GPA entry points.
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

## System Requirements
* An AMD Radeon GCN-based GPU or APU
* Radeon Software Crimson Adrenaline Edition 18.2.3 or later (Driver Packaging Version 17.50.25 or later).
* Pre-GCN-based GPUs or APUs are no longer supported by GPUPerfAPI. Please use an older version ([2.17](http://developer.amd.com/tools-and-sdks/graphics-development/gpuperfapi/)) with older hardware.
* Windows 7, 8.1, and 10
* Ubuntu (16.04 and later) and RHEL (7 and later) distributions

## Cloning the Repository
To clone the GPA repository, execute the following git commands
  * git clone https://github.com/GPUOpen-Tools/GPA.git

After cloning the repository, please run the following python script to retrieve the required dependencies (see [BUILD.md](BUILD.md) for more information):
  * python Scripts/UpdateCommon.py

UpdateCommon.py has replaced the use of git submodules in the GPA repository

## Source Code Directory Layout
* [Build](Build) -- contains both Linux and Windows build-related files
* [Common](Common) -- Common libs, header and source code not found in other repositories
* [docs](docs) -- contains documentation sources and a Doxygen configuration file
* [Src/DeviceInfo](Src/DeviceInfo) -- builds a lib containing the Common/Src/DeviceInfo code (Linux only)
* [Src/GPUPerfAPI](Src/GPUPerfAPI) -- builds a lib containing Src/GPUPerfAPI-Common/GPUPerfAPI.cpp (Linux only)
* [Src/GPUPerfAPI-Common](Src/GPUPerfAPI-Common) -- contains source code for a Common library shared by all versions of GPUPerfAPI
* [Src/GPUPerfAPICL](Src/GPUPerfAPICL) -- contains the source for the OpenCL™ version of GPUPerfAPI
* [Src/GPUPerfAPICounterGenerator](Src/GPUPerfAPICounterGenerator) -- contains the source code for a Common library providing all counter data
* [Src/GPUPerfAPICounters](Src/GPUPerfAPICounters) -- contains the source code for a library that can be used to query counters without an active GPUPerfAPI context
* [Src/GPUPerfAPIDX](Src/GPUPerfAPIDX) -- contains source code shared by the DirectX versions of GPUPerfAPI
* [Src/GPUPerfAPIDX11](Src/GPUPerfAPIDX11) --contains the source for the DirectX11 version of GPUPerfAPI
* [Src/GPUPerfAPIDX12](Src/GPUPerfAPIDX12) -- contains the source for the DirectX12 version of GPUPerfAPI (Developer Preview)
* [Src/GPUPerfAPIGL](Src/GPUPerfAPIGL) -- contains the source for the OpenGL version of GPUPerfAPI
* [Src/GPUPerfAPIHSA](Src/GPUPerfAPIHSA) -- contains the source for the ROCm/HSA version of GPUPerfAPI
* [Src/GPUPerfAPIUnitTests](Src/GPUPerfAPIUnitTests) -- contains a small set of unit tests for GPUPerfAPI
* [Src/GPUPerfAPIVk](Src/GPUPerfAPIVk) -- contains the source for the Vulkan version of GPUPerfAPI
* [Src/PublicCounterCompiler](Src/PublicCounterCompiler) -- source code for a tool to generate C++ code for public counters from text files defining the counters.
* [Src/PublicCounterCompilerInputFiles](Src/PublicCounterCompilerInputFiles) -- input files that can be fed as input to the PublicCounterCompiler tool
* [Scripts](Scripts) -- scripts to use to clone/update dependent repositories

## Documentation
The documentation for GPUPerfAPI can be found in each [GitHub release](https://github.com/GPUOpen-Tools/GPA/releases). In the release .zip file or .tgz file, there
will be a "docs" directory. Simply open the index.html file in a web browser to view the documentation.

The documentation is hosted publicly at: http://gpuperfapi.readthedocs.io/en/latest/

## "Public" vs "Internal" Versions
This open source release supports building both the "Public" and "Internal" versions of GPUPerfAPI. By default the Visual Studio solution and the Linux build scripts
will produce what is referred to as the "Public" version of GPUPerfAPI. This version exposes "Public", or "Derived", counters. These are counters that are computed
using a set of hardware counters. Until now, only the Public version of GPUPerfAPI was available on the AMD Developer website. As part of the open-source effort,
we are also providing the ability to build the "Internal" versions of GPUPerfAPI. In addition to exposing the same counters as the Public version, the Internal version
also exposes some of the hardware Counters available in the GPU/APU. It's important to note that not all hardware counters receive the same validation as other parts of
the hardware on all GPUs, so in some cases accuracy of counter data cannot be guaranteed. The usage of the Internal version is identical to the Public version. The only
difference will be in the name of the library an application loads at runtime and the list of counters exposed by the library. See the [Build Instructions](BUILD.md) for
more information on how to build and use the Internal version. In the future, we see there being only a single version of GPUPerfAPI, with perhaps a change in the API to
allow users of GPA to indicate whether the library exposes just the Derived counters or both the Derived and the Hardware counters. We realize using the term "Internal"
for something which is no longer actually Internal-to-AMD can be a bit confusing, and we will aim to change this in the future.

## Known Issues
 * DirectX 12 support currently does not work with the most recent Radeon Pro Software Enterprise Edition 18.Q1
 * Adjusting the GPU clock mode on Linux is accomplished by writing to <br><br>/sys/class/drm/card\<N\>/device/power_dpm_force_performance_level<br><br> where \<N\> is
   the index of the card in question. By default this file is only modifiable by root, so the application being profiled would have to be run as root in order for it to
   modify the clock mode. It is possible to modify the permissions for the file instead so that it can be written by unprivileged users. The following command will
   achieve this. Note, however, that changing the permissions on a system file like this could circumvent security. Also, on multi-GPU systems, you may have to replace
   "card0" with the appropriate card number:
   * sudo chmod ugo+w /sys/class/drm/card0/device/power_dpm_force_performance_level
