//==============================================================================
// Copyright (c) 2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Gpa counter context
//==============================================================================

#ifndef _GPA_COUNTER_CONTEXT_H_
#define _GPA_COUNTER_CONTEXT_H_

#include "gpu_perf_api_types.h"
#include "gpu_perf_api_counters.h"
#include "gpa_counter_accessor_interface.h"
#include "gpa_counter_scheduler_interface.h"
#include "gpa_hw_info.h"

/// GpaCounterContext class
class GpaCounterContext
{
public:
    /// Constructor
    /// \param[in] api_type API
    /// \param[in] gpa_counter_context_hardware_info context hardware info
    /// \param[in] context_flags context flags
    /// \param[in] generate_asic_specific_counters flag indicating asic specific counter generation is required
    GpaCounterContext(const GPA_API_Type&                  api_type,
                      const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                      const GPA_OpenContextFlags&          context_flags,
                      const gpa_uint8&                     generate_asic_specific_counters);

    /// Initializes the counter for the context
    /// \return true upon success otherwise false
    bool InitCounters();

    /// Returns the hardware info of the context
    /// \return pointer to hardware info
    const GPA_HWInfo* GetHardwareInfo() const;

    /// Returns the counter accessor for the given context
    /// \return counter accessor if found for the context else nullptr
    const IGPACounterAccessor* GetCounterAccessor() const;

    /// Returns the counter scheduler for the given context
    /// \return counter scheduler for given context else nullptr
    IGPACounterScheduler* GetCounterScheduler() const;

private:
    GPA_API_Type          gpa_api_type_;            ///< api type
    GPA_HWInfo            gpa_hw_info_;             ///< hardware info
    bool                  asic_specific_;           ///< asic specific flag
    GPA_OpenContextFlags  gpa_open_context_flags_;  ///< context flags
    bool                  initialized_;             ///< flag indicating context initialization status
    IGPACounterAccessor*  gpa_counter_accessor_;    ///< context counter accessor
    IGPACounterScheduler* gpa_counter_scheduler_;   ///< context counter scheduler
};

/// _GPA_CounterContext struct
struct _GPA_CounterContext
{
    /// Constructor
    /// \param[in] gpa_counter_context gpa counter context
    _GPA_CounterContext(GpaCounterContext* gpa_counter_context);

    /// member from pointer operator overloading
    /// \return returns the pointer to the underlying object
    GpaCounterContext* operator->() const;

    ///Destructor
    ~_GPA_CounterContext();

    GpaCounterContext* gpa_counter_context;  ///< underlying GpaCounterContext class object
};

/// GpaCounterContextManager singleton class
class GpaCounterContextManager
{
public:
    /// Get the instance of virtual context manager
    /// \return static instance of gpa virtual context manager
    static GpaCounterContextManager* Instance();

    /// Deletes the instance
    static void DeleteInstance();

    /// Destructor
    ~GpaCounterContextManager();

    /// creates a virtual context
    /// \param[in] api_type the api whose available counters are requested.
    /// \param[in] gpa_counter_context_hardware_info counter context hardware info.
    /// \param[in] context_flags Flags used to initialize the context. Should be a combination of GPA_OpenContext_Bits.
    /// \param[in] generate_asic_specific_counters Flag that indicates whether the counters should be ASIC specific, if available.
    /// \param[out] gpa_counter_context Unique identifier of the opened virtual context.
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    GPA_Status OpenCounterContext(const GPA_API_Type&                  api_type,
                                  const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                                  const GPA_OpenContextFlags&          context_flags,
                                  const gpa_uint8&                     generate_asic_specific_counters,
                                  GPA_CounterContext*                  gpa_counter_context);

    /// Returns the counter accessor for the given context
    /// \param[in] gpa_counter_context Unique identifier of the opened virtual context.
    /// \return counter accessor if found for the context else nullptr
    const IGPACounterAccessor* GetCounterAccessor(const GPA_CounterContext gpa_counter_context);

    /// Returns the counter scheduler for the given context
    /// \param[in] gpa_counter_context Unique identifier of the opened virtual context.
    /// \return counter scheduler for given context else nullptr
    IGPACounterScheduler* GetCounterScheduler(const GPA_CounterContext gpa_counter_context);

    /// Closes the opened context
    /// \param[in] gpa_counter_context Unique identifier of the opened virtual context.
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    GPA_Status CloseCounterContext(const GPA_CounterContext gpa_counter_context);

    /// Checks whether the virtual context is open or not
    /// \param[in] gpa_counter_context Unique identifier of the opened virtual context.
    /// \return true if virtual context is open otherwise false
    bool IsCounterContextOpen(GPA_CounterContext gpa_counter_context);

private:
    /// Constructor
    GpaCounterContextManager() = default;

    /// Initializes the counter context
    /// \param[in] api_type api type
    void Init(const GPA_API_Type& api_type);

    /// Initializes the counter accessor
    /// \param[in] api_type api type
    void InitCounterAccessor(const GPA_API_Type& api_type);

    /// Initializes the counter scheduler
    /// \param[in] api_type api type
    void InitCounterScheduler(const GPA_API_Type& api_type);

    /// Closes all the contexts
    void CloseAllContext();

    static GpaCounterContextManager*              gpa_counter_context_manager_;  ///< static instance of counter context manager
    std::map<GPA_CounterContext, GPA_API_Type>    gpa_counter_context_map_;      ///< map of counter contexts vs api
    std::map<GPA_API_Type, IGPACounterAccessor*>  gpa_counter_accessor_map_;     ///< map of counter accessor
    std::map<GPA_API_Type, IGPACounterScheduler*> gpa_counter_scheduler_map_;    ///< map of counter scheduler
};

#endif  //_GPA_COUNTER_CONTEXT_H_