## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPIUnitTests)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/Common.cmake)

include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_AMD_DX_EXT})
include(${CMAKE_COMMON_SRC_GLOBAL_AMD_VK_EXT})
include(${GPA_CMAKE_MODULES_DIR}/GPA-Vulkan.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC_COMMON}
                    ${GPA_SRC_COUNTERS}
                    ${GPA_SRC_COUNTER_GENERATOR}
                    ${GPA_SRC_TESTS}/counters)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/APIErrorTests.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/CounterGeneratorCLTests.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/CounterGeneratorGLTests.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/CounterGeneratorTests.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/CounterGeneratorVKTests.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/CounterSchedulerTests.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GPAInterfaceLoaderTests.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GPUPerfAPILoaderTests.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GPUPerfAPIUnitTests.cpp
                 ${ADDITIONAL_UNIT_TEST_SOURCES})

if(WIN32)
    set(SOURCE_FILES ${SOURCE_FILES}
                     ${CMAKE_CURRENT_SOURCE_DIR}/CounterGeneratorDX11Tests.cpp
                     ${CMAKE_CURRENT_SOURCE_DIR}/CounterGeneratorDX12Tests.cpp)
endif()

if(NOT WIN32)
    set(SOURCE_FILES ${SOURCE_FILES}
                     ${CMAKE_CURRENT_SOURCE_DIR}/CounterGeneratorHSATests.cpp)
endif()

if(NOT DEFINED UNITTEST_COUNTER_DIR)
    set(UNITTEST_COUNTER_DIR ${CMAKE_CURRENT_LIST_DIR}/counters)
endif()

set(INTERNAL_COUNTERS_SRC
    ${UNITTEST_COUNTER_DIR}/GetInternalDerivedCounters.cpp)


set(HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/CounterGeneratorTests.h")

foreach(API GL DX11 DX12 VK CL HSA)
    if(NOT WIN32 AND (${API} STREQUAL "DX11" OR ${API} STREQUAL DX12))
        continue()
    endif()
    if(WIN32 AND (${API} STREQUAL "HSA"))
        continue()
    endif()
    include ("counters/Counters${API}.cmake")
    set(COUNTER_FILES ${COUNTER_FILES} ${PUBLIC_COUNTERS_TEST_API_HEADERS} ${PUBLIC_COUNTERS_TEST_API_SRC})
endforeach()

set(UTIL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/utils/GPUPerfAPILoader.h
               ${CMAKE_CURRENT_SOURCE_DIR}/utils/GPUPerfAPILoader.cpp)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${COUNTER_FILES}
    ${UTIL_FILES}
    ${INTERNAL_COUNTERS_SRC})

if(WIN32)
    set(ADDITIONAL_COMPILE_OPTIONS ${ADDITIONAL_COMPILE_OPTIONS}
                                     -wd4389)
endif()

add_compile_options(${ADDITIONAL_COMPILE_OPTIONS})
link_directories(${ADDITIONAL_LINK_DIRECTORIES})
add_executable(${GPA_PROJECT_NAME} ${SOURCES})
ADD_GPA_USER_COMPILE_DEFINITIONS()
target_link_libraries(${GPA_PROJECT_NAME}
                      GPUPerfAPI-Common
                      GPUPerfAPICounterGenerator
                      gtest
                      $<$<PLATFORM_ID:Linux>:dl>
                      $<$<PLATFORM_ID:Linux>:pthread>)

ADD_LINKER_FLAGS()
set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER Tests)
SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})

if(WIN32)
    source_group("Utils" FILES ${UTIL_FILES})

    foreach(API GL DX11 DX12 VK CL HSA)
        include ("counters/Counters${API}.cmake")
        source_group("Source Files\\GeneratedTestFiles\\${API}" FILES ${PUBLIC_COUNTERS_TEST_API_HEADERS})
        source_group("Source Files\\GeneratedTestFiles\\${API}" FILES ${PUBLIC_COUNTERS_TEST_API_SRC})
        source_group("Source Files\\GeneratedTestFiles\\${API}" FILES ${SW_COUNTERS_TEST_HEADERS})
        source_group("Source Files\\GeneratedTestFiles\\${API}" FILES ${SW_COUNTERS_TEST_SRC})
    endforeach(API)
endif()

