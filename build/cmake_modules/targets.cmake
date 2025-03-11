## Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

## GPA has only Debug and Release
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(DEPTH "./")

include(${GPA_CMAKE_MODULES_DIR}/build_flags.cmake)

include(CTest)
enable_testing()

add_subdirectory(${GPA_SRC_COMMON} ${CMAKE_BINARY_DIR}/${GPA_SRC_COMMON_REL_PATH})
add_subdirectory(${GPA_SRC_COUNTER_GENERATOR} ${CMAKE_BINARY_DIR}/${GPA_SRC_COUNTER_GENERATOR_REL_PATH})
add_subdirectory(${GPA_SRC_COUNTERS} ${CMAKE_BINARY_DIR}/${GPA_SRC_COUNTERS_REL_PATH})

if(APPLE)
    return()
endif()

if(WIN32)
    add_subdirectory(${GPA_SRC_DX} ${CMAKE_BINARY_DIR}/${GPA_SRC_DX_REL_PATH})
    if(NOT ${skipdx11})
        add_subdirectory(${GPA_SRC_DX11} ${CMAKE_BINARY_DIR}/${GPA_SRC_DX11_REL_PATH})
    else()
        message(STATUS "Skipping DX11 in the build")
    endif()

    if(NOT ${skipdx12})
        add_subdirectory(${GPA_SRC_DX12} ${CMAKE_BINARY_DIR}/${GPA_SRC_DX12_REL_PATH})
    else()
        message(STATUS "Skipping DX12 in the build")
    endif()

    if(CMAKE_GENERATOR MATCHES "Visual Studio")
        if(NOT ${skipcsharp})
            add_subdirectory(${GPA_SRC_PUBLIC_COUNTER_COMPILER} ${CMAKE_BINARY_DIR}/${GPA_SRC_PUBLIC_COUNTER_COMPILER_REL_PATH})
        endif()
        add_subdirectory(${GPA_SRC_PUBLIC_COUNTER_INPUT_FILES} ${CMAKE_BINARY_DIR}/${GPA_SRC_PUBLIC_COUNTER_INPUT_FILES_REL_PATH})
    endif()
endif()

if(NOT ${skipopengl})
    add_subdirectory(${GPA_SRC_GL} ${CMAKE_BINARY_DIR}/${GPA_SRC_GL_REL_PATH})
else()
    message(STATUS "Skipping OpenGL in the build")
endif()

if(NOT ${skipvulkan})
    add_subdirectory(${GPA_SRC_VK} ${CMAKE_BINARY_DIR}/${GPA_SRC_VK_REL_PATH})
else()
    message(STATUS "Skipping Vulkan in the build")
endif()

if(NOT ${skiptests})
    # Build GoogleTest libs
    add_subdirectory(${GPA_SRC_GOOGLE_TEST} ${CMAKE_BINARY_DIR}/${GPA_SRC_GOOGLE_TEST_REL_PATH})
    add_subdirectory(${GPA_SRC_TESTS} ${CMAKE_BINARY_DIR}/${GPA_SRC_TESTS_REL_PATH})
else()
    message(STATUS "Skipping Tests in the build")
endif()

if(NOT ${skipdocs})
    add_subdirectory(${GPA_SPHINX_DOCS} ${CMAKE_BINARY_DIR}/${GPA_SPHINX_DOCS_REL_PATH})
endif()
