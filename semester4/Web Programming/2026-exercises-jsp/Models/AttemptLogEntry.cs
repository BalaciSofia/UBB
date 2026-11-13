namespace _2026_exercises.Models
{
    public class AttemptLogEntry
    {
        public string Prompt { get; set; }
        public string GivenAnswer { get; set; }
        public bool Correct { get; set; }
        public DateTime AttemptedAt { get; set; }

        public AttemptLogEntry(string prompt, string givenAnswer, bool correct, DateTime attemptedAt)
        {
            Prompt = prompt;
            GivenAnswer = givenAnswer;
            Correct = correct;
            AttemptedAt = attemptedAt;
        }
    }
}
