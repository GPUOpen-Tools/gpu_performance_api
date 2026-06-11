# GPUPerfAPI Build Instructions

## Table of Contents
* [Windows Build Information](#windows-build-information)
* [Linux Build Information](#linux-build-information)
* [PublicCounterCompiler Tool](#publiccountercompiler-tool)

#### Prerequisites
  * Python 3.6 or newer which can be installed from https://www.python.org/.
  * CMake 3.25 and newer which can be installed from https://cmake.org/download/ or your package manager.
    * On Windows, this can also be installed using:
      * `winget install cmake`
    * On Linux, this can also be installed using:
      * `sudo apt-get install cmake`
  * To build the documentation:
    * Install Sphinx:
      * `pip install sphinx`
    * Install Sphinx Read The Docs theme:
      * `pip install sphinx-rtd-theme` (read the docs theme is not installed by default)
    * Install spelling checker (optional)
      * `pip install pyenchant`
      * `pip install sphinxcontrib-spelling`
    * **Note:** Be sure to add Python scripts to PATH in order to build documentation from pre_build scripts.
  * C++20 compiler toolchain that supports `std::format` (GNU 13+, Clang 17+, etc.)

## Windows Build Information
The Windows projects each include a .rc file that embeds the VERSIONINFO resource into the final binary.

##### Prerequisites
 * Microsoft Visual Studio 2022 (17.13.5)
 * Within the Visual Studio Installer, the following workloads:
   * Desktop development with C++
 * Within the Visual Studio Installer, the following individual components:
   * Windows 11 SDK (10.0.22621.0)
   * MSVC v143 - VS 2022 C++ x64/x86 build tools (latest)
   * C++ CMake tools for Windows
   * C++ Clang Compiler for Windows (19.1.1)
   * .NET SDK
   * .NET 8.0 Runtime (Long Term Support)
   * C# and Visual Basic
   * C# and Visual Basic Roslyn compilers

## Linux Build Information

##### Prerequisites
 * Install the Mesa common development package:
   * `sudo apt-get install mesa-common-dev`

#### Instructions (pre_build.py)

GPA utilizes a python script pre_build.py to help users configure/setup the CMake build.
```sh
python build/pre_build.py --help
```

Additional switches that can be used with the pre_build.py script:
--vs=[2022]: Specify the Visual Studio version for which to generate projects. Default is 2022.
--config=[Debug,Release]: Specify the config for which to generate makefiles. Default is both. A specific config can only be specified on Linux. On Windows, both configs are always supported by the generated VS solution and project files.
--clean: Delete cmake-generated directories created by this script
--skipdx11: Does not generate build files for DX11 version of GPA (Windows only)
--skipdx12: Does not generate build files for DX12 version of GPA (Windows only)
--skipvulkan: Does not generate build files for Vulkan version of GPA
--skipopengl: Does not generate build files for OpenGL version of GPA
--skiptests: Does not generate build files for unit tests
--skipdocs: Does not generate build files for documentation
--skipexamples: Does not generate build files for GPA examples
--cmakecmd="CMD": Override the "cmake" command with "CMD"
--runtests="all": Run all tests

By default the project will not build the generated CMake project (Although you can with `--build`).

On Windows

* Load build\win\vs2022_x64\GPUPerfAPI-x64.sln into Visual Studio to build the 64-bit version of GPA.
* After a successful build, the GPUPerfAPI binaries can be found in gpu_performance_api\build\output\(configuration) (e.g. gpu_performance_api\build\output\debug_x64).

You can use CMake to open the solution from the command line:
```sh
cmake --open build/win/vs2022_x64/
```

On Linux

* Execute `make` in the build/linux/make_debug_x64 to build the 64-bit debug version of GPA.
* Execute `make` in the build/linux/make_release_x64 to build the 64-bit release version of GPA.
* After a successful build, the GPUPerfAPI binaries can be found in gpu_performance_api/build/output/$(Configuration) (e.g. gpu_performance_api/build/output/debug_x64).

#### Instructions (CMake)

You can also use CMake directly:

On Windows

Assuming you use `Visual Studio` which is the default `generator` on Windows

```sh
cmake -S . -B build/win/
cmake --build build/win/ --config Debug
```

On Linux

Assuming you use `Unix Makefiles` which is the default `generator` on Linux

```sh
cmake -S . -B build/linux -D CMAKE_BUILD_TYPE=Debug
cmake --build build/linux
```

NOTES:
- You may want to configure with `-Dskipdocs=ON` if you don't want to add python scripts to your PATH.
- You may want to configure with `-Dskipcsharp=ON` if you don't want to download C# development tools.
- CMake 3.30+ brings drastic performance improvements to FetchContent highly recommended for developers.

## PublicCounterCompiler Tool

NOTE: The PublicCounterCompiler Tool requires using the `Visual Studio` generator due to `C#` usage!

The PublicCounterCompiler Tool is a C# CLI utility that generates C++ code to define the public (or derived) counters.
It reads counter definition files from [source/codegen](source/codegen) and outputs files to
[source/auto_generated/gpu_perf_api_counter_generator](source/auto_generated/gpu_perf_api_counter_generator),
[source/auto_generated/gpu_perf_api_unit_tests/counters](source/auto_generated/gpu_perf_api_unit_tests/counters),
and [documentation/sphinx/source](documentation/sphinx/source).

```sh
# Generate the C++ code
PublicCounterCompiler

# Get command line options for more granular control
PublicCounterCompiler --help
```

See the `public_counter_definitions_*.txt` files in [source/codegen](source/codegen). These contain all the counter definitions.
Each counter is given a name, a description, a type, an optional usage type, a list of hardware counters required and a formula applied to the values of the hardware counters to calculate the value of the counter.

Counter formulas are expressed in a Reverse Polish Notation and are made up the following elements:
* numbers: Zero-based counter indexes referring to individual counters within the list of hardware counters
* math operators: Supported operators are +, -, /, *
* numeric literals: Numbers contained within parentheses are numeric literals (as opposed to counter indexes)
* functions: Supported functions are: min, max, sum, ifnotzero, and vcomparemax4. "max and "sum" have variants that work on multiple items at once (i.e. sum16, sum64, etc.)
* hardware params: Supported hardware params are "num_shader_engines", "num_simds", "su_clock_prim", "num_prim_pipes", and "TS_FREQ"
* **Note:** Hardware counters may also be referred to by name (e.g.: GPUTime_Bottom_To_Bottom) or templated name (e.g.: SPI*_SPI_PERF_CSG_BUSY) which will automatically refer to the correct number of instances.

For more details, see the "EvaluateExpression" function in the [gpa_derived_counter.cc](source/gpu_perf_api_counter_generator/gpa_derived_counter.cc) file.
