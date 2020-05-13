//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A class for handling custom hw validation
//==============================================================================

#include "gpa_custom_hw_validation_manager.h"

void GPACustomHwValidationManager::RegisterCustomHardwareValidator(CustomHWValidationFuncPtr hwValidationFunc, void* pUserData)
{
    if (nullptr != hwValidationFunc)
    {
        CustomValidationFuncPair validationPair(hwValidationFunc, pUserData);
        m_validationFunctionList.push_back(validationPair);
    }
}

GPA_Status GPACustomHwValidationManager::ValidateHW(void* pContext, GPA_HWInfo* pHwInfo)
{
    GPA_Status retVal = GPA_STATUS_OK;

    for (auto it = m_validationFunctionList.begin(); it != m_validationFunctionList.end() && GPA_STATUS_OK == retVal; ++it)
    {
        retVal = (it->first)(pContext, pHwInfo, it->second);
    }

    return retVal;
}
