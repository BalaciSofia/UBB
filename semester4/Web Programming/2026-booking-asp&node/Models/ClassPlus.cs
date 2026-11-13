namespace _2026_booking.Models
{
    public class ClassPlus
    {
        public int Id { get; }
        public string className { get; set; }
        public string instructorName { get; set; }
        public DateTime classDate { get; set; }
        public int maxCapacity { get; set; }

        public int available {  get; set; }

        public ClassPlus(int id, string className, string instructorName, DateTime classDate, int maxCapacity, int available    )
        {
            this.Id = id;
            this.className = className;
            this.instructorName = instructorName;
            this.classDate = classDate;
            this.maxCapacity = maxCapacity;
            this.available = available;
        }
    }
}
