//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A class for handling custom hw validation
//==============================================================================

#ifndef _GPA_CUSTOM_HW_VALIDATOR_H_
#define _GPA_CUSTOM_HW_VALIDATOR_H_

#include <TSingleton.h>

#include "GPAHWInfo.h"

/// Class to manage custom hw validation
class GPACustomHwValidationManager : public TSingleton<GPACustomHwValidationManager>
{
public:
    /// Typedef for the function pointer type used to validate hardware
    typedef GPA_Status (*CustomHWValidationFuncPtr)(void*, GPA_HWInfo*, void*);

    /// Registers a function that is used to validate hardware
    /// \param hwValidationFunc the function to call to validate hardware
    /// \param pUserData the user data to pass to the validation function
    void RegisterCustomHardwareValidator(CustomHWValidationFuncPtr hwValidationFunc, void* pUserData);

    /// Validates the specified hardware by calling all validators
    /// \param pContext the GPA Context
    /// \param pHwInfo the hardware info to validate
    /// \return GPA_STATUS_OK if all validators validate this hardware
    GPA_Status ValidateHW(void* pContext, GPA_HWInfo* pHwInfo);

private:
    typedef std::pair<CustomHWValidationFuncPtr, void*> CustomValidationFuncPair;  ///< typedef used to store validator/userdata pair
    std::vector<CustomValidationFuncPair>               m_validationFunctionList;  ///< list of validation functions
};

#endif  // _GPA_CUSTOM_HW_VALIDATOR_H_
