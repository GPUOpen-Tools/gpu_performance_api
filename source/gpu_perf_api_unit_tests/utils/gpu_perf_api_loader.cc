//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  class to load the GPA at run-time
//==============================================================================

#include "gpu_perf_api_unit_tests/utils/gpu_perf_api_loader.h"

GpuPerfApiLoader::GpuPerfApiLoader()
{
#ifdef _WIN32
    h_module_ = nullptr;
#else
    handle_ = nullptr;
#endif

// Set all GPA public function pointers to zero.
#define GPA_FUNCTION_PREFIX(f) f = nullptr;
#include "gpu_performance_api/gpu_perf_api_functions.h"
#undef GPA_FUNCTION_PREFIX
}

GpuPerfApiLoader::~GpuPerfApiLoader()
{
    Unload();
}

void GpuPerfApiLoader::Unload()
{
#ifdef _WIN32

    if (h_module_)
    {
        FreeLibrary(h_module_);
        h_module_ = nullptr;
    }

#else

    if (nullptr != handle_)
    {
        dlclose(handle_);
        handle_ = nullptr;
    }

#endif
}

bool GpuPerfApiLoader::Loaded()
{
#ifdef _WIN32

    if (h_module_)
    {
        return true;
    }

#else

    if (nullptr != handle_)
    {
        return true;
    }

#endif
    return false;
}

#ifdef _WIN32
bool GpuPerfApiLoader::Load(const char* dll_path, GpaApiType api, const char** error_message)
{
    std::string dll_full_path = GetGPADllName(std::string(dll_path), api);

    h_module_ = LoadLibraryA(dll_full_path.c_str());

    if (nullptr == h_module_)
    {
        *error_message = "LoadLibrary failed, dll not found.\n";
        return false;
    }

    // Execute GetProcAddress on every public function. If fail assert and return error
#define GPA_FUNCTION_PREFIX(func)                                                          \
    func = (func##PtrType)GetProcAddress(h_module_, #func);                                \
    assert(nullptr != func);                                                               \
    if (nullptr == func)                                                                   \
    {                                                                                      \
        *error_message = #func " not located in the dll. Incorrect or out of date dll.\n"; \
        Unload();                                                                          \
        return false;                                                                      \
    }
#include "gpu_performance_api/gpu_perf_api_functions.h"

#undef GPA_FUNCTION_PREFIX

    return true;
}
#else

bool GpuPerfApiLoader::Load(const char* dll_path, GpaApiType api, const char** error_message)
{
    std::string dll_full_path = GetGPADllName(std::string(dll_path), api);

    handle_ = dlopen(dll_full_path.c_str(), RTLD_LAZY);

    if (nullptr == handle_)
    {
        *error_message = dlerror();  //"dlopen failed, shared library not found.\n";
        return false;
    }

    // Execute GetProcAddress on every public function. If fail assert and return error
#define GPA_FUNCTION_PREFIX(func)                                                                                \
    func = (func##PtrType)dlsym(handle_, #func);                                                                 \
    assert(nullptr != func);                                                                                     \
    if (nullptr == func)                                                                                         \
    {                                                                                                            \
        *error_message = #func " not located in the shared library. Incorrect or out of date shared library.\n"; \
        Unload();                                                                                                \
        return false;                                                                                            \
    }
#include "gpu_performance_api/gpu_perf_api_functions.h"

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

std::string GpuPerfApiLoader::GetGPADllName(const std::string& dll_path, GpaApiType api)
{
    std::string dll_full_path = dll_path;
    dll_full_path.append(LIB_PREFIX);

    switch (api)
    {
    case kGpaApiDirectx11:
        dll_full_path.append("GPUPerfAPIDX11");
        break;

    case kGpaApiDirectx12:
        dll_full_path.append("GPUPerfAPIDX12");
        break;

    case kGpaApiOpengl:
        dll_full_path.append("GPUPerfAPIGL");
        break;

    case kGpaApiOpencl:
        dll_full_path.append("GPUPerfAPICL");
        break;

    case kGpaApiVulkan:
        dll_full_path.append("GPUPerfAPIVK");
        break;

    default:
        assert("unknown API type");
    }

    dll_full_path.append(AMDT_PLATFORM_SUFFIX);
    dll_full_path.append(LIB_DEBUG_SUFFIX);
    dll_full_path.append(AMDT_BUILD_SUFFIX);
    dll_full_path.append(LIB_SUFFIX);

    return dll_full_path;
}