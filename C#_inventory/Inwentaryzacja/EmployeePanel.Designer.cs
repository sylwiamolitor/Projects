
namespace Inwentaryzacja
{
    partial class EmployeePanel
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EmployeePanel));
            this.DisplayOrders = new System.Windows.Forms.Button();
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.DisplayEquipments = new System.Windows.Forms.Button();
            this.LogOut = new System.Windows.Forms.Button();
            this.DoTheOrder = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // DisplayOrders
            // 
            this.DisplayOrders.BackColor = System.Drawing.Color.RoyalBlue;
            this.DisplayOrders.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.DisplayOrders.FlatAppearance.BorderSize = 2;
            this.DisplayOrders.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.DisplayOrders.Location = new System.Drawing.Point(16, 10);
            this.DisplayOrders.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.DisplayOrders.Name = "DisplayOrders";
            this.DisplayOrders.Size = new System.Drawing.Size(353, 66);
            this.DisplayOrders.TabIndex = 0;
            this.DisplayOrders.Text = "Wyświetl zlecenia";
            this.DisplayOrders.UseVisualStyleBackColor = false;
            this.DisplayOrders.Click += new System.EventHandler(this.DisplayOrders_Click);
            // 
            // dataGridView
            // 
            dataGridViewCellStyle1.BackColor = System.Drawing.Color.PaleTurquoise;
            this.dataGridView.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dataGridView.BackgroundColor = System.Drawing.Color.PaleTurquoise;
            this.dataGridView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dataGridView.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.None;
            this.dataGridView.ColumnHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.Color.PaleTurquoise;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
            this.dataGridView.ColumnHeadersHeight = 29;
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle3.BackColor = System.Drawing.Color.PaleTurquoise;
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            dataGridViewCellStyle3.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle3.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dataGridView.DefaultCellStyle = dataGridViewCellStyle3;
            this.dataGridView.EnableHeadersVisualStyles = false;
            this.dataGridView.GridColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridView.Location = new System.Drawing.Point(15, 85);
            this.dataGridView.Margin = new System.Windows.Forms.Padding(6);
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle4.BackColor = System.Drawing.Color.PaleTurquoise;
            dataGridViewCellStyle4.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            dataGridViewCellStyle4.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle4.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle4.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle4.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView.RowHeadersDefaultCellStyle = dataGridViewCellStyle4;
            this.dataGridView.RowHeadersWidth = 51;
            dataGridViewCellStyle5.BackColor = System.Drawing.Color.PaleTurquoise;
            this.dataGridView.RowsDefaultCellStyle = dataGridViewCellStyle5;
            this.dataGridView.RowTemplate.DefaultCellStyle.BackColor = System.Drawing.Color.PaleTurquoise;
            this.dataGridView.Size = new System.Drawing.Size(693, 509);
            this.dataGridView.TabIndex = 2;
            // 
            // DisplayEquipments
            // 
            this.DisplayEquipments.BackColor = System.Drawing.Color.RoyalBlue;
            this.DisplayEquipments.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.DisplayEquipments.FlatAppearance.BorderSize = 2;
            this.DisplayEquipments.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.DisplayEquipments.Location = new System.Drawing.Point(378, 10);
            this.DisplayEquipments.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.DisplayEquipments.Name = "DisplayEquipments";
            this.DisplayEquipments.Size = new System.Drawing.Size(331, 66);
            this.DisplayEquipments.TabIndex = 3;
            this.DisplayEquipments.Text = "Wyświetl sprzęty";
            this.DisplayEquipments.UseVisualStyleBackColor = false;
            this.DisplayEquipments.Click += new System.EventHandler(this.DisplayEquipments_Click);
            // 
            // LogOut
            // 
            this.LogOut.BackColor = System.Drawing.Color.RoyalBlue;
            this.LogOut.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.LogOut.FlatAppearance.BorderSize = 2;
            this.LogOut.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.LogOut.Location = new System.Drawing.Point(507, 604);
            this.LogOut.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.LogOut.Name = "LogOut";
            this.LogOut.Size = new System.Drawing.Size(202, 56);
            this.LogOut.TabIndex = 4;
            this.LogOut.Text = "Wyloguj";
            this.LogOut.UseVisualStyleBackColor = false;
            this.LogOut.Click += new System.EventHandler(this.LogOut_Click);
            // 
            // DoTheOrder
            // 
            this.DoTheOrder.BackColor = System.Drawing.Color.RoyalBlue;
            this.DoTheOrder.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.DoTheOrder.FlatAppearance.BorderSize = 2;
            this.DoTheOrder.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.DoTheOrder.Location = new System.Drawing.Point(298, 604);
            this.DoTheOrder.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.DoTheOrder.Name = "DoTheOrder";
            this.DoTheOrder.Size = new System.Drawing.Size(202, 56);
            this.DoTheOrder.TabIndex = 5;
            this.DoTheOrder.Text = "Wykonaj zlecenie";
            this.DoTheOrder.UseVisualStyleBackColor = false;
            this.DoTheOrder.Click += new System.EventHandler(this.DoTheOrder_Click);
            // 
            // EmployeePanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 23F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.PaleTurquoise;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(730, 680);
            this.Controls.Add(this.DoTheOrder);
            this.Controls.Add(this.LogOut);
            this.Controls.Add(this.DisplayEquipments);
            this.Controls.Add(this.dataGridView);
            this.Controls.Add(this.DisplayOrders);
            this.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.Name = "EmployeePanel";
            this.Text = "EmployeePanel";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button DisplayOrders;
        private System.Windows.Forms.DataGridView dataGridView;
        private System.Windows.Forms.Button DisplayEquipments;
        private System.Windows.Forms.Button LogOut;
        private System.Windows.Forms.Button DoTheOrder;
    }
}