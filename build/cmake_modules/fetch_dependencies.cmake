## Copyright (c) 2025 Advanced Micro Devices, Inc. All rights reserved.

# When this script is ran in standalone script mode, we need to explicitly set the
# policies since it no longer can rely on the top level CMakeLists.txt
cmake_policy(VERSION 3.25...3.30) # A new policy in 3.30 helps FetchContent performance

## Helper variables for external content
set(GPA_ROOT_DIR                                   ${CMAKE_CURRENT_LIST_DIR}/../../)
set(COMMON_DIR                                     ${GPA_ROOT_DIR}/external)
set(CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO            ${COMMON_DIR}/device_info/Global-DeviceInfo.cmake)

if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/dependencies_server.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/dependencies_server.cmake)
else()
    set(GITHUB_SERVER "https://github.com/GPUOpen-Tools")
endif()


option(GPA_NO_FETCH "Skip fetching repo dependencies using FetchContent")
if(GPA_NO_FETCH)
    message(DEBUG "Skipping FetchContent!")
    return()
endif()

# FetchContent needs assistance on where to place its artifacts when
# running in script mode. Otherwise it will leave artifacts in the CWD.
if (CMAKE_SCRIPT_MODE_FILE)
    set(FETCHCONTENT_BASE_DIR "${GPA_ROOT_DIR}/build/CMakeBuild-tmp")
    # In any other situation setting CMAKE_CURRENT_BINARY_DIR is NOT advised.
    # But in script mode CMAKE_CURRENT_BINARY_DIR defaults to the cwd.
    # Which makes invoking this script problematic since FetchContent
    # relies on CMAKE_CURRENT_BINARY_DIR. This fixes the issue.
    set(CMAKE_CURRENT_BINARY_DIR "${FETCHCONTENT_BASE_DIR}")
endif()

include(FetchContent)


FetchContent_Populate(adl
    GIT_REPOSITORY "${GITHUB_SERVER}/adl.git"
    SOURCE_DIR "${COMMON_DIR}/adl"
    GIT_TAG 3c40dc2a9538e5a08c779e5f6bd088126cda0707
)

FetchContent_Populate(adl_util
    GIT_REPOSITORY "${GITHUB_SERVER}/adl_util.git"
    SOURCE_DIR "${COMMON_DIR}/adl_util"
    GIT_TAG af2b4b313abe8bff98652811c6456f0a3bbf7faa
)

FetchContent_Populate(device_info
    GIT_REPOSITORY "${GITHUB_SERVER}/device_info.git"
    SOURCE_DIR "${COMMON_DIR}/device_info"
    GIT_TAG a224c0940e9b296e9de0d5808a842f58e76d06aa
)

FetchContent_Populate(dynamic_library_module
    GIT_REPOSITORY "${GITHUB_SERVER}/dynamic_library_module.git"
    SOURCE_DIR "${COMMON_DIR}/dynamic_library_module"
    GIT_TAG a2d7e0109719f5c68bfdca5755131f8ecf50d82e
)

FetchContent_Populate(tsingleton
    GIT_REPOSITORY "${GITHUB_SERVER}/tsingleton.git"
    SOURCE_DIR "${COMMON_DIR}/tsingleton"
    GIT_TAG d048b8fdea9d84e8939116a442ef70608189f6e2
)

FetchContent_Populate(GPADX11GetDeviceInfo
    URL "${GITHUB_SERVER}/gpu_performance_api/releases/download/v3.17-tag/GPUPerfAPI-3.17.0.19.zip"
    SOURCE_DIR "${COMMON_DIR}/GPADX11GetDeviceInfo"
    # Adds far too much noise to the CMake configure step and is not useful
    DOWNLOAD_NO_PROGRESS ON
)

FetchContent_Populate(googletest
    GIT_REPOSITORY "${GITHUB_SERVER}/googletest.git"
    SOURCE_DIR "${COMMON_DIR}/googletest"
    GIT_TAG v1.16.0
)
