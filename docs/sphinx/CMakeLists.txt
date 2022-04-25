## Copyright (c) 2018-2022 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../")

find_program(SPHINX_EXECUTABLE sphinx-build)
if(NOT SPHINX_EXECUTABLE)
  message(FATAL_ERROR "SPHINX_EXECUTABLE (sphinx-build) is not found!")
endif()

set(GPA_PROJECT_NAME SphinxDocsGenerator)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/common.cmake)

file(GLOB DOC_FILES ${DOC_FILES} ${CMAKE_CURRENT_LIST_DIR}/source/*.rst)
file(GLOB DOC_FILES ${DOC_FILES} ${CMAKE_CURRENT_LIST_DIR}/source/*.txt)
file(GLOB DOC_FILES ${DOC_FILES} ${CMAKE_CURRENT_LIST_DIR}/source/*.py)
file(GLOB DOC_FILES ${DOC_FILES} ${CMAKE_CURRENT_LIST_DIR}/source/api_functions/*.rst)

set(SOURCES ${DOC_FILES})

ADD_STATIC_LIBRARY(${GPA_PROJECT_NAME} ${SOURCES})
target_link_libraries(${GPA_PROJECT_NAME}
                      GPUPerfAPI-Common)

add_custom_command(TARGET ${GPA_PROJECT_NAME} PRE_BUILD
                   COMMAND ${SPHINX_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/source ${GPA_OUTPUT_DIR}/docs/
                   COMMENT "Generating sphinx documentation..." )
