//==============================================================================
// Copyright (c) 2012-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Interface to access to the available counters
///         in GPUPerfAPI.
//==============================================================================

#ifndef _GPU_PERF_API_COUNTERS_H_
#define _GPU_PERF_API_COUNTERS_H_

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4201)
#endif

#include "gpu_perf_api_types.h"

#ifndef __cplusplus
#include <stdbool.h>
#endif

/// macro to export public API functions
#ifndef GPU_PERF_API_COUNTERS_DECL
#ifdef _WIN32
#ifdef __cplusplus
#define GPU_PERF_API_COUNTERS_DECL extern "C" __declspec(dllimport)
#else
#define GPU_PERF_API_COUNTERS_DECL __declspec(dllimport)
#endif
#else  //_LINUX
#define GPU_PERF_API_COUNTERS_DECL extern
#endif
#endif

/// Virtual Context ID opaque pointer type
GPA_DEFINE_OBJECT(CounterContext)

/// Gpa counter library major version
#define GPA_COUNTER_LIB_FUNC_TABLE_MAJOR_VERSION 3

/// Gpa counter library minor version
#define GPA_COUNTER_LIB_FUNC_TABLE_MINOR_VERSION (sizeof(struct _GpaCounterLibFuncTable))

/// Gpa hardware blocks
typedef enum
{
    GPA_HW_BLOCK_CPF = 0,  ///< The Gpa hardware block is CPF
    GPA_HW_BLOCK_IA,       ///< The Gpa hardware block is IA
    GPA_HW_BLOCK_VGT,      ///< The Gpa hardware block is VGT
    GPA_HW_BLOCK_PA,       ///< The Gpa hardware block is PA
    GPA_HW_BLOCK_SC,       ///< The Gpa hardware block is SC
    GPA_HW_BLOCK_SPI,      ///< The Gpa hardware block is SPI
    GPA_HW_BLOCK_SQ,       ///< The Gpa hardware block is SQ
    GPA_HW_BLOCK_SX,       ///< The Gpa hardware block is SX
    GPA_HW_BLOCK_TA,       ///< The Gpa hardware block is TA
    GPA_HW_BLOCK_TD,       ///< The Gpa hardware block is TD
    GPA_HW_BLOCK_TCP,      ///< The Gpa hardware block is TCP
    GPA_HW_BLOCK_TCC,      ///< The Gpa hardware block is TCC
    GPA_HW_BLOCK_TCA,      ///< The Gpa hardware block is TCA
    GPA_HW_BLOCK_DB,       ///< The Gpa hardware block is DB
    GPA_HW_BLOCK_CB,       ///< The Gpa hardware block is CB
    GPA_HW_BLOCK_GDS,      ///< The Gpa hardware block is GDS
    GPA_HW_BLOCK_SRBM,     ///< The Gpa hardware block is SRBM
    GPA_HW_BLOCK_GRBM,     ///< The Gpa hardware block is GRBM
    GPA_HW_BLOCK_GRBMSE,   ///< The Gpa hardware block is GRBMSE
    GPA_HW_BLOCK_RLC,      ///< The Gpa hardware block is RLC
    GPA_HW_BLOCK_DMA,      ///< The Gpa hardware block is DMA
    GPA_HW_BLOCK_MC,       ///< The Gpa hardware block is MC
    GPA_HW_BLOCK_CPG,      ///< The Gpa hardware block is CPG
    GPA_HW_BLOCK_CPC,      ///< The Gpa hardware block is CPC
    GPA_HW_BLOCK_WD,       ///< The Gpa hardware block is WD
    GPA_HW_BLOCK_TCS,      ///< The Gpa hardware block is TCS
    GPA_HW_BLOCK_ATC,      ///< The Gpa hardware block is ATC
    GPA_HW_BLOCK_ATCL2,    ///< The Gpa hardware block is ATCL2
    GPA_HW_BLOCK_MCVML2,   ///< The Gpa hardware block is MCVML2
    GPA_HW_BLOCK_EA,       ///< The Gpa hardware block is EA
    GPA_HW_BLOCK_RPB,      ///< The Gpa hardware block is RPB
    GPA_HW_BLOCK_RMI,      ///< The Gpa hardware block is RMI
    GPA_HW_BLOCK_UMCCH,    ///< The Gpa hardware block is UMCCH
    GPA_HW_BLOCK_GE,       ///< The Gpa hardware block is GE
    GPA_HW_BLOCK_GL1A,     ///< The Gpa hardware block is GL1A
    GPA_HW_BLOCK_GL1C,     ///< The Gpa hardware block is GL1C
    GPA_HW_BLOCK_GL1CG,    ///< The Gpa hardware block is GL1CG
    GPA_HW_BLOCK_GL2A,     ///< The Gpa hardware block is GL2A
    GPA_HW_BLOCK_GL2C,     ///< The Gpa hardware block is GL2C
    GPA_HW_BLOCK_CHA,      ///< The Gpa hardware block is CHA
    GPA_HW_BLOCK_CHC,      ///< The Gpa hardware block is CHC
    GPA_HW_BLOCK_CHCG,     ///< The Gpa hardware block is CHCG
    GPA_HW_BLOCK_GUS,      ///< The Gpa hardware block is GUS
    GPA_HW_BLOCK_GCR,      ///< The Gpa hardware block is GCR
    GPA_HW_BLOCK_PH,       ///< The Gpa hardware block is PH
    GPA_HW_BLOCK_UTCL1,    ///< The Gpa hardware block is UTCL1
    GPA_HW_BLOCK_GEDIST,   ///< The Gpa hardware block is GEDIST
    GPA_HW_BLOCK_GESE,     ///< The Gpa hardware block is GESE
    GPA_HW_BLOCK_DFMALL,   ///< The Gpa hardware block is DFMALL
    GPA_HW_BLOCK_COUNT,    ///< Count
} GpaHwBlock;

