//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  class to load the GPA at run-time
//==============================================================================

#include "GPUPerfAPILoader.h"

GPUPerfAPILoader::GPUPerfAPILoader()
{
#ifdef _WIN32
    m_hMod = nullptr;
#else
    pHandle = nullptr;
#endif

    // set all GPA public function pointers to zero
#define GPA_FUNCTION_PREFIX(f) f = nullptr;
#include "GPAFunctions.h"
#undef GPA_FUNCTION_PREFIX
}

GPUPerfAPILoader::~GPUPerfAPILoader()
{
    Unload();
}

void GPUPerfAPILoader::Unload()
{
#ifdef _WIN32

    if (m_hMod)
    {
        FreeLibrary(m_hMod);
        m_hMod = nullptr;
    }

#else

    if (nullptr != pHandle)
    {
        dlclose(pHandle);
        pHandle = nullptr;
    }

#endif
}

bool GPUPerfAPILoader::Loaded()
{
#ifdef _WIN32

    if (m_hMod)
    {
        return true;
    }

#else

    if (nullptr != pHandle)
    {
        return true;
    }

#endif
    return false;
}

#ifdef _WIN32
bool GPUPerfAPILoader::Load(const char* pDllPath, GPA_API_Type api, const char** ppErrorMessage)
{
    std::string dllFullPath = GetGPADllName(std::string(pDllPath), api);

    m_hMod = LoadLibraryA(dllFullPath.c_str());

    if (nullptr == m_hMod)
    {
        *ppErrorMessage = "LoadLibrary failed, dll not found.\n";
        return false;
    }

    // Execute GetProcAddress on every public function. If fail assert and return error
#define GPA_FUNCTION_PREFIX(func)                                                           \
    func = (func##PtrType)GetProcAddress(m_hMod, #func);                                    \
    assert(nullptr != func);                                                                \
    if (nullptr == func)                                                                    \
    {                                                                                       \
        *ppErrorMessage = #func " not located in the dll. Incorrect or out of date dll.\n"; \
        Unload();                                                                           \
        return false;                                                                       \
    }
#include "GPAFunctions.h"

#undef GPA_FUNCTION_PREFIX

    return true;
}
#else

bool GPUPerfAPILoader::Load(const char* pDllPath, GPA_API_Type api, const char** ppErrorMessage)
{
    std::string dllFullPath = GetGPADllName(std::string(pDllPath), api);

    pHandle = dlopen(dllFullPath.c_str(), RTLD_LAZY);

    if (nullptr == pHandle)
    {
        *ppErrorMessage = dlerror();  //"dlopen failed, shared library not found.\n";
        return false;
    }

    // Execute GetProcAddress on every public function. If fail assert and return error
#define GPA_FUNCTION_PREFIX(func)                                                                                 \
    func = (func##PtrType)dlsym(pHandle, #func);                                                                  \
    assert(nullptr != func);                                                                                      \
    if (nullptr == func)                                                                                          \
    {                                                                                                             \
        *ppErrorMessage = #func " not located in the shared library. Incorrect or out of date shared library.\n"; \
        Unload();                                                                                                 \
        return false;                                                                                             \
    }
#include "GPAFunctions.h"

#undef GPA_FUNCTION_PREFIX

    return true;
}

#endif

#ifdef _WIN32
#define LIB_PREFIX ""
#define LIB_SUFFIX ".dll"
#else
#define LIB_PREFIX "lib"
#define LIB_SUFFIX ".so"
#endif

#ifndef AMDT_PLATFORM_SUFFIX
#ifdef PLATFORM_SUFFIX
#define AMDT_PLATFORM_SUFFIX PLATFORM_SUFFIX
#endif
#endif

#ifdef USE_DEBUG_GPA
#define LIB_DEBUG_SUFFIX "-d"
#else
#define LIB_DEBUG_SUFFIX ""
#endif

std::string GPUPerfAPILoader::GetGPADllName(const std::string& dllPath, GPA_API_Type api)
{
    std::string dllFullPath = dllPath;
    dllFullPath.append(LIB_PREFIX);

    switch (api)
    {
    case GPA_API_DIRECTX_11:
        dllFullPath.append("GPUPerfAPIDX11");
        break;

    case GPA_API_DIRECTX_12:
        dllFullPath.append("GPUPerfAPIDX12");
        break;

    case GPA_API_OPENGL:
        dllFullPath.append("GPUPerfAPIGL");
        break;

    case GPA_API_OPENCL:
        dllFullPath.append("GPUPerfAPICL");
        break;

    case GPA_API_ROCM:
        dllFullPath.append("GPUPerfAPIROCm");
        break;

    case GPA_API_VULKAN:
        dllFullPath.append("GPUPerfAPIVK");
        break;

    default:
        assert("unknown API type");
    }

    dllFullPath.append(AMDT_PLATFORM_SUFFIX);
    dllFullPath.append(LIB_DEBUG_SUFFIX);
    dllFullPath.append(AMDT_BUILD_SUFFIX);
    dllFullPath.append(LIB_SUFFIX);

    return dllFullPath;
}
