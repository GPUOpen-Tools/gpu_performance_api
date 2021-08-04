//==============================================================================
// Copyright (c) 2020-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Gpa counter context
//==============================================================================

#ifndef _GPA_COUNTER_CONTEXT_H_
#define _GPA_COUNTER_CONTEXT_H_

#include "gpu_performance_api/gpu_perf_api_types.h"
#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpa_counter_accessor_interface.h"
#include "gpa_counter_scheduler_interface.h"
#include "gpa_hw_info.h"

/// GpaCounterContextHandler class
class GpaCounterContextHandler
{
public:
    /// Constructor
    /// @param [in] api_type API
    /// @param [in] gpa_counter_context_hardware_info context hardware info
    /// @param [in] context_flags context flags
    /// @param [in] generate_asic_specific_counters flag indicating asic specific counter generation is required
    GpaCounterContextHandler(const GpaApiType&                    api_type,
                             const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                             const GpaOpenContextFlags&           context_flags,
                             const GpaUInt8&                      generate_asic_specific_counters);

    /// Initializes the counter for the context
    /// @return true upon success otherwise false
    bool InitCounters();

    /// Returns the hardware info of the context
    /// @return pointer to hardware info
    const GpaHwInfo* GetHardwareInfo() const;

    /// Returns the counter accessor for the given context
    /// @return counter accessor if found for the context else nullptr
    const IGpaCounterAccessor* GetCounterAccessor() const;

    /// Returns the counter scheduler for the given context
    /// @return counter scheduler for given context else nullptr
    IGpaCounterScheduler* GetCounterScheduler() const;

private:
    GpaApiType            gpa_api_type_;            ///< api type
    GpaHwInfo            gpa_hw_info_;             ///< hardware info
    bool                  asic_specific_;           ///< asic specific flag
    GpaOpenContextFlags   gpa_open_context_flags_;  ///< context flags
    bool                  initialized_;             ///< flag indicating context initialization status
    IGpaCounterAccessor*  gpa_counter_accessor_;    ///< context counter accessor
    IGpaCounterScheduler* gpa_counter_scheduler_;   ///< context counter scheduler
};

/// _GpaCounterContext struct
struct _GpaCounterContext
{
    /// Constructor
    /// @param [in] gpa_counter_context gpa counter context
    _GpaCounterContext(GpaCounterContextHandler* gpa_counter_context);

    /// member from pointer operator overloading
    /// @return returns the pointer to the underlying object
    GpaCounterContextHandler* operator->() const;

    ///Destructor
    ~_GpaCounterContext();

    GpaCounterContextHandler* gpa_counter_context_handler;  ///< underlying GpaCounterContextHandler class object
};

/// GpaCounterContextManager singleton class
class GpaCounterContextManager
{
public:
    /// Get the instance of virtual context manager
    /// @return static instance of gpa virtual context manager
    static GpaCounterContextManager* Instance();

    /// Deletes the instance
    static void DeleteInstance();

    /// Destructor
    ~GpaCounterContextManager();

    /// creates a virtual context
    /// @param [in] api_type the api whose available counters are requested.
    /// @param [in] gpa_counter_context_hardware_info counter context hardware info.
    /// @param [in] context_flags Flags used to initialize the context. Should be a combination of GPA_OpenContext_Bits.
    /// @param [in] generate_asic_specific_counters Flag that indicates whether the counters should be ASIC specific, if available.
    /// @param [out] gpa_counter_context Unique identifier of the opened virtual context.
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    GpaStatus OpenCounterContext(const GpaApiType&                    api_type,
                                 const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                                 const GpaOpenContextFlags&           context_flags,
                                 const GpaUInt8&                      generate_asic_specific_counters,
                                 GpaCounterContext*                   gpa_counter_context);

    /// Returns the counter accessor for the given context
    /// @param [in] gpa_counter_context Unique identifier of the opened virtual context.
    /// @return counter accessor if found for the context else nullptr
    const IGpaCounterAccessor* GetCounterAccessor(const GpaCounterContext gpa_counter_context);

    /// Returns the counter scheduler for the given context
    /// @param [in] gpa_counter_context Unique identifier of the opened virtual context.
    /// @return counter scheduler for given context else nullptr
    IGpaCounterScheduler* GetCounterScheduler(const GpaCounterContext gpa_counter_context);

    /// Closes the opened context
    /// @param [in] gpa_counter_context Unique identifier of the opened virtual context.
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    GpaStatus CloseCounterContext(const GpaCounterContext gpa_counter_context);

    /// Checks whether the virtual context is open or not
    /// @param [in] gpa_counter_context Unique identifier of the opened virtual context.
    /// @return true if virtual context is open otherwise false
    bool IsCounterContextOpen(GpaCounterContext gpa_counter_context);

private:
    /// Constructor
    GpaCounterContextManager() = default;

    /// Initializes the counter context
    /// @param [in] api_type api type
    void Init(const GpaApiType& api_type);

    /// Initializes the counter accessor
    /// @param [in] api_type api type
    void InitCounterAccessor(const GpaApiType& api_type);

    /// Initializes the counter scheduler
    /// @param [in] api_type api type
    void InitCounterScheduler(const GpaApiType& api_type);

    /// Closes all the contexts
    void CloseAllContext();

    static GpaCounterContextManager*            gpa_counter_context_manager_;  ///< static instance of counter context manager
    std::map<GpaCounterContext, GpaApiType>     gpa_counter_context_map_;      ///< map of counter contexts vs api
    std::map<GpaApiType, IGpaCounterAccessor*>  gpa_counter_accessor_map_;     ///< map of counter accessor
    std::map<GpaApiType, IGpaCounterScheduler*> gpa_counter_scheduler_map_;    ///< map of counter scheduler
};

#endif  //_GPA_COUNTER_CONTEXT_H_