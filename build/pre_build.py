## Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
#! /usr/bin/python
# Utility Python Script to generate GPA projects on Windows and Linux

import os
import sys
import shutil
import argparse
import subprocess
import time

import gpa_utils as GpaUtils

# Prevent script from leaving a compiled .pyc file in the directory.
sys.dont_write_bytecode = True

# Remember the start time.
start_time = time.time()

pre_bld_script_root = os.path.dirname(os.path.realpath(__file__))
gpa_root = os.path.normpath(os.path.join(pre_bld_script_root, ".."))
cmakelists_root = gpa_root
fetch_dependencies_script = os.path.join(pre_bld_script_root, "fetch_dependencies.py")
sys.path.append(gpa_root)

# Specify the type of Build files to generate.
cmake_generator = None
cmake_generator_platforms = ["x86", "x64"]
cmake_generator_configs = ["debug", "release"]
cmake_vs2015_generators = {'x86':'Visual Studio 14 2015', 'x64':'Visual Studio 14 2015 Win64'}
cmake_vs2017_generators = {'x86':'Visual Studio 15 2017', 'x64':'Visual Studio 15 2017 Win64'}
cmake_vs2019_generators = {'x86':'Visual Studio 16 2019', 'x64':'Visual Studio 16 2019'}
cmake_vs2022_generators = {'x86':'Visual Studio 17 2022', 'x64':'Visual Studio 17 2022'}
cmake_make_file_generators = {'x86':'Unix Makefiles', 'x64':'Unix Makefiles'}
cmake_ninja_file_generators = {'x86':'Ninja', 'x64':'Ninja'}

cmake_cmd = "cmake"

verbosity_enabled = False

def Log(var):
    if verbosity_enabled == True:
        print(var, flush=True)

def GenerateProjectFileUsingCmake(cmake_generator, target_platform,
                                  project_config, additional_cmake_args,
                                  cmake_list_dir, clean, build_file_dir):
    print("")

    # Store the previous working directory
    current_working_dir = os.getcwd()
    Log("Current Directory is " + current_working_dir)

    cmake_build_file_dir = "CMakeBuild"

    if build_file_dir is not None:
        cmake_build_file_dir = build_file_dir

    print("INFO: Build output directory is: " + cmake_build_file_dir)

    if not os.path.isabs(cmake_build_file_dir):
        if sys.platform == "win32" and cmake_generator != "Ninja":
            cmake_build_file_dir = os.path.join(cmake_list_dir, cmake_build_file_dir, target_platform)
        else:
            cmake_build_file_dir = os.path.join(cmake_list_dir, cmake_build_file_dir, target_platform, project_config)

    cmake_build_file_dir = os.path.normpath(cmake_build_file_dir)

    if clean == True:
        shutil.rmtree(cmake_build_file_dir, ignore_errors=True)
        Log("Deleting directory " + cmake_build_file_dir)

    # Create Diretories if it doesn't exist
    if False == os.path.isdir(cmake_build_file_dir):
        os.makedirs(cmake_build_file_dir)
        Log("Creating creating " + cmake_build_file_dir)

    # Change directory to CMake Build dir
    os.chdir(cmake_build_file_dir)
    Log("Changing directory to " + cmake_build_file_dir)

    if target_platform == "x86":
        cmake_platform_arg = "-Dbuild-32bit=ON"
        architecture = "Win32"
    else:
        cmake_platform_arg = "-Dbuild-32bit=OFF"
        architecture = "x64"

    if project_config == "debug":
        cmake_config_arg = "-Dbuild-debug=ON"
    else:
        cmake_config_arg = "-Dbuild-debug=OFF"

    print("Running CMake with arguments:")
    for args in additional_cmake_args:
        print(args, flush=True)

    if cmake_generator == "Visual Studio 16 2019" or cmake_generator == "Visual Studio 17 2022":
        cmake_arguments = [cmake_cmd, "-G", cmake_generator, "-A", architecture,"-Dusingscript=ON", cmake_config_arg, cmake_platform_arg]
    else:
        cmake_arguments = [cmake_cmd, "-G", cmake_generator, "-Dusingscript=ON", cmake_config_arg, cmake_platform_arg]


    for args in additional_cmake_args:
        cmake_arguments.append(args)

    cmake_arguments.append(cmake_list_dir)
    Log("cmake " + cmake_list_dir)

    # Run CMake - Generate projects
    if sys.platform == "win32":
        cmake_process = subprocess.Popen(cmake_arguments, shell = True)
    else:
        cmake_process = subprocess.Popen(cmake_arguments)

    cmake_process.wait()
    sys.stdout.flush()
    sys.stderr.flush()
    os.chdir(current_working_dir)
    if(cmake_process.returncode != 0):
        print("ERROR: cmake failed with %d"%cmake_process.returncode)
        return False

    return True



