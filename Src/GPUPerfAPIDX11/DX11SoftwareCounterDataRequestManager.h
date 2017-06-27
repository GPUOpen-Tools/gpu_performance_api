//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A manager for DX11 Software Counter Data Requests
//==============================================================================

#ifndef _DX11_SOFTWARE_COUNTER_DATA_REQUEST_MANAGER_H_
#define _DX11_SOFTWARE_COUNTER_DATA_REQUEST_MANAGER_H_

#include <unordered_map>

#include <TSingleton.h>
#include <DeviceInfo.h>

#include "GPACounterDataRequestManager.h"

#include "ICounterDataRequest.h"

class GPA_DataRequest; ///< forward declaration

/// Class that will get the correct DX11 Software Counter DataRequest for the given HW generation
class DX11SoftwareCounterDataRequestManager : public TSingleton<DX11SoftwareCounterDataRequestManager>, public GPACounterDataRequestManager<ICounterDataRequest>
{
    friend class TSingleton<DX11SoftwareCounterDataRequestManager>;

protected:
    /// Constructor
    DX11SoftwareCounterDataRequestManager();

    /// overridden base class method
    /// \return nullptr
    virtual ICounterDataRequest* GetDefaultDataRequest();
};

#endif // _DX11_SOFTWARE_COUNTER_DATA_REQUEST_MANAGER_H_
