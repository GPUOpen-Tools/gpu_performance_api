//==============================================================================
// Copyright (c) 2019-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA Helper class
//==============================================================================

#ifndef _GPA_HELPER_H_
#define _GPA_HELPER_H_

#define DISABLE_GPA 0

#include <vector>
#include <fstream>
#include <sstream>
#include <map>

#include "gpu_perf_api_interface_loader.h"

/// Enums for the Application error
enum APP_ERRORS
{
    GL_ERROR       = GPA_LOGGING_DEBUG_ALL + 1,     ///< GL errors
    WIN_ERROR,                                      ///< Windows error
    X_SERVER_ERROR,                                 ///< X server error on Linux
    GENERAL_ERROR                                   ///< any app error unrelated to GPA and platform
};

extern void GPALogger(GPA_Logging_Type logType, const char* logMsg);

#ifdef _WIN32
typedef HGLRC GLContext;  ///< typedef for Windows GL context
#else
#include <GL/glx.h>
typedef GLXContext GLContext;  ///< typedef for Linux GL context
#endif

/// GPA  Helper class
class GPAHelper
{
public:
    /// Returns the static instance of the GPA Helper
    /// \return static instance of the GPA Helper
    static GPAHelper* Instance();

    /// Setups the GPA
    /// \return true upon successful operation otherwise false
    bool SetUpGPA();

    /// Opens the GPA context
    /// \param[in] glContext GL context
    /// \param[in] includeHwCounters flag indicating whether or not to include hardware counters in the non-internal build
    /// \return true upon successful operation otherwise false
    bool OpenContext(GLContext glContext, bool includeHwCounters);

    /// Closes the context
    /// \return true upon successful operation otherwise false
    bool CloseContext();

    /// Create the GPA session
    /// \return true upon successful operation otherwise false
    bool CreateGpaSession();

    /// Destroys the GPA session
    /// \return true upon successful operation otherwise false
    bool DestroyGpaSession();

    ///  Enables all the counters
    /// \return true upon successful operation otherwise false
    bool EnableAllCounters();

    ///  Enables counter by name
	/// \param pName the name of the counter to enable
    /// \return true upon successful operation otherwise false
    bool EnableCounterByName(const char* pName);

    /// Begins the GPA session
    /// \return true upon successful operation otherwise false
    bool OnGpaSessionStart();

    ///  Ends the GPA session
    /// \return true upon successful operation otherwise false
    bool OnGpaSessionEnd();

    /// Starts the GPA pass
    /// \return true upon successful operation otherwise false
    bool OnPassStart();

    /// Ends the GPA pass
    /// \return true upon successful operation otherwise false
    bool OnPassEnd();

    /// Begins the sample
    /// \return true upon successful operation otherwise false
    bool BeginSample();

    ///  Ends the sample
    /// \return true upon successful operation otherwise false
    bool EndSample();

    ///  Populate the sample result
    /// \return true upon successful operation otherwise false
    bool PrintGPASampleResults(bool verify = false);

    ///  Returns the number of passes required
    /// \return number of passes required
    unsigned int GetPassRequired() const;

    /// Increments the frame counter
    void IncrementFrameCounter();

    /// Returns the current frame index
    /// \return current frame index
    unsigned int GetCurrentFrameCount() const;

    /// Destructor
    ~GPAHelper();

    std::fstream m_gpaLogFileStream;                         ///< log file stream
    std::string  m_gpaLogFileName = "GLTriangleGpaLog.txt";  ///< log file name
    bool         m_anyGpaError;                              ///< flag indicating if any GPA error occurred

private:
    /// struct for GPA counter
    struct GPACounter
    {
        const char*    m_counterName;         ///< Counter name
        gpa_uint32     m_counterIndex;        ///< Counter index
        const char*    m_counterGroup;        ///< Counter group
        const char*    m_counterDescription;  ///< counter description
        GPA_Data_Type  m_counterDataType;     ///< Counter data type
        GPA_Usage_Type m_counterUsageType;    ///< Counter usage
        gpa_float64    m_counterValue;        ///< Counter Value

        /// Constructor
        GPACounter()
            : m_counterName(nullptr)
            , m_counterIndex(0u)
            , m_counterGroup(nullptr)
            , m_counterDescription(nullptr)
            , m_counterDataType()
            , m_counterUsageType()
            , m_counterValue()
        {
        }

        /// < than operator overloading
        /// \param[in] comparer comparing value
        /// \return true if counter value is < comparer
        bool operator<(const float& comparer) const
        {
            return m_counterValue < comparer;
        }

        /// <= than operator overloading
        /// \param[in] comparer comparing value
        /// \return true if counter value is <= comparer
        bool operator<=(const float& comparer) const
        {
            return m_counterValue <= comparer;
        }

        /// < than operator overloading
        /// \param[in] comparer comparing value
        /// \return true if counter value is < comparer
        bool operator==(const float& comparer) const
        {
            return m_counterValue == comparer;
        }

        /// > than operator overloading
        /// \param[in] comparer comparing value
        /// \return true if counter value is > comparer
        bool operator>(const float& comparer) const
        {
            return m_counterValue > comparer;
        }

        /// >= than operator overloading
        /// \param[in] comparer comparing value
        /// \return true if counter value is >= comparer
        bool operator>=(const float& comparer) const
        {
            return m_counterValue >= comparer;
        }
    };

    /// Constructor
    GPAHelper();

    static GPAHelper*         m_pGpaHelper;                                 ///< GPA Helper instance
    GPAFunctionTable*         m_pGpaFuncTable;                              ///< GPA function table
    std::vector<unsigned int> m_samples;                                    ///< sample list
    GPA_ContextId             m_gpaContextId;                               ///< GPA context id
    GPA_SessionId             m_gpaSessionId;                               ///< GPA session id
    GPA_CommandListId         m_gpaCommandListId;                           ///< GPA command list id
    unsigned int              m_numOfPassReq;                               ///< required pass count
    int                       m_currentPassIndex;                           ///< current pass
    int                       m_sampleCounter = -1;                         ///< sample counter
    std::fstream              m_counterDataFileStream;                      ///< counter data file stream
    std::string               m_counterFileName = "GLTriangleCounter.csv";  ///< counter file name
    bool                      m_isHeaderWritten = false;                    ///< flag indicating status of header
    std::stringstream         m_header;                                     ///< header stream
    std::stringstream         m_content;                                    ///< counter data stream
    unsigned int              m_frameCounter = 0;                           ///< frame counter
};

#endif  // _GPA_HELPER_H_