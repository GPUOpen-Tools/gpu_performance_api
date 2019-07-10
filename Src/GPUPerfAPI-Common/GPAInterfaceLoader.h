//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Interface Loader Utility header file
//==============================================================================

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

#ifndef _GPA_INTERFACE_LOADER_H_
#define _GPA_INTERFACE_LOADER_H_

#ifdef _WIN32
#include <Windows.h>
#define GPA_MAX_PATH MAX_PATH  ///< Macro for max path length
#ifdef _WIN64
#define GPA_IS_64_BIT  ///< Macro specifying 64-bit build
#else
#define GPA_IS_32_BIT  ///< Macro specifying 32-bit build
#endif
#else
#include <dlfcn.h>
#include <unistd.h>
#define GPA_MAX_PATH 4096  ///< Macro for max path length
#ifdef __x86_64__
#define GPA_IS_64_BIT  ///< Macro specifying 64-bit build
#else
#define GPA_IS_32_BIT  ///< Macro specifying 32-bit build
#endif
#endif

#include <wchar.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
#include <string>
#endif

#include "GPUPerfAPI.h"

#ifdef UNICODE
typedef wchar_t LocaleChar;  ///< Typedef for ANSI vs. Unicode character
#ifdef __cplusplus
typedef std::wstring LocaleString;  ///< Typedef for ANSI vs. Unicode string
#endif

#define TFORMAT2(x) L##x        ///< Macro for string expansion
#define TFORMAT(x) TFORMAT2(x)  ///< Macro for string expansion

#define STR_CAT(dest, destSize, src) wcscat_s(dest, destSize, src)                    ///< Macro for safe strcat
#define STR_COPY(dest, destSize, src) wcscpy_s(dest, destSize, src)                   ///< Macro for safe strcpy
#define STR_NCOPY(dest, destSize, src, count) wcsncpy_s(dest, destSize, src, count);  ///< Macro for safe strncpy
#define STR_LEN(str, strLength) wcsnlen_s(str, strLength)                             ///< Macro for safe strnlen
#else
typedef char        LocaleChar;    ///< Typedef for ANSI vs. Unicode character
#ifdef __cplusplus
typedef std::string LocaleString;  ///< Typedef for ANSI vs. Unicode string
#endif

#define TFORMAT(x) (x)  ///< Macro for string expansion

#define STR_CAT(dest, destSize, src) strcat_s(dest, destSize, src)                    ///< Macro for safe strcat
#define STR_COPY(dest, destSize, src) strcpy_s(dest, destSize, src)                   ///< Macro for safe strcpy
#define STR_NCOPY(dest, destSize, src, count) strncpy_s(dest, destSize, src, count);  ///< Macro for safe strncpy
#define STR_LEN(str, strLength) strnlen_s(str, strLength)                             ///< Macro for safe strnlen
#endif

#define GPA_OPENCL_LIB TFORMAT("GPUPerfAPICL")       ///< Macro for base name of GPA OpenCL library
#define GPA_OPENGL_LIB TFORMAT("GPUPerfAPIGL")       ///< Macro for base name of GPA OpenGL library
#define GPA_DIRECTX11_LIB TFORMAT("GPUPerfAPIDX11")  ///< Macro for base name of GPA DirectX 11 library
#define GPA_DIRECTX12_LIB TFORMAT("GPUPerfAPIDX12")  ///< Macro for base name of GPA DirectX 12 library
#define GPA_VULKAN_LIB TFORMAT("GPUPerfAPIVK")       ///< Macro for base name of GPA Vulkan library
#define GPA_ROCM_LIB TFORMAT("GPUPerfAPIROCm")       ///< Macro for base name of GPA ROCm library

