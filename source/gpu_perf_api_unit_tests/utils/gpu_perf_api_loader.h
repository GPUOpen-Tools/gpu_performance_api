//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  class to load the GPA at run-time.
//==============================================================================

#ifndef GPU_PERF_API_UNIT_TESTS_UTILS_GPU_PERF_API_LOADER_H_
#define GPU_PERF_API_UNIT_TESTS_UTILS_GPU_PERF_API_LOADER_H_

#ifdef _WIN32
#include <windows.h>
#endif

#if defined(_LINUX) || defined(LINUX)
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#endif

#include <assert.h>

#include <string>

#include "gpu_performance_api/gpu_perf_api_types.h"
#include "gpu_performance_api/gpu_perf_api_function_types.h"

/// @brief Class to load the GPUPerfAPI at run-time.
///
/// To call a function create an instance of GPUPerfAPILoader and use '.' notation to access the function as normal.
class GpuPerfApiLoader
{
public:
    /// @brief Constructor.
    GpuPerfApiLoader();

    /// @brief Destructor.
    ~GpuPerfApiLoader();

    /// @brief Loads the GPA Dll for the specified API and initializes all the GPA function pointers.
    ///
    /// @param [in] dll_path path to load GPA Dlls from.
    /// @param [in] api the API to load GPA for.
    /// @param [out] error_message the error message if loading fails.
    ///
    /// @return true if the GPA Dll is successfully loaded, false otherwise.
    bool Load(const char* dll_path, GpaApiType api, const char** error_message);

    /// @brief Unload may safely be called multiple times.
    void Unload();

    /// @brief Determine if Load has been successfully called.
    ///
    /// @return true if the GPA Dll is loaded.
    bool Loaded();

    // Define all GPA public functions.
#define GPA_FUNCTION_PREFIX(f) f##PtrType f;
#include "gpu_performance_api/gpu_perf_api_functions.h"
#undef GPA_FUNCTION_PREFIX

protected:
#ifdef _WIN32
    HMODULE h_module_;  ///< DLL module handle.
#else
    void* handle_;  ///< Shared library handle.
#endif

private:

    /// @brief Get the GPA DLL name for the specified api.
    ///
    /// @param [in] dll_path The path to load GPA Dlls from.
    /// @param [in] api The API to load GPA for.
    ///
    /// @return The full path to the dll to load.
    std::string GetGPADllName(const std::string& dll_path, GpaApiType api);
};

#endif
