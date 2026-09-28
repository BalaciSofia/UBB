using MySqlConnector;
using lab8.Domain;

namespace lab8.Repositories
{
    public sealed record StudentCourseGradeRow(string CourseName, decimal? Grade);

    public class GradeRepository
    {
        private readonly string _connectionString;

        public GradeRepository(string connectionString)
            {
                _connectionString = connectionString;
        }

        public Grade mapGrade(MySqlDataReader read)
        {
            int gradeId = (int)read["gradeId"];
            int studentId = (int)read["studentId"];
            int courseId = (int)read["courseId"];
            int gradeValue = (int)read["gradeValue"];
            return new Grade
            {
                GradeId = gradeId,
                StudentId = studentId,
                CourseId = courseId,
                GradeValue = gradeValue
            };
        }
         public List<Grade> GetAll()
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            string query = "SELECT * FROM grades";
            List<Grade> grades = new List<Grade>();
            MySqlCommand command = new MySqlCommand(query, conn);
            conn.Open();
            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    grades.Add(mapGrade(reader));
                }
            }
            conn.Close();
            return grades;
        }

        public void Add(Grade grade) { 
            MySqlConnection conn = new MySqlConnection(_connectionString);
            string query = "INSERT INTO grades (studentId, courseId, gradeValue) VALUES (@studentId, @courseId, @gradeValue)";
            MySqlCommand command = new MySqlCommand(query, conn);
            command.Parameters.AddWithValue("@studentId", grade.StudentId);
            command.Parameters.AddWithValue("@courseId", grade.CourseId);
            command.Parameters.AddWithValue("@gradeValue", grade.GradeValue);
            conn.Open();
            command.ExecuteNonQuery();
            conn.Close();
        }


        public void Update(Grade grade)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            string query = "UPDATE grades SET studentId = @studentId, courseId = @courseId, gradeValue = @gradeValue WHERE gradeId = @gradeId";
            MySqlCommand command = new MySqlCommand(query, conn);
            command.Parameters.AddWithValue("@studentId", grade.StudentId);
            command.Parameters.AddWithValue("@courseId", grade.CourseId);
            command.Parameters.AddWithValue("@gradeValue", grade.GradeValue);
            command.Parameters.AddWithValue("@gradeId", grade.GradeId);
            conn.Open();
            command.ExecuteNonQuery();
            conn.Close();
        }

        public void Delete(Grade grade)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            string query = "DELETE FROM grades WHERE gradeId = @gradeId";
            MySqlCommand command = new MySqlCommand(query, conn);
            command.Parameters.AddWithValue("@gradeId", grade.GradeId);
            conn.Open();
            command.ExecuteNonQuery();
            conn.Close();
        }

        public Grade GetById(int id)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            string query = "SELECT * FROM grades WHERE gradeId = @gradeId";
            MySqlCommand command = new MySqlCommand(query, conn);
            command.Parameters.AddWithValue("@gradeId", id);
            conn.Open();
            using (MySqlDataReader reader = command.ExecuteReader())
            {
                if (reader.Read())
                {
                    return mapGrade(reader);
                }
            }
            conn.Close();
            return null;
        }

        public bool GradeExists(int studentId, int courseId)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            conn.Open();

            MySqlCommand command = conn.CreateCommand();
            command.CommandText = "SELECT COUNT(*) FROM grades WHERE studentId = @studentId AND courseId = @courseId";
            command.Parameters.AddWithValue("@studentId", studentId);
            command.Parameters.AddWithValue("@courseId", courseId);

            object? result = command.ExecuteScalar();
            conn.Close();
            return Convert.ToInt32(result) > 0;
        }

        public void SaveGrade(int studentId, int courseId, decimal grade)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            conn.Open();

            MySqlCommand command = conn.CreateCommand();
            command.CommandText = @"
                UPDATE grades
                SET grade = @grade
                WHERE studentId = @studentId AND courseId = @courseId";
            command.Parameters.AddWithValue("@studentId", studentId);
            command.Parameters.AddWithValue("@courseId", courseId);
            command.Parameters.AddWithValue("@grade", grade);

            int updatedRows = command.ExecuteNonQuery();
            if (updatedRows > 0)
            {
                conn.Close();
                return;
            }

            command.CommandText = @"
                INSERT INTO grades (studentId, courseId, grade)
                VALUES (@studentId, @courseId, @grade)";
            command.ExecuteNonQuery();
            conn.Close();
        }

        public List<StudentCourseGradeRow> GetGradesForStudent(int studentId)
        {
            MySqlConnection conn = new MySqlConnection(_connectionString);
            conn.Open();

            MySqlCommand command = conn.CreateCommand();
            command.CommandText = @"
                SELECT c.name AS courseName, g.grade
                FROM grades g
                INNER JOIN courses c ON g.courseId = c.courseId
                WHERE g.studentId = @studentId
                ORDER BY c.name";
            command.Parameters.AddWithValue("@studentId", studentId);

            List<StudentCourseGradeRow> grades = new List<StudentCourseGradeRow>();
            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    grades.Add(new StudentCourseGradeRow(
                        reader.GetString("courseName"),
                        reader.IsDBNull(reader.GetOrdinal("grade")) ? null : reader.GetDecimal("grade")));
                }
            }

            conn.Close();
            return grades;
        }
    }
}
