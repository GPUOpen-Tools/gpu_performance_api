# GPU Performance API
---
The AMD GPU Performance API (GPUPerfAPI, or GPA) is a powerful library which provides access to GPU Performance Counters.
It can help analyze the performance and execution characteristics of applications using an AMD Radeon™ GPU. This library
is used by [AMD Radeon GPU Profiler](https://github.com/GPUOpen-Tools/radeon_gpu_profiler) as well as several third-party tools.

## Table of Contents
* [Downloads](#downloads)
* [Major Features](#major-features)
* [System Requirements](#system-requirements)
* [Cloning the Repository](#cloning-the-repository)
* [Source Code Directory Layout](#source-code-directory-layout)
* [Documentation](#documentation)
* [Raw Hardware Counters](#raw-hardware-counters)
* [Known Issues](#known-issues)
* [Building the Source Code](build.md)
* [License](LICENSE.txt)
* [Release Notes](RELEASE_NOTES.txt)
* [Style and Format Change](#Style-and-Format-Change)

## Downloads
Prebuilt binaries can be downloaded from the Releases page: https://github.com/GPUOpen-Tools/gpu_performance_api/releases.

## Major Features
* Provides a standard API for accessing GPU Performance counters for both graphics and compute workloads across multiple GPU APIs.
* Supports Vulkan™, DirectX™ 12, DirectX 11, and OpenGL™.
* Supports all current AMD Radeon graphics cards and APUs based on Graphics IP version 10 and newer.
* Supports both Windows and Linux.
* Provides derived "public" counters based on raw hardware counters.
* Provides access to some raw hardware counters. See [Raw Hardware Counters](#raw-hardware-counters) for more information.

### Transitioning from GPA 3.x to 4.0
#### Summary
The main change in GPA 4.0 is that the counters are no longer exposed via the GpaContext and are now exposed by the GpaSession. There are now two different sets of counters, depending on the GpaSessionSampleType that is passed in when creating the session.
Not all hardware and not all rendering APIs support all the `GpaSessionSampleTypes`, so after creating the GpaContext you should call `GpaGetSupportedSampleTypes(..)` to query which GpaSessionSampleTypes are supported on the given configuration.
Users of the GPU Performance API should still only be looking for the `kGpaSessionSampleTypeDiscreteCounter` sample type. No support will be provided for the other sample types. Once the GpaSession is created, you can then use `GpaGetNumCounters(..)` and all
of the `GpaGetCounter*(..)` entrypoints to query information about the available counters.

Below you will find an example of a likely subset of GPA 3.x series of API calls, and then a similar series of calls using the modified GPA 4.0 entrypoints. Note that no error checking is being done here for sake of clarity.

#### Example of GPA 3.x Usage
```c++
GpaContextId context = nullptr;
GpaOpenContext(api_context, kGpaOpenContextDefaultBit, &context);
GpaUInt32 num_counters = 0;
GpaGetNumCounters(context, &num_counters);
for (GpaUInt32 i = 0; i < num_counters; ++i)
{
    const char* name = nullptr;
    GpaUInt32 index = 0;
    const char* description = nullptr;
    GpaDataType data_type = kGpaDataTypeLast;
    GpaUsageType usage_type = kGpaUsageTypeLast;
    GpaUuid uuid = {};
    GpaCounterSampleType sample_type = kGpaCounterSampleTypeDiscrete;

    GpaGetCounterName(context, i, &name);
    GpaGetCounterIndex(context, name, &index);
    assert(i == index);
    GpaGetCounterDescription(context, i, &description);
    GpaGetCounterDataType(context, i, &data_type);
    GpaGetCounterUsageType(context, i, &usage_type);
    GpaGetCounterUuid(context, i, &uuid);
    GpaGetCounterSampleType(context, i, &sample_type);
    assert(sample_type == kGpaCounterSampleTypeDiscrete);
}
GpaSessionId session = nullptr;
GpaCreateSession(context, kGpaContextSampleTypeDiscreteCounter, &session);
GpaUInt32 desired_counter_index = 0;
GpaEnableCounter(session, desired_counter_index);
GpaBeginSession(session);
```

#### Example of equivalent GPA 4.X Usage
```c++
GpaContextId context = nullptr;
GpaOpenContext(api_context, kGpaOpenContextDefaultBit, &context);

// These next two lines and the following conditional ensure that discrete
// counters are supported by the GpaContext for the current hardware and
// driver. In general the GpaOpenContext call above will report an error
// if the hardware and driver are not supported at all, but in some rare cases
// the discrete counters may not be supported while other sample types are.
GpaContextSampleTypeFlags supported_sample_types = kGpaSessionSampleTypeLast;
GpaGetSupportedSampleTypes(context, &supported_sample_types);

if (supported_sample_types & kGpaSessionSampleTypeDiscreteCounter != 0)
{
    // The set of available counters are now dependent on the SampleType being
    // collected within the session, so the session must now be created prior
    // to querying for the available counters.
    GpaSessionId session = nullptr;
    GpaCreateSession(context, kGpaContextSampleTypeDiscreteCounter, &session);

    // The GpaSessionId is now supplied into GpaGetNumCounters() to get the
    // number of discrete counters that are available.
    GpaUInt32 num_counters = 0;
    GpaGetNumCounters(session, &num_counters);
    for (GpaUInt32 i = 0; i < num_counters; ++i)
    {
        const char* name = nullptr;
        GpaUInt32 index = 0;
        const char* description = nullptr;
        GpaDataType data_type = kGpaDataTypeLast;
        GpaUsageType usage_type = kGpaUsageTypeLast;
        GpaUuid uuid = {};
        GpaCounterSampleType sample_type = kGpaCounterSampleTypeDiscrete;

        // These next set of counter querying entrypoints now take in
        // a GpaSessionId rather than the GpaContextId.
        GpaGetCounterName(session, i, &name);
        GpaGetCounterIndex(session, name, &index);
        assert(i == index);
        GpaGetCounterDescription(session, i, &description);
        GpaGetCounterDataType(session, i, &data_type);
        GpaGetCounterUsageType(session, i, &usage_type);
        GpaGetCounterUuid(session, i, &uuid);
        GpaGetCounterSampleType(session, i, &sample_type);
        assert(sample_type == kGpaCounterSampleTypeDiscrete);
    }
    GpaUInt32 desired_counter_index = 0;
    GpaEnableCounter(session, desired_counter_index);
    GpaBeginSession(session);
}
```

## System Requirements
* An AMD Radeon GPU or APU based on Graphics IP version 10 and newer.
* Windows: Radeon Software Adrenalin 2020 Edition 20.11.2 or later (Driver Packaging Version 20.45 or later).
* Linux: Radeon Software for Linux Revision 20.45 or later.
* Radeon GPUs or APUs based on Graphics IP version 8 and 9 are no longer supported by GPUPerfAPI. Please use an older version ([3.17](https://github.com/GPUOpen-Tools/gpu_performance_api/releases/tag/v3.17-tag)) with older hardware.
* Radeon GPUs or APUs based on Graphics IP version 6 and 7 are no longer supported by GPUPerfAPI. Please use an older version ([3.3](https://github.com/GPUOpen-Tools/gpu_performance_api/releases/tag/v3.3)) with older hardware.
* Windows 10 or 11.
* Ubuntu (22.04 and later) and CentOS/RHEL (7 and later) distributions.

## Source Code Directory Layout
* [build](build) -- contains build scripts and cmake build modules
* [docs](docs) -- contains sphinx documentation sources and a Doxygen configuration file
* [include/gpu_performance_api](include/gpu_performance_api) -- contains GPUPerfAPI public headers
* [scripts](scripts) -- scripts to use to clone/update dependent repositories
* [source/auto_generated](source/auto_generated) -- contains auto-generated source code used when building GPUPerfAPI
* [source/gpu_perf_api_common](source/gpu_perf_api_common) -- contains source code for a Common library shared by all versions of GPUPerfAPI
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
* [source/third_party](source/third_party) -- third-party files that are included as part of the GPUPerfAPI repo

## Documentation
The documentation for GPUPerfAPI can be found in each [GitHub release](https://github.com/GPUOpen-Tools/gpu_performance_api/releases). In the release .zip file or .tgz file, there
will be a "docs" directory. Simply open the index.html file in a web browser to view the documentation.

The documentation is hosted publicly at: https://gpuopen.com/manuals/gpu_performance_api_manual/

## Raw Hardware Counters
This release exposes "Discrete", "Streaming" (SPM), and "Hardware" counters. Discrete and streaming counters are computed (ie: derived) using a set of low level hardware counters. Not all discrete counters are available as streaming counters, and not all streaming counters are available as discrete counters.
This version allows you to access the hardware counters by simply specifying a flag when calling GpaOpenContext.

## Pipeline-Based Counter Nomenclature
It was discovered that the improvements introduced in Vega, RDNA, and RDNA2 architectures were not being properly accounted for in GPUPerfAPI v3.9, and caused a lot of known issues to be called out in that release. In certain cases, the driver and hardware are able to make optimizations by combining two shader stages together, which prevented GPUPerfAPI from identifying which instructions were executed for which shader type. As a result of these changes, GPUPerfAPI is no longer able to expose instruction counters for each API-level shader, specifically Vertex Shaders, Hull Shaders, Domain Shaders, and Geometry Shaders. Pixel Shaders and Compute Shaders remain unchanged. We are now exposing these instruction counters based on the type of shader pipeline being used. In pipelines that do not use tessellation, the instruction counts for both the Vertex and Geometry Shaders (if used) will be combined in the VertexGeometry group (ie: counters with the "VsGs" prefix). In pipelines that use tessellation, the instruction counts for both the Vertex and Hull Shaders will be combined in the PreTessellation group (ie: counters with the "PreTessellation" or "PreTess" prefix), and instruction counts for the Domain and Geometry Shaders (if used) will be combined in the PostTessellation group (ie: counters with the "PostTessellation" or "PostTess" prefix). The table below may help to better understand the new mapping between the API-level shaders (across the top), and which prefixes to look for in the GPUPerfAPI counters.

| Pipeline       | Vertex  |  Hull   |  Domain  | Geometry | Pixel | Compute |
|----------------|:-------:|:-------:|:--------:|:--------:|:-----:|:-------:|
| VS-PS          |  VsGs   |         |          |          |  PS   |         |
| VS-GS-PS       |  VsGs   |         |          |   VsGs   |  PS   |         |
| VS-HS-DS-PS    | PreTess | PreTess | PostTess | PostTess |  PS   |         |
| VS-HS-DS-GS-PS | PreTess | PreTess | PostTess | PostTess |  PS   |         |
| CS             |         |         |          |          |       |   CS    |

## Known Issues

### Unable to set clock mode on Windows after Nth time (N ~= 50)
After a large number of consecutive profiling sessions (typically around 50), the GPU Performance API (GPA) may become unable to configure the GPU clock mode on Windows systems.

This behavior has been traced to an issue in the AMD Windows kernel‑mode driver. The only known workaround is to restart the system when this condition occurs.

### Intermittent TDR Events on RDNA4 GPUs
During profiling on AMD RDNA4‑based graphics hardware, users may encounter sporadic Timeout Detection and Recovery (TDR) events. AMD is actively investigating the root cause and working on a fix.

### GPA doesn't support MESA on Linux
GPA is only compatible with AMD's Pro and Open Source drivers.

### Counter Validity on Specific Hardware
There are some counters that are returning unexpected results on specific hardware with certain APIs.
* AMD Radeon RX 6700M, DX11: CSLDSBankConflict and CSLDSBankConflictCycles may consistently report as much as 30x higher than expected.
* VsGsVerticesIn is incorrectly reporting zero when using Vulkan on Linux for some hardware.

### OpenGL FetchSize Counter on Radeon RX 6000 Series GPUs
FetchSize counter will show an error when enabled on Radeon RX 6000 Series GPUs using OpenGL.

### Adjusting Linux Clock Mode
Adjusting the GPU clock mode on Linux is accomplished by writing to: `/sys/class/drm/card\<N\>/device/power_dpm_force_performance_level`, where \<N\> is the index of the card in question.

By default this file is only modifiable by root, so the application being profiled would have to be run as root in order for it to modify the clock mode. It is possible to modify the permissions for the file instead so that it can be written by unprivileged users. The following command will achieve this: `sudo chmod ugo+w /sys/class/drm/card0/device/power_dpm_force_performance_level`
* Note that changing the permissions on a system file like this could circumvent security.
* On multi-GPU systems you may have to replace "card0" with the appropriate card number.
* You may have to reboot the system for the change to take effect.
* Setting the GPU clock mode is not working correctly for <b>Radeon 5700 Series GPUs</b>, potentially leading to some inconsistencies in counter values from one run to the next.

### Profiling Bundles
Profiling bundles in DirectX12 and Vulkan is not working properly. It is recommended to remove those GPA Samples from your application, or move the calls out of the bundle for profiling.

## Style and Format Change
The source code of GPUPerfAPI is formatted to follow the Google C++ Style Guide https://google.github.io/styleguide/cppguide.html.
Please refer to the .clang-format file in the root directory of the product for additional style information.
