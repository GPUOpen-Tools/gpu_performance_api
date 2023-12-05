## Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

enable_language(CSharp)

set(DEPTH "../../")

set(GPA_PROJECT_NAME PublicCounterCompiler)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/properties/AssemblyInfo.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/app.config
            ${CMAKE_CURRENT_SOURCE_DIR}/app.manifest
            ${CMAKE_CURRENT_SOURCE_DIR}/DerivedCounterDef.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/Form1.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/Form1.designer.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/Form1.resx
            ${CMAKE_CURRENT_SOURCE_DIR}/InternalCounterDef.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/packages.config
            ${CMAKE_CURRENT_SOURCE_DIR}/Program.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/CounterCompiler.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/FileNameAndPath.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/GpaUtility.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/CMakeGenerator.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/CounterDefCMakeGen.cs)

add_executable(${GPA_PROJECT_NAME} WIN32 ${SOURCES})
target_compile_options(${GPA_PROJECT_NAME} PRIVATE "/langversion:6")
set_target_properties(${GPA_PROJECT_NAME} PROPERTIES
                        VS_GLOBAL_ROOTNAMESPACE ${GPA_PROJECT_NAME}
                        DOTNET_TARGET_FRAMEWORK_VERSION "v4.7"
                        VS_DOTNET_REFERENCES "Microsoft.CSharp;System;System.Configuration;System.Data;System.Drawing;System.Web.Extensions;System.Windows.Forms;System.Xml")

SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})

set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER Tools)
