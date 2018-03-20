# UpdateCommonMap.py
#
#    Map of GitHub project names to clone target paths, relative to the GPUPerfAPI
#    project root on the local disk.
#    This script is used by the UpdateCommon.py script

# GitHub GPUOpen-Tools projects map
GitHubMapping = {
    "common-lib-amd-ADL"                     : ["../Common/Lib/AMD/ADL", "99cb60efe22718c1e12415b6b381facfdc7c7979"],
    "common-lib-amd-APPSDK-3.0"              : ["../Common/Lib/AMD/APPSDK", "52c521c0b6ae72d38bb6b324941a9bc2bff88b20"],
    "common-lib-ext-GoogleTest-1.7"          : ["../Common/Lib/Ext/GoogleTest", "7ab958af33ee2d435b52d341f95aafb67e0189d0"],
    "common-lib-ext-OpenGL"                  : ["../Common/Lib/Ext/OpenGL", "6b6684bf5408da05efeb24c53f4241a003c1ac6e"],
    "common-lib-ext-WindowsKits"             : ["../Common/Lib/Ext/Windows-Kits", "75d314b074e5899e1d8133e6ca253c3dca0307c9"],
    "common-lib-ext-Vulkan-1.0.49.0"         : ["../Common/Lib/Ext/Vulkan", "2940df77aed7f794f0c6808f8a42f3dbd812457a"],
    "common-src-ADLUtil"                     : ["../Common/Src/ADLUtil", "fa6949339b23529b30cf186188039adcb63ec596"],
    "common-src-AmdDxExt"                    : ["../Common/Src/AmdDxExt", "1e16621535a70dc4e088aaa7975ac4b84949f9e3"],
    "common-src-AmdVkExt"                    : ["../Common/Src/AmdVkExt", "ddee45ff247d37e6abc662dcd11d7a48a3cd3707"],
    "common-src-DeviceInfo"                  : ["../Common/Src/DeviceInfo", "15ab2c9116565f277113ede928df3f1cb1fc52d6"],
    "common-src-DynamicLibraryModule"        : ["../Common/Src/DynamicLibraryModule", "c331489a4167aca1f6d2e9a907ab7758c0b9bd90"],
    "common-src-TSingleton"                  : ["../Common/Src/TSingleton", "2a338d5b7e649ffba0225772c521726c18b13fff"],
    "common-src-Vsprops"                     : ["../Common/Src/Vsprops", "5a434b269727ed1f36c3c31aa56a0ca06502b198"],
}

downloadAndInstallMappingWin = {
    "https://sdk.lunarg.com/sdk/download/1.0.49.0/windows/VulkanSDK-1.0.49.0-Installer.exe" : ["../Common/Lib/Ext/Vulkan", "c:/VulkanSDK/1.0.49.0/Include", "../Common/Lib/Ext/Vulkan/1.0.49.0/SDK/Include"],
}

downloadAndInstallMappingLin = {
    "https://sdk.lunarg.com/sdk/download/1.0.49.0/linux/Vulkansdk-linux-x86_64-1.0.49.0.run" : ["../Common/Lib/Ext/Vulkan"],
}
