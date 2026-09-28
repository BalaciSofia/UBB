namespace lab2
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
            this.dgvT1 = new System.Windows.Forms.DataGridView();
            this.dgvT2 = new System.Windows.Forms.DataGridView();
            this.buttonSaveData = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgvT1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvT2)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvT1
            // 
            this.dgvT1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvT1.Location = new System.Drawing.Point(2, 3);
            this.dgvT1.Name = "dgvT1";
            this.dgvT1.RowHeadersWidth = 62;
            this.dgvT1.RowTemplate.Height = 28;
            this.dgvT1.Size = new System.Drawing.Size(537, 229);
            this.dgvT1.TabIndex = 0;
            // 
            // dgvT2
            // 
            this.dgvT2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvT2.Location = new System.Drawing.Point(2, 229);
            this.dgvT2.Name = "dgvT2";
            this.dgvT2.RowHeadersWidth = 62;
            this.dgvT2.RowTemplate.Height = 28;
            this.dgvT2.Size = new System.Drawing.Size(537, 220);
            this.dgvT2.TabIndex = 1;
            // 
            // buttonSaveData
            // 
            this.buttonSaveData.Location = new System.Drawing.Point(591, 218);
            this.buttonSaveData.Name = "buttonSaveData";
            this.buttonSaveData.Size = new System.Drawing.Size(111, 29);
            this.buttonSaveData.TabIndex = 2;
            this.buttonSaveData.Text = "Save Data";
            this.buttonSaveData.UseVisualStyleBackColor = true;
            this.buttonSaveData.Click += new System.EventHandler(this.buttonSaveData_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.buttonSaveData);
            this.Controls.Add(this.dgvT2);
            this.Controls.Add(this.dgvT1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load_1);
            ((System.ComponentModel.ISupportInitialize)(this.dgvT1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvT2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvT1;
        private System.Windows.Forms.DataGridView dgvT2;
        private System.Windows.Forms.Button buttonSaveData;
    }
}

