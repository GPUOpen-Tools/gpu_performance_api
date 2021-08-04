#!/usr/bin/python
# Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
# Utility Python Script to generate GPA projects on Windows and Linux

import os
import sys
import shutil
import subprocess
import argparse

# Specify the type of Build files to generate
cmake_generator=None
cmake_generator_platforms = ["x86", "x64"]
cmake_generator_configs = ["debug", "release"]
cmake_vs2015_generators = {'x86':'Visual Studio 14 2015', 'x64':'Visual Studio 14 2015 Win64'}
cmake_vs2017_generators = {'x86':'Visual Studio 15 2017', 'x64':'Visual Studio 15 2017 Win64'}
cmake_vs2019_generators = {'x86':'Visual Studio 16 2019', 'x64':'Visual Studio 16 2019'}
cmake_make_file_generators = {'x86':'Unix Makefiles', 'x64':'Unix Makefiles'}
cmake_cmd = "cmake"
verbosity_enabled=False

def log(var):
    if verbosity_enabled==True:
        print(var)

def generate_project_file_using_cmake(cmake_generator, target_platform,
                                      project_config, additional_cmake_args,
                                      cmake_list_dir, clean, build_file_dir):
    # Store the previous working directory
    current_working_dir = os.getcwd()
    log("Current Directory is " + current_working_dir)

    cmake_build_file_dir = "CMakeBuild"

    if build_file_dir is not None:
        cmake_build_file_dir = build_file_dir

    if sys.platform == "win32":
        cmake_build_file_dir = os.path.join(cmake_list_dir, cmake_build_file_dir, target_platform)
    else:
        cmake_build_file_dir = os.path.join(cmake_list_dir, cmake_build_file_dir, target_platform, project_config)

    cmake_build_file_dir = os.path.normpath(cmake_build_file_dir)

    if clean == True:
        shutil.rmtree(cmake_build_file_dir, ignore_errors=True)
        log("Deleting directory " + cmake_build_file_dir)

    # Create Diretories if it doesn't exist
    if False == os.path.isdir(cmake_build_file_dir):
        os.makedirs(cmake_build_file_dir)
        log("Creating creating " + cmake_build_file_dir)

    # Change directory to CMake Build dir
    os.chdir(cmake_build_file_dir)
    log("Changing directory to " + cmake_build_file_dir)

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
        print(args)

    if cmake_generator == "Visual Studio 16 2019":
        cmake_arguments = [cmake_cmd, "-G", cmake_generator, "-A", architecture,"-Dusingscript=ON", cmake_config_arg, cmake_platform_arg]
    else:
        cmake_arguments = [cmake_cmd, "-G", cmake_generator, "-Dusingscript=ON", cmake_config_arg, cmake_platform_arg]


    for args in additional_cmake_args:
        cmake_arguments.append(args)

    cmake_arguments.append(cmake_list_dir)
    log("cmake" + cmake_list_dir)

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

def define_cmake_arguments():
    # parse the command line arguments
    script_parser = argparse.ArgumentParser(description="Utility script to generate GPA Unix/Windows projects")
    if sys.platform == "win32":
        script_parser.add_argument("--vs", default="2017", choices=["2015", "2017", "2019"], help="specify the version of Visual Studio to be used with this script (default: 2017)")

    script_parser.add_argument("--config", choices=["debug", "release"], help="specify the build config for Makefiles (default: both)")
    script_parser.add_argument("--platform", choices=["x86", "x64"], help="specify the platform for the project has to be generated (default: both)" )
    script_parser.add_argument("--clean", action="store_true", help="delete any directories created by this script")
    script_parser.add_argument("--build", action="store", help="GPA Build number")

    if sys.platform == "win32":
        script_parser.add_argument("--skipdx11", action="store_true", help="skip DX11 from the CMake generated project")
        script_parser.add_argument("--skipdx12", action="store_true", help="skip DX12 from the CMake generated project")

    script_parser.add_argument("--skipvulkan", action="store_true", help="skip Vulkan from the CMake generated project")
    script_parser.add_argument("--skipopengl", action="store_true", help="skip OpenGL from the CMake generated project")
    script_parser.add_argument("--skipopencl", action="store_true", help="skip OpenCL from the CMake generated project")
    script_parser.add_argument("--skiptests", action="store_true", help="skip Tests from the CMake generated project")
    script_parser.add_argument("--skipsamples", action="store_true", help="skip Samples from the CMake generated project")
    script_parser.add_argument("--skipdocs", action="store_true", help="skip Docs from the CMake generated project")
    script_parser.add_argument("--nofetch", action="store_true", help="skip fetching repo dependencies")
    script_parser.add_argument("--cmakecmd", type=str, default="cmake", help="command to use in place of 'cmake'")
    script_parser.add_argument("--verbose", action="store_true", help="Turns on the verbosity of the script'")
    script_parser.add_argument("--android", action="store_true", help="CMake will generate project files for android")
    return script_parser

def parse_cmake_arguments(cmake_arguments):

    cmake_additional_args=[""]

    if cmake_arguments.verbose == True:
        cmake_additional_args.append("-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON")

    if sys.platform == "win32":
        if cmake_arguments.skipdx11 == True:
            cmake_additional_args.append("-Dskipdx11=ON")
        else:
            cmake_additional_args.append("-Dskipdx11=OFF")

        if cmake_arguments.skipdx12 == True:
            cmake_additional_args.append("-Dskipdx12=ON")
        else:
            cmake_additional_args.append("-Dskipdx12=OFF")

    if cmake_arguments.skipvulkan == True:
        cmake_additional_args.append("-Dskipvulkan=ON")
    else:
        cmake_additional_args.append("-Dskipvulkan=OFF")

    if cmake_arguments.skipopengl == True:
        cmake_additional_args.append("-Dskipopengl=ON")
    else:
        cmake_additional_args.append("-Dskipopengl=OFF")

    if cmake_arguments.skipopencl == True:
        cmake_additional_args.append("-Dskipopencl=ON")
    else:
        cmake_additional_args.append("-Dskipopencl=OFF")

    if cmake_arguments.skiptests == True:
        cmake_additional_args.append("-Dskiptests=ON")
    else:
        cmake_additional_args.append("-Dskiptests=OFF")

    if cmake_arguments.skipsamples == True:
        cmake_additional_args.append("-Dskipsamples=ON")
    else:
        cmake_additional_args.append("-Dskipsamples=OFF")

    if cmake_arguments.skipdocs == True:
        cmake_additional_args.append("-Dskipdocs=ON")
    else:
        cmake_additional_args.append("-Dskipdocs=OFF")


    ## If platform or config is not provided we will generate projects for both platforms and their both configs
    global cmake_generator_platforms
    if cmake_arguments.platform == 'x86':
        cmake_generator_platforms.remove('x64')

    if cmake_arguments.platform == 'x64':
        cmake_generator_platforms.remove('x86')

    global cmake_generator_configs
    if cmake_arguments.config == "debug":
        cmake_generator_configs.remove("release")

    if cmake_arguments.config == "release":
        cmake_generator_configs.remove("debug")

    if sys.platform == "win32":
        global cmake_generator
        if cmake_arguments.vs == "2015":
            cmake_generator = cmake_vs2015_generators
        elif cmake_arguments.vs == "2019":
            cmake_generator = cmake_vs2019_generators
        else:
            cmake_generator = cmake_vs2017_generators
    else:
        cmake_generator = cmake_make_file_generators

    global cmake_cmd
    cmake_cmd = cmake_arguments.cmakecmd

    global verbosity_enabled
    verbosity_enabled=cmake_arguments.verbose

    return cmake_additional_args
