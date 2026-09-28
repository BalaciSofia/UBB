namespace _2024_hotel_flights.Models
{
    public class Flight
    {
        private int id;
        private DateTime date;
        private string destinationCity;
        private int avaialableSeats;

        public Flight(int id, DateTime date, string destinationCity, int avaialableSeats)
        {
            this.id = id;
            this.date = date;
            this.destinationCity = destinationCity;
            this.avaialableSeats = avaialableSeats;
        }

        public int getId()
        {
            return this.id;
        }

        public DateTime getDate()
        {
            return this.date;
        }

        public string getDestinationCity()
        {
            return this.destinationCity;
        }

        public int getAvaialableSeats()
        {
            return this.avaialableSeats;
        }
    }
}
