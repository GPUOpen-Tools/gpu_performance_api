//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  This file provides access to an API's runtime module.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_API_RT_MODULE_LOADER_H_
#define GPU_PERF_API_COMMON_API_RT_MODULE_LOADER_H_

#include <new>

#include "TSingleton.h"

/// @brief Singleton to hold global API RT Module.
template <class T>
class ApiRuntimeModuleLoader : public TSingleton<ApiRuntimeModuleLoader<T> >
{
    /// TSingleton needs to be able to use our constructor.
    friend class TSingleton<ApiRuntimeModuleLoader<T>>;

public:
    /// @brief Deleted copy constructor.
    ApiRuntimeModuleLoader(const ApiRuntimeModuleLoader&) = delete;

    /// @brief Deleted equal operator.
    ApiRuntimeModuleLoader& operator=(ApiRuntimeModuleLoader&) = delete;

    /// @brief Checks whether or not the RT Module is loaded.
    ///
    /// @return True if the RT Module is loaded, false otherwise.
    bool IsModuleLoaded()
    {
        bool retVal = false;

        if (nullptr != run_time_module_)
        {
            retVal = run_time_module_->IsModuleLoaded();
        }

        return retVal;
    }

    /// @brief Gets the Runtime Module.
    ///
    /// @return The Runtime Module.
    T* GetApiRuntimeModule()
    {
        if (nullptr == run_time_module_)
        {
            run_time_module_ = new (std::nothrow) T();
        }

        return run_time_module_;
    };

private:
    /// @brief Private constructor.
    ApiRuntimeModuleLoader()
    {
    };

    /// @brief Private Virtual destructor.
    virtual ~ApiRuntimeModuleLoader()
    {
        if (nullptr != run_time_module_)
        {
            run_time_module_->UnloadModule();
            delete run_time_module_;
            run_time_module_ = nullptr;
        }
    };

    T* run_time_module_ = nullptr;  ///< The DynamicLibraryModule instance that wraps the RT API.
};

#endif  // GPU_PERF_API_COMMON_API_RT_MODULE_LOADER_H_
