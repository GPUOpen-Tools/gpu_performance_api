//==============================================================================
// Copyright (c) 2020-2021 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Deprecated header; use gpu_performance_api/gpu_perf_api_interface_loader.h
//==============================================================================

#pragma message("Warning: You are including a deprecated header. Please use gpu_performance_api/gpu_perf_api_interface_loader.h")

// Note: For usage, copy and paste (and then uncomment) the
// following four lines into a compilation unit that uses
// this header file. These are needed to initialize
// static/extern data declared in this header file:

// #ifdef __cplusplus
// GPAApiManager* GPAApiManager::m_pGpaApiManager = nullptr;
// #endif
// GPAFuncTableInfo* g_pFuncTableInfo = NULL;

// In order to use this header file with a debug build of GPA
// the "USE_DEBUG_GPA" preprocessor macro should be defined before
// including this header file

// In order to use this header file with an internal build of GPA
// the "USE_INTERNAL_GPA" preprocessor macro should be defined before
// including this header file

#ifndef GPU_PERF_API_INTERFACE_LOADER_H_
#define GPU_PERF_API_INTERFACE_LOADER_H_

// New header
#include "gpu_performance_api/gpu_perf_api_interface_loader.h"

// Deprecated headers
#include "gpu_perf_api_types.h"
#include "gpu_perf_api.h"

#define GPA_GET_FUNCTION_TABLE_FUNCTION_NAME_DEPRECATED "GPA_GetFuncTable"  ///< Macro for GPA_GetFuncTable entry point

/// GPAFunctionTableInfo structure
typedef struct _GPAFuncTableInfo
{
    GPA_API_Type      m_gpaApiType;     ///< API type
    GPAFunctionTable* m_pGpaFuncTable;  ///< GPA function table
    LibHandle         m_libHandle;      ///< library handle
    void*             m_pNext;          ///< pointer to next function table info
} GPAFuncTableInfo;

extern GPAFuncTableInfo* g_pFuncTableInfo;  ///< global instance of GPA function table info

/// Get the current working directory
/// \return the current working directory
static const LocaleChar* GPAIL_GetWorkingDirectoryPath()
{
    return GpaInterfaceLoaderGetWorkingDirectoryPath();
}

/// Gets the library file name for the given API
/// \param[in] pApiType type of the API
/// \return library file name
static inline const LocaleChar* GPAIL_GetLibraryFileName(GPA_API_Type pApiType)
{
    return GpaInterfaceLoaderGetLibraryFileName((GpaApiType)pApiType);
}

/// Get the library full path
/// \param[in] apiType type of the API
/// \param[in] pLibPath local path to the library files
/// \return library with full path
static inline const LocaleChar* GPAIL_GetLibraryFullPath(GPA_API_Type apiType, const LocaleChar* pLibPath)
{
    return GpaInterfaceLoaderGetLibraryFullPath((GpaApiType)apiType, pLibPath);
}

