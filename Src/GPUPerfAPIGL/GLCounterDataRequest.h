//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL Counter Data Request
//==============================================================================

#ifndef _GL_COUNTER_DATA_REQUEST_H_
#define _GL_COUNTER_DATA_REQUEST_H_

#include "GPUPerfAPIImp.h"
#include "GPUPerfAPIGL.h"

//-----------------------------------------------------------------------------
/// GLCounter Struct
/// structure used to store data that is needed to retrieve and store the
/// results for a counter.
//-----------------------------------------------------------------------------
struct GLCounter
{
    /// Initializes a new instance of the GLCounter class
    GLCounter()
    {
        m_counterID = 0;
        m_counterType = 0;
        m_counterGroup = 0;
        m_counterIndex = 0;
        m_isCounterResultReady = false;
    }

    GLuint m_counterID;           ///< ID that is calculated in the CounterDefinition files
    GLenum m_counterType;         ///< data type that GL specifies the result will be
    GLuint m_counterGroup;        ///< group that this counter is in
    GLuint m_counterIndex;        ///< index to this counter within its group
    bool   m_isCounterResultReady;///< indicates whether the result has been stored in the pCounterResult buffer
};

//-----------------------------------------------------------------------------
/// GLCounterDataRequest class
/// this class is responsible for enabling, disabling, and gathering all the
/// counter results for a single request.
//-----------------------------------------------------------------------------
class GLCounterDataRequest : public GPA_DataRequest
{
public:

    /// Initializes a new GLCounterDataRequest object
    GLCounterDataRequest();

    /// Destructor
    ~GLCounterDataRequest();

    /// mechanism to permit reuse of resources
    /// selected counters may not have changed, so can just use query resources again
    /// \param selectionID index of the counter selection to reset
    /// \param pCounters The set of counters to enable in place of the existing ones
    virtual void Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);

protected:

    virtual bool BeginRequest(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);
    virtual bool EndRequest();
    virtual bool CollectResults(GPA_CounterResults& resultStorage);
    virtual void ReleaseCounters();

    /// Create the GPUTime Query object
    void CreateGPUTimeQuery();

    /// static method to get the results from the specified data request
    /// \param pRequest the data request instance in which to store the results
    /// \return indicates whether or not the results were collected for the specified request
    static bool GetResults(GLCounterDataRequest* pRequest);

    GLuint m_monitor;             ///< The GL Monitor that is assigned to this request
    GLuint m_gpuTimeQuery[2];     ///< The Query used to get GPUTime results
    GLCounter* m_counters;        ///< Array of active counters

    GLint m_appsCurrentTimerQuery;               ///< the TimerQuery object being used by the application.
    GLint m_appsCurrentOcclusionQuery;           ///< the occlusion query (SAMPLES_PASSED) object being used by the application.
    GLint m_appsCurrentOcclusionQuery2;          ///< the occlusion query2 (ANY_SAMPLES_PASSED) object being used by the application.
    GLint m_appsCurrentTransformFeedbackQuery;   ///< the transform feedback query being used by the application.

    bool m_haveAlreadyBegunGPUTimeQuery;         ///< indicates whether or not the GPUTime Query was begun

    gpa_uint32 m_dataReadyCount;                 ///< number of counters with data ready

    GPA_CounterResults m_counterResults;         ///< saved counter results for this data request
    bool               m_areAllResultsSaved;     ///< indicates whether or not all of the results have been saved in m_counterResults
    bool               m_isAMD;                  ///< indicates whether or not an AMD GPU is in use
};

#endif // _GL_COUNTER_DATA_REQUEST_H_
