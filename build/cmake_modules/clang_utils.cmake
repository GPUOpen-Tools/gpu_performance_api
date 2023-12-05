## Copyright (c) 2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

find_program(CLANG_FORMAT clang-format DOC "Clang format executable")
find_program(CLANG_TIDY clang-tidy DOC "Clang tidy executable")

function(ADD_LINT_PASSES TARGET)
    ADD_CLANG_FORMAT_PASS(${TARGET} ${ARGN})
    ADD_CLANG_TIDY_PASS(${TARGET} ${ARGN})
endfunction()

# Add a pre build action to run clang-format on the source files for a given target.
# The list of source files should be passed after the name of the target (ARGN in this function).
function(ADD_CLANG_FORMAT_PASS TARGET)
    if(GPA_RUN_CLANG_FORMAT)
        if(CLANG_FORMAT)
            # ARGN is not a normal variable, so we need to assign it before we can mutate it
            set(CLANG_FORMAT_SOURCES ${ARGN})
            list(
                FILTER
                CLANG_FORMAT_SOURCES
                EXCLUDE
                REGEX
                    "auto_generated"
            )

            add_custom_command(
                TARGET
                    ${TARGET}
                PRE_BUILD
                COMMAND
                    ${CLANG_FORMAT}
                ARGS
                    $<$<BOOL:${GPA_REQUIRE_CLEAN_LINT}>:-Werror>
                    $<$<BOOL:${GPA_APPLY_LINT_FIXES}>:-i>
                    ${CLANG_FORMAT_SOURCES}
                WORKING_DIRECTORY
                    ${CMAKE_PROJECT_DIR}
                COMMAND_EXPAND_LISTS
                COMMENT
                    "Running clang format on sources for ${TARGET}..."
            )
        else()
            message(
                WARNING
                "clang-format cannot be run as part of the build because the clang-format executable could not be found"
            )
        endif()
    endif()
endfunction()

# Add a post build action to run clang-tidy on the source files for a given target.
# While it would be optimal to run clang-tidy as a pre-build action to avoid having to rebuild
# with any changes from clang-tidy (which will be applied automatically if --fix was passed to
# a pre_build script), we need to make this a post-build action since clang-tidy relies on the
# presence of a compile_commands.json file, which is a build product.
# The list of source files should be passed after the name of the target (ARGN in this function).
function(ADD_CLANG_TIDY_PASS TARGET)
    if(GPA_RUN_CLANG_TIDY)
        if(CLANG_TIDY)
            # ARGN is not a normal variable, so we need to assign it before we can mutate it
            set(CLANG_TIDY_SOURCES ${ARGN})
            list(
                FILTER
                CLANG_TIDY_SOURCES
                EXCLUDE
                REGEX
                    "auto_generated"
            )

            add_custom_command(
                TARGET
                    ${TARGET}
                POST_BUILD
                COMMAND
                    ${CLANG_TIDY}
                ARGS
                    "-p=${PROJECT_BINARY_DIR}"
                    $<$<BOOL:${GPA_REQUIRE_CLEAN_LINT}>:--warnings-as-errors=true>
                    $<$<BOOL:${GPA_APPLY_LINT_FIXES}>:--fix>
                    ${CLANG_TIDY_SOURCES}
                WORKING_DIRECTORY
                    ${CMAKE_PROJECT_DIR}
                COMMAND_EXPAND_LISTS
                COMMENT
                    "Running clang tidy on sources for ${TARGET}..."
            )
        else()
            message(
                WARNING
                "clang-tidy cannot be run as part of the build because the clang-tidy executable could not be found"
            )
        endif()
    endif()
endfunction()
