// =============================================================================
// <copyright file="Form1.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
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
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Data;
    using System.Drawing;
    using System.Text;
    using System.Windows.Forms;

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
        /// Initializes a new instance of the Form1 class.
        /// </summary>
        public Form1()
        {
            InitializeComponent();
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
            m_output.Text += strMsg.Replace("\n", "\r\n") + "\r\n";
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
            if (apiName.TextLength == 0 ||
                 GPUFamily.TextLength == 0)
            {
                MessageBox.Show("Required data not provided.\nPlease fill in all the fields on the form.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            this.m_output.Clear();
            Program.CompileCounters(apiName.Text, GPUFamily.Text);
        }

        /// <summary>
        /// Ensures that the batchApiList and batchGpuFamilyList fields are not empty, then
        /// compiles the permutations of associated counters
        /// </summary>
        /// <param name="sender">the compile button</param>
        /// <param name="e">default event args</param>
        private void BatchCompile_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(batchApiList.Text)
                || string.IsNullOrEmpty(batchGpuFamilyList.Text))
            {
                MessageBox.Show("Required data not provided.\nPlease fill in all the fields on the form.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            m_output.Clear();

            string[] apis = batchApiList.Text.Split(',');
            string[] gpus = batchGpuFamilyList.Text.Split(',');

            this.m_output.Clear();
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

                    Output("\nCompiling API " + api + " for GPU Family " + gpu);

                    Program.CompileCounters(api, gpu);
                }
            }
        }
    }
}
