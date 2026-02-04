// =====================================================================
// <copyright file="CounterCompiler.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2025 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//    Given an ordered internal counter definition file and the derived (e.g.: public)
//    definitions, produces c++ code to define them for the run-time.
// </summary>
// =====================================================================
namespace PublicCounterCompiler
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Windows.Forms;
    using System.Diagnostics;
    using GpaTools;
    using static GpaTools.Gpa;
    using CounterGroup = System.String;
    using CounterName = System.String;
    using CounterDescription = System.String;
    using System.Runtime.Serialization;

    /// <summary>
    /// Compiles the derived counters definitions into C++ files.
    /// </summary>
    public class CounterCompiler
    {
        /// <summary>
        /// Derived counter input file
        /// </summary>
        public class DerivedCounterFileInput
        {
            /// <summary>
            /// Root filename
            /// </summary>
            public string rootFilename;

            /// <summary>
            /// compiler type string
            /// </summary>
            public string compiler_type_str;

            /// <summary>
            /// Compiler input path
            /// </summary>
            public string compilerInputPath;

            /// <summary>
            /// Auto-generated compiler file input path
            /// </summary>
            public string autoGenCompilerInputFilePath;

            /// <summary>
            /// Derived counter h/cpp file output directory
            /// </summary>
            public string outputDirectory;

            /// <summary>
            /// Counter list output directory
            /// </summary>
            public string counterListOutputDirectory;

            /// <summary>
            /// Test output directory
            /// </summary>
            public string testOutputDirectory;
        }

        /// <summary>
        /// Derived counter file input
        /// </summary>
        public DerivedCounterFileInput derivedCounterFileInput = null;

        /// <summary>
        /// A map of Counter Group to a map of counter name to documentation info for Graphics Counters
        /// </summary>
        private Dictionary<GfxGeneration, Dictionary<CounterGroup, Dictionary<string, DerivedCounterDef>>>
            docInfoMapGraphicsByGeneration =
                new Dictionary<GfxGeneration, Dictionary<CounterGroup, Dictionary<string, DerivedCounterDef>>>();

        /// <summary>
        /// Indicates if this app is being run as a console app (true) or UI app (false)
        /// </summary>
        public bool isConsoleApp = true;

        /// <summary>
        /// List of global GPU generation internal counters
        /// </summary>
        private List<InternalCounterDef> globalInternalCounterList = null;

        /// <summary>
        /// Gets a value indicating whether invalid counters should be considered errors, or if they should be ignored.
        /// </summary>
        /// <returns>True to ignore the invalid counters; false if they should be considered errors.</returns>
        public bool IgnoreInvalidCounters()
        {
            if (isConsoleApp)
            {
                // by default, running from the console will ignore invalid counters
                return true;
            }

            return Form1.GetIgnoreInvalidCounters;
        }

        /// <summary>
        /// Sets directories based on the supplied API and generation and
        /// compiles the derived counters
        /// </summary>
        /// <param name="api">The API to compile counters for</param>
        /// <param name="generation">The HW generation</param>
        /// <param name="infoHandler">Called in response to an informational message</param>
        /// <param name="errorHandler">Called in response to a error condition</param>
        /// <returns>true on success, false if there were any errors</returns>
        public bool CompileCounters(
            string api,
            string generation,
            Func<string, bool> infoHandler,
            Func<string, bool> errorHandler
            )
        {
            try
            {
                string baseGfxFileName = derivedCounterFileInput.rootFilename + GpaTools.Gpa.counterFileNamePrefix + api.ToLower() + "_" + generation.ToLower() + ".txt";
                string[] baseGfxFileNames = Directory.GetFiles(derivedCounterFileInput.autoGenCompilerInputFilePath, baseGfxFileName);

                // Iterate over files that match the base of the counter name's generation file
                string searchForAsicFilename = derivedCounterFileInput.rootFilename + GpaTools.Gpa.counterFileNamePrefix + api.ToLower() + "_" + generation.ToLower() + "_*.txt";

                string[] asicfileNames = Directory.GetFiles(derivedCounterFileInput.autoGenCompilerInputFilePath, searchForAsicFilename);

                List<String> fileNames = new List<string>();

                foreach (string counterNamesFile in baseGfxFileNames)
                {
                    // Enforce that only lowercase file names are used.
                    string filename = Path.GetFileName(counterNamesFile);
                    if (filename != filename.ToLower())
                    {
                        errorHandler("Public counter name file has uppercase characters in it: " + counterNamesFile + ". Only lowercase names are currently supported.");
                        return false;
                    }

                    fileNames.Add(counterNamesFile);
                }

                foreach (string counterNamesFile in asicfileNames)
                {
                    fileNames.Add(counterNamesFile);
                }

                if (fileNames.Count == 0)
                {
                    infoHandler("No files found at:" + derivedCounterFileInput.compilerInputPath + " matching:" + baseGfxFileName);
                    return false;
                }

                List<string> asicSpecificFiles = new List<string>();

                string baseCounterDefFile = "";
                foreach (string counterNamesFile in fileNames)
                {
                    // Determine the specific ASIC, if any
                    string baseFilename = Path.GetFileNameWithoutExtension(counterNamesFile);
                    bool isBaseDeriveCounterDefFileParsing = false;

                    int asicIndex = baseFilename.IndexOf(generation.ToLower());
                    string asic = baseFilename.Substring(asicIndex + generation.Length);

                    if (!string.IsNullOrEmpty(asic))
                    {
                        asic = asic.Substring(1, asic.Length - 1);
                        asicSpecificFiles.Add(asic);
                        isBaseDeriveCounterDefFileParsing = false;
                    }
                    else
                    {
                        isBaseDeriveCounterDefFileParsing = true;
                    }

                    // Suffix
                    string suffix = string.Empty;

                    string derivedCounterDefsFile = derivedCounterFileInput.compilerInputPath +
                                                    derivedCounterFileInput.rootFilename +
                                                    GpaTools.Gpa.counterDefinitionsStr +
                                                    suffix +
                                                    generation.ToLower() +
                                                    (!String.IsNullOrEmpty(asic) ? "_" + asic.ToLower() : "") +
                                                    ".txt";

                    string section = api + generation;

                    if (isBaseDeriveCounterDefFileParsing && String.IsNullOrEmpty(baseCounterDefFile))
                    {
                        baseCounterDefFile = derivedCounterDefsFile;
                    }

                    // Some files may not exist for certain combinations of APIs and architectures
                    if (!File.Exists(derivedCounterDefsFile))
                    {
                        if (!isBaseDeriveCounterDefFileParsing && !String.IsNullOrEmpty(baseCounterDefFile))
                        {
                            infoHandler("Info: Unable to find file " + derivedCounterDefsFile + " Using base counter def file.");
                            derivedCounterDefsFile = baseCounterDefFile;
                        }
                        else
                        {
                            infoHandler("Info: Unable to find file " + derivedCounterDefsFile);
                            return true;
                        }
                    }

                    if (LoadFilesAndGenerateOutput(derivedCounterFileInput.rootFilename,
                        counterNamesFile,
                        derivedCounterDefsFile,
                        derivedCounterFileInput.outputDirectory,
                        derivedCounterFileInput.counterListOutputDirectory,
                        derivedCounterFileInput.testOutputDirectory,
                        api,
                        generation,
                        asic,
                        infoHandler,
                        errorHandler))
                    {
                        infoHandler(derivedCounterFileInput.rootFilename + Gpa.counterDefinitionsStr + section + asic + ".cpp / .h written out to:" + derivedCounterFileInput.outputDirectory);
                    }
                    else
                    {
                        return false;
                    }
                }

                // Generate section + ASIC file
                bool retVal = GenerateSectionAsicFiles(derivedCounterFileInput.rootFilename, api, generation, derivedCounterFileInput.outputDirectory, asicSpecificFiles, infoHandler, errorHandler);

                if (retVal)
                {
                    infoHandler("Counter generation completed successfully");
                }
                else
                {
                    errorHandler("Counter generation failed");
                }

                return retVal;
            }
            catch (Exception e)
            {
                errorHandler(e.ToString());
                return false;
            }
        }

        /// <summary>
        /// Generates ASIC files
        /// </summary>
        /// <param name="rootFilename">Root filename for ASIC files.</param>
        /// <param name="api">API being generated.</param>
        /// <param name="generation">GPU generation.</param>
        /// <param name="outputDirectory">Output directory.</param>
        /// <param name="asicSpecificFiles">List of ASIC-specific files.</param>
        /// <param name="infoHandler">Called in response to an informational message</param>
        /// <param name="errorHandler">Called in response to a error condition</param>
        /// <returns>True is files are successfully loaded and generated.</returns>
        private bool GenerateSectionAsicFiles(
            string rootFilename,
            string api,
            string generation,
            string outputDirectory,
            List<string> asicSpecificFiles,
            Func<string, bool> infoHandler,
            Func<string, bool> errorHandler
            )
        {
            string section = api + "_" + generation;
            string filename = outputDirectory + rootFilename + Gpa.counterDefinitionsStr +
                              api.ToLower() + "_" + generation.ToLower() + "_" + "asics.h";

            // Write header file.
            infoHandler("Writing ASIC header to " + filename);
            StreamWriter includeFile = null;
            try
            {
                includeFile = new StreamWriter(filename);
            }
            catch
            {
                errorHandler("Failed to open file for writing: " + filename);
                return false;
            }

            string baseDirForHeaderGuard = "GPA";

            includeFile.WriteLine("//==============================================================================");
            includeFile.WriteLine("// Copyright (c) 2010-{0} Advanced Micro Devices, Inc. All rights reserved.", DateTime.Today.Year);
            includeFile.WriteLine("/// @author AMD Developer Tools Team");
            includeFile.WriteLine("/// @file");
            includeFile.WriteLine("/// @brief {0} Counter Definitions ASIC file for {1}", derivedCounterFileInput.compiler_type_str, section.ToUpper());
            includeFile.WriteLine("//==============================================================================");
            includeFile.WriteLine();
            includeFile.WriteLine("#ifndef {0}_AUTO_GEN_COUNTER_GEN_{1}COUNTER_DEFINITIONS_{2}_ASICS_H_", baseDirForHeaderGuard, rootFilename.ToUpper(), section.ToUpper());
            includeFile.WriteLine("#define {0}_AUTO_GEN_COUNTER_GEN_{1}COUNTER_DEFINITIONS_{2}_ASICS_H_", baseDirForHeaderGuard, rootFilename.ToUpper(), section.ToUpper());
            includeFile.WriteLine();
            includeFile.WriteLine("//*** Note, this is an auto-generated file. Do not edit. Execute {0}CounterCompiler to rebuild.", derivedCounterFileInput.compiler_type_str);
            includeFile.WriteLine();
            includeFile.WriteLine("#include \"gpu_perf_api_counter_generator/gpa_derived_counter.h\"");
            includeFile.WriteLine();

            includeFile.WriteLine("#include \"auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_{0}_{1}.h\"", api.ToLower(), generation.ToLower());
            includeFile.WriteLine();

            foreach (string asic in asicSpecificFiles)
            {
                includeFile.WriteLine("#include \"auto_generated/gpu_perf_api_counter_generator/{0}{1}{2}_{3}_{4}.h\"", rootFilename, counterDefinitionsStr, api.ToLower(), generation.ToLower(), asic.ToLower());
            }

            if (0 != asicSpecificFiles.Count)
            {
                includeFile.WriteLine();
            }

            includeFile.WriteLine("namespace {0}_asics", section.ToLower());
            includeFile.WriteLine("{");

            includeFile.WriteLine("    /// @brief Updates default GPU generation derived counters with ASIC specific derived counters if available.");
            includeFile.WriteLine("    ///");
            includeFile.WriteLine("    /// @param [in] desired_generation Hardware generation currently in use.");
            includeFile.WriteLine("    /// @param [in] asic_type The ASIC type that is currently in use.");
            includeFile.WriteLine("    /// @param [out] c Returned set of derived counters, if available.");
            includeFile.WriteLine("    ///");
            includeFile.WriteLine("    /// @return True if the ASIC matched one available, and c was updated.");
            includeFile.WriteLine("    inline void Update{0}AsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c)", derivedCounterFileInput.compiler_type_str);
            includeFile.WriteLine("    {");

            if (asicSpecificFiles.Count == 0)
            {
                includeFile.WriteLine("        UNREFERENCED_PARAMETER(desired_generation);");
                includeFile.WriteLine("        UNREFERENCED_PARAMETER(asic_type);");
                includeFile.WriteLine("        UNREFERENCED_PARAMETER(c);");
                if ("dx12" == api.ToLower())
                {
                    includeFile.WriteLine();
                    includeFile.WriteLine("        // Assign default max block events.");
                    includeFile.WriteLine("        counter_{0}::OverrideMaxBlockEvents(asic_type);", section.ToLower());
                }
            }
            else
            {
                if ("dx12" == api.ToLower())
                {
                    includeFile.WriteLine("        // Override max block events first so we could chain these if we want");
                    includeFile.WriteLine("        counter_{0}::OverrideMaxBlockEvents(asic_type);", section.ToLower());
                    includeFile.WriteLine();
                }

                for (int i = 0; i < asicSpecificFiles.Count; ++i)
                {
                    includeFile.WriteLine("        if ({0}_{1}::Update{2}AsicSpecificCounters(desired_generation, asic_type, c))", section.ToLower(), asicSpecificFiles[i].ToLower(), derivedCounterFileInput.compiler_type_str);
                    includeFile.WriteLine("        {");
                    includeFile.WriteLine("            return;");
                    includeFile.WriteLine("        }");
                    includeFile.WriteLine();
                }
            }

            includeFile.WriteLine("    }");

            includeFile.WriteLine();
            includeFile.WriteLine("}  // namespace " + section.ToLower() + "asics");
            includeFile.WriteLine();

            includeFile.WriteLine("#endif  // {0}_AUTO_GEN_COUNTER_GEN_{1}COUNTER_DEFINITIONS_{2}_ASICS_H_", baseDirForHeaderGuard, rootFilename.ToUpper(), section.ToUpper());
            includeFile.Close();
            return true;
        }

        /// <summary>
        /// Formats a counter error for output
        /// </summary>
        /// <param name="counterName">Derived counter name</param>
        /// <param name="component">Component of the formula that is referenced</param>
        /// <param name="index">Index of the component of the formula that is referenced</param>
        /// <param name="errorMessage">Error message</param>
        private void OutputCounterError(string counterName, string component, int index, string errorMessage, Func<string, bool> errorHandler)
        {
            errorHandler(counterName + " - " + errorMessage + " " + component + " at index " + index);
        }

        /// <summary>
        /// Validates the counter formula and referenced hardware counters
        /// </summary>
        /// <param name="counter">Derived counter to validate</param>
        /// <returns>True if the formula and referenced counters are correct, otherwise false.</returns>
        private bool ValidateFormulaAndReferencedCounter(DerivedCounterDef counter, Func<string, bool> infoHandler, Func<string, bool> errorHandler)
        {
            bool retVal = true;

            string comp = counter.Comp.ToLower();
            string[] components = comp.Split(',');

            // Basic validation of comp formula
            // Validate count of counters vs. those referenced in formula
            // Validate that all counter references are 1, or multiple of 4

            Stack<string> rpnStack = new Stack<string>();

            int componentIndex = -1;

            foreach (string component in components)
            {
                ++componentIndex;

                // Empty
                if (string.IsNullOrEmpty(component))
                {
                    OutputCounterError(counter.Name, component, componentIndex, "empty comp component", errorHandler);
                    retVal = false;
                    break;
                }

                // Range hardware counter reference
                bool isNumeric = false;

                if (component.Contains(".."))
                {
                    int startingCounter = 0;
                    isNumeric = int.TryParse(component, out startingCounter);
                    if (!isNumeric)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "invalid hardware counter range", errorHandler);
                        retVal = false;
                        break;
                    }

                    int ellipsisIndex = component.IndexOf("..");
                    if (ellipsisIndex < 0)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "invalid hardware counter range", errorHandler);
                        retVal = false;
                        break;
                    }

                    int endingCounter = 0;
                    isNumeric = int.TryParse(component.Substring(ellipsisIndex + 2), out endingCounter);
                    if (!isNumeric)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "invalid hardware counter range", errorHandler);
                        retVal = false;
                        break;
                    }

                    if (endingCounter <= startingCounter)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "invalid hardware counter range", errorHandler);
                        retVal = false;
                        break;
                    }

                    if (((endingCounter - startingCounter) + 1) % 4 != 0)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "hardware counter range is not a multiple of 4", errorHandler);
                        retVal = false;
                        break;
                    }

                    for (int i = startingCounter; i <= endingCounter; ++i)
                    {
                        rpnStack.Push(i.ToString());

                        var hardwareCounter = counter.GetCounter(i);
                        if (hardwareCounter == null)
                        {
                            OutputCounterError(counter.Name, component, componentIndex, "reference to undefined hardware counter index", errorHandler);
                            retVal = false;
                            break;
                        }

                        hardwareCounter.Referenced = true;
                    }

                    continue;
                }

                // Singleton hardware counter reference
                int index;
                isNumeric = int.TryParse(component, out index);
                if (isNumeric)
                {
                    rpnStack.Push(component);

                    if (index < 0 || index >= counter.GetCounterCount())
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "reference to out of range hardware counter index", errorHandler);
                        retVal = false;
                        break;
                    }

                    var hardwareCounter = counter.GetCounter(index);
                    if (hardwareCounter == null)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "reference to undefined hardware counter index", errorHandler);
                        retVal = false;
                        break;
                    }

                    hardwareCounter.Referenced = true;

                    continue;
                }

                // Numeric
                if (component.Substring(0, 1) == "(")
                {
                    string n = component.Substring(1, component.Length - 2);

                    float value = 0;
                    isNumeric = float.TryParse(n, out value);
                    if (!isNumeric)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "invalid numeric value", errorHandler);
                        retVal = false;
                        break;
                    }

                    rpnStack.Push(component);
                    continue;
                }

                // Operator
                switch (component)
                {
                    case "+":
                    case "-":
                    case "*":
                    case "/":
                        {
                            if (rpnStack.Count < 2)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "stack has insufficient entries (pop 2) for", errorHandler);
                                retVal = false;
                                break;
                            }
                            string result = rpnStack.Pop();
                            result = component + result;
                            result = rpnStack.Pop() + result;
                            rpnStack.Push(result);
                        }
                        continue;

                    case "ifnotzero":
                        {
                            if (rpnStack.Count < 3)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "stack has insufficient entries (pop 3) for", errorHandler);
                                retVal = false;
                                break;
                            }
                            string result = rpnStack.Pop();

                            // the format is: false,true,condition,ifnotzero
                            // detect if condition is a constant value
                            if (result.Contains("("))
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "ifnotzero conditional expression is constant", errorHandler);
                                retVal = false;
                                break;
                            }

                            result += "!=0 ? ";
                            result += rpnStack.Pop();
                            result += " : ";
                            result += rpnStack.Pop();
                            rpnStack.Push(result);
                        }
                        continue;

                    case "comparemax6":
                        {
                            if (rpnStack.Count < 12)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "stack has insufficient entries (pop 12) for", errorHandler);
                                retVal = false;
                                break;
                            }
                            string result = string.Empty;
                            result = "max(";
                            for (int i = 0; i < 6; ++i)
                            {
                                result = rpnStack.Pop();
                                if (i != 5)
                                {
                                    result += ", ";
                                }
                            }
                            result = ") ? ret(";
                            for (int i = 0; i < 6; ++i)
                            {
                                result = rpnStack.Pop();
                                if (i != 5)
                                {
                                    result += ", ";
                                }
                            }
                            result = ")";
                            rpnStack.Push(result);
                        }
                        continue;

                    case "comparemax4":
                        {
                            if (rpnStack.Count < 8)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "stack has insufficient entries (pop 8) for", errorHandler);
                                retVal = false;
                                break;
                            }
                            string result = string.Empty;
                            result = "max(";
                            for (int i = 0; i < 4; ++i)
                            {
                                result += rpnStack.Pop();
                                if (i != 3)
                                {
                                    result += ", ";
                                }
                            }
                            result += ") ? ret(";
                            for (int i = 0; i < 4; ++i)
                            {
                                result += rpnStack.Pop();
                                if (i != 3)
                                {
                                    result += ", ";
                                }
                            }
                            result += ")";
                            rpnStack.Push(result);
                        }
                        continue;

                    case "comparemax2":
                        {
                            if (rpnStack.Count < 4)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "stack has insufficient entries (pop 4) for", errorHandler);
                                retVal = false;
                                break;
                            }
                            string result = string.Empty;
                            result = "max(";
                            for (int i = 0; i < 2; ++i)
                            {
                                result += rpnStack.Pop();
                                if (i != 1)
                                {
                                    result += ", ";
                                }
                            }
                            result += ") ? ret(";
                            for (int i = 0; i < 2; ++i)
                            {
                                result += rpnStack.Pop();
                                if (i != 1)
                                {
                                    result += ", ";
                                }
                            }
                            result += ")";
                            rpnStack.Push(result);
                        }
                        continue;
                    case "num_shader_engines":
                    case "num_shader_arrays":
                    case "num_simds":
                    case "max_waves":
                    case "su_clocks_prim":
                    case "num_prim_pipes":
                    case "ts_freq":
                    case "num_cus":
                        rpnStack.Push(component);
                        continue;
                }

                // Special handling for [sum, min, max, avg, mul, div]{N}
                if (component.Length >= 3)
                {
                    var prefix3 = component.Substring(0, 3);

                    if ("sum" == prefix3
                        || "sub" == prefix3
                        || "max" == prefix3
                        || "min" == prefix3
                        || "avg" == prefix3)
                    {
                        int popCount = 0;
                        string strCount = component.Substring(3);
                        if (string.IsNullOrEmpty(strCount))
                        {
                            popCount = 2;
                        }
                        else
                        {
                            isNumeric = int.TryParse(strCount, out popCount);
                            if (!isNumeric)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, prefix3 + " operator with invalid component count", errorHandler);
                                retVal = false;
                                break;
                            }

                            if (rpnStack.Count < popCount)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "attempt to " + prefix3 + " more components than exist on stack", errorHandler);
                                retVal = false;
                                break;
                            }
                        }

                        for (int i = 0; i < popCount; ++i)
                        {
                            rpnStack.Pop();
                        }

                        rpnStack.Push("result:" + component);

                        continue;
                    }

                    // Special handling for vector multiply and divide [vecMul, vecDiv, vecSum, vecSub]{N}
                    prefix3 = component.Substring(0, 3);

                    if ("vec" == prefix3)
                    {
                        int popCount = 0;
                        string strCount = component.Substring(6);
                        if (string.IsNullOrEmpty(strCount))
                        {
                            popCount = 2;
                        }
                        else
                        {
                            isNumeric = int.TryParse(strCount, out popCount);
                            if (!isNumeric)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, prefix3 + " operator with invalid component count", errorHandler);
                                retVal = false;
                                break;
                            }

                            if (rpnStack.Count < popCount)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "attempt to " + prefix3 + " more components than exist on stack", errorHandler);
                                retVal = false;
                                break;
                            }
                        }

                        for (int i = 0; i < (2 * popCount); ++i)
                        {
                            rpnStack.Pop();
                        }

                        for (int i = 0; i < popCount; ++i)
                        {
                            rpnStack.Push("result:" + component + i.ToString());
                        }

                        continue;
                    }
                }

                // Special handling for dividesum{N}
                if (component.StartsWith("dividesum"))
                {
                    int popCount = 0;
                    string strCount = component.Substring(9);
                    if (string.IsNullOrEmpty(strCount))
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "dividesum operator missing number of components", errorHandler);
                        retVal = false;
                        break;
                    }

                    isNumeric = int.TryParse(strCount, out popCount);
                    if (!isNumeric)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "dividesum operator with invalid component count", errorHandler);
                        retVal = false;
                        break;
                    }

                    if (rpnStack.Count < popCount)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "attempt to dividesum more components than exist on stack", errorHandler);
                        retVal = false;
                        break;
                    }

                    for (int i = 0; i < popCount; ++i)
                    {
                        rpnStack.Pop();
                    }
                    rpnStack.Push("result:" + component);
                    continue;
                }

                // scalarSub[n], scalarMul[n] scalarDiv[n]
                if (component.StartsWith("scalarmul")
                    || component.StartsWith("scalardiv")
                    || component.StartsWith("scalarsub"))
                {
                    int popCount = 0;
                    string strCount = component.Substring(9);
                    if (string.IsNullOrEmpty(strCount))
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "scalar operator missing number of components", errorHandler);
                        retVal = false;
                        break;
                    }

                    isNumeric = int.TryParse(strCount, out popCount);
                    if (!isNumeric)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "scalar operator with invalid component count", errorHandler);
                        retVal = false;
                        break;
                    }

                    popCount += 1;

                    if (rpnStack.Count < popCount)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "not enough components on the stack for the specified scalar operator", errorHandler);
                        retVal = false;
                        break;
                    }

                    for (int i = 0; i < popCount; ++i)
                    {
                        rpnStack.Pop();
                    }

                    for (int i = 0; i < (popCount - 1); ++i)
                    {
                        rpnStack.Push("result:" + component + i.ToString());
                    }
                    continue;
                }

                // Unknown component - error
                OutputCounterError(counter.Name, component, componentIndex, "unknown formula component", errorHandler);
                return false;
            }

            // Validate stack contains a single result
            if (rpnStack.Count != 1)
            {
                errorHandler(counter.Name + " stack incorrectly contains " + rpnStack.Count.ToString() + " entries instead of a single result");
                retVal = false;
            }

            // Validate all hardware counters were referenced
            int counterIndex = 0;

            foreach (var hardwareCounter in counter.GetCounters())
            {
                if (hardwareCounter.Referenced == false)
                {
                    if (hardwareCounter.Name.StartsWith("SPI") && (hardwareCounter.Name.Contains("PERF_PS_CTL_BUSY")
                        || hardwareCounter.Name.Contains("PERF_PS_BUSY")))
                    {
                        infoHandler("Warning:" + counter.Name + " unreferenced block instance counter " + hardwareCounter.Name + " at index "
                            + counterIndex + ". This is required for some counter definitions.");
                    }
                    else
                    {
                        errorHandler(counter.Name + " unreferenced block instance counter " + hardwareCounter.Name + " at index " + counterIndex);
                        retVal = false;
                    }
                }

                ++counterIndex;
            }

            return retVal;
        }

        /// <summary>
        /// Validates the formula and referenced counters
        /// </summary>
        /// <param name="publicCounterList">List of public counter to validate</param>
        /// <returns>True if the formula and referenced counters are correct, otherwise false.</returns>
        private bool ValidateFormulaAndReferencedCounters(ref List<DerivedCounterDef> counters, Func<string, bool> infoHandler, Func<string, bool> errorHandler)
        {
            bool retVal = true;

            foreach (DerivedCounterDef counter in counters)
            {
                retVal &= ValidateFormulaAndReferencedCounter(counter, infoHandler, errorHandler);
            }

            return retVal;
        }

        /// <summary>
        /// Generates output file of GPU counter data by API and ASIC for use in documentation, etc.
        /// </summary>
        /// <param name="outputCsv">True to output the counter name and description only.</param>
        /// <param name="derivedCounterList">List of derived counters.</param>
        /// <param name="internalCounterList">List of internal counters.</param>
        /// <param name="outputDir">Output directory.</param>
        /// <param name="api">API being generated.</param>
        /// <param name="generation">GPU generation.</param>
        /// <param name="asic">Optional ASIC name.</param>
        /// <returns>True is files are successfully loaded and generated.</returns>
        private void GenerateDerivedCounterDocFile(
            bool outputCsv,
            ref List<DerivedCounterDef> derivedCounterList,
            ref List<InternalCounterDef> internalCounterList,
            string outputDir,
            string api,
            string generation,
            string asic,
            Func<string, bool> infoHandler,
            Func<string, bool> errorHandler
            )
        {
            // Ignore generating ASIC-specific docs for now, as the public counters are identical for the user.
            bool asicSpecific = !string.IsNullOrEmpty(asic);
            if (asicSpecific)
            {
                return;
            }

            StreamWriter docStream = null;

            string docFilePath;
            docFilePath = outputDir + api + generation + asic + (outputCsv ? ".csv" : ".txt");

            try
            {
                docStream = new StreamWriter(docFilePath);
            }
            catch
            {
                errorHandler("Failed to open file for writing: " + docStream);
                return;
            }

            docStream.WriteLine("API: " + api);
            docStream.WriteLine("GPU: " + generation + asic);
            docStream.WriteLine("Counters: " + derivedCounterList.Count);
            docStream.WriteLine("Date: " + String.Format("{0:d MMM yyyy h:mm tt}", DateTime.Now));
            docStream.WriteLine();

            foreach (var counter in derivedCounterList)
            {
                if (asicSpecific && !DerivedCounterReferencesAsicRegisters(ref internalCounterList, counter))
                {
                    continue;
                }

                string sampleType = "";
                if (counter.IsDiscreteCounter && !counter.IsSpmCounter)
                {
                    sampleType = "Discrete";
                }
                else if (!counter.IsDiscreteCounter && counter.IsSpmCounter)
                {
                    sampleType = "Streaming";
                }
                else
                {
                    sampleType = "Discrete + Streaming";
                }

                if (outputCsv)
                {
                    string desc = counter.Desc.Replace(',', ' ');
                    docStream.WriteLine(counter.Name + "," + sampleType + "," + counter.Usage + "," + desc);
                }
                else
                {
                    docStream.WriteLine(counter.Name);
                    docStream.WriteLine(sampleType);
                    docStream.WriteLine(counter.Usage);
                    docStream.WriteLine(counter.Desc);
                    docStream.WriteLine(counter.CompReadable);
                    docStream.WriteLine();
                }
            }

            docStream.Close();
            infoHandler("Counter Doc file written: " + docFilePath);
        }

        /// <summary>
        /// Adds information to the counter info structure that will be used to generate counter documentation.
        /// </summary>
        /// <param name="derivedCounterList">List of public counters.</param>
        /// <param name="generation">GPU generation.</param>
        /// <param name="docInfoMap">the counter info structure in which to add information</param>
        private void AddInfoToRSTDocInfo(
            ref List<DerivedCounterDef> derivedCounterList,
            string generation,
            Dictionary<GfxGeneration, Dictionary<CounterGroup, Dictionary<string, DerivedCounterDef>>> docInfoMap,
            Func<string, bool> infoHandler
            )
        {
            GfxGeneration gfxGen = GfxGeneration.Unknown;

            if ("Gfx12" == generation)
            {
                gfxGen = GfxGeneration.Gfx12;
            }
            else if ("Gfx11" == generation)
            {
                gfxGen = GfxGeneration.Gfx11;
            }
            else if ("Gfx103" == generation)
            {
                gfxGen = GfxGeneration.Gfx103;
            }
            else if ("Gfx10" == generation)
            {
                gfxGen = GfxGeneration.Gfx10;
            }
            else
            {
                throw new Exception("Unknown hardware generation");
            }

            foreach (var counter in derivedCounterList)
            {
                if (!docInfoMap.ContainsKey(gfxGen))
                {
                    docInfoMap.Add(gfxGen, new Dictionary<CounterGroup, Dictionary<string, DerivedCounterDef>>());
                }

                if (!docInfoMap[gfxGen].ContainsKey(counter.Group))
                {
                    docInfoMap[gfxGen].Add(counter.Group, new Dictionary<string, DerivedCounterDef>());
                }

                if (!docInfoMap[gfxGen][counter.Group].ContainsKey(counter.Name))
                {
                    docInfoMap[gfxGen][counter.Group].Add(counter.Name, new DerivedCounterDef());
                }

                docInfoMap[gfxGen][counter.Group][counter.Name] = counter;
            }
        }

        /// <summary>
        /// Loads internal counters and generates output files.
        /// </summary>
        /// <param name="counterNamesFile">File that contains counter names.</param>
        /// <param name="derivedCounterDefFile">Derived counter definition files.</param>
        /// <param name="outputDir">Output directory.</param>
        /// <param name="counterListOutputDirectory">Counter list output directory.</param>
        /// <param name="testOutputDirectory">Test file output directory.</param>
        /// <param name="api">API being generated.</param>
        /// <param name="generation">Gfx generation.</param>
        /// <param name="asic">Optional ASIC name.</param>
        /// <param name="infoHandler">Called in response to an informational message</param>
        /// <param name="errorHandler">Called in response to a error condition</param>
        /// <returns>True is files are successfully loaded and generated.</returns>
        public bool LoadFilesAndGenerateOutput(
            string rootFilename,
            string counterNamesFile,
            string derivedCounterDefFile,
            string outputDir,
            string counterListOutputDirectory,
            string testOutputDirectory,
            string api,
            string generation,
            string asic,
            Func<string, bool> infoHandler,
            Func<string, bool> errorHandler
            )
        {
            string sectionLabel = api + generation;

            // Load the internal counters
            List<InternalCounterDef> internalCounterList = new List<InternalCounterDef>();
            bool readOk = LoadInternalCounters(counterNamesFile, ref internalCounterList, asic, infoHandler, errorHandler);
            if (!readOk)
            {
                errorHandler("Unable to read counter name file (" + counterNamesFile + ").\n");
                return false;
            }

            infoHandler("Read " + internalCounterList.Count + " internal counters from " + counterNamesFile + ".");

            // Save global internal counters, or update ASIC specific internal counter list for completeness in order generate public counters
            if (string.IsNullOrEmpty(asic))
            {
                globalInternalCounterList = internalCounterList;
            }
            else
            {
                Debug.Assert(globalInternalCounterList.Count > 0);

                List<InternalCounterDef> thisAsicCounterList = globalInternalCounterList;

                // If the counter doesn't exist, add it.
                // Counter output indices will already match because the ASIC CounterName file is generated
                // to overlay section(s) of the global GPU generation base file.

                List<InternalCounterDef> extraCounterList = new List<InternalCounterDef>();
                foreach (var internalCounter in internalCounterList)
                {
                    int foundIndex = thisAsicCounterList.FindIndex(x => x.name == internalCounter.name);

                    if (-1 != foundIndex)
                    {
                        thisAsicCounterList[foundIndex] = internalCounter;
                    }
                    else
                    {
                        extraCounterList.Add(new InternalCounterDef(internalCounter));
                    }
                }

                if (extraCounterList.Count != 0)
                {
                    // We don't expect that we'll have extras, but if we do, just add them to the end of the list
                    thisAsicCounterList.AddRange(extraCounterList);
                }

                internalCounterList = thisAsicCounterList;

            }

            // load the public counter definitions using the filename in the second param
            List<DerivedCounterDef> publicCounterDerivedList = new List<DerivedCounterDef>();
            readOk = LoadDerivedCounterDefinitions(derivedCounterDefFile, ref publicCounterDerivedList, ref internalCounterList,
                sectionLabel, asic, infoHandler, errorHandler);
            if (!readOk)
            {
                errorHandler("Unable to process public counter file (" + derivedCounterDefFile + ").\n");
                return false;
            }

            if ("dx12" != api.ToLower())
            {
                // Non-DX12 only supports discrete counters. Enforce this.
                // Remove SPM-only counters if they happen to exist.
                publicCounterDerivedList.RemoveAll(x => (x.IsSpmCounter && !x.IsDiscreteCounter));

                // Force the counters to not indicate they are SPM counters. This simplifies a lot of logic later.
                foreach (var counter in publicCounterDerivedList)
                {
                    counter.IsSpmCounter = false;
                }
            }

            if (publicCounterDerivedList.Count == 0)
            {
                infoHandler("0 counters were exposed by the counter definitions file.");
                return false;
            }
            else
            {
                infoHandler("Read " + publicCounterDerivedList.Count + " public counters from " + derivedCounterDefFile + ".");
            }

            if (ValidateFormulaAndReferencedCounters(ref publicCounterDerivedList, infoHandler, errorHandler) == false)
            {
                return false;
            }

            if (GenerateOutputFiles(ref internalCounterList, ref publicCounterDerivedList, rootFilename, api, generation, outputDir,
                    counterListOutputDirectory, asic, infoHandler, errorHandler) == false)
            {
                return false;
            }
            else
            {
                bool genTestOutputFilesStatus = GenerateTestOutputFiles(ref internalCounterList, ref publicCounterDerivedList, rootFilename,
                    testOutputDirectory, api, generation, asic, infoHandler, errorHandler);
                if (false == genTestOutputFilesStatus)
                {
                    errorHandler("Failed to generate output test files for " + sectionLabel);
                }
            }

            if (Form1.GenerateCounterDocs)
            {
                GenerateDerivedCounterDocFile(true, ref publicCounterDerivedList, ref internalCounterList, outputDir, api, generation, asic, infoHandler, errorHandler);
                GenerateDerivedCounterDocFile(false, ref publicCounterDerivedList, ref internalCounterList, outputDir, api, generation, asic, infoHandler, errorHandler);
            }

            {
                AddInfoToRSTDocInfo(ref publicCounterDerivedList, generation, docInfoMapGraphicsByGeneration, infoHandler);
            }

            return true;
        }

        private bool CreateReadableEquation(ref DerivedCounterDef counterDef, string inputLine)
        {
            string[] equations = inputLine.Split('|');

            counterDef.CompReadable = string.Empty;

            foreach (string eqn in equations)
            {
                string[] compParts = eqn.Split(',');

                string compReadable = string.Empty;

                foreach (string part in compParts)
                {
                    if (compReadable.Length > 0 && compReadable.EndsWith(",") == false)
                    {
                        compReadable += ",";
                    }

                    if (part.Contains(".."))
                    {
                        // This could cross over multiple counters
                        // - expand the range
                        // - query for each index, but prevent duplicate base name adds
                        List<ReferencedRegister> refRegisters = new List<ReferencedRegister>();

                        List<int> values = ExpandEllipses(part);
                        foreach (int value in values)
                        {
                            int startIndex, endIndex;
                            string register = counterDef.GetRegisterCounterBaseNameForIndex(value, out startIndex, out endIndex);

                            bool found = false;

                            foreach (var refReg in refRegisters)
                            {
                                if (refReg.registerName == register)
                                {
                                    if (value > refReg.refEndIndex)
                                    {
                                        refReg.refEndIndex = value;
                                        found = true;
                                        break;
                                    }
                                }
                            }

                            // add new register reference
                            if (!found)
                            {
                                ReferencedRegister refReg = new ReferencedRegister();
                                refReg.registerName = register;
                                refReg.refStartIndex = value;
                                refReg.refEndIndex = value;
                                refReg.startIndex = startIndex;
                                refReg.endIndex = endIndex;
                                refRegisters.Add(refReg);
                            }
                        }

                        foreach (var refReg in refRegisters)
                        {
                            if (compReadable.Length > 0 && compReadable.EndsWith(",") == false)
                            {
                                compReadable += ",";
                            }

                            compReadable += refReg.registerName;
                            if (refReg.startIndex != refReg.endIndex)
                            {
                                if (refReg.refStartIndex != refReg.refEndIndex)
                                {
                                    compReadable +=
                                        "[" +
                                        (refReg.refStartIndex - refReg.startIndex).ToString() +
                                        ".." +
                                        (refReg.refEndIndex - refReg.startIndex).ToString() +
                                        "]";
                                }
                                else
                                {
                                    compReadable += "[" + (refReg.refStartIndex - refReg.startIndex) + "]";
                                }
                            }
                        }
                    }
                    else
                    {
                        int result = 0;
                        bool ret = int.TryParse(part, out result);
                        if (ret)
                        {
                            int startIndex, endIndex;
                            string register = counterDef.GetRegisterCounterBaseNameForIndex(result, out startIndex, out endIndex);
                            compReadable += register;

                            if (startIndex != endIndex)
                            {
                                compReadable += "[" + (result - startIndex) + "]";
                            }
                        }
                        else
                        {
                            compReadable += part;
                        }
                    }
                }

                if (!string.IsNullOrEmpty(counterDef.CompReadable))
                {
                    counterDef.CompReadable += ";";
                }

                counterDef.CompReadable += compReadable;
            }

            return true;
        }

        /// <summary>
        /// Load a list of counter name from the specified file (expecting one name per line, order implies counters index)
        /// Format is: number , name , type
        /// </summary>
        /// <param name="file">File of internal counters to load.</param>
        /// <param name="internalCounterList">Returned list of internal counter definitions.</param>
        /// <param name="asic">Optional ASIC name.</param>
        /// <param name="infoHandler">Called in response to an informational message</param>
        /// <param name="errorHandler">Called in response to a error condition</param>
        /// <returns>True if internal counters are successfully loaded.</returns>
        public bool LoadInternalCounters(string file,
            ref List<InternalCounterDef> internalCounterList,
            string asic,
            Func<string, bool> infoHandler,
            Func<string, bool> errorHandler
            )
        {
            bool isAsicSpecific = !string.IsNullOrEmpty(asic);

            string[] internalDerivedCounterDefs;
            try
            {
                internalDerivedCounterDefs = File.ReadAllLines(file);
            }
            catch (Exception e)
            {
                errorHandler("Could not read contents of " + file + ": " + e.Message);
                return false;
            }

            HashSet<int> usedCounterNumbers = new HashSet<int>();

            int lastCounterNumber = -1;
            foreach (string s in internalDerivedCounterDefs)
            {
                if (s.Length == 0)
                {
                    continue;
                }

                if (s.Contains("="))
                {
                    errorHandler("Hardware counter names may not contain = symbols. Change the counter name or change PCC public counter parsing to support = in names.");
                    return false;
                }

                if (s.Trim().StartsWith("#"))
                {
                    // Lines that start with '#' are comments, skip it.
                    continue;
                }

                string[] counterText = s.Split(',');
                if (counterText.Length != 3)
                {
                    errorHandler("Problem reading hardware counter definition. Format must be: 'number , name , type'. Line='" + s + "'");
                    return false;
                }

                int counterNumber = -1;
                System.Int32.TryParse(counterText[0], out counterNumber);
                if (usedCounterNumbers.Contains(counterNumber))
                {
                    errorHandler("Duplicate counter numbers detected. Line='" + s + "'");
                    return false;
                }
                else if (counterNumber <= lastCounterNumber)
                {
                    errorHandler("Internal counter numbers defined out of sequence. Line='" + s + "'");
                    return false;
                }

                usedCounterNumbers.Add(counterNumber);
                lastCounterNumber = counterNumber;

                internalCounterList.Add(new InternalCounterDef(counterNumber, counterText[1].Trim(), counterText[2].Trim(), isAsicSpecific));
            }

            return true;
        }

        /// <summary>
        /// Get the index of a string in a list (case insensitive)
        /// </summary>
        /// <param name="counterName">Name of the counter.</param>
        /// <param name="internalCounterList">Internal counter list.</param>
        /// <param name="index">Returned index of the counter.</param>
        /// <returns>True if the counter was found, otherwise false.</returns>
        public bool GetCounterIndex(string counterName,
            ref List<InternalCounterDef> internalCounterList,
            out int index)
        {
            foreach (InternalCounterDef c in internalCounterList)
            {
                if (c.name.Equals(counterName, StringComparison.OrdinalIgnoreCase))
                {
                    index = c.index;
                    return true;
                }
            }

            index = -1;
            return false;
        }

        /// <summary>
        /// Definition of a referenced register used during the building of the readable comp formula.
        /// </summary>
        class ReferencedRegister
        {
            public string registerName = string.Empty;
            public int refStartIndex = -1;
            public int refEndIndex = -1;
            public int startIndex = -1;
            public int endIndex = -1;
        }

        /// <summary>
        /// Given the counter name list, create a list of CounterDefinitions using definitions in the specified file.
        /// </summary>
        /// <param name="file">Name of the file to load.</param>
        /// <param name="counterDefList">Returned counter definition list, expected to be empty on first call.</param>
        /// <param name="internalCounterList">Internal counter list.</param>
        /// <param name="activeSectionLabel">Current section label.</param>
        /// <param name="asic">Optional ASIC name.</param>
        /// <param name="strError">Optional error return.</param>
        /// <returns>True if the exposed counter definitions are successfully loaded.</returns>
        public bool LoadDerivedCounterDefinitions(string file,
            ref List<DerivedCounterDef> counterDefList,
            ref List<InternalCounterDef> internalCounterList,
            string activeSectionLabel,
            string asic,
            Func<string, bool> infoHandler,
            Func<string, bool> errorHandler
            )
        {
            // Some files may not exist for certain combinations of APIs and architectures
            if (!File.Exists(file))
            {
                infoHandler("Info: Unable to find file " + file);
                return true;
            }

            infoHandler("Reading: " + file);

            string[] derivedCounterDefs;
            try
            {
                derivedCounterDefs = File.ReadAllLines(file);
            }
            catch (Exception e)
            {
                errorHandler(e.Message);
                return false;
            }

            bool discardApiSections = true;
            uint numInvalidCounterNames = 0;
            uint lineNumber = 0;

            DerivedCounterDef counterDef = null;

            List<string> currentApis;

            foreach (string line in derivedCounterDefs)
            {
                ++lineNumber;

                string s = line.Trim();

                // Trim any comments, but not from a counter description
                if (!s.StartsWith("desc="))
                {
                    int index = s.IndexOf('#');
                    if (index > -1)
                    {
                        s = s.Substring(0, index);
                        s = s.Trim();
                    }
                }

                if (string.IsNullOrEmpty(s))
                {
                    continue;
                }

                if (s.StartsWith("#include"))
                {
                    string pathToFile = Path.GetDirectoryName(file);
                    string includeFile = s.Substring(8);
                    includeFile = includeFile.Trim();
                    includeFile = pathToFile + "\\" + includeFile;
                    bool loadedInclude = LoadDerivedCounterDefinitions(includeFile, ref counterDefList,
                        ref internalCounterList, activeSectionLabel, asic, infoHandler, errorHandler);
                    if (!loadedInclude)
                    {
                        errorHandler("Loading of include file " + includeFile + " failed.\n");
                        return false;
                    }

                    continue;
                }

                string[] lineSplit = s.Split('=');
                lineSplit[0] = lineSplit[0].Trim();

                if (lineSplit.Length > 1)
                {
                    lineSplit[1] = lineSplit[1].Trim();

                    if (lineSplit[0].Equals("name", StringComparison.OrdinalIgnoreCase))
                    {
                        // if we were trying to define a counter, but never did a comp for it, output a warning since the counter will not be generated
                        if (counterDef != null && !counterDef.ValidUsage())
                        {
                            infoHandler("Warning: no comp found for " + activeSectionLabel +
                                   ", will not expose counter for: " + counterDef.Name);
                        }

                        if (lineSplit[1].Length == 0)
                        {
                            errorHandler("Name definition empty. Line='" + s + "'");
                            return false;
                        }

                        counterDef = new DerivedCounterDef { Name = lineSplit[1] };

                        // Make sure counter name isn't already in the list.
                        bool counterAlreadyDefined = false;
                        foreach (DerivedCounterDef def in counterDefList)
                        {
                            if (def.Name == counterDef.Name)
                            {
                                counterAlreadyDefined = true;
                                break;
                            }
                        }

                        if (counterAlreadyDefined)
                        {
                            errorHandler("Duplicate name found. Line'" + s + "'");
                            return false;
                        }

                        currentApis = new List<string>();

                        discardApiSections = true;
                    }
                    else if (lineSplit[0].Equals("group", StringComparison.OrdinalIgnoreCase))
                    {
                        if (!counterDef.ValidName())
                        {
                            errorHandler("name= should appear before group=. Line='" + s + "'");
                            return false;
                        }

                        counterDef.Group = lineSplit[1];
                    }
                    else if (lineSplit[0].Equals("desc", StringComparison.OrdinalIgnoreCase))
                    {
                        if (!counterDef.ValidName())
                        {
                            errorHandler("name= should appear before desc=. Line='" + s + "'");
                            return false;
                        }

                        counterDef.Desc = lineSplit[1];

                        if (counterDef.Desc.StartsWith("#"))
                        {
                            int secondHashIndex = counterDef.Desc.IndexOf('#', 1);
                            counterDef.Group = counterDef.Desc.Substring(1, secondHashIndex - 1);
                            counterDef.Desc = counterDef.Desc.Substring(secondHashIndex + 1);
                        }
                    }
                    else if (lineSplit[0].Equals("type", StringComparison.OrdinalIgnoreCase))
                    {
                        if (!counterDef.ValidName())
                        {
                            errorHandler("name= should appear before type=. Line='" + s + "'");
                            return false;
                        }

                        // map input type to a GPA type
                        if (lineSplit[1].Equals("gpa_float64", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Type = "kGpaDataTypeFloat64";
                        }
                        else if (lineSplit[1].Equals("gpa_uint64", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Type = "kGpaDataTypeUint64";
                        }
                        else
                        {
                            errorHandler("Type not recognized. Line='" + s + "'");
                            return false;
                        }
                    }
                    else if (lineSplit[0].Equals("spm", StringComparison.OrdinalIgnoreCase))
                    {
                        uint value = Convert.ToUInt32(lineSplit[1]);

                        counterDef.IsSpmCounter = (0 != value);
                    }
                    else if (lineSplit[0].Equals("discrete", StringComparison.OrdinalIgnoreCase))
                    {
                        uint value = Convert.ToUInt32(lineSplit[1]);

                        counterDef.IsDiscreteCounter = (0 != value);
                    }
                    else if (lineSplit[0].Equals("usage", StringComparison.OrdinalIgnoreCase))
                    {
                        if (!counterDef.ValidName())
                        {
                            errorHandler("name= should appear before usage=. Line='" + s + "'");
                            return false;
                        }

                        // map input type to a GPA type
                        if (lineSplit[1].Equals("ratio", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "kGpaUsageTypeRatio";
                        }
                        else if (lineSplit[1].Equals("percentage", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "kGpaUsageTypePercentage";
                        }
                        else if (lineSplit[1].Equals("cycles", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "kGpaUsageTypeCycles";
                        }
                        else if (lineSplit[1].Equals("nanoseconds", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "kGpaUsageTypeNanoseconds";
                        }
                        else if (lineSplit[1].Equals("bytes", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "kGpaUsageTypeBytes";
                        }
                        else if (lineSplit[1].Equals("items", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "kGpaUsageTypeItems";
                        }
                        else if (lineSplit[1].Equals("kilobytes", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "kGpaUsageTypeKilobytes";
                        }
                        else
                        {
                            errorHandler("Usage not recognized. Line='" + s + "'");
                            return false;
                        }

                    }
                    else if (lineSplit[0].Equals("eqn", StringComparison.OrdinalIgnoreCase))
                    {
                        if (discardApiSections)
                        {
                            continue;
                        }

                        if (counterDef.ValidEquation())
                        {
                            // already done the comp for this counter, so skip this one
                            errorHandler("Duplicate equation. Line='" + s + "'");
                            return false;
                        }

                        if (!counterDef.ValidName())
                        {
                            errorHandler("comp= encountered before name=. Ensure name and optional description appear before comp=. Line='" + s + "'");
                            return false;
                        }

                        if (counterDef.GetCounterCount() == 0)
                        {
                            errorHandler("Block instance events must be defined before comp encountered. Line='" + s + "'");
                            return false;
                        }

                        string equation = lineSplit[1];

                        // build a readable version of the comp for readable debugging, validation, output
                        if (!CreateReadableEquation(ref counterDef, lineSplit[1]))
                        {
                            errorHandler("Unable to create readable equation. Line='" + s + "'");
                            return false;
                        }

                        // if the computation contains a range, find it, then expand the values into a string and rewrite the computation.
                        if (equation.Contains(".."))
                        {
                            string[] compParts = equation.Split(',');

                            // clear the computation so that we can rebuild it
                            equation = string.Empty;

                            foreach (string part in compParts)
                            {
                                if (equation.Length > 0 && equation.EndsWith(",") == false)
                                {
                                    equation += ",";
                                }

                                if (part.Contains(".."))
                                {
                                    List<int> values = ExpandEllipses(part);
                                    foreach (int value in values)
                                    {
                                        equation += value + ",";
                                    }
                                }
                                else
                                {
                                    equation += part;
                                }
                            }
                        }

                        // translate counter name references to indices
                        {
                            counterDef.Comp = string.Empty;

                            string[] equations = equation.Split('|');
                            foreach (string eqn in equations)
                            {
                                string[] compParts = eqn.Split(',');

                                string newEqn = string.Empty;

                                foreach (string part in compParts)
                                {
                                    if (!string.IsNullOrEmpty(newEqn) && newEqn.EndsWith(",") == false)
                                    {
                                        newEqn += ",";
                                    }

                                    // does it refer to all instances of a counter?
                                    if (part.Length > 1 && part.Contains("*"))
                                    {
                                        List<int> allIndices = counterDef.GetAllRegisterCounterIndices(part);

                                        foreach (int counterIndex in allIndices)
                                        {
                                            if (!string.IsNullOrEmpty(newEqn) && newEqn.EndsWith(",") == false)
                                            {
                                                newEqn += ",";
                                            }

                                            newEqn += counterIndex.ToString();
                                        }
                                    }
                                    else if (part.Contains("["))
                                    {
                                        // Virtualized index, e.g.: for timing
                                        int index = part.IndexOf('[');
                                        string reg = part.Substring(0, index);
                                        string subscript = part.Substring(index);

                                        index = counterDef.GetRegisterCounterIndex(reg);
                                        if (index >= 0)
                                        {
                                            newEqn += index.ToString();
                                        }
                                        else
                                        {
                                            // normal component that is directly output
                                            newEqn += part;
                                        }
                                        newEqn += subscript;
                                    }
                                    else
                                    {
                                        // is it a singleton counter reference?
                                        int index = counterDef.GetRegisterCounterIndex(part);
                                        if (index >= 0)
                                        {
                                            newEqn += index.ToString();
                                        }
                                        else
                                        {
                                            // normal component that is directly output
                                            newEqn += part;
                                        }
                                    }
                                }

                                if (!string.IsNullOrEmpty(counterDef.Comp))
                                {
                                    counterDef.Comp += "|";
                                }

                                counterDef.Comp += newEqn;
                            }
                        }

                        // With the equation parsed, the derived counter is complete
                        counterDefList.Add(counterDef);

                        discardApiSections = true;
                        counterDef = null;
                    }
                }
                else
                {
                    // CounterDef is set to null at the end of the section that's of interest.
                    // Therefore, this is now a subsequent section that we don't care about.
                    if (counterDef == null)
                    {
                        continue;
                    }

                    // must be an internal counter name
                    if (!counterDef.ValidName())
                    {
                        errorHandler("Encountered API section " + s + " before derived counter name. Check order of definitions.");
                        return false;
                    }

                    // determine if we are inside a matching section
                    if (lineSplit[0][0] == '[')
                    {
                        if (discardApiSections)
                        {
                            // looking for specific section label, check for match
                            if (string.Equals(lineSplit[0], "[" + activeSectionLabel + "]",
                                StringComparison.OrdinalIgnoreCase))
                            {
                                discardApiSections = false;
                            }
                        }
                        else
                        {
                            // Current section runs until equation is parsed
                            if (counterDef.ValidEquation())
                            {
                                discardApiSections = true;
                            }
                        }

                        continue;
                    }

                    if (discardApiSections)
                    {
                        continue;
                    }

                    // add the current internal counter to the current public counter definition
                    List<string> curLineCounterNames = new List<string>();
                    if (lineSplit[0].Contains("*") && lineSplit[0].Contains("[") && lineSplit[0].EndsWith("]"))
                    {
                        // this line contains multiple counter names
                        // example format: TA*_TA_PERF_SEL_BUSY[0,1,2,3,4,5,6,7]
                        // example format: TA*_TA_PERF_SEL_BUSY[0..7]
                        // example format: TA*_TA_PERF_SEL_BUSY[0,1..5,6,7]
                        // which means substitute each of the values in [..] for the * and add that counter
                        int startRange = lineSplit[0].IndexOf('[');
                        int endRange = lineSplit[0].IndexOf(']');
                        string counterNameBase = lineSplit[0].Substring(0, startRange);

                        // add one to the start range so that we don't include the brackets
                        string rangeContents = lineSplit[0].Substring(startRange + 1, endRange - startRange - 1);

                        int startIndex = int.MaxValue;
                        int endIndex = int.MinValue;

                        // iterate through each value and add the corresponding counter
                        string[] rangeValues = rangeContents.Split(',');
                        foreach (string valueString in rangeValues)
                        {
                            List<int> values = ExpandEllipses(valueString);

                            foreach (int value in values)
                            {
                                if (value < startIndex)
                                {
                                    startIndex = value;
                                }

                                if (value > endIndex)
                                {
                                    endIndex = value;
                                }

                                string counterName = counterNameBase.Replace("*", value.ToString());
                                curLineCounterNames.Add(counterName);
                                counterDef.AddRegisterCounter(counterName);
                            }
                        }

                        counterDef.AddRegisterCounterBaseNameRange(counterNameBase, startIndex, endIndex);
                    }
                    else
                    {
                        curLineCounterNames.Add(lineSplit[0]);
                        counterDef.AddRegisterCounter(lineSplit[0]);

                        counterDef.AddRegisterCounterBaseNameRange(lineSplit[0], 0, 0);
                    }

                    // now add each of the internal counters on this line to the list for the current public counter.
                    foreach (string counterName in curLineCounterNames)
                    {
                        int index;

                        if (GetCounterIndex(counterName, ref internalCounterList, out index))
                        {
                            if (counterDef.CounterDefined(index))
                            {
                                errorHandler("Counter named '" + counterDef.Name + "' has a duplicate counter definition '" + s + "'.");
                                return false;
                            }

                            counterDef.AddCounter(counterName, index);
                        }
                        else
                        {
                            errorHandler("Counter named '" + counterDef.Name + "' uses an unrecognized hardware counter '" + counterName + "'.");
                            counterDef.AddCounter(s, index);
                            numInvalidCounterNames++;
                        }
                    }
                }
            }

            // if we were trying to define a counter, but never did a comp for it, output a warning since the counter will not be generated
            if (counterDef != null && !counterDef.ValidEquation())
            {
                infoHandler("Warning: incomplete counter " + activeSectionLabel + ", will not expose counter for: " + counterDef.Name);
            }

            if (numInvalidCounterNames > 0 && IgnoreInvalidCounters() == false)
            {
                errorHandler("Encountered " + numInvalidCounterNames + " invalid counter names.");
                return false;
            }

            return true;
        }

        /// <summary>
        /// Expands a series of numbers separated by an ellipses.
        /// Example: "0..7" will expand to a list containing the numbers 0,1,2,3,4,5,6,7
        /// </summary>
        /// <param name="input">the ellipsed string to expand</param>
        /// <returns>A list of numbers</returns>
        private List<int> ExpandEllipses(string input)
        {
            List<int> values = new List<int>();
            if (input.Contains(".."))
            {
                // split on a decimal, we expect the 2nd result to be an empty value between the two ".."
                string[] valueParts = input.Split('.');
                System.Diagnostics.Debug.Assert(3 <= valueParts.Length);
                int first = 0;
                int second = 0;
                if (int.TryParse(valueParts[0], out first) &&
                    int.TryParse(valueParts[2], out second))
                {
                    System.Diagnostics.Debug.Assert(valueParts[1].Length == 0);
                    System.Diagnostics.Debug.Assert(first < second);
                    for (int i = first; i <= second; i++)
                    {
                        values.Add(i);
                    }
                }
            }
            else
            {
                int value = 0;
                if (int.TryParse(input, out value))
                {
                    values.Add(value);
                }
            }

            return values;
        }

        public bool DerivedCounterReferencesAsicRegisters(ref List<InternalCounterDef> internalCounterList, DerivedCounterDef c)
        {
            foreach (DerivedCounterDef.HardwareCounterDef counter in c.GetCounters())
            {
                if (internalCounterList.Exists(x => x.name == counter.Name && x.isAsicSpecific == true))
                {
                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// Generates public counter definition files.
        /// </summary>
        /// <param name="internalCounterList">List of internal counters.</param>
        /// <param name="counterDefList">List of public counter definitions.</param>
        /// <param name="api">API.</param>
        /// <param name="generation">GPU generation.</param>
        /// <param name="outputDir">Output directory.</param>
        /// <param name="counterListOutputDirectory">Counter list output directory.</param>
        /// <param name="asic">Optional ASIC identifier.</param>
        /// <returns>True if the files could be generated; false on error.</returns>
        public bool GenerateOutputFiles(
            ref List<InternalCounterDef> internalCounterList,
            ref List<DerivedCounterDef> counterDefList,
            string rootFilename,
            string api,
            string generation,
            string outputDir,
            string counterListOutputDirectory,
            string asic,
            Func<string, bool> infoHandler,
            Func<string, bool> errorHandler
            )
        {
            if (string.IsNullOrEmpty(counterListOutputDirectory))
            {
                return true;
            }

            bool asicSpecific = !string.IsNullOrEmpty(asic);
            string asic_prefix_str = asicSpecific ? "_" + asic.ToLower() : "";

            string activeSectionLabel = api + "_" + generation;
            string activeSectionLabelInFunction = api.ToCamelCase() + generation.ToCamelCase();

            if (outputDir.Length > 0 && !outputDir.EndsWith("\\"))
            {
                outputDir = outputDir + "\\";
            }

            if (counterListOutputDirectory.Length > 0 && !counterListOutputDirectory.EndsWith("\\"))
            {
                counterListOutputDirectory = counterListOutputDirectory + "\\";
            }

            Directory.CreateDirectory(counterListOutputDirectory);

            string filename = string.Format("{0}{1}{2}{3}{4}.h", outputDir, rootFilename, Gpa.counterDefinitionsStr, api.ToLower() + "_" + generation.ToLower(), asic_prefix_str);

            // Write header file
            infoHandler("Writing header to " + filename);
            StreamWriter includeFile = null;
            try
            {
                includeFile = new StreamWriter(filename);
            }
            catch
            {
                errorHandler("Failed to open file for writing: " + filename);
                return false;
            }

            string baseDirForHeaderGuard = "GPA";

            includeFile.WriteLine("//==============================================================================");
            includeFile.WriteLine("// Copyright (c) 2010-{0} Advanced Micro Devices, Inc. All rights reserved.", DateTime.Today.Year);
            includeFile.WriteLine("/// @author AMD Developer Tools Team");
            includeFile.WriteLine("/// @file");
            includeFile.WriteLine("/// @brief {0} Counter Definitions for {1} {2}{3}.", derivedCounterFileInput.compiler_type_str, api.ToUpper(), generation.ToUpper(), asic_prefix_str.ToUpper());
            includeFile.WriteLine("//==============================================================================");
            includeFile.WriteLine();
            includeFile.WriteLine("#ifndef {0}_AUTO_GEN_COUNTER_GEN_{1}COUNTER_DEFINITIONS_{2}_{3}{4}_H_", baseDirForHeaderGuard, rootFilename.ToUpper(), api.ToUpper(), generation.ToUpper(), asic_prefix_str.ToUpper());
            includeFile.WriteLine("#define {0}_AUTO_GEN_COUNTER_GEN_{1}COUNTER_DEFINITIONS_{2}_{3}{4}_H_", baseDirForHeaderGuard, rootFilename.ToUpper(), api.ToUpper(), generation.ToUpper(), asic_prefix_str.ToUpper());
            includeFile.WriteLine();

            includeFile.WriteLine("// clang-format off");

            includeFile.WriteLine("//*** Note, this is an auto-generated file. Do not edit. Execute {0}CounterCompiler to rebuild.", derivedCounterFileInput.compiler_type_str);
            includeFile.WriteLine();
            includeFile.WriteLine("#include \"gpa_derived_counter.h\"");
            includeFile.WriteLine();

            if (!asicSpecific)
            {
                includeFile.WriteLine("/// @brief Defines the {0} derived counters for {1} {2}.", derivedCounterFileInput.compiler_type_str, api.ToUpper(), asic_prefix_str.ToUpper());
                includeFile.WriteLine("///");
                includeFile.WriteLine("/// @param [in] c derived counters instance");
                includeFile.WriteLine("void AutoDefine{0}DerivedCounters{1}(GpaDerivedCounters& c);", derivedCounterFileInput.compiler_type_str, activeSectionLabelInFunction);
            }
            else
            {
                includeFile.WriteLine("namespace {0}_{1}", activeSectionLabel.ToLower(), asic.ToLower());
                includeFile.WriteLine("{");
                includeFile.WriteLine("    /// @brief Updates default GPU generation {0} derived counters with ASIC specific versions if available.", derivedCounterFileInput.compiler_type_str);
                includeFile.WriteLine("    ///");
                includeFile.WriteLine("    /// @param [in] desired_generation Hardware generation currently in use.");
                includeFile.WriteLine("    /// @param [in] asic_type The ASIC type that is currently in use.");
                includeFile.WriteLine("    /// @param [in] c Derived counters instance.");
                includeFile.WriteLine("    ///");
                includeFile.WriteLine("    /// @return True if the ASIC matched one available, and derivedCounters was updated.");
                includeFile.WriteLine("    extern bool Update{0}AsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c);", derivedCounterFileInput.compiler_type_str);
                includeFile.WriteLine();
                includeFile.WriteLine("}}  // namespace {0}_{1}", activeSectionLabel.ToLower(), asic.ToLower());
            }

            includeFile.WriteLine();

            includeFile.WriteLine("// clang-format on");
            includeFile.WriteLine("#endif  // {0}_AUTO_GEN_COUNTER_GEN_{1}COUNTER_DEFINITIONS_{2}_{3}{4}_H_",
                baseDirForHeaderGuard, rootFilename.ToUpper(), api.ToUpper(), generation.ToUpper(),
                asic_prefix_str.ToUpper());
            includeFile.Close();

            string cppFilename = string.Format("{0}{1}{2}{3}{4}.cc", outputDir, rootFilename, Gpa.counterDefinitionsStr, api.ToLower() + "_" + generation.ToLower(), asic_prefix_str.ToLower());

            // Write cpp file
            infoHandler("Writing cpp to " + cppFilename);
            StreamWriter cppFile = null;
            try
            {
                cppFile = new StreamWriter(cppFilename);
            }
            catch
            {
                errorHandler("Failed to open file for writing: " + filename);
                return false;
            }

            cppFile.WriteLine("//==============================================================================");
            cppFile.WriteLine("// Copyright (c) 2010-{0} Advanced Micro Devices, Inc. All rights reserved.",
                DateTime.Today.Year);
            cppFile.WriteLine("/// @author AMD Developer Tools Team");
            cppFile.WriteLine("/// @file");
            cppFile.WriteLine("/// @brief {0} Counter Definitions for {1} {2}{3}.", derivedCounterFileInput.compiler_type_str, api.ToUpper(), generation.ToUpper(), asic_prefix_str.ToUpper());
            cppFile.WriteLine("//==============================================================================");
            cppFile.WriteLine();
            cppFile.WriteLine("#include <array>");
            cppFile.WriteLine("#include \"gpu_perf_api_common/gpa_array_view.hpp\"");

            cppFile.WriteLine("// clang-format off");

            cppFile.WriteLine("#include \"{0}\"", Gpa.gpaCounterHeaderFileStr);
            cppFile.WriteLine("#include \"auto_generated/gpu_perf_api_counter_generator/{0}counter_definitions_{1}_{2}{3}.h\"", rootFilename.ToLower(), api.ToLower(), generation.ToLower(), asic_prefix_str.ToLower());
            cppFile.WriteLine();
            cppFile.WriteLine("// *** Note, this is an auto-generated file. Do not edit. Execute {0}CounterCompiler to rebuild.", derivedCounterFileInput.compiler_type_str);
            cppFile.WriteLine();

            if (!asicSpecific)
            {
                cppFile.WriteLine("void AutoDefine{0}DerivedCounters{1}{2}(GpaDerivedCounters& c)", derivedCounterFileInput.compiler_type_str, activeSectionLabelInFunction, asic);
                cppFile.WriteLine("{");
            }
            else
            {
                cppFile.WriteLine("#include \"auto_generated/gpu_perf_api_counter_generator/{0}{1}{2}.h\"", Gpa.gpaHwCounterFilenamePrefix, generation.ToLower(), asic_prefix_str.ToLower());
                cppFile.WriteLine();
                cppFile.WriteLine("namespace {0}_{1}", activeSectionLabel.ToLower(), asic.ToLower());
                cppFile.WriteLine("{");
                cppFile.WriteLine("bool Update{0}AsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c)", derivedCounterFileInput.compiler_type_str);
                cppFile.WriteLine("{");
                cppFile.WriteLine("    UNREFERENCED_PARAMETER(desired_generation);");
                cppFile.WriteLine("    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers");
                cppFile.WriteLine();
                cppFile.WriteLine("    if (!counter_{0}_{1}::MatchAsic(asic_type))", generation.ToLower(), asic.ToLower());
                cppFile.WriteLine("    {");
                cppFile.WriteLine("        return false;");
                cppFile.WriteLine("    }");
                cppFile.WriteLine();
                cppFile.WriteLine("    counter_{0}_{1}::OverrideBlockInstanceCounters(asic_type);", generation.ToLower(), asic.ToLower());
                cppFile.WriteLine();
            }

            StreamWriter lsw = null;

            if (!string.IsNullOrEmpty(counterListOutputDirectory))
            {
                string listFilename = string.Format("{0}{1}{2}{3}{4}.txt", counterListOutputDirectory, rootFilename, counterNameListFilePrefix, api.ToLower() + "_" + generation.ToLower(), asic_prefix_str.ToLower());

                infoHandler("Writing counter name list to " + listFilename);
                try
                {
                    lsw = new StreamWriter(listFilename);
                }
                catch
                {
                    errorHandler("Failed to open file for writing: " + filename);
                    return false;
                }
            }

            int counter_index = 0;
            foreach (DerivedCounterDef c in counterDefList)
            {
                if (asicSpecific && !DerivedCounterReferencesAsicRegisters(ref internalCounterList, c))
                {
                    continue;
                }

                if (lsw != null)
                {
                    lsw.WriteLine("{0} - {1}", c.Name, c.Desc);
                }

                cppFile.WriteLine("    {{ // Index:{0}", counter_index);
                counter_index++;

                var counters = c.GetCounters();
                cppFile.WriteLine("        static constexpr std::array<GpaUInt32, {0}> kHardwareCounters = {{", counters.Count);
                foreach (DerivedCounterDef.HardwareCounterDef counter in counters)
                {
                    cppFile.WriteLine("                {0},", counter.Id);
                }
                cppFile.WriteLine("        };");

                if (!asicSpecific)
                {
                    cppFile.WriteLine("        c.DefineDerivedCounter(\"{0}\",", c.Name);
                    cppFile.WriteLine("                               \"{0}\",", c.Group);
                    cppFile.WriteLine("                               \"{0}\",", c.Desc);
                    cppFile.WriteLine("                               {0},", c.Type);
                    cppFile.WriteLine("                               {0},", c.Usage);
                    cppFile.WriteLine("                               {0},", c.IsDiscreteCounter ? "true" : "false");
                    cppFile.WriteLine("                               {0},", c.IsSpmCounter ? "true" : "false");
                    cppFile.WriteLine("                               kHardwareCounters,");
                    cppFile.WriteLine("                               \"{0}\",", c.Comp);
                    cppFile.WriteLine("                               \"{0}\");", c.GuidHash.ToString("D"));
                }
                else
                {
                    cppFile.WriteLine("        c.UpdateAsicSpecificDerivedCounter(\"{0}\",", c.Name);
                    cppFile.WriteLine("                                           kHardwareCounters,");
                    cppFile.WriteLine("                                           \"{0}\");", c.Comp);
                }

                cppFile.WriteLine("    }");
            }

            if (!asicSpecific)
            {
                cppFile.WriteLine("}");
                cppFile.WriteLine();
            }
            else
            {
                cppFile.WriteLine("    return true;");
                cppFile.WriteLine("}");
                cppFile.WriteLine();
                cppFile.WriteLine("}}  // namespace {0}_{1}", activeSectionLabel.ToLower(), asic.ToLower());
                cppFile.WriteLine();
            }

            cppFile.WriteLine("// clang-format on");
            cppFile.WriteLine();

            cppFile.Close();
            if (lsw != null)
            {
                lsw.Close();
            }

            return true;
        }

        /// <summary>
        /// Generate the test output file
        /// </summary>
        /// <param name="internalCounterList">List of internal counters</param>
        /// <param name="counterDefList">List of derived counters</param>
        /// <param name="rootFilename">Root filename of counters</param>
        /// <param name="testOutputDirectory">Directory that will contain output test files</param>
        /// <param name="api">API being generated.</param>
        /// <param name="generation">Gfx generation.</param>
        /// <param name="asic">Specific ASIC, or empty string.</param>
        /// <returns>True if files are successfully generated.</returns>
        public bool GenerateTestOutputFiles(
            ref List<InternalCounterDef> internalCounterList,
            ref List<DerivedCounterDef> counterDefList,
            string rootFilename,
            string testOutputDirectory,
            string api,
            string generation,
            string asic,
            Func<string, bool> infoHandler,
            Func<string, bool> errorHandler
            )
        {
            if (string.IsNullOrEmpty(testOutputDirectory))
            {
                return true;
            }

            // Don't generate these for ASICs, just once for the base generation
            if (!string.IsNullOrEmpty(asic))
            {
                return true;
            }

            bool asicSpecific = !string.IsNullOrEmpty(asic);

            if (testOutputDirectory.Length > 0 && !testOutputDirectory.EndsWith("\\"))
            {
                testOutputDirectory = testOutputDirectory + "\\";
            }

            string activeSectionLabel = api + generation;
            string api_generation_file_str = api.ToLower() + "_" + generation.ToLower();

            string derivedCounterFileNamePrefix = rootFilename + Gpa.derivedCounterOutFileName;
            string headerFileName = string.Format("{0}{1}{2}.h", derivedCounterFileNamePrefix, api_generation_file_str.ToLower(), asicSpecific ? "_" + asic.ToLower() : "");
            string headerFilePath = string.Format("{0}{1}", testOutputDirectory, headerFileName);

            string cppFilePath = string.Format("{0}{1}{2}{3}.cc", testOutputDirectory, derivedCounterFileNamePrefix,
                api_generation_file_str.ToLower(), asicSpecific ? "_" + asic.ToLower() : "");
            infoHandler("Writing header to " + cppFilePath);
            StreamWriter cppStream = null;
            try
            {
                cppStream = new StreamWriter(cppFilePath);
            }
            catch
            {
                errorHandler("Failed to open file for writing: " + cppFilePath);
                return false;
            }

            cppStream.WriteLine("//==============================================================================");
            cppStream.WriteLine("// Copyright (c) 2015-{0} Advanced Micro Devices, Inc. All rights reserved.",
                DateTime.Today.Year);
            cppStream.WriteLine("/// @author AMD Developer Tools Team");
            cppStream.WriteLine("/// @file");
            cppStream.WriteLine("/// @brief {0}CounterDefinitions for {1} {2} {3} for testing.", derivedCounterFileInput.compiler_type_str, api.ToUpper(), generation.ToUpper(), asic);
            cppStream.WriteLine("//==============================================================================");
            cppStream.WriteLine();
            cppStream.WriteLine("// clang-format off");
            cppStream.WriteLine("// *** Note, this is an auto-generated file. Do not edit. Execute {0}CounterCompiler to rebuild.", derivedCounterFileInput.compiler_type_str);
            cppStream.WriteLine();
            cppStream.WriteLine("#include \"auto_generated/gpu_perf_api_unit_tests/counters/{0}\"", headerFileName);
            cppStream.WriteLine();

            string derivedCountersConstant = "k" + api.ToCamelCase('_') + generation.ToCamelCase('_') + asic.ToCamelCase('_') + derivedCounterFileInput.compiler_type_str.ToCamelCase('_') + "Counters";
            string derivedCounterCountConstant = "k" + api.ToCamelCase('_') + generation.ToCamelCase('_') + asic.ToCamelCase('_') + derivedCounterFileInput.compiler_type_str.ToCamelCase('_') + "CounterCount";
            cppStream.WriteLine("const GpaCounterDesc {0}[{1}] = {{", derivedCountersConstant, derivedCounterCountConstant);

            infoHandler("Writing header to " + headerFilePath);
            StreamWriter headerStream = null;
            try
            {
                headerStream = new StreamWriter(headerFilePath);
            }
            catch
            {
                errorHandler("Failed to open file for writing: " + headerFilePath);
                return false;
            }

            headerStream.WriteLine("//==============================================================================");
            headerStream.WriteLine("// Copyright (c) 2015-{0} Advanced Micro Devices, Inc. All rights reserved.",
                DateTime.Today.Year);
            headerStream.WriteLine("/// @author AMD Developer Tools Team");
            headerStream.WriteLine("/// @file");
            headerStream.WriteLine("/// @brief {0}CounterDefinitions for {1} {2} for testing.", derivedCounterFileInput.compiler_type_str, api.ToUpper(), generation.ToUpper());
            headerStream.WriteLine("//==============================================================================");
            headerStream.WriteLine();
            headerStream.WriteLine("// *** Note, this is an auto-generated file. Do not edit. Execute {0}CounterCompiler to rebuild.", derivedCounterFileInput.compiler_type_str);
            headerStream.WriteLine();

            string asicStr = asic;
            if (!String.IsNullOrEmpty(asicStr))
            {
                asicStr = '_' + asic.ToCamelCase('_') + '_';
            }

            string repoStr = "GPA";
            string headerGuard = repoStr + "_AUTO_GEN_UNIT_TESTS_COUNTERS_" + derivedCounterFileInput.compiler_type_str.ToUpper() + "_" + api.ToUpper() + "_" + generation.ToUpper() + asicStr;

            headerStream.WriteLine("#ifndef {0}", headerGuard);
            headerStream.WriteLine("#define {0}", headerGuard);
            headerStream.WriteLine();
            headerStream.WriteLine("#include \"gpu_perf_api_unit_tests/counters/gpa_counter_desc.h\"");
            headerStream.WriteLine();
            headerStream.WriteLine("/// Macros for {0}{1} {2} counter index", activeSectionLabel, asic, derivedCounterFileInput.compiler_type_str);
            headerStream.WriteLine("// clang-format off");

            int numExposedCounters = 0;
            int numDiscreteCounters = 0;
            int numStreamingCounters = 0;
            foreach (DerivedCounterDef exposedCounter in counterDefList)
            {
                ++numExposedCounters;

                int discreteCounterIndex = numDiscreteCounters;
                if (exposedCounter.IsDiscreteCounter)
                {
                    ++numDiscreteCounters;
                }

                int streamingCounterIndex = numStreamingCounters;
                if (exposedCounter.IsSpmCounter)
                {
                    ++numStreamingCounters;
                }

                if (exposedCounter.IsDiscreteCounter && !exposedCounter.IsSpmCounter)
                {
                    // Discrete-only counter.
                    cppStream.WriteLine("    {{// Discrete Counter Index: {0}", discreteCounterIndex);
                }
                else if (!exposedCounter.IsDiscreteCounter && exposedCounter.IsSpmCounter)
                {
                    // Streaming-only counter.
                    cppStream.WriteLine("    {{// Streaming Counter Index: {0}", streamingCounterIndex);
                }
                else
                {
                    // Both a discrete and streaming counter.
                    cppStream.WriteLine("    {{// Discrete Counter Index: {0}; Streaming Counter Index: {1}", discreteCounterIndex, streamingCounterIndex);
                }
                cppStream.WriteLine("    \"{0}\",", exposedCounter.Name);
                cppStream.WriteLine("    \"{0}\",", exposedCounter.Group);
                cppStream.WriteLine("    \"{0}\",", exposedCounter.Desc);
                cppStream.WriteLine("    \"{0}\",", exposedCounter.Comp);
                cppStream.WriteLine("    {0},", exposedCounter.GetCounterCount());
                cppStream.WriteLine("    {0},", exposedCounter.Type);
                cppStream.WriteLine("    {0},", exposedCounter.Usage);
                cppStream.WriteLine("    {0},", exposedCounter.IsDiscreteCounter ? "true" : "false");
                cppStream.WriteLine("    {0},", exposedCounter.IsSpmCounter ? "true" : "false");

                cppStream.WriteLine("    {0}}},", exposedCounter.GuidHash.ToString("X").Replace(",", ", "));
                if (exposedCounter.IsDiscreteCounter)
                {
                    headerStream.WriteLine("#define DISCRETE_{0}_{1}_{2}_{3}{4} {5}", exposedCounter.Name.ToUpper(), derivedCounterFileInput.compiler_type_str.ToUpper(), api.ToUpper(), generation.ToUpper(), asicStr, discreteCounterIndex);
                }

                if (exposedCounter.IsSpmCounter)
                {
                    headerStream.WriteLine("#define STREAMING_{0}_{1}_{2}_{3}{4} {5}", exposedCounter.Name.ToUpper(), derivedCounterFileInput.compiler_type_str.ToUpper(), api.ToUpper(), generation.ToUpper(), asicStr, streamingCounterIndex);
                }
            }

            cppStream.WriteLine("};");
            cppStream.WriteLine("// clang-format on");
            cppStream.Close();

            headerStream.WriteLine();
            headerStream.WriteLine("/// Number of public counters for {0} {1} {2}", api.ToUpper(), generation.ToUpper(), asicStr);
            headerStream.WriteLine("const size_t {0} = {1};", derivedCounterCountConstant, numExposedCounters);
            headerStream.WriteLine();
            headerStream.WriteLine("/// Array of public counters for {0} {1} {2}", api.ToUpper(), generation.ToUpper(), asic, asicStr);
            headerStream.WriteLine("extern const GpaCounterDesc {0}[{1}];", derivedCountersConstant, derivedCounterCountConstant);
            headerStream.WriteLine();
            headerStream.WriteLine("// clang-format on");
            headerStream.WriteLine("#endif  // {0}", headerGuard);
            headerStream.Close();
            return true;
        }

        /// <summary>
        /// Start the process of collecting information for RST documentation
        /// </summary>
        public void StartRSTDocumentation()
        {
            docInfoMapGraphicsByGeneration.Clear();
        }

        /// <summary>
        /// Writes a counter table to the specified stream
        /// </summary>
        /// <param name="docStream">the stream in which to write data</param>
        /// <param name="groupKvp">the data to use to write the counter data</param>
        private void WriteRSTCounterTable(StreamWriter docStream, KeyValuePair<string, Dictionary<string, DerivedCounterDef>> groupKvp)
        {
            docStream.WriteLine();
            string groupHeading = string.Format("{0} Group", groupKvp.Key);
            docStream.WriteLine(groupHeading);
            docStream.WriteLine(new String('%', groupHeading.Length));
            docStream.WriteLine();
            docStream.WriteLine(".. csv-table::");
            docStream.WriteLine("    :header: \"Counter Name\", \"Sample Type\", \"Usage\", \"Brief Description\"");
            docStream.WriteLine("    :widths: 15, 10, 10, 65");
            docStream.WriteLine();

            foreach (KeyValuePair<string, DerivedCounterDef> counter in groupKvp.Value)
            {
                string usage = counter.Value.Usage;
                const string kPrefix = "kGpaUsageType";
                usage = usage.Remove(0, kPrefix.Length);
                string sampleType = "";
                if (counter.Value.IsDiscreteCounter && !counter.Value.IsSpmCounter)
                {
                    sampleType = "Discrete";
                }
                else if (!counter.Value.IsDiscreteCounter && counter.Value.IsSpmCounter)
                {
                    sampleType = "Streaming";
                }
                else
                {
                    sampleType = "Discrete, Streaming";
                }

                docStream.WriteLine("    \"{0}\", \"{1}\", \"{2}\", \"{3}\"", counter.Key, sampleType, usage, counter.Value.Desc);
            }
        }

        /// <summary>
        /// Finish the process of collecting information for RST documentation. This will write the data to files.
        /// </summary>
        public void DoneRSTDocumentation(Func<string, bool> infoHandler, Func<string, bool> errorHandler)
        {
            {
                { // Graphics Counters
                    foreach (var counterGroupByGfxGen in docInfoMapGraphicsByGeneration)
                    {
                        string docOutputFileName = "graphics_counter_tables_" + gfxGenAsStr[counterGroupByGfxGen.Key] + ".rst";
                        string docOutputFile = GpaTools.Gpa.GetGpuPerfApiPath() + GpaTools.Gpa.gpaDocSourceDir + docOutputFileName;

                        StreamWriter docStream = null;
                        try
                        {
                            docStream = new StreamWriter(docOutputFile);
                        }
                        catch
                        {
                            errorHandler("Failed to open file for writing: " + docOutputFile);
                            return;
                        }

                        docStream.WriteLine(".. Graphics Performance Counters for {0}", gfxGenerationDisplayName[counterGroupByGfxGen.Key]);
                        docStream.WriteLine();
                        docStream.WriteLine(".. *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.");

                        docStream.WriteLine();
                        string gfxHeading = string.Format("{0} Counters", gfxGenerationDisplayName[counterGroupByGfxGen.Key]);
                        docStream.WriteLine(gfxHeading);
                        docStream.WriteLine(new String('+', gfxHeading.Length));

                        foreach (KeyValuePair<string, Dictionary<string, DerivedCounterDef>> groupKvp in counterGroupByGfxGen.Value)
                        {
                            WriteRSTCounterTable(docStream, groupKvp);
                        }

                        docStream.Close();
                    }
                }
            }
        }
    }
}
