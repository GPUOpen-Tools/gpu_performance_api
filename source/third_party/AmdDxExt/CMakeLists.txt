## Copyright (C) 2025-2026 Advanced Micro Devices, Inc. All rights reserved. ##

add_library(amd_d3d_extensions INTERFACE)
add_library(AMD::d3dExtensions ALIAS amd_d3d_extensions)

target_sources(amd_d3d_extensions PUBLIC
    FILE_SET public_headers
    TYPE "HEADERS"
    BASE_DIRS .
    FILES
        AmdDxCounter.h
        AmdDxExt.h
        AmdDxExtApi.h
        AmdDxExtASICInfo.h
        AmdDxExtASICInfoApi.h
        AmdDxExtIface.h
        AmdDxExtPerfProfile.h
        AmdDxExtPerfProfileApi.h
        AmdExtD3D.h
        AmdExtD3DCommandListMarkerApi.h
        AmdExtD3DDeviceApi.h
        AmdExtDeviceWrapper.h
        AmdExtGpaInterface.h
        AmdExtGpaInterfaceApi.h
)
