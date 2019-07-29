## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../../../")

set(GPA_PROJECT_NAME VkColorCube)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/Common.cmake)
include(${GPA_CMAKE_MODULES_DIR}/GPA-Vulkan.cmake)

include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC_COMMON})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/vkcolorcube.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/vkcolorcube.h
            ${CMAKE_CURRENT_SOURCE_DIR}/GPAHelper.h
            ${CMAKE_CURRENT_SOURCE_DIR}/GPAHelper.cpp)

add_definitions(${ADDITIONAL_DEFINTIONS})
link_directories(${ADDITIONAL_LINK_DIRECTORIES})
add_executable(${GPA_PROJECT_NAME} WIN32 ${SOURCES})
add_dependencies(${GPA_PROJECT_NAME} GPUPerfAPIVK)
ADD_GPA_USER_COMPILE_DEFINITIONS()
target_link_libraries(${GPA_PROJECT_NAME}
                      ${VK_LIB}
                      $<$<PLATFORM_ID:Linux>:dl>
                      $<$<PLATFORM_ID:Linux>:xcb>)

ADD_LINKER_FLAGS()

if(WIN32)
    add_custom_command(TARGET ${GPA_PROJECT_NAME} POST_BUILD
                       COMMAND CompileShaders.bat ${GPA_OUTPUT_DIR}/$<CONFIG>/
                       BYPRODUCTS vkcolorcubeshader.vert.spv vkcolorcubeshader.frag.spv
                       WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                       COMMENT "Compiling Vulkan Shaders vkcolorcubeshader.vert vkcolorcubeshader.frag vkcolorcubewireframeshader.frag")
else()
    add_custom_command(TARGET ${GPA_PROJECT_NAME} PRE_BUILD
                       COMMAND ${CMAKE_CURRENT_LIST_DIR}/CompileShaders.sh ${GPA_OUTPUT_DIR}/$<CONFIG>/ ${VK_TOOLS_DIR}
                       BYPRODUCTS vkcolorcubeshader.vert.spv vkcolorcubeshader.frag.spv
                       WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                       COMMENT "Compiling Vulkan Shaders vkcolorcubeshader.vert vkcolorcubeshader.frag vkcolorcubewireframeshader.frag")
endif()

set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER "Examples/Vulkan")

SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})