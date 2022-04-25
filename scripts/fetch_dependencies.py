#! /usr/bin/python3
# Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
#
# Simple script to update a set of common directories that are needed as dependencies of the GPUPerfAPI
# Usage:
#   fetch_dependencies.py [latest]
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
import zipfile
import gpa_utils as GpaUtils
import dependencies_map as DependencyMap

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

# to allow the script to be run from anywhere - not just the cwd - store the absolute path to the script file
scriptRoot = os.path.dirname(os.path.realpath(__file__))

# When running this script on Windows (and not under cygwin), we need to set the Shell=True argument to Popen and similar calls
# Without this option, Jenkins builds fail to find the correct version of git
SHELLARG = False
# The environment variable SHELL is only set for Cygwin or Linux
SHELLTYPE = os.environ.get('SHELL')
if SHELLTYPE is None:
    # running on windows under default shell
    SHELLARG = True

# Print the version of git being used. This also confirms that the script can find git
try:
     subprocess.call(["git","--version"], shell=SHELLARG)
except OSError:
    # likely to be due to inability to find git command
    print("Error calling command: git --version")

parser = argparse.ArgumentParser(description='fetch_dependencies args')
parser.add_argument('--showrevisions', action='store_true', default=False, help='Show git revisions of HEAD in dependent repo')
parser.add_argument('--gitserver', help='Git Server')
parser.add_argument('--usebranch', action='store', help='Branch to use when cloning dependencies instead of the script default branch.')

# To allow the script to be run from anywhere - not just the cwd - store the absolute path to the script file.
scriptRoot = os.path.dirname(os.path.realpath(__file__))
gpaRoot = os.path.normpath(os.path.join(scriptRoot, ".."))

# Wait up to a certain number of seconds for a file to become available for deletion, re-trying once a second.
# os.remove raises a PermissionError on Windows if the file is currently open elsewhere, and we rethrow this
# exception if our timeout expires. If the archive is deleted (i.e. by the other process that has the archive
# opened), the FileNotFoundError that would occur in that situation is suppressed.
def TryRemoveFile(filepath):
    max_wait_secs = 10
    for i in range(max_wait_secs):
        try:
            os.remove(filepath)
            break
        except PermissionError:
            time.sleep(1)
            if i == max_wait_secs - 1:
                print("Waited {} seconds but could not delete {}".format(max_wait_secs, filepath))
                raise
        except FileNotFoundError:
            break

# For each dependency - test if it has already been fetched - if not, then fetch it, otherwise update it to top of tree.
def UpdateGitHubRepo(repoRootUrl, location, commit):
    # Convert targetPath to OS specific format.
    # Add script directory to targetPath.
    targetPath = os.path.join(gpaRoot, location)

    reqdCommit = commit

    print("\nChecking out commit: %s for %s\n"%(reqdCommit, targetPath))

    if os.path.isdir(targetPath):
        # Directory exists - get latest from git using pull.
        print("Directory " + targetPath + " exists. \n\tUsing 'git pull' to get latest")
        sys.stdout.flush()
        try:
            subprocess.check_call(["git", "-C", targetPath, "pull", "origin"], shell=SHELLARG)
        except subprocess.CalledProcessError as e:
            print ("'git pull' failed with returncode: %d\n" % e.returncode)
            sys.exit(1)
        sys.stdout.flush()

        if reqdCommit is not None:
            GpaUtils.SwitchToBranchOrRef(targetPath, reqdCommit)
    else:
        # Directory doesn't exist - clone from git.
        ghRepoSource = repoRootUrl

        print("Directory " + targetPath + " does not exist. \n\tUsing 'git clone' to get from " + ghRepoSource)
        sys.stdout.flush()

        if not GpaUtils.CloneGitRepo(ghRepoSource, reqdCommit, targetPath):
            sys.exit(1)