/// Gpa shader masks
typedef enum
{
    GPA_SHADER_MASK_PS,   ///< The Gpa PS shader mask
    GPA_SHADER_MASK_VS,   ///< The Gpa VS shader mask
    GPA_SHADER_MASK_GS,   ///< The Gpa GS shader mask
    GPA_SHADER_MASK_ES,   ///< The Gpa ES shader mask
    GPA_SHADER_MASK_HS,   ///< The Gpa HS shader mask
    GPA_SHADER_MASK_LS,   ///< The Gpa LS shader mask
    GPA_SHADER_MASK_CS,   ///< The Gpa CS shader mask
    GPA_SHADER_MASK_ALL,  ///< The Gpa all shader mask
} GpaShaderMask;

/// Gpa hardware attribute types
typedef enum
{
    GPA_HARDWARE_ATTRIBUTE_NUM_SHADER_ENGINES,         ///< number of shader engines
    GPA_HARDWARE_ATTRIBUTE_NUM_SHADER_ARRAYS,          ///< number of shader arrays
    GPA_HARDWARE_ATTRIBUTE_NUM_SIMDS,                  ///< number of simds
    GPA_HARDWARE_ATTRIBUTE_NUM_COMPUTE_UNITS,          ///< number of compute units
    GPA_HARDWARE_ATTRIBUTE_NUM_RENDER_BACKENDS,        ///< number of render backends
    GPA_HARDWARE_ATTRIBUTE_CLOCKS_PER_PRIMITIVE,       ///< clocks per primitive
    GPA_HARDWARE_ATTRIBUTE_NUM_PRIMITIVE_PIPES,        ///< number of primitive pipes
    GPA_HARDWARE_ATTRIBUTE_TIMESTAMP_FREQUENCY,        ///< timestamp frequency
    GPA_HARDWARE_ATTRIBUTE_PEAK_VERTICES_PER_CLOCK,    ///< peak vertices per clock
    GPA_HARDWARE_ATTRIBUTE_PEAK_PRIMITIVES_PER_CLOCK,  ///< peak primitives per clock
    GPA_HARDWARE_ATTRIBUTE_PEAK_PIXELS_PER_CLOCK       ///< peak pixels per clocks

} GpaHardwareAttributeType;

/// Gpa Hardware attribute
typedef struct _GpaHardwareAttribute
{
    GpaHardwareAttributeType gpa_hardware_attribute_type;   ///< gpa hardware attribute type
    gpa_uint32               gpa_hardware_attribute_value;  ///< gpa hardware attribute value

} GpaHardwareAttribute;

/// Gpa counter context hardware info
typedef struct _GpaCounterContextHardwareInfo
{
    gpa_uint32 vendor_id;    ///< vendor Id
    gpa_uint32 device_id;    ///< device Id
    gpa_uint32 revision_id;  ///< revision Id

    GpaHardwareAttribute* gpa_hardware_attributes;       ///< pointer to array of hardware attributes
    gpa_uint32            gpa_hardware_attribute_count;  ///< number of hardware attributes

} GpaCounterContextHardwareInfo;

