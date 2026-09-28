namespace _2026_booking.Models
{
    public class Booking
    {
        public int id { get; set; }
        public int userID {  get; set; }
        public int classID {  get; set; }
        public DateTime bookedAt { get; set; }
        public int cancelled {  get; set; }

        public Booking(int id, int userID, int classID, DateTime bookedAt, int cancelled)
        {
            this.id = id;
            this.userID = userID;
            this.classID = classID;
            this.bookedAt = bookedAt;
            this.cancelled = cancelled;
        }
    }
}
