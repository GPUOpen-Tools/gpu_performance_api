# UpdateCommonMap.py
#
#    Map of GitHub project names to clone target paths, relative to the GPUPerfAPI
#    project root on the local disk.
#    This script is used by the UpdateCommon.py script

# GitHub GPUOpen-Tools projects map
GitHubMapping = {
    "common-lib-amd-ADL"                     : "../Common/Lib/AMD/ADL",
    "common-lib-amd-APPSDK-3.0"              : "../Common/Lib/AMD/APPSDK",
    "common-lib-ext-GoogleTest-1.7"          : "../Common/Lib/Ext/GoogleTest",
    "common-lib-ext-OpenGL"                  : "../Common/Lib/Ext/OpenGL",
    "common-lib-ext-OpenGLES"                : "../Common/Lib/Ext/OpenGLES",
    "common-lib-ext-WindowsKits"             : "../Common/Lib/Ext/Windows-Kits",
    "common-lib-ext-Vulkan-1.0.49.0"         : "../Common/Lib/Ext/Vulkan",
    "common-src-ADLUtil"                     : "../Common/Src/ADLUtil",
    "common-src-AMDTMutex"                   : "../Common/Src/AMDTMutex",
    "common-src-AmdDxExt"                    : "../Common/Src/AmdDxExt",
    "common-src-AmdVkExt"                    : "../Common/Src/AmdVkExt",
    "common-src-DeviceInfo"                  : "../Common/Src/DeviceInfo",
    "common-src-DynamicLibraryModule"        : "../Common/Src/DynamicLibraryModule",
    "common-src-GPUPerfAPIUtils"             : "../Common/Src/GPUPerfAPIUtils",
    "common-src-TSingleton"                  : "../Common/Src/TSingleton",
    "common-src-Vsprops"                     : "../Common/Src/Vsprops",
}

downloadAndInstallMappingWin = {
    "https://sdk.lunarg.com/sdk/download/1.0.49.0/windows/VulkanSDK-1.0.49.0-Installer.exe" : ["../Common/Lib/Ext/Vulkan", "c:/VulkanSDK/1.0.49.0/Include", "../Common/Lib/Ext/Vulkan/1.0.49.0/SDK/Include"],
}

downloadAndInstallMappingLin = {
    "https://sdk.lunarg.com/sdk/download/1.0.49.0/linux/Vulkansdk-linux-x86_64-1.0.49.0.run" : ["../Common/Lib/Ext/Vulkan"],
}
