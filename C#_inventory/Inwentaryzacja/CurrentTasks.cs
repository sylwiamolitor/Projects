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

    public partial class CurrentTasks : Form
    {
        private int UserId { get; set; }
        private Użytkownik CurrentUser { get; set; }
        private string Position { get; set; }
        private ManagerPanel managerPanel;
        private EmployeePanel employeePanel;

        private void GridViewUpdate()
        {
            DataClasses1DataContext db = new DataClasses1DataContext();

            switch (Position)
            {
                case "PT":
                case "PTW": //select tasks, which was assigned to PT / PTW
                    {
                        dataGridView1.DataSource = (from t in db.Zlecenies
                                                    where UserId == t.Użytkownik_ID_użytkownika && t.stan == "nieaktywne" //only active tasks
                                                    select new { t.typ_zlecenia, t.id_zlecenia, t.stan, t.Użytkownik_ID_użytkownika, t.Pomieszczenie_ID_pomieszczenia }).ToList();
                    }
                    break;
                case "KW": //select tasks, which was created by KW
                    {
                        dataGridView1.DataSource = (from z in db.Zlecenies
                                                    join p in db.Pomieszczenies on CurrentUser.Pomieszczenie_ID_pomieszczenia equals p.ID_pomieszczenia
                                                    join pp in db.Pomieszczenies on z.Pomieszczenie_ID_pomieszczenia equals pp.ID_pomieszczenia
                                                    where p.Wydział_ID_wydziału == pp.Wydział_ID_wydziału && pp.Katedra == null
                                                    select new { z.typ_zlecenia, z.id_zlecenia, z.stan, z.Użytkownik_ID_użytkownika, z.Pomieszczenie_ID_pomieszczenia, pp.Wydział_ID_wydziału }).ToList();
                    }
                    break;
                case "KK": //select tasks, which was created by KK
                    {
                        dataGridView1.DataSource = (from z in db.Zlecenies
                                                    join p in db.Pomieszczenies on CurrentUser.Pomieszczenie_ID_pomieszczenia equals p.ID_pomieszczenia
                                                    join pp in db.Pomieszczenies on z.Pomieszczenie_ID_pomieszczenia equals pp.ID_pomieszczenia
                                                    where p.Katedra_ID_katedry == pp.Katedra_ID_katedry
                                                    select new { z.typ_zlecenia, z.id_zlecenia, z.stan, z.Użytkownik_ID_użytkownika, z.Pomieszczenie_ID_pomieszczenia, pp.Katedra_ID_katedry }).ToList();
                    }
                    break;

            }
            dataGridView1.Columns[0].HeaderText = "typ";
            dataGridView1.Columns[1].HeaderText = "id";
            dataGridView1.Columns[3].HeaderText = "ID_użytkownika";
            dataGridView1.Columns[4].HeaderText = "ID_pomieszczenia";


        }
        public CurrentTasks(int userID)
        {
            InitializeComponent();

            DataClasses1DataContext db = new DataClasses1DataContext();

            UserId = userID;
            var user = from u in db.Użytkowniks
                       where u.ID_użytkownika == UserId
                       select u;
            CurrentUser = user.FirstOrDefault();
            if (CurrentUser.nazwa_stanowiska == "KK" || CurrentUser.nazwa_stanowiska == "KW")
                managerPanel = ManagerPanel.GetInstance;
            else
                employeePanel = EmployeePanel.Instance;

            dataGridView1.MultiSelect = false;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView2.MultiSelect = false;
            dataGridView2.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            Position = CurrentUser.nazwa_stanowiska;
            GridViewUpdate();
        

          
        }
        
        private void onRowTaskCLick(object sender, DataGridViewCellEventArgs e)
        {
            DataClasses1DataContext db = new DataClasses1DataContext();

            dataGridView2.DataSource = null;
            dataGridView2.Rows.Clear();
            dataGridView2.Columns.Clear();
            var roomID = (int)dataGridView1.SelectedRows[0].Cells[4].Value;
            var taskType = (string)dataGridView1.SelectedRows[0].Cells[0].Value;
            var query2 = from s in db.Sprzęts
                         where s.Pomieszczenie_ID_pomieszczenia == roomID
                         select new { s.ID_sprzętu, s.nazwa_sprzętu, s.Pomieszczenie_ID_pomieszczenia, s.stan };
            switch (Position)
            {
                case "PT":
                case "PTW":
                    {
                        switch (taskType)
                        {
                            case "N":
                                {
                                    if (!dataGridView2.Columns.Contains("nazwa"))
                                    {
                                        DataGridViewColumn c = new DataGridViewTextBoxColumn();
                                        c.HeaderText = "nazwa";
                                        c.Name = "nazwa";
                                        dataGridView2.Columns.Add(c);
                                        dataGridView2.Columns["nazwa"].ReadOnly = false;
                                    }
                                }
                                break;
                            case "U":
                                {

                                    if (!dataGridView2.Columns.Contains("isdead"))
                                    {
                                        DataGridViewCheckBoxColumn c = new DataGridViewCheckBoxColumn();
                                        c.HeaderText = "do usunięcia";
                                        c.Name = "isdead";
                                        c.TrueValue = 1;
                                        dataGridView2.Columns.Add(c);
                                    }
                                    dataGridView2.DataSource = (from s in db.Sprzęts
                                                                where s.Pomieszczenie_ID_pomieszczenia == roomID && s.stan == "do zezlomowania"
                                                                select new { s.ID_sprzętu, s.nazwa_sprzętu, s.Pomieszczenie_ID_pomieszczenia, s.stan }).ToList();
                                    foreach (DataGridViewColumn dc in dataGridView2.Columns)
                                    {
                                        dc.ReadOnly = true;
                                    }
                                    dataGridView2.Columns["isdead"].ReadOnly = false;
                                }
                                break;
                            case "A":
                                {
                                    if (!dataGridView2.Columns.Contains("nowy stan"))
                                    {
                                        DataGridViewComboBoxColumn c = new DataGridViewComboBoxColumn
                                        {
                                            HeaderText = "nowy stan"
                                        };
                                        c.Items.Add("dobry");
                                        c.Items.Add("do zezlomowania");
                                        c.Items.Add("do naprawy");
                                        c.Items.Add("w naprawie");
                                        c.Name = "nowy stan";
                                        dataGridView2.Columns.Add(c);
                                    }
                                    dataGridView2.DataSource = query2.ToList();

                                    foreach (DataGridViewColumn dc in dataGridView2.Columns)
                                    {
                                        dc.ReadOnly = true;
                                    }
                                    dataGridView2.Columns["nowy stan"].ReadOnly = false;
                                }
                                break;
                        }
                    }
                    break;
                case "KK":
                case "KW":
                    {
                        dataGridView2.DataSource = query2.ToList();
                    }
                    break;
            }
        }

        private void SubmitButtonClick(object sender, EventArgs e)
        {
            
            var taskType = (string)dataGridView1.SelectedRows[0].Cells[0].Value;
            DataClasses1DataContext db = new DataClasses1DataContext();
            var selectedTask = (from z in db.Zlecenies
                                where z.id_zlecenia == (int)dataGridView1.SelectedRows[0].Cells[1].Value
                                select z).ToList()[0];
            switch (Position)
            {
                case "PT":
                case "PTW":
                    {
                        switch (taskType)
                        {
                            case "N":
                                {
                                    foreach (DataGridViewRow r in dataGridView2.Rows)
                                    {
                                        if (r.Cells[0].Value != null)
                                        {
                                            Sprzęt s = new Sprzęt();
                                            s.nazwa_sprzętu = r.Cells[0].Value.ToString();
                                            s.numer_inwentaryzacyjny = selectedTask.id_zlecenia + selectedTask.Pomieszczenie_ID_pomieszczenia;
                                            s.Pomieszczenie_ID_pomieszczenia = selectedTask.Pomieszczenie_ID_pomieszczenia;
                                            s.stan = "dobry";
                                            db.Sprzęts.InsertOnSubmit(s);

                                        }
                                    }
                                    selectedTask.stan = "ukonczone";
                                    GridViewUpdate();
                                    try
                                    {
                                        db.SubmitChanges();
                                        MessageBox.Show("Zlecenie ukończone!");
                                    }
                                    catch
                                    {
                                        MessageBox.Show("Nie udało się ukończyć zlecenia");
                                    }
                                }
                                break;
                            case "A":
                                {
                                    foreach (DataGridViewRow r in dataGridView2.Rows)
                                    {
                                        var selectEquipment = (from s in db.Sprzęts
                                                               where (int)r.Cells[1].Value == s.ID_sprzętu
                                                               select s).ToList()[0];
                                        if (r.Cells[0].Value != null) //if new state was not selected
                                            selectEquipment.stan = r.Cells[0].Value.ToString(); //new state
                                    }
                                    selectedTask.stan = "ukonczone";
                                    GridViewUpdate();
                                    try
                                    {
                                        db.SubmitChanges();
                                        MessageBox.Show("Zlecenie ukończone!");
                                    }
                                    catch
                                    {
                                        MessageBox.Show("Nie udało się ukończyć zlecenia");
                                    }
                                }
                                break;
                            case "U":
                                {
                                    foreach (DataGridViewRow r in dataGridView2.Rows)
                                    {
                                        DataGridViewCheckBoxCell c = (DataGridViewCheckBoxCell)r.Cells["isdead"];
                                        if (c.Value == c.TrueValue)
                                        {
                                            var q = from s in db.Sprzęts
                                                    where s.ID_sprzętu == (int)r.Cells[1].Value
                                                    select s;
                                            q.FirstOrDefault().stan = "usunięte";
                                        }
                                    }
                                    selectedTask.stan = "ukonczone";
                                    GridViewUpdate();
                                    try
                                    {
                                        db.SubmitChanges();
                                        MessageBox.Show("Zlecenie ukończone!");
                                    }
                                    catch
                                    {
                                        MessageBox.Show("Nie udało się ukończyć zlecenia");
                                    }
                                }
                                break;
                        }


                    }
                    break;
                case "KK":
                case "KW":
                    {
                        if (selectedTask.stan == "ukonczone")
                        {
                            if(selectedTask.typ_zlecenia == "U")
                            {
                                var toDestroy = (from s in db.Sprzęts
                                                 where s.stan == "usunięte" && selectedTask.Pomieszczenie_ID_pomieszczenia == s.Pomieszczenie_ID_pomieszczenia
                                                 select s).ToList();
                                foreach(var s in toDestroy)
                                db.Sprzęts.DeleteOnSubmit(s);
                            }
                            db.Zlecenies.DeleteOnSubmit(selectedTask);
                            try
                            {
                                db.SubmitChanges();
                                MessageBox.Show("Zlecenie zatwierdzone");
                            }
                            catch
                            {
                                MessageBox.Show("Nie udało się zatwierdzić zlecenia");
                            }
                        }
                        else
                            MessageBox.Show("Zlecenie jeszcze nieukończone");
                    }
                    break;
            }

            dataGridView2.DataSource = null;
            dataGridView2.Rows.Clear();
            dataGridView2.Columns.Clear();
            GridViewUpdate();
        }




        private void CloseClick(object sender, EventArgs e)
        {
            switch (Position)
            {
                case "PT":
                case "PTW":
                    this.Close();
                    employeePanel.ShowDialog();
                    break;
                case "KK":
                case "KW":
                    this.Close();
                    managerPanel.ShowDialog();
                    break;
            }
            this.Close();

        }

        private void Help_button_Click(object sender, EventArgs e)
        {
            //manager
            if(Position=="KW" || Position== "KK")
            MessageBox.Show("W aktulnych zleceniach wyświetlają się zlecenia dla twojej katedry/wydziału.\nPo kliknięciu w zlecenie, po prawej stronie widoczna jest lista sprzętów dla wybranego zlecenia." +
                "\nPrzycisk zatwierdź służy do zaakceptowania ukończonego zlecenia.\nPowrót- cofa cię do poprzedniego panelu.","    Pomoc");

            if(Position=="PT" || Position=="PTW")
                MessageBox.Show("Po lewej stronie widoczne są zlecenia do wykonania. Po kliknięciu na zlecenie po prawej stronie widoczna jest lista sprzętów dla tego zlecenia." +
                    "\nW zależności od typu zlecenia możliwe są inne akcje. " +
                    "\nTypy zleceń:" +
                    "\nN(Nowy)- po prawej należy wpisać nazwę nowego sprzętu, reszta parametrów jest nadawana autoamtycznie," +
                    "\nU(Usunięcie)- Dla każdego sprzętu ze statusem \"do zezlomowania\" należy wybrać sprzęt, który ma zostać usunięty(zaznaczając checkboxa)" +
                    "\nA(Aktualny sprzęt)- Dla każdego ze sprzętów jest możliwość zmiany ich stanów." +
                    "\nPrzycisk zatwierdź służy do przekazania ukończonego zlecenia do akceptacji przez kierownika.\nPowrót- cofa cię do poprzedniego panelu.", "    Pomoc");
        }
    }
}
