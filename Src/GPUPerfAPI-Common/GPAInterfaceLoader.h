//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Interface Loader Utility header file
//==============================================================================

#ifndef _GPA_INTERFACE_LOADER_H_
#define _GPA_INTERFACE_LOADER_H_

#ifdef _WIN32
    #include <windows.h>
    #define GPA_MAX_PATH MAX_PATH  ///< Macro for max path length
    #ifdef _WIN64
        #define GPA_IS_64_BIT ///< Macro specifying 64-bit build
    #else
        #define GPA_IS_32_BIT ///< Macro specifying 32-bit build
    #endif
#else
    #include <dlfcn.h>
    #include <unistd.h>
    #define GPA_MAX_PATH 4096 ///< Macro for max path length
    #ifdef __x86_64__
        #define GPA_IS_64_BIT ///< Macro specifying 64-bit build
    #else
        #define GPA_IS_32_BIT ///< Macro specifying 32-bit build
    #endif
#endif

#include "GPUPerfAPI.h"
#include <map>
#include <stdint.h>
#include <algorithm>

#ifdef UNICODE
    typedef wchar_t LocaleChar;                 ///< Typedef for ANSI vs. Unicode character
    typedef std::wstring LocaleString;          ///< Typedef for ANSI vs. Unicode string
    #define GPA_OPENCL_LIB L"GPUPerfAPICL"      ///< Macro for base name of GPA OpenCL library
    #define GPA_OPENGL_LIB L"GPUPerfAPIGL"      ///< Macro for base name of GPA OpenGL library
    #define GPA_DIRECTX11_LIB L"GPUPerfAPIDX11" ///< Macro for base name of GPA DirectX 11 library
    #define GPA_DIRECTX12_LIB L"GPUPerfAPIDX12" ///< Macro for base name of GPA DirectX 12 library
    #define GPA_VULKAN_LIB L"GPUPerfAPIVK"      ///< Macro for base name of GPA Vulkan library
    #define GPA_HSA_LIB L"GPUPerfAPIHSA"        ///< Macro for base name of GPA HSA library

    #ifdef _WIN32
        #define GPA_LIB_PREFIX L""              ///< Macro for platform-specific lib file prefix
        #define GPA_LIB_SUFFIX L".dll"          ///< Macro for platform-specific lib file suffix
        #define GPA_X64_ARCH_SUFFIX L"-x64"     ///< Macro for 64-bit lib file architecture suffix
        #define GPA_X86_ARCH_SUFFIX L""         ///< Macro for 32-bit lib file architecture suffix
    #else
        #define GPA_LIB_PREFIX L"lib"           ///< Macro for platform-specific lib file prefix
        #define GPA_LIB_SUFFIX L".so"           ///< Macro for platform-specific lib file suffix
        #define GPA_X64_ARCH_SUFFIX L""         ///< Macro for 64-bit lib file architecture suffix
        #define GPA_X86_ARCH_SUFFIX L"32"       ///< Macro for 32-bit lib file architecture suffix
    #endif

    #define GPA_DEBUG_SUFFIX L"-d"              ///< Macro for debug build lib file suffix
    #define GPA_INTERNAL_SUFFIX L"-Internal"    ///< Macro for internal build lib file suffix

#else
    typedef char LocaleChar;                   ///< Typedef for ANSI vs. Unicode character
    typedef std::string LocaleString;          ///< Typedef for ANSI vs. Unicode string
    #define GPA_OPENCL_LIB "GPUPerfAPICL"      ///< Macro for base name of GPA OpenCL library
    #define GPA_OPENGL_LIB "GPUPerfAPIGL"      ///< Macro for base name of GPA OpenGL library
    #define GPA_DIRECTX11_LIB "GPUPerfAPIDX11" ///< Macro for base name of GPA DirectX 11 library
    #define GPA_DIRECTX12_LIB "GPUPerfAPIDX12" ///< Macro for base name of GPA DirectX 12 library
    #define GPA_VULKAN_LIB "GPUPerfAPIVK"      ///< Macro for base name of GPA Vulkan library
    #define GPA_HSA_LIB "GPUPerfAPIHSA"        ///< Macro for base name of GPA HSA library

    #ifdef _WIN32
        #define GPA_LIB_PREFIX ""              ///< Macro for platform-specific lib file prefix
        #define GPA_LIB_SUFFIX ".dll"          ///< Macro for platform-specific lib file suffix
        #define GPA_X64_ARCH_SUFFIX "-x64"     ///< Macro for 64-bit lib file architecture suffix
        #define GPA_X86_ARCH_SUFFIX ""         ///< Macro for 32-bit lib file architecture suffix
    #else
        #define GPA_LIB_PREFIX "lib"           ///< Macro for platform-specific lib file prefix
        #define GPA_LIB_SUFFIX ".so"           ///< Macro for platform-specific lib file suffix
        #define GPA_X64_ARCH_SUFFIX ""         ///< Macro for 64-bit lib file architecture suffix
        #define GPA_X86_ARCH_SUFFIX "32"       ///< Macro for 32-bit lib file architecture suffix
    #endif

    #define GPA_DEBUG_SUFFIX "-d"             ///< Macro for debug build lib file suffix
    #define GPA_INTERNAL_SUFFIX "-Internal"   ///< Macro for internal build lib file suffix
