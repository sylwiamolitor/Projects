using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using iTextSharp;
using iTextSharp.text;
using iTextSharp.text.pdf;


namespace Inwentaryzacja
{
    public partial class ManagerPanel : Form
    {
        private static int userId;
         
        public int UserId { get { return userId; } set { userId = value; } }
        
        private static ManagerPanel instance;
        private Użytkownik CurrentManager { get; set; }
        private DataClasses1DataContext DataBase { get; set; } = new DataClasses1DataContext();

        public ManagerPanel(int id)
        {
            UserId = id;

            InitializeComponent();
            // query about current user
            var query =
        from Użytkownik in DataBase.Użytkowniks
        where Użytkownik.ID_użytkownika == UserId
        select Użytkownik;

            CurrentManager = query.FirstOrDefault();
        }

        private void CreateOrder_Click(object sender, EventArgs e)
        {
            TaskPanel taskPanel = new TaskPanel(UserId);
            this.Hide();
            taskPanel.Show();
        }

        private void ShowActualOrder_Click(object sender, EventArgs e)
        {
            CurrentTasks currentTask = new CurrentTasks(UserId);
            this.Hide();
            currentTask.Show();
        }

        private void ShowDevice_Click(object sender, EventArgs e)
        {
            ShowEquipmentPanel showEquipmentPanel = new ShowEquipmentPanel();
            this.Hide();
            showEquipmentPanel.Show();
        }

        private void ShowEmployees_Click(object sender, EventArgs e)
        {
            ShowEmployeesPanel showEmployeesPanel = new ShowEmployeesPanel();
            this.Hide();
            showEmployeesPanel.Show();
        }

