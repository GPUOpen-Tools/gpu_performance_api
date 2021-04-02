//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  A class for handling custom hw validation.
//==============================================================================

#include "gpu_perf_api_common/gpa_custom_hw_validation_manager.h"

void GpaCustomHwValidationManager::RegisterCustomHardwareValidator(CustomHWValidationFuncPtr hw_validation_func, void* user_data)
{
    if (nullptr != hw_validation_func)
    {
        CustomValidationFuncPair validation_pair(hw_validation_func, user_data);
        validation_function_list_.push_back(validation_pair);
    }
}

GpaStatus GpaCustomHwValidationManager::ValidateHW(void* context, GpaHwInfo* hw_info)
{
    GpaStatus ret_val = kGpaStatusOk;

    for (auto it = validation_function_list_.begin(); it != validation_function_list_.end() && kGpaStatusOk == ret_val; ++it)
    {
        ret_val = (it->first)(context, hw_info, it->second);
    }

    return ret_val;
}
