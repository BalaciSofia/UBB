using _2024_hotel_flights.Models;
using MySql.Data.MySqlClient;
namespace _2024_hotel_flights.DAL
{
    public class Dal
    {
        private readonly string connstring= "server=localhost;uid=root;pwd=;database=2024-hotel&flights";
        public List<Flight> GetFlights(DateTime searchdate,string destination)
        {
            List<Flight> flights = new List<Flight>();
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "SELECT * FROM flights WHERE date=@date AND destinationCity=@destination" +
                    " and availableSeats >= 1";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@date", searchdate);
                    cmd.Parameters.AddWithValue("@destination", destination);
                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            int id = reader.GetInt32("id");
                            int availableSeats = reader.GetInt32("availableSeats");
                            string destinationCity = reader.GetString("destinationCity");
                            DateTime date = reader.GetDateTime("date");
                            Flight flight = new Flight(id, date, destinationCity, availableSeats);
                            flights.Add(flight);
                        }
                    }
                }
            }
            return flights;
        }

        public List<Hotel> GetHotels(DateTime searchdate, string destination)
        {
            List<Hotel> hotels = new List<Hotel>();
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "SELECT * FROM hotels WHERE date=@date AND city=@destination" +
                    " and availableRooms >= 1";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@date", searchdate);
                    cmd.Parameters.AddWithValue("@destination", destination);
                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            int id = reader.GetInt32("id");
                            int availableRooms = reader.GetInt32("availableRooms");
                            string city = reader.GetString("city");
                            DateTime date = reader.GetDateTime("date");
                            string hotelName = reader.GetString("hotelName");
                            Hotel hotel = new Hotel(id,hotelName,date,city,availableRooms);
                            hotels.Add(hotel);
                        }
                    }
                }
            }
            return hotels;
        }

        public int MakeReservation(string person, DateTime date, string type, int idReservationResource)
        {
            if (type == "flight")
            {
                using (MySqlConnection conn = new MySqlConnection(connstring))
                {
                    conn.Open();
                    string query = "UPDATE flights SET availableSeats = availableSeats - 1 WHERE id = @id";
                    using (MySqlCommand cmd = new MySqlCommand(query, conn))
                    {
                        cmd.Parameters.AddWithValue("@id", idReservationResource);
                        cmd.ExecuteNonQuery();
                    }
                }
            }
            else if (type == "hotel")
            {
                using (MySqlConnection conn = new MySqlConnection(connstring))
                {
                    conn.Open();
                    string query = "UPDATE hotels SET availableRooms = availableRooms - 1 WHERE id = @id";
                    using (MySqlCommand cmd = new MySqlCommand(query, conn))
                    {
                        cmd.Parameters.AddWithValue("@id", idReservationResource);
                        cmd.ExecuteNonQuery();
                    }
                }
            }
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "INSERT INTO reservations (person, date, type, idReservedResource) VALUES (@person, @date, @type, @idReservedResource); SELECT LAST_INSERT_ID();";
                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@person", person);
                    cmd.Parameters.AddWithValue("@date", date);
                    cmd.Parameters.AddWithValue("@type", type);
                    cmd.Parameters.AddWithValue("@idReservedResource", idReservationResource);
                        int reservationId = Convert.ToInt32(cmd.ExecuteScalar());
                    return reservationId;
                }
            }
           
        }

        public void CancelReservation(int id)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string queryGetReservation = "SELECT * FROM reservations WHERE id = @id";
                int idReservedResource;
                string type;
                using (MySqlCommand cmd = new MySqlCommand(queryGetReservation, conn))
                {
                    cmd.Parameters.AddWithValue("@id", id);
                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            idReservedResource = reader.GetInt32("idReservedResource");
                            type = reader.GetString("type");
                        }
                        else
                        {
                            return;
                        }
                    }
                }
                if (type == "flight")
                {
                    string queryUpdateFlight = "UPDATE flights SET availableSeats = availableSeats + 1 WHERE id = @id";
                    using (MySqlCommand cmd = new MySqlCommand(queryUpdateFlight, conn))
                    {
                        cmd.Parameters.AddWithValue("@id", idReservedResource);
                        cmd.ExecuteNonQuery();
                    }
                }
                else if (type == "hotel")
                {
                    string queryUpdateHotel = "UPDATE hotels SET availableRooms = availableRooms + 1 WHERE id = @id";
                    using (MySqlCommand cmd = new MySqlCommand(queryUpdateHotel, conn))
                    {
                        cmd.Parameters.AddWithValue("@id", idReservedResource);
                        cmd.ExecuteNonQuery();
                    }
                }
                string queryDeleteReservation = "DELETE FROM reservations WHERE id = @id";
                using (MySqlCommand cmd = new MySqlCommand(queryDeleteReservation, conn))
                {
                    cmd.Parameters.AddWithValue("@id", id);
                    cmd.ExecuteNonQuery();
                }
            }
        }
    }
}
