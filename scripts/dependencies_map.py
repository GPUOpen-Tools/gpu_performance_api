# Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
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
    "adl"              : ["external/Lib/AMD/ADL",               "da98d7a9d2b8a6222d32c82952ee44bdfc827b2e"],
    "appsdk"           : ["external/Lib/AMD/APPSDK",            "55a6940ebc963daec69152314a1bb94943287d4c"],
    "opengl"           : ["external/Lib/Ext/OpenGL",            "792c2291a4443ebef17ca5a7e3e24a1f854f0d1d"],
    "windows_kits"     : ["external/Lib/Ext/Windows-Kits",      "51845a3771122a9dc1406b8617e9a67d9a2f55b6"],
    "googletest"       : ["external/Lib/Ext/GoogleTest",        "542e057c6c5bf45454b43764b881397b71164d62"],
# Src.
    "adl_util"                 : ["external/Src/ADLUtil",               "d62c94514326775c83fc129bb89d299c8749ebd1"],
    "device_info"              : ["external/Src/DeviceInfo",            "8c2adcc8136dab662a58e93ead3027ee68e318c6"],
    "dynamic_library_module"   : ["external/Src/DynamicLibraryModule",  "e6451ce26b8509cf724c7cf5d007878791143a58"],
    "tsingleton"               : ["external/Src/TSingleton",            "02e8fa7d98f33cdbd0e1f77d1a8a403a32e35882"],
}

# Name : Source , Destination, version, Copied/Installation location wrt to Script root
downloadWin = {
    "GPADX11GetDeviceInfo" : [ "https://github.com/GPUOpen-Tools/gpu_performance_api/releases/download/v3.13/GPUPerfAPI-3.13.0.28.zip" , "default", "3_13", "external/Lib/AMD/GPUPerfAPI"]
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
