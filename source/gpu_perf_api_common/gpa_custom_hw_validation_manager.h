//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  A class for handling custom hw validation.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_CUSTOM_HW_VALIDATION_MANAGER_H_
#define GPU_PERF_API_COMMON_GPA_CUSTOM_HW_VALIDATION_MANAGER_H_

#include <TSingleton.h>

#include "gpu_perf_api_common/gpa_hw_info.h"

/// @brief Class to manage custom hw validation.
class GpaCustomHwValidationManager : public TSingleton<GpaCustomHwValidationManager>
{
public:
    /// @brief Typedef for the function pointer type used to validate hardware.
    typedef GpaStatus (*CustomHWValidationFuncPtr)(void*, GpaHwInfo*, void*);

    /// @brief Registers a function that is used to validate hardware.
    ///
    /// @param [in] hw_validation_func The function to call to validate hardware.
    /// @param [in] user_data The user data to pass to the validation function.
    void RegisterCustomHardwareValidator(CustomHWValidationFuncPtr hw_validation_func, void* user_data);

    /// @brief Validates the specified hardware by calling all validators.
    ///
    /// @param [in] context The GPA Context.
    /// @param [in] hw_info The hardware info to validate.
    ///
    /// @return kGpaStatusOk if all validators validate this hardware.
    GpaStatus ValidateHW(void* context, GpaHwInfo* hw_info);

private:
    typedef std::pair<CustomHWValidationFuncPtr, void*> CustomValidationFuncPair;   ///< Typedef used to store validator/user data pair.
    std::vector<CustomValidationFuncPair>               validation_function_list_;  ///< List of validation functions.
};

#endif  // GPU_PERF_API_COMMON_GPA_CUSTOM_HW_VALIDATION_MANAGER_H_
