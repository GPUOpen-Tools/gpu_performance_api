## Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

if(WIN32)
    include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})

    set(RESOURCE_COMPILER_COMMAND_ARG /I\"${WINDOWS_SDK_UM}\" /I\"${WINDOWS_SDK_SHARED}\" /I\"${GPA_SRC_COMMON}/\" /D AMDT_PROJECT_SUFFIX=\"${AMDTPlatformSuffix}$<$<CONFIG:DEBUG>:-d>\" /D AMDT_PROJECT_SUFFIX_W=L\"-d\" /D \"_DEBUG\" /l\"0x0409\" /nologo /fo \"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INTDIR}/${RESOURCE_FILE_NAME}.res\" \"${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FILE_NAME}.rc\")
    add_custom_command(TARGET ${GPA_PROJECT_NAME} PRE_LINK
                       COMMAND rc ${RESOURCE_COMPILER_COMMAND_ARG}
                       COMMENT "Compiling resource file ${RESOURCE_FILE_NAME}.rc")

    set_property(TARGET ${GPA_PROJECT_NAME} PROPERTY LINK_FLAGS \"${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_FILE_NAME}.res\")
endif()