//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  An abstract class which manages registration/retrieval of DataRequests
//==============================================================================

#ifndef _GPA_COUNTER_DATA_REQUEST_MANAGER_H_
#define _GPA_COUNTER_DATA_REQUEST_MANAGER_H_

#include <map>

#include <DeviceInfo.h>

#include "GPUPerfAPITypes.h"

class GPA_DataRequest; ///< forward declaration

/// Manager class that will get the correct CounterDataRequest for the given HW generation
template<typename T>
class GPACounterDataRequestManager
{
public:
    typedef T* (*CreateDataRequestFn)(void* pUserData); ///< Function typedef for creating data requests

    /// Register a counter data request creation function for a specified hardware generation
    /// \param generation the hardware generation
    /// \param createFunc the creation function for the specified hardware generation
    void RegisterCounterDataRequest(GDT_HW_GENERATION generation, CreateDataRequestFn createFunc)
    {
        m_counterDataRequestItems[generation] = createFunc;
    }

    /// Gets the counter data request for the specified hardware generations
    /// \param generation the hardware generation
    /// \param pUserData user data to pass to the creation function
    /// \return the counter data request returned by the creation function
    T* GetCounterDataRequest(GDT_HW_GENERATION generation, void* pUserData)
    {
        if (0 < m_counterDataRequestItems.count(generation))
        {
            return m_counterDataRequestItems[generation](pUserData);
        }
        else
        {
            return GetDefaultDataRequest();
        }
    }

protected:
    /// Constructor
    GPACounterDataRequestManager() {}

    /// Destructor
    virtual ~GPACounterDataRequestManager() {}

    /// Gets the default data request (if one is not registered). May allocate memory.
    /// \return the newly created data request
    virtual T* GetDefaultDataRequest() = 0;

    /// typedef for the map of generation to creation function
    typedef std::map<GDT_HW_GENERATION, CreateDataRequestFn> GenerationDataRequestCreatorMap;

    /// map of generation to creation function
    GenerationDataRequestCreatorMap m_counterDataRequestItems;
};

#endif // _GPA_COUNTER_DATA_REQUEST_MANAGER_H_
