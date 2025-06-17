## Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.
include(${CMAKE_CURRENT_LIST_DIR}/Global-Internal.cmake)

# ProjectName must be set by each Tools project
# ${ProjectName}
## If CMAKE_BUILD_TYPE is not specified, we will set it to Release
if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "")
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})
else()
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT DEFINED AMDTPlatform)
    set(AMDTPlatform "x64")
endif()

if(NOT DEFINED AMDTPlatformExt)
    set(AMDTPlatformExt "x86_64")
endif()

if(NOT DEFINED AMDTPlatformSuffix)
    if(WIN32)
        set(AMDTPlatformSuffix "-x64")
    else()
        set(AMDTPlatformSuffix "")
    endif()
endif()

if(NOT DEFINED AMDTPlatformSuffixNumBitsOnly)
    set(AMDTPlatformSuffixNumBitsOnly "64")
endif()

set(COMMON_PREPROCESSOR_DEFINITION ${COMMON_PREPROCESSOR_DEFINITION} X64)

if(NOT DEFINED AMDTOutputDir)
    set(AMDTOutputDir "${CMAKE_SOURCE_DIR}/Output")
endif()

if(NOT DEFINED AMDTBuildSuffix)
    set(AMDTBuildSuffix "")
endif()

if(NOT DEFINED AMDTCrt)
    set(AMDTCrt "MD")
endif()

if(NOT DEFINED AMDTBuild)
    set(AMDTBuild "AMDT_PUBLIC")
endif()

## Set the global property to use folders for VS filters
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

## Set additional compilation flags
if(WIN32)
    set(COMMON_COMPILATION_FLAGS ${COMMON_COMPILATION_FLAGS} /W4 /WX)
else()
    set(COMMON_COMPILATION_FLAGS ${COMMON_COMPILATION_FLAGS} -std=c++17 -D_LINUX -fPIC -Wall -Werror)
endif()

## Set Global defintions
set(COMMON_COMPILE_DEFINITIONS  ${COMMON_PREPROCESSOR_DEFINITION}
                                AMDT_BUILD="${AMDTBuild}"
                                ${AMDTBuild}
                                AMDTCRT="${AMDTCrt}"
                                AMDT_PLATFORM_SUFFIX="${AMDTPlatformSuffix}"
                                AMDT_PLATFORM_SUFFIX_W=L"${AMDTPlatformSuffix}"
                                AMDT_BUILD_SUFFIX="${AMDTBuildSuffix}"
                                AMDT_BUILD_SUFFIX_W=L"${AMDTBuildSuffix}"
                                SU_USE_NATIVE_STL
                                NOMINMAX)

if(WIN32)
    set(COMMON_COMPILE_DEFINITIONS ${COMMON_COMPILE_DEFINITIONS}
                                   _WINDOWS
                                   WIN32
                                   WIN32_LEAN_AND_MEAN)
endif()

## Debug config definitions
set(Global-Debug-AMDTDebugSuffix "-d")
set(Global-Debug-AMDTDebugSuffixNoDash "d")
set(Global-Debug-AMDTDebugSuffixUnderscore "_d")

## Set common compilation definitions through COMPILE_DEFINITIONS property in folder/directory scope
## CMake generates project files for all allowed configs while using VS generators.
## To add config conditional definitions, we are using cmake-generator-expressions e.g. $<$<CONFIG:DEBUG>:_DEBUG>
## Note: cmake-generator-expressions only work in some of the CMake functions
set_property(DIRECTORY PROPERTY COMPILE_DEFINITIONS
                                ${COMMON_COMPILE_DEFINITIONS}
                                AMDTDebugSuffix="$<$<CONFIG:DEBUG>:${Global-Debug-AMDTDebugSuffix}>"
                                AMDT_DEBUG_SUFFIX="$<$<CONFIG:DEBUG>:${Global-Debug-AMDTDebugSuffix}>"
                                AMDT_DEBUG_SUFFIX_W="$<$<CONFIG:DEBUG>:L${Global-Debug-AMDTDebugSuffix}>"
                                AMDTDebugSuffixNoDash="$<$<CONFIG:DEBUG>:${Global-Debug-AMDTDebugSuffixNoDash}>"
                                AMDTDebugSuffixUnderscore="$<$<CONFIG:DEBUG>:${Global-Debug-AMDTDebugSuffixUnderscore}>"
                                AMDTProjectSuffix="${AMDTPlatformSuffix}$<$<CONFIG:DEBUG>:${Global-Debug-AMDTDebugSuffix}>${AMDTBuildSuffix}"
                                AMDT_PROJECT_SUFFIX="${AMDTPlatformSuffix}$<$<CONFIG:DEBUG>:${Global-Debug-AMDTDebugSuffix}>${AMDTBuildSuffix}"
                                AMDT_PROJECT_SUFFIX_W=L"${AMDTPlatformSuffix}$<$<CONFIG:DEBUG>:${Global-Debug-AMDTDebugSuffix}>${AMDTBuildSuffix}"
                                AMDTProjectName="${ProjectName}${AMDTPlatformSuffix}$<$<CONFIG:DEBUG>:${Global-Debug-AMDTDebugSuffix}>${AMDTBuildSuffix}"
                                AMDT_PROJECT_NAME="${ProjectName}${AMDTPlatformSuffix}$<$<CONFIG:DEBUG>:${Global-Debug-AMDTDebugSuffix}>${AMDTBuildSuffix}"
                                $<$<CONFIG:DEBUG>:_DEBUG>
                                $<$<CONFIG:RELEASE>:NDEBUG>)

