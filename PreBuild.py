## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
#! /usr/bin/python
# Utility Python Script to generate GPA projects on Windows and Linux

import os
import sys
import argparse
import subprocess
import PreBuildCMakeCommon

# script root
PreBuildScriptRoot = os.path.dirname(os.path.realpath(__file__))
PreBuildCMakeCommon.DefineCMakeArguments()
args = PreBuildCMakeCommon.ScriptParser.parse_args()

if args.nofetch == False:
    # Run CMake - Generate projects
    FetchDependenciesScript = os.path.join(PreBuildScriptRoot, "Scripts", "UpdateCommon.py")
    FetchDependenciesScript = os.path.normpath(FetchDependenciesScript)
    FetchDependenciesArgs = ["python", FetchDependenciesScript]
    FetchDependencies = subprocess.Popen(FetchDependenciesArgs)
    FetchDependencies.wait()
    sys.stdout.flush()
    sys.stderr.flush()
    if(FetchDependencies.returncode != 0):
        print("ERROR: Unable to fetch all dependencies %d"%FetchDependencies.returncode)
        sys.exit(-1)

if args.clean == True:
    firstClean = True
else:
    firstClean = False

buildDirName = "CMakeBuild"

if args.android == True:
    buildDirName = "CMakeBuild-Android"

CMakeAdditionalArgs = PreBuildCMakeCommon.ParseCMakeArguments(args)

if args.android == True:
    PreBuildCMakeCommon.CMakeGeneratorUsePlatforms.remove('x86')
    android_ndk=os.environ["ANDROID_NDK"]
    if android_ndk == "":
        print("Android environment variable is not defined. Exiting.")
        exit(1)
    CMakeAdditionalArgs.append("-DBUILD_ANDROID=ON")
    CMakeAdditionalArgs.append("-DANDROID_ABI=x86_64")
    CMakeAdditionalArgs.append("-DANDROID_PLATFORM=24")
    CMakeAdditionalArgs.append("-DANDROID_NATIVE_API_LEVEL=24")
    CMakeAdditionalArgs.append("-DANDROID_STL=c++_static")
    CMakeAdditionalArgs.append("-Dskipopengl=ON")
    CMakeAdditionalArgs.append("-Dskipopencl=ON")
    CMakeAdditionalArgs.append("-Dskiptests=ON")
    CMakeAdditionalArgs.append("-Dskipdocs=ON")
    CMakeAdditionalArgs.append("-Dbuild-32bit=OFF")

print(PreBuildCMakeCommon.CMakeGenerator)
if sys.platform == "win32":
    for platform in PreBuildCMakeCommon.CMakeGeneratorUsePlatforms:
        if PreBuildCMakeCommon.GenerateProjectFileUsingCMake(PreBuildCMakeCommon.CMakeGenerator[platform], platform, "debug", CMakeAdditionalArgs, PreBuildScriptRoot, firstClean, buildDirName) == False:
            print("Unable to generate project files")
else:
    for platform in PreBuildCMakeCommon.CMakeGeneratorUsePlatforms:
        for config in PreBuildCMakeCommon.CMakeGeneratorConfigs:
            if  PreBuildCMakeCommon.GenerateProjectFileUsingCMake(PreBuildCMakeCommon.CMakeGenerator[platform], platform, config, CMakeAdditionalArgs, PreBuildScriptRoot, firstClean, buildDirName) == False:
                print("Unable to generate project files")









