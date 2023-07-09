namespace Inwentaryzacja
{
    partial class UserData
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserData));
            this.loginText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.passwordText = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.applyButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.firstNameText = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.lastNameText = new System.Windows.Forms.TextBox();
            this.jobPositionListBox = new System.Windows.Forms.ListBox();
            this.roomIDListBox = new System.Windows.Forms.ListBox();
            this.helpLabel = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.FacultyListBox = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // loginText
            // 
            this.loginText.BackColor = System.Drawing.Color.LightCyan;
            this.loginText.Location = new System.Drawing.Point(48, 42);
            this.loginText.Margin = new System.Windows.Forms.Padding(4);
            this.loginText.Name = "loginText";
            this.loginText.Size = new System.Drawing.Size(300, 30);
            this.loginText.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Location = new System.Drawing.Point(161, 13);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 23);
            this.label1.TabIndex = 1;
            this.label1.Text = "Login";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Location = new System.Drawing.Point(160, 105);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 23);
            this.label2.TabIndex = 2;
            this.label2.Text = "Hasło";
            // 
            // passwordText
            // 
            this.passwordText.BackColor = System.Drawing.Color.LightCyan;
            this.passwordText.Location = new System.Drawing.Point(48, 134);
            this.passwordText.Margin = new System.Windows.Forms.Padding(4);
            this.passwordText.Name = "passwordText";
            this.passwordText.Size = new System.Drawing.Size(300, 30);
            this.passwordText.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Location = new System.Drawing.Point(458, 13);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(173, 23);
            this.label3.TabIndex = 4;
            this.label3.Text = "Nazwa stanowiska";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.Color.Transparent;
            this.label5.Location = new System.Drawing.Point(117, 405);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(163, 23);
            this.label5.TabIndex = 8;
            this.label5.Text = "ID pomieszczenia";
            // 
            // applyButton
            // 
            this.applyButton.BackColor = System.Drawing.Color.RoyalBlue;
            this.applyButton.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.applyButton.FlatAppearance.BorderSize = 2;
            this.applyButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.applyButton.Location = new System.Drawing.Point(462, 657);
            this.applyButton.Margin = new System.Windows.Forms.Padding(4);
            this.applyButton.Name = "applyButton";
            this.applyButton.Size = new System.Drawing.Size(133, 33);
            this.applyButton.TabIndex = 10;
            this.applyButton.Text = "Zaakceptuj";
            this.applyButton.UseVisualStyleBackColor = false;
            this.applyButton.Click += new System.EventHandler(this.ClickAcceptButton);
            // 
            // cancelButton
            // 
            this.cancelButton.BackColor = System.Drawing.Color.RoyalBlue;
            this.cancelButton.FlatAppearance.BorderColor = System.Drawing.Color.MidnightBlue;
            this.cancelButton.FlatAppearance.BorderSize = 2;
            this.cancelButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cancelButton.Location = new System.Drawing.Point(164, 657);
            this.cancelButton.Margin = new System.Windows.Forms.Padding(4);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(103, 33);
            this.cancelButton.TabIndex = 11;
            this.cancelButton.Text = "Anuluj";
            this.cancelButton.UseVisualStyleBackColor = false;
            this.cancelButton.Click += new System.EventHandler(this.ClickCancelButton);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.Transparent;
            this.label4.Location = new System.Drawing.Point(161, 206);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 23);
            this.label4.TabIndex = 12;
            this.label4.Text = "Imię";
            // 
            // firstNameText
            // 
            this.firstNameText.BackColor = System.Drawing.Color.LightCyan;
            this.firstNameText.Location = new System.Drawing.Point(48, 234);
            this.firstNameText.Margin = new System.Windows.Forms.Padding(4);
            this.firstNameText.Name = "firstNameText";
            this.firstNameText.Size = new System.Drawing.Size(300, 30);
            this.firstNameText.TabIndex = 13;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.Color.Transparent;
            this.label6.Location = new System.Drawing.Point(160, 303);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(93, 23);
            this.label6.TabIndex = 14;
            this.label6.Text = "Nazwisko";
            // 
            // lastNameText
            // 
            this.lastNameText.BackColor = System.Drawing.Color.LightCyan;
            this.lastNameText.Location = new System.Drawing.Point(48, 332);
            this.lastNameText.Margin = new System.Windows.Forms.Padding(4);
            this.lastNameText.Name = "lastNameText";
            this.lastNameText.Size = new System.Drawing.Size(300, 30);
            this.lastNameText.TabIndex = 15;
            // 
            // jobPositionListBox
            // 
            this.jobPositionListBox.BackColor = System.Drawing.Color.PaleTurquoise;
            this.jobPositionListBox.FormattingEnabled = true;
            this.jobPositionListBox.ItemHeight = 23;
            this.jobPositionListBox.Items.AddRange(new object[] {
            "PT",
            "PTW",
            "KK",
            "KW",
            "A"});
            this.jobPositionListBox.Location = new System.Drawing.Point(510, 40);
            this.jobPositionListBox.Margin = new System.Windows.Forms.Padding(4);
            this.jobPositionListBox.Name = "jobPositionListBox";
            this.jobPositionListBox.Size = new System.Drawing.Size(69, 119);
            this.jobPositionListBox.TabIndex = 16;
            this.jobPositionListBox.SelectedIndexChanged += new System.EventHandler(this.PositionChanged);
            // 
            // roomIDListBox
            // 
            this.roomIDListBox.BackColor = System.Drawing.Color.PaleTurquoise;
            this.roomIDListBox.FormattingEnabled = true;
            this.roomIDListBox.ItemHeight = 23;
            this.roomIDListBox.Location = new System.Drawing.Point(121, 434);
            this.roomIDListBox.Margin = new System.Windows.Forms.Padding(4);
            this.roomIDListBox.Name = "roomIDListBox";
            this.roomIDListBox.Size = new System.Drawing.Size(144, 188);
            this.roomIDListBox.TabIndex = 17;
            // 
            // helpLabel
            // 
            this.helpLabel.AutoSize = true;
            this.helpLabel.BackColor = System.Drawing.Color.Transparent;
            this.helpLabel.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.helpLabel.Location = new System.Drawing.Point(29, 628);
            this.helpLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.helpLabel.Name = "helpLabel";
            this.helpLabel.Size = new System.Drawing.Size(713, 24);
            this.helpLabel.TabIndex = 18;
            this.helpLabel.Text = "Przy dodaniu wypełnij wszystkie pola, przy edycji pola wybrane do zmiany.";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.BackColor = System.Drawing.Color.Transparent;
            this.label7.Location = new System.Drawing.Point(433, 206);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(221, 23);
            this.label7.TabIndex = 19;
            this.label7.Text = "Nazwa katedry/wydziału";
            // 
            // FacultyListBox
            // 
            this.FacultyListBox.BackColor = System.Drawing.Color.PaleTurquoise;
            this.FacultyListBox.FormattingEnabled = true;
            this.FacultyListBox.ItemHeight = 23;
            this.FacultyListBox.Location = new System.Drawing.Point(385, 233);
            this.FacultyListBox.Margin = new System.Windows.Forms.Padding(4);
            this.FacultyListBox.Name = "FacultyListBox";
            this.FacultyListBox.Size = new System.Drawing.Size(319, 372);
            this.FacultyListBox.TabIndex = 20;
            this.FacultyListBox.SelectedIndexChanged += new System.EventHandler(this.FacultyListBox_SelectedIndexChanged);
            // 
            // UserData
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 23F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.PaleTurquoise;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(756, 727);
            this.Controls.Add(this.FacultyListBox);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.helpLabel);
            this.Controls.Add(this.roomIDListBox);
            this.Controls.Add(this.jobPositionListBox);
            this.Controls.Add(this.lastNameText);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.firstNameText);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.applyButton);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.passwordText);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.loginText);
            this.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "UserData";
            this.Text = "UserData";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox loginText;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox passwordText;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button applyButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox firstNameText;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox lastNameText;
        private System.Windows.Forms.ListBox jobPositionListBox;
        private System.Windows.Forms.ListBox roomIDListBox;
        private System.Windows.Forms.Label helpLabel;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ListBox FacultyListBox;
    }
}
