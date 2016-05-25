//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This file provides access to the an API's runtime module
//==============================================================================

#ifndef _API_RT_MODULE_LOADER_H_
#define _API_RT_MODULE_LOADER_H_

#include <new>

#include "TSingleton.h"

/// Singleton to hold global API RT Module
template <class T>
class APIRTModuleLoader : public TSingleton<APIRTModuleLoader<T> >
{
    /// TSingleton needs to be able to use our constructor.
    friend class TSingleton<APIRTModuleLoader<T> >;

public:
    /// Destructor
    virtual ~APIRTModuleLoader()
    {
        if (nullptr != m_pRtModule)
        {
            m_pRtModule->UnloadModule();
            delete m_pRtModule;
            m_pRtModule = nullptr;
        }
    }

    /// Checks whether or not the RT Module is loaded
    /// \return true if the RT Module is loaded, false otherwise
    bool IsModuleLoaded()
    {
        bool retVal = false;

        if (nullptr != m_pRtModule)
        {
            retVal = m_pRtModule->IsModuleLoaded();
        }

        return retVal;
    }

    /// Gets the Runtime Module
    /// \return the Runtime Module
    T* GetAPIRTModule()
    {
        if (nullptr == m_pRtModule)
        {
            m_pRtModule = new(std::nothrow) T();
        }

        return m_pRtModule;
    };

private:
    T* m_pRtModule = nullptr; ///< the DynamicLibraryModule instance that wraps the RT API
};

#endif  //_API_RT_MODULE_LOADER_H_
