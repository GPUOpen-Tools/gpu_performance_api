#! /usr/bin/python
#
# Simple script to update a set of common directories that are needed as dependencies of the GPUPerfAPI
# Usage:
#   UpdateCommon.py [latest]
#
# If "latest" is specified, the latest commit will be checked out.
# Otherwise, the repos will be updated to the commit specified in the "gitMapping" table.
# If the required commit in the "gitMapping" is None, the repo will be updated to the latest commit.

import argparse
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
import zipfile

PYTHON_MAJOR_VER=sys.version_info.major
MACHINE_OS = ""
VULKAN_LIB_FILENAME = ""
VULKAN_LIB_PATH = "/lib/"
VULKAN_HEADER_FILE_PATH = "/include/vulkan/vulkan.h"
if "windows" in platform.system().lower():
    MACHINE_OS = "Windows"
    VULKAN_LIB_FILENAME = "vulkan-1.lib"
elif "linux" in platform.system().lower():
    MACHINE_OS = "Linux"
    VULKAN_LIB_FILENAME = "libvulkan.so"
else:
    print("Operating system not recognized correctly")
    sys.exit(1)

if PYTHON_MAJOR_VER == 3:
    import urllib.request

# to allow the script to be run from anywhere - not just the cwd - store the absolute path to the script file
scriptRoot = os.path.dirname(os.path.realpath(__file__))

# When running this script on Windows (and not under cygwin), we need to set the Shell=True argument to Popen and similar calls
# Without this option, Jenkins builds fail to find the correct version of git
SHELLARG = False
# The environment variable SHELL is only set for Cygwin or Linux
SHELLTYPE = os.environ.get('SHELL')
if ( SHELLTYPE == None ):
    # running on windows under default shell
    SHELLARG = True

# Print the version of git being used. This also confirms that the script can find git
try:
     subprocess.call(["git","--version"], shell=SHELLARG)
except OSError:
    # likely to be due to inability to find git command
    print("Error calling command: git --version")

# Defined an absolute URL to GPUOpen-Tools on github
ghAmdRoot = "https://github.com/GPUOpen-Tools/"

# GPUPerfAPI git project to folder map definitions
# - gitMapping
from UpdateCommonMap import *

# specify whether or not to download the Vulkan SDK (default is to download it)
parser = argparse.ArgumentParser(description='UpdateCommon args')
parser.add_argument('--skipvulkansdk', action='store_true', default=False, help='Prevents script from checking for the Vulkan SDK')
parser.add_argument('--downloadvulkansdk', action='store_true', default=False, help='Tells script to install the Vulkan SDK, regardless if one is already installed')
args = parser.parse_args()

# to allow the script to be run from anywhere - not just the cwd - store the absolute path to the script file
scriptRoot = os.path.dirname(os.path.realpath(__file__))

# for each dependency - test if it has already been fetched - if not, then fetch it, otherwise update it to top of tree
for key in gitMapping:
    # convert targetPath to OS specific format
    # add script directory to targetPath
    tmppath = os.path.join(scriptRoot, "..", gitMapping[key][0])
    # clean up targetPath, collapsing any ../ and converting / to \ for Windows
    targetPath = os.path.normpath(tmppath)

    reqdCommit = gitMapping[key][1]
    # reqdCommit may be "None" - or user may override commit via command line. In this case, use tip of tree
    if((len(sys.argv) != 1 and sys.argv[1] == "latest") or reqdCommit is None):
        reqdCommit = "master"

    print("\nChecking out commit: " + reqdCommit + " for " + key)

    if os.path.isdir(targetPath):
        # directory exists - get latest from git using pull
        print("Directory " + targetPath + " exists. \n\tUsing 'git pull' to get latest")
        sys.stdout.flush()
        try:
            subprocess.check_call(["git", "-C", targetPath, "pull", "origin"], shell=SHELLARG)
        except subprocess.CalledProcessError as e:
            print ("'git pull' failed with returncode: %d\n" % e.returncode)
            sys.exit(1)
        sys.stdout.flush()

        try:
            subprocess.check_call(["git", "-C", targetPath, "checkout", reqdCommit], shell=SHELLARG)
        except subprocess.CalledProcessError as e:
            print ("'git checkout' failed with returncode: %d\n" % e.returncode)
            sys.exit(1)
        sys.stderr.flush()
        sys.stdout.flush()
    else:
        # directory doesn't exist - clone from git
        ghRepoSource = ghAmdRoot + key

        print("Directory " + targetPath + " does not exist. \n\tUsing 'git clone' to get from " + ghRepoSource)
        sys.stdout.flush()
        try:
            subprocess.check_call(["git", "-C", scriptRoot, "clone", ghRepoSource, targetPath, "--branch", reqdCommit], shell=SHELLARG)
        except subprocess.CalledProcessError as e:
            print("'git clone' failed with returncode: %d\n" % e.returncode)
            sys.exit(1)
        sys.stderr.flush()
        sys.stdout.flush()

