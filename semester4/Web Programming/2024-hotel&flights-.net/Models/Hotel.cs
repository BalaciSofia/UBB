namespace _2024_hotel_flights.Models
{
    public class Hotel
    {
        private int id;
        private string hotelName;
        private DateTime date;
        private string city;
        private int availableRooms;

        public Hotel(int id, string hotelName, DateTime date, string city, int availableRooms)
        {
            this.id = id;
            this.hotelName = hotelName;
            this.date = date;
            this.city = city;
            this.availableRooms = availableRooms;
        }

        public int getId() {
            return this.id;
        }

        public string getHotelName() {
            return this.hotelName;
        }

        public DateTime getDate() {
            return this.date;
        }

        public string getCity() {
            return this.city;
        }

        public int getAvailableRooms() {
            return this.availableRooms;
        }
    }
}
