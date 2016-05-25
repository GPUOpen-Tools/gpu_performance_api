//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage the D3D11 Query-based software counters
//==============================================================================

#ifndef _GPA_SW_COUNTER_MANAGER_H_
#define _GPA_SW_COUNTER_MANAGER_H_

#include "TSingleton.h"
#include "GPAInternalCounter.h"
#include <vector>
#include <set>
#include <unordered_map>

/// Enum for the D3D11 query counters
enum class D3DCOUNTERS : gpa_uint32
{
    GPUTIME,
    OCCLUSION,
    IAVERTICES,
    IAPRIMITIVES,
    VSINVOCATIONS,
    GSINVOCATIONS,
    GSPRIMITIVES,
    CINVOCATIONS,
    CPRIMITIVES,
    PSINVOCATIONS,
    HSINVOCATIONS,
    DSINVOCATIONS,
    CSINVOCATIONS,
    OCCLUSIONPREDICATE,
    SOPRIMSWRITTEN,
    SOPRIMSSTORAGENEED,
    SOOVERFLOWPRED,
    PRIMSWRITTEN_S0,
    PRIMSSTORAGENEED_S0,
    OVERFLOWPRED_S0,
    PRIMSWRITTEN_S1,
    PRIMSSTORAGENEED_S1,
    OVERFLOWPRED_S1,
    PRIMSWRITTEN_S2,
    PRIMSSTORAGENEED_S2,
    OVERFLOWPRED_S2,
    PRIMSWRITTEN_S3,
    PRIMSSTORAGENEED_S3,
    OVERFLOWPRED_S3
};

typedef std::vector<GPA_SoftwareCounterDesc>        SwCounterDescVec;    ///< Typedef for a list of software counters
typedef std::set<gpa_uint32>                        EnabledSwCounterSet; ///< Typedef for a set of enabled counters
typedef std::unordered_map<gpa_uint32, gpa_uint32>  CounterIndexMap;     ///< Typedef for a map of counter indices

/// singleton wrapper class for DX11 SW counters.
class SwCounterManager : public TSingleton<SwCounterManager>
{
public :
    /// default constructor
    SwCounterManager();

    /// destructor
    virtual ~SwCounterManager();

    /// generate a SW counter
    /// \param counterDesc reference to the GPA_SoftwareCounterDesc to generate
    void GenerateSwCounter(const GPA_SoftwareCounterDesc& counterDesc);

    /// check if DX11 SW counters have been generated
    /// \return true if  DX11 SW counters generated.
    bool SwCountersGenerated() const;

    /// set SW counters generating status
    /// \param set the status of SW counter generation to be set
    void SetSwCountersGenerated(const bool set);

    /// check if any SW counter is enabled
    /// \return true if SW counters enabled.
    bool SwCounterEnabled() const;

    /// clear enabled SW counters
    void ClearEnabledSwCounters();

    /// get SW counter list
    /// \return a pointer to swCounterDescVec
    const SwCounterDescVec* GetSwCounters();

    /// get the number of SW counters
    /// \return number of SW counters
    const gpa_uint32 GetNumSwCounters();

    /// enable SW counter
    /// \param index the public index of the SW counter to be enabled
    void EnableSwCounter(const gpa_uint32 index);

    /// Disable SW counter
    /// \param index the public index of the SW counter to be disabled
    void DisableSwCounter(gpa_uint32 index);

    /// map public counter index and SW counter index
    /// \param pubIndex the public index of the SW counter
    /// \param swIndex the SW index of the SW counter
    void AddSwCounterMap(const gpa_uint32 pubIndex, const gpa_uint32 swIndex);

    /// set SW GPUTime counter public index
    /// \param pubIndex the public index to set
    void SetSwGPUTimeCounterIndex(const gpa_uint32 pubIndex);

    /// get SW GPUTime counter public index
    /// \return SW GPUTime counter public index
    const gpa_uint32 GetSwGPUTimeCounterIndex() const;

    /// set SW GPUTime counter enabled status
    /// \param enabled the status to set
    void SetSwGPUTimeCounterEnabled(const bool enabled);

    /// get SW GPUTime counter enabled status
    /// \return m_swGPUTimeEnabled
    bool SwGPUTimeCounterEnabled() const;

    /// get public counter index of SW counter from SW counter map
    /// \param swIndex the SW index of the SW counter
    /// \return public counter index
    gpa_uint32  GetSwCounterPubIndex(const gpa_uint32 swIndex) const;

    /// clear m_swCounterIndexMap
    void ClearSwCounterMap();

    /// set number of AMD counters
    /// \param counters number of total AMD counters
    void SetNumAmdCounters(const gpa_uint32 counters);

    /// get the number of AMD counters
    /// \return number of AMD counters
    const gpa_uint32 GetNumAmdCounters() const;

    /// get enabled SW counter list
    /// \return a pointer to  enabledSwCounterSet
    const EnabledSwCounterSet* GetEnabledSwCounters();

private:
    /// disable copy constructor
    SwCounterManager(const SwCounterManager& copy);

    /// disable copy assignment operator
    SwCounterManager& operator=(SwCounterManager& rhs);

    SwCounterDescVec          m_swCounters;             ///<vector containing SW D3D11 counters
    EnabledSwCounterSet       m_enabledSwCounters;      ///< set of currently enabled SW D3D11 counters(ids)
    gpa_uint32                m_amdCounters;            ///< number of AMD counters
    CounterIndexMap           m_swCounterIndexMap;      ///< SW counter public index, SW index map
    gpa_uint32                m_swGPUTimeCounter;       ///< SW GPUTime counter public index
    bool                      m_swGPUTimeEnabled;       ///< Indicates if SW GPUTime counter is enabled
    bool                      m_swCountersGenerated;    ///< Indicates if SW counters have been generated

};  // end of class SwCounterManager

/// declare singleton SwCounterManager object as extern
extern SwCounterManager* s_pSwCounterManager;

#endif // _GPA_SW_COUNTER_MANAGER_H_

