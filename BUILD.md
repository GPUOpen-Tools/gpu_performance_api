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
  * Python, which can be installed from https://www.python.org/
  * CMake 3.5.1 or newer
    * For Windows, this can be downloaded from https://cmake.org/download/
    * For Linux, this can be installed using: sudo apt-get install cmake
  * To build the documentation:
    * Install Sphinx:
      * `pip install Sphinx`
    * Install Sphinx Read The Docs theme:
      * `pip install sphinx-rtd-theme` (read the docs theme is not installed by default)
    * Install spelling checker (optional)
      * `pip install pyenchant`
      * `pip install sphinxcontrib-spelling`

#### Instructions
 * Simply execute the [PreBuild.py](PreBuild.py) python script located in the GPA directory:
   * `python PreBuild.py`
 * This script will clone any dependent repositories that are not present on the system. If any of the dependent repositories are already
present on the system, this script will instead do a "git pull" on those repositories to ensure that they are up to date. Please re-run
this script everytime you pull new changes from GPA repository.
 * NOTE: For GPA 3.3 or newer, if you are updating an existing clone of the GPA repo from an earlier GPA release, you will first need to delete the Common/Lib/Ext/GoogleTest directory. Starting with GPA 3.3, GPA is now using a fork of the official GoogleTest repo. Failure to remove this directory will lead to git errors when running PreBuild.py or UpdateCommon.py.
 * This script will also download and execute the Vulkan™ SDK installer.
   * On Windows, running the installer may require elevation.  If you've previously installed the required Vulkan version, UpdateCommon will simply copy the files form the default installation location into the correct place into the GPUPerfAPI directory tree.
   * UpdateCommon is set up to install the version of the Vulkan SDK which was used during development. If you want to use a newer version of the SDK, the following file will need to be updated:
     * [UpdateCommonMap.py](Scripts/UpdateCommonMap.py)
   * By default the build will expect the Vulkan SDK to be found in a directory pointed to by the `VULKAN_SDK` environment variable. This environment variable is automatically set by the Windows SDK installer, but you may need to set it manually after running the Linux SDK installer. The Linux SDK includes a script called `setup-env.sh` to aid in setting this environment variable:
     * `source ~/VulkanSDK/1.0.68.0/setup-env.sh` (adjust path as necessary)
 * This script also executes cmake to generate all required files to build GPA.
 * If you want to generate all cmake build files without trying to clone/pull dependent repos, you can add "--nofetch" to the PreBuild.py command line.
 * Additional switches that can be used with the PreBuild.py script:
   * `--vs=[2015,2017]`: Specify the Visual Studio version for which to generate projects. Default is 2017.
    * `--config=[debug,release]`: Specify the config for which to generate makefiles. Default is both. A specific config can only be specified on Linux. On Windows, both configs are always supported by the generated VS solution and project files.
   * `--platform=[x86,x64]`: Specify the platform for which to generate build files. Default is both.
   * `--clean`: Deletes CMakeBuild directory and regenerates all build files from scratch
   * `--internal`: Generates build files to build the internal version of GPA
   * `--skipdx11`: Does not generate build files for DX11 version of GPA (Windows only)
   * `--skipdx12`: Does not generate build files for DX12 version of GPA (Windows only)
   * `--skipvulkan`: Does not generate build files for Vulkan version of GPA
   * `--skipopengl`: Does not generate build files for OpenGL version of GPA
   * `--skipopencl`: Does not generate build files for OpenCL version of GPA
   * `--skiprocm`: Does not generate build files for ROCm version of GPA (Linux only)
   * `--skiptests`: Does not generate build files for unit tests
   * `--skipdocs`: Does not generate build files for documentation
   * `--cmakecmd="CMD"`: Override the "cmake" command with "CMD"

## Windows Build Information

##### Prerequisites
 * Microsoft Visual Studio 2017
 * Windows 10 SDK Version 10.0.10586.0 from https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk
   * You can override the version of the Windows 10 SDK used by modifying Common/Lib/Ext/Windows-Kits/Global-WindowsSDK.props
 * Microsoft .NET 4.6.2 SDK from https://www.microsoft.com/en-us/download/details.aspx?id=53321

##### Build Instructions
 * Load CMakeBuild\x64\GPUPerfAPI.sln into Visual Studio to build the 64-bit version of GPA
 * Load CMakeBuild\x86\GPUPerfAPI.sln into Visual Studio to build the 32-bit version of GPA
 * After a successful build, the GPUPerfAPI binaries can be found in `GPA\Output\$(Configuration)` (for example GPA\Output\Release)

#### Additional Information
 * The Windows projects each include a .rc file that embeds the VERSIONINFO resource into the final binary. Internally within AMD, a Jenkins build system will dynamically update
   the build number. The version and build numbers can be manually updated by modifying the [GPAVersion.h](Src/GPUPerfAPI-Common/GPAVersion.h) file.
 * When building the internal version (using the --internal switch when calling PreBuild.py), each binary filename will have a "-Internal" suffix (for example GPUPerfAPIDX11-x64-Internal.dll)

## Linux Build Information

##### Prerequisites
 * Install the Mesa common development package: sudo apt-get install mesa-common-dev
 * For 32-bit builds, install the multilib packages: sudo apt-get install gcc-multilib g++-multilib
 * In order to build the ROCm/HSA version of GPA, you will need all or part of the ROCm stack installed
   * Follow the ROCm installation instructions to install either rocm-dkms or rocm-dev: https://rocm.github.io/ROCmInstall.html
     * In addition, please make sure that the optional ROCm package "rocprofiler-dev" is installed:
       * Ubuntu: sudo apt install rocprofiler-dev
       * CentOS: sudo yum install rocprofiler-dev

##### Build Instructions
 * Execute "make" in the CMakeBuild/x64/debug to build the 64-bit debug version of GPA
 * Execute "make" in the CMakeBuild/x64/release to build the 64-bit release version of GPA
 * Execute "make" in the CMakeBuild/x86/debug to build the 32-bit debug version of GPA
 * Execute "make" in the CMakeBuild/x86/release to build the 32-bit release version of GPA
 * After a successful build, the GPUPerfAPI binaries can be found in `GPA/Output/$(Configuration)` (for example GPA/Output/release)
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
