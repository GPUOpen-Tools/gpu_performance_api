## Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.5.1)

set(DEPTH "../../../../")

set(GPA_PROJECT_NAME VkColorCube)
set(ProjectName ${GPA_PROJECT_NAME})

include (${GPA_CMAKE_MODULES_DIR}/common.cmake)
include(${GPA_CMAKE_MODULES_DIR}/gpa_vulkan.cmake)
include (${CMAKE_COMMON_SRC_GLOBAL_TSINGLETON})

include_directories(${ADDITIONAL_INCLUDE_DIRECTORIES}
                    ${GPA_PUBLIC_HEADER}
                    ${GPA_SRC})

if(ANDROID)
    include_directories(${ANDROID_INCLUDE_DIRECTORIES})

    ## Reset all variables after creating the lib
    include (${GPA_CMAKE_MODULES_DIR}/common.cmake)
    set(ADDITIONAL_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/android_main.cc)
    add_compile_options(-Wno-missing-braces)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/vk_color_cube.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/vk_color_cube.h
            ${CMAKE_CURRENT_SOURCE_DIR}/gpa_helper.h
            ${CMAKE_CURRENT_SOURCE_DIR}/gpa_helper.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/vk_util.h
            ${CMAKE_CURRENT_SOURCE_DIR}/vk_util.cc
            ${ADDITIONAL_SOURCE})

add_definitions(${ADDITIONAL_DEFINTIONS})
link_directories(${ADDITIONAL_LINK_DIRECTORIES})

set(LINK_LIBS ${GPA_PROJECT_NAME})

if(ANDROID)
    add_library(${GPA_PROJECT_NAME} SHARED ${SOURCES})
    set(LINK_LIBS ${LINK_LIBS} ${ANDROID_LIBS})
    ADD_GPA_USER_COMPILE_DEFINITIONS()
else()
    add_executable(${GPA_PROJECT_NAME} WIN32 ${SOURCES})
    ADD_GPA_USER_COMPILE_DEFINITIONS()
endif()

add_dependencies(${GPA_PROJECT_NAME} GPUPerfAPIVK)

target_link_libraries(${LINK_LIBS}
                      $<$<PLATFORM_ID:Linux>:dl>
                      $<$<PLATFORM_ID:Linux>:xcb>)
ADD_LINKER_FLAGS()

if(WIN32)
    add_custom_command(TARGET ${GPA_PROJECT_NAME} POST_BUILD
                       COMMAND compile_shaders.bat ${GPA_OUTPUT_DIR}/$<CONFIG>/
                       BYPRODUCTS vk_color_cube_shader.vert.spv vk_color_cube_shader.frag.spv vk_color_cube_wireframe_shader.frag.spv
                       WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                       COMMENT "Compiling Vulkan Shaders vk_color_cube_shader.vert vk_color_cube_shader.frag vk_color_cube_wireframe_shader.frag")

    set_target_properties(${GPA_PROJECT_NAME} PROPERTIES FOLDER "Examples/Vulkan")
    SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})

