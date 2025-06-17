## Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.
#! /usr/bin/python
# Utility Python script to generate GPA projects on Windows and Linux

import os
import sys
import shutil
import argparse
import subprocess
import time
import stat

import gpa_utils as GpaUtils

def remove_readonly(func, path, _):
    "Clear the readonly bit and reattempt the removal"
    os.chmod(path, stat.S_IWRITE)
    func(path)

# Prevent script from leaving a compiled .pyc file in the directory.
sys.dont_write_bytecode = True

# Remember the start time.
start_time = time.time()

pre_bld_script_root = os.path.dirname(os.path.realpath(__file__))
gpa_root = os.path.normpath(os.path.join(pre_bld_script_root, ".."))
android_toolchain = os.path.join(gpa_root, "build", "cmake_modules", "android.cmake")
fetch_dependencies_script = os.path.join(gpa_root, "build", "cmake_modules", "fetch_dependencies.cmake")
cmakelists_root = gpa_root
sys.path.append(gpa_root)

# Specify the type of build files to generate
cmake_generator = None
cmake_generator_configs = ["debug", "release"]
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
                                  clean, build_file_dir):
    cmake_arguments = [cmake_cmd, "--version"]
    if sys.platform == "win32":
        cmake_process = subprocess.Popen(cmake_arguments, shell = True)
    else:
        cmake_process = subprocess.Popen(cmake_arguments)

    cmake_process.wait()
    if(cmake_process.returncode != 0):
        print("ERROR: cmake --version failed!")
        return False

    cmake_build_file_dir = "CMakeBuild"

    if build_file_dir is not None:
        cmake_build_file_dir = build_file_dir

    if not os.path.isabs(cmake_build_file_dir):
        if sys.platform == "win32" and cmake_generator != "Ninja":
            cmake_build_file_dir = os.path.join(cmakelists_root, cmake_build_file_dir, target_platform)
        else:
            cmake_build_file_dir = os.path.join(cmakelists_root, cmake_build_file_dir, target_platform, project_config)

    cmake_build_file_dir = os.path.normpath(cmake_build_file_dir)

    print("INFO: Build output directory is: " + cmake_build_file_dir)

    if clean == True:
        # NOTE in python 3.12 onerror is deprecated
        # This should eventually be updated to onexc
        #
        # ignore_errors=True helps handle the case where cmake_build_file_dir doesn't exist yet.
        shutil.rmtree(cmake_build_file_dir, onerror=remove_readonly, ignore_errors=True)
        Log("Deleting directory " + cmake_build_file_dir)

    if project_config == "debug":
        cmake_config_arg = "-Dbuild-debug=ON"
    else:
        cmake_config_arg = "-Dbuild-debug=OFF"

    print("Running CMake with arguments:")
    for args in additional_cmake_args:
        print(args, flush=True)

    cmake_arguments = [cmake_cmd, "-S", cmakelists_root, "-B", cmake_build_file_dir]
    cmake_arguments += ["-G", cmake_generator, "-Dusingscript=ON", cmake_config_arg]

    for args in additional_cmake_args:
        cmake_arguments.append(args)

    # Run CMake - Generate projects
    if sys.platform == "win32":
        cmake_process = subprocess.Popen(cmake_arguments, shell = True)
    else:
        cmake_process = subprocess.Popen(cmake_arguments)

    cmake_process.wait()
    sys.stdout.flush()
    sys.stderr.flush()
    if(cmake_process.returncode != 0):
        print("ERROR: cmake failed with %d"%cmake_process.returncode)
        return False

    return True



script_parser = argparse.ArgumentParser(description="Utility script to generate GPA Unix/Windows projects")
if sys.platform == "win32":
    script_parser.add_argument("--vs", default="2022", choices=["2022"], help="specify the version of Visual Studio to be used with this script (default: 2022; overrides --ninja)")

script_parser.add_argument("--ninja", action="store_true", help="Generate build files for the Ninja build system")
script_parser.add_argument("--config", choices=["debug", "release"], help="Specify the build config for Makefiles (default: both)")
script_parser.add_argument("--clean", action="store_true", help="Delete cmake-generated directories created by this script")
script_parser.add_argument("--build-number", default="0", help="Specify the build number, primarily to be used by build machines to produce versioned builds")
script_parser.add_argument("--build", action="store_true", help="Perform the GPA build after running CMake")
script_parser.add_argument("--builddir", action="store", help="Directory where the cmake files will be generated and the build will be performed; if not given as an absolute path then this will be relative to the top-level pre_build script")
script_parser.add_argument("--build-jobs", default="8", help="number of simultaneous jobs to run during a build (default = 8)")
script_parser.add_argument("--package", action="store_true", help="Generate GPA packages")
script_parser.add_argument("--package-suffix", action="store", help="Suffix to append to the generated GPA packages")
script_parser.add_argument("--nofetch", action="store_true", help="Avoids CMake build using FetchContent")

