## Copyright (c) 2018-2022 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.19)

## Define the GPA version
set(GPA_MAJOR_VERSION 3)
set(GPA_MINOR_VERSION 13)
set(GPA_UPDATE_VERSION 1)

if(NOT DEFINED GPA_BUILD_NUMBER)
    set(GPA_BUILD_NUMBER 0)
endif()

if(NOT DEFINED GPA_ROOT)
    file(REAL_PATH "${CMAKE_CURRENT_LIST_DIR}/../.." GPA_ROOT)
endif()

if(NOT DEFINED GPA_OUTPUT_DIR)
    set(GPA_OUTPUT_DIR ${GPA_ROOT}/output)
endif()

## Set the Common Directories
set(COMMON_DIR                                              "${GPA_ROOT}/external")
set(COMMON_DIR_LIB                                          "${COMMON_DIR}/Lib")
set(COMMON_DIR_SRC                                          "${COMMON_DIR}/Src")
set(GPA_PUBLIC_HEADER_REL_PATH                              "include")
set(GPA_PUBLIC_HEADER                                       "${GPA_ROOT}/${GPA_PUBLIC_HEADER_REL_PATH}")
set(GPA_SRC                                                 "${GPA_ROOT}/source")
set(GPA_SRC_COMMON_REL_PATH                                 "source/gpu_perf_api_common")
set(GPA_SRC_COMMON                                          "${GPA_ROOT}/${GPA_SRC_COMMON_REL_PATH}")
set(GPA_SRC_COUNTER_GENERATOR_REL_PATH                      "source/gpu_perf_api_counter_generator")
set(GPA_SRC_COUNTER_GENERATOR                               "${GPA_ROOT}/${GPA_SRC_COUNTER_GENERATOR_REL_PATH}")
set(GPA_AUTOGEN_SRC_COUNTER_GENERATOR_REL_PATH              "source/auto_generated/gpu_perf_api_counter_generator")
set(GPA_AUTOGEN_SRC_COUNTER_GENERATOR                       "${GPA_ROOT}/${GPA_AUTOGEN_SRC_COUNTER_GENERATOR_REL_PATH}")
set(GPA_SRC_COUNTERS_REL_PATH                               "source/gpu_perf_api_counters")
set(GPA_SRC_COUNTERS                                        "${GPA_ROOT}/${GPA_SRC_COUNTERS_REL_PATH}")
set(GPA_SRC_GL_REL_PATH                                     "source/gpu_perf_api_gl")
set(GPA_SRC_GL                                              "${GPA_ROOT}/${GPA_SRC_GL_REL_PATH}")
set(GPA_SRC_DX_REL_PATH                                     "source/gpu_perf_api_dx")
set(GPA_SRC_DX                                              "${GPA_ROOT}/${GPA_SRC_DX_REL_PATH}")
set(GPA_SRC_DX11_REL_PATH                                   "source/gpu_perf_api_dx11")
set(GPA_SRC_DX11                                            "${GPA_ROOT}/${GPA_SRC_DX11_REL_PATH}")
set(GPA_SRC_DX12_REL_PATH                                   "source/gpu_perf_api_dx12")
set(GPA_SRC_DX12                                            "${GPA_ROOT}/${GPA_SRC_DX12_REL_PATH}")
set(GPA_SRC_VK_REL_PATH                                     "source/gpu_perf_api_vk")
set(GPA_SRC_VK                                              "${GPA_ROOT}/${GPA_SRC_VK_REL_PATH}")
set(GPA_SRC_CL_REL_PATH                                     "source/gpu_perf_api_cl")
set(GPA_SRC_CL                                              "${GPA_ROOT}/${GPA_SRC_CL_REL_PATH}")
set(GPA_SRC_TESTS_REL_PATH                                  "source/gpu_perf_api_unit_tests")
set(GPA_SRC_TESTS                                           "${GPA_ROOT}/${GPA_SRC_TESTS_REL_PATH}")
set(GPA_AUTOGEN_SRC_TESTS_REL_PATH                          "source/auto_generated/gpu_perf_api_unit_tests")
set(GPA_AUTOGEN_SRC_TESTS                                   "${GPA_ROOT}/${GPA_AUTOGEN_SRC_TESTS_REL_PATH}")
set(GPA_SRC_PUBLIC_COUNTER_COMPILER_REL_PATH                "source/public_counter_compiler")
set(GPA_SRC_PUBLIC_COUNTER_COMPILER                         "${GPA_ROOT}/${GPA_SRC_PUBLIC_COUNTER_COMPILER_REL_PATH}")
set(GPA_SRC_PUBLIC_COUNTER_INPUT_FILES_REL_PATH             "source/public_counter_compiler_input_files")
set(GPA_SRC_PUBLIC_COUNTER_INPUT_FILES                      "${GPA_ROOT}/${GPA_SRC_PUBLIC_COUNTER_INPUT_FILES_REL_PATH}")
set(GPA_SRC_EXAMPLE_COMMON_REL_PATH                         "source/examples/common")
set(GPA_SRC_EXAMPLE_COMMON_PATH                             "${GPA_ROOT}/${GPA_SRC_EXAMPLE_COMMON_REL_PATH}")
set(GPA_SRC_D3D12_COLOR_CUBE_REL_PATH                       "source/examples/dx12/dx12_color_cube")
set(GPA_SRC_D3D12_COLOR_CUBE                                "${GPA_ROOT}/${GPA_SRC_D3D12_COLOR_CUBE_REL_PATH}")
set(GPA_SRC_VK_COLOR_CUBE_REL_PATH                          "source/examples/vulkan/vk_color_cube")
set(GPA_SRC_VK_COLOR_CUBE                                   "${GPA_ROOT}/${GPA_SRC_VK_COLOR_CUBE_REL_PATH}")
set(GPA_SPHINX_DOCS_REL_PATH                                "docs/sphinx")
set(GPA_SPHINX_DOCS                                         "${GPA_ROOT}/${GPA_SPHINX_DOCS_REL_PATH}")
set(GPA_SRC_GOOGLE_TEST_REL_PATH                            "source/google_test")
set(GPA_SRC_GOOGLE_TEST                                     "${GPA_ROOT}/${GPA_SRC_GOOGLE_TEST_REL_PATH}")
set(GPA_AUTOGEN_PUBLIC_COUNTER_INPUT_FILES_REL_PATH         "source/auto_generated/public_counter_compiler_input_files")
set(GPA_AUTOGEN_PUBLIC_COUNTER_INPUT_FILES                  "${GPA_ROOT}/${GPA_AUTOGEN_PUBLIC_COUNTER_INPUT_FILES_REL_PATH}")
set(GPA_SRC_GL_TRIANGLE_REL_PATH                            "source/examples/opengl/gl_triangle")
set(GPA_SRC_GL_TRIANGLE                                     "${GPA_ROOT}/${GPA_SRC_GL_TRIANGLE_REL_PATH}")
set(GPA_SRC_D3D11_TRIANGLE_REL_PATH                         "source/examples/dx11/dx11_triangle")
set(GPA_SRC_D3D11_TRIANGLE                                  "${GPA_ROOT}/${GPA_SRC_D3D11_TRIANGLE_REL_PATH}")
set(GPA_SRC_THIRD_PARTY_REL_PATH                            "source/third_party")
set(GPA_SRC_THIRD_PARTY                                     "${GPA_ROOT}/${GPA_SRC_THIRD_PARTY_REL_PATH}")

