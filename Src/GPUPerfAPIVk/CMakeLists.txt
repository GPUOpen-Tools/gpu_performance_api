## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPIVK)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/Common.cmake)

include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_AMD_VK_EXT})
include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})
include(${GPA_CMAKE_MODULES_DIR}/GPA-Vulkan.cmake)

INCLUDE_ADDITIONAL_MODULE()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTER_GENERATOR})

set(HEADER_FILES ${GPA_SRC_COMMON}/GPUPerfAPI-VK.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkCommandListSwQueries.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkCommandListSWQueryGroup.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkEntrypoints.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPACommandList.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPAContext.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPAHardwareSample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPAImplementor.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPAPass.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPASample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPASession.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPASoftwareSample.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkIncludes.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkSoftwareCountersResults.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkUtils.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/VkCommandListSwQueries.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkCommandListSWQueryGroup.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkEntrypoints.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPACommandList.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPAContext.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPAHardwareSample.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPAImplementor.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPAPass.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPASample.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPASession.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkGPASoftwareSample.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/VkUtils.cpp)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

ADD_SHARED_LIBRARY(${GPA_PROJECT_NAME} ${DEPTH}/GPAFunctionExports.def)
INCLUDE_WIN_RESOURCE()

target_link_libraries(${GPA_PROJECT_NAME}
                      ${GPA_COMMON_LINK_ARCHIVE_FLAG}
                      GPUPerfAPI-Common
                      ${GPA_COMMON_LINK_NO_ARCHIVE_FLAG}
                      GPUPerfAPICounterGenerator)

ADD_LINKER_FLAGS()






