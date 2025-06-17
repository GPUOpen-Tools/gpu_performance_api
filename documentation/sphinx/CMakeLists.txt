## Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.
find_program(SPHINX_EXECUTABLE sphinx-build)
if(NOT SPHINX_EXECUTABLE)
  message(FATAL_ERROR "SPHINX_EXECUTABLE (sphinx-build) is not found!")
endif()

file(GLOB DOC_FILES ${DOC_FILES} ${CMAKE_CURRENT_LIST_DIR}/source/*.rst)
file(GLOB DOC_FILES ${DOC_FILES} ${CMAKE_CURRENT_LIST_DIR}/source/*.txt)
file(GLOB DOC_FILES ${DOC_FILES} ${CMAKE_CURRENT_LIST_DIR}/source/*.py)
file(GLOB DOC_FILES ${DOC_FILES} ${CMAKE_CURRENT_LIST_DIR}/source/api_functions/*.rst)

set(GPA_DOC_OUTPUT_DIR "${GPA_OUTPUT_DIR}/documentation")

add_custom_target(SphinxDocsGenerator ALL
  COMMAND ${SPHINX_EXECUTABLE} -M html ${CMAKE_CURRENT_LIST_DIR}/source ${GPA_DOC_OUTPUT_DIR}
  COMMENT "Generating sphinx documentation."
  SOURCES ${DOC_FILES}
)

install(DIRECTORY "${GPA_DOC_OUTPUT_DIR}/html/" DESTINATION "${GPA_INSTALL_PREFIX}/help" COMPONENT GPUPerfAPI)
