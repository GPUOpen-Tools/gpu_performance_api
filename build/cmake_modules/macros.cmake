## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

macro(INCLUDE_ADDITIONAL_MODULE)
    if(NOT ${ADDITIONAL_INCLUDE} STREQUAL "")
        include(${ADDITIONAL_INCLUDE})
    endif()
endmacro()

## Macro to create shared library target with exports
macro(ADD_SHARED_LIBRARY SHARED_LIB_NAME EXPORT_FILE_PATH)
    add_library(${ARGV0} SHARED ${SOURCES} ${ARGV1})
endmacro()

## Macro to create shared library target without exports
macro(ADD_SHARED_LIBRARY_NO_EXPORT SHARED_LIB_NAME)
    add_library(${ARGV0} SHARED ${SOURCES})
endmacro()

## Macro to static library target
macro(ADD_STATIC_LIBRARY STATIC_LIB_NAME)
    add_library(${ARGV0} ${SOURCES})
endmacro()

## Macro to compile Win32 resource
macro(INCLUDE_WIN_RESOURCE RES_FILE_NAME)
    set(RESOURCE_FILE_NAME ${RES_FILE_NAME})
    include(${GPA_CMAKE_MODULES_DIR}/win_resource_compile.cmake)
endmacro()

## MAcro to add linker flags
macro(ADD_LINKER_FLAGS)
    ## Each Projects have debug/release linker flags
    set_property(TARGET ${GPA_PROJECT_NAME} PROPERTY LINK_FLAGS_DEBUG "${COMMON_LINKER_FLAGS} ${COMMON_DEBUG_LINKER_FLAGS} ${ADDITIONAL_LINK_OPTIONS}")
    set_property(TARGET ${GPA_PROJECT_NAME} PROPERTY LINK_FLAGS_RELEASE "${COMMON_LINKER_FLAGS} ${COMMON_RELEASE_LINKER_FLAGS} ${ADDITIONAL_LINK_OPTIONS}")
endmacro()

## Macro to set the name of the executables
macro(SET_EXECUTABLE_NAME EXECUTABLE_NAME)
    set_target_properties(${ARGV0} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

    if(NOT ${CMAKE_RELEASE_POSTFIX} STREQUAL "")
        set_target_properties(${ARGV0} PROPERTIES RELEASE_POSTFIX ${CMAKE_RELEASE_POSTFIX})
    endif()
endmacro()

## Macro to define additional compile defintion to GPA user
macro(ADD_GPA_USER_COMPILE_DEFINITIONS)
    set_property(TARGET ${GPA_PROJECT_NAME} PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:DEBUG>:USE_DEBUG_GPA> ${ADDITIONAL_INTERNAL_DEFINITION})
endmacro()

if(WIN32)
    set(EXCLUDE_FROM_BUILD EXCLUDE_FROM_DEFAULT_BUILD)
else()
    set(EXCLUDE_FROM_BUILD EXCLUDE_FROM_ALL)
endif()

## Macro to exclude a target from the default build process
macro(REMOVE_TARGET_FROM_BUILD TARGET_NAME)
    set_property(TARGET ${ARGV0} PROPERTY ${EXCLUDE_FROM_BUILD} ON)
endmacro()

## Macro to remove C++ options for C builds
macro(REMOVE_CPP_COMPILE_OPTIONS)
    get_property(NATIVE_C_BUILD_OPTIONS DIRECTORY PROPERTY COMPILE_OPTIONS)
    set(USE_COMPILE_OPTIONS "")

    foreach(OPTION IN ITEMS ${NATIVE_C_BUILD_OPTIONS})
        if(OPTION STREQUAL "-std=c++11")
            continue()
        endif()
        if(OPTION STREQUAL "-Wno-non-virtual-dtor")
            continue()
        endif()
        set(USE_COMPILE_OPTIONS ${USE_COMPILE_OPTIONS} ${OPTION})
    endforeach()
    set_property(DIRECTORY PROPERTY COMPILE_OPTIONS ${USE_COMPILE_OPTIONS})
endmacro()