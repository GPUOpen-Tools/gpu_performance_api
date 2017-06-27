// =====================================================================
// <copyright file="Program.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//    Given an ordered internal counter definition file and the public counter definitions,
//    produces c++ code to define them for the run-time.
// </summary>
// =====================================================================
namespace PublicCounterCompiler
{
   using System;
   using System.Collections.Generic;
   using System.IO;
   using System.Text;
   using System.Windows.Forms;

   /// <summary>
   /// A program which compiles the public counters definitions into C++ files.
   /// </summary>
   public class Program
   {
      /// <summary>
      /// Indicates if this app is being run as a console app (true) or UI app (false)
      /// </summary>
      private static bool isConsoleApp = true;

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
      /// Sets directories based on the supplied API and generation and
      /// compiles the public counters
      /// </summary>
      /// <param name="api">The API to compile counters for</param>
      /// <param name="generation">The HW </param>
      /// <returns>true on success, false if there were any errors</returns>
      public static bool CompileCounters(string api, string generation)
      {
         // calculate the proper path to output to
         string CompilerOutputFolder = "Output\\";
         int endPath = Application.StartupPath.IndexOf(CompilerOutputFolder) + CompilerOutputFolder.Length;

         if (CompilerOutputFolder.Length == endPath)
         {
            Output(Application.ProductName + " was started out of unexpected folder.");
            return false;
         }

         string gpaPath = Application.StartupPath.Substring(0, endPath - CompilerOutputFolder.Length);
         string compilerInputPath = gpaPath + "Src\\PublicCounterCompilerInputFiles\\";
		 
         // file names
         string counterNamesFile = compilerInputPath + "CounterNames" + api + generation + ".txt";
         string suffix;
         if (api == "CL")
         {
            suffix = "CL";
         }
         else if (api == "HSA")
         {
            suffix = "HSA";
         }
         else
         {
            suffix = string.Empty;
         }

         string counterDefsFile = compilerInputPath + "PublicCounterDefinitions" + suffix + generation + ".txt";
         string outputDirectory = gpaPath + "Src\\GPUPerfAPICounterGenerator\\";
         string counterListOutputDirectory = gpaPath + "Output\\CounterListFiles\\";
         string testOutputDirectory = gpaPath + "Src\\GPUPerfAPIUnitTests\\counters\\";
         string section = api + generation;

         ////if (MessageBox.Show("CounterNamesFile: " + counterNamesFile + Environment.NewLine +
         ////                      "Counter Defs    : " + counterDefsFile + Environment.NewLine +
         ////                      "Output Folder   : " + outputDirectory + Environment.NewLine +
         ////                      "Section Label   : " + section + Environment.NewLine + Environment.NewLine +
         ////                      "Is this correct?") == DialogResult.Cancel)
         ////{
         ////   return false;
         ////}

         string strError;
         if (LoadFilesAndGenerateOutput(counterNamesFile, counterDefsFile, outputDirectory, counterListOutputDirectory, testOutputDirectory, section, out strError) == false)
         {
            Output(strError);
            return false;
         }
         else
         {
            Output("Success!" + Environment.NewLine + Environment.NewLine +
                   "PublicCounterDefs" + section + ".cpp / .h written out to:" + Environment.NewLine +
                   outputDirectory);
            return true;
         }
      }

