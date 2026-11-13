using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab3
{
    public partial class Form1 : Form
    {
        private SqlConnection dbConn;
        private DataSet ds;
        private SqlDataAdapter daParent, daChild;
        private SqlCommandBuilder cbChild;
        private BindingSource bsParent, bsChild;
        string parentTable = ConfigurationManager.AppSettings["ParentTable"];//Habitats,Visitors
        string childTable = ConfigurationManager.AppSettings["ChildTable"];//Events,Donations
        //key HabitatID
        private void saveButton_Click(object sender, EventArgs e)
        {
            daChild.Update(ds, childTable);
        }

        private void ReloadButton_Click(object sender, EventArgs e)
        {
            ds.Clear();
            daParent.Fill(ds, parentTable);
            daChild.Fill(ds, childTable);
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string connectionString = ConfigurationManager.AppSettings["ConnectionString"];
            dbConn = new SqlConnection(connectionString);

            daParent = new SqlDataAdapter("SELECT * FROM "+parentTable, dbConn);
            daChild = new SqlDataAdapter("SELECT * FROM " + childTable, dbConn);
            cbChild = new SqlCommandBuilder(daChild);

            ds = new DataSet();
            daParent.Fill(ds, parentTable);
            daChild.Fill(ds, childTable);

            string relationName = "FK_" + childTable + "_" + parentTable;

            string parentColumn = ConfigurationManager.AppSettings["ParentColumn"];
            string childColumn = ConfigurationManager.AppSettings["ChildColumn"];

            DataRelation dr = new DataRelation(relationName , ds.Tables[parentTable].Columns[parentColumn], ds.Tables[childTable].Columns[childColumn]);
            ds.Relations.Add(dr);

            bsParent = new BindingSource();
            bsChild = new BindingSource();

            bsParent.DataSource = ds;
            bsParent.DataMember = parentTable ;

            bsChild.DataSource = bsParent;
            bsChild.DataMember = relationName;

            dgv1.DataSource = bsParent;
            dgv2.DataSource = bsChild;
        }
    }
}
