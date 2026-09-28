using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace practical_exam
{
    public partial class Form1 : Form
    {
        private SqlConnection dbConn;
        private DataSet ds;
        private SqlDataAdapter daTaskTypes, daTasks;
        private SqlCommandBuilder cbTasks;
        private BindingSource bsTaskTypes, bsTasks;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dbConn = new SqlConnection(@"Data Source=DESKTOP-HG3EVRO\SQLEXPRESS;Initial Catalog=company;Integrated Security=True");

            daTaskTypes = new SqlDataAdapter("Select * from taskTypes", dbConn);
            daTasks = new SqlDataAdapter("Select * from tasks", dbConn);
            cbTasks = new SqlCommandBuilder(daTasks);

            ds = new DataSet();
            daTaskTypes.Fill(ds, "taskTypes");
            daTasks.Fill(ds, "tasks");

            DataRelation dr = new DataRelation("FK_TaskTypes_Tasks", ds.Tables["taskTypes"].Columns["taskTypeID"], ds.Tables["tasks"].Columns["taskID"]);
            ds.Relations.Add(dr);

            bsTaskTypes = new BindingSource();
            bsTasks = new BindingSource();

            bsTaskTypes.DataSource = ds;
            bsTaskTypes.DataMember = "taskTypes";

            bsTasks.DataSource = bsTaskTypes;
            bsTasks.DataMember = "FK_TaskTypes_Tasks";

            dgvTaskTypes.DataSource = bsTaskTypes;
            dgvTasks.DataSource = bsTasks;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            bsTasks.EndEdit();
            daTasks.Update(ds, "tasks");
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dgvTasks_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
