#!/bin/bash
# Copyright 2018 Advanced Micro Devices, Inc.

# This script requires an output directory and the Vulkan SDK directory as parameter

# First Verify that two parameters exists
if [ $# -ne 2 ]
then
    echo "Insufficient arguments to the script."
    echo "Usage: CompileShaders.sh <output_dir> <vulkan_sdk_dir>"
    exit 1
fi

OutDir="$1"

if [ -z ${OutDir} ]; then
    OutDir=./
fi

VK_TOOLS_DIR="$2"
if [ -z VK_TOOLS_DIR ]; then
  echo "No Vulkan SDK found"
  exit 1
fi

${VK_TOOLS_DIR}/glslangValidator -V vkcolorcubeshader.vert -o ${OutDir}/vkcolorcubeshader.vert.spv
${VK_TOOLS_DIR}/glslangValidator -V vkcolorcubeshader.frag -o ${OutDir}/vkcolorcubeshader.frag.spv
${VK_TOOLS_DIR}/glslangValidator -V vkcolorcubewireframeshader.frag -o ${OutDir}/vkcolorcubewireframeshader.frag.spv

