## Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required(VERSION 3.10)

## Define AMD DirectX extension directory
set(AMD_DX_EXT_DIR ${GPA_SRC_THIRD_PARTY}/AmdDxExt)

## Include directory
set(ADDITIONAL_INCLUDE_DIRECTORIES ${ADDITIONAL_INCLUDE_DIRECTORIES}
                                   ${AMD_DX_EXT_DIR})
