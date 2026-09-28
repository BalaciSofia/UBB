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
namespace assg1
{
    public partial class Form1 : Form
    {
        private SqlConnection dbConn;
        private DataSet ds;
        private SqlDataAdapter daHabitats, daEvents;
        private SqlCommandBuilder cbEvents;
        private BindingSource bsHabitats, bsEvents;

        public Form1()
        {
            InitializeComponent();
        }

        private void ReloadButton_Click(object sender, EventArgs e)
        {
            ds.Tables["Events"].Clear();
            ds.Tables["Habitats"].Clear();

            daEvents.Fill(ds, "Events");
            daHabitats.Fill(ds, "Habitats");
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            bsEvents.EndEdit();
            daEvents.Update(ds, "Events");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dbConn = new SqlConnection(@"Data Source=DESKTOP-HG3EVRO\SQLEXPRESS;Initial Catalog=ZooManagement;Integrated Security=True");

            daHabitats = new SqlDataAdapter("Select * from Habitats", dbConn);
            daEvents = new SqlDataAdapter("Select * from Events", dbConn);
            cbEvents = new SqlCommandBuilder(daEvents);

            ds = new DataSet();
            daHabitats.Fill(ds, "Habitats");
            daEvents.Fill(ds, "Events");

            DataRelation dr = new DataRelation("FK_Events_Habitats", ds.Tables["Habitats"].Columns["HabitatID"], ds.Tables["Events"].Columns["HabitatID"]);
            ds.Relations.Add(dr);

            bsHabitats = new BindingSource();
            bsEvents = new BindingSource();

            bsHabitats.DataSource = ds;
            bsHabitats.DataMember = "Habitats";

            bsEvents.DataSource = bsHabitats;
            bsEvents.DataMember = "FK_Events_Habitats";

            dgvHabitats.DataSource = bsHabitats;
            dgvEvents.DataSource = bsEvents;
        }
    }
}
