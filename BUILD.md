# GPUPerfAPI Build Instructions
---
## Table of Contents
* [Cloning/Updating Dependent Repositories](#cloningupdating-dependent-repositories)
* [Windows Build Information](#windows-build-information)
* [Linux Build Information](#linux-build-information)
* [PublicCounterCompiler Tool](#publiccountercompiler-tool)
* [Building the Documentation](#building-the-documentation)

## Cloning/Updating Dependent Repositories
GPUPerfAPI no longer uses git submodules to reference dependent repositories. Instead, you need to follow these instructions in
order to clone/update any dependent repositories.

#### Prerequisites
  * Python, which can be installed from https://www.python.org/

#### Instructions
 * Simply execute the [UpdateCommon.py](Scripts/UpdateCommon.py) python script located in the [Scripts](Scripts) directory:
   * `python Scripts/UpdateCommon.py`
 * This script will clone any dependent repositories that are not present on the system. If any of the dependent repositories are already
present on the system, this script will instead do a "git pull" on those repositories to ensure that they are up to date. Please re-run
this script everytime you pull new changes from GPA repository.
 * This script will also download and execute the Vulkan™ SDK installer.
   * On Windows, running the installer may require elevation.  If you've previously installed the required Vulkan version, UpdateCommon will simply copy the files form the default installation location into the correct place into the GPUPerfAPI directory tree.
   * UpdateCommon is set up to install the version of the Vulkan SDK which was used during development. If you want to use a newer version of the SDK, the following files will need to be updated:
     * [UpdateCommonMap.py](Scripts/UpdateCommonMap.py)
     * Linux-specific: [Common.mk](GPA/Build/Linux/Common.mk)
     * Windows-specific: Common/Lib/Ext/Global-Vulkan.props

## Windows Build Information

##### Prerequisites
 * Microsoft Visual Studio 2015 Community Edition or higher + Update 3
 * Windows 10 SDK Version 10.0.10586.0 from https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk
   * You can override the version of the Windows 10 SDK used by modifying Common/Lib/Ext/Windows-Kits/Global-WindowsSDK.props

##### Build Instructions
 * Load Build\VS2015\GPUPerfAPI.sln into Visual Studio
 * Build the 64-bit and/or 32-bit configuration
 * After a successful build, the GPUPerfAPI binaries can be found in `GPA\Output\$(Configuration)\bin` (for example GPA\Output\Release\bin)

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

##### Prerequisites
 * Install the Mesa common development package: sudo apt-get install mesa-common-dev
 * For 32-bit builds, install the multilib packages: sudo apt-get install gcc-multilib g++-multilib

##### Build Instructions
 * cd into the Build/Linux directory
 * Execute `./build.sh`
   * By default this performs a from-scratch build of the release versions of GPUPerfAPI, both 32-bit and 64-bit binaries.
 * The following arguments can be passed to build.sh to alter the build:
   * `debug`: performs a debug build
   * `skip32bitbuild`: skips building the 32-bit binaries
   * `skipopengl`: skips building the OpenGL version of GPUPerfAPI
   * `skipopencl`: skips building the OpenCL version of GPUPerfAPI
   * `skiphsa`: skips building the ROCm/HSA version of GPUPerfAPI
   * `skipvulkan`: skips building the Vulkan version of GPUPerfAPI
   * `doc`: builds the documentation
   * `quick` or `incremental`: performs an incremental build (as opposed to a from-scratch build)
   * `buildinternal`: builds the internal versions of GPUPerfAPI
   * `hsadir`: overrides the location of the ROCm/HSA header files (by default they are expected to be in /opt/rocm/hsa)
   * `gtestlibdir`: overrides the location of the GoogleTest libraries (by default they are expected to be in Common/Lib/Ext/GoogleTest/1-7/lib/gcc5/x64. There is also a gcc4.x-compatible version in Common/Lib/Ext/GoogleTest/1-7/lib/x64 for use when building on a system with gcc 4.x)
   * `gtestlibdir32`: overrides the location of the 32-bit GoogleTest libraries (by default they are expected to be in Common/Lib/Ext/GoogleTest/1-7/lib/gcc5/x86. There is also a gcc4.x-compatible version in Common/Lib/Ext/GoogleTest/1-7/lib/x86 for use when building on a system with gcc 4.x)
 * After a successful build, the GPUPerfAPI binaries can be found in Output/bin.
 * Example build command line (builds the debug versions of the binaries, skipping the HSA library):
   * ./build.sh debug skiphsa
 * In addition to using the build.sh build script to build all of GPUPerfAPI, you can also build a single API library by executing `make` in that library's directory. This is useful when making localized changes in a single version of GPUPerfAPI. When using `make`, the following default targets are supported:
   * `\<default\>`: makes the 64-bit release version
   * `x86`: makes the 32-bit release version
   * `Dbg`: makes the 64-bit debug version
   * `Dbgx86`: makes the 32-bit debug version
   * `Internal`: makes the 64-bit release Internal version
   * `Internalx86`: makes the 32-bit release Internal version
   * `DbgInternal`: makes the 64-bit debug Internal version
   * `DbgInternalx86`: makes the 32-bit debug Internal version
 * `Make` is supported in the following directories (those marked with (*) are required to be built before the others, as they produce static libraries used by the others):
   * DeviceInfo (*)
   * GPUPerfAPI (*)
   * GPUPerfAPI-Common (*)
   * GPUPerfAPICounterGenerator (*)
   * GPUPerfAPICounters
   * GPUPerfAPICL
   * GPUPerfAPIGL
   * GPUPerfAPIHSA
   * GPUPerfAPIVk
 * When using `make` to build the ROCM/HSA version of GPUPerfAPI, by default the HSA headers are expected to be in /opt/rocm/hsa. You can override this by specifying "HSA_DIR=<dir>" on the make command line:
   * Example: make Dbg HSA_DIR=/home/user/hsa_dir
 * When building the internal version, each binary filename will also have a "-Internal" suffix (for example libGPUPerfAPIGL-Internal.so)

## PublicCounterCompiler Tool

The PublicCounterCompiler Tool is a utility, written in C#, that will generate C++ code to define the public (or derived) counters.
It takes as input text files contained in the [PublicCounterCompilerInputFiles](Src/PublicCounterCompilerInputFiles) directory and
outputs files in the [GPUPerfAPICounterGenerator](Src/GPUPerfAPICounterGenerator), [GPUPerfAPIUnitTests](Src/GPUPerfAPIUnitTests)
and [docs](docs) directories.

There are three ways to execute the tool:
* With no parameters - it opens the user interface with no fields prepopulated
* With two parameters - it opens the user interface with the two main fields prepopulated. When you press the "Compile Public Counters" button it will load the correct input files and generate the output files in the correct location.
  * Param 1: API -- the API to compile counters for (ex: GL, CL, HSA, DX11, DX12, VK, etc).
  * Param 2: HW generation: the generation to compile counters for (ex: Gfx6, Gfx7, Gfx8, etc.)
* With six or seven parameters - the user interface does not open. It simply generates the c++ files using the specified input and output file locations
  * Param 1: Counter names file - text file containing hardware counter names and type (CounterNames[API][GEN].txt)
  * Param 2: Public counter definition file - text file defining how the public counters are calculated (PublicCounterDefinitions\*.txt)
  * Param 3: Output Dir - the directory to generate the output in (Ex: the path to the GPUPerfAPICounterGenerator directory)
  * Param 4: Test output Dir - the directory to generate the test output in (Ex: the path to the GPUPerfAPIUnitTests/counters directory)
  * Param 5: API - the API to take the counter names from (ex: DX12)
  * Param 6: GPU - the GPU to take the counter names from (ex: Gfx9)
  * Param 7: GPU ASIC - (optional) the subversion of GPU to take the counter names from

See the various PublicCounterDefinitions/*.txt files in the [PublicCounterCompilerInputFiles](Src/PublicCounterCompilerInputFiles) directory. These contain all the counter definitions.
Each counter is given a name, a description, a type, an optional usage type, a list of hardware counters required and a formula applied to the values of the hardware counters to calculate the value of the counter.

Counter formulas are expressed in a Reverse Polish Notation and are made up the following elements:
* numbers: these are zero-based counter indexes referring to individual counters within the list of hardware counters
* hardware counters may also be referred to by name (e.g.: GPUTime_Bottom_To_Bottom) or templated name (e.g.: SPI*_SPI_PERF_CSG_BUSY) which will automatically refer to the correct number of instances
* math operators: The supported operators are +, -, /, *
* numeric literals: Numbers contained within parentheses are numeric literals (as opposed to counter indexes)
* functions: The supported functions are: min, max, sum, ifnotzero, and vcomparemax4. "max and "sum" have variants that work on multiple items at once (i.e. sum16, sum64, etc.)
* hardware params: The supported hardware params are "num_shader_engines". "num_simds", "su_clock_prim", "num_prim_pipes", and "TS_FREQ"

For more details, see the "EvaluateExpression" function in the [GPAPublicCounters.cpp](Src/GPUPerfAPICounterGenerator/GPAPublicCounters.cpp) file.

## Building the Documentation

##### Prerequisites
 * A working python installation is required
 * Install Sphinx:
   * `pip install Sphinx`
 * Install Sphinx Read The Docs theme:
   * `pip install sphinx-rtd-theme` (read the docs theme is not installed by default)
 * Install spelling checker (optional)
  * `pip install pyenchant`
  * `pip install sphinxcontrib-spelling`

##### Building
 * Once you have Sphinx installed, simply run the following command from the "docs" subdirectory:
   * `make html`
 * To run the spelling checker:
   * edit conf.py and uncomment the line adding in the `sphinxcontrib.spelling` extension
   * `make spelling`
