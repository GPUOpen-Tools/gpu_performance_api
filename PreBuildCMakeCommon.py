# Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
#! /usr/bin/python
# Utility Python Script to generate GPA projects on Windows and Linux

import os
import sys
import shutil
import subprocess
import argparse

# Specify the type of Build files to generate
CMakeGenerator=None
CMakeGeneratorUsePlatforms = ["x86", "x64"]
CMakeGeneratorConfigs = ["debug", "release"]
CMakeVS2015Generators = {'x86':'Visual Studio 14 2015', 'x64':'Visual Studio 14 2015 Win64'}
CMakeVS2017Generators = {'x86':'Visual Studio 15 2017', 'x64':'Visual Studio 15 2017 Win64'}
CMakeMakeFileGenerators = {'x86':'Unix Makefiles', 'x64':'Unix Makefiles'}
CMakeCmd = "cmake"
ScriptParser = argparse.ArgumentParser(description="Utility script to generate GPA Unix/Windows projects")
VerbosityEnable=False

def Log(var):
    if VerbosityEnable==True:
        print(var)


def GenerateProjectFileUsingCMake(Generator, Platform, Config, additionalArgs, CMakeListDir, clean, buildDirName):
    # Store the previous working directory
    currentCwd = os.getcwd()
    Log("Current Directory is " + currentCwd)

    if buildDirName is None:
        buildDirName="CMakeBuild"

    if sys.platform == "win32":
        buildDir = os.path.join(CMakeListDir, buildDirName, Platform)
    else:
        buildDir = os.path.join(CMakeListDir, buildDirName, Platform, Config)

    buildDir = os.path.normpath(buildDir)

    if clean == True:
        shutil.rmtree(buildDir, ignore_errors=True)
        Log("Deleting directory " + buildDir)

    # Create Diretories if it doesn't exist
    if False == os.path.isdir(buildDir):
        os.makedirs(buildDir)
        Log("Creating creating " + buildDir)

    # Change directory to CMake Build dir
    os.chdir(buildDir)
    Log("Changing directory to " + buildDir)

    if Platform == "x86":
        platformArg = "-Dbuild-32bit=ON"
    else:
        platformArg = "-Dbuild-32bit=OFF"

    if Config == "debug":
        configArg = "-Dbuild-debug=ON"
    else:
        configArg = "-Dbuild-debug=OFF"

    print("Running CMake with arguments:")
    for cmakearg in additionalArgs:
        print(cmakearg)

    CMakeArgs = [CMakeCmd, "-G", Generator, "-Dusingscript=ON", configArg, platformArg]

    for args in additionalArgs:
        CMakeArgs.append(args)

    CMakeArgs.append(CMakeListDir)
    Log("cmake" + CMakeListDir)

    # Run CMake - Generate projects
    if sys.platform == "win32":
        CMakeProcess = subprocess.Popen(CMakeArgs, shell = True)
    else:
        CMakeProcess = subprocess.Popen(CMakeArgs)

    CMakeProcess.wait()
    sys.stdout.flush()
    sys.stderr.flush()
    os.chdir(currentCwd)
    if(CMakeProcess.returncode != 0):
        print("ERROR: cmake failed with %d"%CMakeProcess.returncode)
        return False

    return True

