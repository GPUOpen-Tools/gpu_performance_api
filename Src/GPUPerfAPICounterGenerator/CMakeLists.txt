## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME GPUPerfAPICounterGenerator)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/Common.cmake)
include(${CMAKE_COMMON_LIB_GLOBAL_AMD_ADL})
include(${CMAKE_COMMON_LIB_GLOBAL_EXT_OPENGL})
include(${CMAKE_COMMON_SRC_GLOBAL_ADL_UTIL})
include(${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})
include(${CMAKE_COMMON_SRC_GLOBAL_DEVICE_INFO})
include(${CMAKE_COMMON_SRC_GLOBAL_AMD_DX_EXT})
include(${CMAKE_COMMON_SRC_GLOBAL_AMD_VK_EXT})
include(${CMAKE_COMMON_LIB_GLOBAL_EXT_WINDOWS_SDK})
include(${GPA_CMAKE_MODULES_DIR}/GPA-Vulkan.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_SRC_COMMON})

set(INTERNALLY_EXPOSED_HEADER_FILES
    GPACounterGenerator.h
    IGPACounterAccessor.h
    IGPACounterScheduler.h)

set(COUNTER_GENERATORS_HEADERS
    GPACounterGeneratorBase.h
    GPACounterGeneratorSchedulerManager.h
    GPASwCounterManager.h)

set(COUNTER_GENERATORS_SRC
    GPACounterGenerator.cpp
    GPACounterGeneratorBase.cpp
    GPACounterGeneratorSchedulerManager.cpp
    GPASwCounterManager.cpp)

set(COUNTER_SCHEDULERS_HEADERS
    GPACounterSchedulerBase.h)

set(COUNTER_SCHEDULERS_SRC
    GPACounterSchedulerBase.cpp)

set(INTERNAL_COUNTERS_HEADERS
    GPACounterGroupAccessor.h
    GPAInternalCounter.h
    GPAInternalCountersGfx6.h
    GPAInternalCountersGfx7.h
    GPAInternalCountersGfx8.h
    GPAInternalCountersGfx8_Baffin.h
    GPAInternalCountersGfx8_Carrizo.h
    GPAInternalCountersGfx8_Ellesmere.h
    GPAInternalCountersGfx8_Fiji.h
    GPAInternalCountersGfx8_Iceland.h
    GPAInternalCountersGfx8_Tonga.h
    GPAInternalCountersGfx9.h
    GPAInternalCountersGfx9_Placeholder4.h
    GPAInternalCountersGfx9_Gfx906.h)

if(NOT DEFINED COUNTER_DIR)
    set(COUNTER_DIR ${CMAKE_CURRENT_LIST_DIR})
endif()

set(INTERNAL_COUNTERS_SRC
    ${COUNTER_DIR}/GPAInternalCountersGfx6.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx7.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx8.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx8_Baffin.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx8_Carrizo.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx8_Ellesmere.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx8_Fiji.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx8_Iceland.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx8_Tonga.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx9.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx9_Placeholder4.cpp
    ${COUNTER_DIR}/GPAInternalCountersGfx9_Gfx906.cpp
    ${COUNTER_DIR}/LoadInternalCounters.cpp
    ${ADDITIONAL_COUNTER_GEN_SOURCES})

set(PUBLIC_COUNTERS_HEADERS
    GPADerivedCounters.h)

set(PUBLIC_COUNTERS_SRC
    GPADerivedCounters.cpp)

set(COUNTER_SPLITTING_ALGO_HEADERS
    GPASplitCounterFactory.h
    GPASplitCountersConsolidated.h
    GPASplitCountersInterfaces.h
    GPASplitCountersMaxPerPass.h
    GPASplitCountersOnePerPass.h)

set(COUNTERS_HEADER
    GPAHardwareCounters.h
    GPASoftwareCounters.h)

set(HEADER_FILES ${INTERNALLY_EXPOSED_HEADER_FILES}
                 ${COUNTER_GENERATORS_HEADERS}
                 ${COUNTER_SCHEDULERS_HEADERS}
                 ${INTERNAL_COUNTERS_HEADERS}
                 ${PUBLIC_COUNTERS_HEADERS}
                 ${COUNTER_SPLITTING_ALGO_HEADERS}
                 ${COUNTERS_HEADER})

