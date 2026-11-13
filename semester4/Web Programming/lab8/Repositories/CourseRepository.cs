using MySqlConnector;
using lab8.Domain;
namespace lab8.Repositories
{
    public class CourseRepository
    {
        private readonly string _connectionString;

        public CourseRepository(string connectionString)
        {
            _connectionString = connectionString;
        }

        public Course mapCourse(MySqlDataReader read)
        {
            int courseId = (int)read["courseId"];
            string name = (string)read["name"];
            int professorId = (int)read["professorId"];
            return new Course
            {
                CourseId = courseId,
                Name = name,
                ProfessorId = professorId
            };
        }

        public List<Course> GetAll()
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            string query = "SELECT * FROM courses";
            List<Course> courses = new List<Course>();
            MySqlCommand command = new MySqlCommand(query, conn);
            conn.Open();
            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    courses.Add(mapCourse(reader));
                }
            }
            conn.Close();
            return courses;
        }

        public Course? GetProfessorCourse(int professorId)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            conn.Open();

            MySqlCommand command = conn.CreateCommand();
            command.CommandText = @"
                SELECT courseId, name, professorId
                FROM courses
                WHERE professorId = @professorId
                ORDER BY name
                LIMIT 1";
            command.Parameters.AddWithValue("@professorId", professorId);

            using (MySqlDataReader reader = command.ExecuteReader())
            {
                if (reader.Read())
                {
                    return mapCourse(reader);
                }
            }

            conn.Close();
            return null;
        }

    }
}
