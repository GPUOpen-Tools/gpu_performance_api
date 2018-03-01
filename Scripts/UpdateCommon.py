#! /usr/bin/python
#
# Simple script to clone or update a set of common directories that are needed as dependencies of the GPUPerfAPI.
# This script should be run after cloning the GPA repository.

import ctypes
import os
import platform
import shutil
import stat
import string
import subprocess
import sys
import time
import urllib

MACHINE_OS = ""
if "windows" in platform.system().lower():
    MACHINE_OS = "Windows"
elif "linux" in platform.system().lower():
    MACHINE_OS = "Linux"
else:
    print("Operating system not recognized correctly")
    sys.exit(1)

SHELLTYPE = os.environ.get('SHELL')
# SHELL only set for Cygwin or Linux, use "shell=False" in Popen calls
SHELLARG = False
if ( SHELLTYPE == None ):
    # on Windows, set "shell=True"
    SHELLARG = True

# GPUPerfAPI git project to folder map definitions
# - GitHubMapping
from UpdateCommonMap import *
if MACHINE_OS == "Linux":
    from UpdateCommonMap import downloadAndInstallMappingLin as downloadAndInstallMapping
else:
    from UpdateCommonMap import downloadAndInstallMappingWin as downloadAndInstallMapping

# to allow the script to be run from anywhere - not just the cwd - store the absolute path to the script file
scriptRoot = os.path.dirname(os.path.realpath(__file__))

# for each GitHub dependency - test if it has already been fetched - if not, then fetch it,
# otherwise update it to top of tree

for key in GitHubMapping:
    # convert targetPath to OS specific format
    tmppath = os.path.join(scriptRoot, "..", GitHubMapping[key][0])
    # clean up path, collapsing any ../ and converting / to \ for Windows
    targetPath = os.path.normpath(tmppath)
    if os.path.isdir(targetPath):
        print("\nDirectory " + targetPath + " exists, using 'git pull' to get latest")
        p = subprocess.Popen(["git","pull"], cwd=targetPath, shell=SHELLARG)
        p.wait();
    else:
        print("\nDirectory " + targetPath + " does not exist, using 'git clone' to get latest")
        gitamdRoot = "https://github.com/GPUOpen-Tools/" + key
        commandArgs = ["git", "clone", gitamdRoot, targetPath]
        p = subprocess.Popen(commandArgs, shell=SHELLARG)
        p.wait()
        p = subprocess.Popen(["git","reset","--hard",GitHubMapping[key][1]], cwd=targetPath, shell=SHELLARG)
        p.wait()

# Downloads and runs an installer for a Common Dir (just used for VulkanSDK currently)
# key is the URL to download the installer
# value[0] is the Common directory in which to "install" the files
# value[1] is the source from which to copye files (only used on Windows, currently)
# value[2] is the destination in which to copy files  (only used on Windows, currently)
def download_and_run(key, value):
    # convert targetPath to OS specific format
    tmppath = os.path.join(scriptRoot, "..", value[0])
    # clean up path, collapsing any ../ and converting / to \ for Windows
    targetPath = os.path.normpath(tmppath)
    if False == os.path.isdir(targetPath):
        os.makedirs(targetPath)
    sdkFileName = key.split('/')[-1].split('#')[0].split('?')[0]
    sdkInstallerPath = os.path.join(targetPath, sdkFileName)
    if MACHINE_OS == "Linux":
        if False == os.path.isfile(sdkInstallerPath):
            print("\nDownloading " + key + " into " + sdkInstallerPath)
            urllib.urlretrieve(key, sdkInstallerPath)
            sdkFileName = "./" + sdkFileName
            print("\nExecuting " + sdkFileName + " with cwd=" + targetPath)
            os.chdir(targetPath)
            st = os.stat(sdkFileName)
            os.chmod(sdkFileName, st.st_mode | stat.S_IEXEC)
            p = subprocess.Popen([sdkFileName], cwd=targetPath)
            p.wait()
    else:
        if False == os.path.isdir(value[1]):
            # did not find the SDK installed, so we need to download and install it
            if False == os.path.isfile(sdkInstallerPath):
                print("\nDownloading " + key + " into " + sdkInstallerPath)
                urllib.urlretrieve(key, sdkInstallerPath)
            print("\nExecuting " + sdkInstallerPath)
            p = subprocess.Popen([sdkInstallerPath, "/S"], shell=True)
            p.wait()
        dstDir = os.path.join(scriptRoot, "..", value[2])
        if False == os.path.isdir(dstDir):
            print("\nCopying " + value[1] + " to " + dstDir)
            shutil.copytree(value[1], dstDir)

for key in downloadAndInstallMapping:
    download_and_run(key, downloadAndInstallMapping[key])
