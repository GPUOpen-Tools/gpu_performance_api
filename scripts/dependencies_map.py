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
    "adl"              : ["external/Lib/AMD/ADL",               None],
    "appsdk"           : ["external/Lib/AMD/APPSDK",            None],
    "opengl"           : ["external/Lib/Ext/OpenGL",            None],
    "windows_kits"     : ["external/Lib/Ext/Windows-Kits",      None],
    "googletest"       : ["external/Lib/Ext/GoogleTest",        "v1.8.x"],
# Src.
    "adl_util"                 : ["external/Src/ADLUtil",               None],
    "device_info"              : ["external/Src/DeviceInfo",            None],
    "dynamic_library_module"   : ["external/Src/DynamicLibraryModule",  None],
    "tsingleton"               : ["external/Src/TSingleton",            None],
}

# Name : Source , Destination, version, Copied/Installation location wrt to Script root
downloadWin = {
    "GPADX11GetDeviceInfo" : [ "https://github.com/GPUOpen-Tools/gpu_performance_api/releases/download/v3.10/GPUPerfAPI-3.10.0.77.zip" , "default", "3_10", "external/Lib/AMD/GPUPerfAPI"]
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
