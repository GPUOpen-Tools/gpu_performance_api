//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL GPA Pass Object Header
//==============================================================================

#ifndef _GL_GPA_PASS_H_
#define _GL_GPA_PASS_H_

// GPA Common
#include "gpa_pass.h"
#include "gpa_command_list_interface.h"
#include "gl_entry_points.h"

using GLPerfMonitorId = GLuint;  ///< type alias for GL perf monitor id

/// GLCounter Struct
/// structure used to store data that is needed to retrieve and store the
/// results for a counter.
struct GLCounter
{
    /// Initializes a new instance of the GLCounter class
    GLCounter()
    {
        m_counterID            = 0;
        m_counterType          = 0;
        m_counterGroup         = 0;
        m_counterIndex         = 0;
        m_isCounterResultReady = false;
    }

    GLuint m_counterID;             ///< ID that is calculated in the CounterDefinition files
    GLenum m_counterType;           ///< data type that GL specifies the result will be
    GLuint m_counterGroup;          ///< group that this counter is in
    GLuint m_counterIndex;          ///< index to this counter within its group
    bool   m_isCounterResultReady;  ///< indicates whether the result has been stored in the pCounterResult buffer
};

/// Class for OpenGL gpa pass
class GLGPAPass : public GPAPass
{
public:
    /// Constructor
    /// \param[in] pGpaSession GPA session object pointer
    /// \param[in] passIndex pass index
    /// \param[in] counterSource counter source
    /// \param[in] pPassCounters counter list for the pass
    GLGPAPass(IGPASession* pGpaSession, PassIndex passIndex, GPACounterSource counterSource, CounterList* pPassCounters);

    /// Destructor
    ~GLGPAPass();

    /// \copydoc GPAPass::CreateAPISpecificSample
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList, GpaSampleType sampleType, ClientSampleId sampleId) override final;

    /// \copydoc GPAPass::ContinueSample
    bool ContinueSample(ClientSampleId srcSampleId, IGPACommandList* pPrimaryGpaCmdList) override final;

    /// \copydoc GPAPass::CreateAPISpecificCommandList
    IGPACommandList* CreateAPISpecificCommandList(void* pCmd, CommandListId commandListId, GPA_Command_List_Type cmdType) override final;

    /// \copydoc GPAPass::EndSample
    bool EndSample(IGPACommandList* pCmdList) override final;

    /// Returns the GL performance monitor, it may return if cached monitor is available otherwise returns by creating one.
    /// \param[out] glPerfMonitorId cached/new performance moniotr Id
    /// \return true upon successful operation otherwise false
    bool GetPerfMonitor(GLPerfMonitorId& glPerfMonitorId);

    /// Marks the data for the passed performance moniotr to be collected and it can be used as for cache
    /// \param[in] glPerfMonitorId performance monitor Id
    void MarkDataCollected(const GLPerfMonitorId glPerfMonitorId);

    /// Returns the GL counter in the pass
    /// \param[in] counterGroup group of the counter
    /// \param[in] counterIndex index of the counter
    /// \param[out] indexOfCounterWithinPass index of the counter within pass
    /// \return pointer to the GL counter if found otherwise nullptr
    const GLCounter* GetGLCounter(const GLuint& counterGroup, const GLuint& counterIndex, unsigned int& indexOfCounterWithinPass) const;

private:
    /// Intializes the counter info for the passed performance Id
    /// \param[in] glPerfMonitorId performance monitor Id
    /// \return true upon successful operation otherwise false
    bool InitializeCounters(const GLPerfMonitorId& glPerfMonitorId);

    /// Class for handling perf monitor
    class GLPerfMonitor
    {
    public:
        /// Constructor
        GLPerfMonitor();

        /// Initializes the perf monitor id
        /// \return true upon successful operation otherwise false
        bool Initialize();

        /// Returns the perf monitor Id
        /// \return GL perf monitor Id
        GLPerfMonitorId GetPerfMonitorId() const;

        /// Checks whether or not the data has been collected from the monitor
        /// \return true upon successful operation otherwise false
        bool IsDataCollected() const;

        /// Adds/increments the reference of the monitor
        /// \return value of the monitor reference after adding
        unsigned int AddRef();

        /// Release/decrements the reference of the monitor
        /// \return value of the reference after releasing
        unsigned int Release();

        /// Deletes the performance monitor in the driver if it's not being used
        /// \param[in] forceClear flag indicating whether the monitor needs to be deleted even if it's data is not populated
        /// \return true upon successful operation otherwise false
        bool Clear(bool forceClear = false);

        /// Destructor
        ~GLPerfMonitor() = default;

    private:
        GLPerfMonitorId m_glPerfMonitorId;  ///< Perf Monitor Id
        unsigned int    m_refCount;         ///< reference count
    };

    std::map<GLPerfMonitorId, GLPerfMonitor> m_glPerfMonitorInfoList;  ///< Map of perf monitor Id and GLPerfMonitor
    mutable std::vector<GLCounter>           m_glCounterList;          ///< List of counters in the pass
};

#endif  // _GL_GPA_PASS_H_
