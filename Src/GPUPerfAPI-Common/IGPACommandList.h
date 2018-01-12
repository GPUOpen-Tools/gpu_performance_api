//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Interface for GPA Command List Object
//==============================================================================

#ifndef _I_GPA_COMMAND_LIST_H_
#define _I_GPA_COMMAND_LIST_H_

#include "GPUPerfAPITypes.h"
#include "IGPAInterfaceTrait.h"
#include "GPAPass.h"
#include <list>

class IGPASession;      // forward declaration

/// Interface for GPA Command List
class IGPACommandList : public IGPAInterfaceTrait
{
public:

    /// Virtual Destructor
    virtual ~IGPACommandList() = default;

    /// Gets the session object on which this CommandList was started.
    /// \return The session object on which this CommandList was started.
    virtual IGPASession* GetParentSession() const = 0;

    /// Changes the state of command list to sample recording state
    /// \return true if successful otherwise false
    virtual bool Begin() = 0;

    /// Changes the state of command list from sample recording state to closed state
    /// \return true if successful otherwise false
    virtual bool End() = 0;

    /// Checks whether the command list is running or not
    /// \return true if command list is started but not yet ended otherwise false
    virtual bool IsCommandListRunning() const = 0;

    /// Returns the associated index of the pass
    /// \return index of the pass
    virtual GPAPass* GetPass() const = 0;

    /// Returns the number of samples created on the command list
    /// \return number of samples
    virtual gpa_uint32 GetSampleCount() const = 0;

    /// Begins the sample on the command list
    /// \param[in] clientSampleIndex index of the sample
    /// \param[in] pSample The sample to start
    /// \param[in] pCounterList The set of counters to start on the sample
    /// \return true if sample was successfully begun, false otherwise
    virtual bool BeginSample(ClientSampleId clientSampleIndex, GPASample* pSample, const std::vector<CounterIndex>* pCounterList) = 0;

    /// Gets the current open sample
    /// \return the current open sample or nullptr if no sample is open
    virtual GPASample* GetLastSample() const = 0;

    /// Closes the most recent sample
    /// \param closingByClient flag indicating if the sample is being closed by the client rather than by GPA itself. Default is true.
    /// \return true if most recent sample was closed, false otherwise
    virtual bool CloseLastSample(bool closingByClient = true) = 0;

    /// Checks whether the last sample has been closed or not
    /// \return true if last sample has been closed otherwise false
    virtual bool IsLastSampleClosed() const = 0;

    /// Checks whether the command list has finished executing and ready for returning the data
    /// \return true if command list is finished executing otherwise false
    virtual bool IsComplete() const = 0;

    /// Returns the cmd type of the command list
    /// \return cmd type of the command list
    virtual GPA_Command_List_Type GetCmdType() const = 0;
};

#endif // _I_GPA_COMMAND_LIST_H_
