// =============================================================================
// <copyright file="form1.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2025 Advanced Micro Devices, Inc. All rights reserved.
// </copyright>
// <author>
//    AMD Developer Tools Team
// </author>
// <summary>
//    Main form for PublicCounterCompiler.
// </summary>
// =============================================================================
namespace PublicCounterCompiler
{
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Linq;
    using System.Threading;
    using System.Windows.Forms;
    using GpaTools;
    using Microsoft.Win32;

    /// <summary>
    /// The main form of the PublicCounterCompiler.
    /// </summary>
    public partial class Form1 : Form
    {
        /// <summary>
        /// The singleton instance.
        /// </summary>
        private static Form1 _instance = null;

        /// <summary>
        /// Registry key root for the utility
        /// </summary>
        private static string _registryKey = "HKEY_CURRENT_USER\\Software\\AMD\\DevTools";

        /// <summary>
        /// Previously entered API
        /// </summary>
        private static string _registryApiEntry = "PccApi";

        /// <summary>
        /// Previously entered GPU family
        /// </summary>
        private static string _registryGpuFamilyEntry = "PccGpuFamily";

        /// <summary>
        /// Background worker thread
        /// </summary>
        private static BackgroundWorker _backgroundWorker = new BackgroundWorker();

        /// <summary>
        /// Background worker thread arguments
        /// </summary>
        private static BackgroundWorkerArgs _backgroundWorkerArgs;

        /// <summary>
        /// Counter compiler instance
        /// </summary>
        public CounterCompiler _counterCompiler;

        /// <summary>
        /// Initializes a new instance of the Form1 class.
        /// </summary>
        public Form1(CounterCompiler counterCompiler)
        {
            _counterCompiler = counterCompiler;

            InitializeComponent();

            apiName.Text = (string)Registry.GetValue(_registryKey, _registryApiEntry, string.Empty);

            GPUFamily.Text = (string)Registry.GetValue(_registryKey, _registryGpuFamilyEntry, string.Empty);

            CompileButton.Text = "Compile " + counterCompiler.derivedCounterFileInput.compiler_type_str + " Counters";

            _backgroundWorker.WorkerSupportsCancellation = true;
            _backgroundWorker.DoWork += new DoWorkEventHandler(backgroundWorker_CompileCounters);
            _backgroundWorker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(backgroundWorker_CompileCountersCompleted);
        }

        /// <summary>
        /// Accessor to the singleton instance
        /// </summary>
        /// <returns>The instance of the form</returns>
        public static Form1 Instance(CounterCompiler counterCompiler)
        {
            if (_instance == null)
            {
                _instance = new Form1(counterCompiler);
            }

            return _instance;
        }

        /// <summary>
        /// Determines whether invalid counters should be ignored
        /// </summary>
        /// <returns>True if invalid counters should be ignored</returns>
        public static bool GetIgnoreInvalidCounters
        {
            get
            {
                return _instance.IgnoreInvalidCountersCheckBox.Checked;
            }
        }

        /// <summary>
        /// Adds a message to the output window
        /// </summary>
        /// <param name="message">The message to add to the output window</param>
        public bool DisplayMessageHandler(string message)
        {
            if (_counterCompiler.isConsoleApp)
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
            if (_counterCompiler.isConsoleApp)
            {
                Console.Out.Write("Error: " + message);
            }
            else
            {
                // Invoke is used as this may be called from the worker thread
                BeginInvoke((Action)(() =>
                {
                    richTextBoxOutput.Text += "Error: " + message + "\n";
                    richTextBoxOutput.SelectionStart = richTextBoxOutput.Text.Length;
                    richTextBoxOutput.ScrollToCaret();
                }));
            }

            System.Diagnostics.Debug.Print("Error: " + message);
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

            Registry.SetValue(_registryKey, _registryApiEntry, api);
            Registry.SetValue(_registryKey, _registryGpuFamilyEntry, gpu);

            string[] apis = { api };
            string[] gpus = { gpu };
            StartCompileCounters(apis, gpus);
        }

