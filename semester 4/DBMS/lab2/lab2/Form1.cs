using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
namespace lab2
{
    public partial class Form1 : Form
    {
        SqlConnection dbConn;
        SqlDataAdapter daParent,daChild;
        DataSet ds;
        SqlCommandBuilder cb;
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonSaveData_Click(object sender, EventArgs e)
        {
            daChild.Update(ds, "T2");
        }

        private void Form1_Load_1(object sender, EventArgs e)
        { 
            dbConn = new SqlConnection(@"Data Source=DESKTOP-HG3EVRO\SQLEXPRESS;Initial Catalog=lab1_ex;Integrated Security=True");
            
            daParent = new SqlDataAdapter("Select * from T1",dbConn);
            daChild = new SqlDataAdapter("Select * from T2", dbConn);
            cb = new SqlCommandBuilder(daChild);

            ds = new DataSet();
            daParent.Fill(ds, "T1");
            daChild.Fill(ds, "T2");

            DataRelation dr = new DataRelation("FK_T2_T1", ds.Tables["T1"].Columns["ID"], ds.Tables["T2"].Columns["FKT1"]);
            ds.Relations.Add(dr);

            dgvT1.DataSource = ds;
            dgvT1.DataMember = "T1";

            dgvT2.DataSource = ds;
            dgvT2.DataMember = "T1.FK_T2_T1";
        }
    }
}
