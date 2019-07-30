# UpdateCommonMap.py
#
#    Map of GitHub project names to clone target paths, relative to the GPUPerfAPI
#    project root on the local disk.
#    This script is used by the UpdateCommon.py script

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
    "Vulkan" : [ "https://sdk.lunarg.com/sdk/download/1.0.68.0/windows/VulkanSDK-1.0.68.0-Installer.exe", "default", "1.0.68.0", "default"],
    "GPADX11GetDeviceInfo" : [ "https://github.com/GPUOpen-Tools/GPA/releases/download/v3.4/GPUPerfAPI-3.4.1319.zip" , "default", "3_4", "../Common/Lib/AMD/GPUPerfAPI"]
}

# Name : Source , Destination, version, Copied/Installation location wrt to Script root
downloadLinux = {
    "Vulkan" : [ "https://sdk.lunarg.com/sdk/download/1.0.68.0/linux/Vulkansdk-linux-x86_64-1.0.68.0.run", "default", "1.0.68.0", "default"]
}