#endif

#define GPA_GET_FUNCTION_TABLE_FUNCTION_NAME "GPA_GetFuncTable" ///< Macro for GPA_GetFuncTable entrypoint

/// Get the current working directory
/// \return the current working directory
inline LocaleString GetWorkingDirectoryPath()
{
    LocaleChar selfModuleName[GPA_MAX_PATH];
    LocaleString path;

#ifdef _WIN32
    GetModuleFileName(nullptr, selfModuleName, GPA_MAX_PATH);
    path = LocaleString(selfModuleName);
    std::replace(path.begin(), path.end(), '\\', '/');
#else
    int len;
    len = readlink("/proc/self/exe", selfModuleName, GPA_MAX_PATH - 1);

    if (len != -1)
    {
        selfModuleName[len] = '\0';
    }

    path = LocaleString(selfModuleName);
#endif

    size_t lastSlashPos = path.find_last_of('/');

    if (std::string::npos != lastSlashPos)
    {
        path = path.substr(0, lastSlashPos + 1);
    }

    return path;
}

/// Singleton Class to handle the loading and unloading the possible APIs
class GPAApiManager
{
public:

    /// Returns the instance of the GPAApiManger
    /// \return returns  the instance of the GPAApiManager
    static GPAApiManager* Instance()
    {
        if (nullptr == m_pGpaApiManager)
        {
            m_pGpaApiManager = new(std::nothrow) GPAApiManager();
        }

        return m_pGpaApiManager;
    }

    /// Deletes the static instance instance
    static void DeleteInstance()
    {
        if (nullptr != m_pGpaApiManager)
        {
            delete m_pGpaApiManager;
            m_pGpaApiManager = nullptr;
        }
    }

