//==============================================================================
// Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA API Helper class
//==============================================================================

#ifndef _GPA_HELPER_H_
#define _GPA_HELPER_H_

#include "GPAInterfaceLoader.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

/// Class that demonstrates one approach to loading GPA into an application.
/// It can query the addresses of all GPA entry points, and has utility functions to demonstrate
/// how to access information about the available counters, as well as how to query the profile
/// result for a given sample Id.
class GPAHelper
{
public:
    /// Constructor
    GPAHelper();

    /// Destructor
    ~GPAHelper();

    /// Indicates whether or not the GPA library is loaded.
    bool IsLoaded() const;

    /// Loads the necessary GPA library.
    /// \return True if the library loaded successfully; false otherwise.
    bool Load();

    /// Unloads the GPA library.
    void Unload();

    /// Print the available counters from the specified context.
    /// \param contextId A valid GPA Context ID.
    void PrintGPACounterInfo(GPA_ContextId contextId) const;

    /// Gets the path of the running executable
    /// \return the path of the running executable
    static std::string GetExecutablePath();

    /// Gets the name of the CSV file in which to output profile results.
    /// \return the name of the CSV file in which to output profile results.
    std::string GetCSVFileName() const;

    /// Gets the name of the GPA log file.
    /// \return the name of the GPA log file
    static std::string GetGPALogFileName();

    /// Opens the CSV file to output profile results.
    /// \return True if the csv file was successfully opened; false otherwise.
    bool OpenCSVFile();

    /// Closes the CSV File so that it gets saved to disk.
    void CloseCSVFile();

    /// Callback function for any error messages that GPA produces.
    /// \param type The type of logging message.
    /// \param msg The message.
    static void gpaLoggingCallback(GPA_Logging_Type type, const char* msg);

    /// Enum to define type of counter validation to perform
    typedef enum
    {
        COMPARE_TYPE_EQUAL,                     ///< Counter value must be equal to a specified value
        COMPARE_TYPE_GREATER_THAN,              ///< Counter value must be greater than a specified value
        COMPARE_TYPE_GREATER_THAN_OR_EQUAL_TO,  ///< Counter value must be greater than or equal to a specified value
        COMPARE_TYPE_LESS_THAN,                 ///< Counter value must be less than a specified value
        COMPARE_TYPE_LESS_THAN_OR_EQUAL_TO,     ///< Counter value must be less than or equal to a specified value
    } CompareType;

    /// Compare retrieved counter value to an expected value
    /// \param sampleIndex the sample index of the counter being compared
    /// \param pCounterName the name of the counter being compared
    /// \param counterValue the retrieved counter value
    /// \param compareType the type of compare to perform
    /// \param compareVal the expected counter value (subject to the compare type)
    /// \return true if the counter value compares successfully, false otherwise
    bool CounterValueCompare(unsigned int sampleIndex, const char* pCounterName, gpa_float64 counterValue, CompareType compareType, gpa_float64 compareVal);

    /// Validate a specified counter in a specified sample
    /// \param sampleIndex the index of the sample containing the counter
    /// \param pCounterName the name of the counter to validate
    /// \param counterValue the value of the counter to validate
    /// \param counterUsageType the usage type of the counter being compared
    /// \return true if the counter value validates successfully, false otherwise
    bool ValidateData(unsigned int sampleIndex, const char* pCounterName, gpa_float64 counterValue, GPA_Usage_Type counterUsageType);

    /// Print counter results from a specific sample.
    /// If the CSV file is open, then the results will be written the CSV file too.
    /// \param contextId A valid Context ID.
    /// \param sessionId A valid Session ID.
    /// \param sampleId A valid Sample ID.
    /// \param outputToConsole flag indicating to show on console or not
    /// \param verifyCounters flag indicating to verify the counters or not
    void PrintGPASampleResults(GPA_ContextId contextId, GPA_SessionId sessionId, gpa_uint32 sampleId, bool outputToConsole, bool verifyCounters);

    /// GPA function table pointer
    GPAFunctionTable* m_pGpaFuncTable;

    /// The name of the csv file that will be written.
    std::string m_csvFileName = "VkColorCube_counterData.csv";

    /// The name of the GPA Log file that will be written.
    static std::string ms_gpaLogFileName;

    /// GPA log file stream
    static std::fstream ms_gpaLogFileStream;

    // Flag indicating if any errors were output via GPA's logging mechanism
    static bool ms_anyGPAErrorsLogged;

private:
    /// The file stream for writing the csv file.
    std::fstream m_csvFile;

    /// Flag to indicate if the header has been written in the csv file.
    bool m_bHeaderWritten;
};

#endif  // _GPUPERFAPI_HELPER_H_
