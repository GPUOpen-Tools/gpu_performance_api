# GPUPerfAPI Build Instructions
---
## Table of Contents
* [Cloning/Updating Dependent Repositories](#cloningupdating-dependent-repositories)
* [Windows Build Information](#windows-build-information)
* [Linux Build Information](#linux-build-information)
* [PublicCounterCompiler Tool](#publiccountercompiler-tool)

## Cloning/Updating Dependent Repositories
GPUPerfAPI no longer uses git submodules to reference dependent repositories. Instead, you need to follow these instructions in
order to clone/update any dependent repositories.

#### Prerequisites
  * This step requires that python be installed on the system. Python can be installed from https://www.python.org/

#### Instructions
 * Simply execute the [UpdateCommon.py](Scripts/UpdateCommon.py) python script located in the [Scripts](Scripts) directory:
   * __python Scripts/UpdateCommon.py__
This script will clone any dependent repositories that are not present on the system. If any of the dependent repositories are already
present on the system, this script will instead do a "git pull" on those repositories to ensure that they are up to date. Please re-run
this script everytime you pull new changes from GPA repository.

## Windows Build Information

##### Prerequisites
 * Microsoft Visual Studio 2015 Community Edition or higher + Update 3
 * Windows 10 SDK Version 10.0.10586.0 from https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk
   * You can override the version of the Windows 10 SDK used by modifying Common/Lib/Ext/Windows-Kits/Global-WindowsSDK.props

##### Build Instructions
 * Load Build\VS2015\GPUPerfAPI.sln into Visual Studio
 * Build the 64-bit and/or 32-bit configuration
 * After a successful build, the GPUPerfAPI binaries can be found in __GPA\Output\\$(Configuration)\bin__ (for example GPA\Output\Release\bin)

#### Additional Information
 * The Visual Studio solution includes a Documentation project that allows you to generate the HTML-based source code documentation using Doxygen. In order
   to build that project, you'll need to modify [Documentation.vcxproj](Build/VS2015/Documentation.vcxproj) and modify the paths to the doxygen executable.
 * The Windows projects each include a .rc file that embeds the VERSIONINFO resource into the final binary. Internally within AMD, a Jenkins build system will dynamically update
   the build number. The version and build numbers can be manually updated by modifying the [GPAVersion.h](Src/GPUPerfAPI-Common/GPAVersion.h) file.
 * Information on building the Internal version:
    * To generate the internal version, two environment variables are required to be set prior to building in Visual Studio:
      * AMDT_BUILD=AMDT_INTERNAL
      * AMDT_BUILD_SUFFIX=-Internal
    * Each binary filename will have a "-Internal" suffix (for example GPUPerfAPIDX11-x64-Internal.dll)

## Linux Build Information

##### Build Instructions
 * cd into the Build\Linux directory
 * Execute __./build.sh__
   * By default this performs a from-scratch build of the release versions of GPUPerfAPI, both 32-bit and 64-bit binaries.
 * The following arguments can be passed to build.sh to alter the build:
   * __debug__: performs a debug build
   * __skip32buildbuild__: skips building the 32-bit binaries
   * __skipopengl__: skips building the OpenGL version of GPUPerfAPI
   * __skipopengles__: skips building the OpenGLES version of GPUPerfAPI
   * __skipopencl__: skips building the OpenCL version of GPUPerfAPI
   * __skiphsa__: skips building the ROCm/HSA version of GPUPerfAPI
   * __quick__ or __incremental__: performs an incremental build (as opposed to a from-scratch build)
   * __buildinternal__: builds the internal versions of GPUPerfAPI
   * __hsadir__: overrides the location of the ROCm/HSA header files (by default they are expected to be in /opt/rocm/hsa)
 * After a successful build, the GPUPerfAPI binaries can be found in their respective source file directories. For instance, the binaries for the OpenGL version of GPUPerfAPI (libGPUPerfAPIGL.so) can be found in the Src/GPUPerfAPIGL subdirectory.
 * Example build command line (builds the debug versions of the binaries, skipping the HSA library):
   * ./build.sh debug skiphsa
 * In addition to using the build.sh build script to build all of GPUPerfAPI, you can also build a single API library by executing __make__ in that library's directory. This is useful when making localized changes in a single version of GPUPerfAPI. When using __make__, the following default targets are supported:
   * __\<default\>__: makes the 64-bit release version
   * __x86__: makes the 32-bit release version
   * __Dbg__: makes the 64-bit debug version
   * __Dbgx86__: makes the 32-bit debug version
   * __Internal__: makes the 64-bit release Internal version
   * __Internalx86__: makes the 32-bit release Internal version
   * __DbgInternal__: makes the 64-bit debug Internal version
   * __DbgInternalx86__: makes the 32-bit debug Internal version
 * __Make__ is supported in the following directories (those marked with (*) are required to be built before the others, as they produce static libraries used by the others):
   * DeviceInfo (*)
   * GPUPerfAPI-Common (*)
   * GPUPerfAPICounterGenerator (*)
   * GPUPerfAPICounters
   * GPUPerfAPICL
   * GPUPerfAPIGL
   * GPUPerfAPIGLES
   * GPUPerfAPIHSA
 * When using __make__ to build the ROCM/HSA version of GPUPerfAPI, by default the HSA headers are expected to be in /opt/rocm/hsa. You can override this by specifying "HSA_DIR=<dir>" on the make command line:
   * Example: make Dbg HSA_DIR=/home/user/hsa_dir
 * When building the internal version, each binary filename will also have a "-Internal" suffix (for example libGPUPerfAPIGL-Internal.so)

## PublicCounterCompiler Tool

The PublicCounterCompiler Tool is a utility, written in C#, that will generate C++ code to define the public (or derived) counters.
It takes as input text files contained in the [PublicCounterCompilerInputFiles](Src/PublicCounterCompilerInputFiles) directory and
outputs files in the [GPUPerfAPICounterGenerator](Src/GPUPerfAPICounterGenerator) and [GPUPerfAPIUnitTests](Src/GPUPerfAPIUnitTests) directories.

There are three ways to execute the tool:
* With no parameters - it opens the user interface with no fields prepopulated
* With two parameters - it opens the user interface with the two main fields prepopulated. When you press the "Compile Public Counters" button it will load the correct input files and generate the output files in the correct location.
  * Param 1: API -- the API to compile counters for (ex: GL, CL, HSA, DX11, etc).
  * Param 2: HW generation: the generation to compile counters for (ex: Gfx6, Gfx7, Gfx8, etc.)
* With five parameters - the user interface does not open. It simply generates the c++ files using the specified input and output file locations
  * Param 1: Counter names file - text file containing hardware counter names and type (CounterNames[API][GEN].txt)
  * Param 2: Public counter definition file - text file defining how the public counters are calculated (PublicCounterDefinitions\*.txt)
  * Param 3: Output Dir - the directory to generate the output in (Ex: the path to the GPUPerfAPICounterGenerator directory)
  * Param 4: Test output Dir - the directory to generate the test output in (Ex: the path to the GPUPerfAPIUnitTests/counters directory)
  * Param 5: Active section label - the label to take the counter names from (ex: dx11gfx6)

See the various PublicCounterDefinitions\*.txt files in the [PublicCounterCompilerInputFiles](Src/PublicCounterCompilerInputFiles) directory. These contain all the counter definitions.
Each counter is given a name, a description, a type, an optional usage type, a list of hardware counters required and a formula applied to the values of the hardware counters to calculate the value of the counter.

Counter formulas are expressed in a Reverse Polish Notation and are made up the following elements:
* numbers: these are zero-based counter indexes referring to individual counters within the list of hardware counters
* math operators: The supported operators are +, -, /, *
* numeric literals: Numbers contained within parentheses are numeric literals (as opposed to counter indexes)
* functions: The supported functions are: min, max, sum, and ifnotzero. "max and "sum" have variants that work on multiple items at once (i.e. sum16, sum63, etc.)
* hardware params: The supported hardware params are "num_shader_engines". "num_simds", "su_clock_prim", "num_prim_pipes", and "TS_FREQ"

For more details, see the "EvaluateExpression" function in the [GPAPublicCounters.cpp](Src/GPUPerfAPICounterGenerator/GPAPublicCounters.cpp) file.

