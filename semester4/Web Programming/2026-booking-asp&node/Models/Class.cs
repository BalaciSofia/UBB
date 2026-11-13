namespace _2026_booking.Models
{
    public class Class
    {
        public int id { get; set; }
        public string className { get; set; }
        public string instructorName { get; set; }
        public DateTime classDate { get; set; }
        public int maxCapacity {  get; set; }

        public Class(int id, string className, string instructorName, DateTime classDate, int maxCapacity)
        {
            this.id = id;
            this.className = className;
            this.instructorName = instructorName;
            this.classDate = classDate;
            this.maxCapacity = maxCapacity;
        }
    }
}
