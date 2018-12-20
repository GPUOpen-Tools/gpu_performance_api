// =============================================================================
// <copyright file="Form1.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2018 Advanced Micro Devices, Inc. All rights reserved.
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
        /// Initializes a new instance of the Form1 class.
        /// </summary>
        public Form1()
        {
            InitializeComponent();

            apiName.Text = (string)Registry.GetValue(registryKey, registryApiEntry, string.Empty);

            GPUFamily.Text = (string)Registry.GetValue(registryKey, registryGpuFamilyEntry, string.Empty);

            CompileButton.Text = "Compile " + CounterCompiler.derivedCounterFileInput.rootFilename + " Counters";
        }

        /// <summary>
        /// Accessor to the singleton instance
        /// </summary>
        /// <returns>The instance of the form</returns>
        public static Form1 Instance()
        {
            if (instance == null)
            {
                instance = new Form1();
            }

            return instance;
        }

        /// <summary>
        /// Adds a message to the output window
        /// </summary>
        /// <param name="strMsg">The message to add to the output window</param>
        public void Output(string strMsg)
        {
            richTextBoxOutput.Text += strMsg + "\n";
            richTextBoxOutput.SelectionStart = richTextBoxOutput.Text.Length;
            richTextBoxOutput.ScrollToCaret();
        }

        /// <summary>
        /// Gets the checked state of the IngoreInvalidCounters box
        /// </summary>
        /// <returns>Whether or not to ignore invalid counters</returns>
        public bool IgnoreInvalidCounters()
        {
            return IgnoreInvalidCountersCheckBox.Checked;
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
            if (false == PublicCounterCompiler.CounterCompiler.CompileCounters(api, gpu))
            {
                Output("Failed to compile counters");
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

            CounterCompiler.StartRSTDocumentation();

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
                    // We know there are some invalid combinations on Gfx6
                    if ("Gfx6" == gpu)
                    {
                        string[] unsupportedApis = new string[] { "DX12", "VK", "HSA" };
                        if (Array.IndexOf(unsupportedApis, api) >= 0)
                        {
                            Output("\nSkipping API " + api + " unsupported on " + gpu);
                            continue;
                        }
                    }

                    if ("Gfx7" == gpu)
                    {
                        string[] unsupportedApis = new string[] { "HSA" };
                        if (Array.IndexOf(unsupportedApis, api) >= 0)
                        {
                            Output("\nSkipping API " + api + " unsupported on " + gpu);
                            continue;
                        }
                    }

                    Output("\nCompiling API " + api + " for GPU Family " + gpu);

                    // For compatibility with InternalCounterCompiler project
                    if (false == PublicCounterCompiler.CounterCompiler.CompileCounters(api, gpu))
                    {
                        Output("Failed to compile counters");
                    }
                }
            }
        }

        /// <summary>
        /// Gets the checked state of the Generate Counter Docs button.
        /// </summary>
        /// <returns>True if counter docs should be generated</returns>
        public bool GenerateCounterDocs
        {
            get
            {
                return checkBoxGenerateCounterDocs.Checked;
            }
        }

    }
}
