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
   }
}