      /// <summary>
      ///
      /// </summary>
      /// <param name="counterNamesFile"></param>
      /// <param name="counterDefsFile"></param>
      /// <param name="outputDir"></param>
      /// <param name="counterListOutputDirectory"></param>
      /// <param name="testOutputDirectory"></param>
      /// <param name="sectionLabel"></param>
      /// <param name="strError"></param>
      /// <returns></returns>
      public static bool LoadFilesAndGenerateOutput(string counterNamesFile, string counterDefsFile, string outputDir, string counterListOutputDirectory, string testOutputDirectory, string sectionLabel, out string strError)
      {
         // load the internal counters using filename in first param
         List<InternalCounterDef> internalCounterList = new List<InternalCounterDef>();
         bool readOk = LoadInternalCounters(counterNamesFile, ref internalCounterList, out strError);
         if (!readOk)
         {
            strError = "Error reading counter name file (" + counterNamesFile + ").\n" + strError;
            return false;
         }

         Output("Read " + internalCounterList.Count + " internal counters from " + counterNamesFile + ".");

         // load the public counter definitions using the filename in the second param
         List<PublicCounterDef> publicCounterList = new List<PublicCounterDef>();
         readOk = LoadPublicCounterDefinitions(counterDefsFile, ref publicCounterList, ref internalCounterList, sectionLabel, out strError);
         if (!readOk)
         {
            strError = "Error processing public counter file (" + counterDefsFile + ").\n" + strError;
            return false;
         }

         if (publicCounterList.Count == 0)
         {
            strError = "Error: 0 counters were exposed by the counter definitions file.";
            return false;
         }
         else
         {
            Output("Read " + publicCounterList.Count + " public counters from " + counterDefsFile + ".");
         }

         if (GenerateOutputFiles(ref internalCounterList, ref publicCounterList, sectionLabel, outputDir, counterListOutputDirectory) == false)
         {
            return false;
         }
         else
         {
             bool genTestOutputFilesStatus = GenerateTestOutputFiles(ref internalCounterList, ref publicCounterList, sectionLabel, testOutputDirectory);
             if (false == genTestOutputFilesStatus)
             {
                 Output("Failed to generate output test files for " + sectionLabel);
             }
         }

         strError = string.Empty;
         return true;
      }

      /// <summary>
      /// Load a list of counter name from the specified file (expecting one name per line, order implies counters index)
      /// Format is: number , name , type
      /// </summary>
      /// <param name="file"></param>
      /// <param name="internalCounterList"></param>
      /// <param name="strError"></param>
      /// <returns></returns>
      public static bool LoadInternalCounters(string file, ref List<InternalCounterDef> internalCounterList, out string strError)
      {
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

         int lineNum = 0;
         foreach (string s in publicCounterDefs)
         {
            if (s.Length == 0)
            {
               continue;
            }

            if (s.Contains("="))
            {
               strError = "Error: Internal counter names may not contain = symbols. Change the counter name or change PCC public counter parsing to support = in names.";
               return false;
            }

            string[] counterText = s.Split(',');
            if (counterText.Length != 3 && counterText.Length != 2)
            {
               strError = "Error: Problem reading internal counter definition. Format is either: 'number , name , type' or 'name , type'. Line='" + s + "'";
               return false;
            }

            int counterNumber;
            if (counterText.Length == 3)
            {
               System.Int32.TryParse(counterText[0], out counterNumber);
               if (counterNumber != lineNum)
               {
                  strError = "Error: internal counter numbers defined out of sequence. Line='" + s + "'";
                  return false;
               }

               InternalCounterDef newDef = new InternalCounterDef();
               newDef.Name = counterText[1].Trim();
               newDef.Type = counterText[2].Trim();
               internalCounterList.Add(newDef);
            }
            else
            {
               InternalCounterDef newDef = new InternalCounterDef();
               newDef.Name = counterText[0].Trim();
               newDef.Type = counterText[1].Trim();
               internalCounterList.Add(newDef);
            }

            lineNum++;
         }

         strError = string.Empty;
         return true;
      }

      /// <summary>
      /// Get the index of a string in a list (case insensitive)
      /// </summary>
      /// <param name="counterName"></param>
      /// <param name="internalCounterList"></param>
      /// <param name="index"></param>
      /// <returns></returns>
      public static bool GetCounterIndex(string counterName, ref List<InternalCounterDef> internalCounterList, out int index)
      {
         index = 0;
         foreach (InternalCounterDef c in internalCounterList)
         {
            if (c.Name.Equals(counterName, StringComparison.OrdinalIgnoreCase))
            {
               return true;
            }

            index++;
         }

         return false;
      }

