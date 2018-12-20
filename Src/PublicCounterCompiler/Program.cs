// =====================================================================
// <copyright file="Program.cs" company="Advanced Micro Devices, Inc.">
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
    /// A program which compiles the derived counters definitions into C++ files.
    /// </summary>
    public class Program
    {
        /// <summary>
        /// The main entry point to the program.
        /// </summary>
        /// <param name="args">cmd line arguments</param>
        [STAThread]
        public static void Main(string[] args)
        {
            // set output paths
            const string compilerOutputFolder = "Output\\";
            int endPath = Application.StartupPath.IndexOf(compilerOutputFolder) + compilerOutputFolder.Length;

            if (compilerOutputFolder.Length == endPath)
            {
                MessageBox.Show(Application.ProductName + " was started out of unexpected folder.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string gpaPath = Application.StartupPath.Substring(0, endPath - compilerOutputFolder.Length) + "..\\GPA\\";

            // Derived counter definition input
            CounterCompiler.DerivedCounterFileInput counterPath = new CounterCompiler.DerivedCounterFileInput();
            counterPath.rootFilename = "Public";
            counterPath.compilerInputPath = gpaPath + "Src\\PublicCounterCompilerInputFiles\\";

            counterPath.outputDirectory = gpaPath + "Src\\GPUPerfAPICounterGenerator\\";
            counterPath.counterListOutputDirectory = gpaPath + "Output\\CounterListFiles\\";
            counterPath.testOutputDirectory = gpaPath + "Src\\GPUPerfAPIUnitTests\\counters\\";

            CounterCompiler.derivedCounterFileInput = counterPath;

            // handle operational mode
            if (args.Length == 0)
            {
                CounterCompiler.isConsoleApp = false;
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(Form1.Instance());
                return;
            }

            if (args.Length == 2
                || args.Length == 7
                || args.Length == 8)
            {
                // We can do this!
            }
            else
            {
                Console.WriteLine("Usage: PublicCounterCompiler.exe");
                Console.WriteLine("   - using no parameters will open the user interface");
                Console.WriteLine("Usage: PublicCounterCompiler [API] [HW generation]");
                Console.WriteLine(
                    "   opens the user interface and populates the input fields with the following parameters:");
                Console.WriteLine("   [API] - the API to compile counters for (ex: GL, CL, HSA, DX11, etc)");
                Console.WriteLine(
                    "   [HW generation] - the generation to compile counters for (ex: R10xx, R11xx, R12xx, etc)");
                Console.WriteLine(
                    "Usage: PublicCounterCompiler [counter names file] [Public counter definition file] [output dir] [API] [GPU]");
                Console.WriteLine(
                    "   [counter names file] - text file containing hardware counter names and type (CounterNames[API][GEN].txt)");
                Console.WriteLine(
                    "   [Public counter definition file] - text file defining how the public counters are calculated (PublicCounterDefinitions*.txt)");
                Console.WriteLine(
                    "   [Output Dir] - the directory to generate the output in (Ex: the path to the Src/GPUPerfAPICounterGenerator directory)");
                Console.WriteLine(
                    "   [Counter List Output Dir] - the directory to generate the counter list text files in (Ex: the path to the Output/CounterListFiles directory)");
                Console.WriteLine(
                    "   [Test output Dir] - the directory to generate the test output in (Ex: the path to the Src/GPUPerfAPIUnitTests/counters directory)");
                Console.WriteLine(
                    "   [API] - the API to compile counters for (ex: GL, CL, HSA, DX11, etc)");
                Console.WriteLine(
                    "   [HW generation] - the generation to compile counters for (ex: R10xx, R11xx, R12xx, etc)");
                Console.WriteLine(
                    "   {ASIC} - name of the ASIC (ex: baffin)");
                return;
            }

            if (args.Length == 2)
            {
                CounterCompiler.isConsoleApp = false;
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Form1.Instance().apiName.Text = args[0];
                Form1.Instance().GPUFamily.Text = args[1];
                Application.Run(Form1.Instance());
                return;
            }
            else if (args.Length == 7)
            {
                string strError;
                if (CounterCompiler.LoadFilesAndGenerateOutput("Public", args[0], args[1], args[2], args[3], args[4], args[5], args[6], string.Empty, out strError) ==
                    false)
                {
                    CounterCompiler.Output(strError);
                }
            }
            else if (args.Length == 8)
            {
                string strError;
                if (CounterCompiler.LoadFilesAndGenerateOutput("Public", args[0], args[1], args[2], args[3], args[4], args[5], args[6], "_" + args[7], out strError) ==
                    false)
                {
                    CounterCompiler.Output(strError);
                }
            }
        }
    }
}

