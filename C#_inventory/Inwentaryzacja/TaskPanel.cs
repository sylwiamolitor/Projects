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
    public partial class TaskPanel : Form
    {
        private ManagerPanel managerPanel;
        private string Position { get; set; }
        public TaskPanel(int id)
        {
            InitializeComponent();

            managerPanel = ManagerPanel.GetInstance;

            dataGridView2.MultiSelect = false;
            dataGridView2.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView1.MultiSelect = false;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            radioButtonCheck.Checked = true;
            DataClasses1DataContext db = new DataClasses1DataContext();




            var emp = (from u in db.Użytkowniks
                       where u.ID_użytkownika == id
                       select u).ToList();
            Position = emp[0].nazwa_stanowiska;
            if (emp.Count() > 0 && Position == "KW")
            {
                dataGridView1.DataSource = (from u in db.Użytkowniks
                                            join p in db.Pomieszczenies on emp[0].Pomieszczenie_ID_pomieszczenia equals p.ID_pomieszczenia
                                            join pp in db.Pomieszczenies on u.Pomieszczenie_ID_pomieszczenia equals pp.ID_pomieszczenia
                                            where u.nazwa_stanowiska == "PTW" && p.Wydział_ID_wydziału == pp.Wydział_ID_wydziału
                                            select new { u.ID_użytkownika, u.login, u.nazwa_stanowiska }).ToList();



                dataGridView2.DataSource = (from p in db.Pomieszczenies
                                            join pp in db.Pomieszczenies on emp[0].Pomieszczenie_ID_pomieszczenia equals pp.ID_pomieszczenia
                                            where p.Katedra_ID_katedry.ToString() == null && p.Wydział_ID_wydziału == pp.Wydział_ID_wydziału
                                            orderby p.Wydział_ID_wydziału
                                            select new { p.ID_pomieszczenia, p.numer_pokoju, p.Wydział_ID_wydziału, p.typ_pomieszczenia }).ToList();
            }
            else if (emp.Count() > 0)
            {
                dataGridView1.DataSource = (from u in db.Użytkowniks
                                            join p in db.Pomieszczenies on u.Pomieszczenie_ID_pomieszczenia equals p.ID_pomieszczenia
                                            join pp in db.Pomieszczenies on emp[0].Pomieszczenie_ID_pomieszczenia equals pp.ID_pomieszczenia
                                            where u.nazwa_stanowiska == "PT" && p.Katedra_ID_katedry == pp.Katedra_ID_katedry
                                            select new { u.ID_użytkownika, u.login, u.nazwa_stanowiska }).ToList();


                dataGridView2.DataSource = (from p in db.Pomieszczenies
                                            join k in db.Katedras on p.Katedra_ID_katedry equals k.ID_katedry
                                            join pp in db.Pomieszczenies on emp[0].Pomieszczenie_ID_pomieszczenia equals pp.ID_pomieszczenia
                                            where p.Katedra_ID_katedry.ToString() != null && k.ID_kierownika_katedry == id && pp.Katedra_ID_katedry == p.Katedra_ID_katedry
                                            orderby p.Wydział_ID_wydziału, p.Katedra_ID_katedry
                                            select new { p.ID_pomieszczenia, p.numer_pokoju, p.Wydział_ID_wydziału, p.Katedra_ID_katedry, p.typ_pomieszczenia }).ToList();
            }
        }

        private void CreateTaskClick(object sender, EventArgs e)
        {

            Zlecenie newZlecenie = new Zlecenie
            {
                stan = "nieaktywne",
                Użytkownik_ID_użytkownika = (int)dataGridView1.SelectedRows[0].Cells[0].Value,
                Pomieszczenie_ID_pomieszczenia = (int)dataGridView2.SelectedRows[0].Cells[0].Value
            };
            if (radioButtonAdd.Checked)
                newZlecenie.typ_zlecenia = "N";
            else if (radioButtonDelete.Checked)
                newZlecenie.typ_zlecenia = "U";
            else
                newZlecenie.typ_zlecenia = "A";

            DataClasses1DataContext db = new DataClasses1DataContext();
            var query = from z in db.Zlecenies
                        where newZlecenie.Pomieszczenie_ID_pomieszczenia == z.Pomieszczenie_ID_pomieszczenia && newZlecenie.typ_zlecenia == z.typ_zlecenia
                        select z;
            if(query.Count()==0)
            {
                db.Zlecenies.InsertOnSubmit(newZlecenie);
                try
                {
                    db.SubmitChanges();
                    MessageBox.Show("Zlecenie utworzone poprawne");
                }
                catch
                {
                    MessageBox.Show("Nie można utworzyć zlecenia");
                }
            }

            else
                MessageBox.Show("Zlecenie już istnieje");
        }

        private void CloseClick(object sender, EventArgs e)
        {
            this.Close();
            managerPanel.ShowDialog();
        }

        private void Help_button_Click(object sender, EventArgs e)
        {
                MessageBox.Show("Po lewej widoczni są pracownicy na twojej katedrze/wydziale.\nPo prawej widoczne są pomieszczenia na twojej katedrze/wydziale.\nPrzycisk Utwórz tworzy zlecenie" +
                   " dla wybranego pracownika na wybrane pomieszczenie." +
                   "\nPrzed utworzeniem zlecenia pamiętaj o wyborze jego typu(służą do tego radio buttony). Domyślnie zaznaczona jest opcja sprawdź sprzęt." +
                   "\nPrzycisk Powrót cofa cię do poprzedniego panelu.", "    Pomoc");
        }
    }
}
