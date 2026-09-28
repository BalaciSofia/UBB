namespace exam_asp.Models
{
    public class User
    {
        public int id {  get; }
        public string username {  get; }

        public string membershipType { get; }

        public User(int id, string username, string membershipType)
        {
            this.id = id;
            this.username = username;
            this.membershipType = membershipType;
        }
    }
}