/// Hardware counter info
typedef struct _GpaHwCounter
{
    bool is_timing_block;  ///< flag indicating time based derived counter
    union
    {
        union
        {
            gpa_uint32 gpu_time_bottom_to_bottom_duration;  ///< index of gpu_time_bottom_to_bottom_duration counter
            gpa_uint32 gpu_time_bottom_to_bottom_start;     ///< index of gpu_time_bottom_to_bottom_duration counter
            gpa_uint32 gpu_time_bottom_to_bottom_end;       ///< index of gpu_time_bottom_to_bottom_duration counter
            gpa_uint32 gpu_time_top_to_bottom_duration;     ///< index of gpu_time_top_to_bottom_duration counter
            gpa_uint32 gpu_time_top_to_bottom_start;        ///< index of gpu_time_top_to_bottom_start counter
            gpa_uint32 gpu_time_top_to_bottom_end;          ///< index of gpu_time_top_to_bottom_end counter
        };

        struct
        {
            GpaHwBlock    gpa_hw_block;           ///< Gpa hardware block
            gpa_uint32    gpa_hw_block_instance;  ///< Gpa hardware block 0-based instance index
            gpa_uint32    gpa_hw_block_event_id;  ///< Gpa hardware block 0-based event id
            GpaShaderMask gpa_shader_mask;        ///< Gpa shader mask, only used if SQ block is queried
        };
    };

} GpaHwCounter;

/// Gpa derived counter info
typedef struct _GpaDerivedCounterInfo
{
    GpaHwCounter*  gpa_hw_counters;       ///< hardware counters
    gpa_uint32     gpa_hw_counter_count;  ///< number of hardware counter
    GPA_Usage_Type counter_usage_type;    ///< usage of the derived counter

} GpaDerivedCounterInfo;

/// Gpa counter info -- can be a derived counter or a hardware counter
typedef struct _GpaCounterInfo
{
    bool is_derived_counter;  ///< flag indicating this is a derived counter
    union
    {
        GpaDerivedCounterInfo* gpa_derived_counter;  ///< derived counter
        GpaHwCounter*          gpa_hw_counter;       ///< hardware counter
    };
} GpaCounterInfo;

/// Gpa counter parameter
typedef struct _GpaCounterParam
{
    bool is_derived_counter;  ///< flag indicating derived counter
    union
    {
        const char*  derived_counter_name;  ///< derived counter name
        GpaHwCounter gpa_hw_counter;        ///< hardware counter
    };
} GpaCounterParam;

///  Gpa counters in a pass
typedef struct _GpaPassCounter
{
    gpa_uint32  pass_index;       ///< pass index
    gpa_uint32  counter_count;    ///< number of counters
    gpa_uint32* counter_indices;  ///< indices of the counters
} GpaPassCounter;

/// \brief Gets the Gpa Counter lib version
///
/// \param[out] major_version The value that will hold the major version of GPA upon successful execution.
/// \param[out] minor_version The value that will hold the minor version of GPA upon successful execution.
/// \param[out] build_number The value that will hold the build number of GPA upon successful execution.
/// \param[out] update_version The value that will hold the update version of GPA upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetVersion(gpa_uint32* major_version,
                                                               gpa_uint32* minor_version,
                                                               gpa_uint32* build_number,
                                                               gpa_uint32* update_version);

/// typedef for GpaCounterLib_GetVersion function pointer
typedef GPA_Status (*GpaCounterLib_GetVersionPtrType)(gpa_uint32*, gpa_uint32*, gpa_uint32*, gpa_uint32*);

/// \brief Gets the Gpa counter library function table.
///
/// \param[out] gpa_counter_lib_function_table pointer to the Gpa counter library function table.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetFuncTable(void* gpa_counter_lib_function_table);

/// typedef for GpaCounterLib_GetFuncTable function pointer
typedef GPA_Status (*GpaCounterLib_GetFuncTablePtrType)(void*);

