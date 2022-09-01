## Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
#! /usr/bin/python
# Utility Python Script to generate GPA projects on Windows and Linux

import os
import sys
import argparse
import subprocess

pre_bld_script_root = os.path.dirname(os.path.realpath(__file__))
gpa_root = os.path.normpath(os.path.join(pre_bld_script_root, "../"))
sys.path.append(gpa_root)

import scripts.pre_build_common as PreBuildCMakeCommon

def pre_build(build_args):
    if build_args.nofetch == False:
        fetch_dependencies_script = os.path.join(gpa_root, "scripts", "fetch_dependencies.py")
        fetch_dependencies_script = os.path.normpath(fetch_dependencies_script)
        fetch_dependencies_args = [sys.executable, fetch_dependencies_script]
        fetch_dependencies_process = subprocess.Popen(fetch_dependencies_args)
        fetch_dependencies_process.wait()
        sys.stdout.flush()
        sys.stderr.flush()
        if(fetch_dependencies_process.returncode != 0):
            print("ERROR: Unable to fetch all dependencies %d"%fetch_dependencies_process.returncode)
            sys.exit(-1)

    if build_args.clean == True:
        first_clean = True
    else:
        first_clean = False

    build_dir_name = "cmake_bld"

    if build_args.android_x64 == True:
        build_dir_name = "cmake_bld_android_x64"
    elif build_args.android_arm64 == True:
        build_dir_name = "cmake_bld_android_arm64"

    cmake_additional_args = PreBuildCMakeCommon.parse_cmake_arguments(build_args)

    if build_args.build is not None:
        cmake_additional_args.append("-Dbuild=" + build_args.build)
    else:
        cmake_additional_args.append("-Dbuild=0")

    if build_args.android_x64 == True or build_args.android_arm64 == True:
        PreBuildCMakeCommon.cmake_generator_platforms.remove('x86')
        android_ndk=os.environ["ANDROID_NDK"]
        if android_ndk == "":
            print("Android environment variable is not defined. Exiting.")
            exit(1)
        cmake_additional_args.append("-DBUILD_ANDROID=ON")
        cmake_additional_args.append("-DANDROID_PLATFORM=24")
        cmake_additional_args.append("-DANDROID_NATIVE_API_LEVEL=24")
        cmake_additional_args.append("-DANDROID_STL=c++_static")
        cmake_additional_args.append("-Dskipopengl=ON")
        cmake_additional_args.append("-Dskipopencl=ON")
        cmake_additional_args.append("-Dskiptests=ON")
        cmake_additional_args.append("-Dbuild-32bit=OFF")

    if build_args.android_x64 == True:
        cmake_additional_args.append("-DANDROID_ABI=x86_64")
    elif build_args.android_arm64 == True:
        cmake_additional_args.append("-DANDROID_ABI=arm64-v8a")

    print(PreBuildCMakeCommon.cmake_generator)
    if sys.platform == "win32":
        for platform in PreBuildCMakeCommon.cmake_generator_platforms:
            if PreBuildCMakeCommon.generate_project_file_using_cmake(PreBuildCMakeCommon.cmake_generator[platform], platform,
                                                                     "debug", cmake_additional_args, gpa_root,
                                                                      first_clean, build_dir_name) == False:
                print("Unable to generate project files")
    else:
        for platform in PreBuildCMakeCommon.cmake_generator_platforms:
            for config in PreBuildCMakeCommon.cmake_generator_configs:
                if  PreBuildCMakeCommon.generate_project_file_using_cmake(PreBuildCMakeCommon.cmake_generator[platform], platform,
                                                                          config, cmake_additional_args, gpa_root,
                                                                          first_clean, build_dir_name) == False:
                    print("Unable to generate project files")


if __name__ == "__main__":
    # script root
    script_parser = PreBuildCMakeCommon.define_cmake_arguments()
    build_args = script_parser.parse_args()
    pre_build(build_args)
