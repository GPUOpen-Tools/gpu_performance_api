# GPUPerfAPI Build Instructions
---
## Table of Contents
* [Cloning & Updating Dependent Repositories](#cloningupdating-dependent-repositories)
* [Windows Build Information](#windows-build-information)
* [Linux Build Information](#linux-build-information)
* [PublicCounterCompiler Tool](#publiccountercompiler-tool)

## Cloning & Updating Dependent Repositories
GPUPerfAPI no longer uses git submodules to reference dependent repositories. Instead, you need to follow these instructions in
order to clone and update any dependent repositories.

#### Prerequisites
  * Python 3.x, which can be installed from https://www.python.org/.
  * CMake 3.19 and newer.
    * For Windows, this can be downloaded from https://cmake.org/download/.
    * For Linux, this can be installed using:
      * `sudo apt-get install cmake`
  * To build the documentation:
    * Install Sphinx:
      * `pip install sphinx`
    * Install Sphinx Read The Docs theme:
      * `pip install sphinx-rtd-theme` (read the docs theme is not installed by default)
    * Install spelling checker (optional)
      * `pip install pyenchant`
      * `pip install sphinxcontrib-spelling`
    * **Note:** Be sure to add Python scripts to PATH in order to build documentation from prebuild scripts.

#### Instructions
 * Simply execute the [pre_build.py](build/pre_build.py) Python script located in the GPA directory:
   * `python build/pre_build.py`
 * This script will clone any dependent repositories that are not present on the system. If any of the dependent repositories are already
present on the system, this script will instead do a "git pull" on those repositories to ensure that they are up to date. Please re-run
this script everytime you pull new changes from GPA repository.
 * **Note:** For GPA 3.3 and newer, if you are updating an existing clone of the GPA repo from a GPA release prior to 3.3, you will first need to delete the Common/Lib/Ext/GoogleTest directory. Starting with GPA 3.3, GPA is now using a fork of the official GoogleTest repo. Failure to remove this directory will lead to Git errors when running [pre_build.py](build/pre_build.py) or [fetch_dependencies.py](scripts/fetch_dependencies.py).
 * **Note:** For GPA 3.11 and newer, the Common/ directory has been removed, and the external/Lib/Ext/GoogleTest will first need to be deleted instead.
 * This script will also download and execute the Vulkan SDK installer.
   * On Windows, running the installer may require elevation. If you've previously installed the required Vulkan version, fetch_dependencies.py will simply copy the files from the default installation location into the correct place into the GPUPerfAPI directory tree.
   * fetch_dependencies.py is set up to install the version of the Vulkan SDK which was used during development. If you want to use a newer version of the SDK, the following file will need to be updated:
     * [fetch_dependencies.py](scripts/fetch_dependencies.py)
   * By default the build will expect the Vulkan SDK to be found in a directory pointed to by the `VULKAN_SDK` environment variable. This environment variable is automatically set by the Windows SDK installer, but you may need to set it manually after running the Linux SDK installer. The Linux SDK includes a script called `setup-env.sh` to aid in setting this environment variable:
     * `source ~/VulkanSDK/1.0.68.0/setup-env.sh` (adjust PATH as necessary)
 * This script also executes CMake to generate all required files to build GPA.
 * If you want to generate all CMake build files without trying to clone/pull dependent repos, you can add "--nofetch" to the [pre_build.py](build/pre_build.py) command line.
 * Additional switches that can be used with the [pre_build.py](build/pre_build.py) script:
   * `--vs=[2015,2017,2019,2022]`: Specify the Visual Studio version for which to generate projects. Default is 2022.
    * `--config=[debug,release]`: Specify the config for which to generate makefiles. Default is both. A specific config can only be specified on Linux. On Windows, both configs are always supported by the generated VS solution and project files.
   * `--platform=[x86,x64]`: Specify the platform for which to generate build files. Default is both.
   * `--clean`: Deletes CMakeBuild directory and regenerates all build files from scratch
   * `--skipdx11`: Does not generate build files for DX11 version of GPA (Windows only)
   * `--skipdx12`: Does not generate build files for DX12 version of GPA (Windows only)
   * `--skipvulkan`: Does not generate build files for Vulkan version of GPA
   * `--skipopengl`: Does not generate build files for OpenGL version of GPA
   * `--skipopencl`: Does not generate build files for OpenCL version of GPA
   * `--skiptests`: Does not generate build files for unit tests
   * `--skipdocs`: Does not generate build files for documentation
   * `--cmakecmd="CMD"`: Override the "cmake" command with "CMD"

## Windows Build Information

##### Prerequisites
 * Microsoft Visual Studio 2022
 * Within the Visual Studio Installer, the following workloads: 
   * Desktop development with C++
 * Within the Visual Studio Installer, the following individual components:
   * Windows 11 SDK (10.0.22621.0)
   * MSVC v143 - VS 2022 C++ x74/x86 build tools (latest)
   * C++ CMake tools for Windows
   * C++ Clang Compiler for Windows (15.0.1)
   * .NET Framework 4.6.2-4.8.1 SDKs and targeting packs
   * C# and Visual Basic
   * C# and Visual Basic Roslyn compilers

##### Build Instructions
 * Load cmake_bld\x64\GPUPerfAPI.sln into Visual Studio to build the 64-bit version of GPA.
 * Load cmake_bld\x86\GPUPerfAPI.sln into Visual Studio to build the 32-bit version of GPA.
 * After a successful build, the GPUPerfAPI binaries can be found in `gpu_performance_api\output\$(Configuration)` (e.g. gpu_performance_api\output\release).

#### Additional Information
 * The Windows projects each include a .rc file that embeds the VERSIONINFO resource into the final binary. Internally within AMD, a Jenkins build system will dynamically update.
   the build number. The version and build numbers can be manually updated by modifying the [gpa_version.h](source/gpu_perf_api_common/gpa_version.h) file.

## Linux Build Information

##### Prerequisites
 * Install the Mesa common development package:
   * `sudo apt-get install mesa-common-dev`

##### Build Instructions
 * Execute "make" in the cmake_bld/x64/debug to build the 64-bit debug version of GPA.
 * Execute "make" in the cmake_bld/x64/release to build the 64-bit release version of GPA.
 * After a successful build, the GPUPerfAPI binaries can be found in `gpu_performance_api/output/$(Configuration)` (e.g. gpu_performance_api/output/release).

## PublicCounterCompiler Tool
The PublicCounterCompiler Tool is a C# utility that will generate C++ code to define the public (or derived) counters.
It takes as input text files contained in the [public_counter_compiler_input_files](source/public_counter_compiler_input_files) directory and
outputs files in the [gpu_perf_api_counter_generator](source/auto_generated/gpu_perf_api_counter_generator), [gpu_perf_api_unit_tests](source/auto_generated/gpu_perf_api_unit_tests)
and [docs](docs) directories.

There are three ways to execute the tool:
* With no parameters - the user interface opens with no fields prepopulated.
* With two parameters - the user interface opens with the two main fields prepopulated. Note that pressing the "Compile Public Counters" button will load the correct input files and generate the output files in the correct location.
  * Param 1: **API** - the API to compile counters for (e.g. GL, CL, DX11, DX12, VK, etc.)
  * Param 2: **HW generation** - the generation to compile counters for (ex: Gfx9, Gfx10, Gfx11 etc.)
* With six or seven parameters - the user interface does not open and will generate the C++ files using the specified input and output file locations.
  * Param 1: **Counter names file** - text file containing hardware counter names and type (CounterNames[API][GEN].txt)
  * Param 2: **Public counter definition file** - text file defining how the public counters are calculated (PublicCounterDefinitions\*.txt)
  * Param 3: **Output Dir** - the directory to generate the output in (e.g. the path to the GPUPerfAPICounterGenerator directory)
  * Param 4: **Test output Dir** - the directory to generate the test output in (e.g. the path to the GPUPerfAPIUnitTests/counters directory)
  * Param 5: **API** - the API to take the counter names from (e.g. DX12)
  * Param 6: **GPU** - the GPU to take the counter names from (e.g. Gfx11)
  * Param 7: **GPU ASIC** - the subversion of GPU to take the counter names from (optional)

See the various `public_counter_definitions_*.txt` files in the [public_counter_compiler_input_files](source/public_counter_compiler_input_files) directory. These contain all the counter definitions.
Each counter is given a name, a description, a type, an optional usage type, a list of hardware counters required and a formula applied to the values of the hardware counters to calculate the value of the counter.

Counter formulas are expressed in a Reverse Polish Notation and are made up the following elements:
* numbers: Zero-based counter indexes referring to individual counters within the list of hardware counters
* math operators: Supported operators are +, -, /, *
* numeric literals: Numbers contained within parentheses are numeric literals (as opposed to counter indexes)
* functions: Supported functions are: min, max, sum, ifnotzero, and vcomparemax4. "max and "sum" have variants that work on multiple items at once (i.e. sum16, sum64, etc.)
* hardware params: Supported hardware params are "num_shader_engines", "num_simds", "su_clock_prim", "num_prim_pipes", and "TS_FREQ"
* **Note:** Hardware counters may also be referred to by name (e.g.: GPUTime_Bottom_To_Bottom) or templated name (e.g.: SPI*_SPI_PERF_CSG_BUSY) which will automatically refer to the correct number of instances.

For more details, see the "EvaluateExpression" function in the [gpa_derived_counter.cc](source/gpu_perf_api_counter_generator/gpa_derived_counter.cc) file.
