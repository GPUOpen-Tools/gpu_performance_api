## Copyright (C) 2025 Advanced Micro Devices, Inc. All rights reserved. ##

# When this script is ran in standalone script mode, we need to explicitly set the
# policies since it no longer can rely on the top level CMakeLists.txt
cmake_policy(VERSION 3.25...3.30) # A new policy in 3.30 helps FetchContent performance

## Helper variables for external content
set(GPA_ROOT_DIR                                   ${CMAKE_CURRENT_LIST_DIR}/../../)
set(COMMON_DIR                                     ${GPA_ROOT_DIR}/external)

set(GITHUB_SERVER "https://github.com/GPUOpen-Tools")

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

if (WIN32)
    FetchContent_Populate(adl
        GIT_REPOSITORY "${GITHUB_SERVER}/adl.git"
        SOURCE_DIR "${COMMON_DIR}/adl"
        GIT_TAG 3c40dc2a9538e5a08c779e5f6bd088126cda0707
    )

    FetchContent_Populate(adl_util
        GIT_REPOSITORY "${GITHUB_SERVER}/adl_util.git"
        SOURCE_DIR "${COMMON_DIR}/adl_util"
        GIT_TAG 0e5415d86c2d80adcc611a09b532e393a6584bcc
    )
endif()

FetchContent_Populate(device_info
    GIT_REPOSITORY "${GITHUB_SERVER}/device_info.git"
    SOURCE_DIR "${COMMON_DIR}/device_info"
    GIT_TAG 0f9cb0d126a1345331e71116733553602b7585d7
)

FetchContent_Populate(tsingleton
    GIT_REPOSITORY "${GITHUB_SERVER}/tsingleton.git"
    SOURCE_DIR "${COMMON_DIR}/tsingleton"
    GIT_TAG d048b8fdea9d84e8939116a442ef70608189f6e2
)

FetchContent_Populate(googletest
    GIT_REPOSITORY "${GITHUB_SERVER}/googletest.git"
    SOURCE_DIR "${COMMON_DIR}/googletest"
    GIT_TAG v1.16.0
)
