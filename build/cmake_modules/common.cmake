#/ Copyright (C) Advanced Micro Devices, Inc. All rights reserved.

include(${GPA_CMAKE_MODULES_DIR}/utils.cmake)

# Include global cmake common file
include(${CMAKE_COMMON_SRC_GLOBAL_CMAKE_MODULE})

# Check for required variables from other cmake files.
if(${GPA_OUTPUT_DIR} STREQUAL "")
    message(FATAL_ERROR "No output directory is defined, make sure defs.cmake is included before common.cmake")
endif()

# Global compiler options
add_compile_options(${COMMON_COMPILATION_FLAGS})

add_compile_options(-DUNICODE
                    -D_UNICODE)

get_cmake_property(GPA_IS_MULTI_CONFIG GENERATOR_IS_MULTI_CONFIG)
if(GPA_IS_MULTI_CONFIG)
    set(CURRENT_CONFIG "Debug/Release")
else()
    set(CURRENT_CONFIG ${CMAKE_BUILD_TYPE})
endif()

## Handling project
if(NOT ${ProjectName} STREQUAL "")
    message(STATUS "Evaluating and including project ${ProjectName} for config ${CURRENT_CONFIG} for ${AMDTPlatform} platform in ${PROJECT_NAME} solution")
endif()

# Only set output directories if this is the top level project.
# This allows subprojects to be included in other builds without forcing the output directories on the parent project.
if (PROJECT_IS_TOP_LEVEL)
    if (GPA_IS_MULTI_CONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${GPA_OUTPUT_DIR}/release${OUTPUT_SUFFIX})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${GPA_OUTPUT_DIR}/debug${OUTPUT_SUFFIX})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${GPA_OUTPUT_DIR}/release${OUTPUT_SUFFIX})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${GPA_OUTPUT_DIR}/debug${OUTPUT_SUFFIX})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${GPA_OUTPUT_DIR}/release${OUTPUT_SUFFIX})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${GPA_OUTPUT_DIR}/debug${OUTPUT_SUFFIX})
    else()
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GPA_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}${OUTPUT_SUFFIX})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    endif()
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(GPA_COMMON_LINK_ARCHIVE_FLAG -Wl,--whole-archive)
    set(GPA_COMMON_LINK_NO_ARCHIVE_FLAG -Wl,--no-whole-archive)
    add_compile_options(
        -Wno-unknown-pragmas
        # Our code base is currently not compliant with strict aliasing rules.
        -Wno-strict-aliasing
        # As a result we must disable strict aliasing optimizations.
        -fno-strict-aliasing
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-non-virtual-dtor>
        -Wno-unused-value
        # Our libraries rely on reinitialization of global variables. This is effectively what happens on Windows which is the platform we primarily develop on.
        # On Linux when compiling with the GNU toolchain dlclose does not reset global variables by default, so we need to disable the gnu unique attribute which would otherwise cause the global
        # variables to be shared across multiple loads of the library.
        #
        # Only GCC emits GNU‑unique symbols because GCC implemented a GNU‑specific workaround for C++ ODR issues involving inline static
        # locals and template statics. This workaround forces symbol unification across DSOs, preventing subtle crashes —
        # but at the cost of disabling dlclose. Clang intentionally avoids this behavior because LLVM developers consider
        # STB_GNU_UNIQUE harmful and unnecessary, choosing instead to preserve unloadability and avoid ABI complications.
        #
        # Android doesn't have this issue. Since it uses Clang. So really this is only an issue on Linux with GNU.
        #
        # In particular: OverrideBlockInstanceCounters modifies global state. Once this global is modified it can't be reset by dlclose
        # and will affect all future loads of the library. This is not an issue on Windows because each load of the library gets its own copy of
        # the global variables, but on Linux we need to disable the gnu unique attribute to get the same behavior.
        # This could be fixed by refactoring the code to avoid reliance on global variables,
        # but for now we need to disable the gnu unique attribute to get the correct behavior on Linux.
        $<$<CXX_COMPILER_ID:GNU>:-fno-gnu-unique>
    )
endif()
