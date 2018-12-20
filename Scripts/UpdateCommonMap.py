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
    "common-lib-amd-ADL"                  : ["../Common/Lib/AMD/ADL",               "da98d7a9d2b8a6222d32c82952ee44bdfc827b2e"],
    "common-lib-amd-APPSDK-3.0"           : ["../Common/Lib/AMD/APPSDK",            "20e6889a76630be01042a3adc4877fd3498fa12c"],
    "common-lib-ext-OpenGL"               : ["../Common/Lib/Ext/OpenGL",            "63cd62c8b25e165b0e6f3307b998ed0cf3810edf"],
    "common-lib-ext-WindowsKits"          : ["../Common/Lib/Ext/Windows-Kits",      "2c99b88d6a8a9b672464436dad771b9799056a8a"],
    "googletest"                          : ["../Common/Lib/Ext/GoogleTest",        "542e057c6c5bf45454b43764b881397b71164d62"],
# Src.
    "common-src-ADLUtil"                  : ["../Common/Src/ADLUtil",               "d62c94514326775c83fc129bb89d299c8749ebd1"],
    "common-src-AmdDxExt"                 : ["../Common/Src/AmdDxExt",              "63544aae312985d57cd8704f5d269911f39e54d9"],
    "common-src-AmdVkExt"                 : ["../Common/Src/AmdVkExt",              "459e1657b0af296aeaac97903f309a90b59338bc"],
    "common-src-DeviceInfo"               : ["../Common/Src/DeviceInfo",            "b55106879ba431c019b288ccd8b8ca628f9292b1"],
    "common-src-DynamicLibraryModule"     : ["../Common/Src/DynamicLibraryModule",  "7d810ff5c589254755e4d1fe84c625cea40ccbb0"],
    "common-src-TSingleton"               : ["../Common/Src/TSingleton",            "02e8fa7d98f33cdbd0e1f77d1a8a403a32e35882"],
    "common-src-CMakeModules"             : ["../Common/Src/CMakeModules",          "9b25e59f240aced09b5025550e453dc0deb51b84"],
}

# Name : Source , Destination, version, Copied/Installation location wrt to Script root
downloadWin = {
    "Vulkan" : [ "https://sdk.lunarg.com/sdk/download/1.0.68.0/windows/VulkanSDK-1.0.68.0-Installer.exe", "default", "1.0.68.0", "default"],
    "GPADX11GetDeviceInfo" : [ "https://github.com/GPUOpen-Tools/GPA/releases/download/v3.2/GPUPerfAPI-3.2.623.0.zip" , "default", "3_2", "../Common/Lib/AMD/GPUPerfAPI"]
}

# Name : Source , Destination, version, Copied/Installation location wrt to Script root
downloadLinux = {
    "Vulkan" : [ "https://sdk.lunarg.com/sdk/download/1.0.68.0/linux/Vulkansdk-linux-x86_64-1.0.68.0.run", "default", "1.0.68.0", "default"]
}
