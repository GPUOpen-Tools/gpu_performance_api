# GPU Performance API
---

## Overview
The GPU Performance API (GPUPerfAPI, or GPA) is a powerful library, providing access to GPU Performance Counters.
It can help analyze the performance and execution characteristics of applications using a Radeon™ GPU. This library
is used by both CodeXL and GPU PerfStudio.

## Table of Contents
* [Major Features](#major-features)
* [What's New](#whats-new)
* [System Requirements](#system-requirements)
* [Cloning the Repository](#cloning-the-repository)
* [Source Code Directory Layout](#source-code-directory-layout)
* ["Public" vs "Internal" Versions](#public-vs-internal-versions)
* [Known Issues](#known-issues)
* [Building the Source Code](BUILD.md)
* [GPUPerfAPI User Guide](Doc/GPUPerfAPI-UserGuide.pdf)
* [License](LICENSE)
* [Historical Release Notes](ReleaseNotes.md)

## Major Features
* Provides a standard API for accessing GPU Performance counters for both graphics and compute workloads across multiple GPU APIs.
* Supports DirectX11, OpenGL, OpenGLES, OpenCL™, and ROCm/HSA
* Developer Preview for DirectX12 (no hardware-based performance counter support yet)
* Supports all current GCN-based Radeon graphics cards and APUs.
* Supports both Windows and Linux
* Provides derived "public" counters based on raw HW counters
* "Internal" version provides access to some raw hardware counters. See ["Public" vs "Internal" Versions](#PublicInternal) for more information.

## What's New
* Version 2.23 (6/27/17)
  * Add support for additional GPUs, including Vega series GPUs
  * Allow unit tests to be built and run on Linux

## System Requirements
* An AMD Radeon GCN-based GPU or APU
* Radeon Software Crimson ReLive Edition 17.4.3 or later (Driver Packaging Version 17.10 or later).
  * For Vega support, a driver with Driver Packaging Version 17.20 or later is required
* Pre-GCN-based GPUs or APUs are no longer supported by GPUPerfAPI. Please use an older version ([2.17](http://developer.amd.com/tools-and-sdks/graphics-development/gpuperfapi/)) with older hardware.
* Windows 7, 8.1, and 10
* Ubuntu (16.04 and later) and RHEL (7 and later) distributions

## Cloning the Repository
To clone the GPA repository, execute the following git commands
 * git clone https://github.com/GPUOpen-Tools/GPA.git
After cloning the repository, please run the following python script to retrieve the required dependencies (see [BUILD.md](BUILD.md) for more information):
 * python Scripts/UpdateCommon.py
UpdateCommon has replaced the use of git submodules in the GPA repository

## Source Code Directory Layout
* [Build](Build) -- contains both Linux and Windows build-related files
* [Common](Common) -- Common libs, header and source code not found in other repositories
* [Doc](Doc) -- contains User Guide and Doxygen configuration files
* [Src/DeviceInfo](Src/DeviceInfo) -- builds a lib containing the Common/Src/DeviceInfo code (Linux only)
* [Src/GPUPerfAPI-Common](Src/GPUPerfAPI-Common) -- contains source code for a Common library shared by all versions of GPUPerfAPI
* [Src/GPUPerfAPICL](Src/GPUPerfAPICL) - contains the source for the OpenCL™ version of GPUPerfAPI
* [Src/GPUPerfAPICounterGenerator](Src/GPUPerfAPICounterGenerator) - contains the source code for a Common library providing all counter data
* [Src/GPUPerfAPICounters](Src/GPUPerfAPICounters) - contains the source code for a library that can be used to query counters without an active GPUPerfAPI context
* [Src/GPUPerfAPIDX](Src/GPUPerfAPIDX) - contains source code shared by the DirectX versions of GPUPerfAPI
* [Src/GPUPerfAPIDX11](Src/GPUPerfAPIDX11) - contains the source for the DirectX11 version of GPUPerfAPI
* [Src/GPUPerfAPIDX12](Src/GPUPerfAPIDX12) - contains the source for the DirectX12 version of GPUPerfAPI (Developer Preview)
* [Src/GPUPerfAPIGL](Src/GPUPerfAPIGL) - contains the source for the OpenGL version of GPUPerfAPI
* [Src/GPUPerfAPIGLES](Src/GPUPerfAPIGLES) - contains the source for the OpenGLES version of GPUPerfAPI
* [Src/GPUPerfAPIHSA](Src/GPUPerfAPIHSA) - contains the source for the ROCm/HSA version of GPUPerfAPI
* [Src/GPUPerfAPIUnitTests](Src/GPUPerfAPIUnitTests) - contains a small set of unit tests for GPUPerfAPI
* [Src/PublicCounterCompiler](Src/PublicCounterCompiler) - source code for a tool to generate C++ code for public counters from text files defining the counters.
* [Src/PublicCounterCompilerInputFiles](Src/PublicCounterCompilerInputFiles) - input files that can be fed as input to the PublicCounterCompiler tool
* [Scripts](Scripts) -- scripts to use to clone/update dependent repositories

## "Public" vs "Internal" Versions
This open source release supports building both the "Public" and "Internal" versions of GPUPerfAPI. By default the Visual Studio solution and the Linux build scripts
will produce what is referred to as the "Public" version of GPUPerfAPI. This version exposes "Public", or "Derived", counters. These are counters that are computed
using a set of hardware counters. Until now, only the Public the version of GPUPerfAPI was available on the AMD Developer website. As part of the open-source effort,
we are also providing the ability to build the "Internal" versions of GPUPerfAPI. In addition to exposing the same counters as the Public version, the Internal version
also exposes some of the hardware Counters available in the GPU/APU. It's important to note that not all hardware counters receive the same validation as other parts of
the hardware on all GPUs, so in some cases accuracy of counter data cannot be guaranteed.  The usage of the Internal version is identical to the Public version. The only
difference will be in the name of the library an application loads at runtime and the list of counters exposed by the library. See the [Build Instructions](BUILD.md) for
more information on how to build and use the Internal version. In the future, we see there being only a single version of GPUPerfAPI, with perhaps a change in the API to
allow users of GPA to indicate whether the library exposes just the Derived counters or both the Derived and the Hardware counters.  We realize using the term "Internal"
for something which is no longer actually Internal-to-AMD can be a bit confusing, and we will aim to change this in the future.

## Known Issues
 * The OpenCL™ version of GPUPerfAPI is not currently working for Vega GPUs on Windows when using a 17.20-based driver. This is due to missing driver support in the 17.20 driver. Future driver versions should provide the support needed.