def download(srcPath, destPath, FileName):
    # Assuming path is absolute
    if False == os.path.isabs(destPath):
        print("Destination path is not valid")
        return False

    # clean up path, collapsing any ../ and converting / to \ for Windows
    destPath = os.path.normpath(destPath)

    if False == os.path.isdir(destPath):
        os.makedirs(destPath)

    targetPath = os.path.join(destPath, FileName)
    print("Downloading " + FileName + " to " + destPath)

    if PYTHON_MAJOR_VER < 3:
        urllib.urlretrieve(srcPath, targetPath)
    else:
        urllib.request.urlretrieve(srcPath, targetPath)

    if (os.path.isfile(targetPath)):
        print("File Downloaded Successfully")
        return True
    else:
        print("Unable to download file")
        return False

def HandleVulkan(vulkanSrc, VulkanDest, vulkanInstallerFileName, version, installationPath):
    VULKAN_SDK = os.environ.get("VULKAN_SDK")

    if True == args.skipvulkansdk:
        if VULKAN_SDK is None:
            print("Please make sure the VULKAN_SDK env var is set to a valid Vulkan SDK installation, or use the --downloadvulkansdk or --skipvulkansdk option.")
        return

    VulkanSDKFile = vulkanInstallerFileName
    if "Linux" == MACHINE_OS:
        LINUX_HOME=os.environ.get("HOME")
        DEST_PATH=LINUX_HOME
        if ("default" != installationPath):
            if (not os.path.isdir(installationPath)):
                os.makedirs(installationPath)
        else:
            installationPath = LINUX_HOME
    else:
        TEMP_DIR=os.environ.get("TEMP")
        if TEMP_DIR is None:
            DEST_PATH=scriptRoot
        else:
            DEST_PATH=TEMP_DIR
        installationPath = scriptRoot

    VulkanSDKInstaller = os.path.join(DEST_PATH, VulkanSDKFile)

    if VulkanDest != "default":
        DEST_PATH = VulkanDest

    os.chdir(installationPath)

    if False == args.downloadvulkansdk:
        if "Windows" == MACHINE_OS:
            if VULKAN_SDK is not None:
                if (os.path.isfile(VULKAN_SDK + VULKAN_LIB_PATH + VULKAN_LIB_FILENAME)) and (os.path.isfile(VULKAN_SDK + VULKAN_HEADER_FILE_PATH)):
                    print("The Vulkan SDK is already installed")
                    return
        if "Linux" == MACHINE_OS:
            installRootPath = os.path.join(installationPath, "VulkanSDK", version, "x86_64")
            if (os.path.isfile(installRootPath + VULKAN_LIB_PATH + VULKAN_LIB_FILENAME)) and (os.path.isfile(installRootPath + VULKAN_HEADER_FILE_PATH)):
                print("The Vulkan SDK is already installed")
                return

    vulkanSrc = vulkanSrc + "?Human=true"
    if (download(vulkanSrc, DEST_PATH, VulkanSDKFile)):
        st = os.stat(VulkanSDKInstaller)
        os.chmod(VulkanSDKInstaller, st.st_mode | stat.S_IEXEC)
        print("Starting VulkanSDK installer. Please follow the instructions...")
        print(VulkanSDKInstaller)

        installVulkanSDKProcess = subprocess.Popen([VulkanSDKInstaller], shell = True)
        installVulkanSDKProcess.wait()

        if "Windows" == MACHINE_OS:
            # Check if VULKAN_SDK environment variable is set
            VulkanSDKInstalledPath = os.environ.get("VULKAN_SDK")
            if (VulkanSDKInstalledPath is None):
                print("The VULKAN_SDK environment variable is not set. This means that either the installation failed or you might need to restart the command shell in which you are running to refresh the environment variables.")
            else:
                if (os.path.isfile(VulkanSDKInstalledPath + VULKAN_LIB_PATH + VULKAN_LIB_FILENAME)) and (os.path.isfile(VulkanSDKInstalledPath + VULKAN_HEADER_FILE_PATH)):
                    print("The Vulkan SDK has been installed")
        if "Linux" == MACHINE_OS:
            installRootPath = os.path.join(installationPath, "VulkanSDK", version, "x86_64")
            if (os.path.isfile(installRootPath + VULKAN_LIB_PATH + VULKAN_LIB_FILENAME)) and (os.path.isfile(installRootPath + VULKAN_HEADER_FILE_PATH)):
                print("The Vulkan SDK has been installed")

        os.remove(VulkanSDKInstaller)
        os.chdir(scriptRoot)
        return

