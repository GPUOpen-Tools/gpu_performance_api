// =====================================================================
// <copyright file="CMakeGenerator.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//      Generates the CMake file for the listed directories
// </summary>
// =====================================================================

using System;
using System.Collections.Generic;
using System.IO;

namespace GPATools
{
    class CMakeGenerator
    {
        public delegate void ProcessFilesDelegate(string fileName);
        public delegate void InitDelegate();
        public delegate void CMakeWriterDelegate();
        public static ProcessFilesDelegate ProcessFile = null;
        public static InitDelegate Init = null;
        public static CMakeWriterDelegate CMakeWriter = null;
        private static readonly List<string> DirList = new List<string>();

        /// <summary>
        /// Adds the directory
        /// </summary>
        /// <param name="dir">directory name</param>
        public static void AddDirectory(string dir)
        {
            DirList.Add(dir);
        }

        /// <summary>
        /// Generates the CMake file
        /// </summary>
        public static void GenerateCMakeFiles()
        {
            Init?.Invoke();
            foreach (var dir in DirList)
            {
                ProcessDir(dir);
            }

            CMakeWriter?.Invoke();

        }

        /// <summary>
        /// Process the directory
        /// </summary>
        /// <param name="directory">directory name</param>
        private static void ProcessDir(string directory)
        {
            string[] files = Directory.GetFiles(directory);
            foreach (var file in files)
            {

                if (file.Contains(".txt") || file.Contains(".h") || file.Contains(".cpp"))
                {
                    ProcessFile?.Invoke(file);
                }

            }

            string[] subDir = Directory.GetDirectories(directory);

            foreach (var dir in subDir)
            {
                ProcessDir(dir);
            }
        }
    }
}
