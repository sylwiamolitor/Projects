
using System;
using System.Collections.Generic;

using System.Drawing;
using System.IO;

using System.Runtime.InteropServices;

using System.Windows.Forms;
using System.Diagnostics;

using System.Threading;

namespace JANET
{
    public partial class Form1 : Form
    {
        float saturacjaWartosc=0.5f;
        int liczbaWatkow=1;
        int rozmiar;
        int szerokosc;
        string sciezkaDoPlikuOdczyt = "C://Users//Public//Documents//repos//wow.bmp";
        string sciezkaDoPlikuZapis = "C://Users//Public//Documents//repos//wallpaper2.bmp";
        Bitmap img;
        byte[] data2;
        bool wyborAlgo = false; //c
        int myIntValue;
        bool wczytano = false;
        public byte[] WczytajPlik(Bitmap img)
        {
            byte[] header = new byte[54];
            byte[] data;
            //otwieram plik bitmapy
            using (FileStream wczytywanieZPliku = new FileStream(sciezkaDoPlikuOdczyt, FileMode.Open, FileAccess.Read))
            using (BinaryReader bin = new BinaryReader((wczytywanieZPliku)))
            {
                long liczba =wczytywanieZPliku.Length;
                myIntValue = unchecked((int)liczba);
                header = bin.ReadBytes(54);
                data = bin.ReadBytes(myIntValue);
                wczytywanieZPliku.Close();
                bin.Close(); 
                return data;
            }
        }
        public void zapiszPlik(byte[] data)
        {
            byte[] header = new byte[54];
            //otwieram plik bitmapy
            using (FileStream wczytywanieZPliku = new FileStream(sciezkaDoPlikuOdczyt, FileMode.Open, FileAccess.Read))
            using (BinaryReader bin1 = new BinaryReader((wczytywanieZPliku)))
            {
                header = bin1.ReadBytes(54);
                wczytywanieZPliku.Close();
                bin1.Close(); ///
            }
            using (FileStream zapisDoPliku = new FileStream(sciezkaDoPlikuZapis, FileMode.Create, FileAccess.Write))
            using (BinaryWriter bin2 = new BinaryWriter((zapisDoPliku)))
            {
                bin2.Write(header);
                bin2.Write(data);
                bin2.Close();//
                zapisDoPliku.Close();
            }

        }


