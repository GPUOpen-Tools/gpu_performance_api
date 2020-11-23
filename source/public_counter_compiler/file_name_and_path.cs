// =====================================================================
// <copyright file="FileNameAndPaths.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2019-2020 Advanced Micro Devices, Inc. All rights reserved.
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
        Gfx103,
        Unknown
    };

    class Gpa
    {
        public const string GpaStr = "GPA\\";
        public const string AutoGenPublicCounterInputDir = GpaStr + "source\\auto_generated\\public_counter_compiler_input_files\\";
        public const string AutoGenCounterGeneratorOutDir = GpaStr + "source\\auto_generated\\gpu_perf_api_counter_generator\\";
        public const string PublicStr = "Public";
        public const string InternalStr = "Internal";
        public const string public_file_prefix = "public_";
        public const string internal_file_prefix = "internal_";
        public const string CounterFileNamePrefix = "counter_names_";
        public const string CounterListOutDir = "counter_list_files\\";
        public const string AutoGenTestOutDir = GpaStr + "source\\auto_generated\\gpu_perf_api_unit_tests\\counters\\";
        public const string GpaDocSourceDir = GpaStr + "docs\\sphinx\\source\\";
        public const string CounterDefDir = GpaStr + "source\\public_counter_compiler_input_files\\";
        public const string CounterDefinitionsStr = "counter_definitions_";
        public const string DerivedCounterOutFileName = "derived_counters_";
        public const string GPACounterHeaderFileStr = "gpa_counter.h";
        public const string gpaHwCounterFilenamePrefix = "gpa_hw_counter_";
        public const string HardwareExposedCounterFileSuffix = "gpa_hw_exposed_counters_";
        public const string counter_name_list_file_prefix = "counter_name_list_";
        public const string DX12 = "dx12";
        public const string DX11 = "dx11";
        public const string GL = "gl";
        public const string CL = "cl";
        public const string VK = "vk";
        public const string gfx8_str = "gfx8";
        public const string gfx9_str = "gfx9";
        public const string gfx10_str = "gfx10";
        public const string gfx103_str = "gfx103";
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

            GfxGenAsStr.Add(GfxGeneration.Gfx103, gfx103_str);
            GfxGenAsStr.Add(GfxGeneration.Gfx10, gfx10_str);
            GfxGenAsStr.Add(GfxGeneration.Gfx9, gfx9_str);
            GfxGenAsStr.Add(GfxGeneration.Gfx8, gfx8_str);

            GfxGenerationDisplayName.Add(GfxGeneration.Gfx103, "RDNA2");
            GfxGenerationDisplayName.Add(GfxGeneration.Gfx10, "RDNA");
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
