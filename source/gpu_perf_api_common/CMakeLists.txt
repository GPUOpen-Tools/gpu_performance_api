## Copyright (C) 2018-2026 Advanced Micro Devices, Inc. All rights reserved. ##

block()
    # Updates gpa_version.h with CMake variables only when neccessary
    string(TIMESTAMP GPA_CURRENT_YEAR %Y)
    configure_file("gpa_version.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/gpa_version.h" @ONLY)
endblock()

set(GPA_PROJECT_NAME GPUPerfAPI-Common)
set(ProjectName ${GPA_PROJECT_NAME})

include(${GPA_CMAKE_MODULES_DIR}/common.cmake)

add_library(GPUPerfAPI-Common STATIC)

target_include_directories(GPUPerfAPI-Common PUBLIC
    ${GPA_PUBLIC_HEADER}
    ${GPA_SRC}
)

target_link_libraries(GPUPerfAPI-Common
    PRIVATE
        $<$<PLATFORM_ID:Linux>:pthread>
        AMD::device_info
        # Logging requires TSingleton.h
        AMD::tsingleton
)

target_sources(GPUPerfAPI-Common PRIVATE
    gpa_array_view.hpp
    gpa_command_list.cc
    gpa_command_list.h
    gpa_command_list_interface.h
    gpa_common_defs.h
    gpa_context.cc
    gpa_context.h
    gpa_context_counter_mediator.cc
    gpa_context_counter_mediator.h
    gpa_context_interface.h
    gpa_counter_data_request_manager.h
    gpa_function_exports.def
    gpa_hw_info.cc
    gpa_hw_info.h
    gpa_hw_support.cpp
    gpa_hw_support.h
    gpa_implementor.cc
    gpa_implementor.h
    gpa_implementor_interface.h
    gpa_interface_trait_interface.h
    gpa_pass.cc
    gpa_pass.h
    gpa_profiler.cc
    gpa_profiler.h
    gpa_sample.cc
    gpa_sample.h
    gpa_session.cc
    gpa_session.h
    gpa_session_interface.h
    gpa_unique_object.cc
    gpa_unique_object.h
    gpa_version.h
    gpa_version.h.in
    gpu_perf_api.cc
    logging.cc
    logging.h
    resource.h
    utility.cc
    utility.h
)
