namespace _2026_booking.Models
{
    public class Waitlist
    {
        public int id { get; set; }
        public int userID { get; set; }
        public int classID { get; set; }
        public DateTime createdAt { get; set; }

        public Waitlist(int id, int userID, int classID, DateTime createdAt)
        {
            this.id = id;
            this.userID = userID;
            this.classID = classID;
            this.createdAt = createdAt;
        }
    }
}
