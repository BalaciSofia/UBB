using lab8.Domain;
using lab8.Repositories;

namespace lab8.Service
{
    public class GradeService
    {

        private readonly GradeRepository _gradeRepository;

        public GradeService(GradeRepository gradeRepository)
        {
            _gradeRepository = gradeRepository;
        }

        public List<Grade> GetAllGrades()
        {
                return _gradeRepository.GetAll();
        }

        public void AddGrade(Grade grade)
        {
            _gradeRepository.Add(grade);
        }

        public void UpdateGrade(Grade grade)
        {
            _gradeRepository.Update(grade);
        }
         public void DeleteGrade(int id)
        {
            Grade grade= _gradeRepository.GetById(id);
            _gradeRepository.Delete(grade);
        }

        public Grade GetById(int id)
        {
            return _gradeRepository.GetById(id);
        }

        public bool GradeExists(int studentId, int courseId)
        {
            return _gradeRepository.GradeExists(studentId, courseId);
        }

        public void SaveGrade(int studentId, int courseId, decimal grade)
        {
            _gradeRepository.SaveGrade(studentId, courseId, grade);
        }

        public List<StudentCourseGradeRow> GetGradesForStudent(int studentId)
        {
            return _gradeRepository.GetGradesForStudent(studentId);
        }
    }
}
