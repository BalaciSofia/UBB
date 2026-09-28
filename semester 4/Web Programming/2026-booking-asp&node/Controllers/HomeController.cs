using _2026_booking.Models;
using exam_asp.DAL;
using exam_asp.Models;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;

namespace _2026_booking.Controllers
{
    public class HomeController : Controller
    {
        [HttpGet]
        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Login(string username)
        {
            Dal dal = new Dal();
            User user = dal.Authentication(username);
            if (user != null)
            {
                HttpContext.Session.SetString("username", user.username);
                HttpContext.Session.SetString("membershupType", user.membershipType);
                HttpContext.Session.SetInt32("id", user.id);
                return RedirectToAction("Home");
            }
            else
            {
                ViewBag.Error = "Invalid username or password.";
                return View();
            }
        }

        [HttpGet]
        public IActionResult Home()
        {
            if (HttpContext.Session.GetString("username") == null)
            {
                return RedirectToAction("Login");
            }
            Dal dal = new Dal();
            return View(dal.GetUpcommingClasses());
        }

        [HttpPost]
        public IActionResult Book(int userID, int classID)
        {
            Dal dal = new Dal();
            string result= dal.Book(userID, classID);
            TempData["Message"] = result;
            return RedirectToAction("Home");
        }
    }
}
