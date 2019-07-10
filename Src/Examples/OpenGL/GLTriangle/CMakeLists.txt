## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GLTriangle)
set(ProjectName ${GPA_PROJECT_NAME})


include (${GPA_CMAKE_MODULES_DIR}/Common.cmake)
include_directories(${GPA_SRC_COMMON})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/GLTriangle.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/GPAHelper.h
            ${CMAKE_CURRENT_SOURCE_DIR}/GPAHelper.cpp)

add_executable(${GPA_PROJECT_NAME} WIN32 ${SOURCES})
add_dependencies(${GPA_PROJECT_NAME} GPUPerfAPIGL)
ADD_GPA_USER_COMPILE_DEFINITIONS()
if(WIN32)
    target_link_libraries(${GPA_PROJECT_NAME}
                            opengl32)
else()
    set_target_properties(${GPA_PROJECT_NAME} PROPERTIES LINK_FLAGS "-L/opt/amdgpu-pro/lib/x86_64-linux-gnu/")
    target_link_libraries(${GPA_PROJECT_NAME} GL dl X11)
endif()

set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER "Examples/OpenGL")
SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})