def HandleGpaDx11GetDeviceInfo(src, dest, fileName, version, copyDest):
    TEMP_DIR=os.environ.get("TEMP")
    if TEMP_DIR is None:
        DEST_PATH=scriptRoot
    else:
        DEST_PATH=TEMP_DIR
        GpaDx11GetDeviceInfoArchiveFileName = fileName
        GpaDx11GetDeviceInfoArchiveAbsPath = os.path.join(DEST_PATH, GpaDx11GetDeviceInfoArchiveFileName)

    if dest != "default":
        DEST_PATH = dest

    copyArchive = os.path.join(scriptRoot, "..", copyDest)
    # clean up targetPath, collapsing any ../ and converting / to \ for Windows
    copyArchive = os.path.normpath(copyArchive)
    dx11DeviceInfoPlatform64File="3_0/Bin/x64/GPUPerfAPIDXGetAMDDeviceInfo-x64.dll"
    dx11DeviceInfoPlatformFile="3_0/Bin/x86/GPUPerfAPIDXGetAMDDeviceInfo.dll"
    dx11DeviceInfoPlatform64FileAbsPath = os.path.join(copyArchive, dx11DeviceInfoPlatform64File)
    dx11DeviceInfoPlatformFileAbsPath = os.path.join(copyArchive, dx11DeviceInfoPlatformFile)

    if(os.path.isfile(dx11DeviceInfoPlatform64FileAbsPath) & os.path.isfile(dx11DeviceInfoPlatformFileAbsPath)):
        print("The DXGetAMDDeviceInfo libraries already exist")
        return

    if(download(src, DEST_PATH, GpaDx11GetDeviceInfoArchiveFileName)):
        print("GPAGetDeviceInfo version " + version + " downloaded successfully")
        dx11getDeviceInfoArchive = zipfile.ZipFile(GpaDx11GetDeviceInfoArchiveAbsPath)
        dx11getDeviceInfoArchive.extract(dx11DeviceInfoPlatform64File, copyArchive)
        dx11getDeviceInfoArchive.extract(dx11DeviceInfoPlatformFile, copyArchive)
        dx11getDeviceInfoArchive.close()
        os.remove(GpaDx11GetDeviceInfoArchiveAbsPath)

        if(os.path.isfile(dx11DeviceInfoPlatform64FileAbsPath) & os.path.isfile(dx11DeviceInfoPlatformFileAbsPath)):
            print("The DXGetAMDDeviceInfo libraries have been copied successfully")
            return
        print("The DXGetAMDDeviceInfo libraries were unable to be copied")
        return
    else:
        print("Unable to download the GPUPerfAPI archive")
        return

if "Linux" == MACHINE_OS:
    for key in downloadLinux:
        keyList = downloadLinux[key]
        if key == "Vulkan":
            FileName = str(keyList[0]).rpartition("/")[2]
            HandleVulkan(keyList[0], keyList[1], FileName, keyList[2], keyList[3])

else:
    for key in downloadWin:
        keyList = downloadWin[key]
        FileName = str(keyList[0]).rpartition("/")[2]
        if key == "Vulkan":
            HandleVulkan(keyList[0], keyList[1], FileName, keyList[2], keyList[3])

        if key == "GPADX11GetDeviceInfo":
            HandleGpaDx11GetDeviceInfo(keyList[0], keyList[1], FileName, keyList[2], keyList[3])


