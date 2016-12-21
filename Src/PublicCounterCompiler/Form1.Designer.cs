// =============================================================================
// <copyright file="Form1.Designer.cs" company="Advanced Micro Devices, Inc.">
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
   partial class Form1
   {
      /// <summary>
      /// Required designer variable.
      /// </summary>
      private System.ComponentModel.IContainer components = null;

      /// <summary>
      /// Clean up any resources being used.
      /// </summary>
      /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
      protected override void Dispose( bool disposing )
      {
         if ( disposing && ( components != null ) )
         {
            components.Dispose();
         }
         base.Dispose( disposing );
      }

      #region Windows Form Designer generated code

      /// <summary>
      /// Required method for Designer support - do not modify
      /// the contents of this method with the code editor.
      /// </summary>
      private void InitializeComponent()
      {
         this.CompileButton = new System.Windows.Forms.Button();
         this.m_outputLabel = new System.Windows.Forms.Label();
         this.m_output = new System.Windows.Forms.TextBox();
         this.IgnoreInvalidCountersCheckBox = new System.Windows.Forms.CheckBox();
         this.label5 = new System.Windows.Forms.Label();
         this.label6 = new System.Windows.Forms.Label();
         this.apiName = new System.Windows.Forms.TextBox();
         this.GPUFamily = new System.Windows.Forms.TextBox();
         this.SuspendLayout();
         // 
         // CompileButton
         // 
         this.CompileButton.Location = new System.Drawing.Point(191, 39);
         this.CompileButton.Name = "CompileButton";
         this.CompileButton.Size = new System.Drawing.Size(147, 39);
         this.CompileButton.TabIndex = 9;
         this.CompileButton.Text = "Compile Public Counters";
         this.CompileButton.UseVisualStyleBackColor = true;
         this.CompileButton.Click += new System.EventHandler(this.CompileButton_Click);
         // 
         // m_outputLabel
         // 
         this.m_outputLabel.AutoSize = true;
         this.m_outputLabel.Location = new System.Drawing.Point(12, 99);
         this.m_outputLabel.Name = "m_outputLabel";
         this.m_outputLabel.Size = new System.Drawing.Size(42, 13);
         this.m_outputLabel.TabIndex = 10;
         this.m_outputLabel.Text = "Output:";
         // 
         // m_output
         // 
         this.m_output.AcceptsReturn = true;
         this.m_output.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
         this.m_output.BackColor = System.Drawing.SystemColors.Window;
         this.m_output.Location = new System.Drawing.Point(15, 115);
         this.m_output.Multiline = true;
         this.m_output.Name = "m_output";
         this.m_output.ReadOnly = true;
         this.m_output.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
         this.m_output.Size = new System.Drawing.Size(750, 164);
         this.m_output.TabIndex = 11;
         // 
         // IgnoreInvalidCountersCheckBox
         // 
         this.IgnoreInvalidCountersCheckBox.AutoSize = true;
         this.IgnoreInvalidCountersCheckBox.Location = new System.Drawing.Point(191, 16);
         this.IgnoreInvalidCountersCheckBox.Name = "IgnoreInvalidCountersCheckBox";
         this.IgnoreInvalidCountersCheckBox.Size = new System.Drawing.Size(135, 17);
         this.IgnoreInvalidCountersCheckBox.TabIndex = 12;
         this.IgnoreInvalidCountersCheckBox.Text = "Ignore Invalid Counters";
         this.IgnoreInvalidCountersCheckBox.UseVisualStyleBackColor = true;
         // 
         // label5
         // 
         this.label5.AutoSize = true;
         this.label5.Location = new System.Drawing.Point(58, 26);
         this.label5.Name = "label5";
         this.label5.Size = new System.Drawing.Size(24, 13);
         this.label5.TabIndex = 13;
         this.label5.Text = "API";
         // 
         // label6
         // 
         this.label6.AutoSize = true;
         this.label6.Location = new System.Drawing.Point(20, 52);
         this.label6.Name = "label6";
         this.label6.Size = new System.Drawing.Size(62, 13);
         this.label6.TabIndex = 14;
         this.label6.Text = "GPU Family";
         // 
         // apiName
         // 
         this.apiName.Location = new System.Drawing.Point(88, 23);
         this.apiName.Name = "apiName";
         this.apiName.Size = new System.Drawing.Size(73, 20);
         this.apiName.TabIndex = 15;
         // 
         // GPUFamily
         // 
         this.GPUFamily.Location = new System.Drawing.Point(88, 49);
         this.GPUFamily.Name = "GPUFamily";
         this.GPUFamily.Size = new System.Drawing.Size(73, 20);
         this.GPUFamily.TabIndex = 16;
         // 
         // Form1
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.ClientSize = new System.Drawing.Size(777, 291);
         this.Controls.Add(this.GPUFamily);
         this.Controls.Add(this.apiName);
         this.Controls.Add(this.label6);
         this.Controls.Add(this.label5);
         this.Controls.Add(this.IgnoreInvalidCountersCheckBox);
         this.Controls.Add(this.m_output);
         this.Controls.Add(this.m_outputLabel);
         this.Controls.Add(this.CompileButton);
         this.MinimumSize = new System.Drawing.Size(400, 300);
         this.Name = "Form1";
         this.Text = "Public Counter Compiler";
         this.ResumeLayout(false);
         this.PerformLayout();

      }

      #endregion

      private System.Windows.Forms.Button CompileButton;
      private System.Windows.Forms.Label m_outputLabel;
      private System.Windows.Forms.TextBox m_output;
      private System.Windows.Forms.CheckBox IgnoreInvalidCountersCheckBox;
      private System.Windows.Forms.Label label5;
      private System.Windows.Forms.Label label6;
      public System.Windows.Forms.TextBox apiName;
      public System.Windows.Forms.TextBox GPUFamily;
   }
}