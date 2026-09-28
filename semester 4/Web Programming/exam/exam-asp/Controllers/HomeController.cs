using exam_asp.DAL;
using exam_asp.Models;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;

namespace exam_asp.Controllers
{
    public class HomeController : Controller
    {
        [HttpGet]
        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Login(string username, string password)
        {
            Dal dal = new Dal();
            User user = dal.Authentication(username, password);
            if (user != null)
            {
                HttpContext.Session.SetString("username", user.Username);
                return RedirectToAction("Home");
            }
            else
            {
                ViewBag.Error = "Invalid username or password.";
                return View();
            }
        }

        public IActionResult Home()
        {
            if (HttpContext.Session.GetString("username") == null)
            {
                return RedirectToAction("Login");
            }
            return View();
        }
    }
}
