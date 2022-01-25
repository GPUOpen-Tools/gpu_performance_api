# Copyright (c) 2018-2022 Advanced Micro Devices, Inc. All rights reserved.
# dependencies_map.py
#
#    Map of GitHub project names to clone target paths, relative to the GPUPerfAPI
#    project root on the local disk.
#    This script is used by the fetch_dependencies.py script

# GitHub GPUOpen-Tools projects map
# Define a set of dependencies that exist as separate git projects. The parameters are:
# "git repo name"  : ["Directory for clone relative to parent project directory",  "branch or commit to checkout (or None for top of tree)"]
gitMapping = {
 # Lib.
    "common-lib-amd-ADL"                  : ["../Common/Lib/AMD/ADL",               None],
    "common-lib-amd-APPSDK-3.0"           : ["../Common/Lib/AMD/APPSDK",            None],
    "common-lib-ext-OpenGL"               : ["../Common/Lib/Ext/OpenGL",            None],
    "common-lib-ext-WindowsKits"          : ["../Common/Lib/Ext/Windows-Kits",      None],
    "googletest"                          : ["../Common/Lib/Ext/GoogleTest",        "v1.8.x"],
# Src.
    "common-src-ADLUtil"                  : ["../Common/Src/ADLUtil",               None],
    "common-src-AmdDxExt"                 : ["../Common/Src/AmdDxExt",              None],
    "common-src-AmdVkExt"                 : ["../Common/Src/AmdVkExt",              None],
    "common-src-DeviceInfo"               : ["../Common/Src/DeviceInfo",            None],
    "common-src-DynamicLibraryModule"     : ["../Common/Src/DynamicLibraryModule",  None],
    "common-src-TSingleton"               : ["../Common/Src/TSingleton",            None],
    "common-src-CMakeModules"             : ["../Common/Src/CMakeModules",          None],
}

# Name : Source , Destination, version, Copied/Installation location wrt to Script root
downloadWin = {
    "GPADX11GetDeviceInfo" : [ "https://github.com/GPUOpen-Tools/gpu_performance_api/releases/download/v3.9/GPUPerfAPI-3.9.0.13.zip" , "default", "3_9", "../Common/Lib/AMD/GPUPerfAPI"]
}

# Name : Source , Destination, version, Copied/Installation location wrt to Script root
downloadLinux = {
}

def parse_args():
    import argparse
    parser = argparse.ArgumentParser(description='Print the GPA git project dependency to local folder mapping.')
    parser.add_argument('--project', '-p', action='store', default=None,
                        help='Return expected relative path for the specified project.')
    args = parser.parse_args()
    return args

def get_all_mapping(display, project=None):
    import os.path

    dependencies_map = []
    if display:
        if project != None:
            normed_path = os.path.normpath(gitMapping[project][0])
            print(normed_path)
        else:
            for git_repo in gitMapping:
                print("%s\t%s" % (git_repo, os.path.normpath(gitMapping[git_repo][0])))
                dependencies_map[git_repo] = gitMapping[git_repo][0]

    return dependencies_map

if __name__ == "__main__":
    script_args = parse_args()
    get_all_mapping(display=True, project=script_args.project)
