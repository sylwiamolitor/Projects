using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Inwentaryzacja
{
    public partial class UserData : Form
    {
        private DataClasses1DataContext db { get; set; } = new DataClasses1DataContext();

        private int Decision { get; set; }
        private int ID { get; set; }
        public UserData(int decision, int id)
        {
            InitializeComponent();
            this.Decision = decision;
            this.ID = id;
        }

        private void ClickCancelButton(object sender, EventArgs e) //cancel
        {
            this.Close();
        }

        private void ClickAcceptButton(object sender, EventArgs e) //accept
        {

            //case sensitive
            if (db.Użytkowniks.Where(t => t.login == loginText.Text).AsEnumerable().FirstOrDefault(t => t.login == loginText.Text) != null)
            {
                helpLabel.Text = "Użytkownik o takim loginie już istnieje!";
                return;
            }

            //if adding new user
            if (Decision == 1)
            {
                if (FacultyListBox.SelectedIndex == -1 || roomIDListBox.SelectedIndex == -1 || jobPositionListBox.SelectedIndex == -1)
                {
                    helpLabel.Text = "Proszę zaznacz stanowisko i pokój albo kliknij anuluj, aby wyjść.";
                    return;
                }
                foreach (Control txtBox in this.Controls)
                {
                    if (txtBox is TextBox)
                    {
                        if (txtBox.Text == "")
                        {

                            helpLabel.Text = "Proszę wypełnij wszystkie pola albo kliknij anuluj, aby wyjść.";
                            return;
                        }
                    }
                }

                String jobPosition = jobPositionListBox.SelectedItem as String;
                Użytkownik newUser = new Użytkownik();
                newUser.login = loginText.Text;
                newUser.hasło = passwordText.Text;
                newUser.nazwa_stanowiska = jobPosition;
                newUser.Pomieszczenie_ID_pomieszczenia = (int)roomIDListBox.SelectedItem;
                newUser.imię = firstNameText.Text;
                newUser.nazwisko = lastNameText.Text;
                db.Użytkowniks.InsertOnSubmit(newUser);
                db.SubmitChanges();
                
                
                var editedUser =
                from user in db.Użytkowniks
                where user.login == newUser.login
                select user.ID_użytkownika;
                EditRoomsConnection(editedUser.FirstOrDefault());
                db.SubmitChanges();
            }

            //if editing user
            else if (Decision == 2)
            {
                var editedUser =
                from user in db.Użytkowniks
                where user.ID_użytkownika == ID
                select user;

                if (loginText.Text != "")
                    editedUser.FirstOrDefault().login = loginText.Text;
                if (passwordText.Text != "")
                    editedUser.FirstOrDefault().hasło = passwordText.Text;
                if (jobPositionListBox.SelectedItem as String != null)
                    editedUser.FirstOrDefault().nazwa_stanowiska = jobPositionListBox.SelectedItem as String;
                if (roomIDListBox.SelectedItem != null)
                {
                    var queryRemoveConnection =
                         (from p in db.Pomieszczenies
                          where p.ID_pomieszczenia == editedUser.FirstOrDefault().Pomieszczenie_ID_pomieszczenia
                          select p).FirstOrDefault();

                    DeleteRoomsConnection(queryRemoveConnection.Katedra_ID_katedry, queryRemoveConnection.Wydział_ID_wydziału);

                    EditRoomsConnection(editedUser.FirstOrDefault().ID_użytkownika);
                    editedUser.FirstOrDefault().Pomieszczenie_ID_pomieszczenia = (int)roomIDListBox.SelectedItem;
                
                }
                if (firstNameText.Text != "")
                    editedUser.FirstOrDefault().imię = firstNameText.Text;
                if (lastNameText.Text != "")
                    editedUser.FirstOrDefault().nazwisko = lastNameText.Text;

                db.SubmitChanges();
            }
            //zamknij
            if (System.Windows.Forms.Application.OpenForms["AdminPanel"] != null)
            {
                (System.Windows.Forms.Application.OpenForms["AdminPanel"] as AdminPanel).ShowResults();
            }
            this.Close();
        }

        private void PositionChanged(object sender, EventArgs e)
        {
            string position = jobPositionListBox.SelectedItem as String;


            //if PTW, KW, A
            var availableFaculties =
                     from c in db.Wydziałs
                     select c.nazwa_wydziału;

            if (position == "KK" || position == "PT")
            {
                availableFaculties =
                     from c in db.Katedras
                     select c.nazwa_katedry;
            }

            FacultyListBox.Items.Clear();
            foreach (string faculty in availableFaculties)
            {
                FacultyListBox.Items.Add(faculty);
            }
        }

        private void FacultyListBox_SelectedIndexChanged(object sender, EventArgs e)
        {

            string position = FacultyListBox.SelectedItem as String;

            var availableRooms =
               from c in db.Pomieszczenies
               where !(from o in db.Użytkowniks
                       select o.Pomieszczenie_ID_pomieszczenia)
                   .Contains(c.ID_pomieszczenia)
                && (from w in db.Wydziałs
                where w.nazwa_wydziału == position
                select w.ID_wydziału).First().Equals(c.Wydział_ID_wydziału)
                && c.Katedra_ID_katedry.Equals(null)
               select c.ID_pomieszczenia;


            if (jobPositionListBox.SelectedItem as String == "KK" || jobPositionListBox.SelectedItem as String == "PT")
            {
                availableRooms =
             from c in db.Pomieszczenies
             where !(from o in db.Użytkowniks
                     select o.Pomieszczenie_ID_pomieszczenia)
                .Contains(c.ID_pomieszczenia)
             && (from k in db.Katedras
                 where k.nazwa_katedry == position
                 select k.ID_katedry).First().Equals(c.Katedra_ID_katedry)
             select c.ID_pomieszczenia;

            }

            roomIDListBox.Items.Clear();
            foreach (int room in availableRooms)
            {
                roomIDListBox.Items.Add(room);
            }
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
        //edits manager connection
        private void EditRoomsConnection(int IDUser)
        {
            if (jobPositionListBox.SelectedItem as String == "KK")
            {
                var faculty =
                from p in db.Pomieszczenies
                where p.ID_pomieszczenia == (int)roomIDListBox.SelectedItem
                select p.Katedra_ID_katedry;

                var editedFaculty =
                from f in db.Katedras
                where f.ID_katedry == faculty.First()
                select f;

                editedFaculty.FirstOrDefault().ID_kierownika_katedry = IDUser;

            }
            else if (jobPositionListBox.SelectedItem as String == "KW")
            {
                 var faculty =
                 from p in db.Pomieszczenies
                 where p.ID_pomieszczenia == (int)roomIDListBox.SelectedItem
                 select p.Wydział_ID_wydziału;

                 var editedFaculty =
                 from f in db.Wydziałs
                 where f.ID_wydziału == faculty.First()
                 select f;

                  editedFaculty.FirstOrDefault().ID_kierownika_wydziału = IDUser;
            }
        }

    }
}

