## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

## GPA has only Debug and Release
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(DEPTH "./")

include(${GPA_CMAKE_MODULES_DIR}/CommonDefs.cmake)
include(${GPA_CMAKE_MODULES_DIR}/BuildFlags.cmake)

add_subdirectory(${GPA_SRC_COMMON} ${CMAKE_BINARY_DIR}/${GPA_SRC_COMMON_REL_PATH})
add_subdirectory(${GPA_SRC_COUNTER_GENERATOR} ${CMAKE_BINARY_DIR}/${GPA_SRC_COUNTER_GENERATOR_REL_PATH})
add_subdirectory(${GPA_SRC_COUNTERS} ${CMAKE_BINARY_DIR}/${GPA_SRC_COUNTERS_REL_PATH})

if(UNIX)
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(skipopencl ON)
        set(skiprocm ON)
    endif()
endif()

if(NOT ${skipopencl})
    add_subdirectory(${GPA_SRC_CL} ${CMAKE_BINARY_DIR}/${GPA_SRC_CL_REL_PATH})
else()
    message("CMake: Skipping OpenCL from the build")
endif()

if(WIN32)
    add_subdirectory(${GPA_SRC_DX} ${CMAKE_BINARY_DIR}/${GPA_SRC_DX_REL_PATH})

    if(NOT ${skipdx11})
        add_subdirectory(${GPA_SRC_DX11} ${CMAKE_BINARY_DIR}/${GPA_SRC_DX11_REL_PATH})
    else()
        message("CMake: Skipping DX11 from the build")
    endif()

    if(NOT ${skipdx12})
        add_subdirectory(${GPA_SRC_DX12} ${CMAKE_BINARY_DIR}/${GPA_SRC_DX12_REL_PATH})
    else()
        message("CMake: Skipping DX12 from the build")
    endif()

    add_subdirectory(${GPA_SRC_D3D12_COLOR_CUBE} ${CMAKE_BINARY_DIR}/${GPA_SRC_D3D12_COLOR_CUBE_REL_PATH})
    add_subdirectory(${GPA_SRC_PUBLIC_COUNTER_COMPILER} ${CMAKE_BINARY_DIR}/${GPA_SRC_PUBLIC_COUNTER_COMPILER_REL_PATH})
    add_subdirectory(${GPA_SRC_PUBLIC_COUNTER_INPUT_FILES} ${CMAKE_BINARY_DIR}/${GPA_SRC_PUBLIC_COUNTER_INPUT_FILES_REL_PATH})
endif()

if(NOT ${skiprocm})
    if(WIN32)
        if(NOT ${GPA_ALL_OPEN_SOURCE})
            add_subdirectory(${GPA_SRC_ROCM} ${CMAKE_BINARY_DIR}/${GPA_SRC_ROCM_REL_PATH})
        endif()
    else()
        add_subdirectory(${GPA_SRC_ROCM} ${CMAKE_BINARY_DIR}/${GPA_SRC_ROCM_REL_PATH})
    endif()
else()
    message("CMake: Skipping ROCm from the build")
endif()

if(NOT ${skipopengl})
    add_subdirectory(${GPA_SRC_GL} ${CMAKE_BINARY_DIR}/${GPA_SRC_GL_REL_PATH})
else()
    message("CMake: Skipping OpenGL from the build")
endif()

if(NOT ${skipvulkan})
    add_subdirectory(${GPA_SRC_VK} ${CMAKE_BINARY_DIR}/${GPA_SRC_VK_REL_PATH})
else()
    message("CMake: Skipping Vulkan from the build")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_subdirectory(${GPA_SRC_VK_COLOR_CUBE} ${CMAKE_BINARY_DIR}/${GPA_SRC_VK_COLOR_CUBE_REL_PATH})
endif()

if(NOT ${skiptests})
    # Build GoogleTest libs
    add_subdirectory(${GPA_SRC_GOOGLE_TEST} ${CMAKE_BINARY_DIR}/${GPA_SRC_GOOGLE_TEST_REL_PATH})
    add_subdirectory(${GPA_SRC_TESTS} ${CMAKE_BINARY_DIR}/${GPA_SRC_TESTS_REL_PATH})
else()
    message("CMake: Skipping Tests from the build")
endif()

if(NOT ${skipdocs})
    add_subdirectory(${GPA_SPHINX_DOCS} ${CMAKE_BINARY_DIR}/${GPA_SPHINX_DOCS_REL_PATH})
endif()