        /// <summary>
        /// Ensures that the batchApiList and batchGpuFamilyList fields are not empty, then
        /// compiles the permutations of associated counters
        /// </summary>
        /// <param name="sender">the compile button</param>
        /// <param name="e">default event args</param>
        private void BatchCompile_Click(object sender, EventArgs e)
        {
            Stopwatch timer = new Stopwatch();
            timer.Start();

            richTextBoxOutput.Text = "";

            _counterCompiler.StartRSTDocumentation();

            if (string.IsNullOrEmpty(batchApiList.Text.Trim())
                || string.IsNullOrEmpty(batchGpuFamilyList.Text.Trim()))
            {
                MessageBox.Show("Required data not provided.\nPlease fill in all the fields on the form.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string[] apis = batchApiList.Text.Trim().Split(',');
            string[] gpus = batchGpuFamilyList.Text.Trim().Split(',');

            var doneEvent = new AutoResetEvent(false);

            StartCompileCounters(apis, gpus, doneEvent);

            // Wait with timeout so we can pump the UI update
            while (false == doneEvent.WaitOne(100))
            {
                Application.DoEvents();
            }

            _counterCompiler.DoneRSTDocumentation(DisplayMessageHandler, ErrorHandler);

            timer.Stop();

            DisplayMessageHandler("\nCode generation completed in " + timer.ToString());
        }

        /// <summary>
        /// Background worker arguments
        /// </summary>
        private class BackgroundWorkerArgs
        {
            /// <summary>
            /// Ctor
            /// </summary>
            /// <param name="_apis">API</param>
            /// <param name="_gpus">GPU ASIC</param>
            /// <param name="_doneEvent">Optional done event</param>
            public BackgroundWorkerArgs(string[] _apis, string[] _gpus, AutoResetEvent _doneEvent)
            {
                apis = _apis;
                gpus = _gpus;
                doneEvent = _doneEvent;
            }

            /// <summary>
            /// The array of APIs to process.
            /// </summary>
            public string[] apis;

            /// <summary>
            /// The array of GPU ASICs to process.
            /// </summary>
            public string[] gpus;

            /// <summary>
            /// Optional done event
            /// </summary>
            public AutoResetEvent doneEvent = null;
        }

        /// <summary>
        /// Starts background worker thread to compile counters
        /// </summary>
        /// <param name="apis">The array of APIs to process.</param>
        /// <param name="gpus">The array of Gfx generations to process.</param>
        /// <param name="autoResetEvent">Optional reset event</param>
        private void StartCompileCounters(string[] apis, string[] gpus, AutoResetEvent autoResetEvent = null)
        {
            CompileButton.Enabled = false;
            batchCompile.Enabled = false;

            _backgroundWorkerArgs = new BackgroundWorkerArgs(apis, gpus, autoResetEvent);

            // Start the asynchronous operation.
            _backgroundWorker.RunWorkerAsync(_backgroundWorkerArgs);
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

            foreach (var api in args.apis)
            {
                foreach (var gpu in args.gpus)
                {
                    DisplayMessageHandler("\nCompiling API " + api + " for GPU Family " + gpu);

                    if (false == _counterCompiler.CompileCounters(api, gpu, DisplayMessageHandler, ErrorHandler))
                    {
                        e.Cancel = true;
                        worker.CancelAsync();
                        return;
                    }
                }
            }

            DisplayMessageHandler("\nAll counter generation completed");
        }

        /// <summary>
        /// Background worker counter compilation completed
        /// </summary>
        /// <param name="sender">Sender object</param>
        /// <param name="e">Completed work event args</param>
        private void backgroundWorker_CompileCountersCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            // Get the BackgroundWorker that raised this event.
            BackgroundWorker worker = sender as BackgroundWorker;

            CompileButton.Enabled = true;
            batchCompile.Enabled = true;

            if (null != _backgroundWorkerArgs.doneEvent)
            {
                _backgroundWorkerArgs.doneEvent.Set();
            }

            if (e.Cancelled)
            {
                DisplayMessageHandler("Stopped early due to an error.");
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
                return _instance.checkBoxGenerateCounterDocs.Checked;
            }
        }
    }
}
