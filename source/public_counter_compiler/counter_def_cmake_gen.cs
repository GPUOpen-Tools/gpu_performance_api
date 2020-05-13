// =====================================================================
// <copyright file="CounterDefCMakeGen.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//      CMake File generator for counter definitions
// </summary>
// =====================================================================

using System;
using System.Collections.Generic;
using System.IO;
using ApiDictionary = System.Collections.Generic.Dictionary<string, System.Collections.Generic.List<string>>;
using FileList = System.Collections.Generic.List<string>;

namespace GPATools
{
    class CounterDefCMakeGenerator
    {
        /// <summary>
        /// Derived counter names dictionary
        /// </summary>
        public static ApiDictionary DerivedCounters = new ApiDictionary();

        /// <summary>
        /// counter definitions dictionary
        /// </summary>
        public static ApiDictionary CounterDefs = new ApiDictionary();

        /// <summary>
        /// Flag indicating the internal counter compiler or not
        /// </summary>
        public static bool IsInternal = false;

        /// <summary>
        /// Initializes the memory for the file lists
        /// </summary>
        public static void Init()
        {
            // PublicCounterDefs - GPA
            CounterDefs.Add(Gpa.DX12, new FileList());
            CounterDefs.Add(Gpa.DX11, new FileList());
            CounterDefs.Add(Gpa.VK, new FileList());
            CounterDefs.Add(Gpa.GL, new FileList());
            CounterDefs.Add(Gpa.CL, new FileList());

            // PublicDerivedCounters - GPA
            DerivedCounters.Add(Gpa.DX12, new FileList());
            DerivedCounters.Add(Gpa.DX11, new FileList());
            DerivedCounters.Add(Gpa.VK, new FileList());
            DerivedCounters.Add(Gpa.GL, new FileList());
            DerivedCounters.Add(Gpa.CL, new FileList());
        }

        /// <summary>
        /// Process the passed files depending on its name prefix
        /// </summary>
        /// <param name="fileName">name of the file</param>
        public static void ProcessFiles(string fileName)
        {
            string file = Gpa.GetFileNameFromFilePath(fileName);

            // PublicCounterDefs*
            {
                int indexOf = file.IndexOf((IsInternal ? Gpa.internal_file_prefix : Gpa.public_file_prefix) + Gpa.CounterDefOutFileName, StringComparison.Ordinal);
                if (indexOf != -1)
                {
                    string api = Gpa.GetApiFromFileName(file);
                    if (null != api)
                    {
                        CounterDefs[api].Add(fileName);
                    }
                }
            }

            // DerivedCounterDefs*
            {
                int indexOf = file.IndexOf((IsInternal ? Gpa.internal_file_prefix : Gpa.public_file_prefix) + Gpa.DerivedCounterOutFileName, StringComparison.Ordinal);
                if (indexOf != -1)
                {
                    string api = Gpa.GetApiFromFileName(file);
                    if (null != api)
                    {
                        DerivedCounters[api].Add(fileName);
                    }
                }
            }
        }

