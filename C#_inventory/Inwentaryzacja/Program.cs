using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Inwentaryzacja
{
    static class Program
    {
        /// <summary>
        ///////// The main entry point for the application.
        /// </summary>
        /// 

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.EnableVisualStyles();
            Application.Run(new Inwentaryzacja.Inwentaryzacja.Welcome());
            Application.Run(new LogIn());
        }
    }
}
