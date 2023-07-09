using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Inwentaryzacja
{
    public partial class ShowEmployeesPanel : Form
    {
        private ManagerPanel managerPanel;
        public ShowEmployeesPanel()
        {
            InitializeComponent();
            DataClasses1DataContext db = new DataClasses1DataContext();
            managerPanel = ManagerPanel.GetInstance;
            employeesList.MultiSelect = false;
            string jobPosition = (from u in db.Użytkowniks
                                  where u.ID_użytkownika == managerPanel.UserId
                                  select u.nazwa_stanowiska).ToList().First();
            switch (jobPosition)
            {
                case "KK":
                    var query = (from u in db.Użytkowniks
                                 where u.nazwa_stanowiska == "PT"
                                 join p in db.Pomieszczenies on u.Pomieszczenie_ID_pomieszczenia equals p.ID_pomieszczenia
                                 join k in db.Katedras on p.Katedra_ID_katedry equals k.ID_katedry
                                 where k.ID_kierownika_katedry == managerPanel.UserId
                                 select new { Imię = u.imię, Nazwisko = u.nazwisko, Login = u.login, Numer_pokoju = p.numer_pokoju }).ToList();
                    employeesList.DataSource = query;
                    break;
                case "KW":
                    var facultyQuery = (from u in db.Użytkowniks
                                        where u.nazwa_stanowiska == "PTW"
                                        join p in db.Pomieszczenies on u.Pomieszczenie_ID_pomieszczenia equals p.ID_pomieszczenia
                                        join w in db.Wydziałs on p.Wydział_ID_wydziału equals w.ID_wydziału
                                        where w.ID_kierownika_wydziału == managerPanel.UserId
                                        select new { Imię = u.imię, Nazwisko = u.nazwisko, Login = u.login, Numer_pokoju = p.numer_pokoju }).ToList();
                    employeesList.DataSource = facultyQuery;
                    break;
            }
        }

        private void BackToManagerPanel(object sender, EventArgs e)
        {
            Hide();
            managerPanel.ShowDialog();
        }
    }
}