        /// <summary>
        /// Writes the CMake file
        /// </summary>
        public static void CMakeWriter()
        {
            string TypePrefix = (IsInternal ? Gpa.InternalStr : Gpa.PublicStr);
            foreach (var api in CounterDefs)
            {
                bool init = false;
                TextWriter CMakeWriter = null;
                string headerFiles = "set(" + TypePrefix.ToUpper() + "_COUNTER_DEF_HEADERS_" + api.Key.ToUpper();
                string sourceFiles = "set(" + TypePrefix.ToUpper() + "_COUNTER_DEF_SRC_" + api.Key.ToUpper();
                bool foundHeader = false;
                foreach (var fileName in api.Value)
                {
                    if (!init)
                    {
                        init = true;
                        string CMakeFileName = Gpa.GetDirectoryFromFilePath(fileName) + "\\" +
                                               TypePrefix.ToLower() + "_" +
                                               Gpa.CounterDefOutFileName + api.Key + ".cmake";
                        CMakeWriter = new StreamWriter(CMakeFileName);
                        CMakeWriter.WriteLine(
                            "## Copyright (c) {0} Advanced Micro Devices, Inc. All rights reserved.", DateTime.Today.Year);
                        CMakeWriter.WriteLine("cmake_minimum_required(VERSION 3.5.1)");
                        CMakeWriter.WriteLine();
                        CMakeWriter.WriteLine("set(CMAKE_INCLUDE_CURRENT_DIR ON)");
                    }

                    if (Gpa.IsHeaderFile(fileName))
                    {
                        headerFiles = headerFiles + Environment.NewLine + "${CMAKE_CURRENT_LIST_DIR}/" + Gpa.GetFileNameFromFilePath(fileName);
                        foundHeader = true;
                    }
                    else
                    {
                        sourceFiles = sourceFiles + Environment.NewLine + "${CMAKE_CURRENT_LIST_DIR}/" + Gpa.GetFileNameFromFilePath(fileName);
                    }
                }

                if (null != CMakeWriter)
                {
                    if (foundHeader)
                    {
                        headerFiles = headerFiles + ")" + Environment.NewLine;
                    }

                    sourceFiles = sourceFiles + ")" + Environment.NewLine;

                    if (foundHeader)
                    {
                        CMakeWriter.WriteLine(headerFiles);
                    }

                    CMakeWriter.WriteLine(sourceFiles);
                    CMakeWriter.Close();
                }
            }

            // DerivedCounterDefs
            foreach (var api in DerivedCounters)
            {
                bool init = false;
                TextWriter CMakeWriter = null;
                string headerFiles = "set(" + TypePrefix.ToUpper() + "_DERIVED_COUNTERS_API_HEADERS_" + api.Key.ToUpper();
                string sourceFiles = "set(" + TypePrefix.ToUpper() + "_DERIVED_COUNTERS_API_SRC_" + api.Key.ToUpper();
                bool foundHeader = false;
                foreach (var fileName in api.Value)
                {
                    if (!init)
                    {
                        init = true;
                        string CMakeFileName = Gpa.GetDirectoryFromFilePath(fileName) + "\\" +
                                               TypePrefix.ToLower() + "_" +
                                               Gpa.DerivedCounterOutFileName + api.Key + ".cmake";
                        CMakeWriter = new StreamWriter(CMakeFileName);
                        CMakeWriter.WriteLine(
                            "## Copyright (c) {0} Advanced Micro Devices, Inc. All rights reserved.", DateTime.Today.Year);
                        CMakeWriter.WriteLine("cmake_minimum_required(VERSION 3.5.1)");
                        CMakeWriter.WriteLine();
                        CMakeWriter.WriteLine("set(CMAKE_INCLUDE_CURRENT_DIR ON)");
                    }

                    if (Gpa.IsHeaderFile(fileName))
                    {
                        headerFiles = headerFiles + Environment.NewLine + "${CMAKE_CURRENT_LIST_DIR}/" + Gpa.GetFileNameFromFilePath(fileName);
                        foundHeader = true;
                    }
                    else
                    {
                        sourceFiles = sourceFiles + Environment.NewLine + "${CMAKE_CURRENT_LIST_DIR}/" + Gpa.GetFileNameFromFilePath(fileName);
                    }
                }

                if (null != CMakeWriter)
                {
                    if (foundHeader)
                    {
                        headerFiles = headerFiles + ")" + Environment.NewLine;
                    }

                    sourceFiles = sourceFiles + ")" + Environment.NewLine;

                    if (foundHeader)
                    {
                        CMakeWriter.WriteLine(headerFiles);
                    }

                    CMakeWriter.WriteLine(sourceFiles);
                    CMakeWriter.Close();
                }
            }
        }
    }
}