        [DllImport("C://Users//Public//Documents//repos//DLLASM//x64//Release//DLLASM.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int MyProc1(byte[] obraz, float saturacjaWartosc, int wielkosc, int poczatek, int bufor, int szerokosc);


        [DllImport("C://Users//Public//Documents//repos//DLLJA//x64//Release//DLLJA.dll", CallingConvention = CallingConvention.Cdecl)]
        public unsafe static extern void wczytaj(byte[] obraz, float saturacjaWartosc, int wielkosc, int poczatek, int bufor, int szerokosc);

        public Form1()
        {
           
            InitializeComponent();
            img = szerokoscIWysokoscOdczyt();


        }

        static void wczytaj2(Object obj)
        {
        
            Tuple<bool, byte[], float, int, int, int, int> params1 = (Tuple<bool, byte[], float, int, int, int, int>)obj;

            if (!params1.Item1)
                wczytaj(params1.Item2, params1.Item3, params1.Item4, params1.Item5, params1.Item6, params1.Item7);
            else
                MyProc1(params1.Item2, params1.Item3, params1.Item4, params1.Item5, params1.Item6, params1.Item7);
          
        }
        private void test()
        {
            if (!wczytano)
            {
                data2 = WczytajPlik(img);
                wczytano = true;
            }
        }
        private void button1_Click(object sender, EventArgs e) //c++
        {
            test();
            byte[] data= new byte[data2.Length];
            for (int i=0; i< data2.Length; i++)
                data[i] = data2[i];

            //bufor - dopełnienie wiersza, w efekcie liczba bajtów jest wielokrotnością 4
            int bufor;
            if (szerokosc % 4 ==0) //rozmiar bufora to liczba bitów brakująca do 4 po obliczeniu reszty z dzielenia szerokości wiersza przez 4
                bufor = 4 - szerokosc % 4;
            else //bufor jest równy 0, jeśli liczba bajtów wiersza jest wielokrotnością 4
                bufor = 0;
            Stopwatch sw = new Stopwatch();
            
            List<Thread>listOfThreads = new List <Thread>();
           
            //Tuple<bool, byte[], float, int, int, int, int> param; //krotka
            int poczatek = 0;
            bool reszta = false;
            int etap = rozmiar / liczbaWatkow;
            if (etap * liczbaWatkow != rozmiar) //jesli reszta
                reszta = true;
            int koniec = etap;
         
            List<Tuple<bool, byte[], float, int, int, int, int>> tupelki = new List<Tuple<bool, byte[], float, int, int, int, int>>();


            sw.Start();

              for (int i = 0; i < liczbaWatkow-1; i++)
              {

                  Tuple<bool, byte[], float, int, int, int, int> param = new Tuple<bool, byte[], float, int, int, int, int>(wyborAlgo, data, saturacjaWartosc, koniec, poczatek, bufor, szerokosc);// true, bo c++
                  listOfThreads.Add(new Thread(new ParameterizedThreadStart(wczytaj2)));
                  listOfThreads[i].Start(param);
                  listOfThreads[i].Join();
                  poczatek += etap;
                  koniec += etap;
              }
            koniec = rozmiar;
            Tuple<bool, byte[], float, int, int, int, int> param3 = new Tuple<bool, byte[], float, int, int, int, int>(wyborAlgo, data, saturacjaWartosc, koniec, poczatek, bufor, szerokosc);// true, bo c++
            listOfThreads.Add(new Thread(new ParameterizedThreadStart(wczytaj2)));
            listOfThreads[liczbaWatkow-1].Start(param3);
            listOfThreads[liczbaWatkow-1].Join();
            sw.Stop();

            czas.Text = sw.ElapsedMilliseconds.ToString();
            czas.Text += "ms";

            zapiszPlik(data);
            szerokoscIWysokoscZapis(img);

        }



        private void textBox3_TextChanged(object sender, EventArgs e) //wartość saturacji
        {
            int test;
            if (Int32.TryParse(textBox3.Text, out test))
            {
                if (test >= 0 && test <= 100)
                    saturacjaWartosc = test;
                saturacjaWartosc /= 100;
            }

        }

        private void textBox1_TextChanged(object sender, EventArgs e) //liczba wątków
        {
            int test;
            if (Int32.TryParse(textBox1.Text, out test))
            {
                if (test > 0 && test < 65)
                    liczbaWatkow = test;
            }
     
        }


            public Bitmap szerokoscIWysokoscOdczyt()
            {
                OpenFileDialog plikWejsciowy = new OpenFileDialog();
                plikWejsciowy.FileName = sciezkaDoPlikuOdczyt;
                
                Bitmap img = new Bitmap(plikWejsciowy.FileName);
                rozmiar = img.Height * img.Width * 3;
                szerokosc = img.Width * 3;
                Bitmap resized = new Bitmap(img, new Size(200, 100));
                pictureBox1.Height = img.Height;
                pictureBox1.Width = img.Width;
                pictureBox1.Image = resized;
                return img;
            }



        public Bitmap szerokoscIWysokoscZapis(Bitmap img32)
        {

            OpenFileDialog plikWyjsciowy = new OpenFileDialog();
            plikWyjsciowy.FileName = sciezkaDoPlikuZapis;
            Bitmap img2 = new Bitmap(plikWyjsciowy.FileName);
            Bitmap resized2 = new Bitmap(img2, new Size(200, 100));
            pictureBox2.Height = img2.Height;
            pictureBox2.Width = img2.Width;
            pictureBox2.Image = resized2;
            return img2;
        }


        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            wyborAlgo = false;
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            wyborAlgo = true;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            sciezkaDoPlikuOdczyt = textBox2.Text;
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            sciezkaDoPlikuZapis = textBox4.Text;
        }
    }
}
