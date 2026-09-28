using _2024_hotel_flights.DAL;
using Microsoft.AspNetCore.Mvc;

namespace _2024_hotel_flights.Controllers
{
    public class MainController : Controller
    {

        [HttpGet]
        public IActionResult Start()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Start(string person, DateTime date, string destinationCity)
        {
            HttpContext.Session.SetString("person", person);
            HttpContext.Session.SetString("date", date.ToString("yyyy-MM-dd"));
            HttpContext.Session.SetString("destinationCity", destinationCity);

            return RedirectToAction("Home");
        }

        public IActionResult Home()
        {
            return View();
        }


        public IActionResult Flights()
        {
            string? dateString = HttpContext.Session.GetString("date");
            string? destinationCity = HttpContext.Session.GetString("destinationCity");
            if (dateString == null || destinationCity == null)
                return RedirectToAction("Start");
            DateTime date = DateTime.Parse(dateString);

            Dal dal = new Dal();
            List<Models.Flight> flights = dal.GetFlights(date, destinationCity);

            return View(flights);
        }
        public IActionResult Hotels()
        {
            string? dateString = HttpContext.Session.GetString("date");
            string? destinationCity = HttpContext.Session.GetString("destinationCity");
            if (dateString == null || destinationCity == null)
                return RedirectToAction("Start");
            DateTime date = DateTime.Parse(dateString);

            Dal dal = new Dal();
            List<Models.Hotel> hotels = dal.GetHotels(date, destinationCity);

            return View(hotels);
        }

        [HttpPost]
        public IActionResult Reserve(int id, string type) {
            string? person = HttpContext.Session.GetString("person");
            string? dateString = HttpContext.Session.GetString("date");
            string? destinationCity = HttpContext.Session.GetString("destinationCity");
            if (dateString == null || destinationCity == null)
                return RedirectToAction("Start");
            DateTime date = DateTime.Parse(dateString);
            Dal dal = new Dal();

            int reservationId = dal.MakeReservation(person, date, type, id);

            string ids = HttpContext.Session.GetString("reservationIds");
            if (string.IsNullOrEmpty(ids))
            {
                ids = reservationId.ToString();
            }
            else
            {
                ids = ids + "," + reservationId;
            }

            HttpContext.Session.SetString("reservationIds", ids);

            return RedirectToAction("Home");
        }

        [HttpPost]
        public IActionResult CancelAll()
        {
            Dal dal = new Dal();
            string ids = HttpContext.Session.GetString("reservationIds");
            if (!string.IsNullOrEmpty(ids))
            {
                string[] parts = ids.Split(',');

                foreach (string part in parts)
                {
                    int reservationId = int.Parse(part);
                    dal.CancelReservation(reservationId);
                }

                HttpContext.Session.Remove("reservationIds");
            }
            return RedirectToAction("Home");
        }
    }
}
