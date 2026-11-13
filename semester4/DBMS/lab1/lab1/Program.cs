using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;

namespace lab1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            SqlConnection dbCon = new SqlConnection("Data Source = desktop-hg3evro\\sqlexpress;" +
                "Initial Catalog = lab1_ex; Integrated Security = true");
             // ; User id =  ; Password = ");
            dbCon.Open();
            SqlCommand cmd = new SqlCommand("SELECT COUNT(*) FROM T1", dbCon);
            int res = (int)cmd.ExecuteScalar();
            Console.WriteLine(res.ToString());
            dbCon.Close();
        }
    }
}
