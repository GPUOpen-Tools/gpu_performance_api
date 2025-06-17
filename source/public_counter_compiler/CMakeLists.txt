## Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.

enable_language(CSharp)

set(GPA_PROJECT_NAME PublicCounterCompiler)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/DerivedCounterDef.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/Form1.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/Form1.designer.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/Form1.resx
            ${CMAKE_CURRENT_SOURCE_DIR}/InternalCounterDef.cs
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
                        DOTNET_SDK "Microsoft.NET.Sdk"
                        DOTNET_TARGET_FRAMEWORK "net8.0-windows"
                        VS_PACKAGE_REFERENCES "Microsoft.NETCore.App"
                        VS_GLOBAL_UseWindowsForms "True")

SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})

set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER Tools)
