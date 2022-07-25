// =====================================================================
// <copyright file="FileNameAndPaths.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//      GPA file name and paths
// </summary>
// =====================================================================

using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.IO;

namespace GpaTools
{
    enum Api
    {
        DX12,
        DX11,
        VK,
        GL,
        CL,
    };

    enum GfxGeneration
    {
        Gfx8,
        Gfx9,
        Gfx10,
        Gfx103,
        Unknown
    };

    class Gpa
    {
        public const string autoGenPublicCounterInputDir = "source\\auto_generated\\public_counter_compiler_input_files\\";
        public const string autoGenCounterGeneratorOutDir = "source\\auto_generated\\gpu_perf_api_counter_generator\\";
        public const string publicStr = "Public";
        public const string internalStr = "Internal";
        public const string publicFilePrefix = "public_";
        public const string internalFilePrefix = "internal_";
        public const string counterFileNamePrefix = "counter_names_";
        public const string counterListOutDir = "..\\counter_list_files\\";
        public const string autoGenTestOutDir = "source\\auto_generated\\gpu_perf_api_unit_tests\\counters\\";
        public const string gpaDocSourceDir = "docs\\sphinx\\source\\";
        public const string counterDefDir = "source\\public_counter_compiler_input_files\\";
        public const string counterDefinitionsStr = "counter_definitions_";
        public const string derivedCounterOutFileName = "derived_counters_";
        public const string gpaCounterHeaderFileStr = "gpu_perf_api_counter_generator/gpa_counter.h";
        public const string gpaHwCounterFilenamePrefix = "gpa_hw_counter_";
        public const string hardwareExposedCounterFileSuffix = "gpa_hw_exposed_counters_";
        public const string counterNameListFilePrefix = "counter_name_list_";
        public const string DX12 = "dx12";
        public const string DX11 = "dx11";
        public const string GL = "gl";
        public const string CL = "cl";
        public const string VK = "vk";
        public const string gfx8Str = "gfx8";
        public const string gfx9Str = "gfx9";
        public const string gfx10Str = "gfx10";
        public const string gfx103Str = "gfx103";
        public static Dictionary<GfxGeneration, string> gfxGenAsStr = new Dictionary<GfxGeneration, string>();
        public static Dictionary<Api, string> apiAsStr = new Dictionary<Api, string>();
        public static Dictionary<GfxGeneration, string> gfxGenerationDisplayName = new Dictionary<GfxGeneration, string>();

        public static string ToCamelCase(string word)
        {
            string temp_string = word[0].ToString().ToUpper() + word.Substring(1, word.Length - 1).ToLower();
            return temp_string;
        }

        /// <summary>
        /// Uses the Application's startup path to find the path to GPUPerfAPI.
        /// It assumes that the project is run from somewhere below the root GPUPerfAPI folder.
        /// </summary>
        /// <returns>The path to the root GPUPerfAPI folder</returns>
        public static string GetGpuPerfApiPath()
        {
            int endPath = Application.StartupPath.LastIndexOf("gpu_performance_api", StringComparison.Ordinal);
            string gpaPath = Application.StartupPath.Substring(0, endPath) + "gpu_performance_api\\";
            return gpaPath;
        }

        /// <summary>
        /// Get the directory from the absolute path of a file
        /// </summary>
        /// <param name="filePath">path of the file</param>
        /// <returns>directory of the file</returns>
        public static string GetDirectoryFromFilePath(string filePath)
        {
            string directory = null;
            int index = filePath.LastIndexOf("\\", StringComparison.OrdinalIgnoreCase);
            if (index < filePath.Length && (index != -1))
            {
                directory = filePath.Substring(0, index);
            }

            return directory;
        }

        /// <summary>
        /// Checks whether the file is a header file or not
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns>flag indicating file is a header file or not</returns>
        public static bool IsHeaderFile(string fileName)
        {
            bool isHeader = false;
            int index = fileName.LastIndexOf(".", StringComparison.OrdinalIgnoreCase);
            if (index != -1)
            {
                string extension = fileName.Substring(index, fileName.Length - index);
                if (extension.Equals(".h"))
                {
                    isHeader = true;
                }
            }

            return isHeader;
        }

        /// <summary>
        /// Get the file name from the absolute path of the file
        /// </summary>
        /// <param name="filePath">path of the file</param>
        /// <returns>name of the file</returns>
        public static string GetFileNameFromFilePath(string filePath)
        {
            string fileName = null;
            int index = filePath.LastIndexOf("\\", StringComparison.OrdinalIgnoreCase);
            if (index < filePath.Length && (index != -1))
            {
                fileName = filePath.Substring(index + 1, filePath.Length - index - 1);
            }

            return fileName;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        static Gpa()
        {
            string gpaPath = GetGpuPerfApiPath();

            string pathName = gpaPath + autoGenPublicCounterInputDir;
            if (!Directory.Exists(pathName))
            {
                Directory.CreateDirectory(pathName);
            }

            pathName = gpaPath + autoGenCounterGeneratorOutDir;
            if (!Directory.Exists(pathName))
            {
                Directory.CreateDirectory(pathName);
            }

            pathName = gpaPath + autoGenTestOutDir;
            if (!Directory.Exists(pathName))
            {
                Directory.CreateDirectory(pathName);
            }

            gfxGenAsStr.Add(GfxGeneration.Gfx103, gfx103Str);
            gfxGenAsStr.Add(GfxGeneration.Gfx10, gfx10Str);
            gfxGenAsStr.Add(GfxGeneration.Gfx9, gfx9Str);
            gfxGenAsStr.Add(GfxGeneration.Gfx8, gfx8Str);

            gfxGenerationDisplayName.Add(GfxGeneration.Gfx103, "RDNA2");
            gfxGenerationDisplayName.Add(GfxGeneration.Gfx10, "RDNA");
            gfxGenerationDisplayName.Add(GfxGeneration.Gfx9, "Vega");
            gfxGenerationDisplayName.Add(GfxGeneration.Gfx8, "Graphics IP v8");

            apiAsStr.Add(Api.DX11, DX11);
            apiAsStr.Add(Api.DX12, DX12);
            apiAsStr.Add(Api.VK, VK);
            apiAsStr.Add(Api.GL, GL);
            apiAsStr.Add(Api.CL, CL);
        }

        /// <summary>
        /// Returns the API string from the file name
        /// </summary>
        /// <param name="fileName">name of the file</param>
        /// <returns>api string</returns>
        public static string GetApiFromFileName(string fileName)
        {
            if (fileName.Contains(DX12))
            {
                return DX12;
            }

            if (fileName.Contains(DX11))
            {
                return DX11;
            }

            if (fileName.Contains(VK))
            {
                return VK;
            }

            if (fileName.Contains(GL))
            {
                return GL;
            }

            if (fileName.Contains(CL))
            {
                return CL;
            }

            return null;
        }
    }
}