#ifdef _WIN32
#define GPA_LIB_PREFIX TFORMAT("")           ///< Macro for platform-specific lib file prefix
#define GPA_LIB_SUFFIX TFORMAT(".dll")       ///< Macro for platform-specific lib file suffix
#define GPA_X64_ARCH_SUFFIX TFORMAT("-x64")  ///< Macro for 64-bit lib file architecture suffix
#define GPA_X86_ARCH_SUFFIX TFORMAT("")      ///< Macro for 32-bit lib file architecture suffix
#else
#define GPA_LIB_PREFIX TFORMAT("lib")      ///< Macro for platform-specific lib file prefix
#define GPA_LIB_SUFFIX TFORMAT(".so")      ///< Macro for platform-specific lib file suffix
#define GPA_X64_ARCH_SUFFIX TFORMAT("")    ///< Macro for 64-bit lib file architecture suffix
#define GPA_X86_ARCH_SUFFIX TFORMAT("32")  ///< Macro for 32-bit lib file architecture suffix
#endif

#define GPA_DEBUG_SUFFIX TFORMAT("-d")            ///< Macro for debug suffix
#define GPA_INTERNAL_SUFFIX TFORMAT("-Internal")  ///< Macro for internal build lib file suffix

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))  ///< Macro to calculate array length

#define GPA_GET_FUNCTION_TABLE_FUNCTION_NAME "GPA_GetFuncTable"  ///< Macro for GPA_GetFuncTable entry point

/// GPAFunctionTableInfo structure
typedef struct _GPAFuncTableInfo
{
    GPA_API_Type      m_gpaApiType;     ///< API type
    GPAFunctionTable* m_pGpaFuncTable;  ///< GPA function table
    LibHandle         m_libHandle;      ///< library handle
    void*             m_pNext;          ///< pointer to next function table info
} GPAFuncTableInfo;

extern GPAFuncTableInfo* g_pFuncTableInfo;  ///< global instance of GPA function table info

/// Replaces the Windows style path separator to Unix style
/// \param[in] pFilePath file path
/// \param[out] pLastSeparatorPosition if not null, last separator position in the path string will be returned
static inline void Win2UnixPathSeparator(LocaleChar* pFilePath, unsigned int* pLastSeparatorPosition)
{
    unsigned int counter      = 0;
    unsigned int lastSlashPos = 0;

    while ('\0' != pFilePath[counter])
    {
        if ('\\' == pFilePath[counter])
        {
            pFilePath[counter] = '/';
        }

        if ('/' == pFilePath[counter])
        {
            lastSlashPos = counter;
        }

        ++counter;
    }

    if (NULL != pLastSeparatorPosition)
    {
        *pLastSeparatorPosition = lastSlashPos;
    }
}

/// Get the current working directory
/// \return the current working directory
static const LocaleChar* GPAIL_GetWorkingDirectoryPath()
{
    static LocaleChar workingDirectoryStaticString[GPA_MAX_PATH];

    workingDirectoryStaticString[0] = 0;

    LocaleChar tempWorkingDirectoryPath[GPA_MAX_PATH] = {0};

#ifdef _WIN32
    GetModuleFileName(NULL, tempWorkingDirectoryPath, ARRAY_LENGTH(tempWorkingDirectoryPath));
#else
    int len;
    len = readlink("/proc/self/exe", tempWorkingDirectoryPath, ARRAY_LENGTH(tempWorkingDirectoryPath) - 1);

    if (len != -1)
    {
        tempWorkingDirectoryPath[len] = '\0';
    }

#endif

    unsigned int lastSlashPos = 0;

    Win2UnixPathSeparator(tempWorkingDirectoryPath, &lastSlashPos);

    memset(workingDirectoryStaticString, 0, sizeof(LocaleChar) * ARRAY_LENGTH(workingDirectoryStaticString));
    STR_NCOPY(workingDirectoryStaticString, ARRAY_LENGTH(workingDirectoryStaticString), tempWorkingDirectoryPath, lastSlashPos);
    return workingDirectoryStaticString;
}

/// Gets the library file name for the given API
/// \param[in] pApiType type of the API
/// \return library file name
static inline const LocaleChar* GPAIL_GetLibraryFileName(GPA_API_Type pApiType)
{
    static LocaleChar filenameStaticString[GPA_MAX_PATH];

    filenameStaticString[0] = 0;

    STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_LIB_PREFIX);

    switch (pApiType)
    {
#ifdef _WIN32

    case GPA_API_DIRECTX_11:
        STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_DIRECTX11_LIB);
        break;

    case GPA_API_DIRECTX_12:
        STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_DIRECTX12_LIB);
        break;
