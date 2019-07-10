// =============================================================================
// <copyright file="Form1.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2019 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//      Main form for PublicCounterCompiler
// </summary>
// =============================================================================
namespace PublicCounterCompiler
{
    using System;
    using System.Windows.Forms;
    using Microsoft.Win32;

    /// <summary>
    /// the main form of the PublicCounterCompiler
    /// </summary>
    public partial class Form1 : Form
    {
        /// <summary>
        /// the singleton instance
        /// </summary>
        private static Form1 instance = null;

        /// <summary>
        /// Registry key root for the utility
        /// </summary>
        private static string registryKey = "HKEY_CURRENT_USER\\Software\\AMD\\DevTools";

        /// <summary>
        /// Previously entered API
        /// </summary>
        private static string registryApiEntry = "PccApi";

        /// <summary>
        /// Previously entered GPU family
        /// </summary>
        private static string registryGpuFamilyEntry = "PccGpuFamily";

        /// <summary>
        /// Counter compiler instance
        /// </summary>
        public CounterCompiler counterCompiler;

        /// <summary>
        /// Initializes a new instance of the Form1 class.
        /// </summary>
        public Form1(CounterCompiler _counterCompiler)
        {
            counterCompiler = _counterCompiler;

            InitializeComponent();

            apiName.Text = (string)Registry.GetValue(registryKey, registryApiEntry, string.Empty);

            GPUFamily.Text = (string)Registry.GetValue(registryKey, registryGpuFamilyEntry, string.Empty);

            CompileButton.Text = "Compile " + counterCompiler.derivedCounterFileInput.rootFilename + " Counters";
        }

        /// <summary>
        /// Accessor to the singleton instance
        /// </summary>
        /// <returns>The instance of the form</returns>
        public static Form1 Instance(CounterCompiler _counterCompiler)
        {
            if (instance == null)
            {
                instance = new Form1(_counterCompiler);
            }

            return instance;
        }

        /// <summary>
        /// Determines whether invalid counters should be ignored
        /// </summary>
        /// <returns>True if invalid counters should be ignored</returns>
        public static bool GetIgnoreInvalidCounters
        {
            get
            {
                return instance.IgnoreInvalidCountersCheckBox.Checked;
            }
        }

        /// <summary>
        /// Adds a message to the output window
        /// </summary>
        /// <param name="message">The message to add to the output window</param>
        public bool DisplayMessageHandler(string message)
        {
            if (counterCompiler.isConsoleApp)
            {
                Console.Out.Write(message);
            }
            else
            {
                richTextBoxOutput.Text += message + "\n";
                richTextBoxOutput.SelectionStart = richTextBoxOutput.Text.Length;
                richTextBoxOutput.ScrollToCaret();
            }

            System.Diagnostics.Debug.Print(message);
            return true;
        }

        /// <summary>
        /// Lambda callback error handler used by RegSpec file loading
        /// </summary>
        /// <param name="message">Error message.</param>
        /// <returns>true if any additional error handling occurred, otherwise false.</returns>
        public bool ErrorHandler(string message)
        {
            if (counterCompiler.isConsoleApp)
            {
                Console.Out.Write("Error:" + message);
            }
            else
            {
                richTextBoxOutput.Text += "Error:" + message + "\n";
                richTextBoxOutput.SelectionStart = richTextBoxOutput.Text.Length;
                richTextBoxOutput.ScrollToCaret();
            }

            System.Diagnostics.Debug.Print("Error:" + message);
            return false;
        }

        /// <summary>
        /// Ensures that the apiName and GPUFamily fields are not empty, then
        /// compiles the associated counters
        /// </summary>
        /// <param name="sender">the compile button</param>
        /// <param name="e">default event args</param>
        private void CompileButton_Click(object sender, EventArgs e)
        {
            richTextBoxOutput.Text = "";

            string api = apiName.Text.Trim();
            string gpu = GPUFamily.Text.Trim();

            if (string.IsNullOrEmpty(api)||
                 string.IsNullOrEmpty(gpu))
            {
                MessageBox.Show("Required data not provided.\nPlease fill in all the fields on the form.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            Registry.SetValue(registryKey, registryApiEntry, api);

            Registry.SetValue(registryKey, registryGpuFamilyEntry, gpu);

            // For compatibility with InternalCounterCompiler project
            if (false == counterCompiler.CompileCounters(api, gpu, DisplayMessageHandler, ErrorHandler))
            {
                ErrorHandler("Failed to compile counters");
            }
        }

        /// <summary>
        /// Ensures that the batchApiList and batchGpuFamilyList fields are not empty, then
        /// compiles the permutations of associated counters
        /// </summary>
        /// <param name="sender">the compile button</param>
        /// <param name="e">default event args</param>
        private void BatchCompile_Click(object sender, EventArgs e)
        {
            richTextBoxOutput.Text = "";

            counterCompiler.StartRSTDocumentation();

            if (string.IsNullOrEmpty(batchApiList.Text.Trim())
                || string.IsNullOrEmpty(batchGpuFamilyList.Text.Trim()))
            {
                MessageBox.Show("Required data not provided.\nPlease fill in all the fields on the form.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string[] apis = batchApiList.Text.Trim().Split(',');
            string[] gpus = batchGpuFamilyList.Text.Trim().Split(',');

            foreach (var api in apis)
            {
                foreach (var gpu in gpus)
                {
                    DisplayMessageHandler("\nCompiling API " + api + " for GPU Family " + gpu);

                    // For compatibility with InternalCounterCompiler project
                    if (false == counterCompiler.CompileCounters(api, gpu, DisplayMessageHandler, ErrorHandler))
                    {
                        ErrorHandler("Failed to compile counters");
                    }
                }
            }

            counterCompiler.DoneRSTDocumentation(DisplayMessageHandler, ErrorHandler);
        }

        /// <summary>
        /// Gets the checked state of the Generate Counter Docs button.
        /// </summary>
        /// <returns>True if counter docs should be generated</returns>
        static public bool GenerateCounterDocs
        {
            get
            {
                return instance.checkBoxGenerateCounterDocs.Checked;
            }
        }

    }
}
