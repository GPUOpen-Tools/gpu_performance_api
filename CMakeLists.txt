## Copyright (C) 2018-2025 Advanced Micro Devices, Inc. All rights reserved. ##

cmake_minimum_required(VERSION 3.25)
set(GPA_CMAKE_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake_modules)

set(GPA_MAJOR_VERSION 4)
set(GPA_MINOR_VERSION 2)
set(GPA_UPDATE_VERSION 0)

if(NOT DEFINED build)
    set(GPA_BUILD_NUMBER 0)
else()
    set(GPA_BUILD_NUMBER ${build})
endif()
set(ProjectSuffix "-x64")
project(GPUPerfAPI${ProjectSuffix} VERSION ${GPA_MAJOR_VERSION}.${GPA_MINOR_VERSION}.${GPA_UPDATE_VERSION}.${GPA_BUILD_NUMBER} LANGUAGES C CXX)

include(${GPA_CMAKE_MODULES_DIR}/defs.cmake)
include(${GPA_CMAKE_MODULES_DIR}/build_flags.cmake)
include(${GPA_CMAKE_MODULES_DIR}/utils.cmake)
include(${GPA_CMAKE_MODULES_DIR}/common.cmake)
include(${GPA_CMAKE_MODULES_DIR}/fetch_dependencies.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT ${skiptests} AND NOT TARGET gtest)
    enable_testing()
    block()
        set(CMAKE_FOLDER "Tests")
        set(BUILD_GMOCK OFF)
        set(INSTALL_GTEST OFF)
        add_subdirectory(external/googletest EXCLUDE_FROM_ALL SYSTEM)
        if (MSVC)
            target_compile_options(gtest PRIVATE
                "$<$<CONFIG:RELEASE>:/MT>"
                "$<$<CONFIG:DEBUG>:/MTd>"
            )
        endif()
    endblock()
endif()

add_subdirectory(external/device_info)
add_subdirectory(external/tsingleton)
if (WIN32)
    add_subdirectory(external/adl)
    add_subdirectory(external/adl_util)
endif()

if(NOT ${skipdocs})
    add_subdirectory(documentation/sphinx)
endif()

add_subdirectory(source)

set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_GROUPING IGNORE)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/gpu_performance_api" DESTINATION ${GPA_INSTALL_INCLUDEDIR} COMPONENT GPUPerfAPI)
install(FILES LICENSE.txt NOTICES.txt DESTINATION ${GPA_INSTALL_PREFIX} COMPONENT GPUPerfAPI)

# Create the archive's suffix (ie: <GPUPerfAPI>[-Android|-Linux]-<version>.[zip|tgz])
set(ARCHIVE_SUFFIX "")
if (LINUX)
    set(ARCHIVE_SUFFIX "${ARCHIVE_SUFFIX}-Linux")
elseif (ANDROID)
    set(ARCHIVE_SUFFIX "${ARCHIVE_SUFFIX}-Android")
endif()
set(ARCHIVE_SUFFIX "${ARCHIVE_SUFFIX}-${PROJECT_VERSION}")
if (GPA_PACKAGE_SUFFIX)
    set(ARCHIVE_SUFFIX "${ARCHIVE_SUFFIX}-${GPA_PACKAGE_SUFFIX}")
endif()
set(CPACK_PACKAGE_VENDOR "AMD")
if (WIN32)
    set(CPACK_GENERATOR "ZIP")
else()
    set(CPACK_GENERATOR "TGZ")
    # By default CMake uses .tar.gz
    set(CPACK_ARCHIVE_FILE_EXTENSION "tgz")
endif()
set(CPACK_PACKAGE_DIRECTORY ${GPA_OUTPUT_DIR})
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)

set(CPACK_ARCHIVE_GPUPERFAPI_FILE_NAME "GPUPerfAPI${ARCHIVE_SUFFIX}")

include(CPack)

cpack_add_component(GPUPerfAPI)