      /// <summary>
      /// Given the counter name list, create a list of CounterDefinitions using definitions in the specified file.
      /// </summary>
      /// <param name="file"></param>
      /// <param name="counterDefList">expected to be empty on first call</param>
      /// <param name="internalCounterList"></param>
      /// <param name="activeSectionLabel"></param>
      /// <param name="strError"></param>
      /// <returns></returns>
      public static bool LoadPublicCounterDefinitions(string file, ref List<PublicCounterDef> counterDefList, ref List<InternalCounterDef> internalCounterList, string activeSectionLabel, out string strError)
      {
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

         bool insideMatchingSection = false;
         bool doneMatchingSection = false;
         bool doneUsage = false;
         bool doneName = false;
         bool doneComp = true;

         uint numInvalidCounterNames = 0;

         PublicCounterDef counterDef = null;

         foreach (string s in publicCounterDefs)
         {
            if (s.Length == 0)
            {
               continue;
            }

            if (s.StartsWith(";"))
            {
               continue;
            }

            if (s.StartsWith("#include"))
            {
               string pathToFile = Path.GetDirectoryName(file);
               string includeFile = s.Substring(8);
               includeFile = includeFile.Trim();
               includeFile = pathToFile + "\\" + includeFile;
               bool loadedInclude = LoadPublicCounterDefinitions(includeFile, ref counterDefList, ref internalCounterList, activeSectionLabel, out strError);
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
                  if (counterDef != null && doneComp == false)
                  {
                     Output("Warning: no comp found for " + activeSectionLabel + ", will not expose counter for: " + counterDef.Name);
                  }

                  if (lineSplit[1].Length == 0)
                  {
                     strError = "Error: name definition empty. Line='" + s + "'";
                     return false;
                  }

                  counterDef = new PublicCounterDef();
                  counterDef.CounterType = "GPA_COUNTER_TYPE_DYNAMIC";
                  counterDef.Name = lineSplit[1];

                  doneName = true;
                  insideMatchingSection = false;
                  doneMatchingSection = false;
                  doneComp = false;
               }
               else if (lineSplit[0].Equals("desc", StringComparison.OrdinalIgnoreCase))
               {
                  if (!doneName)
                  {
                     strError = "Error: name= should appear before desc=. Line='" + s + "'";
                     return false;
                  }

                  counterDef.Desc = lineSplit[1];
               }
               else if (lineSplit[0].Equals("type", StringComparison.OrdinalIgnoreCase))
               {
                  if (!doneName)
                  {
                     strError = "Error: name= should appear before type=. Line='" + s + "'";
                     return false;
                  }

                  // map input type to a GPA type
                  if (lineSplit[1].Equals("gpa_float32", StringComparison.OrdinalIgnoreCase))
                  {
                     counterDef.Type = "GPA_TYPE_FLOAT32";
                  }
                  else if (lineSplit[1].Equals("gpa_float64", StringComparison.OrdinalIgnoreCase))
                  {
                     counterDef.Type = "GPA_TYPE_FLOAT64";
                  }
                  else if (lineSplit[1].Equals("gpa_uint32", StringComparison.OrdinalIgnoreCase))
                  {
                     counterDef.Type = "GPA_TYPE_UINT32";
                  }
                  else if (lineSplit[1].Equals("gpa_uint64", StringComparison.OrdinalIgnoreCase))
                  {
                     counterDef.Type = "GPA_TYPE_UINT64";
                  }
                  else if (lineSplit[1].Equals("gpa_int32", StringComparison.OrdinalIgnoreCase))
                  {
                     counterDef.Type = "GPA_TYPE_INT32";
                  }
                  else if (lineSplit[1].Equals("gpa_int64", StringComparison.OrdinalIgnoreCase))
                  {
                     counterDef.Type = "GPA_TYPE_INT64";
                  }
                  else
                  {
                     strError = "Error: type not recognized. Check what you have entered, and also that PCC handles all relevant types. Line='" + s + "'";
                     return false;
                  }
               }
               else if (lineSplit[0].Equals("usage", StringComparison.OrdinalIgnoreCase))
               {
                  if (!doneName)
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
                  else if (lineSplit[1].Equals("milliseconds", StringComparison.OrdinalIgnoreCase))
                  {
                     counterDef.Usage = "GPA_USAGE_TYPE_MILLISECONDS";
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
                     strError = "Error: usage not recognized. Check what you have entered, and also that PublicCounterCompiler handles all relevant types. Line='" + s + "'";
                     return false;
                  }

                  doneUsage = true;
               }
               else if (lineSplit[0].Equals("countertype", StringComparison.OrdinalIgnoreCase))
               {
                  counterDef.CounterType = String.Copy(lineSplit[1]);
               }
               else if (lineSplit[0].Equals("comp", StringComparison.OrdinalIgnoreCase))
               {
                  if (insideMatchingSection == false &&
                       doneMatchingSection == false)
                  {
                     // aren't finishing the matching section and we haven't done it yet, so just ignore this comp
                     continue;
                  }

                  if (doneComp)
                  {
                     // already done the comp for this counter, so skip this one
                     continue;
                  }

                  if (!doneUsage)
                  {
                     strError = "Error: comp= encountered before usage=. Ensure usage= appears before comp=. Line='" + s + "'";
                     return false;
                  }

                  if (!doneName)
                  {
                     strError = "Error: comp= encountered before name=. Ensure name and optional description appear before comp=. Line='" + s + "'";
                     return false;
                  }

                  if (counterDef.GetCounterCount() == 0)
                  {
                     strError = "Error: No counters defined before comp encountered. Ensure at least one counter appears before comp. Line='" + s + "'";
                     return false;
                  }

                  string computation = lineSplit[1];
                  if (computation.Contains(".."))
                  {
                     // if the computation contains a range, find it, then expand the values into a string and rewrite the computation.
                     string[] compParts = computation.Split(',');

                     // clear the computation so that we can rebuild it
                     computation = string.Empty;

                     foreach (string part in compParts)
                     {
                        if (computation.Length > 0 && computation.EndsWith(",") == false)
                        {
                           computation += ",";
                        }

                        if (part.Contains(".."))
                        {
                           List<int> values = ExpandEllipses(part);
                           foreach (int value in values)
                           {
                              computation += value + ",";
                           }
                        }
                        else
                        {
                           computation += part;
                        }
                     }
                  }

                  counterDef.Comp = computation;
                  counterDefList.Add(counterDef);
                  doneComp = true;
                  doneUsage = false;
               }
            }
            else
            {
               // must be an internal counter name
               if (!doneName)
               {
                  strError = "Error: Encountered text [" + s + "] (maybe counter name) before a name= line after " + counterDef.Name + ". Check order of definitions.";
                  return false;
               }

               // determine if we are inside a matching section
               if (lineSplit[0].StartsWith("["))
               {
                  // found section label
                  if (insideMatchingSection)
                  {
                     if (counterDef.GetCounterCount() > 0)
                     {
                        // if was already in matching section close it
                        doneMatchingSection = true;
                        insideMatchingSection = false;
                     }
                  }

                  if (!insideMatchingSection)
                  {
                     // looking for specific section label, check for match
                     if (string.Equals(lineSplit[0], "[" + activeSectionLabel + "]", StringComparison.OrdinalIgnoreCase))
                     {
                        // hit the section to use
                        insideMatchingSection = true;
                     }
                     else
                     {
                        insideMatchingSection = false;
                     }
                  }

                  // done the section label
                  continue;
               }

               if (!insideMatchingSection)
               {
                  // just ignore this counter
                  continue;
               }

               // add the current internal counter to the current public counter definition
               int index;

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

                  // iterate through each value and add the corresponding counter
                  string[] rangeValues = rangeContents.Split(',');
                  foreach (string valueString in rangeValues)
                  {
                     List<int> values = ExpandEllipses(valueString);

                     foreach (int value in values)
                     {
                        curLineCounterNames.Add(counterNameBase.Replace("*", value.ToString()));
                     }
                  }
               }
               else
               {
                  curLineCounterNames.Add(lineSplit[0]);
               }

               // now add each of the internal counters on this line to the list for the current public counter.
               foreach(string counterName in curLineCounterNames)
               {
                  if (GetCounterIndex(counterName, ref internalCounterList, out index))
                  {
                     if (counterDef.CounterDefined(index))
                     {
                        strError = "Error: Counter named '" + counterDef.Name + "' has a duplicate counter definition '" + s + "'.";
                        return false;
                     }

                     counterDef.AddCounter(index);
                  }
                  else
                  {
                     Output("Warning: Counter not recognized " + s + ". Compare this spelling to the counter names file to see which is incorrect.");
                     counterDef.AddCounter(-1);
                     numInvalidCounterNames++;

                     if (IgnoreInvalidCounters())
                     {
                        // set state as if we did the comp already, this will prevent us from actually
                        // adding the counter to the list of exposed counters
                        doneComp = true;
                     }
                  }
               }
            }
         }