## Define common release config compilation flags
set(COMMON_RELEASE_COMPILATION_FLAGS "")

## Define common debug config compilation flags
set(COMMON_DEBUG_COMPILATION_FLAGS "")

## Define common release config linker flags
set(COMMON_RELEASE_LINKER_FLAGS "")

## Define common debug config linker flags
set(COMMON_DEBUG_LINKER_FLAGS "")

## Enable parallel builds for Visual Studio similar to Ninja

if(NOT CMAKE_VS_GLOBALS MATCHES "(^|;)UseMultiToolTask=")
    list(APPEND CMAKE_VS_GLOBALS "UseMultiToolTask=true")
endif()

if(NOT CMAKE_VS_GLOBALS MATCHES "(^|;)EnforceProcessCountAcrossBuilds=")
    list(APPEND CMAKE_VS_GLOBALS "EnforceProcessCountAcrossBuilds=true")
endif()

if(WIN32)
    ## Windows Release Compilation flags:
    ## /Z7 :Debug Information
    ## /GF :string pooling
    ## /O2 :Optimization
    ## /MD :Multi-threaded DLL

    ## Linker options:
    ## /OPT:REF :References
    ## /DEBUG : generate debug information
    ## /OPT:ICF enable COMDATA folding
    ## /INCREMENTAL:NO : Incremental Link
    set(COMMON_RELEASE_COMPILATION_FLAGS    /Z7 /GF /O2 /MD)
    set(COMMON_RELEASE_LINKER_FLAGS         "/OPT:REF /DEBUG /OPT:ICF /INCREMENTAL:NO /MANIFEST:NO")

    ## Debug Compiler Flags:
    ## /RTC1 : Runtime check
    ## /Z7   : Debug format
    ## /Gm-  : turn off minimal rebuild
    ## /Od   : Optimization disabled
    ## /MDd  : CRT Multi-threaded debug

    ## Debug Linker flags:
    ## /INCREMENTAL:NO - disable incremental linking
    ## /DEBUG          - generate debug info
    ## /MANIFEST:NO    - no manifest
    set(COMMON_DEBUG_COMPILATION_FLAGS        /RTC1 /Z7 /Gm- /Od /MDd)
    set(COMMON_DEBUG_LINKER_FLAGS             "/MANIFEST:NO /DEBUG /INCREMENTAL:NO")
else()
    set(COMMON_DEBUG_COMPILATION_FLAGS        -g -O0 -D_DEBUG)
    set(COMMON_DEBUG_LINKER_FLAGS             "")
endif()

## Each project compilation flags
set_property(DIRECTORY PROPERTY COMPILE_OPTIONS ${COMMON_COMPILATION_FLAGS}
                                $<$<CONFIG:DEBUG>:${COMMON_DEBUG_COMPILATION_FLAGS}>
                                $<$<CONFIG:RELEASE>:${COMMON_RELEASE_COMPILATION_FLAGS}>)


## var for adding additional library dependencies
## For usage add this to target_link_libraries(...)
set(ADDITIONAL_LIBS "")

## var for adding additional compiler preprocessor definitions
## For usage add this to add_definitions(...)
set(ADDITIONAL_DEFINTIONS "")

## var for adding include directories
## For usage add this to include_directories(...)
set(ADDITIONAL_INCLUDE_DIRECTORIES "")

## var for additional link directories
## For usage add this to link_directories(...)
set(ADDITIONAL_LINK_DIRECTORIES "")

## var for additional compile options
## For usage add this to add_compile_options(...)
set(ADDITIONAL_COMPILE_OPTIONS "")

## var for additional link options
## For usage, use LINK_FLAGS_XXX target property
set(ADDITIONAL_LINK_OPTIONS "")

## Set the debug and release postfix to the target names
set(CMAKE_DEBUG_POSTFIX ${AMDTPlatformSuffix}-d${AMDTInternalSuffix})
set(CMAKE_RELEASE_POSTFIX ${AMDTPlatformSuffix}${AMDTInternalSuffix})

## Enable to use folders for VS filters
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
