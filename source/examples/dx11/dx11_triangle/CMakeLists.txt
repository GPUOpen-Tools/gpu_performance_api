## Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../../../")

set(GPA_PROJECT_NAME D3D11Triangle)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/Common.cmake)
include (${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})

include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC})

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/dx11_triangle.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/dx11_triangle.h
            ${CMAKE_CURRENT_SOURCE_DIR}/../sample.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/../sample.h)

add_executable(${GPA_PROJECT_NAME} WIN32 ${SOURCES})
add_dependencies(${GPA_PROJECT_NAME} GPUPerfAPIDX11)
ADD_GPA_USER_COMPILE_DEFINITIONS()
target_link_libraries(${GPA_PROJECT_NAME} dxgi.lib
                                          d3d11.lib
                                          D3DCompiler.lib
                                          dxguid.lib)

# CMake copy command doesn't supports wildcards, we need to specify fully-qualified file names
add_custom_command(TARGET ${GPA_PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/dx11_triangle_shaders.hlsl ${GPA_OUTPUT_DIR}/$<CONFIG>/ VERBATIM)

set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER "Examples/DX11")

SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})

source_group("Shaders" FILES ${CMAKE_CURRENT_SOURCE_DIR}/dx_11_triangle_shaders.hlsl)