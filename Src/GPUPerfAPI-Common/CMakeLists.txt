## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPI-Common)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/Common.cmake)
include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_DYNAMIC_LIBRARY_MODULE})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(ADDITIONAL_SOURCE
    ${ADL_UTIL_DIR}/ADLUtil.cpp
    ${DYNAMIC_LIBRARY_MODULE}/DynamicLibraryModule.cpp
    ${DEVICE_INFO}/DeviceInfoUtils.cpp
    ${ADDITIONAL_DEVICEINFO_SOURCES})

set(ADDITIONAL_SOURCE_HEADERS
    ${ADL_UTIL_DIR}/ADLUtil.h
    ${DYNAMIC_LIBRARY_MODULE}/DynamicLibraryModule.h
    ${DEVICE_INFO}/DeviceInfo.h
    ${DEVICE_INFO}/DeviceInfoUtils.h)

set(PUBLIC_HEADERS
    GPAFunctions.h
    GPAInterfaceLoader.h
    GPUPerfAPI.h
    GPUPerfAPIFunctionTypes.h
    GPUPerfAPIStub.h
    GPUPerfAPITypes.h
    GPUPerfAPI-VK.h)

set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Adapter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/APIRTModuleLoader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CircularBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/DXGetAMDDeviceInfo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPACommandList.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPACommonDefs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAContext.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAContextCounterMediator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPACounterDataRequestManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPACustomHWValidationManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAHWInfo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAImplementor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAPass.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAProfiler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPASample.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPASession.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAUniqueObject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAVersion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IGPACommandList.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IGPAContext.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IGPAImplementor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IGPAInterfaceTrait.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IGPASession.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Logging.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.h)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/GPACommandList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAContextCounterMediator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPACustomHWValidationManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAHWInfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAImplementor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAPass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAProfiler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPASample.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPASession.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPAUniqueObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPUPerfAPI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logging.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.cpp)

if(WIN32)
    set(SOURCE_FILES ${SOURCE_FILES}
                     ${CMAKE_CURRENT_SOURCE_DIR}/Adapter.cpp)
    set(LINK_LIBS dxgi.lib)
endif()

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${ADDITIONAL_SOURCE}
    ${ADDITIONAL_SOURCE_HEADERS}
    ${PUBLIC_HEADERS})

ADD_STATIC_LIBRARY(${GPA_PROJECT_NAME})
target_link_libraries(${GPA_PROJECT_NAME}
                      ${LINK_LIBS})

ADD_LINKER_FLAGS()

if(WIN32)
    source_group("Public Header Files" FILES ${PUBLIC_HEADERS})
endif()