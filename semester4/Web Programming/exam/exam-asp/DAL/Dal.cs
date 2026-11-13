using exam_asp.Models;
using MySql.Data.MySqlClient;

namespace exam_asp.DAL
{
    public class Dal
    {
        private readonly string connstring = "server=localhost;uid=root;pwd=;database=test-db";

        public User Authentication(String username, String password)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "SELECT * FROM users WHERE username=@username";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@username", username);
                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            int id = reader.GetInt32("id");
                            if (reader.GetString("password") == password)
                            {
                                return new User(id, username, password);
                            }
                        }
                    }
                }
            }
            return null;
        }
    }
}
