#/ Copyright (C) Advanced Micro Devices, Inc. All rights reserved.

cmake_minimum_required(VERSION 3.25)
set(GPA_CMAKE_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake_modules)

set(GPA_MAJOR_VERSION 4)
set(GPA_MINOR_VERSION 4)
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

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "Embedded")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_VISIBILITY_PRESET "hidden")
set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
set(CMAKE_VISIBILITY_INLINES_HIDDEN "YES")

if(NOT ${skipdocs})
    add_subdirectory(documentation/sphinx)
endif()

if(NOT ${skiptests})
    enable_testing()
endif()

block()
    set(CMAKE_FOLDER "${CMAKE_FOLDER}/external")

    add_subdirectory(external/device_info)

    set(CMAKE_FOLDER "${CMAKE_FOLDER}/third_party")

    if(NOT ${skiptests} AND NOT TARGET gtest)
        set(BUILD_GMOCK OFF)
        set(INSTALL_GTEST OFF)
        add_subdirectory(external/third_party/googletest EXCLUDE_FROM_ALL SYSTEM)
    endif()

    if (NOT skipvulkan)
        add_subdirectory(external/third_party/Vulkan-Headers EXCLUDE_FROM_ALL SYSTEM)
    endif()
endblock()

add_subdirectory(source/third_party/AmdVkExt SYSTEM)
if (WIN32)
    add_subdirectory(source/third_party/AmdDxExt SYSTEM)
endif()

# Only apply warnings to code we own
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Werror)
endif()

add_library(GPUPerfAPI-Headers INTERFACE)
add_library(AMD::GPUPerfAPI-Headers ALIAS GPUPerfAPI-Headers)
target_sources(GPUPerfAPI-Headers PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gpu_performance_api/gpu_perf_api.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gpu_performance_api/gpu_perf_api_counters.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gpu_performance_api/gpu_perf_api_functions.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gpu_performance_api/gpu_perf_api_function_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gpu_performance_api/gpu_perf_api_interface_loader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gpu_performance_api/gpu_perf_api_stub.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gpu_performance_api/gpu_perf_api_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gpu_performance_api/gpu_perf_api_vk.h
)

if (PROJECT_IS_TOP_LEVEL)
    # Used to verify that all headers in a target's PUBLIC and INTERFACE header sets can be included on their own.
    # This is a helpful test to ensure users of the library can include the headers without needing to worry about include order or missing includes.
    set_target_properties(GPUPerfAPI-Headers PROPERTIES VERIFY_INTERFACE_HEADER_SETS ON)
endif()

add_subdirectory(source)

set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_GROUPING IGNORE)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/gpu_performance_api" DESTINATION ${GPA_INSTALL_INCLUDEDIR} COMPONENT GPUPerfAPI)
install(FILES LICENSE.txt DESTINATION ${GPA_INSTALL_PREFIX} COMPONENT GPUPerfAPI)
install(FILES NOTICES.txt DESTINATION ${GPA_INSTALL_PREFIX} COMPONENT GPUPerfAPI)

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
set(CPACK_ARCHIVE_GPATESTKIT_FILE_NAME "GPATestKit${ARCHIVE_SUFFIX}")

include(CPack)

cpack_add_component(GPUPerfAPI)
cpack_add_component(GPATestKit)
