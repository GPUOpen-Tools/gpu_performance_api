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
    "common-lib-amd-ADL"                  : ["../Common/Lib/AMD/ADL",               "04b97aa3138c282d9c2b84b3b2f3d06decbea6df"],
    "common-lib-amd-APPSDK-3.0"           : ["../Common/Lib/AMD/APPSDK",            "4e6d30e406d2e5a65e1d65e404fe6df5f772a32b"],
    "common-lib-ext-GoogleTest-1.7"       : ["../Common/Lib/Ext/GoogleTest",        "7ab958af33ee2d435b52d341f95aafb67e0189d0"],
    "common-lib-ext-OpenGL"               : ["../Common/Lib/Ext/OpenGL",            "6b6684bf5408da05efeb24c53f4241a003c1ac6e"],
    "common-lib-ext-WindowsKits"          : ["../Common/Lib/Ext/Windows-Kits",      "dc6a865cab7aac7a9d3c033c529dbd37cf3cee41"],
# Src.
    "common-src-ADLUtil"                  : ["../Common/Src/ADLUtil",               "2f57a3e44067379a1bdbb7b420d5e95ab2cab55c"],
    "common-src-AmdDxExt"                 : ["../Common/Src/AmdDxExt",              "3192b5d86218214fa04462523b58553ac9d406e6"],
    "common-src-AmdVkExt"                 : ["../Common/Src/AmdVkExt",              "6b1123404d4bc27ad6b46fb8d8c12b0f02a0c1dd"],
    "common-src-DeviceInfo"               : ["../Common/Src/DeviceInfo",            "10fd4de85f62d9146480e2e76900f284d58dcecd"],
    "common-src-DynamicLibraryModule"     : ["../Common/Src/DynamicLibraryModule",  "37160c2c7543f08b04cf0ac633a38f221bfad31e"],
    "common-src-TSingleton"               : ["../Common/Src/TSingleton",            "ebde730c07eac1c1da7f486d65517b93e1550edb"],
    "common-src-Vsprops"                  : ["../Common/Src/Vsprops",               "69c97737d688a2e3fe5a5d4ba844ae6ab1cd35c4"],
}

# Name : Source , Destination, version, Copied/Installation location wrt to Script root
downloadWin = {
    "Vulkan" : [ "https://sdk.lunarg.com/sdk/download/1.0.68.0/windows/VulkanSDK-1.0.68.0-Installer.exe", "default", "1.0.68.0", "default"],
    "GPADX11GetDeviceInfo" : [ "https://github.com/GPUOpen-Tools/GPA/releases/download/v3.0/GPUPerfAPI-3.0.353.0.zip" , "default", "3_0", "Common/Lib/AMD/GPUPerfAPI"]
}

# Name : Source , Destination, version, Copied/Installation location wrt to Script root
downloadLinux = {
    "Vulkan" : [ "https://sdk.lunarg.com/sdk/download/1.0.68.0/linux/Vulkansdk-linux-x86_64-1.0.68.0.run", "default", "1.0.68.0", "default"]
}