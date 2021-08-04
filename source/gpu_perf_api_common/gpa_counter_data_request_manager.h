//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  An abstract class which manages registration/retrieval of DataRequests.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_COUNTER_DATA_REQUEST_MANAGER_H_
#define GPU_PERF_API_COMMON_GPA_COUNTER_DATA_REQUEST_MANAGER_H_

#include <map>

#include "DeviceInfo.h"

#include "gpu_performance_api/gpu_perf_api_types.h"

class GpaDataRequest;

/// @brief Manager class that will get the correct CounterDataRequest for the given HW generation.
template <typename T>
class GpaCounterDataRequestManager
{
public:
    typedef T* (*CreateDataRequestFn)(void* pUserData);  ///< Function typedef for creating data requests.

    /// @brief Register a counter data request creation function for a specified hardware generation.
    ///
    /// @param [in] generation The hardware generation.
    /// @param [in] create_func The creation function for the specified hardware generation.
    void RegisterCounterDataRequest(GDT_HW_GENERATION generation, CreateDataRequestFn create_func)
    {
        counter_data_request_items_[generation] = create_func;
    }

    /// @brief Gets the counter data request for the specified hardware generations.
    ///
    /// @param [in] generation The hardware generation.
    /// @param [in] user_data User data to pass to the creation function.
    ///
    /// @return The counter data request returned by the creation function.
    T* GetCounterDataRequest(GDT_HW_GENERATION generation, void* user_data)
    {
        if (0 < counter_data_request_items_.count(generation))
        {
            return counter_data_request_items_[generation](user_data);
        }
        else
        {
            return GetDefaultDataRequest();
        }
    }

protected:
    /// @brief Constructor.
    GpaCounterDataRequestManager()
    {
    }

    /// @brief Virtual destructor.
    virtual ~GpaCounterDataRequestManager()
    {
    }

    /// @brief Gets the default data request (if one is not registered). May allocate memory.
    ///
    /// @return The newly created data request.
    virtual T* GetDefaultDataRequest() = 0;

    /// Typedef for the map of generation to creation function.
    typedef std::map<GDT_HW_GENERATION, CreateDataRequestFn> GenerationDataRequestCreatorMap;

    /// Map of generation to creation function.
    GenerationDataRequestCreatorMap counter_data_request_items_;
};

#endif  // GPU_PERF_API_COMMON_GPA_COUNTER_DATA_REQUEST_MANAGER_H_
