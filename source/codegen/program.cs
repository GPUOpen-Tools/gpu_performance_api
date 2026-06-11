// =====================================================================
// <copyright file="program.cs" company="Advanced Micro Devices, Inc.">
//    Copyright Advanced Micro Devices, Inc. All rights reserved.
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
    using System.Diagnostics;
    using System.IO;
    using GpaTools;

    /// <summary>
    /// A program which compiles the derived counters definitions into C++ files.
    /// </summary>
    public class Program
    {
        /// <summary>
        /// Default comma-separated list of APIs to compile.
        /// </summary>
        private const string DefaultApis = "OGLP,VK,DX11,DX12";

        /// <summary>
        /// Default comma-separated list of GPU families to compile.
        /// </summary>
        private const string DefaultGpus = "Gfx12,Gfx115,Gfx11,Gfx103,Gfx10";

        /// <summary>
        /// Displays a message to the console.
        /// </summary>
        /// <param name="message">The message to display.</param>
        /// <returns>true always.</returns>
        private static bool DisplayMessageHandler(string message)
        {
            Console.Out.Write(message);
            System.Diagnostics.Debug.Print(message);
            return true;
        }

        /// <summary>
        /// Displays an error message to the console.
        /// </summary>
        /// <param name="message">The error message.</param>
        /// <returns>false always.</returns>
        private static bool ErrorHandler(string message)
        {
            Console.Error.WriteLine("Error: " + message);
            System.Diagnostics.Debug.Print("Error: " + message);
            return false;
        }

        /// <summary>
        /// Prints the usage information.
        /// </summary>
        private static void PrintUsage()
        {
            Console.WriteLine("Usage: PublicCounterCompiler [options]");
            Console.WriteLine();
            Console.WriteLine("Options:");
            Console.WriteLine("  --api <api1,api2,...>          Comma-separated list of APIs to compile");
            Console.WriteLine("                                (default: " + DefaultApis + ")");
            Console.WriteLine("  --gpu <gpu1,gpu2,...>          Comma-separated list of GPU families");
            Console.WriteLine("                                (default: " + DefaultGpus + ")");
            Console.WriteLine("  --asic <asic>                  Restrict ASIC-specific output to one variant");
            Console.WriteLine("                                (base generation output is always included)");
            Console.WriteLine("                                omit to compile all ASIC variants");
            Console.WriteLine("  --ignore-invalid-counters     Ignore invalid counters instead of treating");
            Console.WriteLine("                                as errors");
            Console.WriteLine("  --help                        Show this help message");
        }

        /// <summary>
        /// The main entry point to the program.
        /// </summary>
        /// <param name="args">cmd line arguments</param>
        /// <returns>0 on success, 1 on failure</returns>
        public static int Main(string[] args)
        {
            string gpaPath = Gpa.GetGpuPerfApiPath();

            // Derived counter definition input
            var counterCompiler = new CounterCompiler();

            CounterCompiler.DerivedCounterFileInput counterPath = new CounterCompiler.DerivedCounterFileInput
            {
                rootFilename = Gpa.publicFilePrefix,
                compiler_type_str = Gpa.publicStr,
                compilerInputPath = gpaPath + Gpa.counterDefDir,
                autoGenCompilerInputFilePath = gpaPath + Gpa.autoGenPublicCounterInputDir,
                outputDirectory = gpaPath + Gpa.autoGenCounterGeneratorOutDir,
                counterListOutputDirectory = gpaPath + Gpa.counterListOutDir,
                testOutputDirectory = gpaPath + Gpa.autoGenTestOutDir
            };

            counterCompiler.derivedCounterFileInput = counterPath;

            // Parse command-line options
            string apiList = DefaultApis;
            string gpuList = DefaultGpus;
            string asicFilter = string.Empty;

            for (int i = 0; i < args.Length; i++)
            {
                switch (args[i].ToLower())
                {
                    case "--api":
                        if (i + 1 < args.Length)
                        {
                            apiList = args[++i];
                        }
                        else
                        {
                            Console.Error.WriteLine("Error: --api requires an argument.");
                            return 1;
                        }
                        break;

                    case "--gpu":
                        if (i + 1 < args.Length)
                        {
                            gpuList = args[++i];
                        }
                        else
                        {
                            Console.Error.WriteLine("Error: --gpu requires an argument.");
                            return 1;
                        }
                        break;

                    case "--asic":
                        if (i + 1 < args.Length)
                        {
                            asicFilter = args[++i];
                        }
                        else
                        {
                            Console.Error.WriteLine("Error: --asic requires an argument.");
                            return 1;
                        }
                        break;

                    case "--ignore-invalid-counters":
                        counterCompiler.ignoreInvalidCounters = true;
                        break;

                    case "--help":
                    case "-h":
                        PrintUsage();
                        return 0;

                    default:
                        Console.Error.WriteLine("Error: Unknown option '" + args[i] + "'.");
                        PrintUsage();
                        return 1;
                }
            }

            string[] apis = apiList.Split(',', StringSplitOptions.RemoveEmptyEntries);
            string[] gpus = gpuList.Split(',', StringSplitOptions.RemoveEmptyEntries);

            if (apis.Length == 0)
            {
                Console.Error.WriteLine("Error: --api must specify at least one API.");
                PrintUsage();
                return 1;
            }

            if (gpus.Length == 0)
            {
                Console.Error.WriteLine("Error: --gpu must specify at least one GPU family.");
                PrintUsage();
                return 1;
            }

            Stopwatch timer = new Stopwatch();
            timer.Start();

            counterCompiler.StartRSTDocumentation();

            // Compile counters for all API/GPU combinations
            bool success = true;
            foreach (var api in apis)
            {
                foreach (var gpu in gpus)
                {
                    DisplayMessageHandler("\nCompiling API " + api.Trim() + " for GPU Family " + gpu.Trim());

                    if (!counterCompiler.CompileCounters(api.Trim(), gpu.Trim(), DisplayMessageHandler, ErrorHandler, asicFilter))
                    {
                        success = false;
                        break;
                    }
                }

                if (!success)
                {
                    break;
                }
            }

            if (success)
            {
                DisplayMessageHandler("\nAll counter generation completed");
            }
            else
            {
                ErrorHandler("Stopped early due to an error.\n");
            }

            if (success)
            {
                counterCompiler.DoneRSTDocumentation(DisplayMessageHandler, ErrorHandler);
            }

            timer.Stop();
            DisplayMessageHandler("\nCode generation completed in " + timer.Elapsed + "\n");

            return success ? 0 : 1;
        }
    }
}
