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
args = PreBuildCMakeCommon.DefineCMakeArguments()

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

if args.internal == True:
    internalBuild=True
else:
    internalBuild=False

CMakeAdditionalArgs = PreBuildCMakeCommon.ParseCMakeArguments(args)
print(PreBuildCMakeCommon.CMakeGenerator)
if sys.platform == "win32":
    for platform in PreBuildCMakeCommon.CMakeGeneratorUsePlatforms:
        if PreBuildCMakeCommon.GenerateProjectFileUsingCMake(PreBuildCMakeCommon.CMakeGenerator[platform], platform, "debug", CMakeAdditionalArgs, PreBuildScriptRoot, firstClean, internalBuild) == False:
            print("Unable to generate project files")
else:
    for platform in PreBuildCMakeCommon.CMakeGeneratorUsePlatforms:
        for config in PreBuildCMakeCommon.CMakeGeneratorConfigs:
            if  PreBuildCMakeCommon.GenerateProjectFileUsingCMake(PreBuildCMakeCommon.CMakeGenerator[platform], platform, config, CMakeAdditionalArgs, PreBuildScriptRoot, firstClean, internalBuild) == False:
                print("Unable to generate project files")









