## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../")

set(GPA_PROJECT_NAME PublicCounterDefinitionFiles)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/Common.cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PUBLIC_COUNTER_DEFINITIONS PublicCounterDefinitionsGfx6.txt
                               PublicCounterDefinitionsGfx7.txt
                               PublicCounterDefinitionsGfx8.txt
                               PublicCounterDefinitionsGfx9.txt)

set(PUBLIC_COUNTER_DEFINITIONS_COMPUTE PublicCounterDefinitionsComputeGfx6.txt
                                       PublicCounterDefinitionsComputeGfx7.txt
                                       PublicCounterDefinitionsComputeGfx8.txt
                                       PublicCounterDefinitionsComputeGfx9.txt)

set(SOURCES ${PUBLIC_COUNTER_DEFINITIONS}
            ${PUBLIC_COUNTER_DEFINITIONS_COMPUTE})

add_executable(${GPA_PROJECT_NAME} ${SOURCES})
target_link_libraries(${GPA_PROJECT_NAME}
                      GPUPerfAPI-Common)

set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER PublicCounterDefinitionFiles)
REMOVE_TARGET_FROM_BUILD(${GPA_PROJECT_NAME})

set(GPA_PROJECT_NAME PublicCounterNames)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/Common.cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PUBLIC_COUNTER_NAMES_CL PublicCounterNamesCLGfx6.txt
                            PublicCounterNamesCLGfx7.txt
                            PublicCounterNamesCLGfx8.txt
                            PublicCounterNamesCLGfx8_Baffin.txt
                            PublicCounterNamesCLGfx8_Carrizo.txt
                            PublicCounterNamesCLGfx8_Ellesmere.txt
                            PublicCounterNamesCLGfx8_Fiji.txt
                            PublicCounterNamesCLGfx8_Iceland.txt
                            PublicCounterNamesCLGfx8_Tonga.txt
                            PublicCounterNamesCLGfx9.txt
                            PublicCounterNamesCLGfx9_Placeholder4.txt
                            PublicCounterNamesCLGfx9_Gfx906.txt)

set(PUBLIC_COUNTER_NAMES_DX11 PublicCounterNamesDX11Gfx6.txt
                              PublicCounterNamesDX11Gfx7.txt
                              PublicCounterNamesDX11Gfx8.txt
                              PublicCounterNamesDX11Gfx8_Baffin.txt
                              PublicCounterNamesDX11Gfx8_Carrizo.txt
                              PublicCounterNamesDX11Gfx8_Ellesmere.txt
                              PublicCounterNamesDX11Gfx8_Fiji.txt
                              PublicCounterNamesDX11Gfx8_Iceland.txt
                              PublicCounterNamesDX11Gfx8_Tonga.txt
                              PublicCounterNamesDX11Gfx9.txt
                              PublicCounterNamesDX11Gfx9_Placeholder4.txt
                              PublicCounterNamesDX11Gfx9_Gfx906.txt)

set(PUBLIC_COUNTER_NAMES_DX12 PublicCounterNamesDX12Gfx7.txt
                              PublicCounterNamesDX12Gfx8.txt
                              PublicCounterNamesDX12Gfx8_Baffin.txt
                              PublicCounterNamesDX12Gfx8_Carrizo.txt
                              PublicCounterNamesDX12Gfx8_Ellesmere.txt
                              PublicCounterNamesDX12Gfx8_Fiji.txt
                              PublicCounterNamesDX12Gfx8_Iceland.txt
                              PublicCounterNamesDX12Gfx8_Tonga.txt
                              PublicCounterNamesDX12Gfx9.txt
                              PublicCounterNamesDX12Gfx9_Placeholder4.txt
                              PublicCounterNamesDX12Gfx9_Gfx906.txt)

set(PUBLIC_COUNTER_NAMES_GL PublicCounterNamesGLGfx6.txt
                            PublicCounterNamesGLGfx7.txt
                            PublicCounterNamesGLGfx8.txt
                            PublicCounterNamesGLGfx8_Baffin.txt
                            PublicCounterNamesGLGfx8_Carrizo.txt
                            PublicCounterNamesGLGfx8_Ellesmere.txt
                            PublicCounterNamesGLGfx8_Fiji.txt
                            PublicCounterNamesGLGfx8_Iceland.txt
                            PublicCounterNamesGLGfx8_Tonga.txt
                            PublicCounterNamesGLGfx9.txt
                            PublicCounterNamesGLGfx9_Placeholder4.txt
                            PublicCounterNamesGLGfx9_Gfx906.txt)

set(PUBLIC_COUNTER_NAMES_HSA PublicCounterNamesHSAGfx8.txt
                             PublicCounterNamesHSAGfx8_Fiji.txt
                             PublicCounterNamesHSAGfx9.txt
                             PublicCounterNamesHSAGfx9_Placeholder4.txt
                             PublicCounterNamesHSAGfx9_Gfx906.txt)

set(PUBLIC_COUNTER_NAMES_VK PublicCounterNamesVKGfx7.txt
                            PublicCounterNamesVKGfx8.txt
                            PublicCounterNamesVKGfx8_Baffin.txt
                            PublicCounterNamesVKGfx8_Carrizo.txt
                            PublicCounterNamesVKGfx8_Ellesmere.txt
                            PublicCounterNamesVKGfx8_Fiji.txt
                            PublicCounterNamesVKGfx8_Iceland.txt
                            PublicCounterNamesVKGfx8_Tonga.txt
                            PublicCounterNamesVKGfx9.txt
                            PublicCounterNamesVKGfx9_Placeholder4.txt
                            PublicCounterNamesVKGfx9_Gfx906.txt)

set(SOURCES ${PUBLIC_COUNTER_NAMES_CL}
            ${PUBLIC_COUNTER_NAMES_DX11}
            ${PUBLIC_COUNTER_NAMES_DX12}
            ${PUBLIC_COUNTER_NAMES_GL}
            ${PUBLIC_COUNTER_NAMES_HSA}
            ${PUBLIC_COUNTER_NAMES_VK})

add_executable(${GPA_PROJECT_NAME} ${SOURCES})
target_link_libraries(${GPA_PROJECT_NAME}
                      GPUPerfAPI-Common)

set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER PublicCounterNames)
REMOVE_TARGET_FROM_BUILD(${GPA_PROJECT_NAME})

if(WIN32)
    source_group("CL" FILES ${PUBLIC_COUNTER_NAMES_CL})
    source_group("DX11" FILES ${PUBLIC_COUNTER_NAMES_DX11})
    source_group("DX12" FILES ${PUBLIC_COUNTER_NAMES_DX12})
    source_group("GL" FILES ${PUBLIC_COUNTER_NAMES_GL})
    source_group("HSA" FILES ${PUBLIC_COUNTER_NAMES_HSA})
    source_group("VK" FILES ${PUBLIC_COUNTER_NAMES_VK})
endif()

