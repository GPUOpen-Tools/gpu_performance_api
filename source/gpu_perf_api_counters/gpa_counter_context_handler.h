//==============================================================================
// Copyright (c) 2020-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA counter context handler.
//==============================================================================

#ifndef GPU_PERF_API_COUNTERS_GPA_COUNTER_CONTEXT_HANDLER_H_
#define GPU_PERF_API_COUNTERS_GPA_COUNTER_CONTEXT_HANDLER_H_

#include "gpu_performance_api/gpu_perf_api_types.h"
#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpa_counter_accessor_interface.h"
#include "gpa_counter_scheduler_interface.h"
#include "gpa_hw_info.h"

/// GpaCounterContextHandler class.
class GpaCounterContextHandler
{
public:
    /// Constructor.
    ///
    /// @param [in] api_type API.
    /// @param [in] sample_type A sample type.
    /// @param [in] gpa_counter_context_hardware_info Context hardware info.
    /// @param [in] context_flags Context flags.
    GpaCounterContextHandler(const GpaApiType&                    api_type,
                             const GpaSessionSampleType           sample_type,
                             const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                             const GpaOpenContextFlags&           context_flags);

    /// Initializes the counter for the context.
    ///
    /// @return true upon success otherwise false.
    bool InitCounters(GpaDriverInfo const& driver_info);

    /// Returns the hardware info of the context.
    ///
    /// @return Pointer to hardware info.
    const GpaHwInfo& GetHardwareInfo() const;

    /// Returns the counter accessor for the given context.
    ///
    /// @return Counter accessor if found for the context else nullptr.
    [[nodiscard]] const IGpaCounterAccessor* GetCounterAccessor() const;

    /// Returns the counter scheduler for the given context.
    ///
    /// @return Counter scheduler for given context else nullptr.
    IGpaCounterScheduler* GetCounterScheduler() const;

private:
    GpaApiType            gpa_api_type_;            ///< API type.
    GpaSessionSampleType  sample_type_;             ///< GPA sample type.
    GpaHwInfo             gpa_hw_info_;             ///< Hardware info.
    GpaOpenContextFlags   gpa_open_context_flags_;  ///< Context flags.
    bool                  initialized_;             ///< Flag indicating context initialization status.
    IGpaCounterAccessor*  gpa_counter_accessor_;    ///< Context counter accessor.
    IGpaCounterScheduler* gpa_counter_scheduler_;   ///< Context counter scheduler.
};

/// _GpaCounterContext struct.
struct _GpaCounterContext
{
    /// Constructor.
    ///
    /// @param [in] gpa_counter_context gpa counter context.
    _GpaCounterContext(GpaCounterContextHandler* gpa_counter_context);

    /// Member from pointer operator overloading.
    ///
    /// @return Returns the pointer to the underlying object.
    GpaCounterContextHandler* operator->() const;

    /// Destructor.
    ~_GpaCounterContext();

    GpaCounterContextHandler* gpa_counter_context_handler;  ///< Underlying GpaCounterContextHandler class object.
};

/// GpaCounterContextManager singleton class
class GpaCounterContextManager
{
public:
    /// Get the instance of virtual context manager.
    ///
    /// @return Static instance of GPA counter context manager.
    static GpaCounterContextManager* Instance();

    /// Deletes the instance.
    static void DeleteInstance();

    /// Deletes the instance if there are zero contexts remaining.
    static void DeleteInstanceIfZero();

    /// Destructor.
    ~GpaCounterContextManager();

    /// Creates a virtual context.
    ///
    /// @param [in] api_type the api whose available counters are requested.
    /// @param [in] sample_type A sample type.
    /// @param [in] gpa_counter_context_hardware_info counter context hardware info.
    /// @param [in] context_flags Flags used to initialize the context. Should be a combination of GpaOpenContextBits.
    /// @param [out] gpa_counter_context Unique identifier of the opened virtual context.
    ///
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    GpaStatus OpenCounterContext(const GpaApiType&                    api_type,
                                 const GpaSessionSampleType           sample_type,
                                 const GpaCounterContextHardwareInfo& gpa_counter_context_hardware_info,
                                 const GpaOpenContextFlags&           context_flags,
                                 GpaCounterContext*                   gpa_counter_context,
                                 GpaDriverInfo const&                 driver_info);

    /// Returns the counter accessor for the given context.
    ///
    /// @param [in] gpa_counter_context Unique identifier of the opened virtual context.
    ///
    /// @return counter accessor if found for the context else nullptr
    [[nodiscard]] const IGpaCounterAccessor* GetCounterAccessor(const GpaCounterContext gpa_counter_context);

    /// Returns the counter scheduler for the given context.
    ///
    /// @param [in] gpa_counter_context Unique identifier of the opened virtual context.
    ///
    /// @return counter scheduler for given context else nullptr
    IGpaCounterScheduler* GetCounterScheduler(const GpaCounterContext gpa_counter_context);

    /// Closes the opened context.
    ///
    /// @param [in] gpa_counter_context Unique identifier of the opened virtual context.
    ///
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    GpaStatus CloseCounterContext(const GpaCounterContext gpa_counter_context);

    /// Checks whether the virtual context is open or not.
    ///
    /// @param [in] gpa_counter_context Unique identifier of the opened virtual context.
    ///
    /// @return true if virtual context is open otherwise false.
    bool IsCounterContextOpen(GpaCounterContext gpa_counter_context);

private:
    /// Constructor
    GpaCounterContextManager() = default;

    /// Initializes the counter context.
    ///
    /// @param [in] api_type API type.
    /// @param [in] sample_type Sample type.
    void Init(const GpaApiType& api_type, const GpaSessionSampleType sample_type);

    /// Initializes the counter accessor.
    ///
    /// @param [in] api_type API type.
    /// @param [in] sample_type Sample type.
    void InitCounterAccessor(const GpaApiType& api_type, const GpaSessionSampleType sample_type);

    /// Initializes the counter scheduler.
    ///
    /// @param [in] api_type API type.
    /// @param [in] sample_type Sample type.
    void InitCounterScheduler(const GpaApiType& api_type, const GpaSessionSampleType sample_type);

    /// Closes all the contexts.
    void CloseAllContext();

    static GpaCounterContextManager*            gpa_counter_context_manager_;  ///< Static instance of counter context manager.
    std::map<GpaCounterContext, GpaApiType>     gpa_counter_context_map_;      ///< Map of counter contexts vs API.
    std::map<GpaApiType, IGpaCounterAccessor*>  gpa_counter_accessor_map_;     ///< Map of counter accessor.
    std::map<GpaApiType, IGpaCounterScheduler*> gpa_counter_scheduler_map_;    ///< Map of counter scheduler.
};

#endif