script_parser = argparse.ArgumentParser(description="Utility script to generate GPA Unix/Windows projects")
if sys.platform == "win32":
    script_parser.add_argument("--vs", default="2022", choices=["2015", "2017", "2019", "2022"], help="specify the version of Visual Studio to be used with this script (default: 2022; overrides --ninja)")

script_parser.add_argument("--ninja", action="store_true", help="Generate build files for the Ninja build system")
script_parser.add_argument("--config", choices=["debug", "release"], help="Specify the build config for Makefiles (default: both)")
script_parser.add_argument("--platform", choices=["x86", "x64"], help="Specify the platform for the project has to be generated (default: both)" )
script_parser.add_argument("--clean", action="store_true", help="Delete cmake-generated directories created by this script")
script_parser.add_argument("--build", action="store", help="GPA Build number")
script_parser.add_argument("--builddir", action="store", help="Directory where the cmake files will be generated and the build will be performed; if not given as an absolute path then this will be relative to the top-level pre_build script")

if sys.platform == "win32":
    script_parser.add_argument("--skipdx11", action="store_true", help="Skip DX11 from the CMake generated project")
    script_parser.add_argument("--skipdx12", action="store_true", help="Skip DX12 from the CMake generated project")

script_parser.add_argument("--skipvulkan", action="store_true", help="Skip Vulkan from the CMake generated project")
script_parser.add_argument("--skipopengl", action="store_true", help="Skip OpenGL from the CMake generated project")
script_parser.add_argument("--skipopencl", action="store_true", help="Skip OpenCL from the CMake generated project")
script_parser.add_argument("--skiptests", action="store_true", help="Skip Tests from the CMake generated project")
script_parser.add_argument("--skipsamples", action="store_true", help="Skip Samples from the CMake generated project")
script_parser.add_argument("--skipdocs", action="store_true", help="Skip Docs from the CMake generated project")
script_parser.add_argument("--nofetch", action="store_true", help="Skip fetching repo dependencies")

script_parser.add_argument("--cmakecmd", type=str, default="cmake", help="Command to use in place of 'cmake'")
script_parser.add_argument("--verbose", action="store_true", help="Turns on the verbosity of the script'")
script_parser.add_argument("--android", action="store_true", help="CMake will generate project files for android")

script_parser.add_argument("--clang_format", action="store_true", help="Run clang-format on source files prior to performing a build")
script_parser.add_argument("--clang_tidy", action="store_true", help="Run clang-tidy on source files after a build completes")
script_parser.add_argument("--fixlint", action="store_true", help="Apply fixes suggested by clang-format and/or clang-tidy directly to source files")
script_parser.add_argument("--cleanlint", action="store_true", help="Fail and stop a build if clang-format and/or clang-tidy suggests a fix")


# parse the command line arguments
build_args = script_parser.parse_args()


if build_args.nofetch == False:
    fetch_dependencies_script = os.path.normpath(fetch_dependencies_script)
    fetch_dependencies_args = [sys.executable, fetch_dependencies_script]


    fetch_dependencies_process = subprocess.Popen(fetch_dependencies_args)
    fetch_dependencies_process.wait()
    sys.stdout.flush()
    sys.stderr.flush()
    if(fetch_dependencies_process.returncode != 0):
        print("ERROR: Unable to fetch all dependencies (return code: %d)"%fetch_dependencies_process.returncode)
        sys.exit(1)

cmake_additional_args=[""]

if build_args.verbose == True:
    cmake_additional_args.append("-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON")

if sys.platform == "win32":
    if build_args.skipdx11 == True:
        cmake_additional_args.append("-Dskipdx11=ON")
    else:
        cmake_additional_args.append("-Dskipdx11=OFF")

    if build_args.skipdx12 == True:
        cmake_additional_args.append("-Dskipdx12=ON")
    else:
        cmake_additional_args.append("-Dskipdx12=OFF")

if build_args.skipvulkan == True:
    cmake_additional_args.append("-Dskipvulkan=ON")
else:
    cmake_additional_args.append("-Dskipvulkan=OFF")

if build_args.skipopengl == True:
    cmake_additional_args.append("-Dskipopengl=ON")
else:
    cmake_additional_args.append("-Dskipopengl=OFF")

if build_args.skipopencl == True:
    cmake_additional_args.append("-Dskipopencl=ON")
else:
    cmake_additional_args.append("-Dskipopencl=OFF")

if build_args.skiptests == True:
    cmake_additional_args.append("-Dskiptests=ON")
else:
    cmake_additional_args.append("-Dskiptests=OFF")

if build_args.skipsamples == True:
    cmake_additional_args.append("-Dskipsamples=ON")
else:
    cmake_additional_args.append("-Dskipsamples=OFF")

if build_args.skipdocs == True:
    cmake_additional_args.append("-Dskipdocs=ON")