def ShowRevisions():
    repos_revision_map={}

    for key in DependencyMap.gitMapping:
        local_git_repo_path = os.path.join(gpaRoot, DependencyMap.gitMapping[key][0])
        revision_str = GpaUtils.GetGitLocalRepoHead(local_git_repo_path)
        if revision_str is not None:
            repos_revision_map[key] = revision_str

    for repo in repos_revision_map:
        print ('{0:35}    :    {1}'.format(repo, repos_revision_map[repo]))

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
    if (GpaUtils.Download(vulkanSrc, DEST_PATH, VulkanSDKFile)):
        st = os.stat(VulkanSDKInstaller)
        os.chmod(VulkanSDKInstaller, st.st_mode | stat.S_IEXEC)
        print("Starting VulkanSDK installer. Please follow the instructions...")
        print(VulkanSDKInstaller)

        installVulkanSDKProcess = subprocess.Popen([VulkanSDKInstaller], shell = True)
        installVulkanSDKProcess.wait()

        if "Windows" == MACHINE_OS:
            # Check if VULKAN_SDK environment variable is set.
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

        TryRemoveFile(VulkanSDKInstaller)
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

    copyArchive = os.path.join(gpaRoot, copyDest)
    dx11DeviceInfoPlatform64File= version + "/Bin/x64/GPUPerfAPIDXGetAMDDeviceInfo-x64.dll"
    dx11DeviceInfoPlatformFile= version + "/Bin/x86/GPUPerfAPIDXGetAMDDeviceInfo.dll"
    dx11DeviceInfoPlatform64FileAbsPath = os.path.join(copyArchive, dx11DeviceInfoPlatform64File)
    dx11DeviceInfoPlatformFileAbsPath = os.path.join(copyArchive, dx11DeviceInfoPlatformFile)

    if(os.path.isfile(dx11DeviceInfoPlatform64FileAbsPath) & os.path.isfile(dx11DeviceInfoPlatformFileAbsPath)):
        print("The DXGetAMDDeviceInfo libraries already exist")
        return

    if(GpaUtils.Download(src, DEST_PATH, GpaDx11GetDeviceInfoArchiveFileName)):
        print("GPAGetDeviceInfo version " + version + " downloaded successfully")
        dx11getDeviceInfoArchive = zipfile.ZipFile(GpaDx11GetDeviceInfoArchiveAbsPath)
        dx11getDeviceInfoArchive.extract(dx11DeviceInfoPlatform64File, copyArchive)
        dx11getDeviceInfoArchive.extract(dx11DeviceInfoPlatformFile, copyArchive)
        dx11getDeviceInfoArchive.close()
        TryRemoveFile(GpaDx11GetDeviceInfoArchiveAbsPath)

        if(os.path.isfile(dx11DeviceInfoPlatform64FileAbsPath) & os.path.isfile(dx11DeviceInfoPlatformFileAbsPath)):
            print("The DXGetAMDDeviceInfo libraries have been copied successfully")
            return
        print("The DXGetAMDDeviceInfo libraries were unable to be copied")
        return
    else:
        print("Unable to download the GPUPerfAPI archive")
        return

if __name__ == "__main__":

    git_tools_remote_server = "https://github.com/GPUOpen-Tools/"

    args = parser.parse_args()

    if args.showrevisions:
        ShowRevisions()
        sys.exit(0)

    if args.gitserver is not None:
        git_tools_remote_server = args.gitserver

    for key in DependencyMap.gitMapping:
        default_branch = DependencyMap.gitMapping[key][1]
        if args.usebranch is not None:
            if key != "googletest":
                if GpaUtils.VerifyBranch((git_tools_remote_server + key), args.usebranch):
                    default_branch = args.usebranch
        UpdateGitHubRepo((git_tools_remote_server + key), DependencyMap.gitMapping[key][0], default_branch)

    if "Windows" == MACHINE_OS:
        for key in DependencyMap.downloadWin:
            keyList = DependencyMap.downloadWin[key]
            FileName = str(keyList[0]).rpartition("/")[2]

            if key == "GPADX11GetDeviceInfo":
                HandleGpaDx11GetDeviceInfo(keyList[0], keyList[1], FileName, keyList[2], keyList[3])
