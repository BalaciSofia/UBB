using lab8.Repositories;
using lab8.Domain;

namespace lab8.Service
{
    public class CourseService
    {
        private readonly CourseRepository _courseRepository;

        public CourseService(CourseRepository courseRepository)
        {
            _courseRepository = courseRepository;
        }

        public List<Course> GetAllCourses()
        {
                return _courseRepository.GetAll();
        }

        public Course? GetProfessorCourse(int professorId)
        {
            return _courseRepository.GetProfessorCourse(professorId);
        }
    }
}
