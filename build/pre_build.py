## Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.
#! /usr/bin/python
# Utility Python script to generate GPA projects on Windows and Linux

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

# Specify the type of build files to generate
cmake_generator = None
cmake_generator_configs = ["debug", "release"]
cmake_vs2015_generator = 'Visual Studio 14 2015 Win64'
cmake_vs2017_generator = 'Visual Studio 15 2017 Win64'
cmake_vs2019_generator = 'Visual Studio 16 2019'
cmake_vs2022_generator = 'Visual Studio 17 2022'
cmake_make_file_generator = 'Unix Makefiles'
cmake_ninja_file_generator = 'Ninja'

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

    # Create directories if they don't exist
    if False == os.path.isdir(cmake_build_file_dir):
        os.makedirs(cmake_build_file_dir)
        Log("Creating creating " + cmake_build_file_dir)

    # Change directory to CMake Build dir
    os.chdir(cmake_build_file_dir)
    Log("Changing directory to " + cmake_build_file_dir)

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
script_parser.add_argument("--clean", action="store_true", help="Delete cmake-generated directories created by this script")
script_parser.add_argument("--build-number", default="0", help="Specify the build number, primarily to be used by build machines to produce versioned builds")
script_parser.add_argument("--build", action="store_true", help="Perform the GPA build after running CMake")
script_parser.add_argument("--builddir", action="store", help="Directory where the cmake files will be generated and the build will be performed; if not given as an absolute path then this will be relative to the top-level pre_build script")
script_parser.add_argument("--build-jobs", default="8", help="number of simultaneous jobs to run during a build (default = 8)")
script_parser.add_argument("--package", action="store_true", help="Generate GPA packages")
script_parser.add_argument("--package-suffix", action="store", help="Suffix to append to the generated GPA packages")


if sys.platform == "win32":
    script_parser.add_argument("--skipdx11", action="store_true", help="Skip DX11 from the CMake generated project")
    script_parser.add_argument("--skipdx12", action="store_true", help="Skip DX12 from the CMake generated project")

script_parser.add_argument("--skipvulkan", action="store_true", help="Skip Vulkan from the CMake generated project")
script_parser.add_argument("--skipopengl", action="store_true", help="Skip OpenGL from the CMake generated project")
script_parser.add_argument("--skiptests", action="store_true", help="Skip Tests from the CMake generated project")
script_parser.add_argument("--skipexamples", action="store_true", help="Skip examples from the CMake generated project")
script_parser.add_argument("--skipdocs", action="store_true", help="Skip Docs from the CMake generated project")
script_parser.add_argument("--skipcsharp", action="store_true", help="Skip C#-based projects from the CMake generation")
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

if build_args.skiptests == True:
    cmake_additional_args.append("-Dskiptests=ON")
else:
    cmake_additional_args.append("-Dskiptests=OFF")

if build_args.skipexamples == True:
    cmake_additional_args.append("-Dskipexamples=ON")
else:
    cmake_additional_args.append("-Dskipexamples=OFF")

if build_args.skipdocs == True:
    cmake_additional_args.append("-Dskipdocs=ON")
else:
    cmake_additional_args.append("-Dskipdocs=OFF")

if build_args.skipcsharp == True:
    cmake_additional_args.append("-Dskipcsharp=ON")
else:
    cmake_additional_args.append("-Dskipcsharp=OFF")

if build_args.config == "debug":
    cmake_generator_configs.remove("release")

if build_args.config == "release":
    cmake_generator_configs.remove("debug")

if sys.platform == "win32":
    if build_args.vs == "2015":
        cmake_generator = cmake_vs2015_generator
    if build_args.vs == "2017":
        cmake_generator = cmake_vs2017_generator
    elif build_args.vs == "2019":
        cmake_generator = cmake_vs2019_generator
    elif build_args.vs == "2022":
        cmake_generator = cmake_vs2022_generator
    elif build_args.ninja:
        cmake_generator = cmake_ninja_file_generator
    else:
        cmake_generator = cmake_vs2019_generator
else:
    if build_args.ninja:
        cmake_generator = cmake_ninja_file_generator
    else:
        cmake_generator = cmake_make_file_generator

cmake_cmd = build_args.cmakecmd

verbosity_enabled = build_args.verbose

if build_args.android == True:
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
cmake_additional_args.append("-Dbuild=" + build_args.build_number)

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
    cmake_generator_configs = ["release"]

cmake_build_configs = ["debug", "release"]

print("configs: %s" % cmake_generator_configs)

for config in cmake_generator_configs:

    platform = 'x64'

    if build_args.builddir != None:
        cmake_output_path = build_args.builddir
    else:
        if sys.platform == "win32":
            cmake_output_path = os.path.join(pre_bld_script_root, "win", "vs" + build_args.vs)
        else:
            cmake_output_path = os.path.join(pre_bld_script_root, "linux", "make_" + config)

        cmake_output_path = cmake_output_path + "_x64"

        # Append _android to output dir if building for android
        if build_args.android == True:
            cmake_output_path = cmake_output_path + "_android"


    if GenerateProjectFileUsingCmake(cmake_generator, platform,
                                        config, cmake_additional_args, cmakelists_root,
                                        build_args.clean, cmake_output_path) == False:
        print("Unable to generate project files")
        sys.exit(1)

if (build_args.build):
    config_suffix = "_x64"
    if build_args.android == True:
        config_suffix = config_suffix + "_android"

    for config in cmake_build_configs:
        print( "\nBuilding " + config + " configuration\n")
        build_dir = ""

        cmake_output_dir = pre_bld_script_root
        if build_args.builddir != None:
            cmake_output_dir = build_args.builddir

        if sys.platform == "win32":
            cmake_output_dir = os.path.join(cmake_output_dir, "win", "vs" + build_args.vs + config_suffix)
        else:
            cmake_output_dir = os.path.join(cmake_output_dir, "linux", "make_" + config + config_suffix)

        if build_args.ninja or sys.platform != "win32":
            cmake_args = ["cmake", "--build", cmake_output_dir, "--parallel", build_args.build_jobs]

        elif sys.platform == "win32":
            # For Visual Studio, specify the config to build
            cmake_args = ["cmake", "--build", cmake_output_dir, "--config", config, "--target", "ALL_BUILD", "--",  "/m:" + build_args.build_jobs, "/p:nodeReuse=false"]

        p = subprocess.Popen(cmake_args, cwd=cmake_output_dir, stderr=subprocess.STDOUT)
        p.wait()
        sys.stdout.flush()

        if(p.returncode != 0):
            print("\nERROR: CMake build failed with %d" % p.returncode)
            sys.exit(1)

if (build_args.package):
    packaging_args = [sys.executable, os.path.join(pre_bld_script_root, "gpa_packaging.py"), "--build-number=" + build_args.build_number]
    if (build_args.android == True):
        packaging_args.append("--android")
    if (build_args.package_suffix is not None):
        packaging_args.append("--suffix=" + build_args.package_suffix)

    p = subprocess.Popen(packaging_args, stderr=subprocess.STDOUT)
    p.wait()
    sys.stdout.flush()

    if(p.returncode != 0):
        print("\nERROR: GPA packaging script failed with %d" % p.returncode)
        sys.exit(1)


minutes, seconds = divmod(time.time() - start_time, 60)
print("Successfully completed in {0:.0f} minutes, {1:.1f} seconds".format(minutes,seconds))
sys.exit(0)
