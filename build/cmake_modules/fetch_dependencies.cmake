#/ Copyright (C) Advanced Micro Devices, Inc. All rights reserved.

# When this script is ran in standalone script mode, we need to explicitly set the
# policies since it no longer can rely on the top level CMakeLists.txt
cmake_policy(VERSION 3.25...3.30) # A new policy in 3.30 helps FetchContent performance

## Helper variables for external content
set(GPA_ROOT_DIR       ${CMAKE_CURRENT_LIST_DIR}/../../)
set(EXTERNAL_DIR       ${GPA_ROOT_DIR}/external)
set(EXTERNAL_PARTY_DIR ${EXTERNAL_DIR}/third_party)

set(GITHUB_ORG "GPUOpen-Tools")

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

FetchContent_Populate(device_info
    GIT_REPOSITORY "git@github.com:${GITHUB_ORG}/device_info.git"
    GIT_TAG 283b7b961ef0eda7294cf4fbf6e1fa94b10919b7
    SOURCE_DIR "${EXTERNAL_DIR}/device_info"
)

FetchContent_Populate(googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    SOURCE_DIR "${EXTERNAL_PARTY_DIR}/googletest"
    GIT_TAG v1.17.0
    GIT_SHALLOW ON
)

FetchContent_Populate(Vulkan-Headers
    GIT_REPOSITORY "https://github.com/KhronosGroup/Vulkan-Headers.git"
    SOURCE_DIR "${EXTERNAL_PARTY_DIR}/Vulkan-Headers"
    GIT_TAG v1.4.332
    GIT_SHALLOW ON
)
