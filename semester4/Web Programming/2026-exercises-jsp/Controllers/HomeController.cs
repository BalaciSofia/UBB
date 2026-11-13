using _2026_exercises.Models;
using exam_asp.DAL;
using Microsoft.AspNetCore.Mvc;
using System.Text.Json;

namespace _2026_exercises.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return RedirectToAction("Home");
        }

        [HttpGet]
        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Login(string username)
        {
            Dal dal = new Dal();
            User? user = dal.Authentication(username);
            if (user != null)
            {
                HttpContext.Session.SetInt32("userID", user.Id);
                HttpContext.Session.SetString("username", user.Username);
                Dictionary<string, int> scoreMap = dal.ComputeScoreMap(user.Id);
                HttpContext.Session.SetString("scoreMap", JsonSerializer.Serialize(scoreMap));
                return RedirectToAction("Home");
            }
            else
            {
                ViewBag.Error = "Invalid username";
                return View();
            }
        }

        public IActionResult Home()
        {
            Dal dal = new Dal();
            if (HttpContext.Session.GetString("username") == null)
            {
                return RedirectToAction("Login");
            }

            string? scoreMapJson = HttpContext.Session.GetString("scoreMap");
            if (scoreMapJson == null)
            {
                return RedirectToAction("Login");
            }

            Dictionary<string, int> scoreMap =
                JsonSerializer.Deserialize<Dictionary<string, int>>(scoreMapJson) ?? new Dictionary<string, int>();
            int? userID = HttpContext.Session.GetInt32("userID");
            if (userID == null)
            {
                return RedirectToAction("Login");
            }

            Exercise? exercise = dal.GetNextExercise(scoreMap, userID.Value);
            if (exercise != null)
            {
                HttpContext.Session.SetInt32("exerciseID", exercise.Id);
            }

            string? masteryBanner = HttpContext.Session.GetString("masteryBanner");
            HttpContext.Session.Remove("masteryBanner");
            List<AttemptLogEntry> attemptLog = dal.GetAttemptLog(userID.Value);

            return View(new HomeViewModel(scoreMap, exercise, masteryBanner, attemptLog));
        }

        [HttpPost]
        public IActionResult SubmitAnswer(string? response)
        {
            int? userID = HttpContext.Session.GetInt32("userID");
            int? exerciseID = HttpContext.Session.GetInt32("exerciseID");
            if (userID == null || exerciseID == null)
            {
                return RedirectToAction("Login");
            }

            Dal dal = new Dal();
            string givenAnswer = response ?? string.Empty;
            Dictionary<string, int> oldScoreMap = GetScoreMapFromSession();
            Dictionary<string, int> newScoreMap = new Dictionary<string, int>(oldScoreMap);
            Exercise? exercise = dal.GetExerciseById(exerciseID.Value);
            if (exercise == null)
            {
                return RedirectToAction("Home");
            }

            bool correct = string.Equals(
                givenAnswer.Trim(),
                exercise.CorrectAnswer.Trim(),
                StringComparison.OrdinalIgnoreCase
            );
            int oldScore = oldScoreMap.GetValueOrDefault(exercise.Topic, 0);
            int newScore = ComputeUpdatedScore(oldScore, correct);

            newScoreMap[exercise.Topic] = newScore;
            SetMasteryBanner(exercise.Topic, oldScore, newScore);
            dal.SaveResult(userID.Value, exerciseID.Value, givenAnswer, correct);
            HttpContext.Session.SetString("scoreMap", JsonSerializer.Serialize(newScoreMap));

            return RedirectToAction("Home");
        }

        private int ComputeUpdatedScore(int oldScore, bool correct)
        {
            double updatedScore = correct
                ? oldScore + 10
                : oldScore - oldScore * 0.8;

            return Math.Clamp((int)Math.Round(updatedScore), 0, 100);
        }

        private Dictionary<string, int> GetScoreMapFromSession()
        {
            string? scoreMapJson = HttpContext.Session.GetString("scoreMap");
            if (scoreMapJson == null)
            {
                return new Dictionary<string, int>();
            }

            return JsonSerializer.Deserialize<Dictionary<string, int>>(scoreMapJson) ?? new Dictionary<string, int>();
        }

        private void SetMasteryBanner(string topic, int oldScore, int newScore)
        {
            string? shownTopicsJson = HttpContext.Session.GetString("masteryShownTopics");
            HashSet<string> shownTopics = shownTopicsJson == null
                ? new HashSet<string>()
                : JsonSerializer.Deserialize<HashSet<string>>(shownTopicsJson) ?? new HashSet<string>();

            bool crossedMasteryThreshold = oldScore < 80 && newScore >= 80;
            if (crossedMasteryThreshold && !shownTopics.Contains(topic))
            {
                shownTopics.Add(topic);
                HttpContext.Session.SetString("masteryBanner", $"You've mastered {topic}!");
            }

            HttpContext.Session.SetString("masteryShownTopics", JsonSerializer.Serialize(shownTopics));
        }

        public IActionResult Privacy()
        {
            return View();
        }
    }
}