/// \brief Creates a virtual context to interrogate the counter information.
///
/// \param[in] api the api whose available counters are requested.
/// \param[in] gpa_counter_context_hardware_info counter context hardware info.
/// \param[in] context_flags Flags used to initialize the context. Should be a combination of GPA_OpenContext_Bits.
/// \param[in] generate_asic_specific_counters Flag that indicates whether the counters should be ASIC specific, if available.
/// \param[out] gpa_virtual_context Unique identifier of the opened virtual context.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_OpenCounterContext(GPA_API_Type                  api,
                                                                       GpaCounterContextHardwareInfo gpa_counter_context_hardware_info,
                                                                       GPA_OpenContextFlags          context_flags,
                                                                       gpa_uint8                     generate_asic_specific_counters,
                                                                       GPA_CounterContext*           gpa_virtual_context);

/// typedef for GpaCounterLib_OpenCounterContext function pointer
typedef GPA_Status (
    *GpaCounterLib_OpenCounterContextPtrType)(GPA_API_Type, GpaCounterContextHardwareInfo, GPA_OpenContextFlags, gpa_uint8, GPA_CounterContext*);

/// \brief Closes the specified context, which ends access to GPU performance counters.
///
/// Counter functions should not be called again until the counters are reopened with GpaCounterLib_OpenCounterContext.
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_CloseCounterContext(const GPA_CounterContext gpa_virtual_context);

/// typedef for GpaCounterLib_CloseCounterContextPtrType function pointer
typedef GPA_Status (*GpaCounterLib_CloseCounterContextPtrType)(const GPA_CounterContext);

/// \brief Gets the number of counters available.
///
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[out] gpa_counter_count The value which will hold the count upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetNumCounters(const GPA_CounterContext gpa_virtual_context, gpa_uint32* gpa_counter_count);

/// typedef for GpaCounterLib_GetNumCountersPtr function pointer
typedef GPA_Status (*GpaCounterLib_GetNumCountersPtrType)(const GPA_CounterContext, gpa_uint32*);

/// \brief Gets the name of the specified counter.
///
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_counter_index The derived_gpa_counter_index of the counter whose name is needed. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] gpa_counter_name The address which will hold the name upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterName(const GPA_CounterContext gpa_virtual_context,
                                                                   gpa_uint32               gpa_counter_index,
                                                                   const char**             gpa_counter_name);

/// typedef for GpaCounterLib_GetCounterName function pointer
typedef GPA_Status (*GpaCounterLib_GetCounterNamePtrType)(const GPA_CounterContext, gpa_uint32, const char**);

/// \brief Gets index of a counter given its name (case insensitive).
///
/// \param[in] gpa_virtual_context Unique identifier of the session.
/// \param[in] gpa_counter_info The name of the counter whose index is needed.
/// \param[out] gpa_counter_index The address which will hold the index upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterIndex(const GPA_CounterContext gpa_virtual_context,
                                                                    const GpaCounterParam*   gpa_counter_info,
                                                                    gpa_uint32*              gpa_counter_index);

/// typedef for GpaCounterLib_GetCounterIndex function pointer
typedef GPA_Status (*GpaCounterLib_GetCounterIndexPtrType)(const GPA_CounterContext, const GpaCounterParam*, gpa_uint32*);

/// \brief Gets the group of the specified counter.
///
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_counter_index The index of the counter whose group is needed. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] gpa_counter_group The address which will hold the group string upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterGroup(const GPA_CounterContext gpa_virtual_context,
                                                                    gpa_uint32               gpa_counter_index,
                                                                    const char**             gpa_counter_group);

/// typedef for GpaCounterLib_GetCounterGroup function pointer
typedef GPA_Status (*GpaCounterLib_GetCounterGroupPtrType)(const GPA_CounterContext, gpa_uint32, const char**);

/// \brief Gets the description of the specified counter.
///
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_counter_index The index of the counter whose description is needed.. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] gpa_counter_description The address which will hold the description upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterDescription(const GPA_CounterContext gpa_virtual_context,
                                                                          gpa_uint32               gpa_counter_index,
                                                                          const char**             gpa_counter_description);

/// typedef for GpaCounterLib_GetCounterDescription function pointer
typedef GPA_Status (*GpaCounterLib_GetCounterDescriptionPtrType)(const GPA_CounterContext, gpa_uint32, const char**);

/// \brief Gets the data type of the specified counter.
///
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_counter_index The index of the counter whose data type is needed.. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] gpa_counter_data_type The value which will hold the counter data type upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterDataType(const GPA_CounterContext gpa_virtual_context,
                                                                       gpa_uint32               gpa_counter_index,
                                                                       GPA_Data_Type*           gpa_counter_data_type);

