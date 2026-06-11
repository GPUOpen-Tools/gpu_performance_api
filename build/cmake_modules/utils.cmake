#/ Copyright (C) Advanced Micro Devices, Inc. All rights reserved.

include(${GPA_CMAKE_MODULES_DIR}/clang_utils.cmake)

macro(INCLUDE_ADDITIONAL_MODULE)
    if(NOT ${ADDITIONAL_INCLUDE} STREQUAL "")
        include(${ADDITIONAL_INCLUDE})
    endif()
endmacro()

## Function to create shared library target with exports
function(ADD_SHARED_LIBRARY SHARED_LIB_NAME EXPORT_FILE_PATH)
    add_library(${SHARED_LIB_NAME} SHARED ${ARGN} ${EXPORT_FILE_PATH})
    add_lint_passes(${SHARED_LIB_NAME} ${ARGN})
endfunction()

## Function to create shared library target without exports
function(ADD_SHARED_LIBRARY_NO_EXPORT SHARED_LIB_NAME)
    add_library(${SHARED_LIB_NAME} SHARED ${ARGN})
    add_lint_passes(${SHARED_LIB_NAME} ${ARGN})
endfunction()

## Function to create static library target
function(ADD_STATIC_LIBRARY STATIC_LIB_NAME)
    add_library(${STATIC_LIB_NAME} ${ARGN})
    add_lint_passes(${STATIC_LIB_NAME} ${ARGN})
endfunction()

## Macro to add linker flags
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

## Macro to define additional compile definition to GPA user
macro(ADD_GPA_USER_COMPILE_DEFINITIONS)
    set_property(TARGET ${GPA_PROJECT_NAME} PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:DEBUG>:USE_DEBUG_GPA> ${ADDITIONAL_INTERNAL_DEFINITION})
endmacro()

## Macro to define additional compile definitions to a named GPA Target project.
macro(ADD_GPA_COMPILE_DEFINITIONS TARGET_NAME)
    set_property(TARGET ${ARGV0} PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:DEBUG>:USE_DEBUG_GPA> ${ADDITIONAL_INTERNAL_DEFINITION})
endmacro()

# A special return code that can be used in tests to indicate that a test should be skipped.
# This allows us to skip tests in a way that is distinguishable from a test failure.
macro(ADD_GPA_SKIP_RETURN_CODE_COMPILE_DEFINITION TARGET_NAME)
    target_compile_definitions(${TARGET_NAME} PRIVATE GPA_SKIP_RETURN_CODE=42)
endmacro()
