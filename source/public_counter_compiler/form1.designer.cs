// =============================================================================
// <copyright file="Form1.Designer.cs" company="Advanced Micro Devices, Inc.">
//    Copyright (c) 2011-2017 Advanced Micro Devices, Inc. All rights reserved.
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
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.CompileButton = new System.Windows.Forms.Button();
            this.IgnoreInvalidCountersCheckBox = new System.Windows.Forms.CheckBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.apiName = new System.Windows.Forms.TextBox();
            this.GPUFamily = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.richTextBoxOutput = new System.Windows.Forms.RichTextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.batchCompile = new System.Windows.Forms.Button();
            this.batchGpuFamilyList = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.batchApiList = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.checkBoxGenerateCounterDocs = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // CompileButton
            // 
            this.CompileButton.AutoSize = true;
            this.CompileButton.Location = new System.Drawing.Point(286, 60);
            this.CompileButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.CompileButton.Name = "CompileButton";
            this.CompileButton.Size = new System.Drawing.Size(220, 60);
            this.CompileButton.TabIndex = 2;
            this.CompileButton.Text = "Compile Derived Counters";
            this.CompileButton.UseVisualStyleBackColor = true;
            this.CompileButton.Click += new System.EventHandler(this.CompileButton_Click);
            // 
            // IgnoreInvalidCountersCheckBox
            // 
            this.IgnoreInvalidCountersCheckBox.AutoSize = true;
            this.IgnoreInvalidCountersCheckBox.Location = new System.Drawing.Point(286, 25);
            this.IgnoreInvalidCountersCheckBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IgnoreInvalidCountersCheckBox.Name = "IgnoreInvalidCountersCheckBox";
            this.IgnoreInvalidCountersCheckBox.Size = new System.Drawing.Size(199, 24);
            this.IgnoreInvalidCountersCheckBox.TabIndex = 12;
            this.IgnoreInvalidCountersCheckBox.Text = "Ignore Invalid Counters";
            this.IgnoreInvalidCountersCheckBox.UseVisualStyleBackColor = true;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(87, 40);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 20);
            this.label5.TabIndex = 13;
            this.label5.Text = "API";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(30, 80);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(93, 20);
            this.label6.TabIndex = 14;
            this.label6.Text = "GPU Family";
            // 
            // apiName
            // 
            this.apiName.Location = new System.Drawing.Point(132, 35);
            this.apiName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.apiName.Name = "apiName";
            this.apiName.Size = new System.Drawing.Size(108, 26);
            this.apiName.TabIndex = 0;
            // 
            // GPUFamily
            // 
            this.GPUFamily.Location = new System.Drawing.Point(132, 75);
            this.GPUFamily.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GPUFamily.Name = "GPUFamily";
            this.GPUFamily.Size = new System.Drawing.Size(108, 26);
            this.GPUFamily.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.richTextBoxOutput);
            this.groupBox1.Location = new System.Drawing.Point(12, 219);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1287, 676);
            this.groupBox1.TabIndex = 15;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = " Output ";
            // 
            // richTextBoxOutput
            // 
            this.richTextBoxOutput.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextBoxOutput.Location = new System.Drawing.Point(3, 22);
            this.richTextBoxOutput.Name = "richTextBoxOutput";
            this.richTextBoxOutput.Size = new System.Drawing.Size(1281, 651);
            this.richTextBoxOutput.TabIndex = 0;
            this.richTextBoxOutput.Text = "";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.batchCompile);
            this.groupBox2.Controls.Add(this.batchGpuFamilyList);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.batchApiList);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Location = new System.Drawing.Point(604, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(581, 112);
            this.groupBox2.TabIndex = 16;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = " Batch Mode ";
            // 
            // batchCompile
            // 
            this.batchCompile.Location = new System.Drawing.Point(422, 69);
            this.batchCompile.Name = "batchCompile";
            this.batchCompile.Size = new System.Drawing.Size(153, 37);
            this.batchCompile.TabIndex = 19;
            this.batchCompile.Text = "Batch Compile";
            this.batchCompile.UseVisualStyleBackColor = true;
            this.batchCompile.Click += new System.EventHandler(this.BatchCompile_Click);
            // 
            // batchGpuFamilyList
            // 
            this.batchGpuFamilyList.Location = new System.Drawing.Point(119, 69);
            this.batchGpuFamilyList.Name = "batchGpuFamilyList";
            this.batchGpuFamilyList.Size = new System.Drawing.Size(268, 26);
            this.batchGpuFamilyList.TabIndex = 18;
            this.batchGpuFamilyList.Text = "Gfx11,Gfx103,Gfx10,Gfx9,Gfx8";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(17, 69);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(93, 20);
            this.label2.TabIndex = 17;
            this.label2.Text = "GPU Family";
            // 
            // batchApiList
            // 
            this.batchApiList.Location = new System.Drawing.Point(119, 27);
            this.batchApiList.Name = "batchApiList";
            this.batchApiList.Size = new System.Drawing.Size(268, 26);
            this.batchApiList.TabIndex = 1;
            this.batchApiList.Text = "DX12,VK,DX11,GL,CL,OGLP";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(64, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "API\'s";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.checkBoxGenerateCounterDocs);
            this.groupBox3.Location = new System.Drawing.Point(15, 142);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(1281, 71);
            this.groupBox3.TabIndex = 17;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = " Options ";
            // 
            // checkBoxGenerateCounterDocs
            // 
            this.checkBoxGenerateCounterDocs.AutoSize = true;
            this.checkBoxGenerateCounterDocs.Location = new System.Drawing.Point(19, 31);
            this.checkBoxGenerateCounterDocs.Name = "checkBoxGenerateCounterDocs";
            this.checkBoxGenerateCounterDocs.Size = new System.Drawing.Size(205, 24);
            this.checkBoxGenerateCounterDocs.TabIndex = 0;
            this.checkBoxGenerateCounterDocs.Text = "Generate Counter Docs";
            this.checkBoxGenerateCounterDocs.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AcceptButton = this.CompileButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1302, 907);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.GPUFamily);
            this.Controls.Add(this.apiName);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.IgnoreInvalidCountersCheckBox);
            this.Controls.Add(this.CompileButton);
            this.Controls.Add(this.groupBox1);
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MinimumSize = new System.Drawing.Size(589, 431);
            this.Name = "Form1";
            this.Text = "Public Counter Compiler";
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button CompileButton;
        private System.Windows.Forms.CheckBox IgnoreInvalidCountersCheckBox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        public System.Windows.Forms.TextBox apiName;
        public System.Windows.Forms.TextBox GPUFamily;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox batchApiList;
        private System.Windows.Forms.TextBox batchGpuFamilyList;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button batchCompile;
        private System.Windows.Forms.RichTextBox richTextBoxOutput;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.CheckBox checkBoxGenerateCounterDocs;
    }
}