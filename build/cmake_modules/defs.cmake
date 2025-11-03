## Copyright (C) 2018-2025 Advanced Micro Devices, Inc. All rights reserved. ##

if(NOT DEFINED GPA_OUTPUT_DIR)
    set(GPA_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/build/output)
endif()

## Set the Common Directories
set(GPA_PUBLIC_HEADER_REL_PATH                              "include")
set(GPA_PUBLIC_HEADER                                       "${PROJECT_SOURCE_DIR}/${GPA_PUBLIC_HEADER_REL_PATH}")
set(GPA_SRC                                                 "${PROJECT_SOURCE_DIR}/source")
set(GPA_SRC_COMMON_REL_PATH                                 "source/gpu_perf_api_common")
set(GPA_SRC_COMMON                                          "${PROJECT_SOURCE_DIR}/${GPA_SRC_COMMON_REL_PATH}")
set(GPA_SRC_COUNTER_GENERATOR_REL_PATH                      "source/gpu_perf_api_counter_generator")
set(GPA_SRC_COUNTER_GENERATOR                               "${PROJECT_SOURCE_DIR}/${GPA_SRC_COUNTER_GENERATOR_REL_PATH}")
set(GPA_AUTOGEN_SRC_COUNTER_GENERATOR_REL_PATH              "source/auto_generated/gpu_perf_api_counter_generator")
set(GPA_AUTOGEN_SRC_COUNTER_GENERATOR                       "${PROJECT_SOURCE_DIR}/${GPA_AUTOGEN_SRC_COUNTER_GENERATOR_REL_PATH}")
set(GPA_SRC_COUNTERS_REL_PATH                               "source/gpu_perf_api_counters")
set(GPA_SRC_COUNTERS                                        "${PROJECT_SOURCE_DIR}/${GPA_SRC_COUNTERS_REL_PATH}")
set(GPA_SRC_GL_REL_PATH                                     "source/gpu_perf_api_gl")
set(GPA_SRC_GL                                              "${PROJECT_SOURCE_DIR}/${GPA_SRC_GL_REL_PATH}")
set(GPA_SRC_TESTS_REL_PATH                                  "source/gpu_perf_api_unit_tests")
set(GPA_SRC_TESTS                                           "${PROJECT_SOURCE_DIR}/${GPA_SRC_TESTS_REL_PATH}")
set(GPA_AUTOGEN_SRC_TESTS_REL_PATH                          "source/auto_generated/gpu_perf_api_unit_tests")
set(GPA_AUTOGEN_SRC_TESTS                                   "${PROJECT_SOURCE_DIR}/${GPA_AUTOGEN_SRC_TESTS_REL_PATH}")
set(GPA_AUTOGEN_PUBLIC_COUNTER_INPUT_FILES_REL_PATH         "source/auto_generated/public_counter_compiler_input_files")
set(GPA_AUTOGEN_PUBLIC_COUNTER_INPUT_FILES                  "${PROJECT_SOURCE_DIR}/${GPA_AUTOGEN_PUBLIC_COUNTER_INPUT_FILES_REL_PATH}")
set(GPA_SRC_THIRD_PARTY_REL_PATH                            "source/third_party")
set(GPA_SRC_THIRD_PARTY                                     "${PROJECT_SOURCE_DIR}/${GPA_SRC_THIRD_PARTY_REL_PATH}")

## List of common cmake files
set(CMAKE_COMMON_SRC_GLOBAL_CMAKE_MODULE                    ${GPA_SRC_THIRD_PARTY}/CMakeModules/Global-Common.cmake)
set(CMAKE_COMMON_SRC_GLOBAL_INTERNAL                        ${GPA_SRC_THIRD_PARTY}/CMakeModules/Global-Internal.cmake)
set(CMAKE_COMMON_SRC_GLOBAL_AMD_DX_EXT                      ${GPA_SRC_THIRD_PARTY}/AmdDxExt/Global-AmdDxExt.cmake)
set(CMAKE_COMMON_SRC_GLOBAL_AMD_VK_EXT                      ${GPA_SRC_THIRD_PARTY}/AmdVkExt/Global-AmdVkExt.cmake)
set(CMAKE_COMMON_LIB_GLOBAL_EXT_OPENGL                      ${GPA_SRC_THIRD_PARTY}/opengl/Global-OpenGL.cmake)
set(CMAKE_COMMON_LIB_GLOBAL_EXT_VULKAN                      ${GPA_SRC_THIRD_PARTY}/Vulkan/Global-Vulkan.cmake)

## Variables for installation.

set(GPA_INSTALL_PREFIX ${PROJECT_VERSION_MAJOR}_${PROJECT_VERSION_MINOR})
set(GPA_INSTALL_BINDIR ${GPA_INSTALL_PREFIX}/bin)
set(GPA_INSTALL_LIBDIR ${GPA_INSTALL_PREFIX}/lib)
set(GPA_INSTALL_INCLUDEDIR ${GPA_INSTALL_PREFIX}/include)

## Options controlling the behavior of clang tools

## clang-format can be run prior to the build, however clang-tidy relies on the
## presence of a compile-commands.json file, which is a build product.
option(
    GPA_RUN_CLANG_FORMAT
    "Run clang-format on source files prior to performing a build"
    OFF
)

option(
    GPA_RUN_CLANG_TIDY
    "Run clang-tidy on source files after a build completes"
    OFF
)

option(
    GPA_APPLY_LINT_FIXES
    "Apply fixes suggested by clang-format and/or clang-tidy fixes directly to source files"
    OFF
)

option(
    GPA_REQUIRE_CLEAN_LINT
    "Fail and stop a build if clang-format and/or clang-tidy suggests a fix"
    OFF
)