#else

    case GPA_API_ROCM:
        STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_ROCM_LIB);
        break;
#endif

    case GPA_API_OPENGL:
        STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_OPENGL_LIB);
        break;

    case GPA_API_OPENCL:
        STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_OPENCL_LIB);
        break;

    case GPA_API_VULKAN:
        STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_VULKAN_LIB);
        break;

    default:
        memset(filenameStaticString, 0, sizeof(filenameStaticString));
        return filenameStaticString;
    }

#ifdef GPA_IS_64_BIT
    STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_X64_ARCH_SUFFIX);
#else
    STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_X86_ARCH_SUFFIX);
#endif

#ifdef USE_DEBUG_GPA
    STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_DEBUG_SUFFIX);
#endif

#ifdef USE_INTERNAL_GPA
    STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_INTERNAL_SUFFIX);
#endif

    STR_CAT(filenameStaticString, ARRAY_LENGTH(filenameStaticString), GPA_LIB_SUFFIX);

    return filenameStaticString;
}

/// Get the library full path
/// \param[in] apiType type of the API
/// \param[in] pLibPath local path to the library files
/// \return library with full path
static inline const LocaleChar* GPAIL_GetLibraryFullPath(GPA_API_Type apiType, const LocaleChar* pLibPath)
{
    static LocaleChar libPathStaticString[GPA_MAX_PATH];

    libPathStaticString[0] = 0;

    const LocaleChar* pLibName = GPAIL_GetLibraryFileName(apiType);

    if (STR_LEN(pLibName, GPA_MAX_PATH) > 1)
    {
        LocaleChar tempLibFileName[GPA_MAX_PATH]      = {0};
        LocaleChar tempWorkingDirectory[GPA_MAX_PATH] = {0};

        STR_COPY(tempLibFileName, ARRAY_LENGTH(tempLibFileName), pLibName);

        if (NULL == pLibPath)
        {
            const LocaleChar* pWorkingDirectoryPath = GPAIL_GetWorkingDirectoryPath();
            STR_COPY(tempWorkingDirectory, ARRAY_LENGTH(tempWorkingDirectory), pWorkingDirectoryPath);
        }
        else
        {
            STR_COPY(tempWorkingDirectory, ARRAY_LENGTH(tempWorkingDirectory), pLibPath);
            Win2UnixPathSeparator(tempWorkingDirectory, NULL);
        }

        size_t stringLength = STR_LEN(tempWorkingDirectory, ARRAY_LENGTH(tempWorkingDirectory));

        if (tempWorkingDirectory[stringLength - 1] != '/')
        {
            tempWorkingDirectory[stringLength]     = '/';
            tempWorkingDirectory[stringLength + 1] = '\0';
        }

        memset(libPathStaticString, 0, sizeof(libPathStaticString));
        STR_COPY(libPathStaticString, ARRAY_LENGTH(libPathStaticString), tempWorkingDirectory);
        STR_CAT(libPathStaticString, ARRAY_LENGTH(libPathStaticString), tempLibFileName);
    }

    return libPathStaticString;
}

/// Loads the dll and initialize the function table for the given API
/// \param[in] apiType type of the API to be loaded
/// \param[in] pLibPath path to the folder containing dll
/// \return GPA_STATUS_OK upon successful operation
static inline GPA_Status GPAIL_LoadApi(GPA_API_Type apiType, const LocaleChar* pLibPath)
{
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
            libHandle = dlopen(pLibFullPath, RTLD_LAZY);
#endif
            GPA_GetFuncTablePtrType funcTableFn;

            if (NULL != libHandle)
            {
#ifdef _WIN32
                funcTableFn = (GPA_GetFuncTablePtrType)(GetProcAddress(libHandle, GPA_GET_FUNCTION_TABLE_FUNCTION_NAME));
#else
                funcTableFn = (GPA_GetFuncTablePtrType)(dlsym(libHandle, GPA_GET_FUNCTION_TABLE_FUNCTION_NAME));
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

#endif
