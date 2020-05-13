@ECHO on
REM Copyright 2018-2020 Advanced Micro Devices, Inc.

SET outDir="%~1"

IF outDir=="" THEN SET outDir=".\"

%VULKAN_SDK%\Bin\glslangValidator.exe -V vk_color_cube_shader.vert -o %outDir%vk_color_cube_shader.vert.spv
%VULKAN_SDK%\Bin\glslangValidator.exe -V vk_color_cube_shader.frag -o %outDir%vk_color_cube_shader.frag.spv
%VULKAN_SDK%\Bin\glslangValidator.exe -V vk_color_cube_wireframe_shader.frag -o %outDir%vk_color_cube_wireframe_shader.frag.spv

