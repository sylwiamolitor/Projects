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
    public partial class ShowEquipmentPanel : Form
    {
        private ManagerPanel managerPanel;
        public ShowEquipmentPanel()
        {
            InitializeComponent();
            DataClasses1DataContext db = new DataClasses1DataContext();
            managerPanel = ManagerPanel.GetInstance;
            roomsList.MultiSelect = false;
            equipmentList.MultiSelect = false;
            roomsList.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            equipmentList.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            string jobPosition = (from u in db.Użytkowniks
                              where u.ID_użytkownika == managerPanel.UserId
                              select u.nazwa_stanowiska).ToList().First();

            switch (jobPosition)
            {
                case "KK":
                    var query = (from k in db.Katedras
                             where k.ID_kierownika_katedry == managerPanel.UserId
                                 join p in db.Pomieszczenies on k.ID_katedry equals p.Katedra_ID_katedry
                             select new { p.ID_pomieszczenia, Numer_pokoju = p.numer_pokoju, Typ_pomieszczenia = p.typ_pomieszczenia, Nazwa_katedry = k.nazwa_katedry }).ToList();

                roomsList.DataSource = query;
                    break;
                case "KW":
                   var facultyQuery = (from w in db.Wydziałs
                             where w.ID_kierownika_wydziału == managerPanel.UserId
                             join p in db.Pomieszczenies on w.ID_wydziału equals p.Wydział_ID_wydziału
                             select new { p.ID_pomieszczenia, Numer_pokoju = p.numer_pokoju, Typ_pomieszczenia = p.typ_pomieszczenia, Nazwa_wydziału = w.nazwa_wydziału }).ToList();

                roomsList.DataSource = facultyQuery;
                    break;
            }

            roomsList.Columns[0].Visible = false;
        }

        private void ShowEquipmentInThisRoom(Object sender, DataGridViewCellMouseEventArgs e)
        {
            DataClasses1DataContext db = new DataClasses1DataContext();

            if (e.RowIndex > 0)
            {
                var query =
          from Sprzet in db.Sprzęts
          where Sprzet.Pomieszczenie_ID_pomieszczenia == int.Parse(roomsList.Rows[e.RowIndex].Cells["ID_pomieszczenia"].Value.ToString())
          select new { Nazwa_sprzętu = Sprzet.nazwa_sprzętu, Stan = Sprzet.stan };

                equipmentList.DataSource = query.ToList();
            }
        }

        private void BackToManagerPanel(object sender, EventArgs e)
        {
            Hide();
            managerPanel.ShowDialog();
        }
    }
}
