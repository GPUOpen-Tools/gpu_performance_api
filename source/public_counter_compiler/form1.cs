// =============================================================================
// <copyright file="Form1.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2020 Advanced Micro Devices, Inc. All rights reserved.
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
    using System.ComponentModel;
    using System.Threading;
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
        /// Background worker thread
        /// </summary>
        private static BackgroundWorker backgroundWorker = new BackgroundWorker();

        /// <summary>
        /// Background worker thread arguments
        /// </summary>
        private static BackgroundWorkerArgs backgroundWorkerArgs;

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

            CompileButton.Text = "Compile " + counterCompiler.derivedCounterFileInput.compiler_type_str + " Counters";

            backgroundWorker.DoWork += new DoWorkEventHandler(backgroundWorker_CompileCounters);
            backgroundWorker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(backgroundWorker_CompileCountersCompleted);
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
                // Invoke is used as this may be called from the worker thread
                BeginInvoke((Action)(() =>
                {
                    richTextBoxOutput.Text += message + "\n";
                    richTextBoxOutput.SelectionStart = richTextBoxOutput.Text.Length;
                    richTextBoxOutput.ScrollToCaret();
                }));
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
                // Invoke is used as this may be called from the worker thread
                BeginInvoke((Action)(() =>
                {
                    richTextBoxOutput.Text += "Error:" + message + "\n";
                    richTextBoxOutput.SelectionStart = richTextBoxOutput.Text.Length;
                    richTextBoxOutput.ScrollToCaret();
                }));
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

            if (string.IsNullOrEmpty(api) ||
                 string.IsNullOrEmpty(gpu))
            {
                MessageBox.Show("Required data not provided.\nPlease fill in all the fields on the form.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            Registry.SetValue(registryKey, registryApiEntry, api);

            Registry.SetValue(registryKey, registryGpuFamilyEntry, gpu);

            StartCompileCounters(api, gpu);
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
                    var doneEvent = new AutoResetEvent(false);

                    StartCompileCounters(api, gpu, doneEvent);

                    // Wait with timeout so we can pump the UI update
                    while (false == doneEvent.WaitOne(100))
                    {
                        Application.DoEvents();
                    }
                }
            }

            counterCompiler.DoneRSTDocumentation(DisplayMessageHandler, ErrorHandler);
        }

        /// <summary>
        /// Background worker arguments
        /// </summary>
        private class BackgroundWorkerArgs
        {
            /// <summary>
            /// Ctor
            /// </summary>
            /// <param name="_api">API</param>
            /// <param name="_gpu">GPU ASIC</param>
            /// <param name="_doneEvent">Optional done event</param>
            public BackgroundWorkerArgs(string _api, string _gpu, AutoResetEvent _doneEvent)
            {
                api = _api;
                gpu = _gpu;
                doneEvent = _doneEvent;
            }

            /// <summary>
            /// API
            /// </summary>
            public string api;

            /// <summary>
            /// GPU ASIC
            /// </summary>
            public string gpu;

            /// <summary>
            /// Optional done event
            /// </summary>
            public AutoResetEvent doneEvent = null;
        }

        /// <summary>
        /// Starts background worker thread to compile counters
        /// </summary>
        /// <param name="api">API</param>
        /// <param name="gpu">GPU</param>
        /// <param name="autoResetEvent">Optional reset event</param>
        private void StartCompileCounters(string api, string gpu, AutoResetEvent autoResetEvent = null)
        {
            CompileButton.Enabled = false;
            batchCompile.Enabled = false;

            backgroundWorkerArgs = new BackgroundWorkerArgs(api, gpu, autoResetEvent);

            // Start the asynchronous operation.
            backgroundWorker.RunWorkerAsync(backgroundWorkerArgs);
        }

        /// <summary>
        /// Background worker compile counters
        /// </summary>
        /// <param name="sender">Sender object</param>
        /// <param name="e">Work event args</param>
        private void backgroundWorker_CompileCounters(object sender, DoWorkEventArgs e)
        {
            // Get the BackgroundWorker that raised this event.
            BackgroundWorker worker = sender as BackgroundWorker;

            var args = e.Argument as BackgroundWorkerArgs;

            DisplayMessageHandler("\nCompiling API " + args.api + " for GPU Family " + args.gpu);

            counterCompiler.CompileCounters(args.api, args.gpu, DisplayMessageHandler, ErrorHandler);
        }

        /// <summary>
        /// Background worker counter compilation completed
        /// </summary>
        /// <param name="sender">Sender object</param>
        /// <param name="e">Completed work event args</param>
        private void backgroundWorker_CompileCountersCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            CompileButton.Enabled = true;
            batchCompile.Enabled = true;

            if (null != backgroundWorkerArgs.doneEvent)
            {
                backgroundWorkerArgs.doneEvent.Set();
            }
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