        private void GeneratingReport_Click(object sender, EventArgs e)
        {
            //lokana ścieżka do projektu//Inwentaryzacja//bin
            String pathTxt = "..//Raport.txt";
            String pathPdf = "..//Raport.pdf";
            StreamWriter sw = new StreamWriter(pathTxt);
            if (CurrentManager.nazwa_stanowiska == "KK")
            {
               
                var query =
                    (from p in DataBase.Pomieszczenies
                     join k in DataBase.Katedras on p.Katedra_ID_katedry equals k.ID_katedry
                     where k.ID_kierownika_katedry == UserId
                     select new {ID_pomieszczenia= p.ID_pomieszczenia, Numer_pokoju = p.numer_pokoju, Typ_pomieszczenia = p.typ_pomieszczenia, nazwa_katedry=k.nazwa_katedry, ID_wydzialu= k.Wydział_ID_wydziału}).ToList();
                if (query.Count() != 0)
                {
                    var temp = (from w in DataBase.Wydziałs where query[0].ID_wydzialu == w.ID_wydziału select new { Nazwa_wydzialu = w.nazwa_wydziału }).ToList();
                    sw.WriteLine("Raport dla kierownika katedry " + query[0].nazwa_katedry + " wydziału " + temp[0].Nazwa_wydzialu + ": " + CurrentManager.imię + " " + CurrentManager.nazwisko + "\n");
                    //Write a line of text
                    for (int i = 0; i < query.Count(); i++)
                    {
                        sw.WriteLine("Numer pokoju: " + query[i].Numer_pokoju + "\nTyp pomieszczenia: " + query[i].Typ_pomieszczenia + "\nSprzęt:");
                        var query2 =
                       (from s in DataBase.Sprzęts
                        where query[i].ID_pomieszczenia == s.Pomieszczenie_ID_pomieszczenia
                        select new { Nazwa_sprzetu = s.nazwa_sprzętu, stan = s.stan, numer_inwentarzowy = s.numer_inwentaryzacyjny }
                        ).ToList();
                        if(query2.Count()==0)
                        {
                            sw.WriteLine("Brak sprzętu w tym pomieszczeniu");
                        }
                        for (int j = 0; j < query2.Count(); j++)
                        {
                            
                            sw.WriteLine(query2[j]);
                        }

                        sw.WriteLine("\n");
                    }
                }
                else
                    sw.WriteLine("Brak katedry dla tego użytkownika!");

            }
            else if (CurrentManager.nazwa_stanowiska == "KW")
            {
               
                var query =
                    (from p in DataBase.Pomieszczenies
                     join w in DataBase.Wydziałs on p.Wydział_ID_wydziału equals w.ID_wydziału
                     where w.ID_kierownika_wydziału == UserId
                     select new { ID_pomieszczenia = p.ID_pomieszczenia, Numer_pokoju = p.numer_pokoju, Typ_pomieszczenia = p.typ_pomieszczenia, Nazwa_wydzialu= w.nazwa_wydziału }).ToList();
                if (query.Count() != 0)
                {
                    sw.WriteLine("Raport dla kierownika wydziału " + query[0].Nazwa_wydzialu + ": " + CurrentManager.imię + " " + CurrentManager.nazwisko + "\n");
                    //Write a line of text
                    for (int i = 0; i < query.Count(); i++)
                    {
                        sw.WriteLine("Numer pokoju: " + query[i].Numer_pokoju + "\nTyp pomieszczenia: " + query[i].Typ_pomieszczenia + "\nSprzęt:");
                        var query2 =
                       (from s in DataBase.Sprzęts
                        where query[i].ID_pomieszczenia == s.Pomieszczenie_ID_pomieszczenia
                        select new { Nazwa_sprzetu = s.nazwa_sprzętu, stan = s.stan, numer_inwentarzowy = s.numer_inwentaryzacyjny }
                        ).ToList();
                        if (query2.Count() == 0)
                        {
                            sw.WriteLine("Brak sprzętu w tym pomieszczeniu");
                        }
                        for (int j = 0; j < query2.Count(); j++)
                        {
                            sw.WriteLine(query2[j]);
                        }
                        sw.WriteLine("\n");
                    }
                }
                else
                    sw.WriteLine("Brak wydziału dla tego użytkownika!");
            }
            sw.Close();
            //lokana ścieżka do projektu//Inwentaryzacja//bin
            StreamReader rdr = new StreamReader(pathTxt);
            //Create a New instance on Document Class
            Document doc = new Document();
            //lokana ścieżka do projektu//Inwentaryzacja//bin
            PdfWriter.GetInstance(doc, new FileStream(pathPdf, FileMode.Create));
            doc.Open();
            //Add the content of Text File to PDF File
            var bigFont = FontFactory.GetFont( BaseFont.HELVETICA, BaseFont.CP1257, 12);
            doc.Add(new Paragraph(rdr.ReadToEnd(),bigFont));
            doc.NewPage();
            doc.Close();
            rdr.Close();
            //usunięcie txt, bo raport miał być tylko w pdf
            File.Delete(pathTxt);

        }
      
        //zamknięcie wszystkich otwartych okien
        private void LogoutButton_Click(object sender, EventArgs e)
        {
            int baseIndex = 0;
            int thisFormIndex = -1;

            while (Application.OpenForms.Count > 1)
            {
                if (Application.OpenForms[baseIndex] is LogIn || Application.OpenForms[baseIndex].Equals(this))
                {
                    if (Application.OpenForms[baseIndex].Equals(this))
                    {
                        thisFormIndex = baseIndex;
                    }
                    baseIndex++;
                }
                else
                {
                    Application.OpenForms[baseIndex].Close();
                }
                if (Application.OpenForms.Count == 2 && thisFormIndex >= 0)
                {
                    break;
                }
            }
            if (thisFormIndex >= 0)
            {
                Application.OpenForms[thisFormIndex].Close();
            }
        }

        public static ManagerPanel GetInstance
        {
            get
            {
                if (instance == null || instance.IsDisposed)
                {
                    instance = new ManagerPanel(ManagerPanel.userId);
                }
                return instance;
            }
        }
    }
}
