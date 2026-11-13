using _2026_exercises.Models;
using MySql.Data.MySqlClient;

namespace exam_asp.DAL
{
    public class Dal
    {
        private readonly string connstring = "server=localhost;uid=root;pwd=;database=2026-exercises";

        public User? Authentication(string username)
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
                            string nativeLanguage = reader.GetString("nativeLanguage");
                            return new User(id, username, nativeLanguage);
                        }
                    }
                }
            }
            return null;
        }


        public Dictionary<string, int> ComputeScoreMap(int userID)
        {
            Dictionary<string, int> scoreMap = new Dictionary<string, int>();

            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();

                string query = @" SELECT 
                e.topic,
                COUNT(r.id) AS total,
                COALESCE(SUM(CASE WHEN r.correct = 1 THEN 1 ELSE 0 END), 0) AS correct
            FROM exercise e
            LEFT JOIN results r ON r.exerciseID = e.id AND r.userID = @userID
            GROUP BY e.topic;
        ";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@userID", userID);

                    try
                    {
                        using (MySqlDataReader reader = cmd.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                string topic = reader.GetString("topic");
                                int total = reader.GetInt32("total");
                                int correct = reader.GetInt32("correct");

                                int score = total == 0 ? 0 : (int)Math.Round((double)correct / total * 100);

                                scoreMap[topic] = score;
                            }
                        }
                    }
                    catch (MySqlException ex) when (ex.Number == 1146)
                    {
                        return scoreMap;
                    }
                }
            }

            return scoreMap;
        }


        public Exercise? GetNextExercise(Dictionary<string,int> scoreMap, int userID)
        {
            foreach (var item in scoreMap.OrderBy(x => x.Value))
            {
                string topic = item.Key;
                int score = item.Value;
                int difficulty;
                if (score < 40)
                {
                    difficulty = 1;
                }
                else if (score < 70)
                {
                    difficulty = 2;
                }
                else
                {
                    difficulty = 3;
                }
                Exercise? exercise = GetUnseenExercise(userID, topic, difficulty);

                if (exercise != null)
                {
                    return exercise;
                }
            }

            return GetAnyUnseenExercise(userID);
        }

        public Exercise? GetUnseenExercise(int userID, string topic, int difficulty)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();

                string query = @"
            SELECT id, prompt, correctAnswer, difficulty, topic
            FROM exercise
            WHERE topic = @topic
            AND difficulty = @difficulty
            AND id NOT IN (
                SELECT exerciseID
                FROM results
                WHERE userID = @userID
            )
            LIMIT 1
        ";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@topic", topic);
                    cmd.Parameters.AddWithValue("@difficulty", difficulty);
                    cmd.Parameters.AddWithValue("@userID", userID);

                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            return new Exercise(
                                reader.GetInt32("id"),
                                reader.GetString("prompt"),
                                reader.GetString("correctAnswer"),
                                reader.GetInt32("difficulty"),
                                reader.GetString("topic")
                            );
                        }
                    }
                }
            }

            return null;
        }

        public Exercise? GetAnyUnseenExercise(int userID)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();

                string query = @"
            SELECT id, prompt, correctAnswer, difficulty, topic
            FROM exercise
            WHERE id NOT IN (
                SELECT exerciseID
                FROM results
                WHERE userID = @userID
            )
            ORDER BY difficulty, id
            LIMIT 1
        ";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@userID", userID);

                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            return new Exercise(
                                reader.GetInt32("id"),
                                reader.GetString("prompt"),
                                reader.GetString("correctAnswer"),
                                reader.GetInt32("difficulty"),
                                reader.GetString("topic")
                            );
                        }
                    }
                }
            }

            return null;
        }

        public void SaveResult(int userID, int exerciseID, string givenAnswer, bool correct)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();

                string query = @"
            INSERT INTO results (userID, exerciseID, givenAnswer, correct, attemptedAt)
            VALUES (@userID, @exerciseID, @givenAnswer, @correct, NOW())
        ";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@userID", userID);
                    cmd.Parameters.AddWithValue("@exerciseID", exerciseID);
                    cmd.Parameters.AddWithValue("@givenAnswer", givenAnswer);
                    cmd.Parameters.AddWithValue("@correct", correct ? 1 : 0);
                    cmd.ExecuteNonQuery();
                }
            }
        }

        public Exercise? GetExerciseById(int exerciseID)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();

                string query = @"
            SELECT id, prompt, correctAnswer, difficulty, topic
            FROM exercise
            WHERE id = @exerciseID
        ";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@exerciseID", exerciseID);

                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            return new Exercise(
                                reader.GetInt32("id"),
                                reader.GetString("prompt"),
                                reader.GetString("correctAnswer"),
                                reader.GetInt32("difficulty"),
                                reader.GetString("topic")
                            );
                        }
                    }
                }
            }

            return null;
        }

        public List<AttemptLogEntry> GetAttemptLog(int userID)
        {
            List<AttemptLogEntry> attemptLog = new List<AttemptLogEntry>();

            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();

                string query = @"
            SELECT e.prompt, r.givenAnswer, r.correct, r.attemptedAt
            FROM results r
            INNER JOIN exercise e ON r.exerciseID = e.id
            WHERE r.userID = @userID
            ORDER BY r.attemptedAt DESC, r.id DESC
        ";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@userID", userID);

                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            attemptLog.Add(new AttemptLogEntry(
                                reader.GetString("prompt"),
                                reader.GetString("givenAnswer"),
                                reader.GetInt32("correct") == 1,
                                reader.GetDateTime("attemptedAt")
                            ));
                        }
                    }
                }
            }

            return attemptLog;
        }
    }
}