if sys.platform == "win32":
    script_parser.add_argument("--skipdx11", action="store_true", help="Skip DX11 from the CMake generated project")
    script_parser.add_argument("--skipdx12", action="store_true", help="Skip DX12 from the CMake generated project")

script_parser.add_argument("--skipvulkan", action="store_true", help="Skip Vulkan from the CMake generated project")
script_parser.add_argument("--skipopengl", action="store_true", help="Skip OpenGL from the CMake generated project")
script_parser.add_argument("--skiptests", action="store_true", help="Skip Tests from the CMake generated project")
script_parser.add_argument("--skipexamples", action="store_true", help="Skip examples from the CMake generated project")
script_parser.add_argument("--skipdocs", action="store_true", help="Skip Docs from the CMake generated project")
script_parser.add_argument("--skipcsharp", action="store_true", help="Skip C#-based projects from the CMake generation")

script_parser.add_argument("--cmakecmd", type=str, default="cmake", help="Command to use in place of 'cmake'")
script_parser.add_argument("--verbose", action="store_true", help="Turns on the verbosity of the script'")
script_parser.add_argument("--android", action="store_true", help="CMake will generate project files for android")

script_parser.add_argument("--clang_format", action="store_true", help="Run clang-format on source files prior to performing a build")
script_parser.add_argument("--clang_tidy", action="store_true", help="Run clang-tidy on source files after a build completes")
script_parser.add_argument("--fixlint", action="store_true", help="Apply fixes suggested by clang-format and/or clang-tidy directly to source files")
script_parser.add_argument("--cleanlint", action="store_true", help="Fail and stop a build if clang-format and/or clang-tidy suggests a fix")


# parse the command line arguments
build_args = script_parser.parse_args()


# Set the BUILD version number.
cmake_additional_args=["-Dbuild=" + build_args.build_number]

if build_args.verbose == True:
    cmake_additional_args.append("-DCMAKE_VERBOSE_MAKEFILE=ON")
    # Helps provide useful information during FetchContent.
    cmake_additional_args.append("--log-level=DEBUG")

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

if build_args.package_suffix is not None:
    cmake_additional_args.append("-DGPA_PACKAGE_SUFFIX=" + build_args.package_suffix)
else:
    cmake_additional_args.append("-UGPA_PACKAGE_SUFFIX")

if build_args.config == "debug":
    cmake_generator_configs.remove("release")

if build_args.config == "release":
    cmake_generator_configs.remove("debug")

if sys.platform == "win32":
    if build_args.vs == "2022":
        cmake_generator = cmake_vs2022_generator
    elif build_args.ninja:
        cmake_generator = cmake_ninja_file_generator
    else:
        cmake_generator = cmake_vs2022_generator
else:
    if build_args.ninja:
        cmake_generator = cmake_ninja_file_generator
    else:
        cmake_generator = cmake_make_file_generator

cmake_cmd = build_args.cmakecmd

verbosity_enabled = build_args.verbose

if build_args.android == True:
    cmake_additional_args.append("-DCMAKE_TOOLCHAIN_FILE=" + android_toolchain)
    cmake_additional_args.append("-Dskipopengl=ON")
    cmake_additional_args.append("-Dskiptests=ON")

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

if build_args.nofetch == True:
    cmake_additional_args.append("-DGPA_NO_FETCH=ON")
else:
    cmake_additional_args.append("-DGPA_NO_FETCH=OFF")


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
                                        config, cmake_additional_args,
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
            # NOTE: -nodeReuse:false helps with sporadic build failures.
            cmake_args = ["cmake", "--build", cmake_output_dir, "--config", config, "--", f"-maxCpuCount:{build_args.build_jobs}", "-nodeReuse:false"]

        p = subprocess.Popen(cmake_args, cwd=cmake_output_dir, stderr=subprocess.STDOUT)
        p.wait()
        sys.stdout.flush()

        if(p.returncode != 0):
            print("\nERROR: CMake build failed with %d" % p.returncode)
            sys.exit(1)
        
        # We currently only package release binaries.
        if (build_args.package and config == "release"):

            cpack_args = ["cpack", "-C", "Release"]
            p = subprocess.Popen(cpack_args, cwd=cmake_output_dir, stderr=subprocess.STDOUT)
            p.wait()
            sys.stdout.flush()

            if(p.returncode != 0):
                print("\nERROR: CPack failed with %d" % p.returncode)
                sys.exit(1)

minutes, seconds = divmod(time.time() - start_time, 60)
print("Successfully completed in {0:.0f} minutes, {1:.1f} seconds".format(minutes,seconds))
sys.exit(0)