/// typedef for GpaCounterLib_GetCounterDataType function pointer
typedef GPA_Status (*GpaCounterLib_GetCounterDataTypePtrType)(const GPA_CounterContext, gpa_uint32, GPA_Data_Type*);

/// \brief Gets the usage type of the specified counter.
///
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_counter_index The index of the counter whose usage type is needed.. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] gpa_counter_usage_type The value which will hold the counter usage type upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterUsageType(const GPA_CounterContext gpa_virtual_context,
                                                                        gpa_uint32               gpa_counter_index,
                                                                        GPA_Usage_Type*          gpa_counter_usage_type);

/// typedef for GpaCounterLib_GetCounterUsageType function pointer
typedef GPA_Status (*GpaCounterLib_GetCounterUsageTypePtrType)(const GPA_CounterContext, gpa_uint32, GPA_Usage_Type*);

/// \brief Gets the UUID of the specified counter.
///
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_counter_index The index of the counter whose UUID is needed. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] gpa_counter_uuid The value which will hold the counter UUID upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterUuid(const GPA_CounterContext gpa_virtual_context,
                                                                   gpa_uint32               gpa_counter_index,
                                                                   GPA_UUID*                gpa_counter_uuid);

/// typedef for GpaCounterLib_GetCounterUuid function pointer
typedef GPA_Status (*GpaCounterLib_GetCounterUuidPtrType)(const GPA_CounterContext, gpa_uint32, GPA_UUID*);

/// \brief Gets the supported sample type of the specified counter.
///
/// Currently, only a single counter type (discrete) is supported
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_counter_index The index of the counter whose sample type is needed.. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] gpa_counter_sample_type The value which will hold the counter's supported sample type upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterSampleType(const GPA_CounterContext gpa_virtual_context,
                                                                         gpa_uint32               gpa_counter_index,
                                                                         GPA_Counter_Sample_Type* gpa_counter_sample_type);

/// typedef for GpaCounterLib_GetCounterSampleType function pointer
typedef GPA_Status (*GpaCounterLib_GetCounterSampleTypePtrType)(const GPA_CounterContext, gpa_uint32, GPA_Counter_Sample_Type*);

/// \brief Get the counter info.
///
/// This can be used only if GPA_OPENCONTEXT_HIDE_PUBLIC_COUNTERS_BIT flag is not used while opening the virtual context.
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_counter_index index of the counter.
/// \param[out] gpa_counter_info counter information.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful. GPA_STATUS_ERROR_FAILED is returned if whitelist/hardware counter index is passed.

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterInfo(const GPA_CounterContext gpa_virtual_context,
                                                                   gpa_uint32               gpa_counter_index,
                                                                   const GpaCounterInfo**   gpa_counter_info);

/// typedef for GpaCounterLib_GetCounterInfo function pointer
typedef GPA_Status (*GpaCounterLib_GetCounterInfoPtrType)(const GPA_CounterContext, gpa_uint32, const GpaCounterInfo**);

/// \brief Computes the derived counter result.
///
/// This can be used only if GPA_OPENCONTEXT_HIDE_PUBLIC_COUNTERS_BIT flag is not used while opening the virtual context.
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_derived_counter_index index of the derived counter.
/// \param[in] gpa_hw_counter_result hardware counter data
/// \param[in] gpa_hw_counter_result_count number of hardware counter data
/// \param[out] gpa_derived_counter_result computed derive counter result.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful. GPA_STATUS_ERROR_FAILED is returned if whitelist/hardware counter index is passed.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_ComputeDerivedCounterResult(const GPA_CounterContext gpa_virtual_context,
                                                                                gpa_uint32               gpa_derived_counter_index,
                                                                                const gpa_uint64*        gpa_hw_counter_result,
                                                                                gpa_uint32               gpa_hw_counter_result_count,
                                                                                gpa_float64*             gpa_derived_counter_result);

/// typedef for GpaCounterLib_ComputeDerivedCounterResult function pointer
typedef GPA_Status (*GpaCounterLib_ComputeDerivedCounterResultPtrType)(const GPA_CounterContext, gpa_uint32, const gpa_uint64*, gpa_uint32, gpa_float64*);

