namespace exam_asp.Models
{
    public class User
    {
        public int Id {  get; }
        public String Username {  get; }
        public String Password {  get;  }

        public User(int id, String username, String password)
        {
            this.Id = id;
            this.Username = username;
            this.Password = password;
        }
    }
}
