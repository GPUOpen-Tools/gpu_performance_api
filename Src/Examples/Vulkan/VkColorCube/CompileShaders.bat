@ECHO off
REM Copyright 2018 Advanced Micro Devices, Inc.

SET outDir="%~1"

IF outDir=="" THEN SET outDir=".\"

%VULKAN_SDK%\Bin\glslangValidator.exe -V vkcolorcubeshader.vert -o %outDir%vkcolorcubeshader.vert.spv
%VULKAN_SDK%\Bin\glslangValidator.exe -V vkcolorcubeshader.frag -o %outDir%vkcolorcubeshader.frag.spv
%VULKAN_SDK%\Bin\glslangValidator.exe -V vkcolorcubewireframeshader.frag -o %outDir%vkcolorcubewireframeshader.frag.spv

