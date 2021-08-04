## Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

## GPA has only Debug and Release
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(DEPTH "./")

include(${GPA_CMAKE_MODULES_DIR}/defs.cmake)
include(${GPA_CMAKE_MODULES_DIR}/build_flags.cmake)

if(UNIX)
    set(skipopencl ON)
endif()

add_subdirectory(${GPA_SRC_COMMON} ${CMAKE_BINARY_DIR}/${GPA_SRC_COMMON_REL_PATH})
add_subdirectory(${GPA_SRC_COUNTER_GENERATOR} ${CMAKE_BINARY_DIR}/${GPA_SRC_COUNTER_GENERATOR_REL_PATH})
add_subdirectory(${GPA_SRC_COUNTERS} ${CMAKE_BINARY_DIR}/${GPA_SRC_COUNTERS_REL_PATH})

if(APPLE)
    return()
endif()

if(NOT ${skipopencl})
    add_subdirectory(${GPA_SRC_CL} ${CMAKE_BINARY_DIR}/${GPA_SRC_CL_REL_PATH})
else()
    message(STATUS "Skipping OpenCL from the build")
endif()

if(WIN32)
    add_subdirectory(${GPA_SRC_DX} ${CMAKE_BINARY_DIR}/${GPA_SRC_DX_REL_PATH})

    if(NOT ${skipdx11})
        add_subdirectory(${GPA_SRC_DX11} ${CMAKE_BINARY_DIR}/${GPA_SRC_DX11_REL_PATH})
        if(NOT ${skipsamples})
            add_subdirectory(${GPA_SRC_D3D11_TRIANGLE} ${CMAKE_BINARY_DIR}/${GPA_SRC_D3D11_TRIANGLE_REL_PATH})
        else()
            message(STATUS "Skipping DX11 sample from the build")
        endif()
    else()
        message(STATUS "Skipping DX11 from the build")
    endif()

    if(NOT ${skipdx12})
        add_subdirectory(${GPA_SRC_DX12} ${CMAKE_BINARY_DIR}/${GPA_SRC_DX12_REL_PATH})
        if(NOT ${skipsamples})
            add_subdirectory(${GPA_SRC_D3D12_COLOR_CUBE} ${CMAKE_BINARY_DIR}/${GPA_SRC_D3D12_COLOR_CUBE_REL_PATH})
        else()
            message(STATUS "Skipping DX12 sample from the build")
        endif()
    else()
        message(STATUS "Skipping DX12 from the build")
    endif()

    add_subdirectory(${GPA_SRC_PUBLIC_COUNTER_COMPILER} ${CMAKE_BINARY_DIR}/${GPA_SRC_PUBLIC_COUNTER_COMPILER_REL_PATH})
    add_subdirectory(${GPA_SRC_PUBLIC_COUNTER_INPUT_FILES} ${CMAKE_BINARY_DIR}/${GPA_SRC_PUBLIC_COUNTER_INPUT_FILES_REL_PATH})
endif()

if(NOT ${skipopengl})
    add_subdirectory(${GPA_SRC_GL} ${CMAKE_BINARY_DIR}/${GPA_SRC_GL_REL_PATH})
    if(NOT ${skipsamples})
        if(WIN32)
            add_subdirectory(${GPA_SRC_GL_TRIANGLE} ${CMAKE_BINARY_DIR}/${GPA_SRC_GL_TRIANGLE_REL_PATH})
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
            add_subdirectory(${GPA_SRC_GL_TRIANGLE} ${CMAKE_BINARY_DIR}/${GPA_SRC_GL_TRIANGLE_REL_PATH})
        endif()
    else()
         message(STATUS "Skipping OpenGL sample from the build")
    endif()
else()
    message(STATUS "Skipping OpenGL from the build")
endif()

if(NOT ${skipvulkan})
    add_subdirectory(${GPA_SRC_VK} ${CMAKE_BINARY_DIR}/${GPA_SRC_VK_REL_PATH})
    if(NOT ${skipsamples})
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            add_subdirectory(${GPA_SRC_VK_COLOR_CUBE} ${CMAKE_BINARY_DIR}/${GPA_SRC_VK_COLOR_CUBE_REL_PATH})
        endif()
    else()
        message(STATUS "Skipping Vulkan sample from the build")
    endif()
else()
    message(STATUS "Skipping Vulkan from the build")
endif()

if(NOT ${skiptests})
    # Build GoogleTest libs
    add_subdirectory(${GPA_SRC_GOOGLE_TEST} ${CMAKE_BINARY_DIR}/${GPA_SRC_GOOGLE_TEST_REL_PATH})
    add_subdirectory(${GPA_SRC_TESTS} ${CMAKE_BINARY_DIR}/${GPA_SRC_TESTS_REL_PATH})
else()
    message(STATUS "Skipping Tests from the build")
endif()

if(NOT ${skipdocs})
    add_subdirectory(${GPA_SPHINX_DOCS} ${CMAKE_BINARY_DIR}/${GPA_SPHINX_DOCS_REL_PATH})
endif()



