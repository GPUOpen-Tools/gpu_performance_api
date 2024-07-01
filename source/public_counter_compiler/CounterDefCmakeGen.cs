// =====================================================================
// <copyright file="CounterDefCMakeGen.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2019-2023 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//      CMake File generator for counter definitions.
// </summary>
// =====================================================================

using System;
using System.Collections.Generic;
using System.IO;
using ApiDictionary = System.Collections.Generic.Dictionary<string, System.Collections.Generic.List<string>>;
using FileList = System.Collections.Generic.List<string>;

namespace GpaTools
{
    class CounterDefCMakeGenerator
    {
        /// <summary>
        /// Derived counter names dictionary
        /// </summary>
        public static ApiDictionary derivedCounters = new ApiDictionary();

        /// <summary>
        /// counter definitions dictionary
        /// </summary>
        public static ApiDictionary counterDefs = new ApiDictionary();


        /// <summary>
        /// Initializes the memory for the file lists
        /// </summary>
        public static void Init()
        {
            // PublicCounterDefs - GPA
            counterDefs.Add(Gpa.DX12, new FileList());
            counterDefs.Add(Gpa.DX11, new FileList());
            counterDefs.Add(Gpa.VK, new FileList());
            counterDefs.Add(Gpa.GL, new FileList());
            counterDefs.Add(Gpa.CL, new FileList());

            // PublicDerivedCounters - GPA
            derivedCounters.Add(Gpa.DX12, new FileList());
            derivedCounters.Add(Gpa.DX11, new FileList());
            derivedCounters.Add(Gpa.VK, new FileList());
            derivedCounters.Add(Gpa.GL, new FileList());
            derivedCounters.Add(Gpa.CL, new FileList());
        }

        /// <summary>
        /// Process the passed files depending on its name prefix
        /// </summary>
        /// <param name="fileName">name of the file</param>
        public static void ProcessFiles(string fileName)
        {
            string file = Gpa.GetFileNameFromFilePath(fileName);

            string prefix = Gpa.publicFilePrefix;

            // PublicCounterDefs*
            {
                int indexOf = file.IndexOf(prefix + Gpa.counterDefinitionsStr, StringComparison.Ordinal);
                if (indexOf != -1)
                {
                    string api = Gpa.GetApiFromFileName(file);
                    if (null != api)
                    {
                        counterDefs[api].Add(fileName);
                    }
                }
            }

            // DerivedCounterDefs*
            {
                int indexOf = file.IndexOf(prefix + Gpa.derivedCounterOutFileName, StringComparison.Ordinal);
                if (indexOf != -1)
                {
                    string api = Gpa.GetApiFromFileName(file);
                    if (null != api)
                    {
                        derivedCounters[api].Add(fileName);
                    }
                }
            }
        }

        /// <summary>
        /// Writes the CMake file
        /// </summary>
        public static void CMakeWriter()
        {
            string TypePrefix = Gpa.publicStr;

            foreach (var api in counterDefs)
            {
                bool Init = false;
                TextWriter CMakeWriter = null;
                string headerFiles = "set(" + TypePrefix.ToUpper() + "_COUNTER_DEF_HEADERS_" + api.Key.ToUpper();
                string sourceFiles = "set(" + TypePrefix.ToUpper() + "_COUNTER_DEF_SRC_" + api.Key.ToUpper();
                bool foundHeader = false;
                foreach (var fileName in api.Value)
                {
                    if (!Init)
                    {
                        Init = true;
                        string CMakeFileName = Gpa.GetDirectoryFromFilePath(fileName) + "\\" +
                                               TypePrefix.ToLower() + "_" +
                                               Gpa.counterDefinitionsStr + api.Key + ".cmake";
                        CMakeWriter = new StreamWriter(CMakeFileName);
                        CMakeWriter.WriteLine("## Copyright (c) {0} Advanced Micro Devices, Inc. All rights reserved.", DateTime.Today.Year);
                        CMakeWriter.WriteLine("cmake_minimum_required(VERSION 3.10)");
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
            foreach (var api in derivedCounters)
            {
                bool Init = false;
                TextWriter CMakeWriter = null;
                string headerFiles = "set(" + TypePrefix.ToUpper() + "_DERIVED_COUNTERS_API_HEADERS_" + api.Key.ToUpper();
                string sourceFiles = "set(" + TypePrefix.ToUpper() + "_DERIVED_COUNTERS_API_SRC_" + api.Key.ToUpper();
                bool foundHeader = false;
                foreach (var fileName in api.Value)
                {
                    if (!Init)
                    {
                        Init = true;
                        string CMakeFileName = Gpa.GetDirectoryFromFilePath(fileName) + "\\" +
                                               TypePrefix.ToLower() + "_" +
                                               Gpa.derivedCounterOutFileName + api.Key + ".cmake";
                        CMakeWriter = new StreamWriter(CMakeFileName);
                        CMakeWriter.WriteLine("## Copyright (c) {0} Advanced Micro Devices, Inc. All rights reserved.", DateTime.Today.Year);
                        CMakeWriter.WriteLine("cmake_minimum_required(VERSION 3.10)");
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
