namespace _2026_exercises.Models
{
    public class Exercise
    {
        public int Id;
        public string Prompt;
        public string CorrectAnswer;
        public int Difficulty;
        public string Topic;

        public Exercise(int id, string prompt, string correctAnswer, int difficulty, string topic)
        {
            Id=id;
            Prompt=prompt;
            CorrectAnswer=correctAnswer;
            Difficulty=difficulty;
            Topic=topic;
        }
    }
}
