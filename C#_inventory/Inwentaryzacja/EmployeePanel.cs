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
    public partial class EmployeePanel : Form
    {
        // PROPERTIES
        private bool IsDepartment { get; set; }
        private int UserId { get; set; }
        private Użytkownik CurrentUser { get; set; }
        private DataClasses1DataContext DataBase { get; set; } = new DataClasses1DataContext();

        // STATIC PROPERTIES
        public static EmployeePanel Instance { get; set; }

        // METHODS
        public EmployeePanel(int id)
        {
            InitializeComponent();
            Instance = this;
            UserId = id;
            dataGridView.MultiSelect = false;
            // query about current user
            var query =
            from Użytkownik in DataBase.Użytkowniks
            where Użytkownik.ID_użytkownika == UserId
            select Użytkownik;

            CurrentUser = query.FirstOrDefault();

            // check if current user belongs to department
            if(CurrentUser.Pomieszczenie.Katedra == null)
            {
                IsDepartment = true;
            }
            else
            {
                IsDepartment = false;
            }
        }

        private void DisplayOrders_Click(object sender, EventArgs e)
        {
            if (IsDepartment == true)
            {
                SetOrdersFromDepartment();
            }
            else
            {
                SetOrdersFromCathedral();
            }
        }

        private void SetOrdersFromDepartment()
        {
                var query =
            from Zlecenie in DataBase.Zlecenies
            where Zlecenie.Pomieszczenie.Katedra == null
            where Zlecenie.Użytkownik.ID_użytkownika == UserId
            select new { Zlecenie.Pomieszczenie.numer_pokoju, Zlecenie.stan };

            // set query result into dataGridView
            dataGridView.DataSource = query.ToList();
        }

        private void SetOrdersFromCathedral()
        {
                var query =
            from Zlecenie in DataBase.Zlecenies
            where Zlecenie.Pomieszczenie.Katedra_ID_katedry == CurrentUser.Pomieszczenie.Katedra_ID_katedry
            where Zlecenie.Użytkownik.ID_użytkownika == UserId
            select new { Zlecenie.Pomieszczenie.numer_pokoju, Zlecenie.stan };

            // set query result into dataGridView
            dataGridView.DataSource = query.ToList();
        }

        private void DisplayEquipments_Click(object sender, EventArgs e)
        {
            if (IsDepartment == true)
            {
                SetEquipmentFromDepartment();
            }
            else
            {
                SetEquipmentFromCathedral();
            }
        }

        private void SetEquipmentFromDepartment()
        {
                var query =
            from Sprzęt in DataBase.Sprzęts
            where Sprzęt.Pomieszczenie.Katedra == null
            where Sprzęt.Pomieszczenie.Wydział_ID_wydziału == CurrentUser.Pomieszczenie.Wydział_ID_wydziału
            select new { Sprzęt.nazwa_sprzętu, Sprzęt.Pomieszczenie.numer_pokoju, Sprzęt.stan };

            // set query result into dataGridView
            dataGridView.DataSource = query.ToList();
        }

        private void SetEquipmentFromCathedral()
        {
                var query =
            from Sprzęt in DataBase.Sprzęts
            where Sprzęt.Pomieszczenie.Katedra_ID_katedry == CurrentUser.Pomieszczenie.Katedra_ID_katedry
            select new { Sprzęt.nazwa_sprzętu, Sprzęt.Pomieszczenie.numer_pokoju, Sprzęt.stan };

            // set query result into dataGridView
            dataGridView.DataSource = query.ToList();
        }

        private void DoTheOrder_Click(object sender, EventArgs e)
        {
            // Close this window
            Hide();

            // Open window called CurrentTasks
            var myForm = new CurrentTasks(CurrentUser.ID_użytkownika);
            myForm.Show();
        }

        private void LogOut_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