else:
    cmake_additional_args.append("-Dskipdocs=OFF")


## If platform or config is not provided we will generate projects for both platforms and their both configs
if build_args.platform == 'x86':
    cmake_generator_platforms.remove('x64')

if build_args.platform == 'x64':
    cmake_generator_platforms.remove('x86')

if build_args.config == "debug":
    cmake_generator_configs.remove("release")

if build_args.config == "release":
    cmake_generator_configs.remove("debug")

if sys.platform == "win32":
    if build_args.vs == "2015":
        cmake_generator = cmake_vs2015_generators
    if build_args.vs == "2017":
        cmake_generator = cmake_vs2017_generators
    elif build_args.vs == "2019":
        cmake_generator = cmake_vs2019_generators
    elif build_args.vs == "2022":
        cmake_generator = cmake_vs2022_generators
    elif build_args.ninja:
        cmake_generator = cmake_ninja_file_generators
    else:
        cmake_generator = cmake_vs2019_generators
else:
    if build_args.ninja:
        cmake_generator = cmake_ninja_file_generators
    else:
        cmake_generator = cmake_make_file_generators

cmake_cmd = build_args.cmakecmd

verbosity_enabled = build_args.verbose

if build_args.android == True:
    cmake_generator_platforms.remove('x86')
    android_ndk=os.environ["ANDROID_NDK"]
    if android_ndk == "":
        print("Android environment variable is not defined. Exiting.")
        exit(1)
    cmake_additional_args.append("-DBUILD_ANDROID=ON")
    cmake_additional_args.append("-DANDROID_ABI=x86_64")
    cmake_additional_args.append("-DANDROID_PLATFORM=24")
    cmake_additional_args.append("-DANDROID_NATIVE_API_LEVEL=24")
    cmake_additional_args.append("-DANDROID_STL=c++_static")
    cmake_additional_args.append("-Dskipopengl=ON")
    cmake_additional_args.append("-Dskipopencl=ON")
    cmake_additional_args.append("-Dskiptests=ON")
    cmake_additional_args.append("-Dbuild-32bit=OFF")

# Set the BUILD version number.
if build_args.build is not None:
    cmake_additional_args.append("-Dbuild=" + build_args.build)
else:
    cmake_additional_args.append("-Dbuild=0")

# Allow the build tool to emit a 'compile_commands.json' file for tools such as clang-tidy
# Ignored by generators other than Make and Ninja, so no harm in leaving it always on
cmake_additional_args.append("-DCMAKE_EXPORT_COMPILE_COMMANDS=ON")

if build_args.clang_format == True:
    cmake_additional_args.append("-DGPA_RUN_CLANG_FORMAT=ON")
else:
    cmake_additional_args.append("-DGPA_RUN_CLANG_FORMAT=OFF")

if build_args.clang_tidy == True:
    cmake_additional_args.append("-DGPA_RUN_CLANG_TIDY=ON")
else:
    cmake_additional_args.append("-DGPA_RUN_CLANG_TIDY=OFF")

if build_args.fixlint == True:
    cmake_additional_args.append("-DGPA_APPLY_LINT_FIXES=ON")
else:
    cmake_additional_args.append("-DGPA_APPLY_LINT_FIXES=OFF")

if build_args.cleanlint == True:
    cmake_additional_args.append("-DGPA_REQUIRE_CLEAN_LINT=ON")
else:
    cmake_additional_args.append("-DGPA_REQUIRE_CLEAN_LINT=OFF")


print(cmake_generator)

if sys.platform == "win32":
    cmake_generator_configs = ["debug"]

print("configs: %s" % cmake_generator_configs)

for platform in cmake_generator_platforms:
    for config in cmake_generator_configs:

        if build_args.builddir != None:
            cmake_output_path = build_args.builddir
        else:
            if sys.platform == "win32":
                cmake_output_path = os.path.join(pre_bld_script_root, "win", "vs" + build_args.vs)
            elif sys.platform == "darwin":
                cmake_output_path = os.path.join(pre_bld_script_root, "mac", "make_" + config)
            else:
                cmake_output_path = os.path.join(pre_bld_script_root, "linux", "make_" + config)

            if platform == "x64":
                cmake_output_path = cmake_output_path + "_x64"
            else:
                cmake_output_path = cmake_output_path + "_x86"

            # Append _android to output dir if building for android
            if build_args.android == True:
                cmake_output_path = cmake_output_path + "_android"


        if GenerateProjectFileUsingCmake(cmake_generator[platform], platform,
                                         config, cmake_additional_args, cmakelists_root,
                                         build_args.clean, cmake_output_path) == False:
            print("Unable to generate project files")
            sys.exit(1)

minutes, seconds = divmod(time.time() - start_time, 60)
print("Successfully completed in {0:.0f} minutes, {1:.1f} seconds".format(minutes,seconds))
sys.exit(0)