/// Loads the dll and initialize the function table for the given API
/// \param[in] apiType type of the API to be loaded
/// \param[in] pLibPath path to the folder containing dll
/// \return GPA_STATUS_OK upon successful operation
static inline GPA_Status GPAIL_LoadApi(GPA_API_Type apiType, const LocaleChar* pLibPath)
{
    // Dummy calls
    GPAIL_GetWorkingDirectoryPath();
    GPAIL_GetLibraryFileName(apiType);

#if DISABLE_GPA
    UNREFERENCED_PARAMETER(apiType);
    UNREFERENCED_PARAMETER(pLibPath);
    if (NULL == g_pFuncTableInfo)
    {
        g_pFuncTableInfo                  = (GPAFuncTableInfo*)malloc(sizeof(GPAFuncTableInfo));
        g_pFuncTableInfo->m_pGpaFuncTable = (GPAFunctionTable*)malloc(sizeof(GPAFunctionTable));
    }

    g_pFuncTableInfo->m_gpaApiType                = GPA_API__LAST;
    g_pFuncTableInfo->m_libHandle                 = NULL;
    g_pFuncTableInfo->m_pGpaFuncTable->m_majorVer = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
    g_pFuncTableInfo->m_pGpaFuncTable->m_minorVer = GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER;
    GPA_Status status                             = GPA_GetFuncTable(g_pFuncTableInfo->m_pGpaFuncTable);
    g_pFuncTableInfo->m_pNext                     = NULL;
#else
    if (NULL == g_pFuncTableInfo)
    {
        g_pFuncTableInfo = (GPAFuncTableInfo*)malloc(sizeof(GPAFuncTableInfo));

        if (NULL != g_pFuncTableInfo)
        {
            g_pFuncTableInfo->m_gpaApiType    = GPA_API_NO_SUPPORT;
            g_pFuncTableInfo->m_libHandle     = NULL;
            g_pFuncTableInfo->m_pGpaFuncTable = NULL;
            g_pFuncTableInfo->m_pNext         = NULL;
        }
    }

    GPA_Status status = GPA_STATUS_ERROR_FAILED;

    if (NULL != g_pFuncTableInfo)
    {
        status = GPA_STATUS_OK;

        if (apiType >= GPA_API__START && apiType < GPA_API_NO_SUPPORT)
        {
            const LocaleChar* pLibName = GPAIL_GetLibraryFileName(apiType);

            if (NULL == pLibName)
            {
                return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
            }

            {
                GPAFuncTableInfo* pFunctionTableInfo = g_pFuncTableInfo;

                while (NULL != pFunctionTableInfo)
                {
                    if (pFunctionTableInfo->m_gpaApiType == apiType)
                    {
                        return GPA_STATUS_ERROR_LIB_ALREADY_LOADED;
                    }

                    pFunctionTableInfo = (GPAFuncTableInfo*)pFunctionTableInfo->m_pNext;
                }
            }

            const LocaleChar* pLibFullPath = GPAIL_GetLibraryFullPath(apiType, pLibPath);
            LibHandle         libHandle    = NULL;

#ifdef _WIN32
            libHandle                      = LoadLibrary(pLibFullPath);
#else

#ifdef UNICODE
            char libFullPathChar[GPA_MAX_PATH];
            int  ret             = wcstombs(libFullPathChar, pLibFullPath, GPA_MAX_PATH);
            libFullPathChar[ret] = '\0';
            libHandle            = dlopen(libFullPathChar, RTLD_LAZY);
#else
            libHandle = dlopen(pLibFullPath, RTLD_LAZY);
#endif

#endif
            GPA_GetFuncTablePtrType funcTableFn;

            if (NULL != libHandle)
            {
#ifdef _WIN32
                funcTableFn = (GPA_GetFuncTablePtrType)(GetProcAddress(libHandle, GPA_GET_FUNCTION_TABLE_FUNCTION_NAME_DEPRECATED));
#else
                funcTableFn = (GPA_GetFuncTablePtrType)(dlsym(libHandle, GPA_GET_FUNCTION_TABLE_FUNCTION_NAME_DEPRECATED));
#endif

                if (NULL != funcTableFn)
                {
                    GPAFunctionTable* pGPAFuncTable = (GPAFunctionTable*)malloc(sizeof(GPAFunctionTable));

                    if (NULL == pGPAFuncTable)
                    {
                        return GPA_STATUS_ERROR_FAILED;
                    }

                    pGPAFuncTable->m_majorVer = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
                    pGPAFuncTable->m_minorVer = GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER;
                    status                    = funcTableFn((void*)(pGPAFuncTable));

                    if (GPA_STATUS_OK == status)
                    {
                        if (NULL == g_pFuncTableInfo->m_pGpaFuncTable)
                        {
                            g_pFuncTableInfo->m_gpaApiType    = apiType;
                            g_pFuncTableInfo->m_pGpaFuncTable = pGPAFuncTable;
                            g_pFuncTableInfo->m_libHandle     = libHandle;
                            g_pFuncTableInfo->m_pNext         = NULL;
                        }
                        else
                        {
                            GPAFuncTableInfo* pNewTableInfo = (GPAFuncTableInfo*)malloc(sizeof(GPAFuncTableInfo));

                            if (NULL == pNewTableInfo)
                            {
                                return GPA_STATUS_ERROR_FAILED;
                            }

                            pNewTableInfo->m_gpaApiType    = apiType;
                            pNewTableInfo->m_pGpaFuncTable = pGPAFuncTable;
                            pNewTableInfo->m_libHandle     = libHandle;
                            pNewTableInfo->m_pNext         = NULL;

                            GPAFuncTableInfo* pFunctionTableInfo = g_pFuncTableInfo;

                            while (NULL != pFunctionTableInfo->m_pNext)
                            {
                                pFunctionTableInfo = (GPAFuncTableInfo*)pFunctionTableInfo->m_pNext;
                            }

                            pFunctionTableInfo->m_pNext = pNewTableInfo;
                        }
                    }
                    else
                    {
                        free(pGPAFuncTable);
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
#endif

    return status;
}

/// Get the function table for the given API
/// \param[in] apiType API type
/// \return returns pointer to the API function table if loaded otherwise null pointer
static inline const GPAFunctionTable* GPAIL_GetFunctionTable(GPA_API_Type apiType)
{
#if DISABLE_GPA
    UNREFERENCED_PARAMETER(apiType);
    return g_pFuncTableInfo->m_pGpaFuncTable;
#else
    GPAFuncTableInfo* pFunctionTableInfo = g_pFuncTableInfo;
    GPAFunctionTable* pRetFuncTable      = NULL;

    while (NULL != pFunctionTableInfo)
    {
        if (pFunctionTableInfo->m_gpaApiType == apiType)
        {
            pRetFuncTable = pFunctionTableInfo->m_pGpaFuncTable;
            break;
        }

        pFunctionTableInfo = (GPAFuncTableInfo*)pFunctionTableInfo->m_pNext;
    }

    return pRetFuncTable;
#endif
}

/// Unloads the function table for the given API
/// \param[in] apiType API type
/// \return GPA_STATUS_OK upon successful operation
static inline GPA_Status GPAIL_UnLoadApi(GPA_API_Type apiType)
{
#if DISABLE_GPA
    UNREFERENCED_PARAMETER(apiType);
    return GPA_STATUS_OK;
#else
    GPA_Status status = GPA_STATUS_ERROR_FAILED;

    GPAFuncTableInfo* pFunctionTableInfo = g_pFuncTableInfo;

    while (NULL != pFunctionTableInfo)
    {
        if (pFunctionTableInfo->m_gpaApiType == apiType)
        {
            free(pFunctionTableInfo->m_pGpaFuncTable);
            LibHandle libHandle = pFunctionTableInfo->m_libHandle;

            if (NULL != libHandle)
            {
#ifdef _WIN32
                FreeLibrary(libHandle);
#else
                dlclose(libHandle);
#endif
                pFunctionTableInfo->m_libHandle     = NULL;
                pFunctionTableInfo->m_pGpaFuncTable = NULL;
                status                              = GPA_STATUS_OK;
                break;
            }
        }

        pFunctionTableInfo = (GPAFuncTableInfo*)pFunctionTableInfo->m_pNext;
    }

    return status;
#endif
}

/// Clears the loader
static inline void GPAIL_ClearLoader()
{
#if DISABLE_GPA
    g_pFuncTableInfo->m_gpaApiType    = GPA_API_NO_SUPPORT;
    g_pFuncTableInfo->m_libHandle     = NULL;
    g_pFuncTableInfo->m_pNext         = NULL;
    g_pFuncTableInfo->m_pGpaFuncTable = NULL;
#else
    if (NULL != g_pFuncTableInfo)
    {
        while (NULL != g_pFuncTableInfo->m_pNext)
        {
            GPAFuncTableInfo* pFunctionTableInfo = (GPAFuncTableInfo*)(g_pFuncTableInfo->m_pNext);

            if (NULL != pFunctionTableInfo->m_libHandle)
            {
#ifdef _WIN32
                FreeLibrary(pFunctionTableInfo->m_libHandle);
#else
                dlclose(pFunctionTableInfo->m_libHandle);
#endif
                pFunctionTableInfo->m_libHandle = NULL;
            }

            if (NULL != pFunctionTableInfo->m_pGpaFuncTable)
            {
                free(pFunctionTableInfo->m_pGpaFuncTable);
                pFunctionTableInfo->m_pGpaFuncTable = NULL;
            }

            if (NULL != pFunctionTableInfo->m_pNext)
            {
                g_pFuncTableInfo->m_pNext = pFunctionTableInfo->m_pNext;
                free(pFunctionTableInfo);
            }
            else
            {
                g_pFuncTableInfo->m_pNext = NULL;
            }
        }

        if (NULL != g_pFuncTableInfo->m_libHandle)
        {
#ifdef _WIN32
            FreeLibrary(g_pFuncTableInfo->m_libHandle);
#else
            dlclose(g_pFuncTableInfo->m_libHandle);
#endif
            g_pFuncTableInfo->m_libHandle = NULL;
        }

        if (NULL != g_pFuncTableInfo->m_pGpaFuncTable)
        {
            free(g_pFuncTableInfo->m_pGpaFuncTable);
            g_pFuncTableInfo->m_pGpaFuncTable = NULL;
        }

        g_pFuncTableInfo->m_gpaApiType = GPA_API_NO_SUPPORT;
        free(g_pFuncTableInfo);
        g_pFuncTableInfo = NULL;
    }
#endif
}

#ifdef __cplusplus
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
            m_pGpaApiManager = new (std::nothrow) GPAApiManager();
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

    /// Loads the dll and initialize the function table for the passed API type
    /// \param[in] apiType type of the API to be loaded
    /// \param[in] libPath path to the folder containing dll
    /// \return returns appropriate status of the operation
    GPA_Status LoadApi(const GPA_API_Type& apiType, const LocaleString libPath = LocaleString()) const
    {
        LocaleChar libPathAsChar[GPA_MAX_PATH] = {0};
        bool       localPathGiven              = false;

        if (!libPath.empty())
        {
            STR_COPY(libPathAsChar, ARRAY_LENGTH(libPathAsChar), libPath.c_str());
            localPathGiven = true;
        }

        return GPAIL_LoadApi(apiType, localPathGiven ? libPathAsChar : NULL);
    }

    /// Unloads the function table for the passed API
    /// \param[in] apiType API type
    void UnloadApi(const GPA_API_Type& apiType) const
    {
        GPAIL_UnLoadApi(apiType);
    }

    /// Get the function table for the passed API
    /// \param[in] apiType API type
    /// \return returns pointer to the API function table if loaded otherwise null pointer
    GPAFunctionTable* GetFunctionTable(const GPA_API_Type& apiType) const
    {
        return const_cast<GPAFunctionTable*>(GPAIL_GetFunctionTable(apiType));
    }

    /// Gets the library file name for the given API
    /// \param[in] apiType type of the API
    /// \return library file name string
    LocaleString GetLibraryFileName(const GPA_API_Type& apiType) const
    {
        return LocaleString(GPAIL_GetLibraryFileName(apiType));
    }

    /// Get the library full path
    /// \param[in] apiType type of the API
    /// \param[in,opt] libPath local path to the library files
    /// \return library with full path string
    LocaleString GetLibraryFullPath(const GPA_API_Type& apiType, const LocaleString libPath = LocaleString()) const
    {
        LocaleChar libPathAsChar[GPA_MAX_PATH] = {0};
        bool       localPathGiven              = false;

        if (!libPath.empty())
        {
            STR_COPY(libPathAsChar, ARRAY_LENGTH(libPathAsChar), libPath.c_str());
            localPathGiven = true;
        }

        return LocaleString(GPAIL_GetLibraryFullPath(apiType, localPathGiven ? libPathAsChar : NULL));
    }

private:
    /// Constructor
    GPAApiManager() = default;

    /// Destructor
    ~GPAApiManager()
    {
        GPAIL_ClearLoader();
    }

    static GPAApiManager* m_pGpaApiManager;  ///< GPA Api Manager pointer
};

#endif  //__cplusplus

#endif  // GPU_PERF_API_INTERFACE_LOADER_H_
