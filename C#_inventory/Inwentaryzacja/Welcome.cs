using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Inwentaryzacja.Inwentaryzacja.Inwentaryzacja
{
    public partial class Welcome : Form
    {
        public Welcome()
        {
            InitializeComponent();
        }

        private void StartClick(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