def DefineCMakeArguments():
    # parse the command line arguments

    if sys.platform == "win32":
        ScriptParser.add_argument("--vs", default="2017", choices=["2015", "2017"], help="specify the version of Visual Studio to be used with this script (default: 2017)")

    ScriptParser.add_argument("--config", choices=["debug", "release"], help="specify the build config for Makefiles (default: both)")
    ScriptParser.add_argument("--platform", choices=["x86", "x64"], help="specify the platform for the project has to be generated (default: both)" )
    ScriptParser.add_argument("--clean", action="store_true", help="delete any directories created by this script")

    if sys.platform == "win32":
        ScriptParser.add_argument("--skipdx11", action="store_true", help="skip DX11 from the CMake generated project")
        ScriptParser.add_argument("--skipdx12", action="store_true", help="skip DX12 from the CMake generated project")

    ScriptParser.add_argument("--skipvulkan", action="store_true", help="skip Vulkan from the CMake generated project")
    ScriptParser.add_argument("--skipopengl", action="store_true", help="skip OpenGL from the CMake generated project")
    ScriptParser.add_argument("--skipopencl", action="store_true", help="skip OpenCL from the CMake generated project")
    ScriptParser.add_argument("--skiptests", action="store_true", help="skip Tests from the CMake generated project")
    ScriptParser.add_argument("--skipdocs", action="store_true", help="skip Docs from the CMake generated project")
    ScriptParser.add_argument("--nofetch", action="store_true", help="skip fetching repo dependencies")
    ScriptParser.add_argument("--cmakecmd", type=str, default="cmake", help="command to use in place of 'cmake'")
    ScriptParser.add_argument("--verbose", action="store_true", help="Turns on the verbosity of the script'")
    ScriptParser.add_argument("--android", action="store_true", help="CMake will generate project files for android")

def ParseCMakeArguments(cmakeParsedArgs):

    CMakeAdditionalArgs=[""]

    if sys.platform == "win32":
        if cmakeParsedArgs.skipdx11 == True:
            CMakeAdditionalArgs.append("-Dskipdx11=ON")
        else:
            CMakeAdditionalArgs.append("-Dskipdx11=OFF")

        if cmakeParsedArgs.skipdx12 == True:
            CMakeAdditionalArgs.append("-Dskipdx12=ON")
        else:
            CMakeAdditionalArgs.append("-Dskipdx12=OFF")

    if cmakeParsedArgs.skipvulkan == True:
        CMakeAdditionalArgs.append("-Dskipvulkan=ON")
    else:
        CMakeAdditionalArgs.append("-Dskipvulkan=OFF")

    if cmakeParsedArgs.skipopengl == True:
        CMakeAdditionalArgs.append("-Dskipopengl=ON")
    else:
        CMakeAdditionalArgs.append("-Dskipopengl=OFF")

    if cmakeParsedArgs.skipopencl == True:
        CMakeAdditionalArgs.append("-Dskipopencl=ON")
    else:
        CMakeAdditionalArgs.append("-Dskipopencl=OFF")

    if cmakeParsedArgs.skiptests == True:
        CMakeAdditionalArgs.append("-Dskiptests=ON")
    else:
        CMakeAdditionalArgs.append("-Dskiptests=OFF")

    if cmakeParsedArgs.skipdocs == True:
        CMakeAdditionalArgs.append("-Dskipdocs=ON")
    else:
        CMakeAdditionalArgs.append("-Dskipdocs=OFF")


    ## If platform or config is not provided we will generate projects for both platforms and their both configs
    global CMakeGeneratorUsePlatforms
    if cmakeParsedArgs.platform == 'x86':
        CMakeGeneratorUsePlatforms.remove('x64')

    if cmakeParsedArgs.platform == 'x64':
        CMakeGeneratorUsePlatforms.remove('x86')

    global CMakeGeneratorConfigs
    if cmakeParsedArgs.config == "debug":
        CMakeGeneratorConfigs.remove("release")

    if cmakeParsedArgs.config == "release":
        CMakeGeneratorConfigs.remove("debug")

    if sys.platform == "win32":
        global CMakeGenerator
        if cmakeParsedArgs.vs == "2015":
            CMakeGenerator = CMakeVS2015Generators
        else:
            CMakeGenerator = CMakeVS2017Generators
    else:
        CMakeGenerator = CMakeMakeFileGenerators

    global CMakeCmd
    CMakeCmd = cmakeParsedArgs.cmakecmd

    global VerbosityEnable
    VerbosityEnable=cmakeParsedArgs.verbose

    return CMakeAdditionalArgs