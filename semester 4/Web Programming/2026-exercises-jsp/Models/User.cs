namespace _2026_exercises.Models
{
    public class User
    {
        public int Id;
        public string Username;
        public string nativeLanguage;

        public User(int id, string username, string nativeLanguage)
        {
            Id = id;
            Username = username;
            this.nativeLanguage = nativeLanguage;
        }
    }
}