elseif(ANDROID)
    add_custom_command(TARGET ${GPA_PROJECT_NAME} PRE_BUILD
                       COMMAND ${ANDROID_NDK_SHADER_TOOL_PATH}/glslc -c ${CMAKE_CURRENT_LIST_DIR}/vk_color_cube_shader.vert -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/vk_color_cube_shader.vert.spv
                       COMMAND ${ANDROID_NDK_SHADER_TOOL_PATH}/glslc -c ${CMAKE_CURRENT_LIST_DIR}/vk_color_cube_shader.frag -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/vk_color_cube_shader.frag.spv
                       COMMAND ${ANDROID_NDK_SHADER_TOOL_PATH}/glslc -c ${CMAKE_CURRENT_LIST_DIR}/vk_color_cube_wireframe_shader.frag -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/vk_color_cube_wireframe_shader.frag.spv
                       BYPRODUCTS vk_color_cube_shader.vert.spv vk_color_cube_shader.frag.spv vk_color_cube_wireframe_shader.frag.spv
                       WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                       COMMENT "Compiling Vulkan Shaders vk_color_cube_shader.vert vk_color_cube_shader.frag vk_color_cube_wireframe_shader.frag")

    set(JAVA_CLASS_PATH "${ANDROID_TARGET_JAR}:obj")
    set(KEYSTORE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug.keystore)
    add_custom_command(OUTPUT ${KEYSTORE}
                    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                    COMMAND keytool -genkey -keystore ${KEYSTORE} -storepass android -alias androiddebugkey -keypass android -keyalg RSA -keysize 2048 -validity 10000 -dname "CN=, OU=, O=, L=, S=, C=")

    if(CMAKE_BUILD_TYPE STREQUAL "debug")
        set(APK_SUFFIX ${CMAKE_DEBUG_POSTFIX})
        set(TARGET_NAME_SUFFIX ${CMAKE_DEBUG_POSTFIX})
    else()
        set(APK_SUFFIX ${CMAKE_RELEASE_POSTFIX})
        set(TARGET_NAME_SUFFIX ${CMAKE_RELEASE_POSTFIX})
    endif()

    set(APK_FILE_NAME com.amd.gpa.vkcolorcube${APK_SUFFIX}.apk)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/android_manifest.xml ${CMAKE_CURRENT_BINARY_DIR}/android_manifest.xml)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/VkColorCubeLoader.java ${CMAKE_CURRENT_BINARY_DIR}/VkColorCubeLoader.java)

    add_custom_command(OUTPUT ${APK_FILE_NAME}
                    DEPENDS ${GPA_PROJECT_NAME}
                    DEPENDS ${KEYSTORE}
                    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/libs/lib
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/bin
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/shaders
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/obj/$<CONFIG>/
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/src/com/amd/gpa/vk_color_cube
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libGPUPerfAPIVK${TARGET_NAME_SUFFIX}.so ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/libs/lib/x86_64/libGPUPerfAPIVK${TARGET_NAME_SUFFIX}.so
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libVkColorCube${TARGET_NAME_SUFFIX}.so ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/libs/lib/x86_64/libVkColorCube${TARGET_NAME_SUFFIX}.so
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/VkColorCubeLoader.java ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/src/com/amd/gpa/vk_color_cube
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/vk_color_cube_shader.vert.spv ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/shaders/vk_color_cube_shader.vert.spv
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/vk_color_cube_shader.frag.spv ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/shaders/vk_color_cube_shader.frag.spv
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/vk_color_cube_wireframe_shader.frag.spv ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/shaders/vk_color_cube_wireframe_shader.frag.spv
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/android_manifest.xml ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/AndroidManifest.xml
                    COMMAND ${ANDROID_BUILD_TOOLS}/aapt package -f -m -J src -M ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/AndroidManifest.xml -I ${ANDROID_TARGET_JAR}
                    COMMAND javac -d ./obj/$<CONFIG> -source 1.7 -target 1.7 -bootclasspath ${JAVA_HOME_PATH}/jre/lib/rt.jar -classpath "${JAVA_CLASS_PATH}" -sourcepath src ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/src/com/amd/gpa/vk_color_cube/*.java
                    COMMAND ${ANDROID_BUILD_TOOLS}/dx --dex --output=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/bin/classes.dex ./obj/$<CONFIG>/
                    COMMAND ${ANDROID_BUILD_TOOLS}/aapt package -f -M ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/APK/$<CONFIG>/AndroidManifest.xml -I ${ANDROID_TARGET_JAR} -A APK/$<CONFIG>/shaders --version-name 3.4 -F ${APK_FILE_NAME}-unalligned APK/$<CONFIG>/libs APK/$<CONFIG>/bin
                    COMMAND ${ANDROID_BUILD_TOOLS}/zipalign -f 4 ${APK_FILE_NAME}-unalligned ${APK_FILE_NAME}
                    COMMAND ${ANDROID_BUILD_TOOLS}/apksigner sign --ks ${KEYSTORE} --ks-pass pass:android --key-pass pass:android --ks-key-alias androiddebugkey ${APK_FILE_NAME})

    add_custom_target(APK_FILE ALL
                      DEPENDS ${APK_FILE_NAME}
                      DEPENDS ${KEYSTORE})

elseif(UNIX)
    add_custom_command(TARGET ${GPA_PROJECT_NAME} PRE_BUILD
                       COMMAND ${CMAKE_CURRENT_LIST_DIR}/compile_shaders.sh ${GPA_OUTPUT_DIR}/$<CONFIG>/ ${VK_TOOLS_DIR}
                       BYPRODUCTS vk_color_cube_shader.vert.spv vk_color_cube_shader.frag.spv vk_color_cube_wireframe_shader.frag.spv
                       WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                       COMMENT "Compiling Vulkan Shaders vk_color_cube_shader.vert vk_color_cube_shader.frag vk_color_cube_wireframe_shader.frag")

    SET_EXECUTABLE_NAME(${GPA_PROJECT_NAME})


endif()