using lab8.Domain;
using MySqlConnector;
namespace lab8.Repositories
{
    public sealed record StudentGradeRow(int UserId, string Name, decimal? Grade);

    public class UserRepository
    {
        private readonly string _connectionString;

        public UserRepository(string connectionString)
        {
            _connectionString = connectionString;
        }

        public User mapUser(MySqlDataReader read)
        {
            int userId = (int)read["userId"];
            string username = (string)read["username"];
            string password = (string)read["password"];
            string name = (string)read["name"];
            string role = (string)read["role"];
            string groupCode = (string)read["groupCode"];
            return new User
            {
                UserId = userId,
                Username = username,
                Password = password,
                Name = name,
                Role = role,
                GroupCode = groupCode
            };

        }

        public List<User> GetAll()
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            string query = "SELECT * FROM users";
            List<User> users = new List<User>();
            MySqlCommand command = new MySqlCommand(query, conn);
            conn.Open();
            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    users.Add(mapUser(reader));
                }
            }
            conn.Close();
            return users;
        }

        public User? FindByUsername(string username)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            conn.Open();

            MySqlCommand command = conn.CreateCommand();
            command.CommandText = @"
                SELECT userId, username, password, role, name, groupCode
                FROM users
                WHERE username = @username
                LIMIT 1";
            command.Parameters.AddWithValue("@username", username);

            using (MySqlDataReader reader = command.ExecuteReader())
            {
                if (reader.Read())
                {
                    return mapUser(reader);
                }
            }

            conn.Close();
            return null;
        }

        public List<string> GetGroups()
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            conn.Open();

            MySqlCommand command = conn.CreateCommand();
            command.CommandText = @"
                SELECT DISTINCT groupCode
                FROM users
                WHERE role = 'student' AND groupCode IS NOT NULL AND groupCode <> ''
                ORDER BY groupCode";

            List<string> groups = new List<string>();
            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    groups.Add(reader.GetString("groupCode"));
                }
            }

            conn.Close();
            return groups;
        }

        public int CountStudentsInGroup(string group)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            conn.Open();

            MySqlCommand command = conn.CreateCommand();
            command.CommandText = "SELECT COUNT(*) FROM users WHERE role = 'student' AND groupCode = @group";
            command.Parameters.AddWithValue("@group", group);

            object? result = command.ExecuteScalar();
            conn.Close();
            return Convert.ToInt32(result);
        }

        public List<StudentGradeRow> GetStudentsFromGroup(string group, int courseId, int limit, int offset)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            conn.Open();

            MySqlCommand command = conn.CreateCommand();
            command.CommandText = @"
                SELECT u.userId, u.name, g.grade
                FROM users u
                LEFT JOIN grades g ON u.userId = g.studentId AND g.courseId = @courseId
                WHERE u.role = 'student' AND u.groupCode = @group
                ORDER BY u.name
                LIMIT @limit OFFSET @offset";
            command.Parameters.AddWithValue("@courseId", courseId);
            command.Parameters.AddWithValue("@group", group);
            command.Parameters.AddWithValue("@limit", limit);
            command.Parameters.AddWithValue("@offset", offset);

            List<StudentGradeRow> students = new List<StudentGradeRow>();
            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    students.Add(new StudentGradeRow(
                        reader.GetInt32("userId"),
                        reader.GetString("name"),
                        reader.IsDBNull(reader.GetOrdinal("grade")) ? null : reader.GetDecimal("grade")));
                }
            }

            conn.Close();
            return students;
        }

        public bool StudentExists(int studentId)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            conn.Open();

            MySqlCommand command = conn.CreateCommand();
            command.CommandText = "SELECT COUNT(*) FROM users WHERE userId = @studentId AND role = 'student'";
            command.Parameters.AddWithValue("@studentId", studentId);

            object? result = command.ExecuteScalar();
            conn.Close();
            return Convert.ToInt32(result) > 0;
        }

        public void Add(User user) { 
            MySqlConnection conn = new MySqlConnection(_connectionString);
            string query = "INSERT INTO users (username, password, name, role, groupCode) VALUES (@username, @password, @name, @role, @groupCode)";
            MySqlCommand command = new MySqlCommand(query, conn);
            command.Parameters.AddWithValue("@username", user.Username);
            command.Parameters.AddWithValue("@password", user.Password);
            command.Parameters.AddWithValue("@name", user.Name);
            command.Parameters.AddWithValue("@role", user.Role);
            command.Parameters.AddWithValue("@groupCode", user.GroupCode);
            conn.Open();
            command.ExecuteNonQuery();
            conn.Close();
        }

        public void Update(User user)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            string query = "UPDATE users SET username = @username, password = @password, name = @name, role = @role, groupCode = @groupCode WHERE userId = @userId";
            MySqlCommand command = new MySqlCommand(query, conn);
            command.Parameters.AddWithValue("@username", user.Username);
            command.Parameters.AddWithValue("@password", user.Password);
            command.Parameters.AddWithValue("@name", user.Name);
            command.Parameters.AddWithValue("@role", user.Role);
            command.Parameters.AddWithValue("@groupCode", user.GroupCode);
            command.Parameters.AddWithValue("@userId", user.UserId);
            conn.Open();
            command.ExecuteNonQuery();
            conn.Close();
        }

        public void Delete(User user)
        {
            MySqlConnection conn= new MySqlConnection(_connectionString);
            string query = "DELETE FROM users WHERE userId = @userId";
            MySqlCommand command = new MySqlCommand(query, conn);
            command.Parameters.AddWithValue("@userId", user.UserId);
            conn.Open();
            command.ExecuteNonQuery();
            conn.Close();
        }

        public User GetById(int id)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            string query = "SELECT * FROM users WHERE userId = @userId";
            MySqlCommand command = new MySqlCommand(query, conn);
            command.Parameters.AddWithValue("@userId", id);
            conn.Open();
            using (MySqlDataReader reader = command.ExecuteReader())
            {
                if (reader.Read())
                {
                    return mapUser(reader);
                }
            }
            conn.Close();
            return null;
        }
    }
}
