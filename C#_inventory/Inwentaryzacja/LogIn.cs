using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.Linq;
//using System.Data.Entity;

namespace Inwentaryzacja
{
    public partial class LogIn : Form
    {

        private int counter { get; set; }
        private DataClasses1DataContext db { get; set; } = new DataClasses1DataContext();

        public LogIn()
        {
            InitializeComponent();
        }

        private void ClickLoginButton(object sender, EventArgs e)
        {
            //checking if other
            //wants to log in, while another is logged in
            counter=0;
            FormCollection fc = Application.OpenForms;
            foreach (Form frm in fc)
            {
                counter++;
                if (counter > 1)
                    return;
            }


            Użytkownik currentUser = db.Użytkowniks.Where(t => t.login == loginText.Text && t.hasło == passwordText.Text).AsEnumerable().FirstOrDefault(t => t.login == loginText.Text && t.hasło == passwordText.Text);
            if (currentUser != null)
            {
                string position = currentUser.nazwa_stanowiska;
                switch (position)
                {
                    case "PT":
                    case "PTW":
                        EmployeePanel employeePanel = new EmployeePanel(currentUser.ID_użytkownika);
                        employeePanel.Show();
                        break;
                    case "KK":
                    case "KW":
                        ManagerPanel managerPanel = new ManagerPanel(currentUser.ID_użytkownika);
                        managerPanel.UserId = currentUser.ID_użytkownika;
                        managerPanel.Show();
                        break;
                    case "A":
                        AdminPanel adminPanel = new AdminPanel();
                        adminPanel.Show();
                        break;
                  }
            }
        }

        private void EndClick(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