    /// Loads the dll and initialize the function table for the passed api type
    /// \param[in] apiType type of the api to be loaded
    /// \param[in] libPath path to the folder containing dll
    /// \return returns appropriate status of the operation
    GPA_Status LoadApi(const GPA_API_Type& apiType, const LocaleString libPath = LocaleString())
    {
        GPA_Status status = GPA_STATUS_OK;

#if USE_GPA

        if (m_gpaFunctionTables.find(apiType) == m_gpaFunctionTables.end())
        {
            if (apiType >= GPA_API__START && apiType < GPA_API_NO_SUPPORT)
            {
                LocaleString libFullPath;
                libFullPath.append(GPA_LIB_PREFIX);

                switch (apiType)
                {
#ifdef _WIN32

                    case GPA_API_DIRECTX_11:
                        libFullPath.append(GPA_DIRECTX11_LIB);
                        break;

                    case GPA_API_DIRECTX_12:
                        libFullPath.append(GPA_DIRECTX12_LIB);
                        break;

#endif

                    case GPA_API_OPENGL:
                        libFullPath.append(GPA_OPENGL_LIB);
                        break;

                    case GPA_API_OPENCL:
                        libFullPath.append(GPA_OPENCL_LIB);
                        break;
#ifdef _LINUX

                    case GPA_API_HSA:
                        libFullPath.append(GPA_HSA_LIB);
                        break;
#endif

                    case GPA_API_VULKAN:
                        libFullPath.append(GPA_VULKAN_LIB);
                        break;

                    default:
                        status = GPA_STATUS_ERROR_API_NOT_SUPPORTED;

                }

#ifdef GPA_IS_64_BIT
                libFullPath.append(GPA_X64_ARCH_SUFFIX);
#else
                libFullPath.append(GPA_X86_ARCH_SUFFIX);
#endif

#ifdef USE_DEBUG_GPA
                libFullPath.append(GPA_DEBUG_SUFFIX);
#endif

#ifdef USE_INTERNAL_GPA
                libFullPath.append(GPA_INTERNAL_SUFFIX);
#endif

                libFullPath.append(GPA_LIB_SUFFIX);

                if (libPath.empty())
                {
                    libFullPath = GetWorkingDirectoryPath() + libFullPath;
                }
                else
                {
                    LocaleString localLibPath = libPath;
                    LocaleChar pathSep = '/';

                    std::replace(localLibPath.begin(), localLibPath.end(), '\\', '/');

                    if (pathSep != localLibPath[localLibPath.length() - 1])
                    {
                        localLibPath = localLibPath + pathSep;
                    }

                    libFullPath = localLibPath + libFullPath;
                }

                LibHandle libHandle;

#ifdef _WIN32
                libHandle = LoadLibrary(libFullPath.c_str());
#else
                libHandle = dlopen(libFullPath.c_str(), RTLD_LAZY);
#endif
                GPA_GetFuncTablePtrType funcTableFn;

                if (nullptr != libHandle)
                {
#ifdef _WIN32
                    funcTableFn = reinterpret_cast<GPA_GetFuncTablePtrType>(GetProcAddress(libHandle, GPA_GET_FUNCTION_TABLE_FUNCTION_NAME));
#else
                    funcTableFn = reinterpret_cast<GPA_GetFuncTablePtrType>(dlsym(libHandle, GPA_GET_FUNCTION_TABLE_FUNCTION_NAME));
#endif

                    if (nullptr != funcTableFn)
                    {
                        GPAFunctionTable* pGPAFuncTable = new(std::nothrow) GPAFunctionTable();
                        status = funcTableFn(reinterpret_cast<void*>(pGPAFuncTable));

                        if (GPA_STATUS_OK == status)
                        {
                            m_gpaFunctionTables.insert(std::pair<GPA_API_Type, std::pair<LibHandle, GPAFunctionTable*>>(apiType, std::pair<LibHandle, GPAFunctionTable*>(libHandle, pGPAFuncTable)));
                        }
                        else
                        {
                            delete pGPAFuncTable;
                        }
                    }
                    else
                    {
                        status = GPA_STATUS_ERROR_LIB_LOAD_FAILED;
                    }
                }
                else
                {
                    status = GPA_STATUS_ERROR_LIB_LOAD_FAILED;
                }
            }
            else
            {
                status = GPA_STATUS_ERROR_API_NOT_SUPPORTED;
            }
        }

#else

        if (m_gpaFunctionTables.find(apiType) == m_gpaFunctionTables.end())
        {
            GPAFunctionTable* pGPAFuncTable = new(std::nothrow) GPAFunctionTable();

            status = GPA_GetFuncTable(reinterpret_cast<void*>(pGPAFuncTable));
            m_gpaFunctionTables.insert(std::pair<GPA_API_Type, std::pair<LibHandle, GPAFunctionTable*>>(apiType, std::pair<LibHandle, GPAFunctionTable*>(nullptr, pGPAFuncTable)));
        }

#endif
        return status;
    }

    /// Unloads the function table for the passed api
    /// \param[in] apiType api type
    void UnloadApi(const GPA_API_Type& apiType)
    {
        GPAFunctionTable* pGPAFuncTable = GetFunctionTable(apiType);

        if (nullptr != pGPAFuncTable)
        {
            delete pGPAFuncTable;
            LibHandle libHandle = m_gpaFunctionTables[apiType].first;
#ifdef _WIN32
            FreeLibrary(libHandle);
#else
            dlclose(libHandle);
#endif
            m_gpaFunctionTables.erase(apiType);
        }
    }

    /// Get the function table for the passed API
    /// \param[in] apiType api type
    /// \return returns pointer to the api function table if loaded otherwise nullpointer
    GPAFunctionTable* GetFunctionTable(const GPA_API_Type& apiType)
    {
        if (m_gpaFunctionTables.find(apiType) != m_gpaFunctionTables.end())
        {
            return m_gpaFunctionTables[apiType].second;
        }

        return nullptr;
    }

private:
    /// Constructor
    GPAApiManager()
    {}

    /// Destructor
    ~GPAApiManager()
    {
        if (nullptr != m_pGpaApiManager)
        {
            for (std::map<GPA_API_Type, std::pair<LibHandle, GPAFunctionTable*>>::iterator it = m_gpaFunctionTables.begin(); it != m_gpaFunctionTables.end(); ++it)
            {
                delete it->second.second;
            }

            m_gpaFunctionTables.clear();
        }
    }

    static GPAApiManager*                                           m_pGpaApiManager;    ///< GPA Api Manager pointer
    std::map<GPA_API_Type, std::pair<LibHandle, GPAFunctionTable*>> m_gpaFunctionTables; ///< container to hold the function pointer table for all loaded api
};

// Note: For usage - Add Initialization of the static instance in compiling unit
// GPAApiManager* GPAApiManager::m_pGpaApiManager = nullptr;

#endif
