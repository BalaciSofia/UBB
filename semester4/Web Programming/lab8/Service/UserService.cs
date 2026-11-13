using lab8.Domain;
using lab8.Repositories;

namespace lab8.Service
{
    public class UserService
    {
        private readonly UserRepository _userRepository;

        public UserService(UserRepository userRepository)
        {
            _userRepository = userRepository;
        }

         public List<User> GetAllUsers()
        {
                return _userRepository.GetAll();
        }

        public User? FindByUsername(string username)
        {
            return _userRepository.FindByUsername(username);
        }

        public List<string> GetGroups()
        {
            return _userRepository.GetGroups();
        }

        public int CountStudentsInGroup(string group)
        {
            return _userRepository.CountStudentsInGroup(group);
        }

        public List<StudentGradeRow> GetStudentsFromGroup(string group, int courseId, int limit, int offset)
        {
            return _userRepository.GetStudentsFromGroup(group, courseId, limit, offset);
        }

        public bool StudentExists(int studentId)
        {
            return _userRepository.StudentExists(studentId);
        }

        public User GetById(int id)
        {
            return _userRepository.GetById(id);
        }

        public void AddUser(User user)
        {
            _userRepository.Add(user);
        }
         public void UpdateUser(User user)
        {
            _userRepository.Update(user);
        }
         public void DeleteUser(int id)
        {
            User user= _userRepository.GetById(id);
            _userRepository.Delete(user);
        }
    }
}