/// \brief Gets the number of passes required for the set of counters.
///
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_counter_indices indices of the counters to be enabled.
/// \param[in] gpa_counter_count number of counters.
/// \param[out] number_of_pass_req The value which will hold the number of required passes upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetPassCount(const GPA_CounterContext gpa_virtual_context,
                                                                 const gpa_uint32*        gpa_counter_indices,
                                                                 gpa_uint32               gpa_counter_count,
                                                                 gpa_uint32*              number_of_pass_req);

/// typedef for GpaCounterLib_GetPassCount function pointer
typedef GPA_Status (*GpaCounterLib_GetPassCountPtrType)(const GPA_CounterContext, const gpa_uint32*, gpa_uint32, gpa_uint32*);

/// \brief For a given set of counters, get information on how the corresponding hardware counters are scheduled into passes
///
/// \param[in] gpa_virtual_context Unique identifier of the opened virtual context.
/// \param[in] gpa_counter_count number of counters.
/// \param[in] gpa_counter_indices indices of the counters to be enabled.
/// \param[in, out] pass_count contains number of passes required for given set of counters if counter_by_pass_list is null, otherwise represents size of the input counter_by_pass_list array.
/// \param[out] counter_by_pass_list list containing number of counters in each pass. Use this to allocate memory for the counter values.
/// \param[out] gpa_pass_counters list containing number of counters in each pass. Use this to allocate memory for the counter values.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCountersByPass(const GPA_CounterContext gpa_virtual_context,
                                                                      gpa_uint32               gpa_counter_count,
                                                                      const gpa_uint32*        gpa_counter_indices,
                                                                      gpa_uint32*              pass_count,
                                                                      gpa_uint32*              counter_by_pass_list,
                                                                      GpaPassCounter*          gpa_pass_counters);

/// typedef for GpaCounterLib_GetPassCount function pointer
typedef GPA_Status (
    *GpaCounterLib_GetCountersByPassPtrType)(const GPA_CounterContext, gpa_uint32, const gpa_uint32*, gpa_uint32*, gpa_uint32*, GpaPassCounter*);

#define GPA_COUNTER_LIB_FUNC(X)                  \
    X(GpaCounterLib_GetVersion)                  \
    X(GpaCounterLib_GetFuncTable)                \
    X(GpaCounterLib_OpenCounterContext)          \
    X(GpaCounterLib_CloseCounterContext)         \
    X(GpaCounterLib_GetNumCounters)              \
    X(GpaCounterLib_GetCounterName)              \
    X(GpaCounterLib_GetCounterIndex)             \
    X(GpaCounterLib_GetCounterGroup)             \
    X(GpaCounterLib_GetCounterDescription)       \
    X(GpaCounterLib_GetCounterDataType)          \
    X(GpaCounterLib_GetCounterUsageType)         \
    X(GpaCounterLib_GetCounterUuid)              \
    X(GpaCounterLib_GetCounterSampleType)        \
    X(GpaCounterLib_GetCounterInfo)              \
    X(GpaCounterLib_ComputeDerivedCounterResult) \
    X(GpaCounterLib_GetPassCount)                \
    X(GpaCounterLib_GetCountersByPass)

/// Gpa counter library function table
typedef struct _GpaCounterLibFuncTable
{
    gpa_uint32 gpa_counter_lib_major_version;
    gpa_uint32 gpa_counter_lib_minor_version;
#define GPA_COUNTER_LIB_DECLARE_FUNC_PTR(func) func##PtrType func;

    GPA_COUNTER_LIB_FUNC(GPA_COUNTER_LIB_DECLARE_FUNC_PTR)

#ifdef __cplusplus
    _GpaCounterLibFuncTable()
    {
        gpa_counter_lib_major_version = GPA_COUNTER_LIB_FUNC_TABLE_MAJOR_VERSION;
        gpa_counter_lib_minor_version = GPA_COUNTER_LIB_FUNC_TABLE_MINOR_VERSION;

#define GPA_COUNTER_LIB_ASSIGN_NULL(func) func = nullptr;
        GPA_COUNTER_LIB_FUNC(GPA_COUNTER_LIB_ASSIGN_NULL)
    }

    bool IsInit() const
    {
        bool is_init = true;

#define GPA_COUNTER_LIB_FUNC_IS_NULL(func) is_init &= nullptr != (func);
        GPA_COUNTER_LIB_FUNC(GPA_COUNTER_LIB_FUNC_IS_NULL)
        return is_init;
    }
#endif

} GpaCounterLibFuncTable;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif  // _GPU_PERF_API_COUNTERS_H_
