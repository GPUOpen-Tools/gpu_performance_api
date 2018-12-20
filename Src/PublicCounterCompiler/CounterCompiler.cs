// =====================================================================
// <copyright file="CounterCompiler.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2018 Advanced Micro Devices, Inc. All rights reserved.
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

    /// <summary>
    /// Compiles the derived counters definitions into C++ files.
    /// </summary>
    public class CounterCompiler
    {
        public class DerivedCounterFileInput
        {
            public string rootFilename;
            public string compilerInputPath;

            public string outputDirectory;
            public string counterListOutputDirectory;
            public string testOutputDirectory;
        }

        public static DerivedCounterFileInput derivedCounterFileInput = null;

        public static bool isInternal = false;

        /// <summary>
        /// Class to hold info for counter documentation
        /// </summary>
        class PublicCounterDocInfo
        {
            /// <summary>
            /// The public counter definition
            /// </summary>
            public DerivedCounterDef publicCounter = null;

            /// <summary>
            /// Flag indicating if the counter support GFX9
            /// </summary>
            public bool gfx9Supported = false;

            /// <summary>
            /// Flag indicating if the counter support GFX8
            /// </summary>
            public bool gfx8Supported = false;

            /// <summary>
            /// Flag indicating if the counter support GFX7
            /// </summary>
            public bool gfx7Supported = false;

            /// <summary>
            /// Flag indicating if the counter support GFX6
            /// </summary>
            public bool gfx6Supported = false;
        }

        /// <summary>
        /// A map of Counter Group to a map of counter name to documentation info for Graphics Counters
        /// </summary>
        private static Dictionary<string, Dictionary<string, PublicCounterDocInfo>> docInfoMapGraphics = new Dictionary<string, Dictionary<string, PublicCounterDocInfo>>();

        /// <summary>
        /// A map of Counter Group to a map of counter name to documentation info for Graphics Counters
        /// </summary>
        private static Dictionary<string, Dictionary<string, PublicCounterDocInfo>> docInfoMapCompute = new Dictionary<string, Dictionary<string, PublicCounterDocInfo>>();

        /// <summary>
        /// Indicates if this app is being run as a console app (true) or UI app (false)
        /// </summary>
        public static bool isConsoleApp = true;

        /// <summary>
        /// List of global GPU generation internal counters
        /// </summary>
        private static List<InternalCounterDef> globalInternalCounterList = null;

        /// <summary>
        /// Outputs a message to the console or the form
        /// </summary>
        /// <param name="strMsg">The message to output</param>
        public static void Output(string strMsg)
        {
            if (isConsoleApp)
            {
                Console.WriteLine(strMsg);
            }
            else
            {
                Form1.Instance().Output(strMsg);
            }
            Debug.Print(strMsg);
        }

        /// <summary>
        /// Gets a value indicating whether invalid counters should be considered errors, or if they should be ignored.
        /// </summary>
        /// <returns>True to ignore the invalid counters; false if they should be considered errors.</returns>
        public static bool IgnoreInvalidCounters()
        {
            if (isConsoleApp)
            {
                // by default, running from the console will ignore invalid counters
                return true;
            }
            else
            {
                return Form1.Instance().IgnoreInvalidCounters();
            }
        }

        /// <summary>
        /// Gets the GPA base path where files should be generated into
        /// </summary>
        /// <returns>the GPA base path where files should be generated into</returns>
        public static string GetGPABasePath()
        {
            // calculate the proper path to output to
            string CompilerOutputFolder = "Output\\";
            int endPath = Application.StartupPath.IndexOf(CompilerOutputFolder) + CompilerOutputFolder.Length;

            if (CompilerOutputFolder.Length == endPath)
            {
                Output(Application.ProductName + " was started out of unexpected folder.");
                return "";
            }

            return Application.StartupPath.Substring(0, endPath - CompilerOutputFolder.Length);
        }

        /// <summary>
        /// Sets directories based on the supplied API and generation and
        /// compiles the derived counters
        /// </summary>
        /// <param name="api">The API to compile counters for</param>
        /// <param name="generation">The HW generation</param>
        /// <returns>true on success, false if there were any errors</returns>
        public static bool CompileCounters(string api, string generation)
        {
            // Iterate over files that match the base of the counter name's generation file
            string searchFilename = derivedCounterFileInput.rootFilename + "CounterNames" + api + generation + "*.txt";

            string[] filenames = Directory.GetFiles(derivedCounterFileInput.compilerInputPath, searchFilename);

            if (filenames.Length == 0)
            {
                Output("No files found at:" + derivedCounterFileInput.compilerInputPath + " matching:" + searchFilename);
                return false;
            }

            List<string> asicSpecificFiles = new List<string>();

            foreach (string counterNamesFile in filenames)
            {
                // Determine the specific ASIC, if any
                string baseFilename = Path.GetFileNameWithoutExtension(counterNamesFile);

                int asicIndex = baseFilename.IndexOf(generation);
                string asic = baseFilename.Substring(asicIndex + generation.Length);

                if (!string.IsNullOrEmpty(asic))
                {
                    asicSpecificFiles.Add(asic);
                }

                // Suffix
                string suffix = string.Empty;
                if (api == "CL" || api == "HSA")
                {
                    suffix = "Compute";
                }

                string derivedCounterDefsFile = derivedCounterFileInput.compilerInputPath + derivedCounterFileInput.rootFilename + "CounterDefinitions" + suffix + generation + ".txt";
                string section = api + generation;
                string strError = string.Empty;

                // Some files may not exist for certain combinations of APIs and architectures
                if (!File.Exists(derivedCounterDefsFile))
                {
                    Output("Info: Unable to find file " + derivedCounterDefsFile);
                    return true;
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
                    out strError))
                {
                    if (!string.IsNullOrEmpty(strError))
                    {
                        Output(strError);
                    }

                    Output(derivedCounterFileInput.rootFilename + "CounterDefs" + section + asic + ".cpp / .h written out to:" + derivedCounterFileInput.outputDirectory);
                }
                else
                {
                    Output(strError);
                    return false;
                }
            }

            // Generate section + ASIC file
            bool retVal = GenerateSectionAsicFiles(derivedCounterFileInput.rootFilename, api, generation, derivedCounterFileInput.outputDirectory, asicSpecificFiles);

            if (retVal)
            {
                Output("Counter generation completed successfully");
            }
            else
            {
                Output("Counter generation failed");
            }

            return retVal;
        }

        private static bool GenerateSectionAsicFiles(
            string rootFilename,
            string api,
            string generation,
            string outputDirectory,
            List<string> asicSpecificFiles)
        {
            string section = api + generation;
            string filename = outputDirectory + rootFilename + "CounterDefs" + section + "Asics.h";

            // Write header file
            Output("Writing ASIC header to " + filename);
            StreamWriter includeFile = null;
            try
            {
                includeFile = new StreamWriter(filename);
            }
            catch
            {
                Output("ERROR: Failed to open file for writing: " + filename);
                return false;
            }

            includeFile.WriteLine("//==============================================================================");
            includeFile.WriteLine("// Copyright (c) 2010-{0} Advanced Micro Devices, Inc. All rights reserved.",
                DateTime.Today.Year);
            includeFile.WriteLine("/// \\author AMD Developer Tools Team");
            includeFile.WriteLine("/// \\file");
            includeFile.WriteLine("/// \\brief {0}CounterDefinitions ASIC file for {1}", rootFilename, section.ToUpper());
            includeFile.WriteLine("//==============================================================================");
            includeFile.WriteLine();
            includeFile.WriteLine("#ifndef _{0}_COUNTER_DEFS_{1}_ASICS_H_", rootFilename.ToUpper(), section.ToUpper());
            includeFile.WriteLine("#define _{0}_COUNTER_DEFS_{1}_ASICS_H_", rootFilename.ToUpper(), section.ToUpper());
            includeFile.WriteLine();
            includeFile.WriteLine("//*** Note, this is an auto-generated file. Do not edit. Execute {0}CounterCompiler to rebuild.", rootFilename);
            includeFile.WriteLine();
            includeFile.WriteLine("#include \"GPADerivedCounters.h\"");
            includeFile.WriteLine();

            foreach(string asic in asicSpecificFiles)
            {
                includeFile.WriteLine("#include \"{0}CounterDefs{1}{2}.h\"", rootFilename, section, asic);
            }

            includeFile.WriteLine();

            includeFile.WriteLine("namespace {0}Asics", section);
            includeFile.WriteLine("{");
            includeFile.WriteLine();

            includeFile.WriteLine("/// Updates default GPU generation derived counters with ASIC specific derived counters if available.");
            includeFile.WriteLine("/// \\param desiredGeneration Hardware generation currently in use.");
            includeFile.WriteLine("/// \\param asicType The ASIC type that is currently in use.");
            includeFile.WriteLine("/// \\param c Returned set of derived counters, if available.");
            includeFile.WriteLine("/// \\return True if the ASIC matched one available, and c was updated.");
            includeFile.WriteLine("inline void Update{0}AsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)", rootFilename);
            includeFile.WriteLine("{");

            if (asicSpecificFiles.Count == 0)
            {
                includeFile.WriteLine("    UNREFERENCED_PARAMETER(desiredGeneration);");
                includeFile.WriteLine("    UNREFERENCED_PARAMETER(asicType);");
                includeFile.WriteLine("    UNREFERENCED_PARAMETER(c);");
            }
            else
            {
                includeFile.WriteLine();

                foreach (string asic in asicSpecificFiles)
                {
                    includeFile.WriteLine("    if ({0}{1}::Update{2}AsicSpecificCounters(desiredGeneration, asicType, c))", section, asic, rootFilename);
                    includeFile.WriteLine("    {");
                    includeFile.WriteLine("        return;");
                    includeFile.WriteLine("    }");
                    includeFile.WriteLine();
                }
            }

            includeFile.WriteLine("}");

            includeFile.WriteLine();
            includeFile.WriteLine("} // " + section + "Asics");
            includeFile.WriteLine();

            includeFile.WriteLine("#endif // _{0}_COUNTER_DEFS_{1}_ASICS_H_", rootFilename.ToUpper(), section.ToUpper());
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
        private static void OutputCounterError(string counterName, string component, int index, string errorMessage)
        {
            Output("Error: " + counterName + " - " + errorMessage + " " + component + " at index " + index);
        }

        /// <summary>
        /// Validates the counter formula and referenced hardware counters
        /// </summary>
        /// <param name="counter">Derived counter to validate</param>
        /// <returns>True if the formula and referenced counters are correct, otherwise false.</returns>
        private static bool ValidateFormulaAndReferencedCounter(DerivedCounterDef counter)
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
                    OutputCounterError(counter.Name, component, componentIndex, "empty comp component");
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
                        OutputCounterError(counter.Name, component, componentIndex, "invalid hardware counter range");
                        retVal = false;
                        break;
                    }

                    int ellipsisIndex = component.IndexOf("..");
                    if (ellipsisIndex < 0)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "invalid hardware counter range");
                        retVal = false;
                        break;
                    }

                    int endingCounter = 0;
                    isNumeric = int.TryParse(component.Substring(ellipsisIndex + 2), out endingCounter);
                    if (!isNumeric)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "invalid hardware counter range");
                        retVal = false;
                        break;
                    }

                    if (endingCounter <= startingCounter)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "invalid hardware counter range");
                        retVal = false;
                        break;
                    }

                    if (((endingCounter - startingCounter) + 1) % 4 != 0)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "hardware counter range is not a multiple of 4");
                        retVal = false;
                        break;
                    }

                    for (int i = startingCounter; i <= endingCounter; ++i)
                    {
                        rpnStack.Push(i.ToString());

                        var hardwareCounter = counter.GetCounter(i);
                        if (hardwareCounter == null)
                        {
                            OutputCounterError(counter.Name, component, componentIndex, "reference to undefined hardware counter index");
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
                        OutputCounterError(counter.Name, component, componentIndex, "reference to out of range hardware counter index");
                        retVal = false;
                        break;
                    }

                    var hardwareCounter = counter.GetCounter(index);
                    if (hardwareCounter == null)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "reference to undefined hardware counter index");
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

                    isNumeric = int.TryParse(n, out index);
                    if (!isNumeric)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "invalid numeric value");
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
                                OutputCounterError(counter.Name, component, componentIndex, "stack has insufficient entries (pop 2) for");
                                retVal = false;
                                break;
                            }
                            string result = rpnStack.Pop();
                            result = component + result;
                            result = rpnStack.Pop() + result;
                            rpnStack.Push(result);
                        }
                        continue;

                    case "min":
                        {
                            if (rpnStack.Count < 2)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "stack has insufficient entries (pop 2) for");
                                retVal = false;
                                break;
                            }
                            string result = component + "(";
                            result += rpnStack.Pop() + ",";
                            result += rpnStack.Pop() + ")";
                            rpnStack.Push(result);
                        }
                        continue;

                    case "ifnotzero":
                        {
                            if (rpnStack.Count < 3)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "stack has insufficient entries (pop 3) for");
                                retVal = false;
                                break;
                            }
                            string result = rpnStack.Pop();

                            // the format is: false,true,condition,ifnotzero
                            // detect if condition is a constant value
                            if (result.Contains("("))
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "ifnotzero conditional expression is constant");
                                retVal = false;
                                break;
                            }

                            result += "?";
                            result += rpnStack.Pop();
                            result += ":";
                            result += rpnStack.Pop();
                            rpnStack.Push(result);
                        }
                        continue;

                    case "comparemax4":
                        {
                            if (rpnStack.Count < 8)
                            {
                                OutputCounterError(counter.Name, component, componentIndex, "stack has insufficient entries (pop 8) for");
                                retVal = false;
                                break;
                            }
                            string result = string.Empty;
                            result = "max(";
                            for (int i = 0; i < 4; ++i)
                            {
                                result = rpnStack.Pop();
                                if (i != 3)
                                {
                                    result += ", ";
                                }
                            }
                            result = ") ? ret(";
                            for (int i = 0; i < 4; ++i)
                            {
                                result = rpnStack.Pop();
                                if (i != 3)
                                {
                                    result += ", ";
                                }
                            }
                            result = ")";
                            rpnStack.Push(result);
                        }
                        continue;

                    case "num_shader_engines":
                    case "num_simds":
                    case "su_clocks_prim":
                    case "num_prim_pipes":
                    case "ts_freq":
                        rpnStack.Push(component);
                        continue;
                }

                // Special handling for sum{N}
                if (component.Substring(0, 3) == "sum")
                {
                    int popCount = 0;
                    string strCount = component.Substring(3);
                    if (string.IsNullOrEmpty(strCount))
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "sum operator missing number of components");
                        retVal = false;
                        break;
                    }

                    isNumeric = int.TryParse(strCount, out popCount);
                    if (!isNumeric)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "sum operator with invalid component count");
                        retVal = false;
                        break;
                    }

                    if (rpnStack.Count < popCount)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "attempt to sum more components than exist on stack");
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

                // Special handling for max{N}
                if (component.Substring(0, 3) == "max")
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
                            OutputCounterError(counter.Name, component, componentIndex, "sum operator with invalid component count");
                            retVal = false;
                            break;
                        }
                    }

                    if (rpnStack.Count < popCount)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "attempt to sum more components than exist on stack");
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

                // Special handling for dividesum{N}
                if (component.Substring(0, 9) == "dividesum")
                {
                    int popCount = 0;
                    string strCount = component.Substring(9);
                    if (string.IsNullOrEmpty(strCount))
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "dividesum operator missing number of components");
                        retVal = false;
                        break;
                    }

                    isNumeric = int.TryParse(strCount, out popCount);
                    if (!isNumeric)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "dividesum operator with invalid component count");
                        retVal = false;
                        break;
                    }

                    if (rpnStack.Count < popCount)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "attempt to dividesum more components than exist on stack");
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

                // Special handling for avg{N}
                if (component.Substring(0, 3) == "avg")
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
                            OutputCounterError(counter.Name, component, componentIndex, "avg operator with invalid component count");
                            retVal = false;
                            break;
                        }
                    }

                    if (rpnStack.Count < popCount)
                    {
                        OutputCounterError(counter.Name, component, componentIndex, "attempt to avg more components than exist on stack");
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

                // Unknown component - error
                OutputCounterError(counter.Name, component, componentIndex, "unknown formula component");
                retVal = false;
            }

            // Validate stack contains a single result
            if (rpnStack.Count != 1)
            {
                Output("Error: " + counter.Name + " stack incorrectly contains " + rpnStack.Count.ToString() + " entries instead a single result");
                retVal = false;
            }

            // Validate all hardware counters were referenced
            int counterIndex = 0;

            foreach (var hardwareCounter in counter.GetCounters())
            {
                if (hardwareCounter.Referenced == false)
                {
                    if (hardwareCounter.Name.Contains("SPI_PERF_PS_CTL_BUSY")
                        || hardwareCounter.Name.Contains("SPI_PERF_PS_BUSY"))
                    {
                        Output("Info: " + counter.Name + " unreferenced block instance counter " + hardwareCounter.Name + " at index "
                            + counterIndex + ". This is required for some counter definitions.");
                    }
                    else
                    {
                        Output("Error: " + counter.Name + " unreferenced block instance counter " + hardwareCounter.Name + " at index " + counterIndex);
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
        private static bool ValidateFormulaAndReferencedCounters(ref List<DerivedCounterDef> counters)
        {
            bool retVal = true;

            foreach (DerivedCounterDef counter in counters)
            {
                retVal &= ValidateFormulaAndReferencedCounter(counter);
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
        /// <param name="strError">Error return.</param>
        /// <returns>True is files are successfully loaded and generated.</returns>
        private static void GenerateDerivedCounterDocFile(
            bool outputCsv,
            ref List<DerivedCounterDef> derivedCounterList,
            ref List<InternalCounterDef> internalCounterList,
            string outputDir,
            string api,
            string generation,
            string asic)
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
                Output("ERROR: Failed to open file for writing: " + docStream);
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

                if (outputCsv)
                {
                    string desc = counter.Desc.Replace(',', ' ');
                    docStream.WriteLine(counter.Name + "," + counter.Usage + "," + desc);
                }
                else
                {
                    docStream.WriteLine(counter.Name);
                    docStream.WriteLine(counter.Usage);
                    docStream.WriteLine(counter.Desc);
                    docStream.WriteLine(counter.CompReadable);
                    docStream.WriteLine();
                }
            }

            docStream.Close();
            Output("Counter Doc file written: " + docFilePath);
        }

        /// <summary>
        /// Adds information to the counter info structure that will be used to generate counter documentation.
        /// </summary>
        /// <param name="derivedCounterList">List of public counters.</param>
        /// <param name="generation">GPU generation.</param>
        /// <param name="docInfoMap">the counter info structure in which to add information</param>
        private static void AddInfoToRSTDocInfo(
            ref List<DerivedCounterDef> derivedCounterList,
            string generation,
            Dictionary<string, Dictionary<string, PublicCounterDocInfo>> docInfoMap)
        {
            foreach (var counter in derivedCounterList)
            {
                PublicCounterDocInfo counterInfo = null;
                Dictionary<string, PublicCounterDocInfo> counterMap = null;

                if (docInfoMap.ContainsKey(counter.Group))
                {
                    counterMap = docInfoMap[counter.Group];

                    if (counterMap.ContainsKey(counter.Name))
                    {
                        // counter already in map
                        counterInfo = counterMap[counter.Name];

                        if (counterInfo.publicCounter.Desc != counter.Desc)
                        {
                            Output("Documentation Message: Same counter with diffferent description");
                            string outputMsg = string.Format("    Name: {0}", counter.Name);
                            Output(outputMsg);
                            outputMsg = string.Format("   Previous description: {0}", counterInfo.publicCounter.Desc);
                            Output(outputMsg);
                            outputMsg = string.Format("   Current description: {0}", counter.Desc);
                            Output(outputMsg);
                        }
                    }
                    else
                    {
                        // counter not in map
                        counterInfo = new PublicCounterDocInfo();
                        counterInfo.publicCounter = counter;
                        counterMap[counter.Name] = counterInfo;
                    }
                }
                else
                {
                    // counter not in map
                    counterInfo = new PublicCounterDocInfo();
                    counterInfo.publicCounter = counter;
                    counterMap = new Dictionary<string, PublicCounterDocInfo>();
                    counterMap[counter.Name] = counterInfo;
                    docInfoMap[counter.Group] = counterMap;
                }

                if ("Gfx9" == generation)
                {
                    counterInfo.gfx9Supported = true;
                }
                else if ("Gfx8" == generation)
                {
                    counterInfo.gfx8Supported = true;
                }
                else if ("Gfx7" == generation)
                {
                    counterInfo.gfx7Supported = true;
                }
                else if ("Gfx6" == generation)
                {
                    counterInfo.gfx6Supported = true;
                }

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
        /// <param name="sectionLabel">Section label: API + GPU generation.</param>
        /// <param name="asic">Optional ASIC name.</param>
        /// <param name="strError">Error return.</param>
        /// <returns>True is files are successfully loaded and generated.</returns>
        public static bool LoadFilesAndGenerateOutput(
            string rootFilename,
            string counterNamesFile,
            string derivedCounterDefFile,
            string outputDir,
            string counterListOutputDirectory,
            string testOutputDirectory,
            string api,
            string generation,
            string asic,
            out string strError)
        {
            strError = string.Empty;

            string sectionLabel = api + generation;

            // Load the internal counters
            List<InternalCounterDef> internalCounterList = new List<InternalCounterDef>();
            bool readOk = LoadInternalCounters(counterNamesFile, ref internalCounterList, asic, out strError);
            if (!readOk)
            {
                strError = "Error reading counter name file (" + counterNamesFile + ").\n" + strError;
                return false;
            }

            Output("Read " + internalCounterList.Count + " internal counters from " + counterNamesFile + ".");

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
                    int foundIndex = thisAsicCounterList.FindIndex(x => x.Name == internalCounter.Name);

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
            List<DerivedCounterDef> publicCounterList = new List<DerivedCounterDef>();
            readOk = LoadDerivedCounterDefinitions(derivedCounterDefFile, ref publicCounterList, ref internalCounterList,
                sectionLabel, asic, out strError);
            if (!readOk)
            {
                strError = "Error processing public counter file (" + derivedCounterDefFile + ").\n" + strError;
                return false;
            }

            if (publicCounterList.Count == 0)
            {
                strError = "Error: 0 counters were exposed by the counter definitions file.";
                return false;
            }
            else
            {
                Output("Read " + publicCounterList.Count + " public counters from " + derivedCounterDefFile + ".");
            }

            if (ValidateFormulaAndReferencedCounters(ref publicCounterList) == false)
            {
                return false;
            }

            if (GenerateOutputFiles(ref internalCounterList, ref publicCounterList, rootFilename, api, generation, outputDir,
                    counterListOutputDirectory, asic) == false)
            {
                return false;
            }
            else
            {
                bool genTestOutputFilesStatus = GenerateTestOutputFiles(ref internalCounterList, ref publicCounterList, rootFilename,
                    sectionLabel, testOutputDirectory, asic);
                if (false == genTestOutputFilesStatus)
                {
                    Output("Failed to generate output test files for " + sectionLabel);
                }
            }

            if (Form1.Instance().GenerateCounterDocs)
            {
                GenerateDerivedCounterDocFile(true, ref publicCounterList, ref internalCounterList, outputDir, api, generation, asic);
                GenerateDerivedCounterDocFile(false, ref publicCounterList, ref internalCounterList, outputDir, api, generation, asic);
            }

            bool isGraphicsAPI = (api != "CL") && (api != "HSA");

            AddInfoToRSTDocInfo(ref publicCounterList, generation, isGraphicsAPI ? docInfoMapGraphics : docInfoMapCompute);

            strError = string.Empty;
            return true;
        }

        private static bool CreateReadableEquation(ref DerivedCounterDef counterDef, string inputLine)
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
                        // this could cross over multiple counters
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
        /// <param name="strError">Optional returned error.</param>
        /// <returns>True if internal counters are successfully loaded.</returns>
        public static bool LoadInternalCounters(string file,
            ref List<InternalCounterDef> internalCounterList,
            string asic,
            out string strError)
        {
            bool isAsicSpecific = !string.IsNullOrEmpty(asic);

            string[] publicCounterDefs;
            try
            {
                publicCounterDefs = File.ReadAllLines(file);
            }
            catch (Exception e)
            {
                strError = "Error: Could not read contents of " + file + ": " + e.Message;
                return false;
            }

            HashSet<int> usedCounterNumbers = new HashSet<int>();

            int lineNum = 0;
            foreach (string s in publicCounterDefs)
            {
                if (s.Length == 0)
                {
                    continue;
                }

                if (s.Contains("="))
                {
                    strError =
                        "Error: Internal counter names may not contain = symbols. Change the counter name or change PCC public counter parsing to support = in names.";
                    return false;
                }

                string[] counterText = s.Split(',');
                if (counterText.Length != 3 && counterText.Length != 2)
                {
                    strError =
                        "Error: Problem reading internal counter definition. Format is either: 'number , name , type' or 'name , type'. Line='" +
                        s + "'";
                    return false;
                }

                int counterNumber = -1;
                if (counterText.Length == 3)
                {
                    System.Int32.TryParse(counterText[0], out counterNumber);
                    if (usedCounterNumbers.Contains(counterNumber))
                    {
                        strError = "Error: duplicate counter numbers detected. Line='" + s + "'";
                        return false;
                    }
                    else if (counterNumber != lineNum)
                    {
                        if (isAsicSpecific)
                        {
                            // This is ok, because ASIC specific data is offset to overlay into the
                            // global base GPU generation block instances
                        }
                        else
                        {
                            strError = "Error: internal counter numbers defined out of sequence. Line='" + s + "'";
                            return false;
                        }
                    }

                    usedCounterNumbers.Add(counterNumber);

                    internalCounterList.Add(new InternalCounterDef(counterNumber, counterText[1].Trim(), counterText[2].Trim(), isAsicSpecific));
                }
                else
                {
                    internalCounterList.Add(new InternalCounterDef(counterNumber, counterText[0].Trim(), counterText[1].Trim(), isAsicSpecific));
                }

                lineNum++;
            }

            strError = string.Empty;
            return true;
        }

        /// <summary>
        /// Get the index of a string in a list (case insensitive)
        /// </summary>
        /// <param name="counterName">Name of the counter.</param>
        /// <param name="internalCounterList">Internal counter list.</param>
        /// <param name="index">Returned index of the counter.</param>
        /// <returns>True if the counter was found, otherwise false.</returns>
        public static bool GetCounterIndex(string counterName,
            ref List<InternalCounterDef> internalCounterList,
            out int index)
        {
            foreach (InternalCounterDef c in internalCounterList)
            {
                if (c.Name.Equals(counterName, StringComparison.OrdinalIgnoreCase))
                {
                    index = c.Index;
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
        /// <returns>True if the public counter definitions are successfully loaded.</returns>
        public static bool LoadDerivedCounterDefinitions(string file,
            ref List<DerivedCounterDef> counterDefList,
            ref List<InternalCounterDef> internalCounterList,
            string activeSectionLabel,
            string asic,
            out string strError)
        {
            strError = string.Empty;

            // Some files may not exist for certain combinations of APIs and architectures
            if (!File.Exists(file))
            {
                Output("Info: Unable to find file " + file);
                return true;
            }

            Output("Reading: " + file);

            string[] publicCounterDefs;
            try
            {
                publicCounterDefs = File.ReadAllLines(file);
            }
            catch (Exception e)
            {
                strError = "Error: " + e.Message;
                return false;
            }

            bool discardApiSections = true;
            uint numInvalidCounterNames = 0;
            uint lineNumber = 0;

            DerivedCounterDef counterDef = null;

            List<string> currentApis;

            foreach (string line in publicCounterDefs)
            {
                ++lineNumber;

                string s = line.Trim();

                // Trim any comments
                {
                    int index = s.IndexOf(';');
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
                        ref internalCounterList, activeSectionLabel, asic, out strError);
                    if (!loadedInclude)
                    {
                        strError = "Error: Loading of include file " + includeFile + " failed.\n" + strError;
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
                            Output("Warning: no comp found for " + activeSectionLabel +
                                   ", will not expose counter for: " + counterDef.Name);
                        }

                        if (lineSplit[1].Length == 0)
                        {
                            strError = "Error: name definition empty. Line='" + s + "'";
                            return false;
                        }

                        counterDef = new DerivedCounterDef { Name = lineSplit[1] };

                        currentApis = new List<string>();

                        discardApiSections = true;
                    }
                    else if (lineSplit[0].Equals("group", StringComparison.OrdinalIgnoreCase))
                    {
                        if (!counterDef.ValidName())
                        {
                            strError = "Error: name= should appear before group=. Line='" + s + "'";
                            return false;
                        }

                        counterDef.Group = lineSplit[1];
                    }
                    else if (lineSplit[0].Equals("desc", StringComparison.OrdinalIgnoreCase))
                    {
                        if (!counterDef.ValidName())
                        {
                            strError = "Error: name= should appear before desc=. Line='" + s + "'";
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
                            strError = "Error: name= should appear before type=. Line='" + s + "'";
                            return false;
                        }

                        // map input type to a GPA type
                        if (lineSplit[1].Equals("gpa_float64", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Type = "GPA_DATA_TYPE_FLOAT64";
                        }
                        else if (lineSplit[1].Equals("gpa_uint64", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Type = "GPA_DATA_TYPE_UINT64";
                        }
                        else
                        {
                            strError =
                                "Error: type not recognized. Check what you have entered, and also that PCC handles all relevant types. Line='" +
                                s + "'";
                            return false;
                        }
                    }
                    else if (lineSplit[0].Equals("usage", StringComparison.OrdinalIgnoreCase))
                    {
                        if (!counterDef.ValidName())
                        {
                            strError = "Error: name= should appear before usage=. Line='" + s + "'";
                            return false;
                        }

                        // map input type to a GPA type
                        if (lineSplit[1].Equals("ratio", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "GPA_USAGE_TYPE_RATIO";
                        }
                        else if (lineSplit[1].Equals("percentage", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "GPA_USAGE_TYPE_PERCENTAGE";
                        }
                        else if (lineSplit[1].Equals("cycles", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "GPA_USAGE_TYPE_CYCLES";
                        }
                        else if (lineSplit[1].Equals("nanoseconds", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "GPA_USAGE_TYPE_NANOSECONDS";
                        }
                        else if (lineSplit[1].Equals("bytes", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "GPA_USAGE_TYPE_BYTES";
                        }
                        else if (lineSplit[1].Equals("items", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "GPA_USAGE_TYPE_ITEMS";
                        }
                        else if (lineSplit[1].Equals("kilobytes", StringComparison.OrdinalIgnoreCase))
                        {
                            counterDef.Usage = "GPA_USAGE_TYPE_KILOBYTES";
                        }
                        else
                        {
                            strError =
                                "Error: usage not recognized. Check what you have entered, and also that PublicCounterCompiler handles all relevant types. Line='" +
                                s + "'";
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
                            strError = "Error: Duplicate equation. Line='" + s + "'";
                            return false;
                        }

                        if (!counterDef.ValidName())
                        {
                            strError =
                                "Error: comp= encountered before name=. Ensure name and optional description appear before comp=. Line='" +
                                s + "'";
                            return false;
                        }

                        if (counterDef.GetCounterCount() == 0)
                        {
                            strError =
                                "Error: Block instance events must be defined before comp encountered. Line='" +
                                s + "'";
                            return false;
                        }

                        string equation = lineSplit[1];

                        // build a readable version of the comp for readable debugging, validation, output
                        if (!CreateReadableEquation(ref counterDef, lineSplit[1]))
                        {
                            strError = "Error: Unable to create readable equation. Line='" + s + "'";
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
                            foreach(string eqn in equations)
                            {
                                string[] compParts = eqn.Split(',');

                                string newEqn = string.Empty;

                                foreach(string part in compParts)
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
                        strError = "Error: Encountered PI section " + s +
                                   "before derived counter name " + counterDef.Name +
                                   ". Check order of definitions.";
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
                                strError = "Error: Counter named '" + counterDef.Name +
                                           "' has a duplicate counter definition '" + s + "'.";
                                return false;
                            }

                            counterDef.AddCounter(counterName, index);
                        }
                        else
                        {
                            Output("Warning: Counter not recognized " + s +
                                   ". Compare this spelling to the counter names file to see which is incorrect.");
                            counterDef.AddCounter(s, index);
                            numInvalidCounterNames++;
                        }
                    }
                }
            }

            // if we were trying to define a counter, but never did a comp for it, output a warning since the counter will not be generated
            if (counterDef != null && !counterDef.ValidEquation())
            {
                strError += "Warning: incomplete counter " + activeSectionLabel + ", will not expose counter for: " 
                    + counterDef.Name + Environment.NewLine;
            }

            if (numInvalidCounterNames > 0 && IgnoreInvalidCounters() == false)
            {
                strError = "Error: Encountered " + numInvalidCounterNames + " invalid counter names.";
                return false;
            }

            strError = string.Empty;
            return true;
        }

        /// <summary>
        /// Expands a series of numbers separated by an ellipses.
        /// Example: "0..7" will expand to a list containing the numbers 0,1,2,3,4,5,6,7
        /// </summary>
        /// <param name="input">the ellipsed string to expand</param>
        /// <returns>A list of numbers</returns>
        private static List<int> ExpandEllipses(string input)
        {
            List<int> values = new List<int>();
            if (input.Contains(".."))
            {
                // split on a decimal, we expect the 2nd result to be an empty value between the two ".."
                string[] valueParts = input.Split('.');
                int first = int.Parse(valueParts[0]);
                int second = int.Parse(valueParts[2]);
                System.Diagnostics.Debug.Assert(valueParts[1].Length == 0);
                System.Diagnostics.Debug.Assert(first < second);
                for (int i = first; i <= second; i++)
                {
                    values.Add(i);
                }
            }
            else
            {
                values.Add(int.Parse(input));
            }
            return values;
        }

        public static bool DerivedCounterReferencesAsicRegisters(ref List<InternalCounterDef> internalCounterList, DerivedCounterDef c)
        {
            foreach (DerivedCounterDef.HardwareCounterDef counter in c.GetCounters())
            {
                if (internalCounterList.Exists(x => x.Name == counter.Name && x.IsAsicSpecific == true))
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
        public static bool GenerateOutputFiles(
            ref List<InternalCounterDef> internalCounterList,
            ref List<DerivedCounterDef> counterDefList,
            string rootFilename,
            string api,
            string generation,
            string outputDir,
            string counterListOutputDirectory,
            string asic)
        {
            if (string.IsNullOrEmpty(counterListOutputDirectory))
            {
                return true;
            }

            bool asicSpecific = !string.IsNullOrEmpty(asic);

            string activeSectionLabel = api + generation;

            if (outputDir.Length > 0 && !outputDir.EndsWith("\\"))
            {
                outputDir = outputDir + "\\";
            }

            if (counterListOutputDirectory.Length > 0 && !counterListOutputDirectory.EndsWith("\\"))
            {
                counterListOutputDirectory = counterListOutputDirectory + "\\";
            }

            Directory.CreateDirectory(counterListOutputDirectory);

            string filename = string.Format("{0}{1}CounterDefs{2}{3}.h", outputDir, rootFilename, activeSectionLabel, asic);

            // Write header file
            Output("Writing header to " + filename);
            StreamWriter hsw = null;
            try
            {
                hsw = new StreamWriter(filename);
            }
            catch
            {
                Output("ERROR: Failed to open file for writing: " + filename);
                return false;
            }

            hsw.WriteLine("//==============================================================================");
            hsw.WriteLine("// Copyright (c) 2010-{0} Advanced Micro Devices, Inc. All rights reserved.",
                DateTime.Today.Year);
            hsw.WriteLine("/// \\author AMD Developer Tools Team");
            hsw.WriteLine("/// \\file");
            hsw.WriteLine("/// \\brief {0}CounterDefinitions for {1}{2}", rootFilename, activeSectionLabel.ToUpper(), asic.ToUpper());
            hsw.WriteLine("//==============================================================================");
            hsw.WriteLine();
            hsw.WriteLine("#ifndef _{0}_COUNTER_DEFS_{1}{2}_H_", rootFilename.ToUpper(), activeSectionLabel.ToUpper(), asic.ToUpper());
            hsw.WriteLine("#define _{0}_COUNTER_DEFS_{1}{2}_H_", rootFilename.ToUpper(), activeSectionLabel.ToUpper(), asic.ToUpper());
            hsw.WriteLine();

            if (isInternal)
            {
                hsw.WriteLine("#ifdef AMDT_INTERNAL");
                hsw.WriteLine();
            }

            hsw.WriteLine(
                "//*** Note, this is an auto-generated file. Do not edit. Execute {0}CounterCompiler to rebuild.", rootFilename);
            hsw.WriteLine();
            hsw.WriteLine("#include \"GPADerivedCounters.h\"");
            hsw.WriteLine();

            if (!asicSpecific)
            {
                hsw.WriteLine("/// Defines the {0} derived counters for {1}{2}", rootFilename.ToLower(), activeSectionLabel.ToUpper(), asic.ToUpper());
                hsw.WriteLine("/// \\param c derived counters instance");
                hsw.WriteLine("void AutoDefine{0}DerivedCounters{1}(GPA_DerivedCounters& c);", rootFilename, activeSectionLabel);
            }
            else
            {
                hsw.WriteLine("namespace {0}{1}", activeSectionLabel, asic);
                hsw.WriteLine("{");
                hsw.WriteLine();
                hsw.WriteLine("/// Updates default GPU generation {0} derived counters with ASIC specific versions if available.", rootFilename.ToLower());
                hsw.WriteLine("/// \\param desiredGeneration Hardware generation currently in use.");
                hsw.WriteLine("/// \\param asicType The ASIC type that is currently in use.");
                hsw.WriteLine("/// \\param c Derived counters instance.");
                hsw.WriteLine("/// \\return True if the ASIC matched one available, and derivedCounters was updated.");
                hsw.WriteLine("extern bool Update{0}AsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c);", rootFilename);
                hsw.WriteLine();
                hsw.WriteLine("} //" + activeSectionLabel + asic);
            }

            hsw.WriteLine();

            if (isInternal)
            {
                hsw.WriteLine("#endif // AMDT_INTERNAL");
                hsw.WriteLine();
            }

            hsw.WriteLine("#endif // _PUBLIC_COUNTER_DEFS_{0}{1}_H_", activeSectionLabel.ToUpper(), asic.ToUpper());
            hsw.Close();

            string cppFilename = string.Format("{0}{1}CounterDefs{2}{3}.cpp", outputDir, rootFilename, activeSectionLabel, asic);

            // Write cpp file
            Output("Writing cpp to " + cppFilename);
            StreamWriter csw = null;
            try
            {
                csw = new StreamWriter(cppFilename);
            }
            catch
            {
                Output("ERROR: Failed to open file for writing: " + filename);
                return false;
            }

            csw.WriteLine("//==============================================================================");
            csw.WriteLine("// Copyright (c) 2010-{0} Advanced Micro Devices, Inc. All rights reserved.",
                DateTime.Today.Year);
            csw.WriteLine("/// \\author AMD Developer Tools Team");
            csw.WriteLine("/// \\file");
            csw.WriteLine("/// \\brief {0}CounterDefinitions for {1}{2}", rootFilename, activeSectionLabel.ToUpper(), asic.ToUpper());
            csw.WriteLine("//==============================================================================");
            csw.WriteLine();

            if (isInternal)
            {
                csw.WriteLine("#ifdef AMDT_INTERNAL");
                csw.WriteLine();
            }

            csw.WriteLine("#include \"GPAInternalCounter.h\"");
            csw.WriteLine("#include \"{0}CounterDefs{1}{2}.h\"", rootFilename, activeSectionLabel, asic);
            csw.WriteLine();
            csw.WriteLine(
                "// *** Note, this is an auto-generated file. Do not edit. Execute {0}CounterCompiler to rebuild.", rootFilename);
            csw.WriteLine();

            if (!asicSpecific)
            {
                csw.WriteLine("void AutoDefine{0}DerivedCounters{1}{2}(GPA_DerivedCounters& c)", rootFilename, activeSectionLabel, asic);
                csw.WriteLine("{");
            }
            else
            {
                csw.WriteLine("#include \"GPAInternalCounters{0}{1}.h\"", generation, asic);
                csw.WriteLine();
                csw.WriteLine("namespace {0}{1}", activeSectionLabel, asic);
                csw.WriteLine("{");
                csw.WriteLine();
                csw.WriteLine("bool Update{0}AsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)", rootFilename);
                csw.WriteLine("{");
                csw.WriteLine("    UNREFERENCED_PARAMETER(desiredGeneration);");
                csw.WriteLine("    UNREFERENCED_PARAMETER(c); // Unreferenced if there are no ASIC specific block instance registers");
                csw.WriteLine();
                csw.WriteLine("    if (!Counter{0}{1}::MatchAsic(asicType))", generation, asic);
                csw.WriteLine("    {");
                csw.WriteLine("        return false;");
                csw.WriteLine("    }");
                csw.WriteLine();
                csw.WriteLine("    Counter{0}{1}::OverrideBlockInstanceCounters(asicType);", generation, asic);
                csw.WriteLine();
            }

            StreamWriter lsw = null;

            if (!string.IsNullOrEmpty(counterListOutputDirectory))
            {
                string listFilename = string.Format("{0}{1}CounterNameList{2}{3}.txt", counterListOutputDirectory, rootFilename, activeSectionLabel, asic);

                Output("Writing counter name list to " + listFilename);
                try
                {
                    lsw = new StreamWriter(listFilename);
                }
                catch
                {
                    Output("ERROR: Failed to open file for writing: " + filename);
                    return false;
                }
            }

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

                csw.WriteLine("    {");
                csw.WriteLine("        vector< gpa_uint32 > internalCounters;");
                foreach (DerivedCounterDef.HardwareCounterDef counter in c.GetCounters())
                {
                    csw.WriteLine("        internalCounters.push_back({0});", counter.Id);
                }

                csw.WriteLine();

                if (!asicSpecific)
                {
                    csw.WriteLine(
                    "        c.DefineDerivedCounter(\"{0}\", \"{1}\", \"{2}\", {3}, {4}, internalCounters, \"{5}\", \"{6}\");",
                    c.Name, c.Group, c.Desc, c.Type, c.Usage, c.Comp, c.GuidHash.ToString("D"));
                }
                else
                {
                    csw.WriteLine(
                    "        c.UpdateAsicSpecificDerivedCounter(\"{0}\", internalCounters, \"{1}\");",
                    c.Name, c.Comp);
                }

                csw.WriteLine("    }");
            }

            if (!asicSpecific)
            {
                csw.WriteLine("}");
                csw.WriteLine();
            }
            else
            {
                csw.WriteLine("    return true;");
                csw.WriteLine();
                csw.WriteLine("}");
                csw.WriteLine();
                csw.WriteLine("} // " + activeSectionLabel + asic);
                csw.WriteLine();
            }

            if (isInternal)
            {
                csw.WriteLine("#endif // AMDT_INTERNAL");
                csw.WriteLine();
            }

            csw.Close();

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
        /// <param name="activeSectionLabel">Counter section (GL/DX/...)</param>
        /// <param name="testOutputDirectory">Directory that will contain output test files</param>
        /// <param name="asic">Specific ASIC, or empty string.</param>
        /// <returns>True if files are successfully generated.</returns>
        public static bool GenerateTestOutputFiles(
            ref List<InternalCounterDef> internalCounterList,
            ref List<DerivedCounterDef> counterDefList,
            string rootFilename,
            string activeSectionLabel,
            string testOutputDirectory,
            string asic)
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

            if (testOutputDirectory.Length > 0 && !testOutputDirectory.EndsWith("\\"))
            {
                testOutputDirectory = testOutputDirectory + "\\";
            }

            string derivedCounterFileNamePrefix = rootFilename + "DerivedCounters";
            string headerFileName = string.Format("{0}{1}{2}.h", derivedCounterFileNamePrefix, activeSectionLabel, asic);
            string headerFilePath = string.Format("{0}{1}", testOutputDirectory, headerFileName);
            string cppFilePath = string.Format("{0}{1}{2}{3}.cpp", testOutputDirectory, derivedCounterFileNamePrefix,
                activeSectionLabel, asic);
            Output("Writing header to " + cppFilePath);
            StreamWriter cppStream = null;
            try
            {
                cppStream = new StreamWriter(cppFilePath);
            }
            catch
            {
                Output("ERROR: Failed to open file for writing: " + cppFilePath);
                return false;
            }

            cppStream.WriteLine("//==============================================================================");
            cppStream.WriteLine("// Copyright (c) 2015-{0} Advanced Micro Devices, Inc. All rights reserved.",
                DateTime.Today.Year);
            cppStream.WriteLine("/// \\author AMD Developer Tools Team");
            cppStream.WriteLine("/// \\file");
            cppStream.WriteLine("/// \\brief {0}CounterDefinitions for {1}{2} for testing", rootFilename, activeSectionLabel, asic);
            cppStream.WriteLine("//==============================================================================");
            cppStream.WriteLine();
            cppStream.WriteLine(
                "// *** Note, this is an auto-generated file. Do not edit. Execute {0}CounterCompiler to rebuild.", rootFilename);
            cppStream.WriteLine();
            cppStream.WriteLine("#include \"{0}\"", headerFileName);
            cppStream.WriteLine();
            string derivedCountersConstant = activeSectionLabel.ToUpper() + asic.ToUpper() + "_" + rootFilename.ToUpper() + "_COUNTERS";
            string derivedCounterCountConstant = activeSectionLabel.ToUpper() + asic.ToUpper() + "_" + rootFilename.ToUpper() + "_COUNTER_COUNT";
            cppStream.WriteLine("const GPACounterDesc {0}[{1}] =", derivedCountersConstant, derivedCounterCountConstant);
            cppStream.WriteLine("{");
            int counterCount = 0;

            Output("Writing header to " + headerFilePath);
            StreamWriter headerStream = null;
            try
            {
                headerStream = new StreamWriter(headerFilePath);
            }
            catch
            {
                Output("ERROR: Failed to open file for writing: " + headerFilePath);
                return false;
            }

            headerStream.WriteLine("//==============================================================================");
            headerStream.WriteLine("// Copyright (c) 2015-{0} Advanced Micro Devices, Inc. All rights reserved.",
                DateTime.Today.Year);
            headerStream.WriteLine("/// \\author AMD Developer Tools Team");
            headerStream.WriteLine("/// \\file");
            headerStream.WriteLine("/// \\brief {0}CounterDefinitions for {1} for testing", rootFilename, activeSectionLabel.ToUpper());
            headerStream.WriteLine("//==============================================================================");
            headerStream.WriteLine();
            headerStream.WriteLine(
                "// *** Note, this is an auto-generated file. Do not edit. Execute {0}CounterCompiler to rebuild.", rootFilename);
            headerStream.WriteLine();
            string headerGuard = "_GPA_TESTS_COUNTERS_" + rootFilename.ToUpper() + "_" + activeSectionLabel.ToUpper() + asic.ToUpper() + "_";
            headerStream.WriteLine("#ifndef {0}", headerGuard);
            headerStream.WriteLine("#define {0}", headerGuard);
            headerStream.WriteLine();
            headerStream.WriteLine("#include \"GPACounterDesc.h\"");
            headerStream.WriteLine();
            headerStream.WriteLine("/// Macros for {0}{1} {2} counter index", activeSectionLabel, asic, rootFilename);

            int counterIndex = 0;
            foreach (DerivedCounterDef publicCounter in counterDefList)
            {
                ++counterCount;
                cppStream.WriteLine("    {{\"{0}\", \"{1}\", \"{2}\", {3}, {4}, {5}}},", publicCounter.Name,
                    publicCounter.Group, publicCounter.Desc, publicCounter.Type, publicCounter.Usage, publicCounter.GuidHash.ToString("X").Replace(",", ", "));
                headerStream.WriteLine("#define {0}{1}{2}{3} {4}", publicCounter.Name, rootFilename, activeSectionLabel, asic, counterIndex);
                counterIndex++;
            }

            cppStream.WriteLine("};");
            cppStream.WriteLine();
            cppStream.Close();

            headerStream.WriteLine();
            headerStream.WriteLine("/// Number of public counters for {0}{1}", activeSectionLabel, asic);
            headerStream.WriteLine("static const size_t {0} = {1};", derivedCounterCountConstant, counterCount);
            headerStream.WriteLine();
            headerStream.WriteLine("/// Array of public counters for {0}{1}", activeSectionLabel, asic);
            headerStream.WriteLine("extern const GPACounterDesc {0}[{1}];", derivedCountersConstant,
                derivedCounterCountConstant);
            headerStream.WriteLine();
            headerStream.WriteLine("#endif // {0}", headerGuard);
            headerStream.Close();
            return true;
        }

        /// <summary>
        /// Start the process of collecting information for RST documentation
        /// </summary>
        public static void StartRSTDocumentation()
        {
            docInfoMapGraphics.Clear();
            docInfoMapCompute.Clear();
        }

        /// <summary>
        /// Writes a counter table to the specified stream
        /// </summary>
        /// <param name="docStream">the stream in which to write data</param>
        /// <param name="groupKvp">the data to use to write the counter data</param>
        private static void WriteRSTCounterTable(StreamWriter docStream, KeyValuePair<string, Dictionary<string, PublicCounterDocInfo>> groupKvp)
        {
            docStream.WriteLine();
            string groupHeading = string.Format("{0} Group", groupKvp.Key);
            docStream.WriteLine(groupHeading);
            docStream.WriteLine(new String('%', groupHeading.Length));
            docStream.WriteLine();
            docStream.WriteLine(".. csv-table::");
            docStream.WriteLine("    :header: \"Counter Name\", \"Brief Description\", \"Availability\"");
            docStream.WriteLine("    :widths: 15, 60, 25");
            docStream.WriteLine();

            foreach (KeyValuePair<string, PublicCounterDocInfo> counterKvp in groupKvp.Value)
            {
                string hwGens = string.Empty;

                if (counterKvp.Value.gfx9Supported)
                {
                    hwGens += "| Vega";
                }

                if (counterKvp.Value.gfx8Supported)
                {
                    if (hwGens != string.Empty)
                    {
                        hwGens += "\r\n    ";
                    }

                    hwGens += "| Graphics IP v8";
                }
                if (counterKvp.Value.gfx7Supported)
                {
                    if (hwGens != string.Empty)
                    {
                        hwGens += "\r\n    ";
                    }

                    hwGens += "| Graphics IP v7";
                }
                if (counterKvp.Value.gfx6Supported)
                {
                    if (hwGens != string.Empty)
                    {
                        hwGens += "\r\n    ";
                    }

                    hwGens += "| Graphics IP v6";
                }

                docStream.WriteLine("    \"{0}\", \"{1}\", \"{2}\"", counterKvp.Key, counterKvp.Value.publicCounter.Desc, hwGens);
            }
        }


        /// <summary>
        /// Finish the process of collecting information for RST documentation. This will write the data to files.
        /// </summary>
        public static void DoneRSTDocumentation()
        {
            string docOutputFile = GetGPABasePath() + "docs\\source\\graphicscountertables.rst";

            StreamWriter docStream = null;
            try
            {
                docStream = new StreamWriter(docOutputFile);
            }
            catch
            {
                Output("ERROR: Failed to open file for writing: " + docOutputFile);
                return;
            }

            docStream.WriteLine(".. Copyright(c) 2018 Advanced Micro Devices, Inc.All rights reserved.");
            docStream.WriteLine(".. Graphics Performance Counters");
            docStream.WriteLine();
            docStream.WriteLine(".. *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.");

            foreach (KeyValuePair<string, Dictionary<string, PublicCounterDocInfo>> groupKvp in docInfoMapGraphics)
            {
                WriteRSTCounterTable(docStream, groupKvp);
            }

            docStream.Close();

            docOutputFile = GetGPABasePath() + "docs\\source\\computecountertables.rst";

            docStream = null;
            try
            {
                docStream = new StreamWriter(docOutputFile);
            }
            catch
            {
                Output("ERROR: Failed to open file for writing: " + docOutputFile);
                return;
            }

            docStream.WriteLine(".. Copyright(c) 2018 Advanced Micro Devices, Inc.All rights reserved.");
            docStream.WriteLine(".. Compute Performance Counters");

            foreach (KeyValuePair<string, Dictionary<string, PublicCounterDocInfo>> groupKvp in docInfoMapCompute)
            {
                WriteRSTCounterTable(docStream, groupKvp);
            }

            docStream.Close();
        }
    }
}
