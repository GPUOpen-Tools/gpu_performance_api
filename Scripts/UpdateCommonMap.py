# UpdateCommonMap.py
#
#    Map of GitHub project names to clone target paths, relative to the GPUPerfAPI
#    project root on the local disk.
#    This script is used by the UpdateCommon.py script

# GitHub GPUOpen-Tools projects map
GitHubMapping = {
    "common-lib-amd-ADL"                     : ["../Common/Lib/AMD/ADL", "0f3122ba840b193ca9ebd8f050a7ddac58f3b27e"],
    "common-lib-amd-APPSDK-3.0"              : ["../Common/Lib/AMD/APPSDK", "acb9bb08f23e5653bbe8b6021a2cf89f1c7fd26f"],
    "common-lib-ext-GoogleTest-1.7"          : ["../Common/Lib/Ext/GoogleTest", "7ab958af33ee2d435b52d341f95aafb67e0189d0"],
    "common-lib-ext-OpenGL"                  : ["../Common/Lib/Ext/OpenGL", "6b6684bf5408da05efeb24c53f4241a003c1ac6e"],
    "common-lib-ext-OpenGLES"                : ["../Common/Lib/Ext/OpenGLES", "758b5caeeaff90858f292adc45f8cfda0d34b000"],
    "common-lib-ext-WindowsKits"             : ["../Common/Lib/Ext/Windows-Kits", "75d314b074e5899e1d8133e6ca253c3dca0307c9"],
    "common-lib-ext-Vulkan-1.0.49.0"         : ["../Common/Lib/Ext/Vulkan", "2940df77aed7f794f0c6808f8a42f3dbd812457a"],
    "common-src-ADLUtil"                     : ["../Common/Src/ADLUtil", "5a54c478c06ced583ac8ad74228f3e84f90e44f6"],
    "common-src-AMDTMutex"                   : ["../Common/Src/AMDTMutex", "fb68811ed3a475cc9ab1c5d5e0482658ec679716"],
    "common-src-AmdDxExt"                    : ["../Common/Src/AmdDxExt", "1e16621535a70dc4e088aaa7975ac4b84949f9e3"],
    "common-src-AmdVkExt"                    : ["../Common/Src/AmdVkExt", "1fc64cdf8da2bd5c1e1b87a6d2ee58c6334e686b"],
    "common-src-DeviceInfo"                  : ["../Common/Src/DeviceInfo", "e5e83b573fb49a16e8e1045d4cb39cbb17326270"],
    "common-src-DynamicLibraryModule"        : ["../Common/Src/DynamicLibraryModule", "4b1587a50119c0a59ce3472facbaa2af7c243fdf"],
    "common-src-GPUPerfAPIUtils"             : ["../Common/Src/GPUPerfAPIUtils", "a05a033a82d3b85e4b219888c992b9586a87375f"],
    "common-src-TSingleton"                  : ["../Common/Src/TSingleton", "2a338d5b7e649ffba0225772c521726c18b13fff"],
    "common-src-Vsprops"                     : ["../Common/Src/Vsprops", "5a434b269727ed1f36c3c31aa56a0ca06502b198"],
}

downloadAndInstallMappingWin = {
    "https://vulkan.lunarg.com/sdk/download/1.0.49.0/windows/VulkanSDK-1.0.49.0-Installer.exe" : ["../Common/Lib/Ext/Vulkan", "c:/VulkanSDK/1.0.49.0/Include", "../Common/Lib/Ext/Vulkan/1.0.49.0/SDK/Include"],
}

downloadAndInstallMappingLin = {
    "https://vulkan.lunarg.com/sdk/download/1.0.49.0/linux/Vulkansdk-linux-x86_64-1.0.49.0.run" : ["../Common/Lib/Ext/Vulkan"],
}

