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
    public partial class AdminPanel : Form
    {

        private DataClasses1DataContext db { get; set; } = new DataClasses1DataContext();

        public AdminPanel()
        {
            InitializeComponent();
            ShowResults();
            dataGridView1.MultiSelect = false;
        }

        //add user
        private void ClickAddButton(object sender, EventArgs e) 
        {
            UserData userData = new UserData(1,0);
            userData.Show();

        }

        //edit user
        private void ClickEditButton(object sender, EventArgs e)
        {
            //if no row is selected
            if (dataGridView1.GetCellCount(DataGridViewElementStates.Selected) != 1)
            {
                int id = (int)dataGridView1.SelectedRows[0].Cells[0].Value;

                UserData userData = new UserData(2,id);
                userData.Show();
            }
            else
                HelpLabel.Text = "Nie wybrałeś użytkownika";
        }

        private void ClickDeleteButton(object sender, EventArgs e) //usuń użytkownika
        {
            //if no row is selected
            if (dataGridView1.GetCellCount(DataGridViewElementStates.Selected) != 1)
            {
                int id = (int)dataGridView1.SelectedRows[0].Cells[0].Value;

                var queryRemove =
                          (from user in db.Użytkowniks
                           where user.ID_użytkownika == id
                           select user).FirstOrDefault();

                if (queryRemove != null)
                {
                            var anyTasks =
                  (from task in db.Zlecenies
                   where task.Użytkownik_ID_użytkownika == id
                   select task).FirstOrDefault();
                    if (anyTasks == null)
                        db.Użytkowniks.DeleteOnSubmit(queryRemove);
                    else
                    {
                        HelpLabel.Text = "Użytkownik ma zadania, nie można go usunąć.";
                        return;
                    }

                    //remove manager connection
                    var queryRemoveConnection =
                          (from p in db.Pomieszczenies
                           where p.ID_pomieszczenia == queryRemove.Pomieszczenie_ID_pomieszczenia
                           select p).FirstOrDefault();

                    DeleteRoomsConnection(queryRemoveConnection.Katedra_ID_katedry,queryRemoveConnection.Wydział_ID_wydziału);
                    db.SubmitChanges();
                    ShowResults();
                }


            }
            else
                HelpLabel.Text = "Nie wybrałeś użytkownika";
        }

        //logout
        private void ClickLogOutButton(object sender, EventArgs e) 
        {
            this.Close();
        }

        //show results on screen
        public void ShowResults()
        {
            var query =
            from user in db.Użytkowniks
            let ID_pomieszczenia = user.Pomieszczenie_ID_pomieszczenia
            select new { user.ID_użytkownika, user.login, user.hasło, user.nazwa_stanowiska, ID_pomieszczenia,user.imię, user.nazwisko };
            dataGridView1.DataSource = query.ToList();

            for(int i =0; i<dataGridView1.Columns.Count; i++)
            {
                dataGridView1.Columns[i].AutoSizeMode=DataGridViewAutoSizeColumnMode.AllCells;
            }
            this.AutoSize = true;
            this.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            int widthD = dataGridView1.Columns.GetColumnsWidth(DataGridViewElementStates.Visible);
            int heightD = dataGridView1.Rows.GetRowsHeight(DataGridViewElementStates.Visible);
            this.Width = widthD;
            this.Height = heightD;
        }

        private void ClickShowResultsButton(object sender, EventArgs e)
        {
            ShowResults(); 
        }
        //remove manager connection
        private void DeleteRoomsConnection(int? IDKat, int? IDFac)
        {
            if (IDKat != null)
            {
                var editedFaculty =
             from f in db.Katedras
             where f.ID_katedry == IDKat
             select f;

                editedFaculty.FirstOrDefault().ID_kierownika_katedry = null;
            }
            else
            {
                var editedFaculty =
            from f in db.Wydziałs
            where f.ID_wydziału == IDFac
            select f;

                editedFaculty.FirstOrDefault().ID_kierownika_wydziału = null;

            }
        }

    }

}
