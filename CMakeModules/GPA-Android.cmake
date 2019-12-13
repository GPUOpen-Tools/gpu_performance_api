## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

if (NOT DEFINED ENV{ANDROID_SDK})
    message(FATAL_ERROR "ANDROID_SDK is not defined")
endif()

if (NOT DEFINED ENV{ANDROID_NDK})
    message(FATAL_ERROR "ANDROID_NDK is not defined")
endif()

if (NOT DEFINED ENV{JAVA_HOME})
    message(FATAL_ERROR "JAVA_HOME is not defined")
endif()

# Android variables
set(ANDROID_NDK_PATH $ENV{ANDROID_NDK})
set(ANDROID_SDK_PATH $ENV{ANDROID_SDK})
set(ANDROID_NDK_SHADER_TOOL_PATH ${ANDROID_NDK_PATH}/shader-tools/linux-x86_64)
set(JAVA_HOME_PATH $ENV{JAVA_HOME})

if (NOT DEFINED ANDROID_PLATFORM)
    set(ANDROID_PLATFORM 24)
    message(STATUS "GPA: Using Android platform level ${ANDROID_PLATFORM}")
endif()

if (NOT DEFINED ANDROID_ABI)
    set(ANDROID_ABI x86_64)
    message(STATUS "GPA: Using Android abi ${ANDROID_ABI}")
endif()

if (NOT DEFINED ANDROID_NATIVE_API_LEVEL)
    set(ANDROID_NATIVE_API_LEVEL 24)
    message(STATUS "GPA: Using Android native api level ${ANDROID_NATIVE_API_LEVEL}")
endif()

if(NOT DEFINED ANDROID_STL)
    set(ANDROID_STL c++_static)
    message(STATUS "GPA: Using Android ${ANDROID_STL} C/C++ STL")
endif()

set(ANDROID_TAGET_PLATFORM_ID ${ANDROID_PLATFORM})
set(ANDROID_NDK_NATIVE_GLUE_DIR "${ANDROID_NDK_PATH}/sources/android/native_app_glue")
set(ANDROID_NDK_INC "${ANDROID_NDK_PATH}/sysroot/usr/include")
set(ANDROID_TARGET_PLATFORM ${ANDROID_SDK_PATH}/platforms/android-${ANDROID_TAGET_PLATFORM_ID})
set(ANDROID_TARGET_JAR ${ANDROID_TARGET_PLATFORM}/android.jar)
set(ANDROID_BUILD_TOOLS ${ANDROID_SDK_PATH}/build-tools/24.0.3)

## Build configurations
set(CMAKE_TOOLCHAIN_FILE ${ANDROID_NDK_PATH}/build/cmake/android.toolchain.cmake)
set(USE_DEFAULT_COMPILER OFF)
set(USE_DEFAULT_OUTPUT_DIRECTORY OFF)
set(GPA_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Output/Android)

if(${AMDT_INTERNAL_BUILD_FLAG})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GPA_OUTPUT_DIR}${AMDTInternalSuffix})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GPA_OUTPUT_DIR}${AMDTInternalSuffix})
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GPA_OUTPUT_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GPA_OUTPUT_DIR})
endif()

set(ANDROID_INCLUDE_DIRECTORIES ${ANDROID_NDK_NATIVE_GLUE_DIR}
                                ${ANDROID_NDK_INC})
set(ANDROID_LIBS log android)