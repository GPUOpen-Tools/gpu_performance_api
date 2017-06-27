//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A manager for GL Data Requests
//==============================================================================

#ifndef _GL_COUNTER_DATA_REQUEST_MANAGER_H_
#define _GL_COUNTER_DATA_REQUEST_MANAGER_H_

#include <unordered_map>

#include <TSingleton.h>
#include <DeviceInfo.h>

#include "GPACounterDataRequestManager.h"

class GPA_DataRequest; ///< forward decalration

/// Class that will get the correct GL Counter DataRequest for the given HW generation
class GLCounterDataRequestManager : public TSingleton<GLCounterDataRequestManager>, public GPACounterDataRequestManager<GPA_DataRequest>
{
    friend class TSingleton<GLCounterDataRequestManager>;

protected:
    /// Constructor
    GLCounterDataRequestManager();

    /// overridden base class method to get default data request
    /// \return the default data request
    virtual GPA_DataRequest* GetDefaultDataRequest();
};

#endif // _GL_COUNTER_DATA_REQUEST_MANAGER_H_
