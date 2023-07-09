
namespace Inwentaryzacja
{
    partial class ManagerPanel
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ManagerPanel));
            this.CreateOrder = new System.Windows.Forms.Button();
            this.ShowActualOrder = new System.Windows.Forms.Button();
            this.ShowDevice = new System.Windows.Forms.Button();
            this.LogoutButton = new System.Windows.Forms.Button();
            this.ShowEmployees = new System.Windows.Forms.Button();
            this.GeneratingReport = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // CreateOrder
            // 
            this.CreateOrder.BackColor = System.Drawing.Color.RoyalBlue;
            this.CreateOrder.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.CreateOrder.FlatAppearance.BorderSize = 2;
            this.CreateOrder.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.CreateOrder.Location = new System.Drawing.Point(22, 62);
            this.CreateOrder.Margin = new System.Windows.Forms.Padding(6);
            this.CreateOrder.Name = "CreateOrder";
            this.CreateOrder.Size = new System.Drawing.Size(496, 40);
            this.CreateOrder.TabIndex = 0;
            this.CreateOrder.Text = "Stwórz zlecenie";
            this.CreateOrder.UseVisualStyleBackColor = false;
            this.CreateOrder.Click += new System.EventHandler(this.CreateOrder_Click);
            // 
            // ShowActualOrder
            // 
            this.ShowActualOrder.BackColor = System.Drawing.Color.RoyalBlue;
            this.ShowActualOrder.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.ShowActualOrder.FlatAppearance.BorderSize = 2;
            this.ShowActualOrder.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ShowActualOrder.Location = new System.Drawing.Point(22, 138);
            this.ShowActualOrder.Margin = new System.Windows.Forms.Padding(6);
            this.ShowActualOrder.Name = "ShowActualOrder";
            this.ShowActualOrder.Size = new System.Drawing.Size(496, 40);
            this.ShowActualOrder.TabIndex = 1;
            this.ShowActualOrder.Text = "Wyświetl aktualne zlecenia";
            this.ShowActualOrder.UseVisualStyleBackColor = false;
            this.ShowActualOrder.Click += new System.EventHandler(this.ShowActualOrder_Click);
            // 
            // ShowDevice
            // 
            this.ShowDevice.BackColor = System.Drawing.Color.RoyalBlue;
            this.ShowDevice.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.ShowDevice.FlatAppearance.BorderSize = 2;
            this.ShowDevice.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ShowDevice.Location = new System.Drawing.Point(22, 208);
            this.ShowDevice.Margin = new System.Windows.Forms.Padding(6);
            this.ShowDevice.Name = "ShowDevice";
            this.ShowDevice.Size = new System.Drawing.Size(496, 40);
            this.ShowDevice.TabIndex = 2;
            this.ShowDevice.Text = "Wyświetl sprzęt";
            this.ShowDevice.UseVisualStyleBackColor = false;
            this.ShowDevice.Click += new System.EventHandler(this.ShowDevice_Click);
            // 
            // LogoutButton
            // 
            this.LogoutButton.BackColor = System.Drawing.Color.RoyalBlue;
            this.LogoutButton.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.LogoutButton.FlatAppearance.BorderSize = 2;
            this.LogoutButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.LogoutButton.Location = new System.Drawing.Point(22, 434);
            this.LogoutButton.Margin = new System.Windows.Forms.Padding(6);
            this.LogoutButton.Name = "LogoutButton";
            this.LogoutButton.Size = new System.Drawing.Size(496, 40);
            this.LogoutButton.TabIndex = 3;
            this.LogoutButton.Text = "Wyloguj";
            this.LogoutButton.UseVisualStyleBackColor = false;
            this.LogoutButton.Click += new System.EventHandler(this.LogoutButton_Click);
            // 
            // ShowEmployees
            // 
            this.ShowEmployees.BackColor = System.Drawing.Color.RoyalBlue;
            this.ShowEmployees.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.ShowEmployees.FlatAppearance.BorderSize = 2;
            this.ShowEmployees.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ShowEmployees.Location = new System.Drawing.Point(22, 286);
            this.ShowEmployees.Margin = new System.Windows.Forms.Padding(6);
            this.ShowEmployees.Name = "ShowEmployees";
            this.ShowEmployees.Size = new System.Drawing.Size(496, 40);
            this.ShowEmployees.TabIndex = 4;
            this.ShowEmployees.Text = "Wyświetl pracowników";
            this.ShowEmployees.UseVisualStyleBackColor = false;
            this.ShowEmployees.Click += new System.EventHandler(this.ShowEmployees_Click);
            // 
            // GeneratingReport
            // 
            this.GeneratingReport.BackColor = System.Drawing.Color.RoyalBlue;
            this.GeneratingReport.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.GeneratingReport.FlatAppearance.BorderSize = 2;
            this.GeneratingReport.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.GeneratingReport.Location = new System.Drawing.Point(22, 362);
            this.GeneratingReport.Margin = new System.Windows.Forms.Padding(6);
            this.GeneratingReport.Name = "GeneratingReport";
            this.GeneratingReport.Size = new System.Drawing.Size(496, 40);
            this.GeneratingReport.TabIndex = 5;
            this.GeneratingReport.Text = "Generuj raport";
            this.GeneratingReport.UseVisualStyleBackColor = false;
            this.GeneratingReport.Click += new System.EventHandler(this.GeneratingReport_Click);
            // 
            // ManagerPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 23F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.PaleTurquoise;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(540, 512);
            this.Controls.Add(this.GeneratingReport);
            this.Controls.Add(this.ShowEmployees);
            this.Controls.Add(this.LogoutButton);
            this.Controls.Add(this.ShowDevice);
            this.Controls.Add(this.ShowActualOrder);
            this.Controls.Add(this.CreateOrder);
            this.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.Margin = new System.Windows.Forms.Padding(6);
            this.Name = "ManagerPanel";
            this.Text = "ManagerPanel";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button CreateOrder;
        private System.Windows.Forms.Button ShowActualOrder;
        private System.Windows.Forms.Button ShowDevice;
        private System.Windows.Forms.Button LogoutButton;
        private System.Windows.Forms.Button ShowEmployees;
        private System.Windows.Forms.Button GeneratingReport;
    }
}