         // if we were trying to define a counter, but never did a comp for it, output a warning since the counter will not be generated
         if (counterDef != null && doneComp == false)
         {
            Output("Warning: no comp found for " + activeSectionLabel + ", will not expose counter for: " + counterDef.Name);
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
      /// <summary>
      ///
      /// </summary>
      /// <param name="internalCounterList"></param>
      /// <param name="counterDefList"></param>
      /// <param name="activeSectionLabel"></param>
      /// <param name="outputDir"></param>
      /// <param name="counterListOutputDirectory"></param>
      /// <returns>True if the files could be generated; false on error.</returns>
      public static bool GenerateOutputFiles(ref List<InternalCounterDef> internalCounterList, ref List<PublicCounterDef> counterDefList, string activeSectionLabel, string outputDir, string counterListOutputDirectory)
      {
         if (outputDir.Length > 0 && !outputDir.EndsWith("\\"))
         {
            outputDir = outputDir + "\\";
         }

         if (counterListOutputDirectory.Length > 0 && !counterListOutputDirectory.EndsWith("\\"))
         {
            counterListOutputDirectory = counterListOutputDirectory + "\\";
         }

         Directory.CreateDirectory(counterListOutputDirectory);

         string filename = string.Format("{0}PublicCounterDefs{1}.h", outputDir, activeSectionLabel);
         string listFilename = string.Format("{0}PublicCounterNameList{1}.txt", counterListOutputDirectory, activeSectionLabel);

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
         hsw.WriteLine("// Copyright (c) 2010-{0} Advanced Micro Devices, Inc. All rights reserved.", DateTime.Today.Year);
         hsw.WriteLine("/// \\author AMD Developer Tools Team");
         hsw.WriteLine("/// \\file");
         hsw.WriteLine("/// \\brief  PublicCounterDefinitions for {0}", activeSectionLabel.ToUpper());
         hsw.WriteLine("//==============================================================================");
         hsw.WriteLine();
         hsw.WriteLine("#ifndef _PUBLIC_COUNTER_DEFS_{0}_H_", activeSectionLabel.ToUpper());
         hsw.WriteLine("#define _PUBLIC_COUNTER_DEFS_{0}_H_", activeSectionLabel.ToUpper());
         hsw.WriteLine();
         hsw.WriteLine("//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.");
         hsw.WriteLine();
         hsw.WriteLine("#include \"GPAPublicCounters.h\"");
         hsw.WriteLine();
         hsw.WriteLine("/// Defines the public counters for {0}", activeSectionLabel.ToUpper());
         hsw.WriteLine("/// \\param p pubilc counters instance");
         hsw.WriteLine("void AutoDefinePublicCounters{0}(GPA_PublicCounters& p);", activeSectionLabel);
         hsw.WriteLine();
         hsw.WriteLine("#endif // _PUBLIC_COUNTER_DEFS_{0}_H_", activeSectionLabel.ToUpper());
         hsw.Close();

         string cppFilename = string.Format("{0}PublicCounterDefs{1}.cpp", outputDir, activeSectionLabel);

         // Write cpp file
         Output("Writing cpp to " + cppFilename);
         StreamWriter csw = new StreamWriter(cppFilename);
         csw.WriteLine("//==============================================================================");
         csw.WriteLine("// Copyright (c) 2010-{0} Advanced Micro Devices, Inc. All rights reserved.", DateTime.Today.Year);
         csw.WriteLine("/// \\author AMD Developer Tools Team");
         csw.WriteLine("/// \\file");
         csw.WriteLine("/// \\brief  PublicCounterDefinitions for {0}", activeSectionLabel.ToUpper());
         csw.WriteLine("//==============================================================================");
         csw.WriteLine();
         csw.WriteLine("#include \"PublicCounterDefs{0}.h\"", activeSectionLabel);
         csw.WriteLine();
         csw.WriteLine("// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.");
         csw.WriteLine();
         csw.WriteLine("void AutoDefinePublicCounters{0}(GPA_PublicCounters& p)", activeSectionLabel);
         csw.WriteLine("{");

         Output("Writing counter name list to " + listFilename);
         StreamWriter lsw = new StreamWriter(listFilename);

         foreach (PublicCounterDef c in counterDefList)
         {
            lsw.WriteLine("{0} - {1}", c.Name, c.Desc);

            csw.WriteLine("    {");
            csw.WriteLine("        vector< gpa_uint32 > internalCounters;");
            foreach (int i in c.GetCounters())
            {
               csw.WriteLine("        internalCounters.push_back({0});", i);
            }

            csw.WriteLine();
            csw.WriteLine("        p.DefinePublicCounter(\"{0}\", \"{1}\", {2}, {3}, {5}, internalCounters, \"{4}\");", c.Name, c.Desc, c.Type, c.Usage, c.Comp, c.CounterType);
            csw.WriteLine("    }");
         }

         csw.WriteLine("}");
         csw.WriteLine();

         csw.Close();

         lsw.Close();

         return true;
      }

      /// <summary>
      /// Generate the test output file
      /// </summary>
      /// <param name="internalCounterList">List of internal counters</param>
      /// <param name="counterDefList">List of public counters</param>
      /// <param name="activeSectionLabel">Counter section (GL/DX/...)</param>
      /// <param name="outputDir">Directory that will contain output test files</param>
      /// <returns></returns>
      public static bool GenerateTestOutputFiles(ref List<InternalCounterDef> internalCounterList, ref List<PublicCounterDef> counterDefList, string activeSectionLabel, string outputDir)
      {
          if (outputDir.Length > 0 && !outputDir.EndsWith("\\"))
          {
              outputDir = outputDir + "\\";
          }

          const string publicCounterFileNamePrefix = "PublicCounters";
          string headerFileName = string.Format("{0}{1}.h", publicCounterFileNamePrefix, activeSectionLabel);
          string headerFilePath = string.Format("{0}{1}", outputDir, headerFileName);
          string cppFilePath = string.Format("{0}{1}{2}.cpp", outputDir, publicCounterFileNamePrefix, activeSectionLabel);
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
          cppStream.WriteLine("// Copyright (c) 2015-{0} Advanced Micro Devices, Inc. All rights reserved.", DateTime.Today.Year);
          cppStream.WriteLine("/// \\author AMD Developer Tools Team");
          cppStream.WriteLine("/// \\file");
          cppStream.WriteLine("/// \\brief  PublicCounterDefinitions for {0} for testing", activeSectionLabel.ToUpper());
          cppStream.WriteLine("//==============================================================================");
          cppStream.WriteLine();
          cppStream.WriteLine("// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.");
          cppStream.WriteLine();
          cppStream.WriteLine("#include \"{0}\"", headerFileName);
          cppStream.WriteLine();
          string publicCountersConstant = activeSectionLabel.ToUpper() + "_PUBLIC_COUNTERS";
          string publicCounterCountConstant = activeSectionLabel.ToUpper() + "_PUBLIC_COUNTER_COUNT";
          cppStream.WriteLine("const GPACounterDesc {0}[{1}] =", publicCountersConstant, publicCounterCountConstant);
          cppStream.WriteLine("{");
          int counterCount = 0;
          foreach (PublicCounterDef publicCounter in counterDefList)
          {
              ++counterCount;
              cppStream.WriteLine("    {{\"{0}\", \"{1}\", {2}, {3}}},", publicCounter.Name, publicCounter.Desc, publicCounter.Type, publicCounter.Usage);
          }

          cppStream.WriteLine("};");
          cppStream.WriteLine();
          cppStream.Close();

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
          headerStream.WriteLine("// Copyright (c) 2015-{0} Advanced Micro Devices, Inc. All rights reserved.", DateTime.Today.Year);
          headerStream.WriteLine("/// \\author AMD Developer Tools Team");
          headerStream.WriteLine("/// \\file");
          headerStream.WriteLine("/// \\brief  PublicCounterDefinitions for {0} for testing", activeSectionLabel.ToUpper());
          headerStream.WriteLine("//==============================================================================");
          headerStream.WriteLine();
          headerStream.WriteLine("// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.");
          headerStream.WriteLine();
          string headerGuard = "_GPA_TESTS_COUNTERS_" + activeSectionLabel.ToUpper() + "_";
          headerStream.WriteLine("#ifndef {0}", headerGuard);
          headerStream.WriteLine("#define {0}", headerGuard);
          headerStream.WriteLine();
          headerStream.WriteLine("#include \"GPACounterDesc.h\"");
          headerStream.WriteLine();
          headerStream.WriteLine("/// Number of public counters for {0}", activeSectionLabel);
          headerStream.WriteLine("static const size_t {0} = {1};", publicCounterCountConstant, counterCount);
          headerStream.WriteLine();
          headerStream.WriteLine("/// Array of public counters for {0}", activeSectionLabel);
          headerStream.WriteLine("extern const GPACounterDesc {0}[{1}];", publicCountersConstant, publicCounterCountConstant);
          headerStream.WriteLine();
          headerStream.WriteLine("#endif // {0}", headerGuard);
          headerStream.Close();
          return true;
      }

      /// <summary>
      /// The main entrypoint to the program.
      /// </summary>
      /// <param name="args">cmd line arguments</param>
      [STAThread]
      public static void Main(string[] args)
      {
         if (args.Length == 0)
         {
            isConsoleApp = false;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(Form1.Instance());
            return;
         }

         if (args.Length != 2 &&
              args.Length != 5)
         {
            Console.WriteLine("Usage: PublicCounterCompiler.exe");
            Console.WriteLine("   - using no parameters will open the user interface");
            Console.WriteLine("Usage: PublicCounterCompiler [API] [HW generation]");
            Console.WriteLine("   opens the user interface and propulates the input fileds with the following parameters:");
            Console.WriteLine("   [API] - the API to compile counters for (ex: GL, CL, HSA, DX11, etc)");
            Console.WriteLine("   [HW generation] - the generation to compile counters for (ex: R10xx, R11xx, R12xx, etc)");
            Console.WriteLine("Usage: PublicCounterCompiler [counter names file] [Public counter definition file] [output dir] [active section label]");
            Console.WriteLine("   [counter names file] - text file containing hardware counter names and type (CounterNames[API][GEN].txt)");
            Console.WriteLine("   [Public counter definition file] - text file defining how the public counters are calculated (PublicCounterDefinitions*.txt)");
            Console.WriteLine("   [Output Dir] - the directory to generate the output in (Ex: the path to the Src/GPUPerfAPICounterGenerator directory)");
            Console.WriteLine("   [Counter List Output Dir] - the directory to generate the counter list text files in (Ex: the path to the Output/CounterListFiles directory)");
            Console.WriteLine("   [Test output Dir] - the directory to generate the test output in (Ex: the path to the Src/GPUPerfAPIUnitTests/counters directory)");
            Console.WriteLine("   [Active section label] - the label to take the counter names from (ex: dx11r10xx)");
            return;
         }

         if (args.Length == 2)
         {
            isConsoleApp = false;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Form1.Instance().apiName.Text = args[0];
            Form1.Instance().GPUFamily.Text = args[1];
            Application.Run(Form1.Instance());
            return;
         }
         else if (args.Length == 5)
         {
            string strError;
            if (LoadFilesAndGenerateOutput(args[0], args[1], args[2], args[3], args[4], args[5], out strError) == false)
            {
               Output(strError);
            }
         }
      }
   }
}

