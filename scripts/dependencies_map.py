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
    "common-lib-amd-ADL"                  : ["../Common/Lib/AMD/ADL",               "da98d7a9d2b8a6222d32c82952ee44bdfc827b2e"],
    "common-lib-amd-APPSDK-3.0"           : ["../Common/Lib/AMD/APPSDK",            "55a6940ebc963daec69152314a1bb94943287d4c"],
    "common-lib-ext-OpenGL"               : ["../Common/Lib/Ext/OpenGL",            "63cd62c8b25e165b0e6f3307b998ed0cf3810edf"],
    "common-lib-ext-WindowsKits"          : ["../Common/Lib/Ext/Windows-Kits",      "2c99b88d6a8a9b672464436dad771b9799056a8a"],
    "googletest"                          : ["../Common/Lib/Ext/GoogleTest",        "542e057c6c5bf45454b43764b881397b71164d62"],
# Src.
    "common-src-ADLUtil"                  : ["../Common/Src/ADLUtil",               "d62c94514326775c83fc129bb89d299c8749ebd1"],
    "common-src-AmdDxExt"                 : ["../Common/Src/AmdDxExt",              "9e79ce1ca673ad977328d0f32a58c2c885efa67f"],
    "common-src-AmdVkExt"                 : ["../Common/Src/AmdVkExt",              "3488d03b7f3bf59c4f41e3f5056801daec5aaa9d"],
    "common-src-DeviceInfo"               : ["../Common/Src/DeviceInfo",            "d834984dc3702f01180d168ad84843b31e88b86b"],
    "common-src-DynamicLibraryModule"     : ["../Common/Src/DynamicLibraryModule",  "e6451ce26b8509cf724c7cf5d007878791143a58"],
    "common-src-TSingleton"               : ["../Common/Src/TSingleton",            "02e8fa7d98f33cdbd0e1f77d1a8a403a32e35882"],
    "common-src-CMakeModules"             : ["../Common/Src/CMakeModules",          "4d593266f3bb8916b15834050744659d0b86fc65"],
}

# Name : Source , Destination, version, Copied/Installation location wrt to Script root
downloadWin = {
    "GPADX11GetDeviceInfo" : [ "https://github.com/GPUOpen-Tools/gpu_performance_api/releases/download/v3.6/GPUPerfAPI-3.6.0.119.zip" , "default", "3_6", "../Common/Lib/AMD/GPUPerfAPI"]
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