set(GOOGLETEST_DIR                                          ${COMMON_DIR_LIB}/Ext/GoogleTest)

## List of common cmake files
set(CMAKE_COMMON_SRC_GLOBAL_CMAKE_MODULE                    ${GPA_SRC_THIRD_PARTY}/CMakeModules/Global-Common.cmake)
set(CMAKE_COMMON_SRC_GLOBAL_INTERNAL                        ${GPA_SRC_THIRD_PARTY}/CMakeModules/Global-Internal.cmake)
set(CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL                        ${COMMON_DIR_SRC}/ADLUtil/Global-ADLUtil.cmake)
set(CMAKE_COMMON_SRC_GLOBAL_AMD_DX_EXT                      ${GPA_SRC_THIRD_PARTY}/AmdDxExt/Global-AmdDxExt.cmake)
set(CMAKE_COMMON_SRC_GLOBAL_AMD_VK_EXT                      ${GPA_SRC_THIRD_PARTY}/AmdVkExt/Global-AmdVkExt.cmake)
set(CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO                     ${COMMON_DIR_SRC}/DeviceInfo/Global-DeviceInfo.cmake)
set(CMAKE_COMMON_SRC_GLOBAL_DYNAMIC_LIBRARY_MODULE          ${COMMON_DIR_SRC}/DynamicLibraryModule/Global-DynamicLibraryModule.cmake)
set(CMAKE_COMMON_SRC_GLOBAL_TSINGLETON                      ${COMMON_DIR_SRC}/TSingleton/Global-TSingleton.cmake)

set(CMAKE_COMMON_LIB_GLOBAL_AMD_ADL                         ${COMMON_DIR_LIB}/AMD/ADL/Global-ADL.cmake)
set(CMAKE_COMMON_LIB_GLOBAL_AMD_OPENCL_NO_LIB               ${COMMON_DIR_LIB}/AMD/APPSDK/Global-OpenCL-NoLib.cmake)
set(CMAKE_COMMON_LIB_GLOBAL_AMD_OPENCL                      ${COMMON_DIR_LIB}/AMD/APPSDK/Global-OpenCL.cmake)
set(CMAKE_COMMON_LIB_GLOBAL_EXT_OPENGL                      ${COMMON_DIR_LIB}/Ext/OpenGL/Global-OpenGL.cmake)
set(CMAKE_COMMON_LIB_GLOBAL_EXT_VULKAN                      ${GPA_SRC_THIRD_PARTY}/Vulkan/Global-Vulkan.cmake)
set(CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK                 ${COMMON_DIR_LIB}/Ext/Windows-Kits/Global-WindowsSDK.cmake)

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
