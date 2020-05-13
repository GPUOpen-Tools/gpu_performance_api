// =====================================================================
// <copyright file="FileNameAndPaths.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
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

namespace GPATools
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
        Unknown
    };

    class Gpa
    {
        public static string GpaStr = "GPA\\";
        public static string AutoGenPublicCounterInputDir = GpaStr + "source\\auto_generated\\public_counter_compiler_input_files\\";
        public static string AutoGenCounterGeneratorOutDir = GpaStr + "source\\auto_generated\\gpu_perf_api_counter_generator\\";
        public static string PublicStr = "Public";
        public static string InternalStr = "Internal";
        public static string public_file_prefix = "public_";
        public static string internal_file_prefix = "internal_";
        public static string CounterFileNamePrefix = "counter_names_";
        public static string CounterListOutDir = "counter_list_files\\";
        public static string AutoGenTestOutDir = GpaStr + "source\\auto_generated\\gpu_perf_api_unit_tests\\counters\\";
        public static string GpaDocSourceDir = GpaStr + "docs\\sphinx\\source\\";
        public static string CounterDefDir = GpaStr + "source\\public_counter_compiler_input_files\\";
        public static string CounterDefFilePrefix = "counter_definitions_";
        public static string CounterDefOutFileName = "counter_definitions_";
        public static string DerivedCounterOutFileName = "derived_counters_";
        public static string GPACounterHeaderFileStr = "gpa_counter.h";
        public static string HardwareCounterFileNamePrefix = "gpa_hw_counter_";
        public static string ApiCountersFileNamePrefix = "gpa_hw_counter_";
        public static string HardwareExposedCounterFileSuffix = "gpa_hw_exposed_counters_";
        public static string counter_name_list_file_prefix = "counter_name_list_";
        public static string DX12 = "dx12";
        public static string DX11 = "dx11";
        public static string GL = "gl";
        public static string CL = "cl";
        public static string VK = "vk";
        public static string gfx8_str = "gfx8";
        public static string gfx9_str = "gfx9";
        public static string gfx10_str = "gfx10";
        public static Dictionary<GfxGeneration, string> GfxGenAsStr = new Dictionary<GfxGeneration, string>();
        public static Dictionary<Api, string> ApiAsStr = new Dictionary<Api, string>();
        public static Dictionary<GfxGeneration, string> GfxGenerationDisplayName = new Dictionary<GfxGeneration, string>();

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
            int endPath = Application.StartupPath.LastIndexOf("GPA", StringComparison.Ordinal);
            string gpaPath = Application.StartupPath.Substring(0, endPath);
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

            string pathName = gpaPath + AutoGenPublicCounterInputDir;
            if (!Directory.Exists(pathName))
            {
                Directory.CreateDirectory(pathName);
            }

            pathName = gpaPath + AutoGenCounterGeneratorOutDir;
            if (!Directory.Exists(pathName))
            {
                Directory.CreateDirectory(pathName);
            }

            pathName = gpaPath + AutoGenTestOutDir;
            if (!Directory.Exists(pathName))
            {
                Directory.CreateDirectory(pathName);
            }

            GfxGenAsStr.Add(GfxGeneration.Gfx10, gfx10_str);
            GfxGenAsStr.Add(GfxGeneration.Gfx9, gfx9_str);
            GfxGenAsStr.Add(GfxGeneration.Gfx8, gfx8_str);

            GfxGenerationDisplayName.Add(GfxGeneration.Gfx10, "Navi");
            GfxGenerationDisplayName.Add(GfxGeneration.Gfx9, "Vega");
            GfxGenerationDisplayName.Add(GfxGeneration.Gfx8, "Graphics IP v8");

            ApiAsStr.Add(Api.DX11, DX11);
            ApiAsStr.Add(Api.DX12, DX12);
            ApiAsStr.Add(Api.VK, VK);
            ApiAsStr.Add(Api.GL, GL);
            ApiAsStr.Add(Api.CL, CL);
        }

        /// <summary>
        /// Returns the API string from the file name
        /// </summary>
        /// <param name="filename">name of the file</param>
        /// <returns>api string</returns>
        public static string GetApiFromFileName(string filename)
        {
            if (filename.Contains(DX12))
            {
                return DX12;
            }

            if (filename.Contains(DX11))
            {
                return DX11;
            }

            if (filename.Contains(VK))
            {
                return VK;
            }

            if (filename.Contains(GL))
            {
                return GL;
            }

            if (filename.Contains(CL))
            {
                return CL;
            }

            return null;
        }
    }
}
