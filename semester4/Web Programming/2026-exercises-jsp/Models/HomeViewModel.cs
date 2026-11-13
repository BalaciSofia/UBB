namespace _2026_exercises.Models
{
    public class HomeViewModel
    {
        public Dictionary<string, int> ScoreMap { get; set; }
        public Exercise? Exercise { get; set; }
        public string? MasteryBanner { get; set; }
        public List<AttemptLogEntry> AttemptLog { get; set; }

        public HomeViewModel(
            Dictionary<string, int> scoreMap,
            Exercise? exercise,
            string? masteryBanner,
            List<AttemptLogEntry> attemptLog)
        {
            ScoreMap = scoreMap;
            Exercise = exercise;
            MasteryBanner = masteryBanner;
            AttemptLog = attemptLog;
        }
    }
}
