## Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

enable_language(CSharp)

set(DEPTH "../../")

set(GPA_PROJECT_NAME PublicCounterCompiler)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/properties/assembly_info.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/app.config
            ${CMAKE_CURRENT_SOURCE_DIR}/app.manifest
            ${CMAKE_CURRENT_SOURCE_DIR}/derived_counter_def.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/form1.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/form1.designer.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/form1.resx
            ${CMAKE_CURRENT_SOURCE_DIR}/internal_counter_def.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/packages.config
            ${CMAKE_CURRENT_SOURCE_DIR}/program.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/counter_compiler.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/file_name_and_path.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake_generator.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/counter_def_cmake_gen.cs)

add_executable(${GPA_PROJECT_NAME} WIN32 ${SOURCES})
target_compile_options(${GPA_PROJECT_NAME} PRIVATE "/langversion:6")
set_target_properties(${GPA_PROJECT_NAME} PROPERTIES
                        VS_GLOBAL_ROOTNAMESPACE ${GPA_PROJECT_NAME}
                        DOTNET_TARGET_FRAMEWORK_VERSION "v4.7"
                        VS_DOTNET_REFERENCES "Microsoft.CSharp;System;System.Configuration;System.Data;System.Drawing;System.Web.Extensions;System.Windows.Forms;System.Xml")

SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})

set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER Tools)