set(SOURCE_FILES ${COUNTER_GENERATORS_SRC}
                 ${COUNTER_SCHEDULERS_SRC}
                 ${INTERNAL_COUNTERS_SRC}
                 ${PUBLIC_COUNTERS_SRC})

foreach(API GL DX11 DX12 VK CL HSA)
    if(NOT WIN32 AND (${API} STREQUAL "DX11" OR ${API} STREQUAL DX12))
        continue()
    endif()
    if(WIN32 AND (${API} STREQUAL "HSA"))
        continue()
    endif()
    include ("CounterGenerator${API}.cmake")
    set(HEADER_FILES ${HEADER_FILES} ${COUNTER_GENERATORS_API_HEADERS}
                                     ${COUNTER_SCHEDULERS_API_HEADERS}
                                     ${INTERNAL_COUNTERS_API_HEADERS}
                                     ${PUBLIC_COUNTERS_API_HEADERS})

    set(SOURCE_FILES ${SOURCE_FILES} ${COUNTER_GENERATORS_API_SRC}
                                     ${COUNTER_SCHEDULERS_API_SRC}
                                     ${INTERNAL_COUNTERS_API_SRC}
                                     ${PUBLIC_COUNTERS_API_SRC})
endforeach(API)

set(SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES})

if(WIN32)
   add_compile_options(/bigobj)
else()
    add_compile_options(-Wno-write-strings)
endif()

ADD_STATIC_LIBRARY(${GPA_PROJECT_NAME})
ADD_LINKER_FLAGS()

if(WIN32)
    set(COUNTER_GENERATOR_FILTER CounterGenerators)
    set(COUNTER_SCHEDULER_FILTER CounterSchedulers)
    set(INTERNAL_COUNTER_FILTER InternalCounters)
    set(PUBLIC_COUNTER_FILTER PublicCounters)

    source_group("Internally Exposed Header Files" FILES ${INTERNALLY_EXPOSED_HEADER_FILES})
    source_group("Internally Exposed Header Files" FILES ${INTERNALLY_EXPOSED_HEADER_FILES})
    source_group("Internally Exposed Header Files" FILES ${INTERNALLY_EXPOSED_HEADER_FILES})
    source_group("Internally Exposed Header Files" FILES ${INTERNALLY_EXPOSED_HEADER_FILES})
    source_group("Internally Exposed Header Files" FILES ${INTERNALLY_EXPOSED_HEADER_FILES})

    source_group("Source Files\\${COUNTER_GENERATOR_FILTER}" FILES ${COUNTER_GENERATORS_HEADERS} ${COUNTER_GENERATORS_SRC})
    source_group("Source Files\\${COUNTER_SCHEDULER_FILTER}" FILES ${COUNTER_SCHEDULERS_HEADERS} ${COUNTER_SCHEDULERS_SRC})
    source_group("Source Files\\${INTERNAL_COUNTER_FILTER}" FILES ${INTERNAL_COUNTERS_HEADERS} ${INTERNAL_COUNTERS_SRC})
    source_group("Source Files\\${PUBLIC_COUNTER_FILTER}" FILES ${PUBLIC_COUNTERS_HEADERS} ${PUBLIC_COUNTERS_SRC})
    source_group("Source Files\\CounterSplittingAlgorithms" FILES ${COUNTER_SPLITTING_ALGO_HEADERS})
    source_group("Source Files" FILES ${COUNTERS_HEADER})

    foreach(API GL DX11 DX12 VK CL HSA)
        include ("CounterGenerator${API}.cmake")
        source_group("Source Files\\${COUNTER_GENERATOR_FILTER}\\${API}" FILES ${COUNTER_GENERATORS_API_HEADERS} ${COUNTER_GENERATORS_API_SRC})
        source_group("Source Files\\${COUNTER_SCHEDULER_FILTER}\\${API}" FILES ${COUNTER_SCHEDULERS_API_HEADERS} ${COUNTER_SCHEDULERS_API_SRC})
        source_group("Source Files\\${INTERNAL_COUNTER_FILTER}\\${API}" FILES ${INTERNAL_COUNTERS_API_HEADERS} ${INTERNAL_COUNTERS_API_SRC})
        source_group("Source Files\\${PUBLIC_COUNTER_FILTER}\\${API}" FILES ${PUBLIC_COUNTERS_API_HEADERS} ${PUBLIC_COUNTERS_API_SRC})
    endforeach(API)
endif()

