namespace _2024_hotel_flights.Models
{
    public class Reservation
    {
        private int id;
        private string person;
        private DateTime date;
        private string type;
        private int idReservedResource;

        public Reservation(int id, string person, DateTime date, string type, int idReservedResource)
        {
            this.id = id;
            this.person = person;
            this.date = date;
            this.type = type;
            this.idReservedResource = idReservedResource;
        }

        public int getId()
        {
            return this.id;
        }

        public string getPerson()
        {
            return this.person;
        }

        public DateTime getDate()
        {
            return this.date;
        }

        public string getType()
        {
            return this.type;
        }

        public int getIdReservedResource()
        {
            return this.idReservedResource;
        }
    }
}
